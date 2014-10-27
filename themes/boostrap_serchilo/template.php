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

    // Put a well around namespaces block.
    $vars['classes_array'][] = 'well';
    $vars['classes_array'][] = 'well-sm';

    break;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function bootstrap_serchilo_preprocess_button(&$vars) {
  
  switch ($vars['element']['#id']) {
  case 'edit-submit-shortcuts':
    // Make Go button a primary button.
    $vars['element']['#attributes']['class'][] = 'btn-primary';
    break; 
  case 'edit-reset':
    // Make Reset button a warning button.
    $vars['element']['#attributes']['class'][] = 'btn-warning';
    break; 
  }
}


