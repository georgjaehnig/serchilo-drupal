<?PHP

/**
 * Creates an options list of namespaces of a given namespace_type.
 *
 * @param string $namespace_type
 *   The namespace type, e.g. 'language' or 'country'.
 *
 * @return array $options
 *   The generated options list.
 */
function serchilo_options_list_namespace_by_type($namespace_type) {

  $namespace_type_id = key(taxonomy_get_term_by_name($namespace_type, 'namespace_types'));

  $efq = new EntityFieldQuery;

  $result = $efq
    ->entityCondition('entity_type', 'taxonomy_term')
    ->fieldCondition('field_namespace_type', 'tid',  $namespace_type_id)
    ->propertyOrderBy('description')
    ->execute();

  $namespace_ids = array_keys(array_shift($result));
  $namespaces = taxonomy_term_load_multiple($namespace_ids);

  $options = array();
  foreach ($namespaces as $namespace) {
    $options[$namespace->tid] = $namespace->description . ' (' . $namespace->name . ')';
  }
  return $options;
}
