<?PHP

function serchilo_page_opensearch($pathElement1, $pathElement2) {

  $default_keyword_get = drupal_array_get_nested_value($_GET, array('default_keyword'));

  $content['ShortName'] = serchilo_opensearch_title($pathElement2, $default_keyword_get);

  $content['UrlTemplate'] = 
    $GLOBALS['base_url'] . 
    '/' . 
    $pathElement1 . 
    '/' . 
    $pathElement2 . 
    '?' .
    ($default_keyword_get ? 'default_keyword=' . $default_keyword_get . '&amp;' : '') .
    'query={searchTerms}' .
    '';

  $content['UrlSuggestionsTemplate'] = 
    $GLOBALS['base_url'] . '/' . 
    SERCHILO_OPENSEARCH_SUGGESTIONS_PATH_AFFIX . 
    '/' . 
    $pathElement1 . 
    '/' . 
    $pathElement2 . 
    '?query={searchTerms}' .
    '';

  $content['UrlOpensearchTemplate'] = 
    $GLOBALS['base_url'] . '/' . 
    SERCHILO_OPENSEARCH_DEFINITION_PATH_AFFIX . 
    '/' . 
    $pathElement1 . 
    '/' . 
    $pathElement2 . 
    '';

  $content['UrlImage'] = 
    $GLOBALS['base_url'] . '/' . 
    drupal_get_path('theme', 'bootstrap_serchilo') . '/' .
    'favicon.ico' .
    '';

  $content['UrlSearchForm'] = 
    $GLOBALS['base_url'] . '/' .
    '';

  $content['UrlUpdate'] = 
    $GLOBALS['base_url'] . 
    '';

  drupal_add_http_header('Content-Type', 'text/xml');
  echo theme(
    'serchilo_opensearch', 
    array(
      'content' => $content,
    )
  );

  drupal_exit();
}
