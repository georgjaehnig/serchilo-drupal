<?PHP

/**
 * Checks if a view uses filters.
 *
 * @param array $filter
 *   The $view->filter array.
 *
 * @return boolean
 *   True if filters are used.
 */
function serchilo_views_is_filter_used($filters) {

  foreach ($filters as $filter) {
    if (!empty($filter->value)) {
      return TRUE; 
    }
  }
  return FALSE; 
}

