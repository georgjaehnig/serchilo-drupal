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
  echo '<pre>b';
  print_r($namespace_names);

  list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
  $namespace_ids = array_map('_serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));

  echo $keyword;
  $command = _serchilo_find_command($keyword, count($arguments), $namespace_ids);
  $variables = _serchilo_get_url_variables($namespace_names, $extra_namespace_name);

  require_once('../../../../../includes/common.inc');
  require_once('../../../../../includes/bootstrap.inc');

  drupal_json_output('fsdf');
  return;
  print_r($command);

  echo
    '[[3,"g","","Google Web Homepage","o",1],[5977,"g","query","Google.es","admin",1],[138,"g+","","Google Plus","o",1],[837,"gb","","Google Blog Search","o",1],[4842,"gbooks","","Google Books","o",1],[24,"gcal","","Google Calendar","o",1],[6031,"gco","","Google Contacts","o",1],[4804,"gdr","","Google Drive","o",1],[0,"!t","g","All commands with \u003Cem class=\u0022placeholder\u0022\u003Eg\u003C\/em\u003E in the title",null,1,"http:\/\/www.serchilo.net\/commands?title=g"],[0,"!u","g","All commands with \u003Cem class=\u0022placeholder\u0022\u003Eg\u003C\/em\u003E in the URL",null,1,"http:\/\/www.serchilo.net\/commands?url=g"]]';

}

