<?php print '<?xml version="1.0" encoding="UTF-8"?> '; ?> 
<OpenSearchDescription 
	xmlns="http://a9.com/-/spec/opensearch/1.1/" 
  xmlns:moz="http://www.mozilla.org/2006/browser/search/"
>
<ShortName><?php echo $content['ShortName'] ?></ShortName>
<Url 
	type="text/html" 
	method="get" 
	xmlns:s="http://serchilo.net/opensearchextensions/1.0/"
  template="<?php echo $content['UrlTemplate'] ?>" 
/>

<Url 
  type="application/x-suggestions+json"
  template="<?php echo $content['UrlSuggestionsTemplate'] ?>"
/>
<Url 
  type="application/opensearchdescription+xml"
  rel="self"
  template="<?php echo $content['UrlOpensearchTemplate'] ?>" />

<Image width="16" height="16"><?php echo $content['UrlImage'] ?></Image>
<Contact>opensearch@serchilo.net</Contact>

<moz:UpdateUrl><?php echo $content['UrlOpensearchTemplate'] ?></moz:UpdateUrl>
<moz:SearchForm><?php echo $content['UrlSearchForm'] ?></moz:SearchForm>
<moz:IconUpdateUrl><?php echo $content['UrlImage'] ?></moz:IconUpdateUrl>
<moz:UpdateInterval>7</moz:UpdateInterval>

<Query 
	role="example" 
  searchTerms="g berlin"
/>
<InputEncoding>utf-8</InputEncoding>
<Tags></Tags>
</OpenSearchDescription>


