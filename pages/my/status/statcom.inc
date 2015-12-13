<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($_POST['statcom'])){ $statcom = $_POST['statcom']; }else{ $statcom = ""; }


		require "pages/my/status/statdisplaycomments.inc";

	if($statcom == 'save'){
	
		require_once "pages/my/status/statsavecomment.inc";
		
	
	}else{
	
	
		require "pages/my/status/statcommentnew.inc";


	}
		
		




?>