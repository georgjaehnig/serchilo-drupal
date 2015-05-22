<?php

/**
 * @file
 * template.php
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function bootstrap_serchilo_preprocess_button(&$vars) {
  
  switch ($vars['element']['#button_type']) {
  // Make Go button a primary button.
  // Make Apply button a primary button.
  case 'submit':
    $vars['element']['#attributes']['class'][] = 'btn-primary';
    break; 
  }
  switch ($vars['element']['#id']) {
  case 'edit-reset':
    // Make Reset button a warning button.
    $vars['element']['#attributes']['class'][] = 'btn-warning';
    break; 
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function bootstrap_serchilo_preprocess_node(&$variables) {

  // Buttonize 'Add new comment' link.
  if (!isset($variables['content']['links']['comment']['#links']['comment-add'])) {
    return; 
  }

  $variables['content']['links']['comment']['#links']['comment-add']['attributes']['class'][] = 'btn';
  $variables['content']['links']['comment']['#links']['comment-add']['attributes']['class'][] = 'btn-default';
}
