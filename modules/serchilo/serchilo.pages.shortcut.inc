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

