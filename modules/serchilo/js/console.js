(function ($) {

  var called = false;

  // command array indexes
  var ID                = 0;
  var KEYWORD           = 1;
  var ARGUMENT_NAMES    = 2;
  var TITLE             = 3;
  var NAMESPACE         = 4;
  var REACHABLE         = 5;
  var URL               = 6;

  Drupal.behaviors.serchilo = {
    attach: function (context, settings) {

      if (called) {
        return; 
      }

      var searchInput = $('#searchInput');
      searchInputBackground = $('#searchInputBackground');

      autocomplete = searchInput.autocomplete({

        minLength: 1,
        delay: 300,

        select: function( event, ui ) {
          // If it is a shortcut
          // go to its node page 
          if (ui.item[ID] > 0 ) {
            // Go to shortcut page
            window.location.href = '/node/' + ui.item[ID];
          } 
          // Else: Call the given URL
          else {
            window.location.href = ui.item[URL];
          }
          return; 
        },

        // create autocomplete list
        source: Drupal.settings.serchilo.autocomplete_url,

        focus: function( event, ui ) {
          // prevents input being emptied when scrolling over commands in autocomplete
          return false;
        },
      
      })
      .data('uiAutocomplete')._renderItem = function( ul, item ) {

        var namespace_html = ''; 
        // show namespace only on actual commands
        // not on serchilo internal search links
        // (e.g. "!t Show all commands with title = ... ")
        if (item[ID] > 0) {
          namespace_html = 
            '<span class="namespace">' + 
            item[NAMESPACE]   
            '</span>';
        }

        var keyword = item[KEYWORD];

        // add "namespace." if unreachable
        if (!item[REACHABLE]) {
          keyword = item[NAMESPACE] + '.' + keyword; 
        }
        var argument_names = item[ARGUMENT_NAMES].split(',').join(', ');
        var title = item[TITLE];

        var html = 
          '<a' + 
            ( item[REACHABLE] ? "" : " class='unreachable'" ) + 
            ( item[ID] > 0 ? ""  : " class='search-command'" ) + 
            '>' + 
            '&nbsp;'+ // to make bar visible /float:-related problem
            '<span class="left">'+
              '<span class="keyword">' + 
                keyword +
              '</span>'+
              '<span class="argument-names">' + 
                argument_names +
              '</span>'+
            '</span>'+
            '<span class="right">'+
              '<span class="title">' + 
                title +
              '</span>' +
              namespace_html +
            '</span>'+
          '</a>' +
          '';
          
        return $( "<li></li>" )
          .data( "item.autocomplete", item )
          .append(html)
          .appendTo( ul );
      };

      searchInput.autocomplete('widget').removeClass('ui-corner-all');
      searchInput.focus();

      called = true;
    }
  }

})(jQuery);
