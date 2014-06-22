<?PHP

define('STAR_NAMESPACE', 'o');

require_once('serchilo.query.inc');

_serchilo_connect_db();

define('NAMESPACE_VOCABULARY_ID', _serchilo_get_values_from_table('taxonomy_vocabulary', 'machine_name', 'namespaces', 'vid')[0]);

_serchilo_dispatch();

# --------------------------------

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

function _serchilo_dispatch() {

  $page_type = $_GET['page_type'];

  switch ($page_type) {
  case 'console':
    _serchilo_process_query_console();
    break;
  case 'ajax':
    _serchilo_process_query_ajax();
    break;
  }
}

function _serchilo_process_query_console() {

  $query = $_GET['query'];

  # can be:
  # 'n' (e.g. n/en.usa) or 
  # 'u' (e.g. u/admin)
  $call_type = $_GET['call_type'];

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

  #echo '<pre>';
  #print_r($namespace_ids);
  // TODO:
  // default_keyword
  $command = _serchilo_find_command($keyword, count($arguments), $namespace_ids);
  $variables = _serchilo_get_url_variables($namespace_names, $extra_namespace_name);
  #print_r($variables);
  #print_r($command);
  if ($command) {
    _serchilo_call_command($command, $arguments, $variables);
  }
  else {
    // redirect to serchilo website
  }
}

function _serchilo_process_query_ajax() {

  $query = $_GET['term'];
  $namespace_names = _serchilo_get_namespace_names_from_path(1);

  list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
  $namespace_ids = array_map('_serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));

  $commands = _serchilo_search_commands( $keyword, $arguments, $query, $namespace_ids );
  
  // filter keys that are allowed to be public
  $commands = array_map(
    function($command) {
      $filtered_command = array_intersect_key($command, array_flip(array('nid', 'keyword', 'arguments', 'title', 'namespace_name', 'reachable')));
      $filtered_command_values = array_values($filtered_command);
      return $filtered_command_values;
    },
    $commands
  );

  require_once('../../../../../includes/common.inc');
  require_once('../../../../../includes/bootstrap.inc');
  drupal_json_output($commands);
}

