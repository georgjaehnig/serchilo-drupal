<?PHP

/**
 * Implements hook_drush_command().
 */
function serchilo_drush_command() {

  $items = array();

  $items['serchilo-import-data'] = array(
    'description' => 'Import Serchilo data from file.',
    'callback' => 'drush_serchilo_import',
    'aliases' => array('sid'), 
    'arguments' => array(
      'file' => 'Full path to the Serchilo JSON file with shortcuts. ',
    ),
    'required-arguments' => TRUE,
  );

  $items['serchilo-export-data'] = array(
    'description' => 'Export Serchilo data to file.',
    'callback' => 'drush_serchilo_export',
    'aliases' => array('sed'), 
    'arguments' => array(
      'file' => 'Full path to the destination file. ',
    ),
    'required-arguments' => TRUE,
  );

  $items['serchilo-export-data-trovu'] = array(
    'description' => 'Export Serchilo data to file.',
    'callback' => 'drush_serchilo_export_trovu',
    'aliases' => array('sedt'), 
    'arguments' => array(
      'dir' => 'Full path to the destination directory. ',
    ),
    'required-arguments' => TRUE,
  );

  $items['serchilo-calculate-shortcut-calls'] = array(
    'description' => 'Calculate shortcut calls.',
    'callback' => 'drush_serchilo_calculate_shortcut_calls',
    'aliases' => array('scsc'), 
  );

  $items['serchilo-calculate-shortcut-weights'] = array(
    'callback' => 'drush_serchilo_calculate_shortcut_weights',
    'description' => 'Calculate shortcut weights.',
    'aliases' => array('scsw'), 
  );

  $items['serchilo-approve-shortcuts'] = array(
    'callback' => 'drush_serchilo_approve_shortcuts',
    'aliases' => array('sas'), 
  );

  $items['serchilo-set-shortcut-owners'] = array(
    'callback' => 'drush_serchilo_set_shortcut_owners',
    'aliases' => array('ssso'), 
  );

  $items['serchilo-set-shortcuts-active'] = array(
    'callback' => 'drush_serchilo_set_shortcuts_active',
    'aliases' => array('sssa'), 
  );

  $items['serchilo-reset-shortcut-stats'] = array(
    'callback' => 'drush_serchilo_reset_shortcut_stats',
    'aliases' => array('srss'), 
  );

  return $items;
}

/**
 * Set shortcut calls and weights to 0.
 *
 * @return void
 */
function drush_serchilo_reset_shortcut_stats() {
  
  $efq = new EntityFieldQuery;

  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->execute();

  $nids = array_keys(array_shift($result));

  foreach ($nids as $nid) {
    echo $nid . ' ';
    $node = node_load($nid);
    drupal_array_set_nested_value($node->field_calls_total,        array(LANGUAGE_NONE, 0, 'value'), 0);
    drupal_array_set_nested_value($node->field_calls_last_30_days, array(LANGUAGE_NONE, 0, 'value'), 0);
    drupal_array_set_nested_value($node->field_weight,             array(LANGUAGE_NONE, 0, 'value'), 0);
    field_attach_update('node', $node);
  }
}

/**
 * Set
 * - owners of user shortcuts to the users of the namespace.
 * - owners of user shortcuts to admin.
 *
 * @return void
 */
function drush_serchilo_set_shortcuts_active() {
  
  $efq = new EntityFieldQuery;

  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->execute();

  $nids = array_keys(array_shift($result));

  foreach ($nids as $nid) {
    echo $nid . ' ';
    $node = node_load($nid);
    drupal_array_set_nested_value($node->field_active, array(LANGUAGE_NONE, 0, 'value'), TRUE);
    field_attach_update('node', $node);
  }
}

/**
 * Set
 * - owners of user shortcuts to the users of the namespace.
 * - owners of user shortcuts to admin.
 *
 * @return void
 */
function drush_serchilo_set_shortcut_owners() {
  
  $efq = new EntityFieldQuery;

  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->execute();

  $nids = array_keys(array_shift($result));

  foreach ($nids as $nid) {
    $shortcut = node_load($nid);
    $wshortcut = entity_metadata_wrapper('node', $shortcut);
    echo '.';
    if ($wshortcut->field_namespace->field_namespace_type->name->value() == 'user') {
      $account = user_load_by_name($wshortcut->field_namespace->name->value());
      if (!$account) {
        echo "\n" . 'Problem loading user: ' .  $wshortcut->field_namespace->value() . "\n";
        echo "\t" . $shortcut->nid . ' ' .  $shortcut->title . "\n";
        continue;
      }
      $wshortcut->author->set($account->uid);
      $wshortcut->save();
    } 
    else {
      // Set to admin.
      //$wshortcut->author->set(1);
      //$wshortcut->save();
    }
  }
}

/**
 * Approve all shortcuts.
 *
 * @return void
 */
function drush_serchilo_approve_shortcuts() {
  
  $efq = new EntityFieldQuery;

  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->execute();

  $nids = array_keys(array_shift($result));

  foreach ($nids as $nid) {
    $node = node_load($nid);
    $node->field_approved[LANGUAGE_NONE][0]['value'] = 1;
    field_attach_update('node', $node);
    echo ".";
  }
}

/**
 * Import Serchilo data from file.
 *
 * @param string $file
 *   The path to the file to import,
 *   based from DRUPAL_ROOT.
 *
 * @return void
 */
function drush_serchilo_import($file = NULL) {

  module_load_include('inc', 'serchilo', 'serchilo.import');

  $msg = serchilo_import($file, TRUE);
  if (is_string($msg)) {
    echo $msg . "\n"; 
  }
}


/**
 * Export Serchilo data to file.
 *
 * @param string $file
 *   The path to the file to export to,
 *   based from DRUPAL_ROOT.
 *
 * @return void
 */
function drush_serchilo_export($file) {

  module_load_include('inc', 'serchilo', 'serchilo.export');
  serchilo_export_to_json_gz_file($file);
}

/**
 * Export Serchilo data to Trovu directory.
 *
 * @param string $dir
 *   The path to the dir to export to,
 *   based from DRUPAL_ROOT.
 *
 * @return void
 */
function drush_serchilo_export_trovu($dir) {

  module_load_include('inc', 'serchilo', 'serchilo.export');
  serchilo_export_to_json_dir($dir);
}

/**
 * Calculate shortcut weights.
 *
 * @return void
 */
function drush_serchilo_calculate_shortcut_weights() {
  
  module_load_include('inc', 'serchilo', 'serchilo.weights');
  serchilo_calculate_shortcut_weights();
}

/**
 * Calculate shortcut calls.
 *
 * @return void
 */
function drush_serchilo_calculate_shortcut_calls() {

  module_load_include('inc', 'serchilo', 'serchilo.weights');
  serchilo_calculate_shortcut_calls();
}
