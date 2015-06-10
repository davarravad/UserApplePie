<?
//Display recent sweets

	//reset vars to sweet
	$sid = $int;


	//Get info from sweet database
	// retrieve the row from the database
	$querySAS = "SELECT * FROM `".$db_table_prefix."sweet` WHERE `sid`='$sid' ";
   
	$resultSAS = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS );

	// print out the results
	if( $resultSAS && $contactSAS = mysqli_fetch_object( $resultSAS ) )
	{
		$sweet_id = $contactSAS -> sweet_id;	
		$sweet_sec_id = $contactSAS -> sweet_sec_id;	
		$sweet_sub = $contactSAS -> sweet_sub;	
		$sweet_location = $contactSAS -> sweet_location;	
		$sweet_userid = $contactSAS -> sweet_userid;	
		$sweet_url = $contactSAS -> sweet_url;	
		$sweet_owner_userid = $contactSAS -> sweet_owner_userid;
		$sweet_timestamp = $contactSAS -> timestamp;	
	}

//	echo "( sweet_id = $sweet_id )<br>";
//	echo "( sweet_sec_id = $sweet_sec_id )<br>";
//	echo "( sweet_sub = $sweet_sub )<br>";
//	echo "( sweet_location = $sweet_location )<br>";
//	echo "( sweet_userid = $sweet_userid )<br>";
//	echo "( sweet_url = $sweet_url )<br>";
//	echo "( sweet_owner_userid = $sweet_owner_userid )<br><br>";


	// Get the user that sweeted post name
	$sw_username = get_user_name_2($sweet_userid); 
	$sw_usernameB = "<a href='${site_url_link}member/$sweet_userid/'>$sw_username</a>";



	//Display post for each sweeted post
	////Vehicle Profile Start
		if($sweet_location == "submit"){
			// retrieve the row from the database
			$querySAS2 = "SELECT * FROM `".$db_table_prefix."submit` WHERE `int`='$sweet_id' ";
   
			$resultSAS2 = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS2 );
			$num_row33 = mysqli_num_rows($resultSAS2);
			if($num_row33 > 0){

			// print out the results
			if( $resultSAS2 && $contactSAS2 = mysqli_fetch_object( $resultSAS2 ) )
			{
				$int = $contactSAS2 -> int;	
				$usrida = $contactSAS2 -> usrida;	
				$name = $contactSAS2 -> name;	
				$color = $contactSAS2 -> color;	
				$year = $contactSAS2 -> year;	
				$make = $contactSAS2 -> make;	
				$model = $contactSAS2 -> model;	
				$type = $contactSAS2 -> type; 
				$sw_u_timestamp = $contactSAS2 -> timestamp;
			}

			$color = stripslashes($color);
			$model = stripslashes($model);

			//Display how long ago this was posted
			unset($timestart);
			$timestart = "$sweet_timestamp";  //Time of post
			require_once "models/timediff.inc";
			$sweet_timestamp_ago = " " . dateDiff("now", "$timestart", 1) . " ago ";
			
			$ID02 = $sweet_userid;
			require('pages/recentposts/userimage_small.inc');
			$sw_user_sweeted =  "<table width=100% height=18><tr><td align=left>$sw_user_sweeted_pic <strong> $sw_usernameB sweeted... </strong></td><td align=right>$sweet_timestamp_ago</td></tr></table><hr>";
			unset($timestart, $timestamp);
			$timestamp = $sw_u_timestamp;
			require "pages/recentposts/rec_veh_pro.inc";

			}else{
				//content missing, now to delete sweet from database

	
				//echo " - Content missing, Sweet to be removed ( $sid ) current url= $cur_pageURL - ";
					$queryUS = "DELETE FROM `".$db_table_prefix."sweet` WHERE `sid`='$sid' LIMIT 1";
					$resultsUS = mysqli_query($GLOBALS["___mysqli_ston"], $queryUS);

					// print out the results
					if( $resultsUS )
					{
						//echo( "Successfully deleted the entry.<br><br>" );
						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url='$cur_pageURL>";
						}
					}

			}
			unset($num_row33);


		}
	////Vehicle Profile End
	
	////Club Start
		if($sweet_location == "clubview"){
			// retrieve the row from the database
			$querySAS2 = "SELECT * FROM `".$db_table_prefix."club` WHERE `club_id`='$sweet_id' ";
   
			$resultSAS2 = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS2 );
			$num_row33 = mysqli_num_rows($resultSAS2);
			if($num_row33 > 0){

			// print out the results
			if( $resultSAS2 && $contactSAS2 = mysqli_fetch_object( $resultSAS2 ) )
			{
				$int = $contactSAS2 -> club_id;	
				$usrida = $contactSAS2 -> club_admin1;	
					
				$color = $contactSAS2 -> club_name;	
				$year = $contactSAS2 -> club_city;	
				$make = $contactSAS2 -> club_state;	
				$model = $contactSAS2 -> club_about;	
				$type = $contactSAS2 -> club_privacy; 
				$sw_u_timestamp = $contactSAS2 -> timestamp;
			}

			$color = stripslashes($color);
			$model = stripslashes($model);

			//Display how long ago this was posted
			unset($timestart);
			$timestart = "$sweet_timestamp";  //Time of post
			require_once "models/timediff.inc";
			$sweet_timestamp_ago = " " . dateDiff("now", "$timestart", 1) . " ago ";
			
			$ID02 = $sweet_userid;
			require('pages/recentposts/userimage_small.inc');
			$sw_user_sweeted =  "<table width=100% height=18><tr><td align=left>$sw_user_sweeted_pic <strong> $sw_usernameB sweeted... </strong></td><td align=right>$sweet_timestamp_ago</td></tr></table><hr>";
			unset($timestart, $timestamp);
			$timestamp = $sw_u_timestamp;
			require "pages/recentposts/rec_club.inc";

			}else{
				//content missing, now to delete sweet from database

	
				//echo " - Content missing, Sweet to be removed ( $sid ) current url= $cur_pageURL - ";
					$queryUS = "DELETE FROM `".$db_table_prefix."sweet` WHERE `sid`='$sid' LIMIT 1";
					$resultsUS = mysqli_query($GLOBALS["___mysqli_ston"], $queryUS);

					// print out the results
					if( $resultsUS )
					{
						//echo( "Successfully deleted the entry.<br><br>" );
						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url='$cur_pageURL>";
						}
					}

			}
			unset($num_row33);

		}
	////Club End
	
	////Vehicle Pic Start
		if($sweet_location == "art"){
			// retrieve the row from the database
			$querySAS2 = "SELECT * FROM `".$db_table_prefix."art` WHERE `id`='$sweet_id' ";
   
			$resultSAS2 = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS2 );
			$num_row33 = mysqli_num_rows($resultSAS2);
			if($num_row33 > 0){
			// print out the results
			if( $resultSAS2 && $contactSAS2 = mysqli_fetch_object( $resultSAS2 ) )
			{
				$int = $contactSAS2 -> id;	
				$usrida = $contactSAS2 -> usrida;	
				$name = $contactSAS2 -> name;	
				$color = $contactSAS2 -> type;	
				$year = $contactSAS2 -> title;	
				$make = $contactSAS2 -> imgname;	
				$model = $contactSAS2 -> content1;	
				$type = $contactSAS2 -> vehicle_id; 
				$sw_u_timestamp = $contactSAS2 -> timestamp;
			}

			$color = stripslashes($color);
			$model = stripslashes($model);

			//Display how long ago this was posted
			unset($timestart);
			$timestart = "$sweet_timestamp";  //Time of post
			require_once "models/timediff.inc";
			$sweet_timestamp_ago = " " . dateDiff("now", "$timestart", 1) . " ago ";
			
			$ID02 = $sweet_userid;
			require('pages/recentposts/userimage_small.inc');
			$sw_user_sweeted =  "<table width=100% height=18><tr><td align=left>$sw_user_sweeted_pic <strong> $sw_usernameB sweeted... </strong></td><td align=right>$sweet_timestamp_ago</td></tr></table><hr>";
			$timestamp = $sw_u_timestamp;
			require "pages/recentposts/rec_veh_pic.inc";
			unset($sw_u_timestamp, $sweet_timestamp);
			unset($timestart, $timestamp);
			}else{
				//content missing, now to delete sweet from database

	
				//echo " - Content missing, Sweet to be removed ( $sid ) current url= $cur_pageURL - ";
					$queryUS = "DELETE FROM `".$db_table_prefix."sweet` WHERE `sid`='$sid' LIMIT 1";
					$resultsUS = mysqli_query($GLOBALS["___mysqli_ston"], $queryUS);

					// print out the results
					if( $resultsUS )
					{
						//echo( "Successfully deleted the entry.<br><br>" );
						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url='$cur_pageURL>";
						}
					}

			}
			unset($num_row33);
		}
	////Vehicle Pic End

	//Display post for each sweeted comment post
	////Vehicle Profile Comment Start
		if($sweet_location == "vpcom"){
			// retrieve the row from the database
			$querySAS2 = "SELECT * FROM `".$db_table_prefix."submit` WHERE `int`='$sweet_sec_id' ";
   
			$resultSAS2 = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS2 );
			$num_row33 = mysqli_num_rows($resultSAS2);

			//Check to see if comment exist
			//echo " ( $sweet_url ... $sweet_id ) ";
			$querySAS2B = "SELECT * FROM `writingcomments` WHERE `id`='$sweet_id' ";
			$resultSAS2B = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS2B );
			$num_row33B = mysqli_num_rows($resultSAS2B);
			//echo " ( $num_row33 ... $num_row33B ) ";

			if($num_row33 > 0 && $num_row33B > 0){

			// print out the results
			if( $resultSAS2 && $contactSAS2 = mysqli_fetch_object( $resultSAS2 ) )
			{
				$int = $contactSAS2 -> int;	
				$usrida = $contactSAS2 -> usrida;	
				$name = $contactSAS2 -> name;	
				$color = $contactSAS2 -> color;	
				$year = $contactSAS2 -> year;	
				$make = $contactSAS2 -> make;	
				$model = $contactSAS2 -> model;	
				$type = $contactSAS2 -> type; 
				$sw_u_timestamp = $contactSAS2 -> timestamp;
			}

			$color = stripslashes($color);
			$model = stripslashes($model);

			//Display how long ago this was posted
			unset($timestart);
			$timestart = "$sweet_timestamp";  //Time of post
			require_once "models/timediff.inc";
			$sweet_timestamp_ago = " " . dateDiff("now", "$timestart", 1) . " ago ";
			
			$ID02 = $sweet_userid;
			require('pages/recentposts/userimage_small.inc');
			$sw_user_sweeted =  "<table width=100% height=18><tr><td align=left>
					$sw_user_sweeted_pic <strong> $sw_usernameB sweeted a <a href='$sweet_url'>comment</a> on... </strong>
					</td><td align=right>$sweet_timestamp_ago</td></tr></table><hr>";
			unset($timestart, $timestamp);
			$timestamp = $sw_u_timestamp;
			//$int = $sweet_owner_userid;
			require "pages/recentposts/rec_veh_pro.inc";


			}else{
				//content missing, now to delete sweet from database

	
				//echo " - Content missing, Sweet to be removed ( $sid ) current url= $cur_pageURL - ";
					$queryUS = "DELETE FROM `".$db_table_prefix."sweet` WHERE `sid`='$sid' LIMIT 1";
					$resultsUS = mysqli_query($GLOBALS["___mysqli_ston"], $queryUS);

					// print out the results
					if( $resultsUS )
					{
						//echo( "Successfully deleted the entry.<br><br>" );
						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url='$cur_pageURL>";
						}
					}

			}
			unset($num_row33);


		}
	////Vehicle Profile Comment End
	
	////Club Comment Start
		if($sweet_location == "club"){
			// retrieve the row from the database
			$querySAS2 = "SELECT * FROM `".$db_table_prefix."club` WHERE `club_id`='$sweet_sec_id' ";
   
			$resultSAS2 = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS2 );
			$num_row33 = mysqli_num_rows($resultSAS2);

			//Check to see if comment exist
			//echo " ( $sweet_url ... $sweet_id ) ";
			$querySAS2B = "SELECT * FROM `clubcomments` WHERE `id`='$sweet_id' ";
			$resultSAS2B = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS2B );
			$num_row33B = mysqli_num_rows($resultSAS2B);

			//echo " ( $num_row33 ... $num_row33B ) ";

			if($num_row33 > 0 && $num_row33B > 0){			

			// print out the results
			if( $resultSAS2 && $contactSAS2 = mysqli_fetch_object( $resultSAS2 ) )
			{
				$int = $contactSAS2 -> club_id;	
				$usrida = $contactSAS2 -> club_admin1;	
				$color = $contactSAS2 -> club_name;	
				$year = $contactSAS2 -> club_city;	
				$make = $contactSAS2 -> club_state;	
				$model = $contactSAS2 -> club_about;	
				$type = $contactSAS2 -> club_privacy; 
				$sw_u_timestamp = $contactSAS2 -> timestamp;
			}

			$color = stripslashes($color);
			$model = stripslashes($model);

			//Display how long ago this was posted
			unset($timestart);
			$timestart = "$sweet_timestamp";  //Time of post
			require_once "models/timediff.inc";
			$sweet_timestamp_ago = " " . dateDiff("now", "$timestart", 1) . " ago ";
			
			$ID02 = $sweet_userid;
			require('pages/recentposts/userimage_small.inc');
			$sw_user_sweeted =  "<table width=100% height=18><tr><td align=left>
					$sw_user_sweeted_pic <strong> $sw_usernameB sweeted a <a href='$sweet_url'>comment</a> on... </strong>
					</td><td align=right>$sweet_timestamp_ago</td></tr></table><hr>";
			unset($timestart, $timestamp);
			$timestamp = $sw_u_timestamp;
			require "pages/recentposts/rec_club.inc";


			}else{
				//content missing, now to delete sweet from database

	
				
					$queryUS = "DELETE FROM `".$db_table_prefix."sweet` WHERE `sid`='$sid' LIMIT 1";
					$resultsUS = mysqli_query($GLOBALS["___mysqli_ston"], $queryUS);

					// print out the results
					if( $resultsUS )
					{
						//echo( "Successfully deleted the entry.<br><br>" );
						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){ 
							echo " - Content missing, Sweet to be removed ( $sid ) current url= $cur_pageURL - ";
							echo "<br> - DEBUG SITE ON - <BR>"; 
						}else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url='$cur_pageURL>";
						}
					}

			}
			unset($num_row33);


		}
	////Club Comment End
	
	////Vehicle Pic Comment Start
		if($sweet_location == "artcom"){
			// retrieve the row from the database
			$querySAS2 = "SELECT * FROM `".$db_table_prefix."art` WHERE `id`='$sweet_sec_id' ";
   
			$resultSAS2 = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS2 );
			$num_row33 = mysqli_num_rows($resultSAS2);

			//Check to see if comment exist
			//echo " ( $sweet_url ... $sweet_id ) ";
			$querySAS2B = "SELECT * FROM `artcomments` WHERE `id`='$sweet_id' ";
			$resultSAS2B = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS2B );
			$num_row33B = mysqli_num_rows($resultSAS2B);
			//echo " ( $num_row33 ... $num_row33B ) ";

			if($num_row33 > 0 && $num_row33B > 0){
			
			// print out the results
			if( $resultSAS2 && $contactSAS2 = mysqli_fetch_object( $resultSAS2 ) )
			{
				$int = $contactSAS2 -> id;	
				$usrida = $contactSAS2 -> usrida;	
				$name = $contactSAS2 -> name;	
				$color = $contactSAS2 -> type;	
				$year = $contactSAS2 -> title;	
				$make = $contactSAS2 -> imgname;	
				$model = $contactSAS2 -> content1;	
				$type = $contactSAS2 -> vehicle_id; 
				$sw_u_timestamp = $contactSAS2 -> timestamp;
			}

			$color = stripslashes($color);
			$model = stripslashes($model);

			//Display how long ago this was posted
			unset($timestart);
			$timestart = "$sweet_timestamp";  //Time of post
			require_once "models/timediff.inc";
			$sweet_timestamp_ago = " " . dateDiff("now", "$timestart", 1) . " ago ";
			
			$ID02 = $sweet_userid;
			require('pages/recentposts/userimage_small.inc');
			$sw_user_sweeted =  "<table width=100% height=18><tr><td align=left>
					$sw_user_sweeted_pic <strong> $sw_usernameB sweeted a <a href='$sweet_url'>comment</a> on... </strong>
					</td><td align=right>$sweet_timestamp_ago</td></tr></table><hr>";
			unset($timestart, $timestamp);
			$timestamp = $sw_u_timestamp;
			require "pages/recentposts/rec_veh_pic.inc";

			}else{
				//content missing, now to delete sweet from database

	
				
					$queryUS = "DELETE FROM `".$db_table_prefix."sweet` WHERE `sid`='$sid' LIMIT 1";
					$resultsUS = mysqli_query($GLOBALS["___mysqli_ston"], $queryUS);

					// print out the results
					if( $resultsUS )
					{
						//echo( "Successfully deleted the entry.<br><br>" );
						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){
							echo "<br> - DEBUG SITE ON - <BR>"; 
							echo " - Content missing, Sweet to be removed ( $sid ) current url= $cur_pageURL - ";
						}else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url='$cur_pageURL>";
						}
					}

			}
			unset($num_row33);

		}
	////Vehicle Pic Comment End

	////Profile Comment Start
		if($sweet_location == "profile"){

			//Display how long ago this was posted
			unset($timestart);
			$timestart = "$sweet_timestamp";  //Time of post
			require_once "models/timediff.inc";
			$sweet_timestamp_ago = " " . dateDiff("now", "$timestart", 1) . " ago ";
			
			$ID02 = $sweet_userid;
			require('pages/recentposts/userimage_small.inc');
			$sw_user_sweeted =  "<table width=100% height=18><tr><td align=left>
					$sw_user_sweeted_pic <strong> $sw_usernameB sweeted a <a href='${site_url_link}member/$sweet_sec_id#comment$sweet_id'>comment</a> on... </strong>
					</td><td align=right>$sweet_timestamp_ago</td></tr></table><hr>";
			unset($timestart, $timestamp);
			if(isset($sw_u_timestamp)){}else{$sw_u_timestamp = "";}
			$timestamp = $sw_u_timestamp;


			//Get the user that was sweeted name
			// retrieve the row from the database
			$querySAS8 = "SELECT ".$db_table_prefix."users.userName FROM `".$db_table_prefix."users` WHERE `userId`='$sweet_sec_id' ";
			$resultSAS8 = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS8 );
			
			$querySAS33 = "SELECT ".$db_table_prefix."profilecomments.id FROM `".$db_table_prefix."profilecomments` WHERE `id`='$sweet_id' ";
			$resultSAS33 = mysqli_query($GLOBALS["___mysqli_ston"],  $querySAS33 );
			$num_row33 = mysqli_num_rows($resultSAS33);
			if($num_row33 > 0){
		
			// print out the results
			if( $resultSAS8 && $contactSAS8 = mysqli_fetch_object( $resultSAS8 ) )
			{
				    $sw_usernameB = $contactSAS8 -> userName;	
			}
			$sw_usernameC = "<a href='${site_url_link}member/$sweet_sec_id'>$sw_usernameB</a>";


			echo "<table width=$tblw500>";
			echo "<tr><td class='$bgcolor'>";
			echo "$sw_user_sweeted";
			$ID02 = $sweet_sec_id;
			echo "<a href='${site_url_link}member/$ID02/'>";
				require "pages/profile/userimage_small.inc";
			echo "</a>";
			echo " $sw_usernameC";
			echo "'s Profile";
			echo "</td></tr></table><br>";

			}else{
				//content missing, now to delete sweet from database

	
				//echo " - Content missing, Sweet to be removed ( $sid ) current url= $cur_pageURL - ";
					$queryUS = "DELETE FROM `".$db_table_prefix."sweet` WHERE `sid`='$sid' LIMIT 1";
					$resultsUS = mysqli_query($GLOBALS["___mysqli_ston"], $queryUS);

					// print out the results
					if( $resultsUS )
					{
						//echo( "Successfully deleted the entry.<br><br>" );
						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url='$cur_pageURL>";
						}
					}

			}
			unset($num_row33);


		}
	////Profile Comment End



unset($sweet_id, $sweet_sec_id, $sweet_sub, $sweet_location, $sweet_userid, $sweet_url, $sweet_owner_userid, $int, $userida, $name, $color, $year, $make, $model, $type);
unset($sw_usernameB, $sw_user_sweeted, $sw_user_sweeted_pic, $sweet_timestamp, $sweet_timestamp_ago);


?>