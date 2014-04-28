<?PHP

require_once('../../../default/settings.php');

$db = $databases['default']['default'];

$mysqli = new mysqli(
  $db['host'],
  $db['username'],
  $db['password'],
  $db['database']
);

  $query = $_GET['query'];
  list($keyword, $arguments) = _serchilo_extract_keyword_and_arguments($query);

  $namespace_ids = array(1,2);

$command = _serchilo_find_command($keyword, count($arguments), $namespace_ids, $mysqli);
echo '<pre>';
print_r($command);

function _serchilo_find_command($keyword, $argument_count, $namespace_ids, $mysqli) {

  if ($argument_count > 0) {
    $sql_argument_count = 'argument_count > 0 AND argument_count <= ' . (int) $argument_count;
  }
  else {
    $sql_argument_count = 'argument_count = 0';
  }

  $sql = "
    SELECT * 
    FROM
    serchilo_shortcut 
    WHERE
    keyword = '" . $mysqli->real_escape_string($keyword) . "'
    AND
    $sql_argument_count
    AND
    namespace_id IN (" . join(',', $namespace_ids) .  ")
    ORDER BY
    " . 
    join(',', array_map(function($v) { return "namespace_id = " . (int) $v;  }, $namespace_ids )) 
    . "
    ";

  #echo $sql;
  #exit();

  $result = $mysqli->query($sql);
  $row = $result->fetch_assoc();

  return $row;
}


function _serchilo_extract_keyword_and_arguments($query, $max_arguments = -1) {

  # extract keyword and arguments
  $keyword_arguments = preg_split('/\s+/', $query, 2);
  $keyword = trim($keyword_arguments[0]);

  # if we have arguments
  if (count($keyword_arguments) > 1) {
    $arguments_str = $keyword_arguments[1];
    $arguments = preg_split('/\s*,\s*/', $arguments_str, $max_arguments);
    $arguments = array_map('trim', $arguments);
  }
  else {
    $arguments = array();
  }
  return array($keyword, $arguments);
}
