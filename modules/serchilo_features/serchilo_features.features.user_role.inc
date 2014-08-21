<?php
/**
 * @file
 * serchilo_features.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function serchilo_features_user_default_roles() {
  $roles = array();

  // Exported role: moderator.
  $roles['moderator'] = array(
    'name' => 'moderator',
    'weight' => 2,
  );

  return $roles;
}
