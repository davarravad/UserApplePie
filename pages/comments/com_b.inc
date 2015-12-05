<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($_POST['statcom'])){ $statcom = $_POST['statcom']; }else{ $statcom = ""; }

		require "pages/comments/com_b_display.inc";

	if($statcom == 'save'){
	
		//Do nothing
		
	}else{
	
		require "pages/comments/com_b_new.inc";
		
	}

?>