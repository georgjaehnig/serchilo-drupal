<?PHP

/**
 * Render a field collection revision.
 *   (as https://www.drupal.org/node/1595702 remains unsolved.)
 *
 * @param array $field_collection 
 *   The field collection to render.
 * @param array $field_collection_field_names 
 *   The fields within the field collection to render.
 * @param string $template 
 *   The template to render the fields. 
 *   Should contain placeholders like [field_name].
 *
 * @return array $rendered_items 
 *   The rendered items.
 */
function serchilo_render_field_collection_revision($field_collection, $field_collection_field_names, $template) {

  if (empty($field_collection)) {
    return array(); 
  }

  $rendered_items = array();
  foreach ($field_collection[LANGUAGE_NONE] as $item) {
    $fcitem = field_collection_item_revision_load($item['revision_id']);

    // Do nothing if field collection item could not be loaded.
    if (empty($fcitem)) {
      continue; 
    }
    // Do nothing if field collection fields are empty.
    foreach($field_collection_field_names as $field_collection_field_name) {
      if (empty($fcitem->{$field_collection_field_name})) {
        continue 2;
      }
    }

    // Take template as the render item base.
    $render_item = $template;
    foreach($field_collection_field_names as $field_collection_field_name) {
      // Replace placeholder in template with field value.
      // (Assumes fields with only 1 value.)
      $render_item = str_replace(
        '['. $field_collection_field_name . ']', 
        $fcitem->{$field_collection_field_name}[LANGUAGE_NONE][0]['value'],
        $render_item
      );
    }
    $rendered_items[] = $render_item;
  }
  return $rendered_items;
}

