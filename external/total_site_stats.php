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


// Get the totals for site stats
	// Give users more information with links

	// Notes: Add total online members with link to view all online members
	
	// Get the global info for site database and such
	global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;

		// Veh Pro Count
		$query_tvp = "SELECT count(*) as total from ".$db_table_prefix."submit";
		if ($result_tvp = $mysqli->query("$query_tvp")) {
			/* determine number of rows result set */
			$total_tvp = $result_tvp->fetch_row();
			$total_tvp = $total_tvp['0'];
			/* close result set */
			$result_tvp->close();
		}

		// Member Count
		$query_mem = "SELECT count(*) as total from ".$db_table_prefix."users "; // WHERE NOT `userStatus`='0'
		if ($result_mem = $mysqli->query("$query_mem")) {
			/* determine number of rows result set */
			$total_mem = $result_mem->fetch_row();
			$total_mem = $total_mem['0'];
			/* close result set */
			$result_mem->close();
		}

		// Forum Topics Count
		$query_diy_topics = "SELECT count(*) as total from ".$db_table_prefix."forum_posts";
		if ($result_diy_topics = $mysqli->query("$query_diy_topics")) {
			/* determine number of rows result set */
			$total_diy_topics = $result_diy_topics->fetch_row();
			$total_diy_topics = $total_diy_topics['0'];
			/* close result set */
			$result_diy_topics->close();
		}
		
		// Forum Replys Count
		$query_diy_replys = "SELECT count(*) as total from ".$db_table_prefix."forum_posts_replys";
		if ($result_diy_replys = $mysqli->query("$query_diy_replys")) {
			/* determine number of rows result set */
			$total_diy_replys = $result_diy_replys->fetch_row();
			$total_diy_replys = $total_diy_replys['0'];
			/* close result set */
			$result_diy_replys->close();
		}		
		
		// Online Members Count
		$query_usr_online = "SELECT count(*) as total from ".$db_table_prefix."loggedusers";
		if ($result_usr_online = $mysqli->query("$query_usr_online")) {
			/* determine number of rows result set */
			$total_usr_online = $result_usr_online->fetch_row();
			$total_usr_online = $total_usr_online['0'];
			/* close result set */
			$result_usr_online->close();
		}

		echo "<div class='panel panel-default'>";
			echo "<div class='panel-heading' style='font-weight: bold'>";
				echo "Site Stats";
			echo "</div>";
				echo "<ul class='list-group'>";
					echo "<li class='list-group-item'><a href='${site_url_link}members/' rel='nofollow'>Members: $total_mem</a></li>";
					echo "<li class='list-group-item'><a href='${site_url_link}whosonline/' rel='nofollow'>Members Online: $total_usr_online</a></li>";
					echo "<li class='list-group-item'><a href='${site_url_link}Forum/'>Forum Topics: $total_diy_topics</a></li>";
					echo "<li class='list-group-item'><a href='${site_url_link}Forum/'>Forum Replys: $total_diy_replys</a></li>";
				echo "</ul>";
			echo "</div>";
		echo "</div>";
?>