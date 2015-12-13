<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
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
$stc_page_description = "";



// Run Header of page func
style_header_content($stc_page_title, $stc_page_description);

	// Start of page content
	echo "
	<strong>Welcome to UserApplePie's Mother Web Site.</strong><br>
	UserApplePie is a fully open source user management system.<hr>
	<div class='panel panel-info'>
		<div class='panel-heading'>
			UserApplePie v1.1.0 is here!
		</div>
		<div class='panel-body' style='text-align:center'>
			<h3>What's new?</h3>
			Bootstrap Enabled!<br>
			More mobile friendly!<br>
			Registration form updated!<br>
			CSRF Tokens updated!<br>
			Much more!
		</div>
	</div>
	<h3><a href='".$websiteUrl."Downloads/'>Download UserApplePie</a></h3><hr>
	UserApplePie was created as an improved version of <a href='http://usercake.com/' target='_blank'>UserCake 2.0.2</a>.<hr>
	The goal of UserApplePie is to create a simple to use User Management System based on MySQL and PHP.  <Br><br>
	Security functions have been updated and added. <Br><br>
	We have changed the site to behave like a web site portal.  Everything is opened from the index.php file. <br><br>
	Apache's mod_rewrite has enabled us to clean the URLs within the site.<br><br>
	ImageMagick has enabled us to allow profile photo uploads. <br>
	It resizes the photos to reduce the amount of storage space needed on a server.<br><br>
	You can visit the <a href='".$websiteUrl."Docs/'>Docs</a> page for detailed information on all Features.<hr>
	UserApplePie and <a href='http://www.usercake.com/' target='_blank'>UserCake</a> are fully opensource! You may download and re-distribute the code in any form.<br>
	A link back to the projects would be appreciated, but are not required.<br><br>
	UserApplePie is a non-profit project, however donations are greatly appreciated.<hr>
	If you need any assistance with UserApplePie, please read the <a href='".$websiteUrl."Docs/'>Docs</a> page 
	or go to our <a href='".$websiteUrl."Forum/'>Forum</a>.<br><br>
	Thanks You For Your Interest in UserApplePie!  Enjoy!
	";
	// End of page content

// Run Footer of page func
style_footer_content();

?>