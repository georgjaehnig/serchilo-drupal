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
