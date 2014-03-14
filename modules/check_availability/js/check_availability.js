(function($) {
  Drupal.behaviors.check_availability_form = {
    attach: function (context, settings) {
      // set page load defaults
      if (!$('#edit-check-in-datepicker-popup-0').val()) {
        $('#edit-check-in-datepicker-popup-0').attr('value', '- Arrival Date -');
      }

      if (!$('#edit-check-out-datepicker-popup-0').val()) {
        $('#edit-check-out-datepicker-popup-0').attr('value', '- Departure Date -');
      }

      // if we lose focus, set a default if no value entered
      $('#edit-check-in-datepicker-popup-0').blur(function() {
          if (!$('#edit-check-in-datepicker-popup-0').val()) {
              $('#edit-check-in-datepicker-popup-0').attr('value', '- Arrival Date -');
          }
      });

      $('#edit-check-out-datepicker-popup-0').blur(function() {
        if (!$('#edit-check-out-datepicker-popup-0').val()) {
          $('#edit-check-out-datepicker-popup-0').attr('value', '- Departure Date -');
        }
      });
    }
  }
})(jQuery);