<?PHP

/**
* @file
* Syncs shortcut nodes with serchilo_shortcut table.
*/

/**
 * Retrieve database fields from shortcut node.
 *
 * @param $node
 *   Node of type shortcut
 * @return
 *   array to pass to fields()
 */
function serchilo_shortcut_to_db_fields($node) {

  $tags = array_map(function ($tag) { return $tag['name']; }, $node->field_tags[LANGUAGE_NONE] ?: array() );
  
  $fields = array(
    'nid'            => $node->nid,
    'title'          => $node->title,
    'keyword'        => drupal_array_get_nested_value($node->field_keyword,        array(LANGUAGE_NONE, 0, 'value')),
    'argument_names' => drupal_array_get_nested_value($node->field_argument_names, array(LANGUAGE_NONE, 0, 'value')),
    'argument_count' => drupal_array_get_nested_value($node->field_argument_count, array(LANGUAGE_NONE, 0, 'value')),
    'url'            => drupal_array_get_nested_value($node->field_url,            array(LANGUAGE_NONE, 0, 'value')),
    'input_encoding' => drupal_array_get_nested_value($node->field_input_encoding, array(LANGUAGE_NONE, 0, 'value')),
    'weight'         => drupal_array_get_nested_value($node->field_weight,         array(LANGUAGE_NONE, 0, 'value')),
    'invisible'      => drupal_array_get_nested_value($node->field_invisible,      array(LANGUAGE_NONE, 0, 'value')),
    'set_referrer'   => drupal_array_get_nested_value($node->field_set_referrer,   array(LANGUAGE_NONE, 0, 'value')),
    'namespace_id'   => drupal_array_get_nested_value($node->field_namespace,      array(LANGUAGE_NONE, 0, 'tid'  )),
    'namespace_name' => drupal_array_get_nested_value($node->field_namespace,      array(LANGUAGE_NONE, 0, 'name' )),
    'tags'           => join(',', $tags),
  );

  return $fields;
}

function serchilo_insert_or_update_shortcut_row($node) {
  $row_count = db_select('serchilo_shortcut') 
    ->fields('serchilo_shortcut')
    ->condition('nid', $node->nid )
    ->execute()
    ->rowCount() 
    ;
  if ($row_count == 0) {
    serchilo_insert_shortcut_row($node); 
  }
  else {
    serchilo_update_shortcut_row($node); 
  }
}

function serchilo_insert_shortcut_row($node) {
  $fields = serchilo_shortcut_to_db_fields($node);
  $result = db_insert('serchilo_shortcut') 
    ->fields($fields)
    ->execute();
  //dpm($result);
  return;
}

function serchilo_update_shortcut_row($node) {
  $fields = serchilo_shortcut_to_db_fields($node);
  $num_updated = db_update('serchilo_shortcut') 
    ->fields($fields)
    ->condition('nid', $node->nid )
    ->execute();
  // TODO
  // raise error when $num_updated != 1
  //dpm($num_updated);
  return $num_updated;
}

function serchilo_delete_shortcut_row($node) {
  $num_deleted = db_delete('serchilo_shortcut') 
    ->condition('nid', $node->nid )
    ->execute();
  // TODO
  // raise error when $num_deleted != 1
  dpm($num_deleted);
}

