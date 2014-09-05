<?PHP

/**
 * Redirect 
 * - shortcut/[id] and
 * - shortcut/[id]/foobar
 * paths.
 *
 * @param int $shorcut_id
 *  The shortcut id.
 *
 * @return void
 */
function serchilo_redirect_shortcuts($shortcut_id) {

  if (
    (empty($shortcut_id)) ||
    (!is_numeric($shortcut_id)) ||
    FALSE
  ) {
    drupal_not_found();
    return;
  }
  drupal_goto(
    'node/' . $shortcut_id,
    array(
      'query' => drupal_get_query_parameters(),
    )
  ); 
}


/**
 * Redirect 
 * - namespace/[name] and
 * - tag/[name]
 * paths to
 * - shorcuts/namespace=[name]
 * - shorcuts/tags=[name]
 *
 * @param object $term
 *  The term object.
 *
 * @return void
 */
function serchilo_redirect_taxonomy($term) {

  switch ($term->vocabulary_machine_name) {
  case 'namespaces':
    drupal_goto(
      'shortcuts',
      array(
        'query' => array(
          'namespace' => $term->name,
        )
      )
    ); 
    break; 
  case 'tags':
    drupal_goto(
      'shortcuts',
      array(
        'query' => array(
          'tags' => $term->name,
        )
      )
    ); 
    break; 
  }
}

