<?
//views Main

global $mysqli, $site_url_link, $db_table_prefix;

if($addview == "yesaddview"){

	//Check to see if user has view post already
	// retrieve the row from the database
	$queryAS = "SELECT * FROM `".$db_table_prefix."views` WHERE `view_id`='$view_id' AND `view_location`='$view_location' AND `view_userid`='$view_userid' ";
   
	$resultAS = mysqli_query($GLOBALS["___mysqli_ston"],  $queryAS );

	// print out the results
	if( $resultAS && $contactAS = mysqli_fetch_object( $resultAS ) )
	{
		$user_view_status = "alreadyview";
	}else{
		$user_view_status = "newview";
	}
	//echo " ( $user_view_status ) "; //testing already view
	//End Check to see if user has view post

		if(isset($rate_id)){ $view_sec_id = $rate_id; }	
		if(isset($club_id)){ $view_sec_id = $club_id; }

}

	//Get total views for post
	$querySWT = "SELECT * FROM `".$db_table_prefix."views` WHERE `view_id`='$view_id' AND `view_location`='$view_location' ";
	$resultSWT = mysqli_query($GLOBALS["___mysqli_ston"], $querySWT)
	or die ("Couldn't ececute query. 98745");
	$num_views = mysqli_num_rows($resultSWT);
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
	unset($user_view_status);
?>