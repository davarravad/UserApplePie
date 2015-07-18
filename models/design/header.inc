<?php

//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

ob_start();

require_once("models/config.inc");
	//Get the Page the user has requested to view
	if(isset($_REQUEST['page']) || isset($_REQUEST['taz'])){
		if(isset($_REQUEST['page'])){ $taz = $_REQUEST['page']; }
		if(isset($_REQUEST['taz'])){ $taz = $_REQUEST['taz']; }
		if (!securePage($taz)){die();}
	}else{
		if (!securePage($_SERVER['PHP_SELF'])){die();}
	}


// Get user information
if(isset($loggedInUser->user_id)){
	$get_loggedin_uid = $loggedInUser->user_id;
}else{
	$get_loggedin_uid = "0";
}
$userId = $get_loggedin_uid;

require("models/members/funcs_user_info.inc");
require("models/functions.inc");
require("models/sublinks.inc");
require("models/funcs_styles.inc");

// Run the page handler
require("models/pagehand.inc");

// Gets the members zip code if they have one set
$userCity = get_up_info($userIdme, 'userCity');

// Setup where the top of the site is
echo"<a class='anchor' name='top'></a>";

// Doc Stuff
echo "
<!DOCTYPE html>
<!--[if lt IE 7 ]><html class='ie ie6' lang='en'> <![endif]-->
<!--[if IE 7 ]><html class='ie ie7' lang='en'> <![endif]-->
<!--[if IE 8 ]><html class='ie ie8' lang='en'> <![endif]-->
<!--[if (gte IE 9)|!(IE)]><!--><html lang='en'> <!--<![endif]-->
<head>
";

// Basic Header Info
echo "
<meta charset='utf-8'>
<meta name=\"msvalidate.01\" content=\"D60A2ED48DC27808B771821430C1922C\" />
<meta name=\"keywords\" content=\" ".$site_gbl_keywords." \">
";

//Sets the title and description of site if no ?=page, ?=profile, ?=club are requested
if(empty($_GET['page']) && empty($_GET['profile'])){
	echo "<meta name=\"description\" content=\" ".$site_gbl_descript." \">";
	echo "<meta name='author' content='DaVaR'>";
	echo "<meta http-equiv=\"Content-Language\" content=\"en\">";
}

// Mobile Meta
echo "
<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1'>
";

// Style Sheet CSS
echo "
<link href=\"/".$site_style_sel."/style.css\" rel=\"stylesheet\" type=\"text/css\" />
<script src=\"/SpryAssets/SpryMenuBar.js\" type=\"text/javascript\"></script>
<script src='/models/funcs.js' type='text/javascript'></script>
";

// IE 9 Settings
echo "
<!--[if lt IE 9]>
<script src='http://html5shim.googlecode.com/svn/trunk/html5.js'></script>
<![endif]-->
";

// Fav Icon Settings
echo "
<link rel='shortcut icon' href='images/favicon.ico'>
<link rel='apple-touch-icon' href='images/apple-touch-icon.png'>
<link rel='apple-touch-icon' sizes='72x72' href='images/apple-touch-icon-72x72.png'>
<link rel='apple-touch-icon' sizes='114x114' href='images/apple-touch-icon-114x114.png'>
";

// End of head
echo "</head>";

// Start the body
echo "<body>";

// Make sure the page var is set
if(isset($_REQUEST['page'])){ $taz = $_REQUEST['page']; }else{ $taz = ""; }

// Site content
echo "<div class='logo'>";

	echo "
	<table width='100%' border='0' cellpadding='0' cellspacing='0' class='top_header_fixed'><tr><td class='header_title' height='50px' colspan='2'>
		$websiteName
	</td></tr><tr><td height='25px' align='left' valign='middle' class='header_links' width='100%'>

		<ul id='MenuBar1' class='MenuBarHorizontal'>
			<li><a href='${site_url_link}' title='Home' class='MenuBarItemSubmenu'>Home</a></li>
			<li><a href='${site_url_link}Downloads/' title='Downloads'>Downloads</a></li>
			<li><a href='${site_url_link}Docs/' title='Docs'>Docs</a></li>
			<li><a href='${site_url_link}Forum/' title='Forum'>Forum</a></li>
	";
	if(isUserLoggedIn()){ 
	$user_displayname = get_up_info_mem_disp_name($userIdme);
	echo "	
		<li><a href='${site_url_link}community/' title='Community' class='MenuBarItemSubmenu'>Community</a>
		  <ul>
			<li><a href='${site_url_link}members/' title='View All Site Members' class='DD_UNLN'>Members</a><hr></li>
			
			<li><a href='${site_url_link}member/$user_displayname/' class='MenuBarItemSubmenu' title='View Your Member Profile'>My Profile</a><hr>
			  <ul>
				<li><a href='${site_url_link}member/$user_displayname/' title='View Your Member Profile'>View My Profile</a></li>
				<li><a href='${site_url_link}editprofilemain/' title='Edit Your Member Profile'>Edit Profile</a></li>
				<li><a href='${site_url_link}editprofilemain/editimages/' title='Edit Your Profile Images'>Edit Profile Images</a></li>
				<li><a href='${site_url_link}editprofilemain/picsubmit/' title='Upload Profile Images'>Upload Profile Images</a><hr></li>
				<li><a href='${site_url_link}editprofilemain/account/' title='Change Your Account Settings'>Account Settings</a></li>
				<li><a href='${site_url_link}editprofilemain/account_email/' title='Change Your Privacy and Email Settings'>Privacy Settings</a></li>
			  </ul>
		  </li>
			<li><a href='${site_url_link}message/'>My Messages</a></li>
			<li><a href='${site_url_link}community/mystatus/'>My Status</a></li>
			<li><a href='${site_url_link}community/myimages/'>My Images</a><hr></li>
			<li><a href='${site_url_link}community/myfriends/'>Friends</a></li>
			<li><a href='${site_url_link}community/friendstatus/'>Friends Status</a></li>
			<li><a href='${site_url_link}community/friendimages/'>Friends Images</a></li>
		  </ul>
		</li>
	";}
	echo "
		</ul>
		<script type='text/javascript'>
		var MenuBar1 = new Spry.Widget.MenuBar('MenuBar1', {imgDown:'/SpryAssets/SpryMenuBarDownHover.gif', imgRight:'/SpryAssets/SpryMenuBarRightHover.gif'});
		</script>
	</td>
	<td align='right' valign='middle' class='header_links' width=''>
	";

	echo "
		<table border='0' align='right' cellpadding='0' cellspacing='0'><tr><td>
		<ul id='MenuBar2' class='MenuBarHorizontal'>
	";
	if(isUserLoggedIn()){ 
			require "pages/profile/usernamememFL.inc";
			require "pages/profile/mainimagetiny.inc";

			if(isset($mainPicLinkA)){}else{ $mainPicLinkA = ""; }
			if(isset($mainPicLinkB)){}else{ $mainPicLinkB = ""; }
			
			$user_displayname = get_up_info_mem_disp_name($userIdme);

	echo "	
		   <li>  <img class='usr_main_img' border='0' height='18px' src='/content/profile/thumb/${mainPic}'></li>
		  <li> <a href='${site_url_link}member/$user_displayname/' title='$user_displayname' class='MenuBarItemSubmenu'>&nbsp;&nbsp;&nbsp; $user_displayname &nbsp;&nbsp;&nbsp;</a>
			<ul>
				<li><a href='${site_url_link}member/$user_displayname/' title='View Your Member Profile'>View My Profile</a></li>
				<li><a href='${site_url_link}editprofilemain/' title='Edit Your Member Profile'>Edit Profile</a></li>
				<li><a href='${site_url_link}editprofilemain/editimages/' title='Edit Your Profile Images'>Edit Profile Images</a></li>
				<li><a href='${site_url_link}editprofilemain/picsubmit/' title='Upload Profile Images'>Upload Profile Images</a><hr></li>
				<li><a href='${site_url_link}editprofilemain/account/' title='Change Your Account Settings'>Account Settings</a></li>
				<li><a href='${site_url_link}editprofilemain/account_email/' title='Change Your Privacy and Email Settings'>Privacy Settings</a></li>
			</ul>
		  </li>
		  <li><a href='${site_url_link}logout/' title='Logout'>Logout</a></li>
	";}else{
	echo "
		<li><a href='${site_url_link}Login/' title='Login'>Login</a></li>
		<li><a href='${site_url_link}Register/' title='Register'>Register</a></li>
	";
	}
	echo "
		</ul>
		<script type='text/javascript'>
		var MenuBar2 = new Spry.Widget.MenuBar('MenuBar2', {imgDown:'/SpryAssets/SpryMenuBarDownHover.gif', imgRight:'/SpryAssets/SpryMenuBarRightHover.gif'});
		</script>
		</td></tr></table>
	</td></tr></table>

	<div class='page_top_overflow'>
	<table width='100%' height='84px' border='0' cellpadding='0' cellspacing='0'><tr><td></td></tr></table>
	</div>
	"; //End of top nav bar
	
echo "</div>";

echo "
<div class='container'>

	<div class='full'>
		


		<div class='left'>
			
			<div class='content'>
";

// Check to see if user has updated their profile.
require("models/members/user_checks_func.inc");