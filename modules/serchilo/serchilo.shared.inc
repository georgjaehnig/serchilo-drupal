<?php

/**
* @file
* Functions shared by the Drupal module and the standalone Process code.
*/

// GENERAL HELPER

/**
 * Return the value of an array given the key.
 * If the key it not set, return a default value.
 *
 * @param array $array
 *    The array to return the value from.
 * @param string $key
 *    The key of the array.
 * @param mixed $default_value
 *    (optional) The default value to return if the key not exists.
 * @return mixed
 *    The returned value.
 */
function serchilo_array_value($array, $key, $default_value = null) {
  if (isset($array[$key])) {
    return $array[$key];
  }
  return $default_value;
}


// PLACEHOLDER EXTRACTORS

/**
 * Get arguments from a string.
 *
 * @param string $str
 *   The string containing placeholders.
 *
 * @return array $arguments
 *   Array keyed with the arguments names and with an array of the attributes as the value. 
 *   An additional attribute '_match' contains the whole match within the URL (for later replacement).
 */
function serchilo_get_arguments_from_string($str) {

  return serchilo_get_placeholders_from_string($str, '%');
}

/**
 * Get variables from a string.
 *
 * @param string $str
 *   The string containing placeholders.
 *
 * @return array $variables
 *   Array keyed with the variable names and with an array of the attributes as the value. 
 *   An additional attribute '_match' contains the whole match within the URL (for later replacement).
 */
function serchilo_get_variables_from_string($str) {

  return serchilo_get_placeholders_from_string($str, '\$');
}

/**
 * Get the Serchilo argument names from a string.
 *
 * @param string $str
 *   The string containing placeholders.
 * @param string $prefix
 *   The prefix of the placeholders. Must be Regex-escaped.
 *
 * @return array $placeholders
 *   Array keyed with the arguments names and with an array of the attributes as the value. 
 *   An additional attribute '_match' contains the whole match within the URL (for later replacement).
 */
function serchilo_get_placeholders_from_string($str, $prefix) {

  $placeholders = array();

  preg_match_all(
    // ? makes ungreedy
    '/\{' . $prefix . '(.+?)\}/',
    $str,
    $matches,
    PREG_SET_ORDER
  );

  foreach ($matches as $match) {

    // Example value:
    // $match = query|encoding=utf-8|another=attribute
    $name_and_attributes = explode('|', $match[1]);

    // Example value:
    // $name = query
    $name = array_shift($name_and_attributes);
    $placeholders[$name] = array();
    $placeholders[$name]['_match'] = $match[0];

    // Example value:
    // $name_and_attributes = encoding=utf-8|another=attribute
    foreach ($name_and_attributes as $attribute_str) {
      $attribute_name_and_value = explode('=', $attribute_str, 2);
      $attribute_name  = array_shift($attribute_name_and_value);
      $attribute_value = array_shift($attribute_name_and_value);
      $placeholders[$name][$attribute_name] = $attribute_value;
    }
  }

  return $placeholders;
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

