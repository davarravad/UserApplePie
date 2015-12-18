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


global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;


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
