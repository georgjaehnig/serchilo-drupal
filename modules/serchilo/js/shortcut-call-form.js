
jQuery(document).ready(function($) {

  serchilo_set_input_widths($);

  var that = $;
  jQuery(window).resize(function(that) {
    serchilo_set_input_widths($);
  });

});

function serchilo_set_input_widths($) {

  // Set widths of text inputs.

  // Get current widths.
  var form_width    = $('#serchilo-shortcut-call-form').outerWidth();
  var keyword_width = $('#serchilo-shortcut-call-form div.keyword').outerWidth();
  var submit_width  = $('#edit-submit').outerWidth();

  // Calculate with for single text input.
  var argument_width_total  = form_width - keyword_width - submit_width - 20;
  var argument_count        = $('#serchilo-shortcut-call-form input.form-text').length;
  var argument_width_single = Math.round(argument_width_total / argument_count) - 5;

  // Set widths for all single text inputs.
  $('#serchilo-shortcut-call-form input.form-text').each(function() {
    $(this).outerWidth(argument_width_single);
  });
}
