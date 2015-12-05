<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($_POST['stat'])){ $stat = $_POST['stat']; }else{ $stat = ""; }



	if($stat == 'save'){
	
		require "pages/my/friendstatus/savecomment.inc";
		
	
	}else{
	
	
		require "pages/my/friendstatus/commentnew.inc";


	}
		
		echo "<br><Br>";

		require "pages/my/friendstatus/displaycomments.inc";


?>