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
  $with_namespace = (bool) (drupal_array_get_nested_value($_GET, array('with_namespace')) ?: FALSE);

  $query_link = theme(
    'serchilo_shortcut_example_link', 
    array(
      'shortcut' => $shortcut, 
      'arguments' => $arguments,
      'with_namespace' => $with_namespace,
    )
  );
  drupal_set_message(
    t(
      ':title changed its keyword to :keyword. Continue with !query_link.',
      array(
        ':title' => $shortcut->title,
        ':keyword' =>  $shortcut->field_keyword[LANGUAGE_NONE][0]['value'],
        '!query_link' => render($query_link),
      )
    ), 
    'warning'
  );

  drupal_goto('node/' . $shortcut->nid );
}


// Approve

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


// Discussion

/**
 * Return the Shortcut discussion page.
 *
 * @param $node
 *   Node of type shortcut.
 * @return array
 *   Render array containing the page.
 */
function serchilo_page_shortcut_discussion($shortcut) {

  $efq = new EntityFieldQuery;

  $efq = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'discussion')
    ->fieldCondition('field_shortcuts_affected', 'target_id',  $shortcut->nid)
    ;

  $result = $efq->execute();

  if (!empty($result)) {

    $nids = array_keys($result['node']);

    $header = array('Title', 'Replies');
    $rows = array();

    foreach ($nids as $nid) {
      $discussion = node_load($nid);
      $rows[] = array(
        l(
          $discussion->title,
          'node/' . $discussion->nid
        ),
        $discussion->comment_count
      );
    }

    // Depending on the context there may be a better choice than this
    $output['discussions'] = array(
      '#theme' => 'table', 
      '#header' => $header, 
      '#rows' => $rows,
      '#caption' => t(
        'Forum discussions about %shortcut_title', 
        array('%shortcut_title' => $shortcut->title)
      ),
    );
  }

  $output['add_discussion'] = array(
    '#theme' => 'link', 
    '#text' => t('Add new discussion'),
    '#path' =>  'node/add/discussion',
    '#attributes' =>  array(),
    '#options' => array(
      'attributes' => array(),
      'html' => FALSE,
      'query' => array(
        'shortcut_affected' => $shortcut->nid, 
      )
    ),
  );

  return $output;
}


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
      serchilo_delete_shortcut_row($node);
      $node->field_active[LANGUAGE_NONE][0]['value'] = (int) FALSE;
      $node->log = 'Deactivated.';
      drupal_set_message(t('Shortcut %title has been deactivated.', array('%title' => $node->title)));
    }
    else {
      serchilo_insert_shortcut_row($node);
      $node->field_active[LANGUAGE_NONE][0]['value'] = (int) TRUE;
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
