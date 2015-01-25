<?PHP

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

