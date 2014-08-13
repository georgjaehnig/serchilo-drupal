<?PHP

require_once('../serchilo.constants.inc');
require_once('serchilo.query.inc');

serchilo_connect_db();

define('NAMESPACE_VOCABULARY_ID', serchilo_get_values_from_table('taxonomy_vocabulary', 'machine_name', 'namespaces', 'vid')[0]);

serchilo_dispatch();

# --------------------------------

/**
 * Connect to the database using Drupal's settings.
 * Remeber connection in global $mysqli.
 */
function serchilo_connect_db() {

  global $mysqli;

  require_once('serchilo.settings.php');
  $db = $databases['default']['default'];

  $mysqli = new mysqli(
    $db['host'],
    $db['username'],
    $db['password'],
    $db['database']
  );
}

/**
 * Dispatch the request.
 * Can be a shortcut call ('console') to redirect to a target
 * or an AJAX ('ajax') call to get some JSON (for autocomplete).
 */
function serchilo_dispatch() {

  // The "environment".
  // Holds all relevant submitted and parsed data 
  // of the current request.
  $env = array();

  $env['page_type'] = $_GET['page_type'];
  $env['call_type'] = $_GET['call_type'];

  serchilo_populate_environment($env);

  switch ($env['page_type']) {
  case CONSOLE:
    serchilo_process_query_console($env);
    break;
  case AUTOCOMPLETE_PATH_AFFIX:
    serchilo_process_query_ajax($env);
    break;
  case OPENSEARCH_SUGGESTIONS_PATH_AFFIX:
    serchilo_process_opensearch_suggestions($env);
    break;
  }
}

/**
 * Process a shortcut call query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_process_query_console($env) {

  // Find shortcut and call it.
  $shortcut = serchilo_find_shortcut($env['keyword'], count($env['arguments']), $env['namespace_ids']);
  if ($shortcut) {
    $variables = serchilo_get_url_variables($env);
    serchilo_call_shortcut($shortcut, $env['arguments'], $variables);
  }

  // Try again with default keyword.
  $env['default_keyword'] = serchilo_get_default_keyword($env['user_name'] ?: NULL);
  $env['query'] = $env['default_keyword'] . ' ' . $env['query'];
  $env = serchilo_parse_query($env['query']) + $env;

  // Find shortcut and call it.
  $shortcut = serchilo_find_shortcut($env['keyword'], count($env['arguments']), $env['namespace_ids']);
  if ($shortcut) {
    $variables = serchilo_get_url_variables($env);
    serchilo_call_shortcut($shortcut, $env['arguments'], $variables);
  }

  // If all failed:
  // Redirect to Serchilo website.
  $url = $_SERVER['REQUEST_URI'] . '&status=not_found';
  header('Location: ' . $url );
  exit();

}

/**
 * Process a AJAX query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_process_query_ajax($env) {

  $shortcuts = serchilo_search_shortcuts($env['keyword'], $env['arguments'], $env['query'], $env['namespace_ids'] );
  
  // filter keys that are allowed to be public
  $shortcuts = array_map(
    function($shortcut) {
      $filtered_shortcut = array(
        $shortcut['nid'], 
        $shortcut['keyword'], 
        $shortcut['argument_names'], 
        $shortcut['title'], 
        $shortcut['namespace_name'], 
        (int) $shortcut['reachable'], 
      );
      return $filtered_shortcut;
    },
    $shortcuts
  );

  header('Content-Type: application/json');
  echo json_encode($shortcuts, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT);
  exit();
}

/**
 * Process an Opensearch suggestions query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_process_opensearch_suggestions($env) {

  $shortcuts = serchilo_search_shortcuts($env['keyword'], $env['arguments'], $env['query'], $env['namespace_ids'] );
  
  $completions = array();
  $descriptions = array();

  foreach ($shortcuts as $shortcut) {

    # add braces to argument names
    $argument_names_braces = array();

    foreach (explode(',', $shortcut['argument_names']) as $argument_name) {

      $argument_name = trim($argument_name);
      if ($argument_name == '') {
        continue; 
      }
      $argument_names_braces[] = '{' . $argument_name . '}';
    }

    $completions[] = 
      # add namespace to keyword if not reachable
      ( (bool) $shortcut['reachable'] ? '' : $shortcut['namespace_name'] . '.' ) .
      $shortcut['keyword'] . 
      ' ' .
      join(', ', $argument_names_braces) . 
      '';
    $descriptions[] = $shortcut['title']; 
  }

  $output = array(
    $env['query'],
    $completions,
    $descriptions, 
  );

  header('Content-Type: application/json');
  echo json_encode($output, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT);
  exit();
}

/**
 * Populate the environment array with
 * - keyword
 * - arguments
 * - namespace_ids
 * - language_namespace_name
 * - country_namespace_name
 * - user_name (optional).
 *
 * @param array $env
 *   The environment, holding already
 *   - call_type
 *     Can be 
 *     - 'n'
 *     - 'u'.
 *   - page_type
 *     Can be
 *     - CONSOLE
 *     - OPENSEARCH_SUGGESTIONS_PATH_AFFIX
 *     - AUTOCOMPLETE_PATH_AFFIX.
 *
 * @return void
 *
 */
function serchilo_populate_environment(&$env) {

  switch ($env['page_type']) {
  case CONSOLE:
    $env['query'] = $_GET['query'];
    $env['path_elements_offset'] = 0;
    break;
  case OPENSEARCH_SUGGESTIONS_PATH_AFFIX:
    $env['query'] = $_GET['query'];
    $env['path_elements_offset'] = 1;
    break;
  case AUTOCOMPLETE_PATH_AFFIX:
    $env['query'] = $_GET['term'];
    $env['path_elements_offset'] = 1;
    break;
  }

  switch ($env['call_type']) {

  case NAMESPACES_PATH_AFFIX:

    // Get namespace names.
    $env['namespace_names'] = serchilo_get_namespace_names_from_path($env['path_elements_offset']);
    $env['language_namespace_name'] = $env['namespace_names'][1];
    $env['country_namespace_name']  = $env['namespace_names'][2];

    // Parse the query and set keyword, arguments and extra_namespace_name.
    $env += serchilo_parse_query($env['query']);

    // Get namespace_ids from namespace_names.
    $env['namespace_ids'] = array_map(
      'serchilo_get_namespace_id', 
      array_merge(
        $env['namespace_names'], 
        array($env['extra_namespace_name'])
      )
    );

    break;

  case USER_PATH_AFFIX:

    // Parse the query and set keyword, arguments and extra_namespace_name.
    $env += serchilo_parse_query($env['query']);

    $env['user_name'] = serchilo_get_user_name_from_path($env['path_elements_offset']);
    $env['namespace_ids'] = serchilo_get_namespace_ids_from_user($env['user_name']);

    // Get namespace_names from namespace_ids.
    $env['language_namespace_name'] = serchilo_get_values_from_table('taxonomy_term_data', 'tid', $env['namespace_ids']['1'], 'name')[0];
    $env['country_namespace_name']  = serchilo_get_values_from_table('taxonomy_term_data', 'tid', $env['namespace_ids']['2'], 'name')[0];

    break;
  }
}
