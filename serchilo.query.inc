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
    join(',', array_map(function($v) { return "namespace_id = " . (int) $v . " DESC";  }, array_reverse($namespace_ids))) 
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
  list($keyword, $extra_namespace_name) = _serchilo_get_extra_namespace_from_keyword($keyword);
  return array($keyword, $arguments, $extra_namespace_name);
}

function _serchilo_get_extra_namespace_from_keyword($keyword) {
  # try to extract extra namespace from query
  # e.g.: de.w berlin
  $extra_namespace_name = '';
  if (strpos($keyword,'.') !== false) {
    list($extra_namespace_name, $keyword) = explode('.', $keyword, 2);
  }
  return array($keyword, $extra_namespace_name);
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

function _serchilo_get_namespace_names() {
  $path = $_SERVER['REDIRECT_URL'];
  // example: '/n/en.usa'
  $path_elements = explode('/', $path);
  switch ($path_elements[1]) {
    case 'n':
      $namespace_names = explode('.', $path_elements[2]);
      return $namespace_names;
      break;
    case 'u':
      // evtl user namespaces zwischenspeichern in
      // serchilo_users_namespaces
      break;
  }
}

function _serchilo_call_command($command, $arguments, $redirect = TRUE) {
  
/*
  $language_namespace = drupal_static('language_namespace');
  $country_namespace = drupal_static('country_namespace');
  $user_namespace = drupal_static('user_namespace');

  $extra_namespace = drupal_static('extra_namespace');

  # take language from extra_namespace
  # if it is a language namespace
  if (
    ($extra_namespace) &&
    ( 'language' == array_shift(_serchilo_field_get_items_taxonomy_term_names('taxonomy_term', $extra_namespace, 'field_namespace_type')) )
  ) {
    $language_namespace = $extra_namespace;
  }

  $variables = array(
    'language' => $language_namespace->name, 
    'country:alpha3' => $country_namespace->name, 
    'user:name' => ($user_namespace ? $user_namespace->name : ''), 
    'user:id' => ($user_namespace ? user_load_by_name($user_namespace->name)->uid : ''), 
  );

  if (strpos($command->url, '{country:alpha2}') !== false) {
    module_load_include('inc', 'serchilo', 'serchilo.countries');
    $variables['country:alpha2'] = serchilo_country_alpha3_to_alpha2($country_namespace->name);
  }
 */
  $variables = array();

  $input_encoding = $command['input_encoding'];

  $url = _serchilo_replace_arguments($command['url'], $arguments, $variables, $input_encoding);

  //_serchilo_log_call($command, $arguments);
  
  if ($redirect) {
    if (empty($command['set_referrer'])) {
      // classic redirect
      drupal_goto($url);
    }
    else {
      // redirect for (paid) commands which need a referrer
      _serchilo_redirect_via_html($url);
    }
  } else {
    return $url;
  }
   
  #drupal_set_message($url);
  #return '.';
}

function _serchilo_replace_arguments($url, $arguments, $variables, $input_encoding = 'utf-8')
{
  foreach ($variables as $key=>$value) {
    $url = str_replace(
      '{' . $key . '}',
      $value,
      $url
    );
  }

  foreach ($arguments as $argument) {
    preg_match(
      '/\{s:(.+?)\}/',
      $url,
      $matches
    );
    if (!count($matches)) {
      continue; 
    } 

    switch($input_encoding) {
      // probably unnecessary, since the option is already not within the Input-encoding dropdown
      case 'double-urlencode':
        $argument = rawurlencode(rawurlencode(utf8_decode($argument)));
        break;
      case 'none':
        $argument = utf8_decode($argument);
        break;
      default:
        # if encoding is valid
        if (in_array(strtoupper($input_encoding), mb_list_encodings())) {
          $argument = mb_convert_encoding($argument, $input_encoding, 'utf-8');
        }
        $argument = rawurlencode($argument);
        break;
    }

    $url = str_replace(
      $matches[0],
      $argument,
      $url 
    );
  }
  return $url;
}
