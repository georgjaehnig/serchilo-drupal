<?PHP

/**
 * Find a shortcut.
 *
 * @param string $keyword
 *   Keyword of shortcut to be found.
 * @param int $argument_count
 *   Argument count of shortcut to be found.
 * @param array $namespace_ids
 *   Array of namespace IDs
 *   in which the shortcut must be part of.
 * @return
 *   Associative array of the found shortcut.
 */
function serchilo_find_shortcut($keyword, $argument_count, $namespace_ids) {

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

/**
 * Search for shortcuts.
 *
 * @param string $keyword
 *   Keyword of shortcuts to be found.
 * @param int $argument_count
 *   Argument count of shortcuts to be found.
 * @param string $query
 *   Full entered query, also to be used for searching
 * @param array $namespace_ids
 *   Array of namespace IDs
 *   in which the shortcut must be part of.
 * @param int $limit
 *   Maximum number of returned shortcuts.
 * @return
 *   Array of associative arrays of the found shortcuts.
 */
function serchilo_search_shortcuts( $keyword, $arguments, $query, $namespace_ids, $limit = 20 ) {

  global $mysqli;

  if ($keyword == '') {
    return array(); 
  }

  # use only extra_namespace when searching

  $order_namespace_ids = array_map(
    function ($namespace_id) {
      return 'namespace_id = ' . (int) $namespace_id . ' DESC';
    },
    array_reverse( $namespace_ids )
  );

  $sql ="
    
SELECT
  *,
  nid,
  nid=(
    SELECT 
      nid  
    FROM 
      serchilo_shortcut AS csub
    WHERE 
      csub.nid = c.nid
      AND
      argument_count = c.argument_count
      AND
      keyword = c.keyword
      AND
      namespace_id IN (" . join(',', $namespace_ids) .  ")
    ORDER BY
      " . join(",", $order_namespace_ids ). "
      LIMIT 1
  ) AS reachable
FROM 
  serchilo_shortcut AS c

WHERE 

  invisible = 0

  AND
  argument_count >= :argument_count
  AND (
    keyword LIKE :keyword_like_both OR 
    title LIKE :keyword_like_both 
    #OR
    # match tags
    #ttd.name LIKE :keyword_like_both 
  )

  # if extra_namespace_id set:
  # shortcut MUST be in extra_namespace 
  AND IF (
    :extra_namespace_id, 
    namespace_id = :extra_namespace_id, 
    TRUE
  )
  GROUP BY nid

ORDER BY
  reachable DESC,

  keyword = :keyword DESC,
  keyword LIKE :keyword_like_right DESC,

  argument_count, 

  # keyword-keyword matches
  keyword LIKE :keyword_like_both DESC,

  title = :keyword DESC,
  title LIKE :keyword_like_right DESC,
  title LIKE :keyword_like_both DESC,

  title = :query DESC,
  title LIKE :query_like_right DESC,
  title LIKE :query_like_both DESC,

  keyword,
  title

LIMIT " . (int) $limit . ";

  ";

  $sql = serchilo_replace_sql_arguments(
    $mysqli, 
    $sql,
    array(
      # note: when prefix is the same
      # put short placeholder below
      'argument_count' => count($arguments), 
      'extra_namespace_id' => (isset($extra_namespace) ? $extra_namespace->tid : null),
      'keyword_like_right' => $keyword . '%',
      'keyword_like_both' => '%' . $keyword . '%',
      'keyword' => $keyword,
      'query_like_right' => $query . '%',
      'query_like_both' => '%' . $query . '%',
      'query' => $query,
      'limit' => (int) $limit,
    )
  );

  $mysqli->set_charset("utf8");
  $result = $mysqli->query($sql);
  if (!$result) {
    return; 
  }
  $shortcuts = $result->fetch_all(MYSQLI_ASSOC);

  return $shortcuts;
}

/**
 * Parse a query.
 *
 * @param string $query
 *   The query to parse.
 * @return
 *   Keyed Array of query items:
 *   - keyword
 *   - arguments
 *   - extra_namespace_name
 */
function serchilo_parse_query($query) {
  $env = serchilo_extract_keyword_and_arguments($query);
  $env = serchilo_get_extra_namespace_from_keyword($env['keyword']) + $env;
  return $env;
}

/**
 * Extract optional extra namespace from the keyword.
 *
 * @param string $keyword
 *   The keyword to extract from.
 * @return
 *   Keyed array with 
 *   - keyword 
 *   - extra namespace (empty string if not existing).
 */
function serchilo_get_extra_namespace_from_keyword($keyword) {
  # try to extract extra namespace from query
  # e.g.: de.w berlin
  $extra_namespace_name = '';
  if (strpos($keyword,'.') !== false) {
    list($extra_namespace_name, $keyword) = explode('.', $keyword, 2);
  }
  return array(
    'keyword' => $keyword, 
    'extra_namespace_name' => $extra_namespace_name
  );
}

/**
 * Extract keyword and arguments from a query.
 *
 * @param string $query
 *   The query to extract from.
 * @param int $max_arguments
 *   Maximum number of arguments to extract.
 *   Default: unlimited
 * @return
 *   Keyed array with
 *   - keyword 
 *   - arguments.
 */
function serchilo_extract_keyword_and_arguments($query, $max_arguments = -1) {

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
  return array(
    'keyword'   => $keyword, 
    'arguments' => $arguments
  );
}


/**
 * Get the namespace ID from a namespace name.
 *
 * @param string $namespace_name
 *   The namespace name.
 * @return
 *   ID of given namespace name.
 *   0 if not found.
 */
function serchilo_get_namespace_id($namespace_name) {

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
  if ($result->num_rows == 0) {
    return 0; 
  }
  $row = $result->fetch_assoc();
  return $row['tid'];
}

function serchilo_call_shortcut($shortcut, $arguments, $variables, $redirect = TRUE) {
  
/*
  $language_namespace = drupal_static('language_namespace');
  $country_namespace = drupal_static('country_namespace');
  $user_namespace = drupal_static('user_namespace');

  $extra_namespace = drupal_static('extra_namespace');

  # take language from extra_namespace
  # if it is a language namespace
  if (
    ($extra_namespace) &&
    ( 'language' == array_shift(serchilo_field_get_items_taxonomy_term_names('taxonomy_term', $extra_namespace, 'field_namespace_type')) )
  ) {
    $language_namespace = $extra_namespace;
  }

  $variables = array(
    'language' => $language_namespace->name, 
    'country:alpha3' => $country_namespace->name, 
    'user:name' => ($user_namespace ? $user_namespace->name : ''), 
    'user:id' => ($user_namespace ? user_load_by_name($user_namespace->name)->uid : ''), 
  );

  if (strpos($shortcut->url, '{country:alpha2}') !== false) {
    module_load_include('inc', 'serchilo', 'serchilo.countries');
    $variables['country:alpha2'] = serchilo_country_alpha3_to_alpha2($country_namespace->name);
  }
 */

  $input_encoding = $shortcut['input_encoding'];

  $url = serchilo_replace_url_arguments($shortcut['url'], $arguments, $variables, $input_encoding);

  //serchilo_log_call($shortcut, $arguments);
  
  // Debugging: Only output URL.
  if (!$redirect) {
    return $url;
  }

  if (empty($shortcut['set_referrer'])) {
    // Classic redirect.
    header('Location: ' . $url);
    exit();
  }
  else {
    // Redirect via HTML page
    // for shortcuts which need a referrer.
    serchilo_redirect_via_html($url);
    exit();
  }
}

function serchilo_redirect_via_html($url) {
  require_once('tpl/serchilo-redirect.tpl.php'); 
}

function serchilo_replace_url_arguments($url, $arguments, $variables, $input_encoding = 'utf-8')
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

function serchilo_get_url_variables($env) {
  $variables = array();
  $variables['language'] = $env['language_namespace_name'];
  $variables['country:alpha3'] = $env['country_namespace_name'];
  switch (strlen($env['extra_namespace_name'])) {
    case 2:
      $variables['language'] = $env['extra_namespace_name'];
      break;
    case 3:
      $variables['country:alpha3'] = $env['extra_namespace_name'];
      break;
  }
  // TODO:
  // country:alpha2
  //    check ob benutzt
  // user:name
  // user:id
  return $variables;
}

function serchilo_replace_sql_arguments($mysqli, $sql_template, $arguments, $left_delimiter = ':', $right_delimiter = '') {
  $sql_replaced = $sql_template;
  foreach ($arguments as $key=>$value) {
    $value_escaped = $mysqli->real_escape_string($value);
    $sql_replaced = str_replace($left_delimiter . $key . $right_delimiter, "'" . $value_escaped . "'", $sql_replaced);
  }
  return $sql_replaced;
}

function serchilo_get_namespace_ids_from_user($user_name) {

  $user_id = serchilo_get_values_from_table('users', 'name', $user_name, 'uid', TRUE)[0];

  $star_namespace_id     = serchilo_get_namespace_id(STAR_NAMESPACE);
  $language_namespace_id = serchilo_get_values_from_table('field_data_field_language_namespace', 'entity_id', $user_id, 'field_language_namespace_tid')[0];
  $country_namespace_id  = serchilo_get_values_from_table('field_data_field_country_namespace', 'entity_id', $user_id, 'field_country_namespace_tid')[0];
  $custom_namespace_ids  = serchilo_get_values_from_table('field_data_field_custom_namespaces', 'entity_id', $user_id, 'field_custom_namespaces_tid');

  $namespace_ids = array_merge(
    array(
      $star_namespace_id, 
      $language_namespace_id, 
      $country_namespace_id
    ),
    $custom_namespace_ids
  );

  return $namespace_ids;
}

function serchilo_get_values_from_table($table, $where_column_name, $where_value, $value_column_name) {

  global $mysqli;

  $sql = "
    SELECT $value_column_name
    FROM $table
    WHERE
    $where_column_name = '" . $mysqli->real_escape_string($where_value) . "' 
  ";

  $result = $mysqli->query($sql);
  
  $values = array();
  if ($result->num_rows > 0) {
    $rows = $result->fetch_all();
    $values = array_map(function($row) { return array_shift($row); }, $rows);
  }
  return $values;
}

function serchilo_get_path_elements() {
  $path = $_SERVER['REDIRECT_URL'];
  // example: '/n/en.usa'
  $path_elements = explode('/', $path);
  return $path_elements;
}

function serchilo_get_namespace_names_from_path($path_elements_offset = 0) {
  $path_elements = serchilo_get_path_elements();
  if ('n' == $path_elements[$path_elements_offset + 1]) {
    $namespace_names = explode('.', $path_elements[$path_elements_offset + 2]);
    array_unshift($namespace_names, STAR_NAMESPACE);
    return $namespace_names;
  }
}

function serchilo_get_user_name_from_path($path_elements_offset = 0) {
  $path_elements = serchilo_get_path_elements();
  if ('u' == $path_elements[$path_elements_offset + 1]) {
    return $path_elements[$path_elements_offset + 2];
  }
}

function serchilo_get_default_keyword($user_name = NULL) {

  // Setting via GET parameter has always the highest priority.
  if (!empty($_GET['default_keyword'])) {
    return $_GET['default_keyword'];
  }
  if ($user_name) {
    $user_id         = serchilo_get_values_from_table('users', 'name', $user_name, 'uid')[0];
    $default_keyword = serchilo_get_values_from_table('field_data_field_default_keyword', 'entity_id', $user_id, 'field_default_keyword_value')[0];
    return $default_keyword;
  }
  return NULL;
}
