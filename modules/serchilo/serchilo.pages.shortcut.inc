<?PHP

// Changed

/**
 * Redirect to the shortcut node page
 * with a message that they keyword of the shortcut changed.
 *
 * @param int $shorcut_id
 *  The shortcut id.
 *
 * @return void
 */
function serchilo_page_shortcut_changed($shortcut_id) {

  $shortcut = node_load($shortcut_id);
  $arguments = (drupal_array_get_nested_value($_GET, array('arguments')) ?: array());

  drupal_set_message(
    t(
      ':title changed its keyword to :keyword. Continue with !query_link.',
      array(
        ':title' => $shortcut->title,
        ':keyword' =>  'g',
        '!query_link' => theme(
          'serchilo_shortcut_example_link', 
          array(
            'shortcut' => $shortcut, 
            'arguments' => $arguments
          )
        ),
      )
    ), 
    'warning'
  );

  drupal_goto('node/' . $shortcut->nid );
}


// Approve

/**
 * Form constructor for the shortcut approval confirmation form.
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
 * Executes shortcut approval.
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


// Discussion

/**
 * Return the Shortcut discussion page.
 *
 * @param $node
 *   Node of type shortcut.
 * @return array
 *   Render array containing the page.
 */
function serchilo_page_shortcut_discussion($node) {

  return 'foo';
}
