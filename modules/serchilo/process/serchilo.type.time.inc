<?PHP

/**
 * Parse an argument of type time.
 *
 * @param string $argument
 *   The string containing a time.
 *   
 * @return DateTime $time
 *   The parsed DateTime object.
 *   NULL if parse failed. 
 */
function serchilo_parse_time($argument) {

  // Match '11'
  if (preg_match('/^(\d+)$/', $argument, $matches)) {
    $time = DateTime::createFromFormat('H', $matches[1]);
  }

  // Match '11:23' and '11.23'
  if (preg_match('/^(\d+)(\.|:)(\d+)$/', $argument, $matches)) {
    $time = DateTime::createFromFormat('H.i', $matches[1] . '.' . $matches[2]);
  }

  // Match '+1' and '-2'
  if (preg_match('/^(-|\+)(\d+)$/', $argument, $matches)) {
    $time = new \DateTime($matches[0] . ' hours');
  }

  return $time;
}

