<?php
/**
 * @file
 * serchilo.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function serchilo_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'access devel information'.
  $permissions['access devel information'] = array(
    'name' => 'access devel information',
    'roles' => array(
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'devel',
  );

  // Exported permission: 'access private fields'.
  $permissions['access private fields'] = array(
    'name' => 'access private fields',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'access toolbar'.
  $permissions['access toolbar'] = array(
    'name' => 'access toolbar',
    'roles' => array(),
    'module' => 'toolbar',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'administer actions'.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(),
    'module' => 'block',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer features'.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'administer field collections'.
  $permissions['administer field collections'] = array(
    'name' => 'administer field collections',
    'roles' => array(),
    'module' => 'field_collection',
  );

  // Exported permission: 'administer field permissions'.
  $permissions['administer field permissions'] = array(
    'name' => 'administer field permissions',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(),
    'module' => 'menu',
  );

  // Exported permission: 'administer module filter'.
  $permissions['administer module filter'] = array(
    'name' => 'administer module filter',
    'roles' => array(),
    'module' => 'module_filter',
  );

  // Exported permission: 'administer modules'.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'administer shortcuts'.
  $permissions['administer shortcuts'] = array(
    'name' => 'administer shortcuts',
    'roles' => array(),
    'module' => 'shortcut',
  );

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer software updates'.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'create field_argument_count'.
  $permissions['create field_argument_count'] = array(
    'name' => 'create field_argument_count',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_argument_names'.
  $permissions['create field_argument_names'] = array(
    'name' => 'create field_argument_names',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_command_id'.
  $permissions['create field_command_id'] = array(
    'name' => 'create field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_invisible'.
  $permissions['create field_invisible'] = array(
    'name' => 'create field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_namespace'.
  $permissions['create field_namespace'] = array(
    'name' => 'create field_namespace',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_set_referrer'.
  $permissions['create field_set_referrer'] = array(
    'name' => 'create field_set_referrer',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_weight'.
  $permissions['create field_weight'] = array(
    'name' => 'create field_weight',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create shortcut content'.
  $permissions['create shortcut content'] = array(
    'name' => 'create shortcut content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'customize shortcut links'.
  $permissions['customize shortcut links'] = array(
    'name' => 'customize shortcut links',
    'roles' => array(),
    'module' => 'shortcut',
  );

  // Exported permission: 'delete any shortcut content'.
  $permissions['delete any shortcut content'] = array(
    'name' => 'delete any shortcut content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own shortcut content'.
  $permissions['delete own shortcut content'] = array(
    'name' => 'delete own shortcut content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in namespaces'.
  $permissions['delete terms in namespaces'] = array(
    'name' => 'delete terms in namespaces',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in tags'.
  $permissions['delete terms in tags'] = array(
    'name' => 'delete terms in tags',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any shortcut content'.
  $permissions['edit any shortcut content'] = array(
    'name' => 'edit any shortcut content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit field_argument_count'.
  $permissions['edit field_argument_count'] = array(
    'name' => 'edit field_argument_count',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_argument_names'.
  $permissions['edit field_argument_names'] = array(
    'name' => 'edit field_argument_names',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_command_id'.
  $permissions['edit field_command_id'] = array(
    'name' => 'edit field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_invisible'.
  $permissions['edit field_invisible'] = array(
    'name' => 'edit field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_namespace'.
  $permissions['edit field_namespace'] = array(
    'name' => 'edit field_namespace',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_set_referrer'.
  $permissions['edit field_set_referrer'] = array(
    'name' => 'edit field_set_referrer',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_weight'.
  $permissions['edit field_weight'] = array(
    'name' => 'edit field_weight',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_argument_count'.
  $permissions['edit own field_argument_count'] = array(
    'name' => 'edit own field_argument_count',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_argument_names'.
  $permissions['edit own field_argument_names'] = array(
    'name' => 'edit own field_argument_names',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_command_id'.
  $permissions['edit own field_command_id'] = array(
    'name' => 'edit own field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_invisible'.
  $permissions['edit own field_invisible'] = array(
    'name' => 'edit own field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_namespace'.
  $permissions['edit own field_namespace'] = array(
    'name' => 'edit own field_namespace',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_set_referrer'.
  $permissions['edit own field_set_referrer'] = array(
    'name' => 'edit own field_set_referrer',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_weight'.
  $permissions['edit own field_weight'] = array(
    'name' => 'edit own field_weight',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own shortcut content'.
  $permissions['edit own shortcut content'] = array(
    'name' => 'edit own shortcut content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit revisions'.
  $permissions['edit revisions'] = array(
    'name' => 'edit revisions',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'revisioning',
  );

  // Exported permission: 'edit terms in namespaces'.
  $permissions['edit terms in namespaces'] = array(
    'name' => 'edit terms in namespaces',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in tags'.
  $permissions['edit terms in tags'] = array(
    'name' => 'edit terms in tags',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'execute php code'.
  $permissions['execute php code'] = array(
    'name' => 'execute php code',
    'roles' => array(),
    'module' => 'devel',
  );

  // Exported permission: 'generate features'.
  $permissions['generate features'] = array(
    'name' => 'generate features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'manage features'.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'publish revisions'.
  $permissions['publish revisions'] = array(
    'name' => 'publish revisions',
    'roles' => array(),
    'module' => 'revisioning',
  );

  // Exported permission: 'publish revisions of any shortcut content'.
  $permissions['publish revisions of any shortcut content'] = array(
    'name' => 'publish revisions of any shortcut content',
    'roles' => array(),
    'module' => 'revisioning',
  );

  // Exported permission: 'publish revisions of own shortcut content'.
  $permissions['publish revisions of own shortcut content'] = array(
    'name' => 'publish revisions of own shortcut content',
    'roles' => array(),
    'module' => 'revisioning',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'switch shortcut sets'.
  $permissions['switch shortcut sets'] = array(
    'name' => 'switch shortcut sets',
    'roles' => array(),
    'module' => 'shortcut',
  );

  // Exported permission: 'switch users'.
  $permissions['switch users'] = array(
    'name' => 'switch users',
    'roles' => array(),
    'module' => 'devel',
  );

  // Exported permission: 'unpublish current revision'.
  $permissions['unpublish current revision'] = array(
    'name' => 'unpublish current revision',
    'roles' => array(),
    'module' => 'revisioning',
  );

  // Exported permission: 'view field_argument_count'.
  $permissions['view field_argument_count'] = array(
    'name' => 'view field_argument_count',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_argument_names'.
  $permissions['view field_argument_names'] = array(
    'name' => 'view field_argument_names',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_command_id'.
  $permissions['view field_command_id'] = array(
    'name' => 'view field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_invisible'.
  $permissions['view field_invisible'] = array(
    'name' => 'view field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_namespace'.
  $permissions['view field_namespace'] = array(
    'name' => 'view field_namespace',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_set_referrer'.
  $permissions['view field_set_referrer'] = array(
    'name' => 'view field_set_referrer',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_weight'.
  $permissions['view field_weight'] = array(
    'name' => 'view field_weight',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_argument_count'.
  $permissions['view own field_argument_count'] = array(
    'name' => 'view own field_argument_count',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_argument_names'.
  $permissions['view own field_argument_names'] = array(
    'name' => 'view own field_argument_names',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_command_id'.
  $permissions['view own field_command_id'] = array(
    'name' => 'view own field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_invisible'.
  $permissions['view own field_invisible'] = array(
    'name' => 'view own field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_namespace'.
  $permissions['view own field_namespace'] = array(
    'name' => 'view own field_namespace',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_set_referrer'.
  $permissions['view own field_set_referrer'] = array(
    'name' => 'view own field_set_referrer',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_weight'.
  $permissions['view own field_weight'] = array(
    'name' => 'view own field_weight',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revision status messages'.
  $permissions['view revision status messages'] = array(
    'name' => 'view revision status messages',
    'roles' => array(),
    'module' => 'revisioning',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revisions of any shortcut content'.
  $permissions['view revisions of any shortcut content'] = array(
    'name' => 'view revisions of any shortcut content',
    'roles' => array(),
    'module' => 'revisioning',
  );

  // Exported permission: 'view revisions of own shortcut content'.
  $permissions['view revisions of own shortcut content'] = array(
    'name' => 'view revisions of own shortcut content',
    'roles' => array(),
    'module' => 'revisioning',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(),
    'module' => 'system',
  );

  return $permissions;
}
