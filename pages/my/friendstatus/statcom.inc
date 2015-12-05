
<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($_POST['statcom'])){ $statcom = $_POST['statcom']; }else{ $statcom = ""; }


		require "pages/my/friendstatus/statdisplaycomments.inc";

	if($statcom == 'save'){
	
		require_once "pages/my/friendstatus/statsavecomment.inc";
		
	
	}else{
	
	
		require "pages/my/friendstatus/statcommentnew.inc";


	}
		
		




?>