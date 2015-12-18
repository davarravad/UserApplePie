<?php
//////////////////////////////////
// UserApplePie Version: 1.1.1  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Security Feature to Disallow File to be opened directly.
// Only allows this file to be include by index.php
if(!defined('Page_Protection')){header("Location: ../");exit();}


if(isset($_POST['stat'])){ $stat = $_POST['stat']; }else{ $stat = ""; }


	if($stat == 'save'){
	
		require "pages/my/status/savecomment.php";
		
	
	}else{
	
	
		require "pages/my/status/commentnew.php";


	}
		
		echo "<br><Br>";

		require "pages/my/status/displaycomments.php";



?>