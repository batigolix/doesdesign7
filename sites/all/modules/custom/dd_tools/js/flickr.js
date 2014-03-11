(function($) {
  Drupal.behaviors.dd_tools = {
    attach: function(context, settings) {
      // --------
            var block_items = Drupal.settings.dd_tools.block_items;

      $(document).ready(function() {
        // Our very special jQuery JSON fucntion call to Flickr, gets details
        // of the most recent 20 images
        // flickr id batigollix 62546836@N00
        //$.getJSON("http://api.flickr.com/services/feeds/groups_pool.gne?id=998875@N22&lang=en-us&format=json&jsoncallback=?", displayImages);
        $.getJSON("http://api.flickr.com/services/feeds/photos_public.gne?id=23406248@N05&lang=en-en&format=json&jsoncallback=?", displayImages);
        function displayImages(data) {
          // Start putting together the HTML string
          var htmlString = "<ul>";
          // Now start cycling through our array of Flickr photo details
          $.each(data.items, function(i, item) {
            // I only want the ickle square thumbnails
            var sourceSquare = (item.media.m).replace("_m.jpg", "_s.jpg");
            // Here's where we piece together the HTML
            htmlString += '<li><a href="' + item.link + '" >';
            htmlString += '<img title="' + item.title + '" src="' + sourceSquare;
            htmlString += '" alt="';
            htmlString += item.title + '" />';
            htmlString += '</a></li>';
            return i < 11;
          });
          // Pop our HTML in the #images DIV
          $('#flickr_images').html(htmlString + "</ul>");
          // Close down the JSON function call
        }
      });


      // --------
    }
  }
})(jQuery);