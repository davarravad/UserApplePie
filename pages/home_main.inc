<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

/*
This is the default home page to visitors that are not logged in.
You can use this page as a template to create any other pages for your site.
*/

// Page title
$stc_page_title = "Welcome to $websiteName UserApplePie";
// Page Description
$stc_page_description = "Welcome to $websiteName home page. - $websiteUrl";



// Run Header of page func
style_header_content($stc_page_title, $stc_page_description);

	// Start of page content
	echo "
	Welcome to $websiteName!  <br><br>
	This website is based on UserCake.  I have created this website as a base for a project called UserApplePie.<br><br>
	The goal of this website is to make adding pages quick and easy with minimal effort.  <br><br>
	Check back soon for updates as this site is not yet fully functional.  
	";
	// End of page content

// Run Footer of page func
style_footer_content();

?>