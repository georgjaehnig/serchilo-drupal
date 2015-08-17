<?PHP

/**
 * Constructs shortcut approval confirmation form.
 *
 * @see serchilo_shortcut_sight_form_sight()
 * @see serchilo_shortcut_sight_form_decline()
 */
function serchilo_shortcut_sight_form($form, $form_state, $node) {

  $url = drupal_array_get_nested_value($_GET, array('url'));

  if (empty($url)) {
    drupal_set_message(
      t('No URL provided.'),
      'error'
    );   
    return;
  }

  drupal_session_start();
  $sighted = drupal_array_get_nested_value($_SESSION, array('serchilo', 'sighted', $node->vid));

  // If sighted:
  // redirect there without asking.
  if ($sighted) {
    drupal_goto(
      $url,
      array(
        'absolute' => TRUE, 
      )
    ); 
    return; 
  }

  $form = array();

  $form['url'] = array(
    '#type'  => 'value', 
    '#value' => $url,
  );
  $form['nid'] = array(
    '#type'  => 'value', 
    '#value' => $node->nid,
  );
  $form['vid'] = array(
    '#type'  => 'value', 
    '#value' => $node->vid,
  );

  $url_parsed = parse_url($url);

  $form['message'] = array(
    '#type' => 'markup',
    '#markup' => '

<div class="url panel panel-danger">
  <div class="panel-heading">
' .  t('This Shortcut has been changed and is not yet approved. Please check the URL carefully:') . '
</div>
  <div class="panel-body">' . l($url, $url) .  '</div>
</div>

',

  );

  // TODO:
  // if exists original, offer link of diff to last approved revision.

  $form['actions']['sight'] = array(
    '#type' => 'submit',
    '#value' => 'URL is OK. Go there, do not ask me again.',
    '#submit' => array('serchilo_shortcut_sight_form_submit_sight'),
    '#attributes' => array(
      'class' => array(
        'btn-default' 
      ),
    ),
  );

  $form['actions']['decline'] = array(
    '#type' => 'submit',
    '#value' => 'URL is bad. Go to revisions and let me revert.',
    '#submit' => array('serchilo_shortcut_sight_form_submit_decline'),
  );

  return $form;
}

function serchilo_shortcut_sight_form_submit_sight($form, $form_state) {
  
  $vid = $form_state['values']['vid'];
  $url = $form_state['values']['url'];

  drupal_array_set_nested_value($_SESSION, array('serchilo', 'sighted', $vid), TRUE, TRUE);
  drupal_goto($url);
}

function serchilo_shortcut_sight_form_submit_decline($form, $form_state) {
  
  $nid = $form_state['values']['nid'];

  // Redirect to revisions page.
  drupal_goto('node/' . $nid . '/revisions');
}


