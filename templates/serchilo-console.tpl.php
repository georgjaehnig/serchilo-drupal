<div id="commandHeader">
  <!--<a id="title" href="#" target="_new"></a>-->
  <h1 class="title" id="page-title"><a id="title" href="#">&nbsp;</a></h1>
  <a href="#" target="_new" id="namespace" class="namespace"></a><span id="tags">  </span>

  <!--<a id="closeButton" href="#">close</a>-->
</div>

<div id="search">
  <form action="?" method="get" id="serchilo-command-query-form" accept-charset="UTF-8" role="form" class="form-inline">
  <div class="form-group">
    <input type="hidden" class="form-control" id="searchInputBackground" name="query" value="<?php echo $query ?>" autocomplete="off" >
    <input type="search" class="form-control" id="searchInput" name="query" value="<?php echo $query ?>" autocomplete="off" >
  </div>
  <input type="hidden" name="default_keyword" value="<?php echo $default_keyword ?>" >
  <button type="submit" class="btn btn-default" id="searchSubmit">Go</button>
  </form>
&nbsp;
</div>


<div id="help">
Start with a <a href="<?php echo $commands_of_current_namespaces_url ?>">keyword</a>, continue with your search.
Or watch a <a href="http://www.youtube.com/watch?v=lNx4CFM-P2M" target="_blank">screencast video</a> to learn more.
</div>

