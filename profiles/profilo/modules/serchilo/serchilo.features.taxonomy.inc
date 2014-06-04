<?php
/**
 * @file
 * serchilo.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function serchilo_taxonomy_default_vocabularies() {
  return array(
    'command_tags' => array(
      'name' => 'Command tags',
      'machine_name' => 'command_tags',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'namespace_types' => array(
      'name' => 'Namespace types',
      'machine_name' => 'namespace_types',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'namespaces' => array(
      'name' => 'Namespaces',
      'machine_name' => 'namespaces',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'tags' => array(
      'name' => 'Tags',
      'machine_name' => 'tags',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
