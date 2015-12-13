<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($_POST['stat'])){ $stat = $_POST['stat']; }else{ $stat = ""; }


	if($stat == 'save'){
	
		require "pages/my/status/savecomment.inc";
		
	
	}else{
	
	
		require "pages/my/status/commentnew.inc";


	}
		
		echo "<br><Br>";

		require "pages/my/status/displaycomments.inc";



?>