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


// Online Members Count
		$query_usr_online = "SELECT count(*) as total from ".$db_table_prefix."loggedusers";
		if ($result_usr_online = $mysqli->query("$query_usr_online")) {
			/* determine number of rows result set */
			$total_usr_online = $result_usr_online->fetch_row();
			$rows = $total_usr_online['0'];
			/* close result set */
			$result_usr_online->close();
		}

	if ($rows) {
		echo "<b><a href='${site_url_link}whosonline/'>Members Online</a></b>: $rows";
	}
	else {
		echo "<b>Members Online</b>: 0";
	}

?>

