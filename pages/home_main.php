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
	<div class='row'>
		<div class='col-lg-6 col-md-6 col-sm-6'>
			<div class='panel panel-primary'>
				<div class='panel-heading' style='text-align:center'>
					UserApplePie v1.1.1!
				</div>
				<div class='panel-body' style='text-align:center'>
					<h4>What's new?</h4>
					Bootstrap Enabled!<br>
					More mobile friendly!<br>
					Registration form updated!<br>
					CSRF Tokens updated!<br>
					Better Page Protection! <br>
					And Much more! <br><br>
					
					<h4>Coming Soon!</h4>
					Server Friendly URLs <br>
					Full MySQL PDO Usage <br>
					Better Forum Administration <br>
					And Much More!
				</div>
			</div>
		</div>
		<div class='col-lg-6 col-md-6 col-sm-6'>
			<div class='panel panel-primary'>
				<div class='panel-heading' style='text-align:center'>
					Features!
				</div>
				<div class='panel-body' style='text-align:center'>
					Bootstrap Responsive Design. <br>
					Forum. <Br>
					User Profiles with Photos. <Br>
					Friends. <br>
					Status Updates. <br>
					Status Comments. <br>
					Clean URL Links. <br>
					Smart Registration. <br>
					Sweets feature. <br>
					Advanced User Account Settings. <br>
					Private Messages. <br>
					Member profile comments. <br>
					Added Security Functions. <br>
					Admin Panel. <br>
					And Much More!
				</div>
			</div>
		</div>
	</div>
	<div class=''>
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
	</div>
	";
	// End of page content

// Run Footer of page func
style_footer_content();

?>