(function ($, Drupal, undefined) {
  $(document).ready(function() {
    $('[name="from_display"]').val(Drupal.t("Pick a date on the calendar"));
    //console.log(calendar);
    //$(calendar).bind("calendarClick", function(e){
    //  $('.field-name-field-escapia-book-unit .form-reset').show();
    //});

    $('<hr>').insertBefore('.group-row-container-book');
    $('<hr>').insertAfter('.group-row-container-book');

  });
  Drupal.behaviors.escapia_api = {
    attach: function (context, settings) {
      $('.field-type-availability-calendar .cal-buttons').height($('.field-type-availability-calendar .cal-viewport').height());
      $('.field-name-field-escapia-book-unit .form-reset').val('Clear').change();
      $(".field-name-field-escapia-book-unit #edit-submit.form-submit").attr("disabled", "disabled").addClass("form-button-disabled").hide();


      $( ".field-name-field-escapia-book-unit .form-reset" ).click(function(e) {
        $('[name="from_display"]').val(Drupal.t("Pick a date on the calendar")).change();
        $(".field-name-field-escapia-book-unit #edit-submit.form-submit").attr("disabled", "disabled").removeClass('hide').addClass("form-button-disabled").hide();
        $('.unavailable-response').html(' ');
        $('.escapia-response').html(' ');
        $('.escapia-errors').html(' ');
        $('.field-name-field-escapia-book-unit .form-type-select').show();
        $('.field-name-field-escapia-book-unit .check-rates').show();
      });



      $( document ).ajaxComplete(function( event, xhr, settings ) {
        var bad_response = $('.escapia-response .unavailable-response');
        if ( settings.url === "/system/ajax" && settings.extraData._triggering_element_value == "Check Availability" && xhr.status == 200) {
          if(bad_response.length == 0) {
            $(".field-name-field-escapia-book-unit #edit-submit.form-submit").removeAttr("disabled").removeClass("form-button-disabled").show();
            $('.field-name-field-escapia-book-unit .form-type-select').hide();
            $('.field-name-field-escapia-book-unit .check-rates').hide();
          } else if(bad_response.length > 0) {
            $(".field-name-field-escapia-book-unit #edit-submit.form-submit").addClass('hide');
            if($( "form .unavailable-response") !== undefined && $( "form .unavailable-response").length > 0) {
              $( "form .unavailable-response" ).detach().insertBefore( ".field-group-htabs-wrapper" );
            }
          }
        }
      });


      if (typeof settings.escapia_api != 'undefined') {

        if (typeof settings.escapia_api.dateSettings != 'undefined') {
          $.each(settings.escapia_api.dateSettings, function(index, value) {
            var settings_val = JSON.parse(value);
            settings_val['onClose'] = function(){
              $(document.activeElement).blur();
            }
            $('.' + index).pickadate(settings_val);
            //$(document).find('#' + index).each(function() {
            //  $(this).pickadate(settings_val);
            //});
          });
        }

        //if (typeof settings.escapia_api.timeSettings != 'undefined') {
        //  $.each(settings.escapia_api.timeSettings, function(index, value) {
        //    $('#' + index).pickatime(JSON.parse(value));
        //  });
        //}
      }

      $("#escapia-avail-rate-details").dialog({
        autoOpen: false,
        draggable: false,
        height: 'auto',
        width: 300,
        modal: true,
        resizable: false,
        title: 'Quote Details',
        closeText: 'Close',
        overlay: { background: "black" }
        //buttons: {
        //  "Okay, I'm done!": function() {
        //    //// the modal won't disappear from the page for some reason.. it is still visible in the lower corner
        //    //$('#realestate-advanced-search-modal').parent().css('left', '-9999px');
        //    //$('#realestate-advanced-search-modal').parent().detach().appendTo('form#prugallo-realestate-rentals-search-form');
        //    //$("form#prugallo-solrsearch-realestate-search-form").submit();
        //  }
        //}
      });

      $( "#escapia-avail-rate-details-link" ).click(function(e) {
        e.preventDefault();
        $( "#escapia-avail-rate-details" ).dialog( "open" );
      });
    }
  };
})(jQuery, Drupal);