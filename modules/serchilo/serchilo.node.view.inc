<?PHP

/**
 * Builds a form for calling a shortcut.
 *
 * @param array $form
 * @param array $form_state
 *   Standard form hook arguments.
 *
 * @param object $node
 *   The node of type shortcut
 *   to build the from.
 *
 * @return array $form
 *   The built form.
 */
function serchilo_shortcut_call_form($form, $form_state, $node) {

  $form = array();

  $form['#attributes']['class'] = array('form-inline'); 
  $form['#attributes']['role'] = 'form'; 

  $form['keyword'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => 
      #render($node->field_namespace ) .
      #$namespace_html .
      #'.' .
      $node->field_keyword[LANGUAGE_NONE][0]['value'],
    '#attributes' => array(
      'class' => array('keyword', 'form-group'), 
    ),
  );

  $form['arguments']['#tree'] = true;

  if (!empty($node->field_argument_names[LANGUAGE_NONE][0]['value'])) {
    $argument_names = explode(',', $node->field_argument_names[LANGUAGE_NONE][0]['value']);
  }
  else {
    $argument_names = array();
  }
  for ($i=0; $i<count($argument_names); $i++) {
    $argument_name = $argument_names[$i];

    #$argument_example = (array_key_exists($i, $argument_examples) ? $argument_examples[$i] : '');
    $form['arguments'][$i] = array(
      '#type' => 'textfield',
      '#required' => true,
      '#size' => 0,
      '#attributes' => array(
        'placeholder' => $argument_name,
      ), 
    );
  }

  $form['node'] = array(
    '#type' => 'value',
    '#value' => $node,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
  );

  // Set focus on first input field
  // or on submit.
  if (isset($form['arguments'][0])) {
    $form['arguments'][0]['#attributes']['autofocus'] = NULL;
  }
  else {
    $form['submit']['#attributes']['autofocus'] = NULL;
  }

  // TODO: This should rather be in the theme,
  // but weirdly, in hook_preprocess_form() it is too late
  // for the JS to get recognized and attached.
  $form['#attached']['js'][] = drupal_get_path('module', 'serchilo') . '/js/shortcut-call-form.js';

  return $form;
}

/**
 * Implements hook_FORM_ID_form_submit().
 *
 * Builds a query out of the shortcut form arguments
 * and redirects it to the query handler.
 *
 * @param array $form
 * @param array $form_state
 *   Standard form hook arguments.
 *
 * @return void
 */
function serchilo_shortcut_call_form_submit($form, &$form_state) {

  if (user_is_logged_in()) {
    // Logged users call their user path.
    global $user; 
    $path = 'u/' . $user->name;
  } else {
    // Anonymous user get the default language and country namespace.
    $path = 'n/' .
      serchilo_get_default_language_namespace()->name .
      '.' .
      serchilo_get_default_country_namespace()->name .
      '';
  }
  $url = url(
    $path,
    array(
      'query' => array(
        'query' => 
        // Force namespace of current shortcut
        $form_state['values']['node']->field_namespace[LANGUAGE_NONE][0]['taxonomy_term']->name .
        '.' . 
        // Prepend keyword
        $form_state['values']['node']->field_keyword[LANGUAGE_NONE][0]['value'] .
        ' ' .
        // Add submitted arguments
        join(',', drupal_array_get_nested_value($form_state, array('values','arguments')) ?: array())
        
      ) 
    ) 
  );
  global $base_url;
  $url = $base_url . $url;
  drupal_goto($url);
}

