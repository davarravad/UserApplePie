/*
 * Plugin jQuery.BBCode
 * Version 0.2 
 *
 * Based on jQuery.BBCode plugin (http://www.kamaikinproject.ru)
 */
(function($){
  $.fn.bbcode = function(options){
		// default settings
    var options = $.extend({
      tag_bold: true,
      tag_italic: true,
      tag_underline: true,
      tag_link: true,
      tag_image: false,
	  tag_quote: true,
	  tag_youtube: true,
	  tag_code: true,
      button_image: true,
      image_url: '/images/bbimage/'
    },options||{});
    //  panel 
    var text = '<div id="bbcode_bb_bar">'
    if(options.tag_bold){
      text = text + '<a href="#" id="b" title="">';
      if(options.button_image){
        text = text + '<img src="./external/' + options.image_url + 'bold.png" />';
      }else{
        text = text + 'Bold';
      }
      text = text + '</a>';
    }
    if(options.tag_italic){
      text = text + '<a href="#" id="i" title="">';
      if(options.button_image){
        text = text + '<img src="./external/' + options.image_url + 'italic.png" />';
      }else{
        text = text + 'Italic';
      }
      text = text + '</a>';
    }
    if(options.tag_underline){
      text = text + '<a href="#" id="u" title="">';
      if(options.button_image){
        text = text + '<img src="./external/' + options.image_url + 'underline.png" />';
      }else{
        text = text + 'Undescore';
      }
      text = text + '</a>';
    }
    if(options.tag_link){
      text = text + '<a href="#" id="url" title="">';
      if(options.button_image){
        text = text + '<img src="./external/' + options.image_url + 'link.png" />';
      }else{
        text = text + 'Link';
      }
      text = text + '</a>';
    }
    if(options.tag_image){
      text = text + '<a href="#" id="img" title="">';
      if(options.button_image){
        text = text + '<img src="./external/' + options.image_url + 'image.png" />';
      }else{
        text = text + 'Image';
      }
      text = text + '</a>';
    }
    if(options.tag_quote){
      text = text + '<a href="#" id="quote" title="">';
      if(options.button_image){
        text = text + '<img src="./external/' + options.image_url + 'quote.png" />';
      }else{
        text = text + 'Quote';
      }
      text = text + '</a>';
    }
    if(options.tag_youtube){
      text = text + '<a href="#" id="youtube" title="">';
      if(options.button_image){
        text = text + '<img src="./external/' + options.image_url + 'youtube.png" />';
      }else{
        text = text + 'YouTube';
      }
      text = text + '</a>';
    }
    if(options.tag_code){
      text = text + '<a href="#" id="code" title="">';
      if(options.button_image){
        text = text + '<img src="./external/' + options.image_url + 'php.png" />';
      }else{
        text = text + 'Code';
      }
      text = text + '</a>';
    }
    text = text + '</div>';
    
    $(this).wrap('<div id="bbcode_container"></div>');
    $("#bbcode_container").prepend(text);
    $("#bbcode_bb_bar a img").css("border", "none");
    var id = '#' + $(this).attr("id");
    var e = $(id).get(0);
    
    $('#bbcode_bb_bar a').click(function() {
      var button_id = $(this).attr("id");
      var start = '['+button_id+']';
      var end = '[/'+button_id+']';

	  var param="";
	  if (button_id=='img')
	  {
	     param=prompt("Enter image URL","http://");
		 if (param)
			start+=param;
		 }
	  else if (button_id=='url')
	  {
			param=prompt("Enter URL","http://");
			if (param) 
				start = '[url href=' + param + ']LINK';
		 }
	  else if (button_id=='youtube')
	  {
			param=prompt("YouTube Share Link","http://youtu.be/");
			if (param) 
				start = '[youtube]' + param + '';
		 }

      insert(start, end, e);
      return false;
    });
	}
  function insert(start, end, element) {
    if (document.selection) {
       element.focus();
       sel = document.selection.createRange();
       sel.text = start + sel.text + end;
    } else if (element.selectionStart || element.selectionStart == '0') {
       element.focus();
       var startPos = element.selectionStart;
       var endPos = element.selectionEnd;
       element.value = element.value.substring(0, startPos) + start + element.value.substring(startPos, endPos) + end + element.value.substring(endPos, element.value.length);
    } else {
      element.value += start + end;
    }
  }
 
// hotkeys 
$(document).keyup(function (e) 
{ if(e.which == 17) isCtrl=false; }).keydown(function (e) 
{ if(e.which == 17) isCtrl=true; 
if (e.which == 66 && isCtrl == true) // CTRL + B, bold
{ 
	$("#b").click();
	return false;
} 
else if (e.which == 73 && isCtrl == true) // CTRL + I, italic
{ 
	$("#i").click();
	return false;
} 
else if (e.which == 85 && isCtrl == true) // CTRL + U, underline
{ 
	$("#u").click();
	return false;
}
})
  
})(jQuery)