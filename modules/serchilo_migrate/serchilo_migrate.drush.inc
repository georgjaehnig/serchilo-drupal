<?PHP

/**
 * Implements hook_drush_command().
 */
function serchilo_migrate_drush_command() {

  $items = array();

  $items['serchilo-migrate-assign-users-to-shortcuts'] = array(
    'description' => 'Assign users to their shortcuts.',
    'callback' => 'drush_serchilo_migrate_assign_users_to_shortcuts',
    'aliases' => array('smauts'), 
  );

  return $items;
}

/**
 * Assign users to their shortcuts.
 *
 * @return void
 */
function drush_serchilo_migrate_assign_users_to_shortcuts() {

  $vocabularies = taxonomy_vocabulary_get_names();
  $user_namespace_type = current(taxonomy_get_term_by_name('user', 'namespace_types'));

  #alle userns ziehen
  #pro ns durchgehen
  #uid setzen

  // Get all user namespaces.
  $efq = new EntityFieldQuery;
  $result = $efq
    ->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', $vocabularies['namespaces']->vid )
    ->fieldCondition('field_namespace_type', 'tid', $user_namespace_type->tid )
    ->execute();

  $namespace_ids = array_keys(array_shift($result));
  $exported_namespaces = array();
  #print_r($namespace_ids);

  foreach ($namespace_ids as $namespace_id) {

    $namespace = taxonomy_term_load($namespace_id);
    $account = user_load_by_name($namespace->name);
    echo "Processing user: " . $namespace->name . "\n";

    $efq = new EntityFieldQuery;
    $result = $efq
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'shortcut')
      ->fieldCondition('field_namespace', 'tid', $namespace_id )
      ->execute();

    if (!empty($result)) {
      $nids = array_keys(array_shift($result));
      foreach ($nids as $nid) {
        $shortcut = node_load($nid);
        $shortcut->uid = $account->uid;
        node_save($shortcut);
      }
    }
  }
}
