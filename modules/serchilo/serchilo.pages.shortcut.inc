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
        '!query_link' => serchilo_shortcut_example_link(array(
          'shortcut' => $shortcut, 
          'arguments' => $arguments
        )),
      )
    ), 
    'warning'
  );

  drupal_goto('node/' . $shortcut->nid );
}

/**
 * Return the render array for an shortcut example query link.
 *
 * @param array $variables
 *   Theme variables, with keys:
 *     - shortcut
 *       The shortcut node object.
 *     - arguments
 *       The arguments array for the query.
 *     - with_namespace
 *       True when the link text shall contain the namespace name.
 *
 * @return void
 */
function serchilo_shortcut_example_link($variables) {

  $shortcut = $variables['shortcut'];
  $arguments = $variables['arguments'];

  if (is_array($arguments)) {
    $arguments_str = join(', ', $arguments); 
  }

  
  $namespace_name = taxonomy_term_load($shortcut->field_namespace[LANGUAGE_NONE][0]['tid'])->name;
  
  $query = 
    $shortcut->field_keyword[LANGUAGE_NONE][0]['value'] . 
    ' ' . 
    $arguments_str;

  // useful when arguments are empty
  $query = trim($query);

  $text = $query;

  if (!empty($variables['with_namespace'])) {
    $text = $namespace_name .  '.' .  $text;
  }

  // The query gets always the namespace name prefixed.
  $query = $namespace_name .  '.' .  $query;

  $link = l(
    $text,
    '',
    array(
      'attributes' => array(
        'rel' => 'nofollow',
        'class' => array('query'),
      ),
      'query' => array(
        'query' => $query,
      ), 
    )
  );

  return $link;
}
