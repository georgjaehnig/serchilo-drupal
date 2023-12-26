<div class="alert alert-block alert-dismissible alert-warning messages warning">
  <a class="close" data-dismiss="alert" href="#">×</a>
<h4 class="element-invisible">Warning message</h4>
FindFind.it will <strong>close on 31 December 2023</strong>. But its successor <a href="https://trovu.net">Trovu</a> is already running, please <a href="https://trovu.net/docs/legacy/migrate/">migrate</a>.
</div>

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
