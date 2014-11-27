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

  return $items;
}

function drush_serchilo_approve_shortcuts() {
  
  $efq = new EntityFieldQuery;

  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->propertyCondition('status', NODE_PUBLISHED)
    #->range(0,100)
    ->execute();

  $nids = array_keys(array_shift($result));

  foreach ($nids as $nid) {
    $node = node_load($nid);
    $node->field_approved[LANGUAGE_NONE][0]['value'] = 1;
    field_attach_update('node', $node);
    echo $nid;
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
