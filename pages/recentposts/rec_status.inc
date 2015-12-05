<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Displays Status updates

			//reset vars to status
			$timestamp = $timestamp;
			$id = $int;
			$com_uid = $usrida;
			$com_name = $name;
			$com_content = $color;
			$com_id = $year;

			echo "<a class='anchor' name='status$id'></a>";
			echo "<table width='$tblw500' border=0 cellpadding=2 cellspacing=2>";
			echo "<tr>";
			echo "<td valign=top class=$bgcolor>";
				$ID02 = $com_id;
			echo "<div class='comt_nm2'><a href='${site_url_link}member/$ID02/'>";
				require "pages/profile/userimage_small.inc";
			echo "</a> Status by ";
			echo "<a href='${site_url_link}member/$ID02/'>";
			echo " $com_name </div>";
			echo "</a>";
			echo "<br>";
			
			echo "<div class='comt_cnt'>";
				//url for read more link
				$com_content_link = "${site_url_link}community/viewstatus/?view_status=$id";
				//Function to clean up and shorten com_content and add read more link
				read_more_com_content($com_content, $com_content_link);
			echo "</div>";
			
				//Display how long ago this was posted
				$timestart = "$timestamp_p";  //Time of post
				require_once "models/timediff.inc";
				echo " " . dateDiff("now", "$timestart", 1) . " ago ";

			//Check to see how many if any comments this post has
			$queryAZ = "SELECT * FROM ".$db_table_prefix."statcom WHERE `statcom_id`='$id' ";

			$resultAZ = mysqli_query($GLOBALS["___mysqli_ston"], $queryAZ)
				or die ("Couldn't ececute query.");
			$num_rowsAZ = mysqli_num_rows($resultAZ);

			if($userIdme == $ID02){
				//Start Sweet
				$sweet_location = "status"; //Location on site where sweet is
				$sweet_id = "$id";  //Post Id number
				$sweet_userid = "$userIdme";  //User's Id
				$sweet_url = "${site_url_link}community/viewstatus/?view_status=$id";
				//$sweet_url = "${site_url_link}?page=community&pee=viewstatus&view_status=$id";
				$sweet_owner_userid = "$ID02";  //Post owners userid
				require "models/sweets.inc";
				//End Sweet 
				echo " <a href='${site_url_link}community/viewstatus/?view_status=$id'>$num_rowsAZ Comments</a>";
			}else{
				//Start Sweet
				$sweet_location = "status"; //Location on site where sweet is
				$sweet_id = "$id";  //Post Id number
				$sweet_userid = "$userIdme";  //User's Id
				$sweet_url = "${site_url_link}community/viewstatus/?view_status=$id";
				//$sweet_url = "${site_url_link}?page=community&pee=friendstatus&rc_view=$rc_view&offset=$offset#viewmore$vm_id_a";
				$sweet_owner_userid = "$ID02";  //Post owners userid
				require "models/sweets.inc";
				//End Sweet 
				echo " <a href='${site_url_link}community/viewstatus/?view_status=$id'>$num_rowsAZ Comments</a>";
			}

		//	echo "</td></tr><tr>";
		//	echo "<td class=$bgcolor>";
		//	$statcom_id = $id;
		//	require_once "pages/my/status/statcom.inc";
			echo "</td></tr></table><br>";


		//Un Set Vars
			unset($timestamp, $id, $com_uid, $com_name, $com_content, $com_id, $ID02);


?>