<?PHP

/**
 * Validate a form element that should contain no HTML tags.
 */
function serchilo_form_validate_no_tags($element, &$form_state) {
  $value = drupal_array_get_nested_value($form_state['values'], $element['#parents']);
  if ($value != preg_replace('/<.*>/', '', $value)) {
    form_error(
      $element, 
      t(
        '@title must not contain HTML tags.', 
        array(
          '@title' => $element['#title'], 
        )
      )
    );
  }
}

/**
 * Validate a form element that should contain no dots.
 */
function serchilo_form_validate_no_dots($element, &$form_state) {
  $value = drupal_array_get_nested_value( $form_state['values'], $element['#parents']);
  if (strpos($value, '.') !== FALSE) {
    form_error(
      $element,
      t(
        'No dots are allowed in the keyword, since !dots_are used_for_forcing_a_namespace.',
        array(
          '!dots_are used_for_forcing_a_namespace' => l(t('dots are used for forcing a namespace'), 'help/namespaces', array('fragment'=>'force')) 
        )
      )
    );
  }
}

/**
 * Validate a form element that should contain no whitespace.
 */
function serchilo_form_validate_no_whitespace($element, &$form_state) {

  $value = drupal_array_get_nested_value($form_state['values'], $element['#parents']);
  if ($value != preg_replace('/\s*/', '', $value)) {
    form_error(
      $element, 
      t(
        '@title must not contain spaces.', 
        array(
          '@title' => $element['#title'], 
        )
      )
    );
  }
}

/**
 * Validate a form element that must be lowercase.
 */
function serchilo_form_validate_lowercase($element, &$form_state) {

  $value = drupal_array_get_nested_value($form_state['values'], $element['#parents']);
  if ($value != strtolower($value)) {
    form_error(
      $element, 
      t(
        '@title must be lowercase.', 
        array(
          '@title' => $element['#title'], 
        )
      )
    );
  }
}

/**
 * Validate field_namespace.
 */
function serchilo_form_validate_field_namespace($element, &$form_state) {

  if (!user_permission('edit any shortcut content')) {
    return TRUE;
  }

  global $user;
  $namespace_name = drupal_array_get_nested_value($form_state['values'], array_slice($element['#parents'], 0, 2));
  $namespace = current(taxonomy_get_term_by_name($namespace_name, 'namespaces'));
  $wnamespace = entity_metadata_wrapper('taxonomy_term', $namespace);

  // If this is a user namespace.
  if ($wnamespace->field_namespace_type->name->value() == 'user') {
    if (user_is_logged_in()) {
      if ($namespace_name != $user->name) {
        form_error( $element, t('Namespace must be a site namespace or your user namespace.'));
      }
    } else {
      form_error( $element, t('Namespace must be a site namespace.'));
    }
  }
}

/**
 * Validate field_tags.
 */
function serchilo_form_validate_field_tags(&$element, &$form_state) {

  // Lowercase all tags and deduplicate.

  $tag_names_str = $element['#value'];
  $tag_names = preg_split('/\s*,\s*/', $tag_names_str); 
  foreach ($tag_names as &$tag_name) {
    $tag_name = strtolower($tag_name); 
  }
  $tag_names = array_unique($tag_names);
  $tag_names_str = join(', ', $tag_names);
  $element['#value'] = $tag_names_str;
}

