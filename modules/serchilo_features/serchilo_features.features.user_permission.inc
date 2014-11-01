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

  // Exported permission: 'administer spamicide'.
  $permissions['administer spamicide'] = array(
    'name' => 'administer spamicide',
    'roles' => array(),
    'module' => 'spamicide',
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

  // Exported permission: 'create field_input_encoding'.
  $permissions['create field_input_encoding'] = array(
    'name' => 'create field_input_encoding',
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

  // Exported permission: 'edit field_input_encoding'.
  $permissions['edit field_input_encoding'] = array(
    'name' => 'edit field_input_encoding',
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

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
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

  // Exported permission: 'edit own field_input_encoding'.
  $permissions['edit own field_input_encoding'] = array(
    'name' => 'edit own field_input_encoding',
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

  // Exported permission: 'edit revisions'.
  $permissions['edit revisions'] = array(
    'name' => 'edit revisions',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'revisioning',
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

  // Exported permission: 'rename features'.
  $permissions['rename features'] = array(
    'name' => 'rename features',
    'roles' => array(),
    'module' => 'features',
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

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'switch users'.
  $permissions['switch users'] = array(
    'name' => 'switch users',
    'roles' => array(),
    'module' => 'devel',
  );

  // Exported permission: 'translate interface'.
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(),
    'module' => 'locale',
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

  // Exported permission: 'view field_input_encoding'.
  $permissions['view field_input_encoding'] = array(
    'name' => 'view field_input_encoding',
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

  // Exported permission: 'view own field_input_encoding'.
  $permissions['view own field_input_encoding'] = array(
    'name' => 'view own field_input_encoding',
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
