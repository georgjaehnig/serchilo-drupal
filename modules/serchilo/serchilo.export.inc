<?PHP

/**
 * Exports shortcuts and namespaces to the files directory.
 * Creates directories if necessary.
 *
 * @return void
 */
function serchilo_export() {
  system('mkdir -p sites/default/files/serchilo/export');
  serchilo_export_to_json_gz_file('sites/default/files/serchilo/export/serchilo');
}

/**
 * Exports shortcuts and namespaces to a .json.gz file.
 *
 * @param string file_without_suffix
 *   Path to the file, without its suffix, e.g.
 *     /path/to/file
 *   will create
 *     /path/to/file.json.gz
 *
 * @return void
 */
function serchilo_export_to_json_gz_file($file_without_suffix) {

  $export = serchilo_export_shortcuts_and_namespaces();
  $export_json = drupal_json_encode($export);

  file_put_contents($file_without_suffix . '.json', $export_json);
  system('gzip -f ' . $file_without_suffix . '.json');
}

/**
 * Exports the shortcuts and the namespaces.
 *
 * @return array $export
 *   Two-item array containing the 
 *   - shortcuts and the
 *   - namespaces 
 */
function serchilo_export_shortcuts_and_namespaces() {

  $export['shortcuts']  = serchilo_export_shortcuts();
  $export['namespaces'] = serchilo_export_namespaces();

  return $export;
}

/**
 * Exports the shortcuts.
 *
 * @return array $exported_namespaces 
 *   Array containing namespaces with
 *   - id
 *   - title
 *   - description
 *   - url
 *   - keyword
 *   - argument_names (array)
 *   - set_referrer
 *   - invisible
 *   - namespace
 *   - tags (array)
 *   - examples, array of two-item array containing
 *     - arguments (as string separated by comma)
 *     - description
 */
function serchilo_export_shortcuts() {

  $efq = new EntityFieldQuery;

  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->execute();

  $nids = array_keys(array_shift($result));

  $exported_shortcuts = array();

  foreach ($nids as $nid) {

    $node = node_load($nid);

    $namespace = taxonomy_term_load($node->field_namespace[LANGUAGE_NONE][0]['tid']);

    $exported_shortcut['id']             = $node->nid;
    $exported_shortcut['title']          = $node->title;
    $exported_shortcut['description']    = (string) drupal_array_get_nested_value($node->field_description,    array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['url']            = (string) drupal_array_get_nested_value($node->field_url,            array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['keyword']        = (string) drupal_array_get_nested_value($node->field_keyword,        array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['argument_names'] = (string) drupal_array_get_nested_value($node->field_argument_names, array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['set_referrer']   = (string) drupal_array_get_nested_value($node->field_set_referrer,   array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['invisible']      = (string) drupal_array_get_nested_value($node->field_invisible,      array(LANGUAGE_NONE, 0, 'value'));

    $wnode = entity_metadata_wrapper('node', $node);

    $exported_shortcut['namespace']      = $wnode->field_namespace->value()->name;
    $exported_shortcut['tags']           = array_map(function ($tag) { return $tag->name; }, $wnode->field_tags->value() ?: array() );

    $exported_shortcut['examples']       = array();

    foreach ($wnode->field_example as $example) {
      $shortcut['examples'][] = array(
        $example->field_example_arguments->value(),
        $example->field_example_description->value() 
      );
    }

    $exported_shortcuts[] = $exported_shortcut;
  }

  return $exported_shortcuts;
}

/**
 * Exports the namespaces.
 *
 * @return array $exported_namespaces 
 *   Array containing namespaces with
 *   * title
 *   * description
 *   * (namespace) type
 */
function serchilo_export_namespaces() {

  $vocabularies = taxonomy_vocabulary_get_names();

  $efq = new EntityFieldQuery;
  $result = $efq
    ->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', $vocabularies['namespaces']->vid )
    ->execute();

  $namespace_ids = array_keys(array_shift($result));
  $exported_namespaces = array();

  foreach ($namespace_ids as $namespace_id) {

    $term = taxonomy_term_load($namespace_id);
    $wterm = entity_metadata_wrapper('taxonomy_term', $term);

    $exported_namespace['tid']        = $wterm->tid->value();
    $exported_namespace['name']        = $wterm->name->value();
    $exported_namespace['description'] = $wterm->description->raw();
    $exported_namespace['type']        = $wterm->field_namespace_type->value()->name;

    $exported_namespaces[] = $exported_namespace;
  }

  return $exported_namespaces;
}
