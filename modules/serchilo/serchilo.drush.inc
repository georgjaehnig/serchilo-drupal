<?PHP

/**
 * Implements hook_drush_command().
 */
function serchilo_drush_command() {

  $items = array();

  $items['import-serchilo-data'] = array(
    'callback' => 'drush_serchilo_import',
    'aliases' => array('isd'), 
    'arguments' => array(
      'file' => 'Full path to the Serchilo JSON file with shortcuts. ',
    ),
  );

  $items['export-serchilo-data'] = array(
    'callback' => 'drush_serchilo_export',
    'aliases' => array('esd'), 
    'arguments' => array(
      'file' => 'Full path to the destination file. ',
    ),
  );

  $items['calculate-shortcut-weights'] = array(
    'aliases' => array('csw'), 
  );

  return $items;
}

/**
 * Import shortcuts from file.
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
 * Export shortcuts to file.
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
