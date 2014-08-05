<?PHP

/**
 * Redirects to shortcuts view, filtered by shortcuts of given user.
 *
 * Builds a query out of the shortcut form arguments
 * and redirects it to the query handler.
 *
 * @param object $user
 *   User object.
 *
 * @return void
 */
function serchilo_page_user_shortcuts($user) {
  drupal_goto(
    'shortcuts',
    array(
      'query' => array(
        'namespace' => $user->name,
      ),
    )
  );
}
