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

  // Exported menu link: main-menu_api:help/api
  $menu_links['main-menu_api:help/api'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/api',
    'router_path' => 'help/api',
    'link_title' => 'API',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_api:help/api',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
  );
  // Exported menu link: main-menu_blog:blog
  $menu_links['main-menu_blog:blog'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'blog',
    'router_path' => 'blog',
    'link_title' => 'Blog',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_blog:blog',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
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
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_browser-integration:help/integration
  $menu_links['main-menu_browser-integration:help/integration'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/integration',
    'router_path' => 'help/integration',
    'link_title' => 'Browser integration',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_browser-integration:help/integration',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
  );
  // Exported menu link: main-menu_changed-shortcuts:new/changes
  $menu_links['main-menu_changed-shortcuts:new/changes'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'new/changes',
    'router_path' => 'new/changes',
    'link_title' => 'Changed shortcuts',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_changed-shortcuts:new/changes',
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
  // Exported menu link: main-menu_default-keyword:help/default-keyword
  $menu_links['main-menu_default-keyword:help/default-keyword'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/default-keyword',
    'router_path' => 'help/default-keyword',
    'link_title' => 'Default keyword',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_default-keyword:help/default-keyword',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
  );
  // Exported menu link: main-menu_differences-to-old-serchilo:help/differences
  $menu_links['main-menu_differences-to-old-serchilo:help/differences'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/differences',
    'router_path' => 'help/differences',
    'link_title' => 'Differences to old Serchilo',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_differences-to-old-serchilo:help/differences',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
  );
  // Exported menu link: main-menu_editing:help/editing
  $menu_links['main-menu_editing:help/editing'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/editing',
    'router_path' => 'help/editing',
    'link_title' => 'Editing',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_editing:help/editing',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
  );
  // Exported menu link: main-menu_export-all:export
  $menu_links['main-menu_export-all:export'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'export',
    'router_path' => 'export',
    'link_title' => 'Export all',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_export-all:export',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'main-menu_browse:browse',
  );
  // Exported menu link: main-menu_forum:forum
  $menu_links['main-menu_forum:forum'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'forum',
    'router_path' => 'forum',
    'link_title' => 'Forum',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_forum:forum',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: main-menu_getting-started:help/start
  $menu_links['main-menu_getting-started:help/start'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/start',
    'router_path' => 'help/start',
    'link_title' => 'Getting started',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_getting-started:help/start',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
  );
  // Exported menu link: main-menu_help:help
  $menu_links['main-menu_help:help'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help',
    'router_path' => 'help',
    'link_title' => 'Help',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_help:help',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
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
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'main-menu_browse:browse',
  );
  // Exported menu link: main-menu_namespaces:help/namespaces
  $menu_links['main-menu_namespaces:help/namespaces'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/namespaces',
    'router_path' => 'help/namespaces',
    'link_title' => 'Namespaces',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_namespaces:help/namespaces',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
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
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'main-menu_browse:browse',
  );
  // Exported menu link: main-menu_new-shortcuts:new/shortcuts
  $menu_links['main-menu_new-shortcuts:new/shortcuts'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'new/shortcuts',
    'router_path' => 'new/shortcuts',
    'link_title' => 'New shortcuts',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_new-shortcuts:new/shortcuts',
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
  // Exported menu link: main-menu_privacy-policy:help/privacy
  $menu_links['main-menu_privacy-policy:help/privacy'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/privacy',
    'router_path' => 'help/privacy',
    'link_title' => 'Privacy policy',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_privacy-policy:help/privacy',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -41,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
  );
  // Exported menu link: main-menu_shortcut-urls:help/url
  $menu_links['main-menu_shortcut-urls:help/url'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/url',
    'router_path' => 'help/url',
    'link_title' => 'Shortcut URLs',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_shortcut-urls:help/url',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
  );
  // Exported menu link: main-menu_shortcuts:shortcuts
  $menu_links['main-menu_shortcuts:shortcuts'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'shortcuts',
    'router_path' => 'shortcuts',
    'link_title' => 'Shortcuts',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_shortcuts:shortcuts',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_browse:browse',
  );
  // Exported menu link: main-menu_source-code:help/code.
  $menu_links['main-menu_source-code:help/code'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'help/code',
    'router_path' => 'help/code',
    'link_title' => 'Source code',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_source-code:help/code',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:help',
  );
  // Exported menu link: main-menu_tags:tags.
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
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_browse:browse',
  );
  // Exported menu link: user-menu_edit:user/edit
  $menu_links['user-menu_edit:user/edit'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/edit',
    'router_path' => 'user/edit',
    'link_title' => 'Edit',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_edit:user/edit',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'user-menu_user-account:user',
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
    'weight' => -46,
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
  // Exported menu link: user-menu_my-shortcuts:user/shortcuts
  $menu_links['user-menu_my-shortcuts:user/shortcuts'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/shortcuts',
    'router_path' => 'user/shortcuts',
    'link_title' => 'My shortcuts',
    'options' => array(
      'identifier' => 'user-menu_my-shortcuts:user/shortcuts',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'user-menu_user-account:user',
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
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('API');
  t('Blog');
  t('Browse');
  t('Browser integration');
  t('Changed shortcuts');
  t('Default keyword');
  t('Differences to old Serchilo');
  t('Edit');
  t('Editing');
  t('Export all');
  t('Forum');
  t('Getting started');
  t('Help');
  t('Log out');
  t('Login');
  t('My shortcuts');
  t('Namespace types');
  t('Namespaces');
  t('New shortcuts');
  t('Privacy policy');
  t('Register');
  t('Shortcut URLs');
  t('Shortcuts');
  t('Source code');
  t('Tags');
  t('User account');

  return $menu_links;
}
