<?PHP

/**
* @file
* Syncs shortcut nodes with serchilo_shortcut table.
*/

// Helper

/**
 * Convert a shortcut node to an array of database fields.
 *
 * @param object $node
 *   Shortcut node to convert.
 *
 * @return array $fields
 *   Array of database fields for the sync database table.
 */
function serchilo_shortcut_to_db_fields($node) {

  $fields = array();

  $fields['nid']             = $node->nid;
  $fields['title']           = $node->title;
  $fields['keyword']         = drupal_array_get_nested_value($node->field_keyword,         array(LANGUAGE_NONE, 0, 'value'));
  $fields['argument_names']  = drupal_array_get_nested_value($node->field_argument_names,  array(LANGUAGE_NONE, 0, 'value'));
  $fields['argument_count']  = drupal_array_get_nested_value($node->field_argument_count,  array(LANGUAGE_NONE, 0, 'value'));
  $fields['url']             = drupal_array_get_nested_value($node->field_url,             array(LANGUAGE_NONE, 0, 'value'));
  $fields['post_parameters'] = drupal_array_get_nested_value($node->field_post_parameters, array(LANGUAGE_NONE, 0, 'value'));
  $fields['input_encoding']  = drupal_array_get_nested_value($node->field_input_encoding,  array(LANGUAGE_NONE, 0, 'value'));
  $fields['weight']          = drupal_array_get_nested_value($node->field_weight,          array(LANGUAGE_NONE, 0, 'value'));
  $fields['invisible']       = drupal_array_get_nested_value($node->field_invisible,       array(LANGUAGE_NONE, 0, 'value'));
  $fields['set_referrer']    = drupal_array_get_nested_value($node->field_set_referrer,    array(LANGUAGE_NONE, 0, 'value'));
  $fields['namespace_id']    = drupal_array_get_nested_value($node->field_namespace,       array(LANGUAGE_NONE, 0, 'tid'));

  $wnode = entity_metadata_wrapper('node', $node);
  $fields['namespace_name'] = $wnode->field_namespace->value()->name;

  $tags = array();
  foreach ($wnode->field_tags->value() as $wtag) {
    $tags[] = $wtag->name;
  }
  $fields['tags'] = join(',', $tags);

  return $fields;
}


// Wrapper

/**
 * Insert or update a shortcut row.
 *
 * @param object $node
 *   Shortcut node to deal with.
 *
 * @return void
 */
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


// DB layer

/**
 * Insert a shortcut row.
 *
 * @param object $node
 *   Shortcut node to deal with.
 *
 * @return void
 */
function serchilo_insert_shortcut_row($node) {

  $fields = serchilo_shortcut_to_db_fields($node);
  $result = db_insert('serchilo_shortcut') 
    ->fields($fields)
    ->execute();
  //dpm($result);
  return;
}

/**
 * Update a shortcut row.
 *
 * @param object $node
 *   Shortcut node to deal with.
 *
 * @return int $num_updated
 *   Number of updated rows.
 */
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

/**
 * Delete a shortcut row.
 *
 * @param object $node
 *   Shortcut node to deal with.
 *
 * @return int $num_deleted
 *   Number of deleted rows.
 */
function serchilo_delete_shortcut_row($node) {
  $num_deleted = db_delete('serchilo_shortcut') 
    ->condition('nid', $node->nid )
    ->execute();
  // TODO
  // raise error when $num_deleted != 1
  return $num_deleted;
}

