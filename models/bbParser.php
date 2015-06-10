<?php
  class bbParser{
    public function __construct(){}
    
    public function getHtml($str){
      $bb[] = "#\[b\](.*?)\[/b\]#si";
      $html[] = "<b>\\1</b>";
      $bb[] = "#\[i\](.*?)\[/i\]#si";
      $html[] = "<i>\\1</i>";
      $bb[] = "#\[u\](.*?)\[/u\]#si";
      $html[] = "<u>\\1</u>";
      $bb[] = "#\[quote\](.*?)\[/quote\]#si";
      $html[] = "<center><div class='epboxc' width='80%' align='left'><b><i>Quote</i></b><br><b>&ldquo;</b><i>\\1</i><b>&rdquo;</b></div></center>";
	  $bb[] = "#\[youtube\](.*?)\[/youtube\]#si";
      $html[] = '<center><iframe width="300" height="169" src="//www.youtube.com/embed/\\1" frameborder="0" allowfullscreen></iframe></center>';
      $bb[] = "#\[hr\]#si";
      $html[] = "<hr>";
      $bb[] = "#\[code\](.*?)\[/code\]#si";
      $html[] = "<center><div class='epboxc' width='80%' align='left'><b><i><font size=0.5>Code</font></i></b><hr><div class=php><pre class=\"code\">\\1</pre></div></div></center>";
	  $str = str_replace('http://youtu.be/','',$str);
      $str = preg_replace ($bb, $html, $str);
      $patern="#\[url href=([^\]]*)\]([^\[]*)\[/url\]#i";
      $replace='<a href="\\1" target="_blank" rel="nofollow">\\2</a>';
      $str=preg_replace($patern, $replace, $str); 
      $patern="#\[img\]([^\[]*)\[/img\]#i";
      $replace='<img src="\\1" alt="" style="max-height:400px;max-width:500px"/>';
      $str=preg_replace($patern, $replace, $str); 
	  //$str=nl2br($str);
      return $str;
    }
  }

if(!empty($_GET["bbcode"])){
  $bb = new bbParser();
  echo $bb->getHtml($_GET["bbcode"]);
}

?>

