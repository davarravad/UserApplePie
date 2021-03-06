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


// Page title
$stc_page_title = "UserApplePie Downloads";
// Page Description
$stc_page_description = "UserApplePie Downloads.  Get the latest version of UserApplePie.  Based on UserCake 2.0.2.";
	
// Run Header of page func
style_header_content($stc_page_title, $stc_page_description);
	
	echo "<div align='left'>";
	echo "Welcome to the UserApplePie Downloads page.";
	echo "<hr>";
	echo "<h3>UserApplePie 1.1</h3>";
	echo " - Stable Version Coming Soon. <br>";
	echo " - 12/17/2015 - UserApplePie v1.1.1-dev UnStable Release <a href='https://github.com/davarravad/UserApplePie/releases/tag/1.1.1-dev' target='_blank'>Download</a>";
	echo "<hr>";
	echo "<h3>UserApplePie Github</h3>";
	echo "You can get the latest daily build from our Github Repository.  However it may or may not be stable.";
	echo "<br>";
	echo " - <a href='https://github.com/davarravad/UserApplePie' target='_blank'>UserApplePie Github Repository</a>";
	echo "<hr>";
	echo "<h3>UserCake 2.0.2 Compatible Forum 1.0</h3>";
	echo " - <a href='https://github.com/davarravad/usercakeforum/releases/tag/v1.0.2' target='_blank'>Forum for UserCake v1.0.2</a>";
	echo "<br>";
	echo " - <a href='https://github.com/davarravad/usercakeforum' target='_blank'>Forum for UserCake Github Repository</a>";
	echo "</div>";
	
	
// Run Footer of page func
style_footer_content();

 ?>