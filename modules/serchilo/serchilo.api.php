<?php

/**
 * @file
 * Hooks provided by the serchilo module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allow modules to alter the console examples.
 *
 * @param array $shortcut_ids
 *   The current draft of shortcut ids to show as examples.
 * @param array $context
 *   An array with context information, currently containing:
 *   - namespace_ids: Array with the IDs of the current namespaces.
 */
function hook_serchilo_console_examples_alter(&$shortcut_ids, $context) {

  // Completely overwrite the current draft
  // and set shortcuts with the IDs 1 and 2 as examples.
  $shortcut_ids = array(1,2);
}

/**
 * @} End of "addtogroup hooks".
 */
