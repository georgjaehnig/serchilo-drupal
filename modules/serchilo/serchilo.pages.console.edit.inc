<?PHP

/**
 * Builds a form for changing the current namespaces.
 *
 * @param array $form
 * @param array $form_state
 *   Standard form hook arguments.
 *
 * @param string $namespace_path_original
 *   The current namespace path, i.e.
 *   a string with namespace names separated by a dot.
 *
 * @return array $form
 *   The built form.
 */
function serchilo_form_console_namespaces($form, &$form_state, $namespace_path_original) {

  module_load_include('inc', 'serchilo', 'serchilo.pages.console');

  $namespace_path = serchilo_validate_namespace_path($namespace_path_original);

  // Redirect if path changed.
  if ($namespace_path != $namespace_path_original) {
      drupal_goto( SERCHILO_NAMESPACES_PATH_AFFIX . '/' . $namespace_path . '/edit', array(), 301);
  }

  $namespace_ids = drupal_static('serchilo_namespace_ids');
  // Drop "o" namespace, which is always first.
  array_shift($namespace_ids);

  // Wrap values in tid-key.
  foreach ($namespace_ids as &$namespace_id) {
    $namespace_id = array('tid' =>$namespace_id); 
  }

  $form = array();
  $form['#parents']  = array();

  $form['intro'] = array(
    '#type' => 'markup',
    '#markup' => 'By setting ' . l('namespaces', 'help/namespaces') . ', you decide which shortcuts you mainly want to use. ',
    '#prefix' => '<div id="intro">',
    '#suffix' => '</div>',
  );

  $form += serchilo_get_form_field('user', 'user', NULL, 'field_language_namespace', array(array_shift($namespace_ids)), $form, $form_state);
  $form += serchilo_get_form_field('user', 'user', NULL, 'field_country_namespace', array(array_shift($namespace_ids)), $form, $form_state);
  $form += serchilo_get_form_field('user', 'user', NULL, 'field_custom_namespaces', $namespace_ids, $form, $form_state);

  // Add submit button to the bottom.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
    '#weight' => 100,
  );

  return $form;
}

/**
 * Submits the form for changing the current namespaces.
 *
 * @param array $form
 * @param array $form_state
 *   Standard form hook arguments.
 *
 * @return void
 */
function serchilo_form_console_namespaces_submit($form, $form_state) {
  
  // Start with language and country namespaces.
  $namespace_names[] = taxonomy_term_load($form_state['values']['field_language_namespace'][LANGUAGE_NONE][0]['tid'])->name;
  $namespace_names[] = taxonomy_term_load($form_state['values']['field_country_namespace'][LANGUAGE_NONE][0]['tid'])->name;

  // Append custom namespaces.
  foreach($form_state['values']['field_custom_namespaces'][LANGUAGE_NONE] as $custom_namespace) {
    $namespace_names[] = $custom_namespace['name'];
  }

  // Redirect to new console page.
  drupal_goto( 
    SERCHILO_NAMESPACES_PATH_AFFIX . 
    '/' . 
    join('.', $namespace_names)
  );
}

/**
 * Get a form field from the Field module.
 */
function serchilo_get_form_field($entity_type, $bundle_name, $entity, $field_name, $items, &$form, &$form_state) {

  $field    = field_info_field($field_name);
  $instance = field_info_instance($entity_type, $field_name, $bundle_name);
  $element  = field_default_form($entity_type, $entity, $field, $instance, LANGUAGE_NONE, $items, $form, $form_state );

  return $element;
}
