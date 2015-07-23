<?PHP

/**
 * Constructs shortcut approval confirmation form.
 *
 * @see serchilo_shortcut_approve_confirm_submit()
 */
function serchilo_shortcut_approve_confirm($form, &$form_state, $node) {

  if (drupal_array_get_nested_value($node->field_approved, array(LANGUAGE_NONE, 0, 'value')) == 1) {
    $form[]['#markup'] = t('Current shortcut revision is already approved.');
    return $form;
  }

  $form['#node'] = $node;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['nid'] = array('#type' => 'value', '#value' => $node->nid);
  return confirm_form(
    $form,
    t('Are you sure you want to approve %title?', array('%title' => $node->title)),
    'node/' . $node->nid,
    '',
    t('Approve'),
    t('Cancel')
  );
}

/**
 * Executes shortcut approval confirmation form.
 *
 * @see serchilo_shortcut_approve_confirm()
 */
function serchilo_shortcut_approve_confirm_submit($form, &$form_state) {

  if ($form_state['values']['confirm']) {
    $node = node_load($form_state['values']['nid']);
    $node->field_approved[LANGUAGE_NONE][0]['value'] = (int) TRUE;
    // Set new revision to track later
    // when a shortcut revision started to be callable.
    $node->revision = TRUE;
    $node->log = 'Approved.';
    node_save($node);
    drupal_set_message(t('@type %title has been approved.', array('@type' => node_type_get_name($node), '%title' => $node->title)));
  }

  $form_state['redirect'] = 'node/' . $node->nid . '/revisions';
}

