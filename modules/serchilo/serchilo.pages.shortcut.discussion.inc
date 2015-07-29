<?PHP

/**
 * Return the Shortcut discussion page.
 *
 * @param $node
 *   Node of type shortcut.
 * @return array
 *   Render array containing the page.
 */
function serchilo_page_shortcut_discussion($shortcut) {

  $efq = new EntityFieldQuery;

  $efq = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'discussion')
    ->fieldCondition('field_shortcuts_affected', 'target_id',  $shortcut->nid)
    ;

  $result = $efq->execute();

  if (!empty($result)) {

    $nids = array_keys($result['node']);

    $header = array('Title', 'Replies');
    $rows = array();

    foreach ($nids as $nid) {
      $discussion = node_load($nid);
      $rows[] = array(
        l(
          $discussion->title,
          'node/' . $discussion->nid
        ),
        $discussion->comment_count
      );
    }

    // Depending on the context there may be a better choice than this
    $output['discussions'] = array(
      '#theme' => 'table', 
      '#header' => $header, 
      '#rows' => $rows,
      '#caption' => t(
        'Forum discussions about %shortcut_title', 
        array('%shortcut_title' => $shortcut->title)
      ),
    );
  }

  $output['add_discussion'] = array(
    '#theme' => 'link', 
    '#text' => t('Add new discussion'),
    '#path' =>  'node/add/discussion',
    '#attributes' =>  array(),
    '#options' => array(
      'attributes' => array(
        'class' => array(
          'btn', 
          'btn-default', 
        )
      ),
      'html' => FALSE,
      'query' => array(
        'shortcut_affected' => $shortcut->nid, 
      )
    ),
  );

  return $output;
}

