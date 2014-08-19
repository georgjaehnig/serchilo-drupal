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
    serchilo_validate_and_set_namespaces();
    $namespace_names = drupal_static('serchilo_namespace_names');
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
  $namespace_path = serchilo_validate_namespace_path($namespace_path_original);
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
  $default_keyword =& drupal_static('serchilo_default_keyword' );

  $default_keyword_get =& drupal_static('serchilo_default_keyword_get' );

  # override default keyword from GET params
  if ($default_keyword_get = serchilo_array_value($_GET, 'default_keyword')) {
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

  serchilo_set_default_keyword($account);
  serchilo_set_user_namespaces($account);

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
    return serchilo_page_console();
  // TODO:
  // remove this as namespace validation (and redirection)
  // shall only happen at console requests. 
  // Other requests shall be solely handled by the PHP standalone processor.
  case AUTOCOMPLETE_PATH_AFFIX:
    return serchilo_autocomplete();
  case OPENSEARCH_SUGGESTIONS_PATH_AFFIX:
    return serchilo_opensearch_suggestions();
  case URL_PATH_AFFIX:
    return serchilo_url();
  case API_PATH_AFFIX:
    return serchilo_api();
  }
}

/**
 * Creates the console page, according to settings found via drupal_static().
 *
 * @return $content
 *   A Drupal render array.
 */
function serchilo_page_console() {

  // Make it the front page.
  $is_front = &drupal_static('drupal_is_front_page');
  $is_front = TRUE;

  $default_keyword_get =& drupal_static('serchilo_default_keyword_get' );

  serchilo_add_opensearch_link($default_keyword_get);

  $autocomplete = true; 
  $content = array();

  # call with a query?

  $query = serchilo_array_value($_GET, 'query');
  $status = serchilo_array_value($_GET, 'status');

  if ($status == 'not_found') {
    drupal_set_message('No matching shortcut found.', 'error');
  }

  $autocomplete_url = base_path() . AUTOCOMPLETE_PATH_AFFIX . '/' . join('/', arg());

  $settings = array(
    'autocomplete' => $autocomplete,
    'autocomplete_url' => $autocomplete_url,
  );

  drupal_add_js(array('serchilo' => $settings), 'setting');

  $module_path = drupal_get_path('module', 'serchilo');
  drupal_add_js($module_path . '/js/console.js');
  drupal_add_library('system', 'ui.autocomplete');
  

  $default_keyword = drupal_static('serchilo_default_keyword' );
  $namespace_names = drupal_static('serchilo_namespace_names');

  /*
  $shortcuts_of_current_namespaces_url = url(
    'shortcuts',
    array(
      'query' => array(
        'namespace' => join(',', $namespace_names),
      ) 
    )
  );
   */
  $shortcuts_of_current_namespaces_url = url('shortcuts');

  $content['console'] = array(
    '#type' => 'markup',
    '#markup' => theme(
      'serchilo-console', 
      array(
        'query' => (string) $query,
        'default_keyword' => (string) $default_keyword,
        'shortcuts_of_current_namespaces_url' => $shortcuts_of_current_namespaces_url,
      )
    ),
  );

  /*
  # add id
  foreach ($content as $key=>$value) {
    $content[$key]['#attributes']['id'] = $key;
  }
   */

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
function serchilo_validate_and_set_namespaces($path_elements = array()) {

  # get language and country namespace types
  $namespace_type_language_id = current(taxonomy_get_term_by_name('language', 'namespace_types'))->tid;
  $namespace_type_country_id = current(taxonomy_get_term_by_name('country', 'namespace_types'))->tid;

  # no namespace duplicates
  # keep namespaces 'from right', e.g.
  # *,de,deu,* => de,deu,*
  $path_elements = array_reverse(array_unique(array_reverse($path_elements)));

  $namespaces = serchilo_namespace_names_to_namespaces($path_elements);

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
    $language_namespace = serchilo_get_default_language_namespace();
    # add to namespace array
    array_unshift($namespaces, $language_namespace);
  }

  # set default country after language if not already in path
  if (!isset($country_namespace)) {
    $country_namespace = serchilo_get_default_country_namespace();

    # inject $country_namespace into $namespaces right after language namespace
    $language_namespace_pos = array_search($language_namespace, $namespaces);
    array_splice($namespaces, $language_namespace_pos + 1, 0, array($country_namespace));
  }

  # set star namespace as first if not already in path
  if (!isset($star_namespace)) {
    $star_namespace = current(taxonomy_get_term_by_name(STAR_NAMESPACE, 'namespaces')); 
    array_unshift($namespaces, $star_namespace);
  }

  $namespace_names = array_map(function ($namespace) { return $namespace->name; }, $namespaces );
  $namespace_ids = array_map(function ($namespace) { return $namespace->tid; }, $namespaces );

  drupal_static('serchilo_namespaces', $namespaces );
  drupal_static('serchilo_namespace_ids', $namespace_ids );
  drupal_static('serchilo_namespace_names', $namespace_names );

  drupal_static('serchilo_language_namespace', $language_namespace );
  drupal_static('serchilo_country_namespace', $country_namespace );

  drupal_static('serchilo_namespaces_validated', TRUE );

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
function serchilo_namespace_names_to_namespaces($namespace_names) {
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
 * Validates a given namespace path.
 *
 * @param $namespace_path_original
 *    String with namespaces seperated by NAMESPACE_PATH_SEPARATOR.
 * @return $namespace_path_validated
 *    String with validated namespaces seperated by NAMESPACE_PATH_SEPARATOR.
 */
function serchilo_validate_namespace_path($namespace_path_original) {

  $namespace_names = explode(
    NAMESPACE_PATH_SEPARATOR,
    $namespace_path_original
  );

  $namespaces = serchilo_validate_and_set_namespaces($namespace_names);

  $namespace_names = array_map(function ($namespace) { return $namespace->name; }, $namespaces );

  $namespace_path_validated = join(
    NAMESPACE_PATH_SEPARATOR,
    # omit star-namespace if at first pos
    $namespace_names[0] == STAR_NAMESPACE ? array_slice($namespace_names, 1) : $namespace_names
  );

  return $namespace_path_validated;
}


/**
 * Set the default keyword of a user via drupal_static().
 *
 * @param $account
 *    A user object.
 * @return void
 *    String of the Opensearch head link.
 */
function serchilo_set_default_keyword($account) {

  $default_keyword =& drupal_static('serchilo_default_keyword');

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
function serchilo_set_user_namespaces($account) {

  $star_namespace     = array_shift(taxonomy_get_term_by_name(STAR_NAMESPACE, 'namespaces') ?: array());
  $language_namespace = array_shift(serchilo_field_get_items_taxonomy_term_load_multiple('user', $account, 'field_language_namespace') ?: array());
  $country_namespace  = array_shift(serchilo_field_get_items_taxonomy_term_load_multiple('user', $account, 'field_country_namespace') ?: array());
  $custom_namespaces  = serchilo_field_get_items_taxonomy_term_load_multiple('user', $account, 'field_custom_namespaces');
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

  drupal_static('serchilo_namespaces',         $namespaces         );
  drupal_static('serchilo_namespace_names',    $namespace_names    );
  drupal_static('serchilo_namespace_ids',      $namespace_ids      );

  drupal_static('serchilo_language_namespace', $language_namespace );
  drupal_static('serchilo_country_namespace',  $country_namespace  );
  drupal_static('serchilo_user_namespace',     $user_namespace     );

  drupal_static('serchilo_user_id',            $account->uid       );

  drupal_static('serchilo_namespaces_validated', TRUE );

  return $namespaces;
}

/**
 * Wrapper for field_get_items().
 * Loads the full Taxonomy terms stored in a Entity Field.
 *
 * @return
 *   Array of Taxonomy terms.
 */
function serchilo_field_get_items_taxonomy_term_load_multiple($entity_type, $entity, $field_name, $langcode = NULL) {
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

/**
 * Add the Opensearch link tag to the HTML head 
 * Loads the full Taxonomy terms stored in a Entity Field.
 *
 * @param string $default_keyword_get
 *    The default keyword that is set as GET variable.
 *
 * @return void
 */
function serchilo_add_opensearch_link($default_keyword_get) {

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
    'title' => serchilo_opensearch_title(arg(1), $default_keyword_get)
  ));
}
