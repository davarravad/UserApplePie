<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Displays user's name with link based on ID02_B
	global $site_url_link;
	echo "<a href='${site_url_link}member/$ID02_B/'>";
	echo get_up_info_mem_disp_name($ID02_B);
	echo "</a>";
?>