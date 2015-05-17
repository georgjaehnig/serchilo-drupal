<?PHP

// Page callbacks

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
      SERCHILO_USER_PATH_AFFIX . '/' . $GLOBALS['user']->name,
      array(
        'query' => drupal_get_query_parameters() 
      )
    ); 
  } 
  else {
    serchilo_validate_and_set_namespaces();
    $namespace_names = drupal_static('serchilo_namespace_names');
    $namespace_path =  join(
      SERCHILO_NAMESPACE_PATH_SEPARATOR,
      # omit star-namespace if at first pos
      $namespace_names[0] == SERCHILO_PLANET_NAMESPACE ? array_slice($namespace_names, 1) : $namespace_names
    );
    # goto n/[namespace_names]
    drupal_goto( 
      SERCHILO_NAMESPACES_PATH_AFFIX . '/' . $namespace_path,
      array(
        'query' => drupal_get_query_parameters() 
      )
    ); 
  }
}

/**
 * Dispatch a request with namespaces.
 *
 * @param string $page_type
 *   Can be
 *   - 'console': a console call
 * @param string $namespace_path_original
 *   The current namespace path, i.e.
 *   a string with namespace names separated by a dot.
 *   
 * @return array 
 *   Render array to display the content.
 */
function serchilo_page_dispatch_namespaces($page_type, $namespace_path_original) {

  $namespace_path = serchilo_validate_namespace_path($namespace_path_original);
  # redirect if path changed
  if ($namespace_path != $namespace_path_original) {
    $path_elements = array(
      SERCHILO_NAMESPACES_PATH_AFFIX,
      $namespace_path, 
    );
    if (SERCHILO_CONSOLE != $page_type) {
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
  case SERCHILO_CONSOLE: 
    $output = metatag_metatags_view(SERCHILO_METATAG_INSTANCE_CONSOLE_NAMESPACES);
    metatag_page_set_metatags(SERCHILO_METATAG_INSTANCE_CONSOLE_NAMESPACES, $output);
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

/**
 * Dispatch a request with a user name.
 *
 * @param string $page_type
 *   Can be
 *   - 'console': a console call
 * @param string $path_affix
 *   The path affix denoting the user name.
 *   
 * @return array 
 *   Render array to display the content.
 */
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
  case SERCHILO_CONSOLE: 
    $output = metatag_metatags_view(SERCHILO_METATAG_INSTANCE_CONSOLE_USER);
    metatag_page_set_metatags(SERCHILO_METATAG_INSTANCE_CONSOLE_USER, $output);
    break;
  }
  return serchilo_page_dispatch($page_type);
}

/**
 * Dispatch a request.
 *
 * @param string $page_type
 *   Can be
 *   - 'console': a console call
 *   
 * @return array 
 *   Render array to display the content.
 */
function serchilo_page_dispatch($page_type) {
  switch ($page_type) {
  case SERCHILO_CONSOLE:
    return serchilo_page_console();
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

  $default_keyword_get =& drupal_static('serchilo_default_keyword_get');

  serchilo_add_opensearch_link($default_keyword_get);

  $autocomplete = true; 
  $content = array();

  $query = serchilo_array_value($_GET, 'query');
  $status = serchilo_array_value($_GET, 'status');

  if ($status == 'not_found') {
    serchilo_set_suggestions_message($query);
  }

  $autocomplete_url = base_path() . SERCHILO_AUTOCOMPLETE_PATH_AFFIX . '/' . join('/', arg());

  $settings = array(
    'autocomplete' => $autocomplete,
    'autocomplete_url' => $autocomplete_url,
  );

  drupal_add_js(array('serchilo' => $settings), 'setting');

  $module_path = drupal_get_path('module', 'serchilo');
  drupal_add_js($module_path . '/js/console.js');
  drupal_add_library('system', 'ui.autocomplete');
  

  $get_parameter_names = array('default_keyword', 'timezone');
  $get_parameters = array_intersect_key(
    drupal_get_query_parameters(), 
    array_flip($get_parameter_names)
  );

  $content['console'] = array(
    '#type' => 'markup',
    '#markup' => theme(
      'serchilo_console', 
      array(
        'query' => (string) $query,
        'get_parameters' => $get_parameters,
      )
    ),
  );

  $content['console_examples']       = serchilo_get_console_examples();
  $content['console_more_shortcuts'] = serchilo_get_more_shortcuts();

  return $content;
}

/**
 * Set the Drupal message with shortcut suggestions.
 *
 * @param string $query
 *   The called query.
 *
 * @return void
 */
function serchilo_set_suggestions_message($query) {

  $suggested_shortcut_ids = serchilo_array_value($_GET, 'nids');
  $arguments = serchilo_array_value($_GET, 'arguments');
  $country_namespace =& drupal_static('serchilo_country_namespace');

  $message = t(
    'None of the available !shortcuts_link matched your query.',
    array(
      '!shortcuts_link' => l(t('shortcuts'), 'shortcuts')
    )
  );

  if (!empty($suggested_shortcut_ids)) {
    $message .= ' ';
    $message .= t('Did you mean:');
    $with_namespace = TRUE;
  }
  else  {
    $message .= ' ';
    $message .= t('Common shortcuts for search engines:');

    $suggested_shortcut_ids[] = (
      serchilo_get_shortcut('g', 1, $country_namespace->name)
      ?:
      serchilo_get_shortcut('g', 1, SERCHILO_PLANET_NAMESPACE)
    );
    $suggested_shortcut_ids[] = serchilo_get_shortcut('b', 1, SERCHILO_PLANET_NAMESPACE);
    $suggested_shortcut_ids[] = serchilo_get_shortcut('y', 1, SERCHILO_PLANET_NAMESPACE);
    $arguments = array($query);
    $with_namespace = FALSE;
  }

  foreach($suggested_shortcut_ids as $suggested_shortcut_id) {

    $shortcut = node_load($suggested_shortcut_id);
    $suggested_shortcut_link = theme(
      'serchilo_shortcut_example_link',
      array(
        'shortcut' => $shortcut,
        'arguments' => $arguments,
        'with_namespace' => $with_namespace,
      )
    );
    // Collect by keys containing the query
    // to deduplicate.
    $suggested_shortcut_links[$suggested_shortcut_link['#title']] = 
      '<dt>' .  
      render($suggested_shortcut_link) .
      '</dt>' .  
      '<dd>' .  
      l($shortcut->title, 'node/' . $shortcut->nid) .
      '</dd>' .  
      '';
  }

  $definition_list = 
    '<dl class="dl-horizontal">' .
    join('', $suggested_shortcut_links) .
    '</dl>' .
    '';

  $message .=  $definition_list;

  drupal_set_message($message, 'error');
}

/**
 * Set the Drupal message with shortcut suggestions.
 *
 * @param string $query
 *   The called query.
 *
 * @return void
 */
function serchilo_get_more_shortcuts() {

  $language_namespace = drupal_static('serchilo_language_namespace');
  $country_namespace  = drupal_static('serchilo_country_namespace');

  $more_shortcuts = array(
    '#type' => 'markup',
    '#prefix' => '<div id="console-more">',
    '#suffix' => '</div>',
    '#markup' => 
'
<div class="dropdown">
<a href="shortcuts" title="" data-target="#" class="dropdown-toggle btn btn-default" data-toggle="dropdown">More shortcuts <span class="caret"></span></a>
<ul class="dropdown-menu">
<li class="leaf">' . 
      l(
        'related to ' . $language_namespace->description, 
        'namespaces/' . $language_namespace->name
      ) .
'</li>
<li class="leaf">' . 
      l(
        'related to ' . $country_namespace->description, 
        'namespaces/' . $country_namespace->name
      ) .
'</li>
<li class="leaf">' . 
      l(
        'tagged with "programming"',
        'shortcuts',
        array(
          'query' => array(
            'tags' => 'programming' 
          ) 
        )
      ) .
'</li>
<li class="leaf">' . 
      l(
        'all',
        'shortcuts'
      ) .
'</li>
</ul>
</div>

<div class="dropdown">
<a href="shortcuts" title="" data-target="#" class="dropdown-toggle btn btn-default" data-toggle="dropdown">Watch videos <span class="caret"></span></a>
<ul class="dropdown-menu">
<li class="leaf"><a href="https://www.youtube.com/watch?v=lNx4CFM-P2M">Short explainer</a></li>
<li class="leaf"><a href="https://www.youtube.com/watch?v=A-lfQyhVVLs">Basic usage</a></li>
<li class="leaf"><a href="https://www.youtube.com/watch?v=KQSKf08kIN8">Namespaces</a></li>
<li class="leaf"><a href="https://www.youtube.com/watch?v=DlMCDM4diyI">User accounts</a></li>
<li class="leaf"><a href="https://www.youtube.com/watch?v=kPhIxK1j-4E">Firefox plugin</a></li>
<li class="leaf"><a href="https://www.youtube.com/watch?v=0YXYavYNZYM">How to add to Chrome</a></li>
<li class="leaf"><a href="https://www.youtube.com/watch?v=zB8kVXPOsiI">How to add to Safari</a></li>
</ul>
</div>

'
  );

  return $more_shortcuts;
}

/**
 * Retrieves the console examples for the current namespaces.
 *
 * @return $console_examples
 *   A Drupal render array.
 */
function serchilo_get_console_examples() {
  
  $namespace_ids =& drupal_static('serchilo_namespace_ids');

  $efq = new EntityFieldQuery;

  $efq = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->fieldCondition('field_namespace', 'tid',    $namespace_ids )
    // Just to make sure there is at least 1 example.
    ->fieldCondition('field_example',   'value',  0, '!=' )
    ->fieldCondition('field_approved',  'value',  1 )
    ->fieldOrderBy('field_weight', 'value', 'DESC')
    ->range(0, 7);

  $result = $efq->execute();

  $shortcut_ids = (!empty($result) ? array_keys($result['node']) : array());

  $context = array(
    'namespace_ids' => $namespace_ids, 
  );

  drupal_alter('serchilo_console_examples', $shortcut_ids, $context);

  if (empty($shortcut_ids)) {
    return array(); 
  }
  $examples = array();
  foreach ($shortcut_ids as $shortcut_id) {
    $shortcut = node_load($shortcut_id);
    // Only use shortcuts with an example.
    $examples[] = field_view_field('node', $shortcut, 'field_example', 'serchilo_console_examples');
  }
  $examples = array_reverse($examples);

  $console_examples = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => array('console-examples'),
    ),
  ); 

  $console_examples['title'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'h3', 
    '#value' => t('Search with shortcuts:'), 
  );
  $console_examples['examples'] = $examples;

  return $console_examples;
}


// Validation

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

  // Get language and country namespace types.
  $namespace_type_language_id = current(taxonomy_get_term_by_name('language', 'namespace_types'))->tid;
  $namespace_type_country_id = current(taxonomy_get_term_by_name('country', 'namespace_types'))->tid;

  // No namespace duplicates.
  // And if duplicates exists: Keep those 'from right', e.g.
  // *,de,deu,* => de,deu,*
  $path_elements = array_reverse(array_unique(array_reverse($path_elements)));

  $namespaces = serchilo_namespace_names_to_namespaces($path_elements);

  foreach ($namespaces as $namespace) {
    
    // Check if this is a language namespace.
    if ($namespace->field_namespace_type[LANGUAGE_NONE][0]['tid'] == $namespace_type_language_id) {
      $language_namespace = $namespace;
    }

    // Check if this is a country namespace.
    if ($namespace->field_namespace_type[LANGUAGE_NONE][0]['tid'] == $namespace_type_country_id) {
      $country_namespace = $namespace;
    }

    // Check if this is the planet namespace.
    if ($namespace->name == SERCHILO_PLANET_NAMESPACE) {
      $star_namespace = $namespace;
    }
  }

  // Set default language.
  if (!isset($language_namespace)) {
    $language_namespace = serchilo_get_default_language_namespace();
    // Add to namespace array.
    array_unshift($namespaces, $language_namespace);
  }

  // Set default country after language, if not already in path.
  if (!isset($country_namespace)) {
    $country_namespace = serchilo_get_default_country_namespace();

    // Inject $country_namespace into $namespaces right after language namespace.
    $language_namespace_pos = array_search($language_namespace, $namespaces);
    array_splice($namespaces, $language_namespace_pos + 1, 0, array($country_namespace));
  }

  // Set star namespace as first if not already in path.
  if (!isset($star_namespace)) {
    $star_namespace = current(taxonomy_get_term_by_name(SERCHILO_PLANET_NAMESPACE, 'namespaces')); 
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
 *    String with namespaces seperated by SERCHILO_NAMESPACE_PATH_SEPARATOR.
 * @return $namespace_path_validated
 *    String with validated namespaces seperated by SERCHILO_NAMESPACE_PATH_SEPARATOR.
 */
function serchilo_validate_namespace_path($namespace_path_original) {

  if ($namespace_path_original != '') {
    $namespace_names = explode(
      SERCHILO_NAMESPACE_PATH_SEPARATOR,
      $namespace_path_original
    );
  } else {
    $namespace_names = array();
  }

  $namespaces = serchilo_validate_and_set_namespaces($namespace_names);

  $namespace_names = array_map(function ($namespace) { return $namespace->name; }, $namespaces );

  $namespace_path_validated = join(
    SERCHILO_NAMESPACE_PATH_SEPARATOR,
    # omit star-namespace if at first pos
    $namespace_names[0] == SERCHILO_PLANET_NAMESPACE ? array_slice($namespace_names, 1) : $namespace_names
  );

  return $namespace_path_validated;
}


// Helpers

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

  $star_namespace     = array_shift(taxonomy_get_term_by_name(SERCHILO_PLANET_NAMESPACE, 'namespaces') ?: array());
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
      SERCHILO_OPENSEARCH_DEFINITION_PATH_AFFIX .  '/' .  arg(0) .  '/' .  arg(1),
      array(
        'absolute' => TRUE,
        'query' => drupal_get_query_parameters(),
      )
    ),
    'title' => serchilo_opensearch_title(arg(1), $default_keyword_get)
  ));
}
