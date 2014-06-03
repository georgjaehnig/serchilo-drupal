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
