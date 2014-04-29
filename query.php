<?PHP

define('NAMESPACE_VOCABULARY_ID', 1);

require_once('../../../default/settings.php');
require_once('serchilo.query.inc');

$db = $databases['default']['default'];

$mysqli = new mysqli(
  $db['host'],
  $db['username'],
  $db['password'],
  $db['database']
);


$query = $_GET['query'];

$namespace_names = _serchilo_get_namespace_names();
list($keyword, $arguments, $extra_namespace_name) = _serchilo_parse_query($query);
$namespace_ids = array_map('_serchilo_get_namespace_id', array_merge($namespace_names, array($extra_namespace_name)));

echo '<pre>';
print_r($namespace_ids);

$command = _serchilo_find_command($keyword, count($arguments), $namespace_ids);
print_r($command);
if ($command) {
  echo _serchilo_call_command($command, $arguments, FALSE);
}
else {
  // redirect to serchilo website
}


// TODO:
// default_keyword

