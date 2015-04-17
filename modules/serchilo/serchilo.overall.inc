<?php

/**
* @file
* Functions shared by the Drupal module and the standalone Process code.
*/

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

/**
 * Get the Serchilo argument names from a string.
 *
 * @param string $str
 *   The string containing placeholders.
 *
 * @return array $arguments
 *   Array keyed with the arguments names and with an array of the attributes as the value. 
 *   An additional attribute '_match' contains the whole match within the URL (for later replacement).
 */
function serchilo_get_arguments_from_string($str) {

  $arguments = array();

  preg_match_all(
    // ? makes ungreedy
    '/\{%(.+?)\}/',
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
    $arguments[$name] = array();
    $arguments[$name]['_match'] = $match[0];

    // Example value:
    // $name_and_attributes = encoding=utf-8|another=attribute
    foreach ($name_and_attributes as $attribute_str) {
      $attribute_name_and_value = explode('=', $attribute_str, 2);
      $attribute_name  = array_shift($attribute_name_and_value);
      $attribute_value = array_shift($attribute_name_and_value);
      $arguments[$name][$attribute_name] = $attribute_value;
    }
  }

  return $arguments;
}

