<?PHP

/**
 * Implements hook_drush_command().
 */
function serchilo_drush_command() {

  $items = array();

  $items['import-shortcuts'] = array(
    'aliases' => array('isc'), 
    'arguments' => array(
      'file' => 'Full path to the Serchilo JSON file with shortcuts. ',
    ),
  );

  $items['export-shortcuts'] = array(
    'aliases' => array('esc'), 
    'arguments' => array(
      'file' => 'Full path to the destination file. ',
    ),
  );

  return $items;
}

/**
 * Import shortcuts from file.
 *
 * @param string $file
 *   The path to the file to import,
 *   based from DRUPAL_ROOT.
 */
function drush_serchilo_import_shortcuts($file = NULL) {

  $msg = serchilo_import_shortcuts($file, TRUE);
  if (is_string($msg)) {
    echo $msg . "\n"; 
  }
}

function drush_serchilo_export_shortcuts($file) {

  serchilo_export_to_json_gz_file($file);
}
