<?PHP

/**
* @file
* Syncs shortcut nodes with serchilo_shortcut table.
*/

// Wrapper

/**
 * Sync a shortcut with its row in serchilo_shortcut table.
 *  (New approach to later replace serchilo_insert_or_update_shortcut_row().)
 *
 * @param object $node
 *   Shortcut node to deal with.
 *
 * @return void
 */
function serchilo_sync_shortcut_row($node) {

  $wnode = entity_metadata_wrapper('node', $node);

  // Always delete first.
  serchilo_delete_shortcut_row($node);

  // Case 1: active, approved
  if (($wnode->field_active->value()) && ($wnode->field_approved->value())) {
    serchilo_insert_shortcut_row($node);
    return;
  }

  // Case 2: active, not approved
  if (($wnode->field_active->value()) && (!$wnode->field_approved->value())) {
    serchilo_insert_shortcut_row($node);
    // Get last approved shortcut.
    $node_approved = serchilo_shortcut_get_last_approved_revision($node);
    if ($node_approved) {
      serchilo_insert_shortcut_row($node_approved);
    }
    return;
  }

  // Case 3: not active, approved
  if ((!$wnode->field_active->value()) && ($wnode->field_approved->value())) {
    // Do nothing, since non-active shortcuts shall not exist (when approved).
    return;
  }

  // Case 4: not active, not approved
  if ((!$wnode->field_active->value()) && (!$wnode->field_approved->value())) {
    // Get last approved revision.
    $node_approved = serchilo_shortcut_get_last_approved_revision($node);
    // If none found: Get out.
    if (!$node_approved) {
      return;
    }
    $wnode_approved = entity_metadata_wrapper('node', $node_approved);
    // If last approved revision is also active: Save only this one.
    if ($wnode_approved->field_active->value()) {
      serchilo_insert_shortcut_row($node_approved);
    }
    return;
  }
}

function serchilo_shortcut_get_last_approved_revision($node) {

  $efq = new EntityFieldQuery;

  $efq = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->propertyCondition('nid', $node->nid )
    ->fieldCondition('field_approved',      'value',    TRUE )
    ->age(FIELD_LOAD_REVISION)
    ->entityOrderBy('revision_id', 'DESC')
    ->range(0,1)
    ;

  $result = $efq->execute();

  if (!empty($result)) {
    $node_approved = current(current($result));
    $node_approved = node_load($node_approved->nid, $node_approved->vid);
    return $node_approved;
  }

  return FALSE; 
}

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
 * Checks if given shortcut has the same keyword, argument count
 * and namespace as an existing shortcut.
 *
 * @param object $node
 *   Shortcut node to check.
 *
 * @return object or FALSE
 *   Node object of the colliding shortcut, if found.
 *   FALSE if found none.
 */
function serchilo_collides_with_existing_shortcut($node) {

  serchilo_set_shortcut_arguments_data($node);

  $efq = new EntityFieldQuery;

  $efq = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->fieldCondition('field_keyword',        'value',  drupal_array_get_nested_value($node->field_keyword,        array(LANGUAGE_NONE, 0, 'value')))
    ->fieldCondition('field_argument_count', 'value',  drupal_array_get_nested_value($node->field_argument_count, array(LANGUAGE_NONE, 0, 'value')))
    ->fieldCondition('field_namespace',      'tid',    drupal_array_get_nested_value($node->field_namespace,      array(LANGUAGE_NONE, 0, 'tid'  )))
    ->fieldCondition('field_active',         'value',  TRUE )
  ;

  // Exclude the current shortcut.
  if (!empty($node->nid)) {
    $efq->propertyCondition('nid', $node->nid, '!=');
  }

  $result = $efq->execute();

  // If found a colliding shortcut:
  if (!empty($result)) {
    $existing_shortcut_nid = array_keys($result['node'])[0];
    $existing_shortcut = node_load($existing_shortcut_nid);
    return $existing_shortcut;
  }
  else {
    return FALSE; 
  }
}

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
  $fields['vid']             = $node->vid;
  $fields['title']           = $node->title;
  $fields['keyword']         = drupal_array_get_nested_value($node->field_keyword,         array(LANGUAGE_NONE, 0, 'value'));
  $fields['argument_names']  = drupal_array_get_nested_value($node->field_argument_names,  array(LANGUAGE_NONE, 0, 'value'));
  $fields['argument_count']  = drupal_array_get_nested_value($node->field_argument_count,  array(LANGUAGE_NONE, 0, 'value'));
  $fields['url']             = drupal_array_get_nested_value($node->field_url,             array(LANGUAGE_NONE, 0, 'value'));
  $fields['post_parameters'] = drupal_array_get_nested_value($node->field_post_parameters, array(LANGUAGE_NONE, 0, 'value'));
  $fields['weight']          = drupal_array_get_nested_value($node->field_weight,          array(LANGUAGE_NONE, 0, 'value'));
  $fields['invisible']       = drupal_array_get_nested_value($node->field_invisible,       array(LANGUAGE_NONE, 0, 'value'));
  $fields['set_referrer']    = drupal_array_get_nested_value($node->field_set_referrer,    array(LANGUAGE_NONE, 0, 'value'));
  $fields['approved']        = drupal_array_get_nested_value($node->field_approved,        array(LANGUAGE_NONE, 0, 'value'));
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

/**
 * Get the Serchilo argument names from the placeholders in URL.
 *
 * @param string $url
 *   The URL containing placeholders.
 * @param string $post_parameters
 *   The POST parameter string containing placeholders.
 *
 * @return array $argument_names
 *   The extracted argument names.
 */
function serchilo_get_argument_names($url, $post_parameters) {

  $argument_names = array_merge(
    array_keys(serchilo_get_arguments_from_string($post_parameters)),
    array_keys(serchilo_get_arguments_from_string($url))
  );

  // treat arguments with same name as only one argument
  $argument_names = array_unique($argument_names);

  // make sure indexes have no gaps
  $argument_names = array_values($argument_names);

  return $argument_names;
}

/**
 * Check if shortcut edit is sensible edit.
 *
 * @param $node
 *   Node of type shortcut.
 * @return 
 *   TRUE if edit is sensible.
 */
function serchilo_is_sensible_edit($node) {

  global $user;

  // Should only be called for shortcuts anyway.
  // But better return TRUE in error case
  // because a wrong TRUE probably causes less harm
  // than a wrong FALSE in this context.
  if ($node->type != 'shortcut') {
    return TRUE;
  }

  // Allow users with approve permission to do anything.
  if (user_access('approve shortcut content')) {
    return FALSE;
  }

  // Default is TRUE.
  $is_sensible_edit = TRUE;

  // Work with wrapped node.
  $wnode = entity_metadata_wrapper('node', $node);

  // Non-new shortcuts:
  // TODO: Find 'proper' way to check if new.
  if (!empty($node->nid)) {

    // An unapproved shortcut stays unapproved.
    if (!$wnode->field_approved->value()) {
      return TRUE; 
    }

    // Do not used cached version.
    $original_node = node_load($node->nid, NULL, TRUE);
    $woriginal_node = entity_metadata_wrapper('node', $original_node);


    $change_in_keyword   = $wnode->field_keyword        ->value() != $woriginal_node->field_keyword        ->value();
    $change_in_url       = $wnode->field_url            ->value() != $woriginal_node->field_url            ->value();
    $change_in_namespace = $wnode->field_namespace->name->value() != $woriginal_node->field_namespace->name->value();
    $change_in_active    = $wnode->field_active         ->value() != $woriginal_node->field_active         ->value();
        
    $is_sensible_edit = 
      $change_in_keyword || 
      $change_in_url ||
      $change_in_namespace ||
      $change_in_active;

    // Allow editing within the first X minutes after creation.
    if (
      $is_sensible_edit && 
      ($woriginal_node->created->value() > time() - SERCHILO_EDIT_NON_SENSIBLE_AFTER_CREATED * 60) 
    ) {
      $is_sensible_edit = FALSE;
      drupal_set_message(
        t(
          'New site shortcuts can freely be edited @minutes minutes after creation. Later edits to keyword, URL or namespace need moderator approval.', 
          array(
            '@minutes' => SERCHILO_EDIT_NON_SENSIBLE_AFTER_CREATED,
          )
        ),
        'status'
      );
    }
  }

  // New shortcuts:
  else {

    // Allow adding a shortcut to SERCHILO_PLANET_NAMESPACE 
    // if the keyword is new in SERCHILO_PLANET_NAMESPACE.
    if (serchilo_keyword_is_new_in_planet_namespace($node)) {
      $is_sensible_edit = FALSE;
      return $is_sensible_edit;
    }

    // Allow adding a shortcut to any site namespace 
    // if the keyword is new to any namespace.
    if (serchilo_keyword_is_new($node)) {
      $is_sensible_edit = FALSE;
      return $is_sensible_edit;
    }

    // Every other new shortcut is sensible.
    $is_sensible_edit = TRUE;
  }

  if ($is_sensible_edit) {
    // If the user is logged in and the shortcut is saved to the current user's namespace,
    // it is not sensible, since users can do anything in their own namespaces.
    if (user_is_logged_in()) {
      // Check on the namespace which was set BEFORE the edit
      // (if available).
      if (isset($woriginal_node)) {
        $is_sensible_edit = ($user->name != $woriginal_node->field_namespace->name->value());
      }
      else {
        $is_sensible_edit = ($user->name != $wnode->field_namespace->name->value());
      }
    }
  }

  return $is_sensible_edit;
}

/**
 * Check if the keyword of the given shortcut
 * is new in SERCHILO_PLANET_NAMESPACE
 * (but may be used in another namespace).
 *
 * @param $node
 *   Node of type shortcut.
 * @return 
 *   TRUE if the keyword is not used in SERCHILO_PLANET_NAMESPACE.
 */
function serchilo_keyword_is_new_in_planet_namespace($node) {

  // Check first is we want to add to SERCHILO_PLANET_NAMESPACE at all.
  if (SERCHILO_PLANET_NAMESPACE != drupal_array_get_nested_value($node->field_namespace, array(LANGUAGE_NONE, 0, 'name'))) {
    return FALSE;
  }
  // Check if there is already a shortcut 
  $efq = new EntityFieldQuery;
  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->fieldCondition('field_keyword',        'value',  $node->field_keyword[LANGUAGE_NONE][0]['value'])
    ->fieldCondition('field_namespace',      'tid',    $node->field_namespace[LANGUAGE_NONE][0]['tid'])
    ->execute();

  if (count($result) == 0) {
    return TRUE;
  }
  
  return FALSE;
}

/**
 * Check if the keyword of the given shortcut
 * is new in site namespaces
 * (but may be used in user namespaces).
 *
 * @param $node
 *   Node of type shortcut.
 * @return 
 *   TRUE if the keyword is not used in site namespaces.
 */
function serchilo_keyword_is_new($node) {

  // Check first is we want to add to a site namespace (=not a user namespace) at all.
  $namespace_type_id = drupal_array_get_nested_value(
    $node->field_namespace, 
    array(LANGUAGE_NONE, 0, 'field_namespace_type', LANGUAGE_NONE, 0, 'tid')
  );
  $namespace_type = taxonomy_term_load($namespace_type_id);
  if ('user' == $namespace_type->name) {
    return FALSE;
  }

  // Check if there is already a shortcut 
  $efq = new EntityFieldQuery;
  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->fieldCondition('field_keyword', 'value',  $node->field_keyword[LANGUAGE_NONE][0]['value'])
    ->execute();

  if (count($result) == 0) {
    return TRUE;
  }

  return FALSE;
}

