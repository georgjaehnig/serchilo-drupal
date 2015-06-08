<?PHP

/**
 * Redirect /commands to /shortcuts, with the GET query parameters.
 *
 * @return void
 */
function serchilo_legacy_redirect_commands() {

  $query_parameters = drupal_get_query_parameters();
  drupal_goto('shortcuts', array('query' => $query_parameters));
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
function serchilo_legacy_redirect_command($command_id, $path_element) {

  if (
    (empty($command_id)) ||
    (!is_numeric($command_id)) ||
    FALSE
  ) {
    return MENU_NOT_FOUND;
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
    return MENU_NOT_FOUND;
  }
}
