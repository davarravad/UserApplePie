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


// Displays user's name with link based on ID02_B
	global $site_url_link;
	echo "<a href='${site_url_link}member/$ID02_B/'>";
	echo get_up_info_mem_disp_name($ID02_B);
	echo "</a>";
?>