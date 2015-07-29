<?PHP

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

  drupal_goto(
    'node/' . $shortcut->nid,
    array(
      'query' => array(
        'arguments' => drupal_array_get_nested_value($_GET, array('arguments')),
      ), 
    )
  );
}

