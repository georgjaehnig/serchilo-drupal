<?PHP

/**
 * Display current namespaces.
 */
function serchilo_block_namespaces() {

  $namespaces      = drupal_static('serchilo_namespaces');
  $namespace_names = drupal_static('serchilo_namespace_names');

  // Get out if no namespaces are set.
  if (count($namespaces) == 0) {
    return;
  }

  // Create edit link if namespaces are editable.
  switch (arg(0)) {
  // If calling with n/:
  case SERCHILO_NAMESPACES_PATH_AFFIX:
    $link_path = SERCHILO_NAMESPACES_PATH_AFFIX . '/' . arg(1) . '/edit';
    break; 
  // If calling with u/:
  case SERCHILO_USER_PATH_AFFIX:
    global $user;
    // If on console of logged-in user:
    if (
      (isset($user->name)) && 
      ($user->name == arg(1))
    ) {
      $link_path = 'user/edit';
    }
    else {
      $link_path = 'help/namespaces';
    }
    break; 
  }

  if (isset($link_path)) {
    $link_text = join('.', $namespace_names);
    $link = array(
      '#type' => 'link',
      '#title' => $link_text,
      '#href' => $link_path,
      '#attributes' => array(
        'class' => array(
          'namespace', 
        ),
      ),
    );
  }
  return $link;
}

/**
 * Display licenses.
 */
function serchilo_block_licenses() {

  $dir = drupal_get_path('module', 'serchilo');

  // TODO: Solve this with theme('image'..);
  return '
    <a href="https://github.com/georgjaehnig/serchilo-drupal">
    <img src="/' . $dir . '/svg/agpl-v3.svg" width="72" height="30" />
    </a>
    <a href="/export">
    <img src="/' . $dir . '/svg/cc-by-sa.svg" width="80" height="15" />
    </a>
    ';
}

/**
 * Display licenses.
 */
function serchilo_block_add_to_browser() {

  return '
      <button class="btn btn-sm btn-default" onclick="window.external.AddSearchProvider( \'https://\' + location.host + \'/opensearch\' + location.pathname + location.search);">Add to browser</button>
    ';
}

