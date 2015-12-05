<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

/*
This is the default home page to visitors that are logged in.
You can use this page as a template to create any other pages for your site.
*/

	//Displays logged in user pannel
	if(isUserLoggedIn()){

		require("models/welcomemem.inc");

	}

	if(isUserLoggedIn()){}else{
		//Send member to home page
		$redir_link_home = "$websiteUrl";
		header("Location: $redir_link_home");
		exit;
	}
	if(isUserLoggedIn())
	{
		if(isset($_REQUEST['rc_view'])){ $rc_view = $_REQUEST['rc_view']; }else{ $rc_view = ""; }
		if($rc_view == "status"){ $link_status = "<font color=#E89104>Status</font>"; }
		else{ $link_status = "<a href='${site_url_link}rp/status/'>Status</a>"; };
		if($rc_view == "sweets"){ $link_sweets = "<font color=#E89104>Sweets</font>"; }
		else{ $link_sweets = "<a href='${site_url_link}rp/sweets/'>Sweets</a>"; };
		if($rc_view == "comments"){ $link_comments = "<font color=#E89104>Comments</font>"; }
		else{ $link_comments = "<a href='${site_url_link}rp/comments/'>Comments</a>"; };
	}

// Page title
$stc_page_title = "$websiteName Newest Content";
// Page Description
$stc_page_description = "Welcome to $websiteName. - $websiteUrl";
	
// Run Header of page func
style_header_content($stc_page_title, $stc_page_description);
	
	echo " <div class='epboxb'><center><strong> $link_status - $link_sweets - $link_comments</strong></center></div><br>";
	require "pages/recentpost.inc";
	
// Run Footer of page func
style_footer_content();

 ?>