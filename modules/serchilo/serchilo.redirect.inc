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

