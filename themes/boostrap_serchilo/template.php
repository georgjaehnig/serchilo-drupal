<?php

/**
 * @file
 * template.php
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function bootstrap_serchilo_preprocess_block(&$vars) {
  
  switch ($vars['block_html_id']) {
  case 'block-serchilo-namespaces':
    $vars['classes_array'][] = 'well';
    $vars['classes_array'][] = 'well-sm';
    break;
  }
}
/**
 * Implements hook_preprocess_HOOK().
 */
function bootstrap_serchilo_preprocess_button(&$vars) {
  
  switch ($vars['element']['#type']) {

  case 'submit':

    // Make Go button a primary button.
    $vars['element']['#attributes']['class'][] = 'btn-primary';

    break; 
  }
}

