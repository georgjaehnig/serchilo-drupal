<form role="form" action="?" method="get" id="serchilo-shortcut-query-form" accept-charset="UTF-8" class="form">  
  <div class="input-group input-group-lg">
      <input id="searchInput" type="text" class="form-control" name="query" value="<?php echo $query ?>" autocomplete="off" />
    <div class="input-group-btn">
      <button type="submit" class="btn btn-primary">Go</button>
    </div><!-- /btn-group -->
    <?php foreach ($get_parameters as $name=>$value): ?>
      <input type="hidden" name="<?php echo $name ?>" value="<?php echo $value ?>"/>
    <?php endforeach; ?>
  </div><!-- /input-group -->
</form>
