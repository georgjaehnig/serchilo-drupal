<?php
/**
 * @file
 * serchilo_features.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function serchilo_features_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function serchilo_features_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function serchilo_features_node_info() {
  $items = array(
    'shortcut' => array(
      'name' => t('Shortcut'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}