<?PHP

// (De)activate

/**
 * Constructs Shortcut deactivate and activate form.
 *
 * @see serchilo_form_shortcut_deactivate_submit()
 */
function serchilo_form_shortcut_deactivate($form, &$form_state, $node) {
  
  if (drupal_array_get_nested_value($node->field_active, array(LANGUAGE_NONE, 0, 'value'))) {
    $action = 'deactivate';
  }
  else {
    // Check if another shortcut with the same
    // keyword, argument_count and namespace exists.
    module_load_include('inc', 'serchilo', 'serchilo.node');
    if (serchilo_collides_with_existing_shortcut($node)) {
      // (Yes, one '=' is correct.)
      if ($existing_shortcut = serchilo_collides_with_existing_shortcut($node)) {
        $form[]['#markup'] = t(
          'Currently cannot activate shortcut. There is already an active shortcut !title using the same keyword, argument count and namespace.',
          array(
            '!title' => '<em>' . l($existing_shortcut->title, 'node/' . $existing_shortcut->nid) . '</em>',
          )
        );
      }
      return $form;
    }
    $action = 'activate';
  }

  $form['#node'] = $node;
  $form['nid'] = array('#type' => 'value', '#value' => $node->nid);

  return confirm_form(
    $form,
    t('Are you sure you want to ' . $action .' %title?', array('%title' => $node->title)),
    'node/' . $node->nid,
    '',
    t('Confirm'),
    t('Cancel')
  );
}

/**
 * Executes Shortcut deactivate and activate form.
 *
 * @see serchilo_form_shortcut_deactivate()
 */
function serchilo_form_shortcut_deactivate_submit($form, &$form_state) {

  if ($form_state['values']['confirm']) {

    module_load_include('inc', 'serchilo', 'serchilo.node');

    $node = node_load($form_state['values']['nid']);

    if (drupal_array_get_nested_value($node->field_active, array(LANGUAGE_NONE, 0, 'value'))) {
      $node->field_active[LANGUAGE_NONE][0]['value'] = (int) FALSE;
      $is_sensible_edit = serchilo_is_sensible_edit($node);
      $node->field_approved[LANGUAGE_NONE][0]['value'] = (int) !$is_sensible_edit;
      $node->log = 'Deactivated.';
      drupal_set_message(t('Shortcut %title has been deactivated.', array('%title' => $node->title)));
    }
    else {
      $node->field_active[LANGUAGE_NONE][0]['value'] = (int) TRUE;
      $is_sensible_edit = serchilo_is_sensible_edit($node);
      $node->field_approved[LANGUAGE_NONE][0]['value'] = (int) !$is_sensible_edit;
      $node->log = 'Activated.';
      drupal_set_message(t('Shortcut %title has been activated.', array('%title' => $node->title)));
    }

    // Set new revision to track later
    // when a shortcut revision was deactivated or activated.
    $node->revision = TRUE;

    node_save($node);
  }

  $form_state['redirect'] = 'node/' . $node->nid . '/revisions';
}
