<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Display how many views a topic has had

global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;

if($addview == "yesaddview"){

	//Check to see if user has view post already
	// retrieve the row from the database
	$queryAS = "SELECT * FROM `".$db_table_prefix."views` WHERE `view_id`='$view_id' AND `view_location`='$view_location' AND `view_userid`='$view_userid' ";
	if ($result = $mysqli->query("$queryAS")) {

		/* determine number of rows result set */
		$num_views = $result->num_rows;

		/* close result set */
		$result->close();
	}

	// print out the results
	if($num_views == "0")
	{
		$user_view_status = "newview";
	}else{
		$user_view_status = "alreadyview";
	}
	//echo " ( $num_views - $user_view_status ) "; //testing already view
	//echo " ( $queryAS ) "; // test user info
	unset ($num_views);
	//End Check to see if user has view post

}

	//Get total views for post

	// Get all Categories from database
	$query = "SELECT * FROM `".$db_table_prefix."views` WHERE `view_id`='$view_id' AND `view_location`='$view_location' ";
	if ($result = $mysqli->query("$query")) {

		/* determine number of rows result set */
		$num_views = $result->num_rows;

		/* close result set */
		$result->close();
	}
	//End total views for post
	
	if(isset($user_view_status)){
		if($user_view_status == "alreadyview"){
			//echo "Already Viewed";
		}else{
			//echo "First View";
				if($addview == "yesaddview"){
					require_once "models/viewsave.inc";
				}
		}
	}
	
	echo " ( <font color=green>$num_views views!</font> )";

	//echo " ( $view_location - $view_id - $view_userid - $view_url ) ";  //For testing	
	

	//Clear out data so it does not carry over to next post
	unset($user_view_status, $new_views);
?>