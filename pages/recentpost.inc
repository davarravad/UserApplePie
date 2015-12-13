<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

unset($timestamp, $userId);
		if(isset($_GET['rc_view'])){ $rc_view = $_GET['rc_view']; }else{ $rc_view = ""; }

	//Check to see if user is logged in to display stats updates
	if(isUserLoggedIn())
	{


		//Check to see if user wants to see more posts    
		if(isset($_GET['offset'])){ $offset = $_GET['offset']; }

		//echo "($rc_view)";
    
		// no of elements per page 
    
		if(isset($offset)){
			$limitfriendstatus = "$offset";
		}else{
			$limitfriendstatus = "10"; 
		}

		require "pages/my/status/commentnew.inc";
		echo "<br>";

		// Order of data selected as from database
		// AS RP_01 - AS RP_02 - AS RP_03 - AS RP_04 - AS RP_05 - AS RP_06 - AS RP_07 - AS RP_08 - AS RP_09 - AS RP_10
		
		// Get recent status comments
		$q_status = "
		(SELECT 
			st.timestamp AS RP_01, 
			st.id AS RP_02, 
			st.com_uid AS RP_03, 
			st.com_name AS RP_04, 
			st.com_content AS RP_05, 
			st.com_id AS RP_06, 
			fr.userId1 AS RP_07, 
			fr.userId2 AS RP_08, 
			fr.status1 AS RP_09, 
			fr.status2 AS RP_10, 
			'status' AS post_type 
		FROM ".$db_table_prefix."status st
			LEFT JOIN ".$db_table_prefix."friend fr
				ON (st.com_id = fr.userId1 AND fr.userId2 = $userIdme)
				OR (st.com_id = fr.userId2 AND fr.userId1 = $userIdme)
			WHERE fr.status1 = '1' AND fr.status2 = '1'
				OR st.com_id = '$userIdme'
			GROUP BY st.id)
		";

		// Get Recent Status Comment Sub Comments
		$q_status_com = "
		(SELECT 
			sc.timestamp AS RP_01, 
			sc.id AS RP_02, 
			sc.statcom_uid AS RP_03, 
			sc.statcom_name AS RP_04, 
			sc.statcom_content AS RP_05, 
			sc.statcom_id AS RP_06, 
			f.userId1 AS RP_07, 
			f.userId2 AS RP_08, 
			f.status1 AS RP_09, 
			f.status2 AS RP_10, 
			'statcom' AS post_type 
		FROM ".$db_table_prefix."statcom sc
			JOIN (SELECT statcom_id,MAX(timestamp) timestamp
					FROM ".$db_table_prefix."statcom GROUP BY statcom_id) t
				ON t.statcom_id = sc.statcom_id
				AND t.timestamp = sc.timestamp
			LEFT JOIN ".$db_table_prefix."friend f
				ON (sc.statcom_uid = f.userId1 AND f.userId2 = $userIdme)
				OR (sc.statcom_uid = f.userId2 AND f.userId1 = $userIdme)
			WHERE f.status1 = '1' AND f.status2 = '1'
				OR sc.statcom_uid = '$userIdme'
			GROUP BY sc.statcom_id)
		";

		// Get Recent Sweets
		$s_status = "
		(SELECT 
			swe.timestamp AS RP_01, 
			swe.sid AS RP_02, 
			swe.sweet_location AS RP_03, 
			swe.sweet_sec_id AS RP_04, 
			swe.sweet_owner_userid AS RP_05, 
			swe.sweet_userid AS RP_06, 
			fri.userId1 AS RP_07, 
			fri.userId2 AS RP_08, 
			fri.status1 AS RP_09, 
			fri.status2 AS RP_10,
			'sweet' AS post_type 
		FROM ".$db_table_prefix."sweet swe
			LEFT JOIN ".$db_table_prefix."friend fri
				ON (swe.sweet_userid = fri.userId1 AND fri.userId2 = $userIdme)
				OR (swe.sweet_userid = fri.userId2 AND fri.userId1 = $userIdme)
			WHERE ( fri.status1 = '1' AND fri.status2 = '1'
				OR swe.sweet_userid = '$userIdme' )
				AND NOT swe.sweet_location = 'status' 
				AND NOT swe.sweet_location = 'statuscom'
				AND NOT swe.sweet_location = 'profilecomments_b' 
				AND NOT swe.sweet_location = 'writingcomments_b'
				AND NOT swe.sweet_location = 'forum_posts_replys'
			GROUP BY swe.sid)
		";

		// Get Recent Profile Comments
		$pc_status = "
		(SELECT 
			procom.timestamp AS RP_01, 
			procom.id AS RP_02, 
			procom.com_uid AS RP_03, 
			procom.com_name AS RP_04, 
			procom.com_content AS RP_05, 
			procom.com_id AS RP_06, 
			frie.userId1 AS RP_07, 
			frie.userId2 AS RP_08, 
			frie.status1 AS RP_09, 
			frie.status2 AS RP_10,
			'profilecomment' AS post_type 
		FROM ".$db_table_prefix."profilecomments procom
			LEFT JOIN ".$db_table_prefix."friend frie
				ON (procom.com_uid = frie.userId1 AND frie.userId2 = $userIdme)
				OR (procom.com_uid = frie.userId2 AND frie.userId1 = $userIdme)
			WHERE frie.status1 = '1' AND frie.status2 = '1'
				OR procom.com_uid = '$userIdme'
			GROUP BY procom.id)
		";

		// Get Recent Profile Comment Sub Comments
		$pc_statcom = "
		(SELECT 
			pcb.timestamp AS RP_01, 
			pcb.id AS RP_02, 
			pcb.statcom_uid AS RP_03, 
			pcb.statcom_name AS RP_04, 
			pcb.statcom_content AS RP_05, 
			pcb.statcom_id AS RP_06,
			f.userId1 AS RP_07, 
			f.userId2 AS RP_08, 
			f.status1 AS RP_09, 
			f.status2 AS RP_10,
			'profilestatcom' AS post_type 
		FROM ".$db_table_prefix."profilecomments_b pcb
			JOIN (SELECT statcom_id,MAX(timestamp) timestamp
				  FROM ".$db_table_prefix."profilecomments_b GROUP BY statcom_id) t
				ON t.statcom_id = pcb.statcom_id
				AND t.timestamp = pcb.timestamp
			LEFT JOIN ".$db_table_prefix."friend f
				ON (pcb.statcom_uid = f.userId1 AND f.userId2 = $userIdme)
				OR (pcb.statcom_uid = f.userId2 AND f.userId1 = $userIdme)
			WHERE f.status1 = '1' AND f.status2 = '1'
				OR pcb.statcom_uid = '$userIdme'
			GROUP BY pcb.statcom_id)
		";


	}else{
		$limitfriendstatus = "10"; 
	}
		
		if($rc_view){
			if($rc_view == "status"){ $query = "$q_status UNION ALL $q_status_com ORDER BY RP_01 DESC"; }
			if($rc_view == "sweets"){ $query = "$s_status ORDER BY RP_01 DESC"; }
			if($rc_view == "comments"){ $query = "$pc_statcom UNION ALL $pc_status ORDER BY RP_01 DESC"; }
		}else{

			if(isUserLoggedIn())
			{
			$query = "
				$q_status UNION ALL
				$q_status_com UNION ALL
				$s_status UNION ALL
				$pc_status UNION ALL
				$pc_statcom
				ORDER BY RP_01 DESC
			";
			}else{
				// Redirect user to not logged in homepage
				$redir_link_url = "$site_url_link";
				header("Location: $redir_link_url");
			}
		}
		
		$queryA = "$query LIMIT $limitfriendstatus";
		$queryB = "$query";
		
		
		if ($result = $mysqli->query("$queryB")) {

			/* determine number of rows result set */
			$num_rows_posts = $result->num_rows;

			/* close result set */
			$result->close();
		}
		
		// Get information from database
		$result = $mysqli->query($queryA);

		// Add error logger here just in case
		
		$arr_am = $result->fetch_all(MYSQLI_BOTH);
		
		foreach($arr_am as $row_am)
		{
			//sub.timestamp, sub.int, sub.usrida, sub.name, sub.color, sub.year, sub.make, sub.model, sub.type, null,
			$post_type = $row_am['post_type'];
			$timestamp = $row_am['RP_01'];
			$int = $row_am['RP_02'];
			$usrida = $row_am['RP_03'];
			$name = $row_am['RP_04'];
			$color = $row_am['RP_05'];
			$year = $row_am['RP_06'];
			$make = $row_am['RP_07'];
			$model = $row_am['RP_08'];
			$type = $row_am['RP_09'];
			$RP_10 = $row_am['RP_10'];

				$bgcolor = "epboxa";

			
			//echo "$usrida";
			//Testing timestamp
			$timestamp_p = $timestamp;
			//echo " ( timestamp = $timestamp_p ) ";
			
			if(isset($vm_id_a)){ $vm_id_a++; }else{ $vm_id_a = '1'; };

			echo "<a class='anchor' name='viewmore$vm_id_a'></a>";

			$color = stripslashes($color);
			$model = stripslashes($model);


			////Status Start
				if($post_type == "status"){
					require "pages/recentposts/rec_status.inc";
				}
			////Status End

			////Status Start
				if($post_type == "statcom"){
					require "pages/recentposts/rec_status_com.inc";
				}
			////Status End
			
			////Sweet Start
				if($post_type == "sweet"){
					require "pages/recentposts/rec_sweet.inc";
				}
			////Sweet End

			////Profile Comment Start
				if($post_type == "profilecomment"){
					require "pages/recentposts/rec_com_profile.inc";
				}
			////Profile Comment End

			////Profile Comment comments Start
				if($post_type == "profilestatcom"){
					require "pages/recentposts/rec_com_profile_com.inc";
				}
			////Profile Comment comments End
			
			////Vehicle Profile Comment Start
				if($post_type == "vpcom"){
					require "pages/recentposts/rec_com_vp.inc";
				}
			////Vehicle Profile Comment End

			////Vehicle Profile Comment comment Start
				if($post_type == "vpstatcom"){
					require "pages/recentposts/rec_com_vp_com.inc";
				}
			////Vehicle Profile Comment comment End
			
			////Vehicle Pic Comment Start
				if($post_type == "artcom"){
					require "pages/recentposts/rec_com_art.inc";
				}
			////Vehicle Pic Comment End

			////Vehicle Pic Comment comments Start
				if($post_type == "artstatcom"){
					require "pages/recentposts/rec_com_art_com.inc";
				}
			////Vehicle Pic Comment comments End
			
			////Club Comment Start
				if($post_type == "clubcom"){
					require "pages/recentposts/rec_com_club.inc";
				}
			////Club Comment End

			////Club Comment comments Start
				if($post_type == "clubstatcom"){
					require "pages/recentposts/rec_com_club_com.inc";
				}
			////Club Comment comments End
			
			////Club Event Start
				if($post_type == "clubevent"){
					require "pages/recentposts/rec_club_event.inc";
				}
			////Club Event End

			////Location Comment Start
				if($post_type == "loc_com"){
					require "pages/recentposts/rec_com_locations.inc";
				}
			////Location Comment End
			
			////Location Comment B Start
				if($post_type == "loc_com_b"){
					require "pages/recentposts/rec_com_locations_com.inc";
				}
			////Location Comment B End
			
			//Testing timestamp
			//echo " ( timestamp = $timestart ) <br>";

						//Clean up vars
						unset($timestart, $timestamp_p, $timestamp, $id, $int, $com_uid, $usrida, $com_name, $name, $com_content, $color, $com_id, $year);
						unset($statfriend, $userId1, $userId2, $userId1a, $userId2a);
						unset($sweet_location, $sweet_id, $sweet_userid, $sweet_url, $sweet_owner_userid);
						unset($sw_usernameB, $sw_username, $sw_user_sweeted, $sw_username888, $sw_username88, $ID02, $timestart);
						unset($com_uid, $com_id, $com_name, $com_content, $com_uid, $com_id, $com_name, $com_content );
						//Clean imgname string just in case its blank on a post
						unset($imgname);

		}  //End of main sql

	//Check to see if user is logged in and if there are later post they can view... then show link
	if(isUserLoggedIn())
	{
		$numofposts = $num_rows_posts;
		if(isset($vm_id_a)){}else{$vm_id_a = "0";}
		echo "<div class='well well-sm'>";
			echo "Currently Showing $vm_id_a of $numofposts Recent Posts";//testing
		echo "</div>";
		if( !isset($numofposts) ){$numofposts = "0";}else{
			//$plussome = ($num_rows - $numofposts);
 			//echo "<Br>$limitfriendstatus - $num_rows - $numofposts - $plussome <br>";
			if(isset($num_rows)){}else{ $num_rows = ""; }
			if($limitfriendstatus < $num_rows || $limitfriendstatus < $numofposts){
				$vm_id = $limitfriendstatus + 1;

				echo "<center>";
				echo "<span class='btn btn-default'>";
					echo "<a href=\"?rc_view=$rc_view&offset=" . ($limitfriendstatus + 10) . "#viewmore$vm_id\">Show More Recent Posts</a> ";
				echo "</span>";
				echo "</center> "; 
		
			}
		}
	}
?>