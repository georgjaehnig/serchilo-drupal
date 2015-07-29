jQuery(document).ready(function () { 
  var link = jQuery("<a style=\"cursor: pointer; cursor: hand;\">" + Drupal.settings.serchilo.link_text + "</a>");
  link.click(function() {
    jQuery("#edit-field-namespace-und").val(Drupal.settings.serchilo.namespace_name);
  });
  jQuery(".form-item-field-namespace-und").append(link);
});
