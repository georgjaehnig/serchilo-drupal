<?PHP

/**
 * Implements hook_migrate_api().
 */
function serchilo_migrate_migrate_api() {

  $api = array(
    'api' => 2,
    'groups' => array(
      'serchilo' => array(
        'title' => t('Serchilo'),
      ),
    ),
  );

  return $api;
}
