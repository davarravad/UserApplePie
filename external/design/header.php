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


ob_start();

require_once("./external/config.php");
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

require("./external/members/funcs_user_info.php");
require("./external/functions.php");
require("./external/sublinks.php");
require("./external/design/funcs_styles.php");

// Run the page handler
require("./external/pagehand.php");

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
<meta http-equiv='X-UA-Compatible' content='IE=edge'>
<meta name='viewport' content='width=device-width, initial-scale=1'>
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
    <!-- Bootstrap -->
	<link href=\"/".$site_style_sel."/css/bootstrap.min.css\" rel=\"stylesheet\" type=\"text/css\" />
	<link href=\"/".$site_style_sel."/css/temp_fix.css\" rel=\"stylesheet\" type=\"text/css\" />
	<!-- Custom styles for this template -->
	<link href=\"/external/design/common_style.css\" rel=\"stylesheet\" type=\"text/css\" />
";

// IE 9 Settings
echo "
    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
      <script src='https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js'></script>
      <script src='https://oss.maxcdn.com/respond/1.4.2/respond.min.js'></script>
    <![endif]-->
";

// Fav Icon Settings
echo "
<link rel='shortcut icon' href='/images/favicon.ico'>
";

// End of head
echo "</head>";

// Start the body
echo "<body>";

// Make sure the page var is set
if(isset($_REQUEST['page'])){ $taz = $_REQUEST['page']; }else{ $taz = ""; }

// Site content

	echo "
    <nav class='navbar navbar-default navbar-fixed-top'>
      <div class='container-fluid'>
        <div class='navbar-header'>
          <button type='button' class='navbar-toggle collapsed' data-toggle='collapse' data-target='#navbar' aria-expanded='false' aria-controls='navbar'>
            <span class='sr-only'>Toggle navigation</span>
            <span class='icon-bar'></span>
            <span class='icon-bar'></span>
            <span class='icon-bar'></span>
          </button>
		 <a class='navbar-brand' href='${site_url_link}' title='Home'>
          <img style='max-height: 20px; border-radius: 5px' alt='Brand' src='/images/logo.gif'>
         </a>
         <a class='navbar-brand' href='${site_url_link}' title='Home'>$websiteName</a>
        </div>
		
		<!-- Collect Left Main Links -->
        <div id='navbar' class='navbar-collapse collapse'>
          <ul class='nav navbar-nav'>
			<li "; if($taz == "Downloads"){echo "class='active'";} echo " ><a href='${site_url_link}Downloads/' title='Downloads'>Downloads</a></li>
			<li "; if($taz == "Docs"){echo "class='active'";} echo " ><a href='${site_url_link}Docs/' title='Docs'>Docs</a></li>
			<li "; if($taz == "Forum"){echo "class='active'";} echo " ><a href='${site_url_link}Forum/' title='Forum'>Forum</a></li>
";
				
			if(isUserLoggedIn()){ 
			$user_displayname = get_up_info_mem_disp_name($userIdme);
			echo "	
				<li class='dropdown'>
					<a href='#' title='Community' class='dropdown-toggle' data-toggle='dropdown' role='button' aria-haspopup='true' aria-expanded='false'>Community <span class='caret'></span></a>
					<ul class='dropdown-menu'>
						<li><a href='${site_url_link}community/' title='Community'> <span class='glyphicon glyphicon-globe' aria-hidden='true'></span> Community</a></li>
						<li><a href='${site_url_link}members/' title='View All Site Members' class='DD_UNLN'> <span class='glyphicon glyphicon-cloud' aria-hidden='true'></span> Members</a></li>
						<li role='separator' class='divider'></li>
						<li><a href='${site_url_link}message/'> <span class='glyphicon glyphicon-inbox' aria-hidden='true'></span> My Messages</a></li>
						<li><a href='${site_url_link}community/mystatus/'> <span class='glyphicon glyphicon-list' aria-hidden='true'></span> My Status</a></li>";
						if($enable_photos == "TRUE"){
							echo "<li><a href='${site_url_link}community/myimages/'> <span class='glyphicon glyphicon-picture' aria-hidden='true'></span> My Images</a></li>";
						}
						echo "<li role='separator' class='divider'></li>
						<li><a href='${site_url_link}community/myfriends/'> <span class='glyphicon glyphicon-user' aria-hidden='true'></span> Friends</a></li>
						<li><a href='${site_url_link}community/friendstatus/'> <span class='glyphicon glyphicon-list-alt' aria-hidden='true'></span> Friends Status</a></li>";
						if($enable_photos == "TRUE"){
							echo "<li><a href='${site_url_link}community/friendimages/'> <span class='glyphicon glyphicon-picture' aria-hidden='true'></span> Friends Images</a></li>";
						}
						echo "     
			";}
				
echo "			
              </ul>
            </li>
          </ul>


		  

	";

	echo "
          <ul class='nav navbar-nav navbar-right'>
	";
	if(isUserLoggedIn()){ 
			require "./pages/profile/usernamememFL.php";
			require "./pages/profile/mainimagetiny.php";
			if(isset($mainPicLinkA)){}else{ $mainPicLinkA = ""; }
			if(isset($mainPicLinkB)){}else{ $mainPicLinkB = ""; }
			$user_displayname = get_up_info_mem_disp_name($userIdme);

			echo "
			<li class='dropdown'>
					<a href='#' title='$user_displayname' class='dropdown-toggle' data-toggle='dropdown' role='button' aria-haspopup='true' aria-expanded='false'> ";					
						if($enable_photos == "TRUE"){
							echo "<span class='glyphicon' aria-hidden='true'><img style='max-height: 20px; border-radius: 5px' border='0' height='18px' src='/content/profile/thumb/${mainPic}'></span>";
						}else{
							echo "<span class='glyphicon glyphicon-user' aria-hidden='true'></span> ";
						}
					echo " $user_displayname ";
						get_total_messages_friend_requests($nname, $userIdme);
					echo "<span class='caret'></span></a>
					<ul class='dropdown-menu'>
						<li><a href='${site_url_link}message/' title='View Your Messages'> <span class='glyphicon glyphicon-inbox' aria-hidden='true'></span> Messages";
							get_total_messages($nname);
						echo "</a></li>
						<li><a href='${site_url_link}community/myfriends/' title='View Your Friend Requests'> <span class='glyphicon glyphicon-heart' aria-hidden='true'></span> Friend Requests";
							get_total_friend_requests($userIdme);
						echo "</a></li>
						<li role='separator' class='divider'></li>
						<li><a href='${site_url_link}member/$user_displayname/' title='View Your Member Profile'> <span class='glyphicon glyphicon-user' aria-hidden='true'></span> View My Profile</a></li>
						<li><a href='${site_url_link}editprofilemain/' title='Edit Your Member Profile'> <span class='glyphicon glyphicon-pencil' aria-hidden='true'></span> Edit Profile</a></li>";
						if($enable_photos == "TRUE"){
							echo "<li><a href='${site_url_link}editprofilemain/editimages/' title='Edit Your Profile Images'> <span class='glyphicon glyphicon-camera' aria-hidden='true'></span> Edit Profile Images</a></li>";
							echo "<li><a href='${site_url_link}editprofilemain/picsubmit/' title='Upload Profile Images'> <span class='glyphicon glyphicon-upload' aria-hidden='true'></span> Upload Profile Images</a><hr></li>";
						}
						echo "<li><a href='${site_url_link}editprofilemain/account/' title='Change Your Account Settings'> <span class='glyphicon glyphicon-briefcase' aria-hidden='true'></span> Account Settings</a></li>
						<li><a href='${site_url_link}editprofilemain/account_email/' title='Change Your Privacy and Email Settings'> <span class='glyphicon glyphicon-lock' aria-hidden='true'></span> Privacy Settings</a></li>
						";
						if(isUserLoggedIn() && is_admin()) {
							echo "<li role='separator' class='divider'></li>";
							echo "<li><a href='${site_url_link}UAP_Admin_Panel/' title='Admin Panel'> <span class='glyphicon glyphicon-cog' aria-hidden='true'></span> Admin Panel</a></li>";
						}
	echo "
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
		</ul></div></div></nav>
	"; //End of top nav bar


	
// Start of content
// Gives a proper display gap on a large screen
echo "<div class='visible-lg visible-md visible-sm' style='height: 70px'></div>";

// Gives a proper display gap on a extra Small screen
echo "<div class='visible-xs' style='height: 110px'></div>";

// Info Stuff container
echo "<div class='container'>";
	echo "<div class='row'>";

		// Check to see if user has updated their profile.
		require("./external/members/user_checks_func.php");

		//Site Adds Top
		require "./external/adds.php"; 

		echo "<div class='col-lg-12'>";
			//Shows a success_message if there is one.
			success_message();
		echo "</div>";
			
		//Admin Message
		require "./external/adminmessage.php";

	echo "</div>";
echo "</div>";

// Pages content container
echo "<div class='container'>";
	echo "<div class='row'>";
		
?>