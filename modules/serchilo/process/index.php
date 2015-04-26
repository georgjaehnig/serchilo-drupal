<?PHP

$execution_time_start = microtime(TRUE);

require_once('../serchilo.constants.inc');
require_once('../serchilo.shared.inc');

serchilo_connect_db();

define('NAMESPACE_VOCABULARY_ID', serchilo_get_values_from_table('taxonomy_vocabulary', 'machine_name', 'namespaces', 'vid')[0]);

serchilo_dispatch();

# --------------------------------

/**
 * Connect to the database using Drupal's settings.
 * Remeber connection in global $mysqli.
 */
function serchilo_connect_db() {

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

/**
 * Dispatch the request.
 * Can be a shortcut call ('console') to redirect to a target
 * or an AJAX ('ajax') call to get some JSON (for autocomplete).
 */
function serchilo_dispatch() {

  // The "environment".
  // Holds all relevant submitted and parsed data 
  // of the current request.
  $env = array();

  $env['page_type'] = $_GET['page_type'];
  $env['call_type'] = $_GET['call_type'];

  serchilo_populate_environment($env);

  switch ($env['page_type']) {
  case SERCHILO_CONSOLE:
    serchilo_process_query_console($env);
    break;
  case SERCHILO_AUTOCOMPLETE_PATH_AFFIX:
    serchilo_process_query_ajax($env);
    break;
  case SERCHILO_OPENSEARCH_SUGGESTIONS_PATH_AFFIX:
    serchilo_process_opensearch_suggestions($env);
    break;
  case SERCHILO_API_PATH_AFFIX:
    serchilo_process_query_api($env);
    break;
  case SERCHILO_URL_PATH_AFFIX:
    serchilo_process_query_url($env);
    break;
  }
}


// Dispatch helpers

/**
 * Populate the environment array with
 * - keyword
 * - arguments
 * - namespace_ids
 * - language_namespace_name
 * - country_namespace_name
 * - user_name (optional).
 *
 * @param array $env
 *   The environment, holding already
 *   - call_type
 *     Can be 
 *     - 'n'
 *     - 'u'.
 *   - page_type
 *     Can be
 *     - SERCHILO_CONSOLE
 *     - SERCHILO_OPENSEARCH_SUGGESTIONS_PATH_AFFIX
 *     - SERCHILO_AUTOCOMPLETE_PATH_AFFIX.
 *
 * @return void
 *
 */
function serchilo_populate_environment(&$env) {

  switch ($env['page_type']) {
  case SERCHILO_CONSOLE:
    $env['path_elements_offset'] = 0;
    $env = serchilo_handle_query_from_request() + $env;
    break;
  case SERCHILO_OPENSEARCH_SUGGESTIONS_PATH_AFFIX:
    $env['path_elements_offset'] = 1;
    $env = serchilo_handle_query_from_request() + $env;
    break;
  case SERCHILO_API_PATH_AFFIX:
  case SERCHILO_URL_PATH_AFFIX:
    if (isset($_GET['query'])) {
      $env = serchilo_handle_query_from_request() + $env;
    } else {
      $env['keyword']        = trim(serchilo_array_value($_GET, 'keyword'));
      $env['argument_count'] = serchilo_array_value($_GET, 'argument_count', 0);
      $env['arguments']      = array();
      $env = serchilo_get_extra_namespace_from_keyword($env['keyword']) + $env;
    }
    $env['path_elements_offset'] = 1;
    break;
  case SERCHILO_AUTOCOMPLETE_PATH_AFFIX:
    $env['path_elements_offset'] = 1;
    $env = serchilo_handle_query_from_request('term') + $env;
    break;
  }

  switch ($env['call_type']) {

  case SERCHILO_NAMESPACES_PATH_AFFIX:

    // Get namespace names.
    $env['namespace_names'] = serchilo_get_namespace_names_from_path($env['path_elements_offset']);
    $env['language_namespace_name'] = $env['namespace_names'][1];
    $env['country_namespace_name']  = $env['namespace_names'][2];

    // Add extra_namespace to namespace_names.
    if (!empty($env['extra_namespace_name'])) {
      $env['namespace_names'][] = $env['extra_namespace_name'];
    }
    // Get namespace_ids from namespace_names.
    $env['namespace_ids'] = array_map('serchilo_get_namespace_id', $env['namespace_names']);

    $env['timezone'] = serchilo_get_timezone($env);

    break;

  case SERCHILO_USER_PATH_AFFIX:

    $env['user_name'] = serchilo_get_user_name_from_path($env['path_elements_offset']);
    $env['user_id']   = serchilo_get_values_from_table('users', 'name', $env['user_name'], 'uid', TRUE)[0];
    $env['timezone']  = serchilo_get_timezone($env);

    $env['namespace_ids'] = serchilo_get_namespace_ids_from_user($env['user_name'], $env['user_id']);

    // Yes, one '=' is correct.
    if ($env['extra_namespace_id'] = serchilo_get_namespace_id($env['extra_namespace_name'])) {
      $env['namespace_ids'][] = $env['extra_namespace_id'];
    }

    // Get namespace_names from namespace_ids.
    $env['language_namespace_name'] = serchilo_get_values_from_table('taxonomy_term_data', 'tid', $env['namespace_ids']['1'], 'name')[0];
    $env['country_namespace_name']  = serchilo_get_values_from_table('taxonomy_term_data', 'tid', $env['namespace_ids']['2'], 'name')[0];

    break;
  }
}

/**
 * Get the timezone from the URL or from the user settings.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 *
 * @return string $timezone
 *   The timezone,
 *   NULL if not found.
 */
function serchilo_get_timezone($env) {

  if (!empty($_GET['timezone'])) {
    // TODO: Validate.
    return $_GET['timezone'];
  }
  if (!empty($env['user_id'])) {
    $timezone = serchilo_get_values_from_table('users', 'uid', $env['user_id'], 'timezone')[0];
    return $timezone;
  }
}

/**
 * Get and handle the query from the request URL
 *
 * @param string $param_name
 *   (optional) The param name in the request URL.
 *   Defaults to 'query'.
 *
 * @return array $env
 *   The return array with environment data from the query.
 */
function serchilo_handle_query_from_request($param_name = 'query') {

  $env = array();
  $env['query'] = serchilo_array_value($_GET, $param_name);
  $env['query'] = trim($env['query']);

  // Parse the query and set keyword, arguments and extra_namespace_name.
  $env += serchilo_parse_query($env['query']);

  return $env;
}


// Process

/**
 * Process a shortcut call query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_process_query_console($env) {

  $output = serchilo_get_output($env);

  if ($output['status']['found']) {

    serchilo_log_shortcut_call($output['#shortcut'], $env['page_type'], $output['status']['default_keyword_used']);

    if (!empty($output['url']['post_parameters'])) {
      // Redirect via HTML form
      // for shortcuts with POST parameters
      serchilo_redirect_via_form($output['url']['final'], $output['url']['post_parameters']);
      exit();
    }
    elseif (empty($output['#shortcut']['set_referrer'])) {
      // Classic redirect.
      header('Location: ' . $output['url']['final']);
      exit();
    }
    else {
      // Redirect via HTML page
      // for shortcuts which need a referrer.
      serchilo_redirect_via_meta($output['url']['final']);
      exit();
    }
  } 

  // If no shortcut found:

  // Get shortcut suggestions.
  $suggested_shortcuts = serchilo_search_shortcuts($env['keyword'], $env['arguments'], $env['query'], $env['namespace_ids'], $env['extra_namespace_name']);

  // Limit to 5 suggestions.
  $suggested_shortcuts = array_slice($suggested_shortcuts, 0, 5);

  // Take only the ID.
  $suggested_shortcut_ids = array_map(function($shortcut){ return $shortcut['nid']; }, $suggested_shortcuts);

  // Build the query parameter.
  $url = $_SERVER['REQUEST_URI'] . '&' . http_build_query(
    array(
      'status' => 'not_found', 
      'arguments' => $env['arguments'],
      'nids' => $suggested_shortcut_ids
    )
  );

  // Redirect to Serchilo website.
  header('Location: ' . $url );
  exit();
}

/**
 * Process a AJAX query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_process_query_ajax($env) {

  $shortcuts = serchilo_search_shortcuts($env['keyword'], $env['arguments'], $env['query'], $env['namespace_ids'], $env['extra_namespace_name'] );
  
  // filter keys that are allowed to be public
  $shortcuts = array_map(
    function($shortcut) {
      $filtered_shortcut = array(
        $shortcut['nid'], 
        $shortcut['keyword'], 
        $shortcut['argument_names'], 
        $shortcut['title'], 
        $shortcut['namespace_name'], 
        (int) $shortcut['reachable'], 
      );
      return $filtered_shortcut;
    },
    $shortcuts
  );

  serchilo_output_json($shortcuts);
}

/**
 * Process an Opensearch suggestions query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_process_opensearch_suggestions($env) {

  $shortcuts = serchilo_search_shortcuts($env['keyword'], $env['arguments'], $env['query'], $env['namespace_ids'] );
  
  $completions = array();
  $descriptions = array();

  foreach ($shortcuts as $shortcut) {

    # add braces to argument names
    $argument_names_braces = array();

    foreach (explode(',', $shortcut['argument_names']) as $argument_name) {

      $argument_name = trim($argument_name);
      if ($argument_name == '') {
        continue; 
      }
      $argument_names_braces[] = '{' . $argument_name . '}';
    }

    $completions[] = 
      # add namespace to keyword if not reachable
      ( (bool) $shortcut['reachable'] ? '' : $shortcut['namespace_name'] . '.' ) .
      $shortcut['keyword'] . 
      ' ' .
      join(', ', $argument_names_braces) . 
      '';
    $descriptions[] = $shortcut['title']; 
  }

  $output = array(
    $env['query'],
    $completions,
    $descriptions, 
  );

  serchilo_output_json($output);
}

/**
 * Process a shortcut API query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_process_query_api($env) {

  $output = serchilo_get_output($env);
  if ($output['status']['found']) {
    serchilo_log_shortcut_call($output['#shortcut'], $env['page_type'], $output['status']['default_keyword_used']);
  }
  unset($output['#shortcut']);
  serchilo_output_json($output);
}

/**
 * Process a shortcut URL query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_process_query_url($env) {

  $output = serchilo_get_output($env);

  if ($output['status']['found']) {
    serchilo_log_shortcut_call($output['#shortcut'], $env['page_type'], $output['status']['default_keyword_used']);
  }

  header('Content-Type: text/plain');
  if (!empty($output['url']['final'])) {
    echo $output['url']['final'];
  }
  else if (!empty($output['url']['replaced_variables'])) {
    echo $output['url']['replaced_variables'];
  }
}


// Process helpers

/**
 * Get the output given the environment.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 *
 * @return array $output
 *   Array holding all data of the found shortcut,
 *   ready to output as JSON
 */
function serchilo_get_output($env) {

  if (!empty($env['query'])) {

    // Try via query.
    $shortcut = serchilo_find_shortcut($env['keyword'], count($env['arguments']), $env['namespace_ids']);

    if ($shortcut) {

      $output = serchilo_shortcut_to_output($shortcut, $env);
      $output['status']['default_keyword_used'] = FALSE;

    } else {

      // Try via default_keyword.
      $env['default_keyword'] = serchilo_get_default_keyword($env['user_name'] ?: NULL);
      $env['query'] = $env['default_keyword'] . ' ' . $env['query'];
      $env = serchilo_parse_query($env['query']) + $env;

      // Add extra namespace from default keyword if present.
      if (!empty($env['extra_namespace_name'])) {
        $env['namespace_ids'][] = serchilo_get_namespace_id($env['extra_namespace_name']);
      }

      $shortcut = serchilo_find_shortcut($env['keyword'], count($env['arguments']), $env['namespace_ids']);
      if ($shortcut) {
        $output = serchilo_shortcut_to_output($shortcut, $env);
      }
      $output['status']['default_keyword_used'] = TRUE;
    }
  }

  else {

    // Try via keyword and argument_count.
    $shortcut = serchilo_find_shortcut($env['keyword'], $env['argument_count'], $env['namespace_ids']);
    if ($shortcut) {
      $output = serchilo_shortcut_to_output($shortcut, $env);
    }
    $output['status']['default_keyword_used'] = FALSE;
  }

  if (empty($output['url'])) {
    $output['status']['found'] = FALSE;
  }

  if (!empty($env['user_name'])) {
    $output['user']['name'] = $env['user_name'];
  }

  $output['version'] = 2;

  // Not set when calling via u/
  // .. so left out for now, maybe not needed.
  //$output['namespaces'] = $env['namespace_names'];

  return $output;
}

/**
 * Convert the found shortcut to an output array.
 *
 * @param array $shortcut
 *   The shortcut to call.
 * @param array $env
 *   The environment.
 *   
 * @return array $output
 *   The output.
 */
function serchilo_shortcut_to_output($shortcut, $env) {

  $output = array();
  $output['url']['template'] = $shortcut['url'];
  $variables = serchilo_get_url_variables($env);
  $output['url']['replaced_variables'] = serchilo_replace_variables($shortcut['url'],  $variables);

  // Reparse arguments if count does not match.
  if (count($env['arguments']) > $shortcut['argument_count']) {
    $env = serchilo_extract_keyword_and_arguments($env['query'], $shortcut['argument_count']) + $env;
  }

  // Create final URL if called with query
  // (and not with keyword/argument_count).
  if (!empty($env['query'])) {
    $output['url']['final'] = serchilo_replace_arguments(
      $output['url']['replaced_variables'],
      $env['arguments'],
      $env
    );
  }
  $output['status']['found']        = TRUE;
  $output['namespace']['name']      = $shortcut['namespace_name'];
  $output['url']['post_parameters'] = serchilo_get_post_parameters($shortcut, $env['arguments'], $variables, $env);
  $output['shortcut']['id']         = (int) $shortcut['nid'];

  $output['#shortcut'] = $shortcut;

  return $output;
}

/**
 * Return the post parameters of a shortcut
 *   and replace them with the query arguments and variables.
 *
 * @param array $shortcut
 *   The shortcut to call.
 * @param array $arguments
 *   The arguments from the query.
 * @param array $variables
 *   The variables.
 *   
 * @return array $post_parameters
 *   The post parameters.
 *   Empty array if none present.
 */
function serchilo_get_post_parameters($shortcut, $arguments, $variables, $env) {

  if (empty($shortcut['post_parameters'])) {
    return array(); 
  }
  $post_parameters_str = serchilo_replace_variables($shortcut['post_parameters'], $variables );
  $post_parameters_str = serchilo_replace_arguments($post_parameters_str, $arguments, $env);
  $post_parameters = array();
  foreach (explode('&', $post_parameters_str) as $post_parameter) {
    $keyValue = explode('=', $post_parameter, 2);
    if (count($keyValue) == 2) {
      $post_parameters[$keyValue[0]] = $keyValue[1];
    }
    else {
      $post_parameters[$keyValue[0]] = 1;
    }
  }
  return $post_parameters; 
}

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
 
    # Highest argument_count first
    argument_count DESC,

    # Rightmost namespaces first
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
 * @param string $extra_namespace_name
 *   Namespace to be forced for that query.
 *   in which the shortcut must be part of.
 * @param int $limit
 *   Maximum number of returned shortcuts.
 *
 * @return
 *   Array of associative arrays of the found shortcuts.
 */
function serchilo_search_shortcuts( $keyword, $arguments, $query, $namespace_ids, $extra_namespace_name = NULL, $limit = 20 ) {

  global $mysqli;

  // No keyword and no extra_namespace:
  // Return empty list.
  if (
    ($keyword == '') &&
    (empty($extra_namespace_name)) &&
    TRUE
  ) {
    return array(); 
  }

  // If set extra_namespace_name ...
  if (!empty($extra_namespace_name)) {
    // ... get its ID.
    $extra_namespace_id = serchilo_get_values_from_table('taxonomy_term_data', 'name', $extra_namespace_name, 'tid')[0];
    if (empty($extra_namespace_id)) {
      return array(); 
    }
  }

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
      argument_count = c.argument_count
      AND
      keyword = c.keyword
      AND
      namespace_id IN (" . join(',', $namespace_ids) .  ")
    ORDER BY
      # Rightmost namespaces first
      " . 
      join(',', array_map(function($v) { return "namespace_id = " . (int) $v . " DESC";  }, array_reverse($namespace_ids))) 
      . "
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

  # keyword-keyword matches
  keyword LIKE :keyword_like_both DESC,

  keyword = :keyword DESC,
  keyword LIKE :keyword_like_right DESC,

  # Short namespaces first, to get site namespaces first
  # TODO: Save namespace type as well and order by it directly
  LENGTH(namespace_name),

  argument_count, 

      " . join(",", $order_namespace_ids ). ",

  title = :keyword DESC,
  title LIKE :keyword_like_right DESC,
  title LIKE :keyword_like_both DESC,

  title = :query DESC,
  title LIKE :query_like_right DESC,
  title LIKE :query_like_both DESC,

  keyword,
  title,

  # Short keywords first
  LENGTH(keyword)

LIMIT " . (int) $limit . ";

  ";

  $sql = serchilo_replace_sql_arguments(
    $mysqli, 
    $sql,
    array(
      'argument_count'     => count($arguments),
      'extra_namespace_id' => (isset($extra_namespace_id) ? $extra_namespace_id : NULL),
      'keyword_like_right' => $keyword . '%',
      'keyword_like_both'  => '%' . $keyword . '%',
      'keyword'            => $keyword,
      'query_like_right'   => $query . '%',
      'query_like_both'    => '%' . $query . '%',
      'query'              => $query,
      'limit'              => (int) $limit,
    )
  );

  $mysqli->set_charset("utf8");
  $result = $mysqli->query($sql);
  if (!$result) {
    return array(); 
  }
  $shortcuts = $result->fetch_all(MYSQLI_ASSOC);

  return $shortcuts;
}


// Query 

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
function serchilo_parse_query($query, $max_arguments = -1) {

  $parsed['query'] = $query;

  $parsed = serchilo_extract_keyword_and_arguments($query, $max_arguments);
  $parsed = serchilo_get_extra_namespace_from_keyword($parsed['keyword']) + $parsed;
  
  // Lowercase the keyword.
  $parsed['keyword'] = strtolower($parsed['keyword']);

  return $parsed;
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


// Namespace 

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

  if (empty($namespace_name)) {
    return 0; 
  }
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

/**
 * Get the user's namespaces as IDs, i.e.
 *   - planet namespace
 *   - language namespace
 *   - country namespace
 *   - custom namespaces
 *   - user namespace.
 *
 * @return array $namespace_ids
 *   The Namespace IDs.
 */
function serchilo_get_namespace_ids_from_user($user_name, $user_id) {

  $star_namespace_id     = serchilo_get_namespace_id(SERCHILO_PLANET_NAMESPACE);
  $language_namespace_id = serchilo_get_values_from_table('field_data_field_language_namespace', 'entity_id', $user_id, 'field_language_namespace_tid')[0];
  $country_namespace_id  = serchilo_get_values_from_table('field_data_field_country_namespace', 'entity_id', $user_id, 'field_country_namespace_tid')[0];
  $custom_namespace_ids  = serchilo_get_values_from_table('field_data_field_custom_namespaces', 'entity_id', $user_id, 'field_custom_namespaces_tid');
  $user_namespace_id     = serchilo_get_values_from_table('taxonomy_term_data', 'name', $user_name, 'tid')[0];

  $namespace_ids = array_merge(
    array(
      $star_namespace_id, 
      $language_namespace_id, 
      $country_namespace_id
    ),
    $custom_namespace_ids,
    array(
      $user_namespace_id,
    )
  );

  return $namespace_ids;
}


// Path 

/**
 * Get all path elements of the current request, e.g.:
 *   /foo/bar/baz
 *   will return
 *   array('foo', 'bar', 'baz')
 *
 * @return array $path_elements
 *   The path elements.
 */
function serchilo_get_path_elements() {
  $path = $_SERVER['REDIRECT_URL'];
  // example: '/n/en.usa'
  $path_elements = explode('/', $path);
  return $path_elements;
}

/**
 * Get the namespace names from the path.
 *
 * @param int $path_elements_offset
 *   The offset of the relevant path elements, e.g
 *     0 when /n/foo.bar
 *     1 when /baz/n/foo.bar.
 *
 * @return array $namespace_names
 *   The namespace names.
 */
function serchilo_get_namespace_names_from_path($path_elements_offset = 0) {
  $path_elements = serchilo_get_path_elements();
  if ('n' == $path_elements[$path_elements_offset + 1]) {
    $namespace_names = explode('.', $path_elements[$path_elements_offset + 2]);
    array_unshift($namespace_names, SERCHILO_PLANET_NAMESPACE);
    return $namespace_names;
  }
}

/**
 * Get the user name from the path.
 *
 * @param int $path_elements_offset
 *   The offset of the relevant path elements, e.g
 *     0 when /n/foo.bar
 *     1 when /baz/n/foo.bar.
 *
 * @return string $user_name
 *   The user name.
 */
function serchilo_get_user_name_from_path($path_elements_offset = 0) {
  $path_elements = serchilo_get_path_elements();
  if ('u' == $path_elements[$path_elements_offset + 1]) {
    return $path_elements[$path_elements_offset + 2];
  }
}


// Call, redirect, output

/**
 * Log a shortcut call.
 *   Adds a row with
 *   - nid
 *   - called (timestamp)
 *   to the serchilo_shortcut_log table.
 *
 * @param array $shortcut
 *   The shortcut being called.
 *
 * @return void
 */
function serchilo_log_shortcut_call($shortcut, $page_type, $default_keyword_used = FALSE) {

  $page_type_mapping = array(
    SERCHILO_CONSOLE        => SERCHILO_LOG_PAGE_CONSOLE, 
    SERCHILO_URL_PATH_AFFIX => SERCHILO_LOG_PAGE_URL, 
    SERCHILO_API_PATH_AFFIX => SERCHILO_LOG_PAGE_API, 
  );

  global $mysqli;

  $sql ="
    
INSERT INTO 
  serchilo_shortcut_log
  (
    shortcut_id, 
    namespace_id, 
    default_keyword_used,
    page_type,
    called,
    execution_time
  )
  VALUES (
    :shortcut_id, 
    :namespace_id, 
    :default_keyword_used,
    :page_type,
    :called,
    :execution_time
  );

  ";

  $sql = serchilo_replace_sql_arguments(
    $mysqli, 
    $sql,
    array(
      'shortcut_id'          => $shortcut['nid'],
      'namespace_id'         => $shortcut['namespace_id'],
      'default_keyword_used' => $default_keyword_used,
      'page_type'            => $page_type_mapping[$page_type],
      'called'               => time(),
      'execution_time'       => serchilo_get_execution_time(),
    )
  );

  $mysqli->query($sql);
}

/**
 * Output a HTML file with 
 * <meta http-equiv="refresh"> 
 * to redirect to the given URL.
 *
 * @param string $url
 *   The URL to redirect to.
 *
 * @return void
 */
function serchilo_redirect_via_meta($url) {
  require_once('tpl/serchilo-redirect-meta.tpl.php'); 
}

/**
 * Output a HTML file with form
 * and the POST parameters as hidden fields
 * to redirect to the given URL.
 *
 * @param string $url
 *   The URL to redirect to.
 * @param array $post_parameters
 *   The POST parameters as a key/value array.
 *   
 * @return void
 */
function serchilo_redirect_via_form($url, $post_parameters) {
  require_once('tpl/serchilo-redirect-form.tpl.php'); 
}


/**
 * Output data as JSON and exit.
 *
 * @return mixed $output
 *   The data to output.
 */
function serchilo_output_json($output) {
  header('Content-Type: application/json');
  echo json_encode($output, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT);
  exit();
}


// URL

/**
 * Replace the placeholders in the given string with variables.
 *
 * @param string $str
 *   The string with placeholders.
 * @param array $variables
 *   The variables to replace in the $str.
 *   
 * @return string $str
 *   The replaced URL. 
 */
function serchilo_replace_variables($str, $variables ) {

  $str_variables = serchilo_get_variables_from_string($str);

  foreach ($str_variables as $name=>$attributes) {
    switch($name) {
      case 'now':
        $output = serchilo_array_value($attributes, 'output', 'Y-m-d');
        $now = new DateTime();
        $value = $now->format($output);
        break; 
      default:
        $value = $variables[$name];
        break; 
    }
    $str = str_replace(
      $attributes['_match'],
      $value,
      $str 
    );
  }
  return $str;
}

/**
 * Replace the placeholders in the given string with arguments.
 *
 * @param string $str
 *   The string with placeholders.
 * @param array $arguments
 *   The arguments to replace in the $str.
 *   
 * @return string $str
 *   The replaced string. 
 */
function serchilo_replace_arguments($str, $arguments, $env) {

  $str_arguments = serchilo_get_arguments_from_string($str);

  foreach ($str_arguments as $name=>$attributes) {

    $argument = array_shift($arguments);

    $type = serchilo_array_value($attributes, 'type');
    switch($type) {
      case 'date':
        require_once(dirname(__FILE__) . '/serchilo.type.date.inc');
        $date = serchilo_parse_date($argument);
        if (!empty($date)) {
          $output   = serchilo_array_value($attributes, 'output', 'Y-m-d');
          $argument = $date->format($output);
        }
        break;
      case 'time':
        require_once(dirname(__FILE__) . '/serchilo.type.time.inc');
        $time = serchilo_parse_time($argument);
        if (!empty($time)) {
          $time->setTimeZone(new DateTimeZone($env['timezone']));
          $output   = serchilo_array_value($attributes, 'output', 'H:i');
          $argument = $time->format($output);
        }
        break;
      case 'city':
        require_once(dirname(__FILE__) . '/serchilo.type.city.inc');
        $city = serchilo_parse_city($argument, $env);
        if (!empty($city)) {
          $argument = $city;
        }
        break;
    }

    // Default encoding: utf-8
    $encoding = serchilo_array_value($attributes, 'encoding', 'utf-8');
    switch($encoding) {
      case 'none':
        $argument = utf8_decode($argument);
        break;
      default:
        # if encoding is valid
        if (in_array(strtoupper($encoding), mb_list_encodings())) {
          $argument = mb_convert_encoding($argument, $encoding, 'utf-8');
        }
        $argument = rawurlencode($argument);
        break;
    }

    $str = str_replace(
      $attributes['_match'],
      $argument,
      $str 
    );
  }

  return $str;
}

/**
 * Get the variables for replacing within the shortcut URL. 
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 *
 * @return array $variables
 *   The $variables to replace within the shortcut URL.
 */
function serchilo_get_url_variables($env) {

  $variables = array();

  $variables['language']       = $env['language_namespace_name'];
  $variables['country:alpha3'] = $env['country_namespace_name'];
  $variables['user:name']      = (!empty($env['user_name'])) ? $env['user_name'] : '';

  switch (strlen($env['extra_namespace_name'])) {
    case 2:
      $variables['language']       = $env['extra_namespace_name'];
      break;
      case 3:
      $variables['country:alpha3'] = $env['extra_namespace_name'];
      break;
  }
  return $variables;
}


// Database

/**
 * Replace argument placeholders in a SQL query string.
 *
 * @param object $mysqli
 *   The Mysqli object, holding the DB connection.
 * @param string $sql_template
 *   The SQL query string containing placeholders.
 * @param array $arguments
 *   The arguments to replace.
 * @param string $left_delimiter
 *   (optional) The left delimiter of the arguments.
 * @param string $right_delimiter
 *   (optional) The right delimiter of the arguments.
 *
 * @return string $sql_replaced
 *   The replaced SQL query string.
 */
function serchilo_replace_sql_arguments($mysqli, $sql_template, $arguments, $left_delimiter = ':', $right_delimiter = '') {
  $sql_replaced = $sql_template;
  foreach ($arguments as $key=>$value) {
    $value_escaped = $mysqli->real_escape_string($value);
    $sql_replaced = str_replace($left_delimiter . $key . $right_delimiter, "'" . $value_escaped . "'", $sql_replaced);
  }
  return $sql_replaced;
}

/**
 * Do a simple SQL select query.
 *
 * @param string $table
 *   The table name to query.
 * @param string $where_column_name
 *   The column for the WHERE condition.
 * @param string $where_value
 *   The value for the WHERE condition.
 * @param string $value_column_name
 *   The column name of the value to return.
 *
 * @return array $values
 *   The array of return values.
 */
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

/**
 * Get the default keyword
 * - of the GET parameters (priority) or
 * - of an user.
 *
 * @param string $user_name
 *   (optional ) The name of the user to get the default keyword from.
 *
 * @return string $default_keyword
 *   The default_keyword. Can be NULL if none found.
 */
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


// Execution time

/**
 * Get the execution time until now.
 *
 * @return float $execution_time
 *   The execution time in seconds,
 *   after decimal point in microseconds.
 */
function serchilo_get_execution_time() {

  global $execution_time_start;

  $execution_time_end = microtime(TRUE);
  $execution_time = $execution_time_end - $execution_time_start;

  return $execution_time;
}
