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

  list($keyword, $arguments, $extra_namespace_id) = _serchilo_parse_query($query);

  $namespace_ids = array(1,2, $extra_namespace_id);
  print_r($namespace_ids);

$command = _serchilo_find_command($keyword, count($arguments), $namespace_ids);
echo '<pre>';
print_r($command);


// TODO:
// default_keyword
