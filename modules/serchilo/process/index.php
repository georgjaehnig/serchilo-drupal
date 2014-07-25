<?PHP

require_once('../serchilo.constants.inc');
require_once('serchilo.query.inc');

_serchilo_connect_db();

define('NAMESPACE_VOCABULARY_ID', _serchilo_get_values_from_table('taxonomy_vocabulary', 'machine_name', 'namespaces', 'vid')[0]);

_serchilo_dispatch();

# --------------------------------

/**
 * Connect to the database using Drupal's settings.
 * Remeber connection in global $mysqli.
 */
function _serchilo_connect_db() {

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
 * Can be a command call ('console') to redirect to a target
 * or an AJAX ('ajax') call to get some JSON (for autocomplete).
 */
function _serchilo_dispatch() {

  $page_type = $_GET['page_type'];

  # can be:
  # 'n' (e.g. n/en.usa) or 
  # 'u' (e.g. u/admin)
  $call_type = $_GET['call_type'];

  switch ($page_type) {
  case CONSOLE:
    _serchilo_process_query_console($call_type);
    break;
  case AUTOCOMPLETE_PATH_AFFIX:
    _serchilo_process_query_ajax($call_type);
    break;
  case OPENSEARCH_SUGGESTIONS_PATH_AFFIX:
    _serchilo_process_opensearch_suggestions($call_type);
    break;
  }
}

/**
 * Process a command call query.
 *
 * @param string $call_type
 *   Can be 
 *   'n' for a call with namespaces or
 *   'u' for a call with a username.
 */
function _serchilo_process_query_console($call_type) {

  $query = $_GET['query'];

  switch ($call_type) {
  case 'n':
    $namespace_names = _serchilo_get_namespace_names_from_path();
    list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
    $namespace_ids = array_map('_serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));
    break;
  case 'u':
    list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
    $user_name = _serchilo_get_user_name_from_path();
    $namespace_ids = _serchilo_get_namespace_ids_from_user($user_name);
    break;
  }

  // TODO:
  // default_keyword
  $command = _serchilo_find_command($keyword, count($arguments), $namespace_ids);
  #print_r($variables);
  #print_r($command);
  if ($command) {
    $variables = _serchilo_get_url_variables($namespace_names, $extra_namespace_name);
    _serchilo_call_command($command, $arguments, $variables);
  }
  else {
    // redirect to Serchilo website
    $url = $_SERVER['REQUEST_URI'] . '&status=not_found';
    header('Location: ' . $url );
  }
}

/**
 * Process a AJAX query.
 *
 * @param string $call_type
 *   Can be 
 *   'n' for a call with namespaces or
 *   'u' for a call with a username.
 */
function _serchilo_process_query_ajax($call_type) {

  $query = $_GET['term'];

  switch ($call_type) {
  case 'n':
    $namespace_names = _serchilo_get_namespace_names_from_path(1);
    list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
    $namespace_ids = array_map('_serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));
    break;
  case 'u':
    list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
    $user_name = _serchilo_get_user_name_from_path(1);
    $namespace_ids = _serchilo_get_namespace_ids_from_user($user_name);
    break;
  }

  $commands = _serchilo_search_commands( $keyword, $arguments, $query, $namespace_ids );
  
  // filter keys that are allowed to be public
  $commands = array_map(
    function($command) {
      $filtered_command = array(
        $command['nid'], 
        $command['keyword'], 
        $command['argument_names'], 
        $command['title'], 
        $command['namespace_name'], 
        (int) $command['reachable'], 
      );
      return $filtered_command;
    },
    $commands
  );

  require_once('../../../../../includes/common.inc');
  require_once('../../../../../includes/bootstrap.inc');
  drupal_json_output($commands);
}

/**
 * Process an Opensearch suggestions query.
 *
 * @param string $call_type
 *   Can be 
 *   'n' for a call with namespaces or
 *   'u' for a call with a username.
 */
function _serchilo_process_opensearch_suggestions($call_type) {

  $query = $_GET['query'];

  switch ($call_type) {
  case 'n':
    $namespace_names = _serchilo_get_namespace_names_from_path(1);
    list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
    $namespace_ids = array_map('_serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));
    break;
  case 'u':
    list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
    $user_name = _serchilo_get_user_name_from_path(1);
    $namespace_ids = _serchilo_get_namespace_ids_from_user($user_name);
    break;
  }

  $commands = _serchilo_search_commands( $keyword, $arguments, $query, $namespace_ids );
  
  $completions = array();
  $descriptions = array();

  foreach ($commands as $command) {

    # add braces to argument names
    $argument_names_braces = array();

    foreach (explode(',', $command['argument_names']) as $argument_name) {

      $argument_name = trim($argument_name);
      if ($argument_name == '') {
        continue; 
      }
      $argument_names_braces[] = '{' . $argument_name . '}';
    }

    $completions[] = 
      # add namespace to keyword if not reachable
      ( (bool) $command['reachable'] ? '' : $command['namespace_name'] . '.' ) .
      $command['keyword'] . 
      ' ' .
      join(', ', $argument_names_braces) . 
      '';
    $descriptions[] = $command['title']; 
  }

  $output = array(
    $query,
    $completions,
    $descriptions, 
  );

  require_once('../../../../../includes/common.inc');
  require_once('../../../../../includes/bootstrap.inc');
  drupal_json_output($output);
}

