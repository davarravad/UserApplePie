<!DOCTYPE html>
	<!--[if lt IE 7 ]><html class='ie ie6' lang='en'> <![endif]-->
	<!--[if IE 7 ]><html class='ie ie7' lang='en'> <![endif]-->
	<!--[if IE 8 ]><html class='ie ie8' lang='en'> <![endif]-->
	<!--[if (gte IE 9)|!(IE)]><!--><html lang='en'> <!--<![endif]-->

	
	
<?php

	//Set the site style to use
	$site_style_sel = "default";

	// Gets the members zip code if they have one set
	$userCity = get_up_info($userIdme, 'userCity');

	// Setup where the top of the site is
	echo"<a class='anchor' name='top'></a>";

	// Setup all the html stuff
	echo "
	<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">
	<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">
	<head>

	<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1'>
	<!--[if lt IE 9]>
	<script src='http://html5shim.googlecode.com/svn/trunk/html5.js'></script>
	<![endif]-->
	<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />
	<title>".$websiteName."</title>
	<link href='/style/".$site_style_sel."/default.css' rel='stylesheet' type='text/css' />
	<script src='/models/funcs.js' type='text/javascript'>
	</script>";

	echo "
		<script src=\"/SpryAssets/SpryMenuBar.js\" type=\"text/javascript\"></script>
		<link href=\"/style/".$site_style_sel."/style.css\" rel=\"stylesheet\" type=\"text/css\" />
	";
	
	//Sets the title and description of site if no ?=page, ?=profile, ?=club are requested
	if(empty($_GET['page']) && empty($_GET['profile']) && empty($_GET['club']) && empty($_GET['Club'])){
		
		echo "<meta name=\"description\" content=\" ".$site_gbl_descript." \">";
		echo "<meta http-equiv=\"Content-Language\" content=\"en\">";
	}

	echo "
	<link rel=\"shortcut icon\" href=\"/images/favicon.ico\" type=\"image/x-icon\" />
	<meta name=\"msvalidate.01\" content=\"D60A2ED48DC27808B771821430C1922C\" />
	<meta name=\"keywords\" content=\" ".$site_gbl_keywords." \">";

	echo "</head>";

	echo "<body>";

	if(isset($_REQUEST['page'])){ $taz = $_REQUEST['page']; }else{ $taz = ""; }
	
	//Top Navigation bar
	echo "

<table width='100%' border='0' cellpadding='0' cellspacing='0' class='top_header_fixed'><tr><td class='header_title' height='50px' colspan='2'>
	<img src=\"/images/tazib_top_header.gif\" width=\"700\" height=\"50\" alt=\"$websiteName\" longdesc=\"http://www.cartruckclubs.com\" />
</td></tr><tr><td height='25px' align='left' valign='middle' class='header_links' width='100%'>

    <ul id='MenuBar1' class='MenuBarHorizontal'>
      <li><a href='${site_url_link}' title='Home' class='MenuBarItemSubmenu'>Home</a>
      </li>
 

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
            <li><a href='${site_url_link}editprofilemain/picsubmit/' title='Upload Profile Images'>Upload Profile Images</a></li>
            <li><a href='${site_url_link}editprofilemain/editvehicles/' title ='Edit Your Vehicles'>Edit Vehicles</a><hr></li>
            <li><a href='${site_url_link}editprofilemain/account/' title='Change Your Account Settings'>Account Settings</a></li>
			<li><a href='${site_url_link}editprofilemain/account_email/' title='Change Your Privacy and Email Settings'>Privacy Settings</a></li>
          </ul>
      </li>
        <li><a href='${site_url_link}message/'>My Messages</a></li>
        <li><a href='${site_url_link}community/mystatus/'>My Status</a></li>
        <li><a href='${site_url_link}community/myvehicles/'>My Vehicles</a></li>
        <li><a href='${site_url_link}community/myimages/'>My Images</a><hr></li>
        <li><a href='${site_url_link}community/myfriends/'>Friends</a></li>
        <li><a href='${site_url_link}community/friendstatus/'>Friends Status</a></li>
        <li><a href='${site_url_link}community/friendvehicles/'>Friends Vehicles</a></li>
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
            <li><a href='${site_url_link}editprofilemain/picsubmit/' title='Upload Profile Images'>Upload Profile Images</a></li>
            <li><a href='${site_url_link}editprofilemain/editvehicles/' title ='Edit Your Vehicles'>Edit Vehicles</a><hr></li>
            <li><a href='${site_url_link}editprofilemain/account/' title='Change Your Account Settings'>Account Settings</a></li>
			<li><a href='${site_url_link}editprofilemain/account_email/' title='Change Your Privacy and Email Settings'>Privacy Settings</a></li>
        </ul>
      </li>
      <li><a href='${site_url_link}logout/' title='Logout from Site'>Logout</a></li>
";}else{
echo "
	<li><a href='${site_url_link}Login/' title='Logout from Site'>Login</a></li>
	<li><a href='${site_url_link}Register/' title='Logout from Site'>Register</a></li>
";
}
echo "
    </ul>
    <script type='text/javascript'>
    var MenuBar2 = new Spry.Widget.MenuBar('MenuBar2', {imgDown:'/SpryAssets/SpryMenuBarDownHover.gif', imgRight:'/SpryAssets/SpryMenuBarRightHover.gif'});
    </script>
    </td></tr></table>
</td></tr></table>

<table width='500px' height='84px' border='0' cellpadding='0' cellspacing='0'><tr><td></td></tr></table>

"; //End of top nav bar



?>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td align="CENTER" valign="TOP" class="main_content_table" width="100%">

<?php	
	
	
	if(isUserLoggedIn()){
		// Create user profile is not one already
		check_create_user_profile($userIdme);
	}
	
							//User Checks Function
							require "models/members/user_checks_func.inc";
	
?>