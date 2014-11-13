<?php
/**
 * @file
 * serchilo_features.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function serchilo_features_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'comment-comment_node_shortcut-comment_body'
  $field_instances['comment-comment_node_shortcut-comment_body'] = array(
    'bundle' => 'comment_node_shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'comment_body',
    'label' => 'Comment',
    'required' => TRUE,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_example-field_example_arguments'
  $field_instances['field_collection_item-field_example-field_example_arguments'] = array(
    'bundle' => 'field_example',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Example arguments to call this shortcut. Separate multiple arguments with comma.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'serchilo',
        'settings' => array(),
        'type' => 'serchilo_shortcut_example_link_formatter',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_example_arguments',
    'label' => 'Arguments',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_example-field_example_description'
  $field_instances['field_collection_item-field_example-field_example_description'] = array(
    'bundle' => 'field_example',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'What happens when calling this shortcut?',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_example_description',
    'label' => 'Description',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_test-field_test_arguments'
  $field_instances['field_collection_item-field_test-field_test_arguments'] = array(
    'bundle' => 'field_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Test arguments to call this shortcut. Separate multiple arguments with comma.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_test_arguments',
    'label' => 'Arguments',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_test-field_test_expected_content'
  $field_instances['field_collection_item-field_test-field_test_expected_content'] = array(
    'bundle' => 'field_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Content that the target page must contain.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_test_expected_content',
    'label' => 'Expected content',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_test-field_test_passed'
  $field_instances['field_collection_item-field_test-field_test_passed'] = array(
    'bundle' => 'field_test',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'If true, the last test succeeded. If false, it failed.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_test_passed',
    'label' => 'Test passed',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_argument_count'
  $field_instances['node-shortcut-field_argument_count'] = array(
    'bundle' => 'shortcut',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'The argument count is extracted automatically from the URL.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_argument_count',
    'label' => 'Argument count',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_argument_names'
  $field_instances['node-shortcut-field_argument_names'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The argument names are extracted automatically from the URL.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_argument_names',
    'label' => 'Argument names',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_calls_last_30_days'
  $field_instances['node-shortcut-field_calls_last_30_days'] = array(
    'bundle' => 'shortcut',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 16,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_calls_last_30_days',
    'label' => 'Calls in the last 30 days',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_calls_total'
  $field_instances['node-shortcut-field_calls_total'] = array(
    'bundle' => 'shortcut',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 15,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_calls_total',
    'label' => 'Calls total',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_command_id'
  $field_instances['node-shortcut-field_command_id'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Ensures backwards compatibility to the old (Drupal) Serchilo (launched 2013). Requests calling command/[command_id] can be redirected to the current Shortcut node page.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_command_id',
    'label' => 'Command ID',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_description'
  $field_instances['node-shortcut-field_description'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 13,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_description',
    'label' => 'Description',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_example'
  $field_instances['node-shortcut-field_example'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Examples show how the shortcut can be used. Add various examples to cover as many use cases as possible.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_collection',
        'settings' => array(
          'add' => '',
          'delete' => '',
          'description' => 0,
          'edit' => '',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_example',
    'label' => 'Examples',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_collection',
      'settings' => array(),
      'type' => 'field_collection_embed',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_input_encoding'
  $field_instances['node-shortcut-field_input_encoding'] = array(
    'bundle' => 'shortcut',
    'default_value' => array(
      0 => array(
        'value' => 'UTF-8',
      ),
    ),
    'deleted' => 0,
    'description' => 'The arguments from the query will be encoded in the URL with the encoding provided here.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_input_encoding',
    'label' => 'Input Encoding',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_invisible'
  $field_instances['node-shortcut-field_invisible'] = array(
    'bundle' => 'shortcut',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'If true, the shortcut will not be shown in the shortcut view or in the autocomplete. Useful for outdated shortcuts, only redirecting the the current shortcut page.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 9,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_invisible',
    'label' => 'Invisible',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_keyword'
  $field_instances['node-shortcut-field_keyword'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Every shortcut is called with a keyword. See Help → "Getting started" for more info. ',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_keyword',
    'label' => 'Keyword',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_namespace'
  $field_instances['node-shortcut-field_namespace'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The shortcut will be available only to users using this namespace. See Help → "Namespaces" for more info. ',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_namespace',
    'label' => 'Namespace',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'content_taxonomy_autocomplete_new_terms' => 'deny',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_post_parameters'
  $field_instances['node-shortcut-field_post_parameters'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A string of key=value pairs separated by "&", to be sent with POST method. May contain placeholders as the URL.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 14,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_post_parameters',
    'label' => 'POST parameters',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_set_referrer'
  $field_instances['node-shortcut-field_set_referrer'] = array(
    'bundle' => 'shortcut',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'If true, the redirect will be done through a HTML page displayed by Serchilo. Thus, the target site will get Serchilo as a referrer site. Useful for affiliate links that require a correct referrer.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_set_referrer',
    'label' => 'Set referrer',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_tags'
  $field_instances['node-shortcut-field_tags'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Separate tags with comma. Add any useful tags for the shortcut to be easily found in listings and autocomplete. Tags do not influence the availability of a shortcut.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_tags',
    'label' => 'Tags',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'content_taxonomy_autocomplete_new_terms' => 'allow',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_test'
  $field_instances['node-shortcut-field_test'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Allows regular automatic testing to check if the shortcut URL is still valid.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 12,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_test',
    'label' => 'Test',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_collection',
      'settings' => array(),
      'type' => 'field_collection_embed',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_url'
  $field_instances['node-shortcut-field_url'] = array(
    'bundle' => 'shortcut',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The URL can contain placeholders like {s:argument_name}. See Help → "Shortcut URLs" for more info. ',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_url',
    'label' => 'URL',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-shortcut-field_weight'
  $field_instances['node-shortcut-field_weight'] = array(
    'bundle' => 'shortcut',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Calculated automatically from usage statistics. Can be used to improve the order of the listed shortcuts in the shortcut view or autocomplete.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_weight',
    'label' => 'Weight',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'taxonomy_term-namespaces-field_namespace_type'
  $field_instances['taxonomy_term-namespaces-field_namespace_type'] = array(
    'bundle' => 'namespaces',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_namespace_type',
    'label' => 'Namespace type',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => 0,
      ),
      'type' => 'options_select',
      'weight' => 41,
    ),
  );

  // Exported field_instance: 'user-user-field_country_namespace'
  $field_instances['user-user-field_country_namespace'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_country_namespace',
    'label' => 'Country namespace',
    'required' => 1,
    'settings' => array(
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => 0,
      ),
      'type' => 'options_select',
      'weight' => 42,
    ),
  );

  // Exported field_instance: 'user-user-field_custom_namespaces'
  $field_instances['user-user-field_custom_namespaces'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The namespaces will have the following priority (first = highest):
    <ol>
      <li>Your user namespace</li>
      <li>Custom namespaces</li>
      <li>Country namespace</li>
      <li>Language namespace</li>
      <li>o (planet namespace)</li>
    </ol>   
    So it will be first checked, if a query matches a command in your user namespace, then in one of your custom namespaces ..., and at least in the planet namespace.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_custom_namespaces',
    'label' => 'Custom namespaces',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'content_taxonomy_autocomplete_new_terms' => 'deny',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 43,
    ),
  );

  // Exported field_instance: 'user-user-field_default_keyword'
  $field_instances['user-user-field_default_keyword'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_default_keyword',
    'label' => 'Default keyword',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 44,
    ),
  );

  // Exported field_instance: 'user-user-field_language_namespace'
  $field_instances['user-user-field_language_namespace'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_language_namespace',
    'label' => 'Language namespace',
    'required' => 1,
    'settings' => array(
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => 0,
      ),
      'type' => 'options_select',
      'weight' => 41,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('A string of key=value pairs separated by "&", to be sent with POST method. May contain placeholders as the URL.');
  t('Allows regular automatic testing to check if the shortcut URL is still valid.');
  t('Argument count');
  t('Argument names');
  t('Arguments');
  t('Calculated automatically from usage statistics. Can be used to improve the order of the listed shortcuts in the shortcut view or autocomplete.');
  t('Calls in the last 30 days');
  t('Calls total');
  t('Command ID');
  t('Comment');
  t('Content that the target page must contain.');
  t('Country namespace');
  t('Custom namespaces');
  t('Default keyword');
  t('Description');
  t('Ensures backwards compatibility to the old (Drupal) Serchilo (launched 2013). Requests calling command/[command_id] can be redirected to the current Shortcut node page.');
  t('Every shortcut is called with a keyword. See Help → "Getting started" for more info. ');
  t('Example arguments to call this shortcut. Separate multiple arguments with comma.');
  t('Examples');
  t('Examples show how the shortcut can be used. Add various examples to cover as many use cases as possible.');
  t('Expected content');
  t('If true, the last test succeeded. If false, it failed.');
  t('If true, the redirect will be done through a HTML page displayed by Serchilo. Thus, the target site will get Serchilo as a referrer site. Useful for affiliate links that require a correct referrer.');
  t('If true, the shortcut will not be shown in the shortcut view or in the autocomplete. Useful for outdated shortcuts, only redirecting the the current shortcut page.');
  t('Input Encoding');
  t('Invisible');
  t('Keyword');
  t('Language namespace');
  t('Namespace');
  t('Namespace type');
  t('POST parameters');
  t('Separate tags with comma. Add any useful tags for the shortcut to be easily found in listings and autocomplete. Tags do not influence the availability of a shortcut.');
  t('Set referrer');
  t('Tags');
  t('Test');
  t('Test arguments to call this shortcut. Separate multiple arguments with comma.');
  t('Test passed');
  t('The URL can contain placeholders like {s:argument_name}. See Help → "Shortcut URLs" for more info. ');
  t('The argument count is extracted automatically from the URL.');
  t('The argument names are extracted automatically from the URL.');
  t('The arguments from the query will be encoded in the URL with the encoding provided here.');
  t('The namespaces will have the following priority (first = highest):
    <ol>
      <li>Your user namespace</li>
      <li>Custom namespaces</li>
      <li>Country namespace</li>
      <li>Language namespace</li>
      <li>o (planet namespace)</li>
    </ol>   
    So it will be first checked, if a query matches a command in your user namespace, then in one of your custom namespaces ..., and at least in the planet namespace.');
  t('The shortcut will be available only to users using this namespace. See Help → "Namespaces" for more info. ');
  t('URL');
  t('Weight');
  t('What happens when calling this shortcut?');

  return $field_instances;
}
