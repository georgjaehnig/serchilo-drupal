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
