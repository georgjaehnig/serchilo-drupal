<?php
/**
 * @file
 * serchilo_features.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function serchilo_features_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_browse:browse
  $menu_links['main-menu_browse:browse'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'browse',
    'router_path' => 'browse',
    'link_title' => 'Browse',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_browse:browse',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: main-menu_namespace-types:namespace-types
  $menu_links['main-menu_namespace-types:namespace-types'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'namespace-types',
    'router_path' => 'namespace-types',
    'link_title' => 'Namespace types',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_namespace-types:namespace-types',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_browse:browse',
  );
  // Exported menu link: main-menu_namespaces:namespaces
  $menu_links['main-menu_namespaces:namespaces'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'namespaces',
    'router_path' => 'namespaces',
    'link_title' => 'Namespaces',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_namespaces:namespaces',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'main-menu_browse:browse',
  );
  // Exported menu link: main-menu_shortcuts:shortcuts
  $menu_links['main-menu_shortcuts:shortcuts'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'shortcuts',
    'router_path' => 'shortcuts',
    'link_title' => 'Shortcuts',
    'options' => array(
      'identifier' => 'main-menu_shortcuts:shortcuts',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_browse:browse',
  );
  // Exported menu link: main-menu_tags:tags
  $menu_links['main-menu_tags:tags'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'tags',
    'router_path' => 'tags',
    'link_title' => 'Tags',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_tags:tags',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_browse:browse',
  );
  // Exported menu link: user-menu_log-out:user/logout
  $menu_links['user-menu_log-out:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'identifier' => 'user-menu_log-out:user/logout',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: user-menu_login:user/login
  $menu_links['user-menu_login:user/login'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/login',
    'router_path' => 'user/login',
    'link_title' => 'Login',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_login:user/login',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: user-menu_register:user/register
  $menu_links['user-menu_register:user/register'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/register',
    'router_path' => 'user/register',
    'link_title' => 'Register',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_register:user/register',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: user-menu_user-account:user
  $menu_links['user-menu_user-account:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'user-menu_user-account:user',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Browse');
  t('Log out');
  t('Login');
  t('Namespace types');
  t('Namespaces');
  t('Register');
  t('Shortcuts');
  t('Tags');
  t('User account');


  return $menu_links;
}
