jQuery(document).ready(function () { 
  var link = jQuery("<a style=\"cursor: pointer; cursor: hand;\">Use my user namespace</a>");
  link.click(function() {
    jQuery("#edit-field-namespace-und").val(Drupal.settings.serchilo.user_name);
  });
  jQuery(".form-item-field-namespace-und").append(link);
});
