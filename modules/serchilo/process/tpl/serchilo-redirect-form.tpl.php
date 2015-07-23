<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
       "http://www.w3.org/TR/html4/loose.dtd">
<html>
<body onload="document.getElementsByTagName('form').item(0).submit();">
<form action="<?php echo $url ?>" method="post" accept-charset="utf-8">
<?php foreach($post_parameters as $post_key=>$post_value): ?>
  <input type="hidden" name="<?php echo $post_key; ?>" value="<?php echo $post_value; ?>" >
<?php endforeach; ?>
<input type="submit" value="Please wait... or click here to proceed" >
</form>
</body>
</html>

