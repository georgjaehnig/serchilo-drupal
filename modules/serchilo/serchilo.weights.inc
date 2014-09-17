<?PHP

/**
 * Calculate shortcut weights.
 *
 * @return void
 */
function serchilo_calculate_shortcut_weights() {

  $after = time() - (7*24*60*60); # within last week
  $after = time() - (7*24*60*60*30); # within last 30 days

  $namespace_calls = 
    db_query('
      SELECT 
        *, 
        COUNT(*) AS count
      FROM 
        serchilo_shortcut_log
      WHERE
        called > :after AND
        namespace_id > 0
      GROUP BY 
        namespace_id;
      ',
      array(
        ':after' => $after,
      ) 
    )
    ->fetchAllAssoc('namespace_id');

  $shortcut_calls = 
    db_query('
      SELECT 
        *, 
        COUNT(*) AS count
      FROM 
        serchilo_shortcut_log
      WHERE
        called > :after AND
        shortcut_id > 0
      GROUP BY 
        shortcut_id, namespace_id;
      ',
      array(
        ':after' => $after,
      ) 
    )
    ->fetchAllAssoc('shortcut_id');
    #->fetchAll();

  foreach ($shortcut_calls as $shortcut_call) {

    // Only if shortcut still exists
    if ($shortcut = node_load($shortcut_call->shortcut_id)) {

      // Only if namespace_id matches current namespace.
      if ($shortcut->field_namespace[LANGUAGE_NONE][0]['tid'] == $shortcut_call->namespace_id) {

        $namespace_count = $namespace_calls[$shortcut_call->namespace_id]->count;

        if ( $namespace_count > 0 ) {
          $weight = $shortcut_call->count / $namespace_count;
        } 
        else {
          $weight = 0;
        }

        $shortcut->field_weight[LANGUAGE_NONE][0]['value'] = $weight;

        node_save($shortcut);
      }
    }
  }

}
