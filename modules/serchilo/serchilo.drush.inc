<?PHP

function serchilo_drush_command() {
  $items = array();

  $items['import-shortcuts'] = array(
    'aliases' => array('isc'), 
    'arguments' => array(
      'file' => 'Full path to the Serchilo JSON file with shortcuts. ',
    ),
  );

  return $items;
}

function drush_serchilo_import_shortcuts($file = NULL) {

  if (!file_exists($file)) {
    return 'Could not find file ' . $file;
  }

  $data_json = file_get_contents($file);
  $data = drupal_json_decode($data_json);

  if ($data === NULL) {
    return 'Could not parse file ' . $file;
  }

  $rows = $data['namespaces']; 
  $vocabularies = taxonomy_vocabulary_get_names();
  foreach ($rows as $row) {

    $namespace         = new StdClass;
    $namespace->vid    = (int) $vocabularies['namespace_types']->vid;
    $namespace->format = 'plain_text';

    foreach (array_keys($row) as $key) {
      switch ($key) {
      case 'type':
        $namespace_type = serchilo_taxonomy_ensure_term($row[$key], 'namespace_types');
        $namespace->field_namespace_type[LANGUAGE_NONE][0]['tid'] = $namespace_type->tid;
        break;
      case 'name':
      case 'description':
        $namespace->{$key} = $row[$key];
        break;
      }
    }
    taxonomy_term_save($namespace);
  }

  $rows = $data['shortcuts']; 
  $rows = array_slice($rows, 0, 1);
  foreach ($rows as $row) {
    $namespace = serchilo_taxonomy_ensure_term($row['namespace'], 'namespaces');
    $shortcut = new StdClass;
    $shortcut->type = 'shortcut';
    $shortcut->uid = 1;
    $shortcut->status = 1;
    $shortcut->revision_moderation = FALSE;
    $shortcut->title = $row['title'];
    drupal_array_set_nested_value($shortcut->field_keyword,        array( LANGUAGE_NONE, 0, 'value'), $row['keyword']);
    drupal_array_set_nested_value($shortcut->field_argument_names, array( LANGUAGE_NONE, 0, 'value'), $row['argument_names']);
    drupal_array_set_nested_value($shortcut->field_argument_count, array( LANGUAGE_NONE, 0, 'value'), count(explode(',', $row['argument_names'])));
    drupal_array_set_nested_value($shortcut->field_url,            array( LANGUAGE_NONE, 0, 'value'), $row['url']);
    drupal_array_set_nested_value($shortcut->field_weight,         array( LANGUAGE_NONE, 0, 'value'), $row['weight']);
    drupal_array_set_nested_value($shortcut->field_invisible,      array( LANGUAGE_NONE, 0, 'value'), $row['invisible']);
    drupal_array_set_nested_value($shortcut->field_set_referrer,   array( LANGUAGE_NONE, 0, 'value'), $row['set_referrer']);
    drupal_array_set_nested_value($shortcut->field_namespace,      array( LANGUAGE_NONE, 0, 'tid'),   $namespace->tid);
    for ($i=0; $i<count($row['tags']); $i++) {
      #print_r( $row['tags'][$i]);
      $tag = serchilo_taxonomy_ensure_term($row['tags'][$i], 'tags');
      drupal_array_set_nested_value($shortcut->field_tags, array( LANGUAGE_NONE, $i, 'tid'), $tag->tid);
    }
    for ($i=0; $i<count($row['examples']); $i++) {
      $field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_example'));
      $field_collection_item->setHostEntity('node', $shortcut);
      $field_collection_item->field_example_arguments[LANGUAGE_NONE][]['value'] = $row['examples'][$i][0];
      $field_collection_item->field_example_description[LANGUAGE_NONE][]['value'] = $row['examples'][$i][1];
      $field_collection_item->save();
    }
    node_save($shortcut);
  }
}
