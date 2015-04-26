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

  // Argument could be prefixed with country.
  $argument_with_prefix = explode('.', $argument, 2);
  if (count($argument_with_prefix) > 1) {
    $prefix = array_shift($argument_with_prefix);
    // Prefix can be either
    // 2-letter country code (e.g. 'de') or
    // 3-letter country code (e.g. 'deu').
    switch (strlen($prefix)) {
      case 2:
        require_once(dirname(__FILE__) . '/serchilo.countries.inc');
        $country_alpha3 = serchilo_country_alpha2_to_alpha3($prefix);
        break;
      case 3:
        $country_alpha3 = $prefix;
        break;
    } 
    $mapping = serchilo_load_mapping(dirname(__FILE__) . '/../mappings/cities/' . $country_alpha3 . '.tsv');
    $argument = array_shift($argument_with_prefix);
  }
  // If did not succeed to load a mapping yet:
  // Pick one by namespaces
  // - first via extra_namespace_name
  // - then via country_namespace_name.
  if (empty($mapping)) {
    $mapping = 
      // Try first via extra namespace ...
      serchilo_load_mapping(dirname(__FILE__) . '/../mappings/cities/' . $env['extra_namespace_name'] . '.tsv') ?:
      // ... then via country namespace.
      serchilo_load_mapping(dirname(__FILE__) . '/../mappings/cities/' . $env['country_namespace_name'] . '.tsv');
  }

  return serchilo_array_value($mapping, $argument, NULL);

}

