<?PHP

require_once('../../../default/settings.php');

print_r($databases);

$db = $databases['default']['default'];

$mysqli = new mysqli(
  $db['host'],
  $db['username'],
  $db['password'],
  $db['database']
);


  $keyword = 'foobar';
  $argument_count = 1;
  $namespace_ids = array(1,2);

_serchilo_find_command('foobar', 1, $namespace_ids, $mysqli);

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

  print_r($row);
  return $row;

}


