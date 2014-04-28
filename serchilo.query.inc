<?PHP

function _serchilo_find_command($keyword, $argument_count, $namespace_ids) {

  global $mysqli;

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
  if (!$result) {
    return; 
  }
  $row = $result->fetch_assoc();

  return $row;
}

function _serchilo_parse_query($query) {
  list($keyword, $arguments) = _serchilo_extract_keyword_and_arguments($query);
  list($keyword, $extra_namespace_id) = _serchilo_get_extra_namespace_from_keyword($keyword);
  return array($keyword, $arguments, $extra_namespace_id);
}

function _serchilo_get_extra_namespace_from_keyword($keyword) {
  # try to extract extra namespace from query
  # e.g.: de.w berlin
  $extra_namespace_id = 0;
  if (strpos($keyword,'.') !== false) {
    list($namespace_name, $keyword) = explode('.', $keyword, 2);
    $extra_namespace_id = _serchilo_get_namespace_id($namespace_name);
  }
  return array($keyword, $extra_namespace_id);
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

function _serchilo_get_namespace_id($namespace_name) {

  global $mysqli;

  $sql = "
    SELECT *
    FROM taxonomy_term_data
    WHERE
    vid = " . (int) NAMESPACE_VOCABULARY_ID .  "
    AND
    name = '" . $mysqli->real_escape_string($namespace_name) . "' 
  ";
  $result = $mysqli->query($sql);
  if (!$result) {
    return 0; 
  }
  $row = $result->fetch_assoc();
  return $row['tid'];
  
}
