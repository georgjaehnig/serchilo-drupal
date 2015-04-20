<?PHP

/**
 * Parse an argument of type city.
 *
 * @param string $argument
 *   The string containing a city abbreviation.
 *   
 * @return string $city
 *   The parsed city name as string.
 *   NULL if parse failed. 
 */
function serchilo_parse_city($argument, $env) {

  $mapping = 
    // Try first via extra namespace ...
    serchilo_load_mapping(dirname(__FILE__) . '/../mappings/cities/' . $env['extra_namespace_name'] . '.tsv') ?:
    // ... then via country namespace.
    serchilo_load_mapping(dirname(__FILE__) . '/../mappings/cities/' . $env['country_namespace_name'] . '.tsv');

  return serchilo_array_value($mapping, $argument, NULL);

}

/**
 * Load a mapping from file.
 *
 * @param string $filename
 *   The name of the file containing the mapping.
 *   
 * @return array $mapping
 *   The parsed city name as string.
 *   NULL if loading failed. 
 */
function serchilo_load_mapping($filename) {

  if (!file_exists($filename)) {
    return NULL; 
  }
  $lines = file($filename);
  $mapping = array();
  foreach ($lines as $line) {
    $split = explode("\t", $line, 2);
    $split[0] = trim($split[0]);
    $split[1] = trim($split[1]);
    $mapping[$split[0]] = $split[1];
  }
  return $mapping;
}

