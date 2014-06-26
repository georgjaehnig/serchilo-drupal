function installSearchPlugin()
{
	window.external.AddSearchProvider(
		"http://" + location.host + "/opensearch" + location.pathname + location.search
	);
}

(function ($) {

  var called = false;
  var searchInput;
  var searchInputBackground;
  /*
  var examples = [
    ['g berlin', 'Google search for "berlin"'],
    ['w berlin', 'Wikipedia article about Berlin'],
    ['db berlin, hamburg', 'Nächste Verbindung von Berlin nach Hamburg']
  ]; */
  var typewriteTimeout;
  var typewriting = false;


  // command array indexes
  var ID                = 0;
  var KEYWORD           = 1;
  var ARGUMENT_NAMES    = 2;
  var TITLE             = 3;
  var NAMESPACE         = 4;
  var REACHABLE         = 5;
  var URL               = 6;

  var commandSelectedIndex = -1;

  function startTypewrite() {

    //var examples = Drupal.settings.serchilo.typewrite_examples;
    function typewrite() {

      if (examplesIndex == examples.length) {
        examplesIndex = 0;
      }
      query = examples[examplesIndex][0];
      description = examples[examplesIndex][1];
      // type query
      if (queryPosition < query.length) {
        searchInput.val(query.substring(0, queryPosition + 1));
        queryPosition = queryPosition + 1;
        typewriteTimeout = setTimeout( function() { typewrite(); }, 100 );
        return;
      }
      // show description
      if (queryPosition == query.length) {
        searchInputBackground.val(description);
        queryPosition = queryPosition + 1;
        typewriteTimeout = setTimeout( function() { typewrite(); }, 3000 );
        return;
      }
      // clear all
      if (queryPosition > query.length) {
        searchInput.val('');
        searchInputBackground.val('');
        queryPosition = 0;
        examplesIndex = examplesIndex + 1;
        typewriteTimeout = setTimeout( function() { typewrite(); }, 100 );
        return;
      }
    }

    examplesIndex = 0;
    queryPosition = 0; 
    typewrite();
    typewriting = true;
  }

  function stopTypewrite() {
    if (typewriting) {
      clearTimeout(typewriteTimeout);
      searchInput.val('');
      searchInputBackground.val('');
      searchInputBackground.css('padding-right', 0);
      searchInputBackground.css('text-align', 'left');
      typewriting = false;
    }
  }

  function parseQuery(queryString)
  {
    //			bg				qS
    // ''						-2
    // 'f'		'f'		' x,y'	-1
    // 'f '		'f '	'x,y'	0
    // 'f a'	'f a'	',y'	1
    // 'f a,'	'f a,'	'y'		2
    // 'f a,b'	'f a,b'	''		2

    var state = -2;
    var keyword = '';
    var args = [];
    var namespace = '';
		// syntax: keyword, args
		// or: namespace.keyword args
    matches = queryString.match( /^\s*((\S*)\.)?(\S*)( *)(.*)$/ )

    keyword = matches[3];
    namespace = matches[2];
    if ( matches[5] != '' ) {
      args = matches[5].split(',');
    }
    if ( keyword != '' ) {
      state = -1;	
    } 
    if ( matches[4] != '' ) {
      state = 0;
    } 
    if ( args.length > 0 ) {
      state = args.length;	
    }
    query = {
      'state': state, 
      'keyword': keyword,
      'args': args,
      'namespace': namespace,
    };
    return query;
  }

  function updateInputBackground()
  {
    command = Drupal.settings.command;
    if (command == null) {
      // make sure background is empty
      unselectCommand();
      return;
    }
    query = parseQuery( searchInput.val());
    if (query.state < 0) {
      unselectCommand();
      return;
    }
    queryString = command.keyword + ' ' + query.args.join(',');
    if (command.reachable == false) {
      queryString = command.namespace + '.' + queryString;
    }
    searchInput.val( queryString );

    var bgVal = queryString;
    if ( query.state == -1 ) {
      bgVal += ' ';	
    }
    if ( 
      ( query.state > 0 ) && 
      ( command.argument_names.split(',').length > query.args.length ) && 
      ( query.args[query.args.length-1] != '' )
       ) {
      bgVal += ',';	
    }
    if (
      ( query.args.length > 1 ) &&
      ( query.args[query.args.length-1] == '' )
       ) {
      query.state = query.state-1;
    }
    bgVal += command.argument_names.split(',').slice(Math.max(0,query.state)).join(',');
    searchInputBackground.val( bgVal );
  }

  function selectCommand( id, reachable ) {

    $.getJSON(Drupal.settings.basePath + 'ajax/command/' + id, function(command) {
      if (command.id == null) {
        console.log('No command with ID ' + id + ' found.');
        return; 
      }

      command.reachable = reachable;

      $( '#title' ).attr('href', encodeURI( Drupal.settings.basePath + 'command/' + command.id  ));

      $( '#title' ).text( command.title);

      $( '#namespace' ).text(command.namespace);
      $( '#namespace' ).attr('href', encodeURI( Drupal.settings.basePath + 'commands?namespace=' + command.namespace ));

      $('#tags').empty();
      $.each(
        command.tags, 
        function(i,tag) {
          $('#tags').append(
            $(
              '<a>', 
              {
                'text': tag,
                'class': 'tag',
                'href': encodeURI( Drupal.settings.basePath + 'commands?tags=' + tag),
                'target': '_new'
              }
            )
          );
        }
      );

      $('#commandHeader').css('visibility', 'visible');

      jQuery.each(command.examples, function(key, value) {
        arguments = value[0];
        description = value[1];
        queryA = $('<a>');
        queryA.text(command.keyword + ' ' + arguments);
        queryA.attr('href', encodeURI( 
            '?query=' + command.namespace + '.' + command.keyword + ' ' + arguments

          )
        );
        queryDT = $('<dt>');
        queryDT.append(queryA);
        $('#examples dl').append(queryDT);

        descriptionDD = $('<dd>');
        descriptionDD.text(description);
        $('#examples dl').append(descriptionDD);

      } );
      $('#examples').show();

      query = parseQuery( searchInput.val());
      queryString = command.keyword + ' ' + query.args.join(',');
      if (command.reachable == false) {
        queryString = command.namespace + '.' + queryString;
      }
      searchInput.val( queryString );

      Drupal.settings.command = command;

      updateInputBackground();

      searchInput.autocomplete('option', 'disabled', true );
      return;
    });

  }
  function hideOnSearch() {
    $('.hide-on-search').hide();
  }

  function hideCommandElements() {
    $('#commandHeader').css('visibility', 'hidden');
    $('#examples').hide();
    $('#examples dl').empty();

  }

  function unselectCommand() {
  
    hideCommandElements();

    Drupal.settings.command = null;
    searchInputBackground.val('');

    searchInput.autocomplete('option', 'disabled', false);
    searchInput.autocomplete('search');
  }

  function emptyInput() {
    searchInput.val('');
    searchInputBackground.val('');
  }

  function command_id_to_index(id) {
    for (var i=0; i<commands.length; i++) {
      if ( commands[i][ID] == id ) {
          return commands[i][INDEX]; 
      }
    }
    return null;
  }

  function isCommandSelected() {
    return commandSelectedIndex > -1; 
  }

  Drupal.behaviors.serchilo = {
    attach: function (context, settings) {

      if (called) {
        return; 
      }

      searchInput = $('#searchInput');
      searchInputBackground = $('#searchInputBackground');

      autocomplete = searchInput.autocomplete({

        minLength: 1,
        delay: 300,

        select: function( event, ui ) {
          //console.log('select');
          //console.log(ui.item[ID]);
          if (ui.item[ID] == 0 ) {
            window.location.href = ui.item[URL];
            return; 
          }
          selectCommand(ui.item[ID], ui.item[REACHABLE] == 1);
          // return false to set input value
          return false;
        },

        // create autocomplete list
        source: Drupal.settings.serchilo.autocomplete_url,

        focus: function( event, ui ) {
          // prevents input being emptied when scrolling over commands in autocomplete
          return false;
        },

        search: function(event, ui) {
          hideOnSearch();
        }

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
          // add "namespace." if unreachable
          keyword +
          '</span>'+
          '<span' +
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

  /*
      // hide all unecessary elements
      hideCommandElements();

      // don't start typewrite when query is already filled
      // (for instance from a failed query before)
      if (searchInput.val() == '') {
        //startTypewrite(examples);
      } 

      // no round corners
      searchInput.autocomplete('widget').removeClass('ui-corner-all');

      // set focus on input
      searchInput.focus();

      // only for html5 browsers
      searchInput.bind('input', function() { 
        updateInputBackground();
      });

      searchInput.click(function(){
        //stopTypewrite();
      });

      searchInput.keydown(function(event) {
        //stopTypewrite();
      });

      // fallback for non-html5 browsers
      searchInput.keyup(function(event) {
        // if there's an input event we can get out of here
        if (typeof(searchInput.data('events').input) !== 'undefined') {
          return;
        }
        updateInputBackground();
        if (27 == event.keyCode) {
          emptyInput();
          unselectCommand();
          //searchInput.autocomplete('search');
        }
      }); 

    */
      called = true;
    }
  }

})(jQuery);
