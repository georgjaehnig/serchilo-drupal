<?php
/**
 * @file
 * serchilo_features.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function serchilo_features_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_advanced_group|node|shortcut|form';
  $field_group->group_name = 'group_advanced_group';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shortcut';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Advanced group',
    'weight' => '6',
    'children' => array(
      0 => 'group_advanced_item',
    ),
    'format_type' => 'accordion',
    'format_settings' => array(
      'label' => 'Advanced group',
      'instance_settings' => array(
        'classes' => 'group-advanced-group field-group-accordion',
        'effect' => 'none',
      ),
    ),
  );
  $export['group_advanced_group|node|shortcut|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_advanced_item|node|shortcut|form';
  $field_group->group_name = 'group_advanced_item';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shortcut';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_advanced_group';
  $field_group->data = array(
    'label' => 'Advanced',
    'weight' => '22',
    'children' => array(
      0 => 'field_input_encoding',
      1 => 'field_test',
      2 => 'field_post_parameters',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'Advanced',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-advanced-item field-group-accordion-item',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_advanced_item|node|shortcut|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_more_info_group|node|shortcut|form';
  $field_group->group_name = 'group_more_info_group';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shortcut';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'More info group',
    'weight' => '4',
    'children' => array(
      0 => 'group_more_info_item',
    ),
    'format_type' => 'accordion',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'effect' => 'none',
        'classes' => '',
      ),
    ),
  );
  $export['group_more_info_group|node|shortcut|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_more_info_item|node|shortcut|form';
  $field_group->group_name = 'group_more_info_item';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shortcut';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_more_info_group';
  $field_group->data = array(
    'label' => 'More info',
    'weight' => '5',
    'children' => array(
      0 => 'field_description',
      1 => 'field_example',
      2 => 'field_tags',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_more_info_item|node|shortcut|form'] = $field_group;

  return $export;
}
