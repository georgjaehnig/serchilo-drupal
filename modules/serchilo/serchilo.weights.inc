<?PHP

/**
 * Calculate shortcut calls. Set the corresponding node fields.
 *
 * @return void
 */
function serchilo_calculate_shortcut_calls() {

  // Within last 30 days
  $shortcut_calls_last_30_days = serchilo_fetch_shortcut_calls(time() - (7*24*60*60*30));
  foreach ($shortcut_calls_last_30_days as $shortcut_call) {
    // Only if shortcut still exists
    if ($shortcut = node_load($shortcut_call->shortcut_id)) {
      $shortcut->field_calls_last_30_days[LANGUAGE_NONE][0]['value'] = $shortcut_call->count;
      $shortcut->revision_operation = REVISIONING_NO_REVISION;
      node_save($shortcut);
    }
  }

  // Total
  $shortcut_calls_total = serchilo_fetch_shortcut_calls(0);
  foreach ($shortcut_calls_total as $shortcut_call) {
    // Only if shortcut still exists
    if ($shortcut = node_load($shortcut_call->shortcut_id)) {
      $shortcut->field_calls_total[LANGUAGE_NONE][0]['value'] = $shortcut_call->count;
      $shortcut->revision_operation = REVISIONING_NO_REVISION;
      node_save($shortcut);
    }
  }
}

/**
 * Fetch shortcut calls.
 *
 * @param int $after_timestamp
 *   The UNIX timestamp after which calls shall be counted.
 *
 * @return array $shortcut_calls
 *   Array of SQL results.
 */
function serchilo_fetch_shortcut_calls($after_timestamp) {

  $shortcut_calls = 
    db_query('
      SELECT 
        *, 
        COUNT(*) AS count
      FROM 
        serchilo_shortcut_log
      WHERE
        called > :after_timestamp AND
        shortcut_id > 0
      GROUP BY 
        shortcut_id, namespace_id;
      ',
      array(
        ':after_timestamp' => $after_timestamp,
      ) 
    )
    ->fetchAllAssoc('shortcut_id');
  return $shortcut_calls;
}

/**
 * Calculate shortcut weights.
 *
 * A shortcut weight is
 *   number of calls / all calls
 *   during the last 30 days.
 *
 * @return void
 */
function serchilo_calculate_shortcut_weights() {

  // Within last 30 days.
  $after_timestamp = time() - (7*24*60*60*30); 

  $calls_last_30_days = 
    db_query('
      SELECT 
        COUNT(*) AS count
      FROM 
        serchilo_shortcut_log
      WHERE
        called > :after_timestamp AND
        namespace_id > 0
      ',
      array(
        ':after_timestamp' => $after_timestamp,
      ) 
    )
    ->fetchAll();

  $shortcut_calls = 
    db_query('
      SELECT 
        *, 
        COUNT(*) AS count
      FROM 
        serchilo_shortcut_log
      WHERE
        called > :after_timestamp AND
        shortcut_id > 0
      GROUP BY 
        shortcut_id;
      ',
      array(
        ':after_timestamp' => $after_timestamp,
      ) 
    )
    ->fetchAllAssoc('shortcut_id');
    #->fetchAll();

  foreach ($shortcut_calls as $shortcut_call) {

    // Only if shortcut still exists
    if ($shortcut = node_load($shortcut_call->shortcut_id)) {

      // Only if namespace_id matches current namespace.
      if ($shortcut->field_namespace[LANGUAGE_NONE][0]['tid'] == $shortcut_call->namespace_id) {

        $shortcut->field_weight[LANGUAGE_NONE][0]['value'] = 
          $shortcut_call->count / $calls_last_30_days[0]->count;

        $shortcut->revision_operation = REVISIONING_NO_REVISION;
        node_save($shortcut);
      }
    }
  }

}
