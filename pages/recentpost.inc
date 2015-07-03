<?php
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

//Status Comments		
$q_status = "
(SELECT 
st.timestamp, 
st.id, 
st.com_uid, 
st.com_name, 
st.com_content, 
st.com_id, 
fr.userId1, 
fr.userId2, 
fr.status1, 
fr.status2, 
'status' AS post_type FROM ".$db_table_prefix."status st
LEFT JOIN ".$db_table_prefix."friend fr
ON (st.com_id = fr.userId1 AND fr.userId2 = $userIdme)
OR (st.com_id = fr.userId2 AND fr.userId1 = $userIdme)
WHERE fr.status1 = '1' AND fr.status2 = '1'
OR st.com_id = '$userIdme'
GROUP BY st.id)
";

//Status Comments Sub Comments
$q_status_com = "
(SELECT 
	sc.timestamp, sc.id, sc.statcom_uid, sc.statcom_name, 
	sc.statcom_content, sc.statcom_id, 
	f.userId1, f.userId2, f.status1, f.status2, 
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

//Sweets
$s_status = "
(SELECT swe.timestamp, swe.sid, 
swe.sweet_location, swe.sweet_sec_id, 
swe.sweet_owner_userid, swe.sweet_userid, 
fri.userId1, fri.userId2, 
fri.status1, fri.status2,
'sweet' AS post_type FROM ".$db_table_prefix."sweet swe
LEFT JOIN ".$db_table_prefix."friend fri
ON (swe.sweet_userid = fri.userId1 AND fri.userId2 = $userIdme)
OR (swe.sweet_userid = fri.userId2 AND fri.userId1 = $userIdme)
WHERE ( fri.status1 = '1' AND fri.status2 = '1'
OR swe.sweet_userid = '$userIdme' )
AND NOT swe.sweet_location = 'status' AND NOT swe.sweet_location = 'statuscom'
AND NOT swe.sweet_location = 'profilecomments_b' AND NOT swe.sweet_location = 'writingcomments_b'
AND NOT swe.sweet_location = 'artcomments_b' AND NOT swe.sweet_location = 'club_events_com' 
AND NOT swe.sweet_location = 'clubevent' AND NOT swe.sweet_location = 'club_events_com_b' 
AND NOT swe.sweet_location = 'profilecomments' AND NOT swe.sweet_location = 'clubcomments'
AND NOT swe.sweet_location = 'clubcomments_b' AND NOT swe.sweet_location = 'artcomments'
AND NOT swe.sweet_location = 'writingcomments' AND NOT swe.sweet_location = 'locations'
AND NOT swe.sweet_location = 'location_comments' AND NOT swe.sweet_location = 'location_comments_b'
AND NOT swe.sweet_location = 'forum_posts' AND NOT swe.sweet_location = 'forum_posts_replys'
AND NOT swe.sweet_location = 'showevent'
GROUP BY swe.sid)
";

//Profile Comments
$pc_status = "
(SELECT procom.timestamp, procom.id, 
procom.com_uid, procom.com_name, 
procom.com_content, procom.com_id, 
frie.userId1, frie.userId2, 
frie.status1, frie.status2,
'profilecomment' AS post_type FROM ".$db_table_prefix."profilecomments procom
LEFT JOIN ".$db_table_prefix."friend frie
ON (procom.com_uid = frie.userId1 AND frie.userId2 = $userIdme)
OR (procom.com_uid = frie.userId2 AND frie.userId1 = $userIdme)
WHERE frie.status1 = '1' AND frie.status2 = '1'
OR procom.com_uid = '$userIdme'
GROUP BY procom.id)
";

//Profile Comments Sub Comments
$pc_statcom = "
(SELECT 
	pcb.timestamp, pcb.id, pcb.statcom_uid, pcb.statcom_name, pcb.statcom_content, pcb.statcom_id,
	f.userId1, f.userId2, f.status1, f.status2,
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


		$vp_updateS = "
			(SELECT sub.timestamp, sub.int, sub.usrida, sub.name, sub.color, sub.year,
				sub.make, sub.model, sub.type, null,
			'submit2' AS post_type FROM ".$db_table_prefix."submit sub LIMIT 0)";


	}else{
		$limitfriendstatus = "10"; 
	}
		
		if($rc_view){
			if($rc_view == "status"){ $query = "$vp_updateS UNION ALL $q_status UNION ALL $q_status_com ORDER BY timestamp DESC"; }
			if($rc_view == "sweets"){ $query = "$vp_updateS UNION $s_status ORDER BY timestamp DESC"; }
			if($rc_view == "comments"){ $query = "$vp_updateS UNION ALL $pc_statcom UNION ALL $pc_status ORDER BY timestamp DESC"; }
		}else{

			if(isUserLoggedIn())
			{
			$query = "
				$vp_updateS UNION ALL
				$q_status UNION ALL
				$q_status_com UNION ALL
				$s_status UNION ALL
				$pc_status UNION ALL
				$pc_statcom
				ORDER BY timestamp DESC
			";
			}else{
				// Redirect user to not logged in homepage
				$redir_link_url = "$site_url_link";
				header("Location: $redir_link_url");
			}
		}
		
		$queryA = "$query LIMIT $limitfriendstatus";
		$queryB = "$query";
		
		// Ouput the full sql query
		//echo "<br><br>  $queryA  <br><br>";
		
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
			$post_type = $row_am['post_type'];
			$timestamp = $row_am['timestamp'];
			$int = $row_am['int'];
			$usrida = $row_am['usrida'];
			$name = $row_am['name'];
			$color = $row_am['color'];
			$year = $row_am['year'];
			$make = $row_am['make'];
			$model = $row_am['model'];
			$type = $row_am['type'];

				$bgcolor = "epboxa";

			
			//echo "$usrida";
			//Testing timestamp
			$timestamp_p = $timestamp;
			//echo " ( timestamp = $timestamp_p ) ";
			
			if(isset($vm_id_a)){ $vm_id_a++; }else{ $vm_id_a = '1'; };

			echo "<a class='anchor' name='viewmore$vm_id_a'></a>";

			$color = stripslashes($color);
			$model = stripslashes($model);

			////Vehicle Profile Start
				if($post_type == "submit"){
					require "pages/recentposts/rec_veh_pro.inc";
				}
			////Vehicle Profile End

			////Club Start
				if($post_type == "club"){
					require "pages/recentposts/rec_club.inc";
				}
			////Club End

			////Vehicle Pic Start
				if($post_type == "art"){
					require "pages/recentposts/rec_veh_pic.inc";
				}
			////Vehicle Pic End


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
		echo "Currently showing $vm_id_a of $numofposts posts.";//testing
		if( !isset($numofposts) ){$numofposts = "0";}else{
			//$plussome = ($num_rows - $numofposts);
 			//echo "<Br>$limitfriendstatus - $num_rows - $numofposts - $plussome <br>";
			if(isset($num_rows)){}else{ $num_rows = ""; }
			if($limitfriendstatus < $num_rows || $limitfriendstatus < $numofposts){
				$vm_id = $limitfriendstatus + 1;
				echo "<table width=100%><tr><td>";
				echo " <center><a href=\"?rc_view=$rc_view&offset=" . ($limitfriendstatus + 10) . "#viewmore$vm_id\">Show More Posts...</a> </center> "; 
				echo "</td></tr></table><br><br>";
			}
		}
	}
?>