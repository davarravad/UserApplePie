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


// Forum Functions

// Total Topics Display Functions
function total_topics_display($forum_id){
	global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;

	// Get all Categories from database
	$query = "SELECT * FROM ".$db_table_prefix."forum_posts WHERE `forum_id`='$forum_id' ";
	
	if ($result = $mysqli->query("$query")) {

		/* determine number of rows result set */
		$row_cnt = $result->num_rows;

		echo "<div class='btn btn-info btn-xs' style='margin-top: 5px'>";
		echo "Topics <span class='badge'>$row_cnt</span>";
		echo "</div>";

		/* close result set */
		$result->close();
	}

}

// Total Topic Replys Display Functions
function total_topic_replys_display($forum_id){
	global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;

	// Get all Categories from database
	$query = "SELECT * FROM ".$db_table_prefix."forum_posts_replys WHERE `fpr_id`='$forum_id' ";
	
	if ($result = $mysqli->query("$query")) {

		/* determine number of rows result set */
		$row_cnt = $result->num_rows;

		echo "<div class='btn btn-info btn-xs' style='margin-top: 3px'>";
		echo "Replies <span class='badge'>$row_cnt</span>";
		echo "</div>";

		/* close result set */
		$result->close();
	}

}

// Total Topic Replys Per Topic Display Functions
function total_topic_replys_display_a($forum_post_id){
	global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;

	// Get all Categories from database
	$query = "SELECT * FROM ".$db_table_prefix."forum_posts_replys WHERE `fpr_post_id`='$forum_post_id' ";
	
	if ($result = $mysqli->query("$query")) {

		/* determine number of rows result set */
		$row_cnt = $result->num_rows;

		echo "<div class='btn btn-info btn-xs' style='margin-top: 3px'>";
		echo "Replies <span class='badge'>$row_cnt</span>";
		echo "</div>";

		/* close result set */
		$result->close();
	}

}

?>