<?PHP

/**
 * Validate user registration.
 */
function serchilo_form_user_register_form_validate($form, &$form_state) {

  // Lowercase the username.
  $form_state['values']['name'] = strtolower($form_state['values']['name']);
  
  // Extract the submitted name.
  $name = $form_state['values']['name'];

  // Make sure length is >=4.
  // Shorter lengths are reserved for site namespaces like language and country 
  // namespaces.
  if (strlen($name) < 4) {
    form_set_error('name', t('The username must contain at least 4 characters.'));
  }

  // Exclude dots and dashes.
  // (Names will be namespaces, dots are used to separate namespaces. And for 
  // dashes I forgot the reason. :-/ )
  if (
    (strpos($name, ' ') !== false) ||
    (strpos($name, '.') !== false) ||
    (strpos($name, '-') !== false) 
  ) {
    form_set_error('name', t('The username must not contain ".", "-" or spaces.'));
  }

  // Disallow user names that collide with existing paths.
  if (in_array($name, array('login', 'autocomplete', 'login', 'register', 'password', 'reset', 'logout'))) {
    form_set_error('name', t('This username is not allowed.'));
  }
}

