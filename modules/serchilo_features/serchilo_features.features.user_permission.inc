<?php
/**
 * @file
 * serchilo_features.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function serchilo_features_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'access all views'.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
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

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer elysia_cron'.
  $permissions['administer elysia_cron'] = array(
    'name' => 'administer elysia_cron',
    'roles' => array(),
    'module' => 'elysia_cron',
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

  // Exported permission: 'administer fieldgroups'.
  $permissions['administer fieldgroups'] = array(
    'name' => 'administer fieldgroups',
    'roles' => array(),
    'module' => 'field_group',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: 'administer languages'.
  $permissions['administer languages'] = array(
    'name' => 'administer languages',
    'roles' => array(),
    'module' => 'locale',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(),
    'module' => 'menu',
  );

  // Exported permission: 'administer meta tags'.
  $permissions['administer meta tags'] = array(
    'name' => 'administer meta tags',
    'roles' => array(),
    'module' => 'metatag',
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

  // Exported permission: 'administer pathauto'.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(),
    'module' => 'user',
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

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(),
    'module' => 'path',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'administer views'.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: 'approve shortcut content'.
  $permissions['approve shortcut content'] = array(
    'name' => 'approve shortcut content',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'serchilo',
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
    'roles' => array(
      'moderator' => 'moderator',
    ),
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

  // Exported permission: 'clone node'.
  $permissions['clone node'] = array(
    'name' => 'clone node',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'clone',
  );

  // Exported permission: 'clone own nodes'.
  $permissions['clone own nodes'] = array(
    'name' => 'clone own nodes',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'clone',
  );

  // Exported permission: 'create article content'.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create discussion content'.
  $permissions['create discussion content'] = array(
    'name' => 'create discussion content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create field_active'.
  $permissions['create field_active'] = array(
    'name' => 'create field_active',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_approved'.
  $permissions['create field_approved'] = array(
    'name' => 'create field_approved',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
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

  // Exported permission: 'create field_body'.
  $permissions['create field_body'] = array(
    'name' => 'create field_body',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_calls_last_30_days'.
  $permissions['create field_calls_last_30_days'] = array(
    'name' => 'create field_calls_last_30_days',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_calls_total'.
  $permissions['create field_calls_total'] = array(
    'name' => 'create field_calls_total',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_command_id'.
  $permissions['create field_command_id'] = array(
    'name' => 'create field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_example'.
  $permissions['create field_example'] = array(
    'name' => 'create field_example',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_example_arguments'.
  $permissions['create field_example_arguments'] = array(
    'name' => 'create field_example_arguments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_example_description'.
  $permissions['create field_example_description'] = array(
    'name' => 'create field_example_description',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_invisible'.
  $permissions['create field_invisible'] = array(
    'name' => 'create field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_keyword'.
  $permissions['create field_keyword'] = array(
    'name' => 'create field_keyword',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
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

  // Exported permission: 'create field_shortcuts_affected'.
  $permissions['create field_shortcuts_affected'] = array(
    'name' => 'create field_shortcuts_affected',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_tags'.
  $permissions['create field_tags'] = array(
    'name' => 'create field_tags',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_test'.
  $permissions['create field_test'] = array(
    'name' => 'create field_test',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_test_passed'.
  $permissions['create field_test_passed'] = array(
    'name' => 'create field_test_passed',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_url'.
  $permissions['create field_url'] = array(
    'name' => 'create field_url',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
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

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(),
    'module' => 'path',
  );

  // Exported permission: 'deactivate any shortcut content'.
  $permissions['deactivate any shortcut content'] = array(
    'name' => 'deactivate any shortcut content',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'serchilo',
  );

  // Exported permission: 'delete any article content'.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any discussion content'.
  $permissions['delete any discussion content'] = array(
    'name' => 'delete any discussion content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any shortcut content'.
  $permissions['delete any shortcut content'] = array(
    'name' => 'delete any shortcut content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own article content'.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own discussion content'.
  $permissions['delete own discussion content'] = array(
    'name' => 'delete own discussion content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own shortcut content'.
  $permissions['delete own shortcut content'] = array(
    'name' => 'delete own shortcut content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in namespace_types'.
  $permissions['delete terms in namespace_types'] = array(
    'name' => 'delete terms in namespace_types',
    'roles' => array(),
    'module' => 'taxonomy',
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

  // Exported permission: 'edit any article content'.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any discussion content'.
  $permissions['edit any discussion content'] = array(
    'name' => 'edit any discussion content',
    'roles' => array(),
    'module' => 'node',
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

  // Exported permission: 'edit field_active'.
  $permissions['edit field_active'] = array(
    'name' => 'edit field_active',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_approved'.
  $permissions['edit field_approved'] = array(
    'name' => 'edit field_approved',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
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

  // Exported permission: 'edit field_body'.
  $permissions['edit field_body'] = array(
    'name' => 'edit field_body',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_calls_last_30_days'.
  $permissions['edit field_calls_last_30_days'] = array(
    'name' => 'edit field_calls_last_30_days',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_calls_total'.
  $permissions['edit field_calls_total'] = array(
    'name' => 'edit field_calls_total',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_command_id'.
  $permissions['edit field_command_id'] = array(
    'name' => 'edit field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_example'.
  $permissions['edit field_example'] = array(
    'name' => 'edit field_example',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_example_arguments'.
  $permissions['edit field_example_arguments'] = array(
    'name' => 'edit field_example_arguments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_example_description'.
  $permissions['edit field_example_description'] = array(
    'name' => 'edit field_example_description',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_invisible'.
  $permissions['edit field_invisible'] = array(
    'name' => 'edit field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_keyword'.
  $permissions['edit field_keyword'] = array(
    'name' => 'edit field_keyword',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
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

  // Exported permission: 'edit field_shortcuts_affected'.
  $permissions['edit field_shortcuts_affected'] = array(
    'name' => 'edit field_shortcuts_affected',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_tags'.
  $permissions['edit field_tags'] = array(
    'name' => 'edit field_tags',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_test'.
  $permissions['edit field_test'] = array(
    'name' => 'edit field_test',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_test_passed'.
  $permissions['edit field_test_passed'] = array(
    'name' => 'edit field_test_passed',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_url'.
  $permissions['edit field_url'] = array(
    'name' => 'edit field_url',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_weight'.
  $permissions['edit field_weight'] = array(
    'name' => 'edit field_weight',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit meta tags'.
  $permissions['edit meta tags'] = array(
    'name' => 'edit meta tags',
    'roles' => array(),
    'module' => 'metatag',
  );

  // Exported permission: 'edit own article content'.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'edit own discussion content'.
  $permissions['edit own discussion content'] = array(
    'name' => 'edit own discussion content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own field_active'.
  $permissions['edit own field_active'] = array(
    'name' => 'edit own field_active',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_approved'.
  $permissions['edit own field_approved'] = array(
    'name' => 'edit own field_approved',
    'roles' => array(
      'moderator' => 'moderator',
    ),
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

  // Exported permission: 'edit own field_body'.
  $permissions['edit own field_body'] = array(
    'name' => 'edit own field_body',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_calls_last_30_days'.
  $permissions['edit own field_calls_last_30_days'] = array(
    'name' => 'edit own field_calls_last_30_days',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_calls_total'.
  $permissions['edit own field_calls_total'] = array(
    'name' => 'edit own field_calls_total',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_command_id'.
  $permissions['edit own field_command_id'] = array(
    'name' => 'edit own field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_example'.
  $permissions['edit own field_example'] = array(
    'name' => 'edit own field_example',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_example_arguments'.
  $permissions['edit own field_example_arguments'] = array(
    'name' => 'edit own field_example_arguments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_example_description'.
  $permissions['edit own field_example_description'] = array(
    'name' => 'edit own field_example_description',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_invisible'.
  $permissions['edit own field_invisible'] = array(
    'name' => 'edit own field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_keyword'.
  $permissions['edit own field_keyword'] = array(
    'name' => 'edit own field_keyword',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
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

  // Exported permission: 'edit own field_shortcuts_affected'.
  $permissions['edit own field_shortcuts_affected'] = array(
    'name' => 'edit own field_shortcuts_affected',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_tags'.
  $permissions['edit own field_tags'] = array(
    'name' => 'edit own field_tags',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_test'.
  $permissions['edit own field_test'] = array(
    'name' => 'edit own field_test',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_test_passed'.
  $permissions['edit own field_test_passed'] = array(
    'name' => 'edit own field_test_passed',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_url'.
  $permissions['edit own field_url'] = array(
    'name' => 'edit own field_url',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
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

  // Exported permission: 'edit terms in namespace_types'.
  $permissions['edit terms in namespace_types'] = array(
    'name' => 'edit terms in namespace_types',
    'roles' => array(),
    'module' => 'taxonomy',
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

  // Exported permission: 'notify of path changes'.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'rename features'.
  $permissions['rename features'] = array(
    'name' => 'rename features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'translate interface'.
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(),
    'module' => 'locale',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format markdown'.
  $permissions['use text format markdown'] = array(
    'name' => 'use text format markdown',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'moderator' => 'moderator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view field_active'.
  $permissions['view field_active'] = array(
    'name' => 'view field_active',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_approved'.
  $permissions['view field_approved'] = array(
    'name' => 'view field_approved',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
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

  // Exported permission: 'view field_body'.
  $permissions['view field_body'] = array(
    'name' => 'view field_body',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_calls_last_30_days'.
  $permissions['view field_calls_last_30_days'] = array(
    'name' => 'view field_calls_last_30_days',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_calls_total'.
  $permissions['view field_calls_total'] = array(
    'name' => 'view field_calls_total',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_command_id'.
  $permissions['view field_command_id'] = array(
    'name' => 'view field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_example'.
  $permissions['view field_example'] = array(
    'name' => 'view field_example',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_example_arguments'.
  $permissions['view field_example_arguments'] = array(
    'name' => 'view field_example_arguments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_example_description'.
  $permissions['view field_example_description'] = array(
    'name' => 'view field_example_description',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_invisible'.
  $permissions['view field_invisible'] = array(
    'name' => 'view field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_keyword'.
  $permissions['view field_keyword'] = array(
    'name' => 'view field_keyword',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
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

  // Exported permission: 'view field_shortcuts_affected'.
  $permissions['view field_shortcuts_affected'] = array(
    'name' => 'view field_shortcuts_affected',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_tags'.
  $permissions['view field_tags'] = array(
    'name' => 'view field_tags',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_test'.
  $permissions['view field_test'] = array(
    'name' => 'view field_test',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_test_passed'.
  $permissions['view field_test_passed'] = array(
    'name' => 'view field_test_passed',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_url'.
  $permissions['view field_url'] = array(
    'name' => 'view field_url',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_weight'.
  $permissions['view field_weight'] = array(
    'name' => 'view field_weight',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_active'.
  $permissions['view own field_active'] = array(
    'name' => 'view own field_active',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_approved'.
  $permissions['view own field_approved'] = array(
    'name' => 'view own field_approved',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'moderator' => 'moderator',
    ),
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

  // Exported permission: 'view own field_body'.
  $permissions['view own field_body'] = array(
    'name' => 'view own field_body',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_calls_last_30_days'.
  $permissions['view own field_calls_last_30_days'] = array(
    'name' => 'view own field_calls_last_30_days',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_calls_total'.
  $permissions['view own field_calls_total'] = array(
    'name' => 'view own field_calls_total',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_command_id'.
  $permissions['view own field_command_id'] = array(
    'name' => 'view own field_command_id',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_example'.
  $permissions['view own field_example'] = array(
    'name' => 'view own field_example',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_example_arguments'.
  $permissions['view own field_example_arguments'] = array(
    'name' => 'view own field_example_arguments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_example_description'.
  $permissions['view own field_example_description'] = array(
    'name' => 'view own field_example_description',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_invisible'.
  $permissions['view own field_invisible'] = array(
    'name' => 'view own field_invisible',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_keyword'.
  $permissions['view own field_keyword'] = array(
    'name' => 'view own field_keyword',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
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

  // Exported permission: 'view own field_shortcuts_affected'.
  $permissions['view own field_shortcuts_affected'] = array(
    'name' => 'view own field_shortcuts_affected',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_tags'.
  $permissions['view own field_tags'] = array(
    'name' => 'view own field_tags',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_test'.
  $permissions['view own field_test'] = array(
    'name' => 'view own field_test',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_test_passed'.
  $permissions['view own field_test_passed'] = array(
    'name' => 'view own field_test_passed',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_url'.
  $permissions['view own field_url'] = array(
    'name' => 'view own field_url',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
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
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
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

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(),
    'module' => 'system',
  );

  return $permissions;
}
