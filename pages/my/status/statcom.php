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


if(isset($_POST['statcom'])){ $statcom = $_POST['statcom']; }else{ $statcom = ""; }


		require "pages/my/status/statdisplaycomments.php";

	if($statcom == 'save'){
	
		require_once "pages/my/status/statsavecomment.php";
		
	
	}else{
	
	
		require "pages/my/status/statcommentnew.php";


	}
		
		




?>