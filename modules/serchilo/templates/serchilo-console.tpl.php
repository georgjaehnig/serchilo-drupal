<div class="container">
  <div id="search">
    <form action="?" method="get" id="serchilo-command-query-form" accept-charset="UTF-8" class="form" role="form">
      <div class="form-group">
        <div class="col-md-10 col-xs-10 col-sm-10 col-lg-10 ">
          <input id="searchInput" type="text" class="form-control" name="query" value="<?php echo $query ?>" autocomplete="off">
        </div>
      <button id="searchSubmit" type="submit" class="btn btn-default col-xs-2 col-sm-2 col-md-2 col-lg-2 ">Go</button>
      </div>
    </form>
    &nbsp;
  </div>

  <div id="help">
    Start with a <a href="<?php echo $commands_of_current_namespaces_url ?>">keyword</a>, continue with your search.
    Or watch a <a href="http://www.youtube.com/watch?v=lNx4CFM-P2M" target="_blank">screencast video</a> to learn more.
  </div>
</div>

