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
 *   Array keyed with the arguments names and with an array of corresponding
 *   placeholders.
 *
 *   If the placeholder with the same name occurs multiple times, there are also
 *   multiple arrays in the nested array. 
 *
 *   Example: 
 *     http://{%first|type=foo}{%first|type=bar}
 *   becomes:
 *   Array 
 *       (
 *            [first] => Array
 *            (
 *                [{%first|type=foo}] => Array
 *                    (
 *                        [type] => foo
 *                    )
 *                [{%first|type=bar}] => Array
 *                    (
 *                        [type] => bar
 *                    )
 *            )
 *        )
 *
 *   An additional attribute '_match' contains the whole match within the URL 
 *   (for later replacement).
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
    $placeholder = array();

    // Example value:
    // $name_and_attributes = encoding=utf-8|another=attribute
    foreach ($name_and_attributes as $attribute_str) {
      $attribute_name_and_value = explode('=', $attribute_str, 2);
      $attribute_name  = array_shift($attribute_name_and_value);
      $attribute_value = array_shift($attribute_name_and_value);
      $placeholder[$attribute_name] = $attribute_value;
    }
    $placeholders[$name][$match[0]] = $placeholder;
  }

  return $placeholders;
}

/**
 * Get the Serchilo argument names from the placeholders in URL.
 *
 * @param string $url
 *   The URL containing placeholders.
 * @param string $post_parameters
 *   The POST parameter string containing placeholders.
 *
 * @return array $argument_names
 *   The extracted argument names.
 */
function serchilo_get_argument_names($url, $post_parameters) {

  $argument_names = array_merge(
    array_keys(serchilo_get_arguments_from_string($post_parameters)),
    array_keys(serchilo_get_arguments_from_string($url))
  );

  // treat arguments with same name as only one argument
  $argument_names = array_unique($argument_names);

  // make sure indexes have no gaps
  $argument_names = array_values($argument_names);

  return $argument_names;
}

/**
 * Return the post parameters of a shortcut
 *   and replace them with the query arguments and variables.
 *
 * @param array $shortcut
 *   The shortcut to call.
 * @param array $arguments
 *   The arguments from the query.
 * @param array $variables
 *   The variables.
 *   
 * @return array $post_parameters
 *   The post parameters.
 *   Empty array if none present.
 */
function serchilo_get_post_parameters($post_parameters_str) {
  if (empty($post_parameters_str)) {
    return array(); 
  }
  $post_parameters = array();
  foreach (explode('&', $post_parameters_str) as $post_parameter) {
    $post_parameter = urldecode($post_parameter);
    $post_parameter = utf8_encode($post_parameter);
    $keyValue = explode('=', $post_parameter, 2);
    if (count($keyValue) == 2) {
      $post_parameters[$keyValue[0]] = $keyValue[1];
    }
    else {
      $post_parameters[$keyValue[0]] = 1;
    }
  }
  return $post_parameters; 
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

