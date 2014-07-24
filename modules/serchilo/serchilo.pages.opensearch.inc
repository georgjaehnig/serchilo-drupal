<?PHP

function serchilo_page_opensearch($pathElement1, $pathElement2) {

  if (isset($_GET['default_keyword'])) {
    $default_keyword_get = $_GET['default_keyword'];
  }

  $content['ShortName'] = _serchilo_opensearch_title($pathElement2, $default_keyword_get);

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
    OPENSEARCH_SUGGESTIONS_PATH_AFFIX . 
    '/' . 
    $pathElement1 . 
    '/' . 
    $pathElement2 . 
    '?query={searchTerms}' .
    '';

  $content['UrlOpensearchTemplate'] = 
    $GLOBALS['base_url'] . '/' . 
    OPENSEARCH_DEFINITION_PATH_AFFIX . 
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
    'serchilo-opensearch', 
    array(
      'content' => $content,
    )
  );

  drupal_exit();
}
