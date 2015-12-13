<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isUserLoggedIn())
	{

		require "pages/profile/usernamememFL.inc";
		require "pages/profile/mainimagetiny.inc";

		if(isset($mainPicLinkA)){}else{ $mainPicLinkA = ""; }
		if(isset($mainPicLinkB)){}else{ $mainPicLinkB = ""; }
		
		$user_displayname = get_up_info_mem_disp_name($userIdme);

		$tazib_memberlink = "<table><tr><td>$mainPicLinkA <a href='${site_url_link}member/$userIdme/'><img class='rounded_5' border='0' height='20' src='/content/profile/thumb/${mainPic}'></a> $mainPicLinkB</td><td><strong> | <a href='${site_url_link}member/$userIdme/'> $user_displayname </a> | <a href='${site_url_link}logout/'>Logout</a> </strong></td></tr></table>";
		
	} else {

		$tazib_memberlink = "<a href='${site_url_link}login/' title='Login' alt='Login'>Login</a> | <a href='${site_url_link}register/' title='Register' alt='Register'>Register</a>";

	}

	
?>