<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

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

	////Forum Topic Sweet Start
		if($sweet_location == "forum_posts"){
			
			$query_RP_FP = "SELECT * FROM `".$db_table_prefix."forum_posts` WHERE `forum_post_id`='$sweet_id' ";

			if($result_RP_FP = $mysqli->query($query_RP_FP)){
				$arr_RP_FP = $result_RP_FP->fetch_all(MYSQLI_BOTH);
				foreach($arr_RP_FP as $row_RP_FP)
				{
					$f_p_id = $row_RP_FP['forum_post_id'];
					$f_p_id_cat = $row_RP_FP['forum_id'];
					$f_p_title = $row_RP_FP['forum_title'];
					$f_p_timestamp = $row_RP_FP['forum_timestamp'];
					$f_p_user_id = $row_RP_FP['forum_user_id'];
					$f_p_status = $row_RP_FP['forum_status'];
					$tstamp = $row_RP_FP['forum_timestamp'];
					$f_p_user_name = get_user_name_2($f_p_user_id);
					
					$f_p_title = stripslashes($f_p_title);


					//Display how long ago this was posted
					unset($timestart);
					$timestart = "$sweet_timestamp";  //Time of post
					require_once "models/timediff.inc";
					$sweet_timestamp_ago = " " . dateDiff("now", "$timestart", 1) . " ago ";
					
					$ID02 = $sweet_userid;
					echo "<table width='100%' class='$bgcolor'>";
					echo "<tr><td>";
					echo "<a href='${site_url_link}member/$ID02/'>";
						require "pages/profile/userimage_small.inc";
					echo "</a>";
					echo "<strong> $sw_usernameB sweeted a Forum Topic..";
					echo "</td><td align=right>$sweet_timestamp_ago</td></tr>";
					echo "<tr><td colspan='2'> <hr>";
					echo "<a href='$sweet_url'>$f_p_title</a>. </strong>";
					echo "</td></tr></table><br>";
					unset($timestart, $timestamp);
				}
			}
			unset($arr2);
		}
	////Forum Topic Sweet End


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


			echo "<table width='100%'>";
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