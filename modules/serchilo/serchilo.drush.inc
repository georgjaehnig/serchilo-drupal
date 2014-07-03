<?PHP

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


function drush_serchilo_import_shortcuts($file = NULL) {
  serchilo_import_shortcuts($file);
}
