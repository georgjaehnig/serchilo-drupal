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

  $fields = array();

  $fields['nid']            = $node->nid;
  $fields['title']          = $node->title;
  $fields['keyword']        = $node->field_keyword        [LANGUAGE_NONE][0]['value'];
  $fields['argument_names'] = $node->field_argument_names [LANGUAGE_NONE][0]['value'];
  $fields['argument_count'] = $node->field_argument_count [LANGUAGE_NONE][0]['value'];
  $fields['url']            = $node->field_url            [LANGUAGE_NONE][0]['value'];
  $fields['input_encoding'] = $node->field_input_encoding [LANGUAGE_NONE][0]['value'];
  $fields['weight']         = $node->field_weight         [LANGUAGE_NONE][0]['value'];
  $fields['invisible']      = $node->field_invisible      [LANGUAGE_NONE][0]['value'];
  $fields['set_referrer']   = $node->field_set_referrer   [LANGUAGE_NONE][0]['value'];
  $fields['namespace_id']   = $node->field_namespace      [LANGUAGE_NONE][0]['tid'];

  // Assign taxonomy term names only if they exists, i.e.: already have been loaded.
  if (!empty($node->field_namespace[LANGUAGE_NONE][0]['name'])) {
    $fields['namespace_name'] = $node->field_namespace[LANGUAGE_NONE][0]['name'];
  }

  if (!empty($node->field_tags[LANGUAGE_NONE][0]['name'])) {
    $tags           = array_map(function ($tag) { return $tag['name']; }, $node->field_tags[LANGUAGE_NONE] ?: array() );
    $fields['tags'] = join(',', $tags);
  }

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
  print_r($fields);
  return;
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

