<div class="container">
  <div id="search">
    <form action="?" method="get" id="serchilo-shortcut-query-form" accept-charset="UTF-8" class="form" role="form">
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
    Enter one of the available <a href="<?php echo $shortcuts_of_current_namespaces_url ?>">shortcuts</a>.
    Or watch a <a href="http://www.youtube.com/watch?v=lNx4CFM-P2M" target="_blank">screencast video</a> to learn more.
  </div>
</div>

