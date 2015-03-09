<?PHP

/**
 * Redirects to shortcuts view, filtered by shortcuts of logged-in user.
 *
 * Builds a query out of the shortcut form arguments
 * and redirects it to the query handler.
 *
 * @return void
 */
function serchilo_page_user_shortcuts() {

  global $user;
  drupal_goto(
    'shortcuts',
    array(
      'query' => array(
        'namespace' => $user->name,
      ),
    )
  );
}
/**
 * Replace user_page().
 */
function serchilo_page_user_view() {

  global $user;

  if (
    (user_is_logged_in())
  ) {
    drupal_goto('u/' . $user->name); 
    return;
  }

  return user_view_page();
}

/**
 * Redirect to Edit profile of currently logged in user().
 */
function serchilo_page_user_edit() {

  global $user;

  if (user_is_logged_in()) {
    drupal_goto('user/' . $user->uid . '/edit'); 
    return;
  }

  return MENU_ACCESS_DENIED;
}

