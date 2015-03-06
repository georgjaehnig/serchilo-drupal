<?PHP

/**
 * Import Serchilo data from a file.
 *
 * @param string $file
 *   The file name to import from.
 * @param bool $verbose
 *   (optional) TRUE if shall run in verbose mode.
 *
 * @return void
 */
function serchilo_import($file = NULL, $verbose = FALSE) {

  if ($verbose) {
    echo "Importing data:\n";
  }

  if (!file_exists($file)) {
    return 'Could not find file ' . $file;
  }

  $data_json = file_get_contents($file);
  $data = drupal_json_decode($data_json);

  if ($data === NULL) {
    return 'Could not parse file ' . $file;
  }

  serchilo_import_namespaces($data['namespaces'], $verbose);
  serchilo_import_shortcuts( $data['shortcuts'],  $verbose);
}

/**
 * Import Serchilo data from a file.
 *
 * @param array $rows
 *   Array of namespaces, as exported.
 * @param bool $verbose
 *   (optional) TRUE if shall run in verbose mode.
 *
 * @return void
 */
function serchilo_import_namespaces($rows, $verbose = FALSE) {

  if ($verbose) {
    echo "Importing namespaces...\n";
  }

  foreach ($rows as $row) {

    $term = array();
    $term['description'] = $row['description'];

    $namespace_type = serchilo_taxonomy_ensure_term($row['type'], 'namespace_types');
    $term['field_namespace_type'][LANGUAGE_NONE][0] = (array) $namespace_type;

    serchilo_taxonomy_ensure_term($row['name'], 'namespaces', $term);

    if ($verbose) {
      echo '.';
    }
  }

  if ($verbose) {
    echo "\n";
  }
}

/**
 * Import Serchilo data from a file.
 *
 * @param array $rows
 *   Array of shortcuts, as exported.
 * @param bool $verbose
 *   (optional) TRUE if shall run in verbose mode.
 *
 * @return void
 */
function serchilo_import_shortcuts($rows, $verbose = FALSE) {

  //for debug: try to import only 1
  //$rows = array_slice($rows, 0, 1);

  if ($verbose) {
    echo "Importing shortcuts...\n";
  }

  foreach ($rows as $row) {
    $namespace = serchilo_taxonomy_ensure_term($row['namespace'], 'namespaces');
    $shortcut = new StdClass;
    $shortcut->type = 'shortcut';

    // If there exist a user with the name of the namespace:
    if (strlen($namespace->name) >= 4) {
      if ($account = user_load_by_name($namespace->name)) {
        // Make this user the owner of the shortcut.
        $shortcut->uid = $account->uid;
      }
    }

    $shortcut->status = NODE_PUBLISHED;
    $shortcut->comment = 0;
    $shortcut->uid = 1;
    $shortcut->language = LANGUAGE_NONE;
    $shortcut->title = $row['title'];
    drupal_array_set_nested_value($shortcut->field_keyword,        array( LANGUAGE_NONE, 0, 'value'), $row['keyword']);
    drupal_array_set_nested_value($shortcut->field_description,    array( LANGUAGE_NONE, 0, 'value'), $row['description']);
    drupal_array_set_nested_value($shortcut->field_url,            array( LANGUAGE_NONE, 0, 'value'), $row['url']);
    drupal_array_set_nested_value($shortcut->field_weight,         array( LANGUAGE_NONE, 0, 'value'), $row['weight']);
    drupal_array_set_nested_value($shortcut->field_invisible,      array( LANGUAGE_NONE, 0, 'value'), $row['invisible']);
    drupal_array_set_nested_value($shortcut->field_set_referrer,   array( LANGUAGE_NONE, 0, 'value'), $row['set_referrer']);
    drupal_array_set_nested_value($shortcut->field_command_id,     array( LANGUAGE_NONE, 0, 'value'), $row['id']);
    drupal_array_set_nested_value($shortcut->field_input_encoding, array( LANGUAGE_NONE, 0, 'value'), $row['input_encoding']);
    drupal_array_set_nested_value($shortcut->field_namespace,      array( LANGUAGE_NONE, 0 ), (array) $namespace);

    // Set all shortcuts to approved.
    drupal_array_set_nested_value($shortcut->field_approved, array( LANGUAGE_NONE, 0, 'value'), 1);

    // Set argument names & count from URL.
    serchilo_set_shortcut_arguments_data($shortcut);

    for ($i=0; $i<count($row['tags']); $i++) {
      #print_r( $row['tags'][$i]);
      $tag = serchilo_taxonomy_ensure_term($row['tags'][$i], 'tags');
      drupal_array_set_nested_value($shortcut->field_tags, array( LANGUAGE_NONE, $i), (array) $tag);
    }
    for ($i=0; $i<count($row['examples']); $i++) {
      $field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_example'));
      $field_collection_item->setHostEntity('node', $shortcut);
      $field_collection_item->field_example_arguments[LANGUAGE_NONE][]['value'] = $row['examples'][$i][0];
      $field_collection_item->field_example_description[LANGUAGE_NONE][]['value'] = $row['examples'][$i][1];
      $field_collection_item->save();
    }
    node_save($shortcut);

    if ($verbose) {
      echo '.';
    }
  }

  if ($verbose) {
    echo "\n";
  }
}

