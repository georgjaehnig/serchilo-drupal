<?PHP

// TODO:
// better read out taxonomy_vocabulary (tiny table)
// by the machine name "namespace"
define('NAMESPACE_VOCABULARY_ID', 1);
define('STAR_NAMESPACE', 'o');

require_once('../../../../default/settings.php');
require_once('serchilo.query.inc');

$db = $databases['default']['default'];

$mysqli = new mysqli(
  $db['host'],
  $db['username'],
  $db['password'],
  $db['database']
);

$page_type = $_GET['page_type'];

switch ($page_type) {
case 'console':
  _serchilo_process_query_console();
  break;
case 'ajax':
  _serchilo_process_query_ajax();
  break;
}

function _serchilo_process_query_console() {
  $query = $_GET['query'];

  $namespace_names = _serchilo_get_namespace_names();
  list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
  $namespace_ids = array_map('_serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));

  echo '<pre>';
  print_r($namespace_ids);
  // TODO:
  // default_keyword
  $command = _serchilo_find_command($keyword, count($arguments), $namespace_ids);
  $variables = _serchilo_get_url_variables($namespace_names, $extra_namespace_name);
  print_r($variables);
  print_r($command);
  if ($command) {
    echo _serchilo_call_command($command, $arguments, $variables, FALSE);
  }
  else {
    // redirect to serchilo website
  }
}

function _serchilo_process_query_ajax() {

  $query = $_GET['term'];
  $namespace_names = _serchilo_get_namespace_names(1);

  list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
  $namespace_ids = array_map('_serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));

  $commands = _serchilo_search_commands( $keyword, $arguments, $query, $namespace_ids );
  
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

