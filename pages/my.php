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


require_once("members/common.php");

if(isUserLoggedIn())
{

	if($usemobile == "TRUE"){ $tblw = "100%"; }else{ $tblw = "600px"; } //Sets width for mobile
	if($usemobile == "TRUE"){ $hpya = "mobile.php"; }else{ $hpya = "../"; } //Sets home page for mobile
	
	$userName = get_name();
	echo '<table border=0 align="center" cellpadding="8" width="$tblw">
			<tr><td	align="center">';
	
	if($userName != "")
	{
		echo "<h3 class='indented'>Welcome back $userName</h3>";
		echo "<BR><Br>";

		//Sends success message to session
		//Shows user success when they are redirected
		$success_msg = "You Have Successfully Logged In!";
		$_SESSION['success_msg'] = $success_msg;

		if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
			
			//Redirects the user
			global $site_url_link;
			$redir_link_url = "$hpya";
			
			// Redirect member to their post
			header("Location: $redir_link_url");
			exit;

		}	
	}
	else
	{
		echo "<h3 class='indented'>Welcome back to ".$websiteName."</h3>";
	}

	if(is_admin())
	{
		echo 'You are Admin on BiZat';
	}
	echo '</tr></table>';
				
		
}
else
{
	echo 'You have been logged out!';
}


?>

