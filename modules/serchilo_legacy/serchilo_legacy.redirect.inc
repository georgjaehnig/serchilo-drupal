<?PHP

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
function serchilo_legacy_redirect_commands($command_id, $path_element) {

  if (
    (empty($command_id)) ||
    (!is_numeric($command_id)) ||
    FALSE
  ) {
    drupal_not_found();
    return;
  }

  $efq = new EntityFieldQuery;

  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->fieldCondition('field_command_id', 'value',  $command_id)
    ->execute();

  if (!empty($result)) {
    $shortcut_id = array_keys($result['node'])[0];
    drupal_goto(
      'shortcuts/' . $shortcut_id . '/' . $path_element,
      array(
        'query' => drupal_get_query_parameters(),
      )
    );
  }
  else {
    drupal_not_found();
    return;
  }
}
