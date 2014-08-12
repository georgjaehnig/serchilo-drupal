<?PHP

/**
 * Redirect 
 * - shortcut/[id] and
 * - shortcut/[id]/foobar
 * paths.
 *
 * @param int $shorcut_id
 *  The shortcut id.
 *
 * @return void
 */
function serchilo_redirect_shortcuts($shortcut_id) {

  if (
    (empty($shortcut_id)) ||
    (!is_numeric($shortcut_id)) ||
    (!$path = drupal_lookup_path('alias', 'node/' . $shortcut_id)) ||
    FALSE
  ) {
    drupal_not_found();
    return;
  }
  drupal_goto($path); 
}
/**
 * Redirect 
 * - command/[id] and
 * - command/[id]/foobar
 * paths to their shortcut node pages
 *
 * @param int $command_id
 *  The command id.
 *
 * @return void
 */
function serchilo_redirect_commands($command_id) {

  if (
    (empty($command_id)) ||
    (!is_numeric($command_id)) ||
    FALSE
  ) {
    drupal_not_found();
    return;
  }

  $query = new EntityFieldQuery;

  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->fieldCondition('field_command_id', 'value',  $command_id)
    ->execute();

  if (!empty($result)) {
    $shortcut_id = array_keys($result['node'])[0];
    serchilo_redirect_shortcuts($shortcut_id);
  }
  else {
    drupal_not_found();
    return;
  }
}
