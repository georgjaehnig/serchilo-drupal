<?PHP

/**
 * Redirect to a shortcut node edit page.
 *  If shortcut not found: Redirect to Shortcuts view.
 *
 * @return mixed
 *   A page callback return.
 */
function serchilo_redirect_edit_shortcuts() {

  // Validate GET params. Expecting
  // - keyword
  // - namespace
  // - argument_count (optional, default: 0)
  if (empty($_GET['keyword'])) {
    drupal_set_message(
      t(
        "Please provide a keyword in the URL, for instance '&keyword=g'"
      ),
      'error'
    );
    return '';
  }
  if (empty($_GET['namespace'])) {
    drupal_set_message(
      t(
        "Please provide a namespace in the URL, for instance '&namespace=o'"
      ),
      'error'
    );
    return '';
  }

  $namespace_name = (string) $_GET['namespace'];
  $namespace_id   = key(taxonomy_get_term_by_name($namespace_name, 'namespaces'));

  if (empty($namespace_id)) {
    drupal_set_message(
      t(
        "No namespace found with the name '@namespace_name'.",
        array(
          '@namespace_name' => $namespace_name, 
        )
      ),
      'error'
    );
    return ''; 
  }

  // Validation done.

  // Now search for the shortcut.

  $keyword        = (string) $_GET['keyword'];

  $efq = new EntityFieldQuery;

  $efq = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->fieldCondition('field_keyword',        'value',  $keyword)
    ->fieldCondition('field_namespace',      'tid',    $namespace_id)
    ->fieldCondition('field_active',         'value',  TRUE )
  ;

  // If no argument_count provided
  // Search for the shortcut with the lowest argument count.
  if (!isset($_GET['argument_count'])) {
    $efq 
      ->fieldCondition('field_argument_count', 'value', 0, '>=')
      ->fieldOrderBy('field_argument_count', 'value')
    ;
  }
  else {
    $argument_count = $_GET['argument_count'];
    $efq 
      ->fieldCondition('field_argument_count', 'value', $argument_count)
    ;
  }

  $result = $efq->execute();

  // If nothing found: 
  // Redirect to Shortcuts view.
  if (empty($result)) {
    drupal_set_message(
      t(
        "No shortcut found with the keyword '@keyword' and '@argument_count' argument(s) in the namespace '@namespace'.", 
        array(
          '@keyword'        => $keyword,
          '@argument_count' => $argument_count,
          '@namespace'      => $namespace_name,
        )
      ),
      'error'
    );
    drupal_goto(
      'shortcuts',
      array(
        'query' => array(
          'keyword'        => $keyword,
          'argument_count' => $argument_count,
          'namespace'      => $namespace_name,
        )
      )
    ); 
    return;
  }

  // If found:
  // Redirect to node edit.
  $nid = array_shift(array_keys($result['node']));
  drupal_goto('node/' . $nid . '/edit');

}
