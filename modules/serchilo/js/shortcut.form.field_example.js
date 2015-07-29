jQuery(document).ready(function () { 

  var set_description = function() {

    var title_input       = jQuery("input[name='title']");
    var arguments_input   = jQuery("input[name='field_example[und][0][field_example_arguments][und][0][value]']");
    var description_input = jQuery("input[name='field_example[und][0][field_example_description][und][0][value]']");

    // Skip if already has a value.
    if (description_input.val()) {
      return; 
    }

    var description_str = 'Search ' + title_input.val() + ' for "' + arguments_input.val() + '"';
    description_input.val(description_str);
  }

  // TODO: Make work for more than first example.
  jQuery("input[name='field_example[und][0][field_example_arguments][und][0][value]']").change(set_description);
});

