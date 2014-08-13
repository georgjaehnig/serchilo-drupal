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

  $page_type = $_GET['page_type'];

  # can be:
  # 'n' (e.g. n/en.usa) or 
  # 'u' (e.g. u/admin)
  $call_type = $_GET['call_type'];

  switch ($page_type) {
  case CONSOLE:
    serchilo_process_query_console($call_type);
    break;
  case AUTOCOMPLETE_PATH_AFFIX:
    serchilo_process_query_ajax($call_type);
    break;
  case OPENSEARCH_SUGGESTIONS_PATH_AFFIX:
    serchilo_process_opensearch_suggestions($call_type);
    break;
  }
}

/**
 * Process a shortcut call query.
 *
 * @param string $call_type
 *   Can be 
 *   'n' for a call with namespaces or
 *   'u' for a call with a username.
 */
function serchilo_process_query_console($call_type) {

  $query = $_GET['query'];

  switch ($call_type) {
  case 'n':
    $namespace_names = serchilo_get_namespace_names_from_path();
    list($keyword, $arguments, $extra_namespace_name) = serchilo_parse_query($query);
    $namespace_ids = array_map('serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));
    break;
  case 'u':
    list($keyword, $arguments, $extra_namespace_name) = serchilo_parse_query($query);
    $user_name = serchilo_get_user_name_from_path();
    $namespace_ids = serchilo_get_namespace_ids_from_user($user_name);

    $language_namespace_name = serchilo_get_values_from_table('taxonomy_term_data', 'tid', $namespace_ids['1'], 'name')[0];
    $country_namespace_name  = serchilo_get_values_from_table('taxonomy_term_data', 'tid', $namespace_ids['2'], 'name')[0];

    $namespace_names[1] = $language_namespace_name;
    $namespace_names[2] = $country_namespace_name;
    break;
  }
  // Find shortcut and call it.
  $shortcut = serchilo_find_shortcut($keyword, count($arguments), $namespace_ids);
  if ($shortcut) {
    $variables = serchilo_get_url_variables($namespace_names, $extra_namespace_name);
    serchilo_call_shortcut($shortcut, $arguments, $variables);
  }

  // Try again with default keyword.
  $default_keyword = serchilo_get_default_keyword($user_name ?: NULL);
  $query = $default_keyword . ' ' . $query;
  list($keyword, $arguments, $extra_namespace_name) = serchilo_parse_query($query);

  // Find shortcut and call it.
  $shortcut = serchilo_find_shortcut($keyword, count($arguments), $namespace_ids);
  if ($shortcut) {
    $variables = serchilo_get_url_variables($namespace_names, $extra_namespace_name);
    serchilo_call_shortcut($shortcut, $arguments, $variables);
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
 * @param string $call_type
 *   Can be 
 *   'n' for a call with namespaces or
 *   'u' for a call with a username.
 */
function serchilo_process_query_ajax($call_type) {

  $query = $_GET['term'];

  switch ($call_type) {
  case 'n':
    $namespace_names = serchilo_get_namespace_names_from_path(1);
    list($keyword, $arguments, $extra_namespace_name) = serchilo_parse_query($query);
    $namespace_ids = array_map('serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));
    break;
  case 'u':
    list($keyword, $arguments, $extra_namespace_name) = serchilo_parse_query($query);
    $user_name = serchilo_get_user_name_from_path(1);
    $namespace_ids = serchilo_get_namespace_ids_from_user($user_name);
    break;
  }

  $shortcuts = serchilo_search_shortcuts( $keyword, $arguments, $query, $namespace_ids );
  
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
 * @param string $call_type
 *   Can be 
 *   'n' for a call with namespaces or
 *   'u' for a call with a username.
 */
function serchilo_process_opensearch_suggestions($call_type) {

  $query = $_GET['query'];

  switch ($call_type) {
  case 'n':
    $namespace_names = serchilo_get_namespace_names_from_path(1);
    list($keyword, $arguments, $extra_namespace_name) = serchilo_parse_query($query);
    $namespace_ids = array_map('serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));
    break;
  case 'u':
    list($keyword, $arguments, $extra_namespace_name) = serchilo_parse_query($query);
    $user_name = serchilo_get_user_name_from_path(1);
    $namespace_ids = serchilo_get_namespace_ids_from_user($user_name);
    break;
  }

  $shortcuts = serchilo_search_shortcuts( $keyword, $arguments, $query, $namespace_ids );
  
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
    $query,
    $completions,
    $descriptions, 
  );

  header('Content-Type: application/json');
  echo json_encode($output, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT);
  exit();
}

