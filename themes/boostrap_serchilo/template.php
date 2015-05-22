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

  // Buttonize links.

  if (isset($variables['content']['links']['node']['#links']['node-readmore'])) {
    $variables['content']['links']['node']['#links']['node-readmore']['attributes']['class'][] = 'btn';
    $variables['content']['links']['node']['#links']['node-readmore']['attributes']['class'][] = 'btn-default';
  }

  if (isset($variables['content']['links']['comment']['#links']['comment-add'])) {
    $variables['content']['links']['comment']['#links']['comment-add']['attributes']['class'][] = 'btn';
    $variables['content']['links']['comment']['#links']['comment-add']['attributes']['class'][] = 'btn-default';
  }

}
