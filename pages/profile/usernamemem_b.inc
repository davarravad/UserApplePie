<?php
// Displays user's name with link based on ID02_B
	global $site_url_link;
	echo "<a href='${site_url_link}member/$ID02_B/'>";
	echo get_up_info_mem_disp_name($ID02_B);
	echo "</a>";
?>