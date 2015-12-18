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




require_once("external/config.php");
// Build Security for Current Page if Any
$cur_page_get = "pages/".$_GET['page'].".php";
if (!securePage($cur_page_get)){die();}

//Log the user out
if(isUserLoggedIn())
{
	$aulio_uid = $userIdme;
	add_user_logged_in_logout($aulio_uid);
	$loggedInUser->userLogOut();
}

if(!empty($websiteUrl)) 
{
	$add_http = "";
	
	if(strpos($websiteUrl,"http://") === false)
	{
		$add_http = "http://";
	}
	
	header("Location: ".$add_http.$websiteUrl);
	die();
}
else
{
	header("Location: http://".$_SERVER['HTTP_HOST']);
	die();
}	

?>

