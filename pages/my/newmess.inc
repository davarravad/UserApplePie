<?php

global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;

 require "models/members/getuserinfo.inc";


$query = "SELECT * FROM `".$db_table_prefix."inbox` WHERE `mto` = '$nname' AND `mread` = 'unread' ";

	if ($result = $mysqli->query("$query")) {

		/* determine number of rows result set */
		$rows = $result->num_rows;

		/* close result set */
		$result->close();
	}


	if ($rows >= "1") {
		echo " <strong><a href='${site_url_link}message/'><img src='/images/tazib_message_new.gif'> $rows</a></strong> ";
	}
	else {
		echo " <strong><a href='${site_url_link}message/'><img src='/images/tazib_message.gif'> 0</a></strong> ";
	}

?>
