<?PHP

/**
* @file
* Syncs shortcut nodes with serchilo_shortcut table.
*/

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

  // Check if shortcut already exists in sync table.
  $row_count = db_select('serchilo_shortcut') 
    ->fields('serchilo_shortcut')
    ->condition('nid', $node->nid )
    ->execute()
    ->rowCount() 
    ;

  // If it does not exist, insert it.
  if ($row_count == 0) {
    $nid = serchilo_insert_shortcut_row($node); 
    if (empty($nid)) {
      // Return 0 to raise an error.
      return 0; 
    } else {
      return 1; 
    }
  }
  // If it does exist, update it.
  else {
    $num_updated = serchilo_update_shortcut_row($node); 
    return $num_updated;
  }
}


// DB layer

/**
 * Insert a shortcut row.
 *
 * @param object $node
 *   Shortcut node to deal with.
 *
 * @return int $nid
 *   ID of the inserted row.
 */
function serchilo_insert_shortcut_row($node) {

  $fields = serchilo_shortcut_to_db_fields($node);
  $nid = db_insert('serchilo_shortcut') 
    ->fields($fields)
    ->execute();

  return $nid;
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
  return $num_deleted;
}


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

/**
 * Check the number of affected rows.
 * 
 * @param int $num_affected
 *   Number of affected rows.
 * @param object $node
 *   The node object that was dealt with.
 * @param string $function_name
 *   The name of the calling function.
 * 
 * @return void
 */
function serchilo_watchdog_check_number_of_affected_rows($num_affected, $node, $function_name) {

  if ($num_affected == 0) {
    watchdog(
      'serchilo', 
      'Wrong number of affected rows in %function: %num_affected rows when processing node %nid',
      array(
        '%function'     => $function_name, 
        '%num_affected' => $num_affected,
        '%nid'          => $node->nid,
      ),
      WATCHDOG_ERROR
    );
  }
}


/**
 * Set the shortcut's argument data, parsed from the url,
 * i.e.
 * - the argument_names
 * - the argument count
 *
 * @param object &$node
 *   The shortcut node as a reference
 *
 * @return void
 */
function serchilo_set_shortcut_arguments_data(&$node) {

  // derive and set url metadata
  $argument_names = serchilo_get_argument_names(
    drupal_array_get_nested_value($node->field_url,             array(LANGUAGE_NONE, 0, 'value')),
    drupal_array_get_nested_value($node->field_post_parameters, array(LANGUAGE_NONE, 0, 'value'))
  );
  drupal_array_set_nested_value($node->field_argument_names, array(LANGUAGE_NONE, 0, 'value'), join(', ', $argument_names));
  drupal_array_set_nested_value($node->field_argument_count, array(LANGUAGE_NONE, 0, 'value'), count($argument_names));
}

