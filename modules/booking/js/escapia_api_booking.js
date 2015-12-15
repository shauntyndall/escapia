(function($) {
  try{
    Drupal.ajax.prototype.commands.ajax_command_raw_html = function (ajax, response, status) {
      $(response.selector).html(response.data);
    };

    $(document).ajaxSend(function(e, xhr, settings){
      var trigger = settings.extraData._triggering_element_name;
      var parent = $('input[name="' + trigger + '"]').closest('tr').attr('id');
      $('#' + parent + ' td.subtotal').fadeTo('150', '.5');
      settings.extraData.parentElement = parent;
    }).ajaxComplete(function(e, xhr, settings) {
      $('#' + settings.extraData.parentElement + ' td.subtotal').fadeTo('150', '1');
    });

    Drupal.behaviors.preventDoubleSubmit = {
      attach: function(context) {
        $('form#escapia-api-booking-contact-information-form', context).once('preventDoubleSubmit', function () {
          var $form = $(this);
          $form.find('#edit-submit').click(function (e) {
            $('form#escapia-api-booking-contact-information-form #edit-submit').html('Please wait...');
            $('form#escapia-api-booking-contact-information-form #edit-submit').fadeTo('fast', '.8');
            return true;
          });
          $form.submit(function (e) {
            if (!e.isPropagationStopped()) {
              $('#edit-submit', $(this)).attr('disabled', 'disabled');
              return true;
            }
          });
        });
      }
    };
  } catch(err) {
    console.log("Escapia API error: " + err.message);
  }
})(jQuery, Drupal);