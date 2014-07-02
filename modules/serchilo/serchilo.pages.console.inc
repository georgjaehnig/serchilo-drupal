<?PHP

/**
 * Page callback for homepage.
 * Redirect to correct console page:
 *   when logged in:
 *     to /u/[username]
 *   when not logged in:
 *     to /n/[language namespace].[country namespace]
 *
 * @return void
 */
function serchilo_page_home() {

  if (user_is_logged_in()) {
    # goto u/[username]
    drupal_goto(
      USER_PATH_AFFIX . '/' . $GLOBALS['user']->name,
      array(
        'query' => drupal_get_query_parameters() 
      )
    ); 
  } 
  else {
    _serchilo_validate_and_set_namespaces();
    $namespace_names = drupal_static('namespace_names');
    $namespace_path =  join(
      NAMESPACE_PATH_SEPARATOR,
      # omit star-namespace if at first pos
      $namespace_names[0] == STAR_NAMESPACE ? array_slice($namespace_names, 1) : $namespace_names
    );
    # goto n/[namespace_names]
    drupal_goto( 
      NAMESPACES_PATH_AFFIX . '/' . $namespace_path,
      array(
        'query' => drupal_get_query_parameters() 
      )
    ); 
  }
}

function serchilo_page_dispatch_namespaces($page_type, $namespace_path_original) {
  $namespace_path = _serchilo_validate_namespace_path($namespace_path_original);
  # redirect if path changed
  if ($namespace_path != $namespace_path_original) {
    $path_elements = array(
      NAMESPACES_PATH_AFFIX,
      $namespace_path, 
    );
    if (CONSOLE != $page_type) {
      array_unshift($path_elements, $page_type); 
    }
    drupal_goto( 
      join(
        '/',
        $path_elements 
      ),
      array(
        'query' => drupal_get_query_parameters(), 
      ), 
      301
    );
  }
  switch ($page_type) {
  case CONSOLE: 
    $output = metatag_metatags_view(METATAG_INSTANCE_CONSOLE_NAMESPACES);
    metatag_page_set_metatags(METATAG_INSTANCE_CONSOLE_NAMESPACES, $output);
    break;
  }

  # allow setting of default keyword
  $default_keyword =& drupal_static('default_keyword' );

  $default_keyword_get =& drupal_static('default_keyword_get' );

  # override default keyword from GET params
  if ($default_keyword_get = _serchilo_array_value($_GET, 'default_keyword')) {
    $default_keyword = $default_keyword_get;
  }
  return serchilo_page_dispatch($page_type);
}

function serchilo_page_dispatch_user($page_type, $path_affix) {
  $account = user_load_by_name($path_affix);
  if (!$account) {
    drupal_set_message(
      t(
        'No user named %user_name found.',
        array(
          '%user_name' => $path_affix,
        )
      ),
      'error'
    );

    return MENU_NOT_FOUND;
  }

  _serchilo_set_default_keyword($account);
  _serchilo_set_user_namespaces($account);

  switch ($page_type) {
  case CONSOLE: 
    $output = metatag_metatags_view(METATAG_INSTANCE_CONSOLE_USER);
    metatag_page_set_metatags(METATAG_INSTANCE_CONSOLE_USER, $output);
    break;
  }
  return serchilo_page_dispatch($page_type);
}

function serchilo_page_dispatch($page_type) {
  switch ($page_type) {
  case CONSOLE:
    $default_keyword_get =& drupal_static('default_keyword_get' );
    drupal_add_html_head_link(array(
      'rel' => 'search',
      'type' => 'application/opensearchdescription+xml',
      'href' => url( 
        OPENSEARCH_DEFINITION_PATH_AFFIX .  '/' .  arg(0) .  '/' .  arg(1),
        array(
          'absolute' => TRUE,
          'query' => drupal_get_query_parameters(),
        )
      ),
      'title' => _serchilo_opensearch_title(arg(1), $default_keyword_get)
    ));
    return _serchilo_page_console();
  // TODO:
  // remove this as namespace validation (and redirection)
  // shall only happen at console requests. 
  // Other requests shall be solely handled by the PHP standalone processor.
  case AUTOCOMPLETE_PATH_AFFIX:
    return _serchilo_autocomplete();
  case OPENSEARCH_DEFINITION_PATH_AFFIX:
    return _serchilo_opensearch_definition(arg(1), arg(2));
  case OPENSEARCH_SUGGESTIONS_PATH_AFFIX:
    return _serchilo_opensearch_suggestions();
  case URL_PATH_AFFIX:
    return _serchilo_url();
  case API_PATH_AFFIX:
    return _serchilo_api();
  }
}

/**
 * Creates the console page, according to settings found via drupal_static().
 *
 * @return $content
 *   A Drupal render array.
 */
function _serchilo_page_console() {

  $autocomplete = true; 
  $content = array();

  # call with a query?

  $search = _serchilo_array_value($_GET, 'search');
  $query = _serchilo_array_value($_GET, 'query');
  $status = _serchilo_array_value($_GET, 'status');
  // TODO
  // redirect from ?query if not found
  // to search=.. and status=not_found

  if (isset($search)) {
    $search = trim($search);
    $namespace_ids = drupal_static('namespace_ids');

    $commands = _serchilo_search_commands($search, array(), $search);
    $content['commands_search_result'] = _serchilo_display_commands($commands, array());

    # copy to show in input field
    $query = $search;
  }

  $typewrite_examples = array();
  $autocomplete_url = base_path() . AUTOCOMPLETE_PATH_AFFIX . '/' . join('/', arg());

  $settings = array(
    'autocomplete' => $autocomplete,
    'autocomplete_url' => $autocomplete_url,
    'typewrite_examples' => $typewrite_examples,
  );

  drupal_add_js(array('serchilo' => $settings), 'setting');

  $module_path = drupal_get_path('module', 'serchilo');
  drupal_add_js($module_path . '/js/console.js');
  drupal_add_library('system', 'ui.autocomplete');
  

  $default_keyword = drupal_static('default_keyword' );
  $namespace_names = drupal_static('namespace_names');

  /*
  $commands_of_current_namespaces_url = url(
    'commands',
    array(
      'query' => array(
        'namespace' => join(',', $namespace_names),
      ) 
    )
  );
   */
  $commands_of_current_namespaces_url = url('shortcuts');

  $content['console'] = array(
    '#type' => 'markup',
    '#markup' => theme(
      'serchilo-console', 
      array(
        'query' => (string) $query,
        'default_keyword' => (string) $default_keyword,
        'commands_of_current_namespaces_url' => $commands_of_current_namespaces_url,
      )
    ),
  );

  # add id
  foreach ($content as $key=>$value) {
    $content[$key]['#attributes']['id'] = $key;
  }

  return $content;
}

/**
 * Validates if given strings are namespaces
 * and if necessary sets additional namespaces 
 * for language and country.
 * Saves them with drupal_static().
 *
 * @param path_elements
 *   Array of strings to validate as namespace names.
 * @return namespaces
 *   Array of Taxonomy term objects.
 */
function _serchilo_validate_and_set_namespaces($path_elements = array()) {

  # get language and country namespace types
  $namespace_type_language_id = array_shift(taxonomy_get_term_by_name('language', 'namespace_types')?:0)->tid;
  $namespace_type_country_id = array_shift(taxonomy_get_term_by_name('country', 'namespace_types')?:0)->tid;

  # no namespace duplicates
  # keep namespaces 'from right', e.g.
  # *,de,deu,* => de,deu,*
  $path_elements = array_reverse(array_unique(array_reverse($path_elements)));

  $namespaces = _serchilo_namespace_names_to_namespaces($path_elements);

  foreach ($namespaces as $namespace) {
    # check if we have the language here
    if ($namespace->field_namespace_type[LANGUAGE_NONE][0]['tid'] == $namespace_type_language_id) {
      $language_namespace = $namespace;
    }

    # check if we have the country here
    if ($namespace->field_namespace_type[LANGUAGE_NONE][0]['tid'] == $namespace_type_country_id) {
      $country_namespace = $namespace;
    }

    # check if we have the star namespace here
    if ($namespace->name == STAR_NAMESPACE) {
      $star_namespace = $namespace;
    }
  }

  # set default language
  if (!isset($language_namespace)) {
    $language_namespace = _serchilo_get_default_language_namespace();
    # add to namespace array
    array_unshift($namespaces, $language_namespace);
  }

  # set default country after language if not already in path
  if (!isset($country_namespace)) {
    $country_namespace = _serchilo_get_default_country_namespace();

    # inject $country_namespace into $namespaces right after language namespace
    $language_namespace_pos = array_search($language_namespace, $namespaces);
    array_splice($namespaces, $language_namespace_pos + 1, 0, array($country_namespace));
  }

  # set star namespace as first if not already in path
  if (!isset($star_namespace)) {
    $star_namespace = array_shift(taxonomy_get_term_by_name(STAR_NAMESPACE, 'namespaces')?:0); 
    array_unshift($namespaces, $star_namespace);
  }

  $namespace_names = array_map(function ($namespace) { return $namespace->name; }, $namespaces );
  $namespace_ids = array_map(function ($namespace) { return $namespace->tid; }, $namespaces );

  drupal_static('namespaces', $namespaces );
  drupal_static('namespace_ids', $namespace_ids );
  drupal_static('namespace_names', $namespace_names );

  drupal_static('language_namespace', $language_namespace );
  drupal_static('country_namespace', $country_namespace );

  drupal_static('namespaces_validated', TRUE );

  return $namespaces;

}

/**
 * Loads namespaces.
 *
 * @param $namespace_names
 *   Array of strings.
 * @return $namespaces
 *   Array of namespace objects.
 */
function _serchilo_namespace_names_to_namespaces($namespace_names) {
  $namespaces = array();
  foreach ($namespace_names as $namespace_name) {
    $namespace = array_shift(taxonomy_get_term_by_name($namespace_name, 'namespaces')?: array());
    if (!is_object($namespace)) { 
      continue;
    }
    array_push($namespaces, $namespace); 
  }
  return $namespaces; 
}

/**
 * Loads default language namespace.
 *
 * @return $language_namespace 
 *   A Taxonomy term object.
 */
function _serchilo_get_default_language_namespace() {
  global $language;

  $default_language = $language->language;
  $language_namespace = array_shift(taxonomy_get_term_by_name($default_language, 'namespaces')?:0); 

  return $language_namespace;
}

/**
 * Loads default country namespace.
 *
 * @return $language_namespace 
 *   A Taxonomy term object.
 */
function _serchilo_get_default_country_namespace() {

  $ip_address = ip_address();

  # set debug IP
  if ('127.0.0.1' == $ip_address) {
    $ip_address = '78.55.17.101';
  }
  $default_country_namespace_name = @geoip_country_code3_by_name($ip_address);
  $default_country_namespace_name = strtolower($default_country_namespace_name);

  if (
    (!$default_country_namespace_name) ||
    (strlen($default_country_namespace_name) != 3 )
  ) {
    $default_country_namespace_name  = DEFAULT_COUNTRY;
  }

  /*
  # fallback if geoip did not find anything
  if (
    (!$default_country_namespace_name) ||
    (strlen($default_country_namespace_name) != 3 )
  ) {

    if (!isset($_SESSION['smart_ip'])) {
      $location = smart_ip_get_location($ip_address);
      smart_ip_set_session_data($location);
    }

    if ( $_SESSION['smart_ip']['location']['country_code'] ) {
      module_load_include('inc', 'serchilo', 'serchilo');
      $default_country_namespace_name = strtolower(
        serchilo_2letter_to_3letter_country_code( $_SESSION['smart_ip']['location']['country_code'])
      );
    }
    watchdog('serchilo', 'Retrieved coutry by IP via smart_ip: ' . $default_country_namespace_name);
  }
   */
  $default_country_namespace = current(taxonomy_get_term_by_name($default_country_namespace_name, 'namespaces')); 

  return $default_country_namespace;
}

/**
 * Validates a given namespace path.
 *
 * @param $namespace_path_original
 *    String with namespaces seperated by NAMESPACE_PATH_SEPARATOR.
 * @return $namespace_path_validated
 *    String with validated namespaces seperated by NAMESPACE_PATH_SEPARATOR.
 */
function _serchilo_validate_namespace_path($namespace_path_original) {

  $namespace_names = explode(
    NAMESPACE_PATH_SEPARATOR,
    $namespace_path_original
  );

  $namespaces = _serchilo_validate_and_set_namespaces($namespace_names);

  $namespace_names = array_map(function ($namespace) { return $namespace->name; }, $namespaces );

  $namespace_path_validated = join(
    NAMESPACE_PATH_SEPARATOR,
    # omit star-namespace if at first pos
    $namespace_names[0] == STAR_NAMESPACE ? array_slice($namespace_names, 1) : $namespace_names
  );

  return $namespace_path_validated;
}

/**
 * Return the title for the Opensearch head link.
 *
 * @param $namespaces_path
 *    String of namespaces seperated by NAMESPACE_PATH_SEPARATOR.
 * @param $default_keyword
 *    (optional) String of the default keyword.
 * @return $title
 *    String of the Opensearch head link.
 */
function _serchilo_opensearch_title($namespaces_path, $default_keyword = NULL) {
  if( $default_keyword ) {
    $title =  'Serchilo: ' . $namespaces_path . ' | ' . $default_keyword;
  }
  else {
    $title =  'Serchilo: ' . $namespaces_path;
  }
  return $title;
}


/**
 * Set the default keyword of a user via drupal_static().
 *
 * @param $account
 *    A user object.
 * @return void
 *    String of the Opensearch head link.
 */
function _serchilo_set_default_keyword($account) {

  $default_keyword =& drupal_static('default_keyword');

  # get default keyword
  $default_keyword = 
    (!empty($account->field_default_keyword)) 
    ? $account->field_default_keyword[LANGUAGE_NONE][0]['value']
    : NULL; 
}

/**
 * Return and set the namespaces of a user via drupal_static().
 *
 * @param $account
 *    A user object.
 * @return $namespaces
 *   Array of Taxonomy term objects.
 */
function _serchilo_set_user_namespaces($account) {

  $star_namespace     = array_shift(taxonomy_get_term_by_name(STAR_NAMESPACE, 'namespaces') ?: array());
  $language_namespace = array_shift(_serchilo_field_get_items_taxonomy_term_load_multiple('user', $account, 'field_language_namespace') ?: array());
  $country_namespace  = array_shift(_serchilo_field_get_items_taxonomy_term_load_multiple('user', $account, 'field_country_namespace') ?: array());
  $custom_namespaces  = _serchilo_field_get_items_taxonomy_term_load_multiple('user', $account, 'field_custom_namespaces');
  $user_namespace     = array_shift(taxonomy_get_term_by_name($account->name, 'namespaces') ?: array());

  $namespaces = array_merge(
    array(
      $star_namespace,
      $language_namespace,
      $country_namespace 
    ),
    $custom_namespaces,
    array(
      $user_namespace,
    )
  );

  $namespace_names = array_map(function ($namespace) { return $namespace->name; }, $namespaces );
  $namespace_ids   = array_map(function ($namespace) { return $namespace->tid; }, $namespaces );

  drupal_static('namespaces',         $namespaces         );
  drupal_static('namespace_names',    $namespace_names    );
  drupal_static('namespace_ids',      $namespace_ids      );

  drupal_static('language_namespace', $language_namespace );
  drupal_static('country_namespace',  $country_namespace  );
  drupal_static('user_namespace',     $user_namespace     );

  drupal_static('user_id',            $account->uid       );

  drupal_static('namespaces_validated', TRUE );

  return $namespaces;
}

/**
 * Wrapper for field_get_items().
 * Loads the full Taxonomy terms stored in a Entity Field.
 *
 * @return
 *   Array of Taxonomy terms.
 */
function _serchilo_field_get_items_taxonomy_term_load_multiple($entity_type, $entity, $field_name, $langcode = NULL) {
  if ( $items = field_get_items($entity_type, $entity, $field_name, $langcode = NULL) ) {
    return taxonomy_term_load_multiple( 
      array_map(
        function ($term) {
          return $term['tid']; 
        },
          $items
        )
      );
  } else {
    return array(); 
  }
}

