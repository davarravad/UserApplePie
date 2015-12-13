<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Sweets Main

global $mysqli, $site_url_link, $db_table_prefix;

//Checks to see if user is loged in
if(isUserLoggedIn())
{

	//Check to see if user has sweet post already
	// retrieve the row from the database
	$queryAS = "SELECT * FROM `".$db_table_prefix."sweet` WHERE `sweet_id`='$sweet_id' AND `sweet_location`='$sweet_location' AND `sweet_userid`='$sweet_userid' ";
   
	$resultAS = mysqli_query($GLOBALS["___mysqli_ston"],  $queryAS );

	// print out the results
	if( $resultAS && $contactAS = mysqli_fetch_object( $resultAS ) )
	{
		$user_sweet_status = "alreadysweet";
	}
	//echo " ( $user_sweet_status ) "; //testing already sweet
	//End Check to see if user has sweet post

		if(isset($rate_id)){ $sweet_sec_id = $rate_id; }	
		if(isset($club_id)){ $sweet_sec_id = $club_id; }
		if(isset($sweet_sec_id)){}else{ $sweet_sec_id = ""; }

	$sweet_formS = "<form enctype='multipart/form-data' action='${site_url_link}sweetsave' method='POST' class='sweetform' onsubmit='sweet.disabled = true; return true;'>";
	$sweet_button = "
		<input type='hidden' name='sweet_sub' value='sweet' />
		<input type='hidden' name='sweet_id' value='$sweet_id' />
		<input type='hidden' name='sweet_sec_id' value='$sweet_sec_id' />
		<input type='hidden' name='sweet_location' value='$sweet_location' />
		<input type='hidden' name='sweet_userid' value='$sweet_userid' />
		<input type='hidden' name='sweet_url' value='$sweet_url' />
		<input type='hidden' name='sweet_owner_userid' value='$sweet_owner_userid' />
		<button type='submit' class='btn btn-success btn-xs' value='Sweet' name='sweet' style='margin-bottom: 5px' data-loading-text='Please wait...' >Sweet</button>
	";
	$unsweet_button = "
		<input type='hidden' name='sweet_sub' value='unsweet' />
		<input type='hidden' name='sweet_id' value='$sweet_id' />
		<input type='hidden' name='sweet_location' value='$sweet_location' />
		<input type='hidden' name='sweet_userid' value='$sweet_userid' />
		<input type='hidden' name='sweet_url' value='$sweet_url' />
		<button type='submit' class='btn btn-danger btn-xs' value='UnSweet' name='sweet' style='margin-bottom: 5px' data-loading-text='Please wait...' >UnSweet</button>
	";
	$sweet_formE = "</form>";

//End Not Loged In Check
}
	

	//Get total Sweets for post
	$querySWT = "SELECT * FROM `".$db_table_prefix."sweet` WHERE `sweet_id`='$sweet_id' AND `sweet_location`='$sweet_location' ";
	$resultSWT = mysqli_query($GLOBALS["___mysqli_ston"], $querySWT)
	or die ("Couldn't ececute query. Sweet 342");
	$num_sweets = mysqli_num_rows($resultSWT);
	//End total Sweets for post

	if(isset($sweet_formS)){
		echo "$sweet_formS";
			// create multi sessions
			if(isset($session_token_num)){
				$session_token_num = $session_token_num + 1;
			}else{
				$session_token_num = "1";
			}
		form_token();
	}

	if(isset($user_sweet_status)){}else{ $user_sweet_status = ""; }

	if($user_sweet_status == "alreadysweet"){
		echo "$unsweet_button";
			if($sweet_location == "forum_posts_replys" || $sweet_location == "forum_posts"){
				echo " ";
			}
	}else{
		if(isset($sweet_button)){ echo "$sweet_button"; }
			if($sweet_location == "forum_posts_replys" || $sweet_location == "forum_posts"){
				echo " ";
			}
	}
	
	if(isset($sweet_formE)){
		echo "$sweet_formE";
	}

	if($num_sweets == '0'){
		echo " <button type='button' class='btn btn-default btn-xs' style='margin-bottom: 5px'>No Sweets</button> ";
	}elseif($num_sweets == '1'){
		echo " <button type='button' class='btn btn-default btn-xs' style='margin-bottom: 5px'>1 Sweet</button> ";
	}else{
		echo " <button type='button' class='btn btn-default btn-xs' style='margin-bottom: 5px'>$num_sweets Sweets</button> ";
	}
		
	//echo " ( $sweet_location - $sweet_id - $sweet_userid - $sweet_url ) ";  //For testing	


	//Clear out data so it does not carry over to next post
	unset($user_sweet_status);
?>