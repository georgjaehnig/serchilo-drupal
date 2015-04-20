<?PHP

/**
 * Parse an argument of type date.
 *
 * @param string $argument
 *   The string containing a date.
 *   
 * @return DateTime $date
 *   The parsed DateTime object.
 *   NULL if parse failed. 
 */
function serchilo_parse_date($argument) {

  // Match '22' and '22.'
  if (preg_match('/^(\d+)(\.)?$/', $argument, $matches)) {
    $date = DateTime::createFromFormat('d', $matches[1]);
    // If date in past: set it to next month.
    if ($date < new \DateTime('now')) {
      $date->modify('+1 month');
    }
  }

  // Match '22.11' and '22.11.'
  if (preg_match('/^(\d+)\.(\d+)(\.)?$/', $argument, $matches)) {
    $date = DateTime::createFromFormat('d m', $matches[1] . ' ' . $matches[2]);
    // If date in past: set it to next year.
    if ($date < new \DateTime('now')) {
      $date->modify('+1 year');
    }
  }

  // Match '22.11.13'
  if (preg_match('/^(\d+)\.(\d+)\.(\d{2})$/', $argument, $matches)) {
    $date = DateTime::createFromFormat('d m y', $matches[1] . ' ' . $matches[2] . ' ' . $matches[3]);
  }

  // Match '22.11.2013'
  if (preg_match('/^(\d+)\.(\d+)\.(\d{4})$/', $argument, $matches)) {
    $date = DateTime::createFromFormat('d m Y', $matches[1] . ' ' . $matches[2] . ' ' . $matches[3]);
  }

  // Match '11/22'
  if (preg_match('/^(\d+)\/(\d+)$/', $argument, $matches)) {
    $date = DateTime::createFromFormat('m d', $matches[1] . ' ' . $matches[2]);
    // If date in past: set it to next year.
    if ($date < new \DateTime('now')) {
      $date->modify('+1 year');
    }
  }

  // Match '11/22/13'
  if (preg_match('/^(\d+)\/(\d+)\/(\d{2})$/', $argument, $matches)) {
    $date = DateTime::createFromFormat('m d y', $matches[1] . ' ' . $matches[2] . ' ' . $matches[3]);
  }

  // Match '11/22/2013'
  if (preg_match('/^(\d+)\/(\d+)\/(\d{4})$/', $argument, $matches)) {
    $date = DateTime::createFromFormat('m d Y', $matches[1] . ' ' . $matches[2] . ' ' . $matches[3]);
  }

  // Match '+1' or '-2'
  if (preg_match('/^(-|\+)(\d+)$/', $argument, $matches)) {
    // Treat as days in future or past.
    $date = new \DateTime($matches[0] . ' days');
  }

  return $date;
}

