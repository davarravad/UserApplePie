<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Displays Status updates

			//reset vars to status
			$timestamp = $timestamp;
			$id = $int;
			$statcom_uid = $usrida;
			$statcom_name = $name;
			$statcom_content = $color;
			$statcom_id = $year;
			
			//Shortens the post for better looks
			$vm_link = " <a href='${site_url_link}community/viewstatus/?view_status=$id'>More</a> ";
			$statcom_content = strlen($statcom_content) > 100 ? substr($statcom_content, 0, 100) . "... $vm_link" : $statcom_content;
			unset($vm_link);

			echo "<a class='anchor' name='status$id'></a>";
			echo "<div class='panel panel-info'>";
				echo "<div class='panel-heading'>";
					$ID02 = $statcom_uid;
					echo "<a href='${site_url_link}member/$ID02/'>";
					require "pages/profile/userimage_small.inc";
					echo "</a>";
					echo " <strong><a href='${site_url_link}member/$ID02/'>";
					echo " $statcom_name </a>";

					echo " <a href='${site_url_link}community/viewstatus/?view_status=$statcom_id'>Commented</a> on...</strong> ";
				echo "</div>";
				echo "<div class='panel-body'>";
					$statcom_content = stripslashes($statcom_content);
					unset($ID02);
		
					$query01 = "SELECT * FROM ".$db_table_prefix."status WHERE `id`='$statcom_id' GROUP BY `id` ORDER BY `id` DESC LIMIT 1";
					$result01 = mysqli_query($GLOBALS["___mysqli_ston"], $query01)
						or die ("Couldn't ececute query.");

					// print out the results
					if( $result01 && $contactXX = mysqli_fetch_object( $result01 ) )
					{
						// print out the info
						$com_id = $contactXX -> com_id;
						$com_content = $contactXX -> com_content;
					}
						$ID02 = $com_id;
						unset($com_id);
		
					echo "<a href='${site_url_link}member/$ID02/'>";
						require "pages/profile/userimage_small.inc";
					echo "</a>";
					echo " <strong> <a href='${site_url_link}member/$ID02/'>";
						get_user_name($ID02);
					echo "</a>'s Status - <a href='${site_url_link}community/viewstatus/?view_status=$statcom_id'>View Comment</a> ";
					echo " </strong> ";
					
					echo "<div class='well well-sm' style='margin-top: 5px; margin-bottom: 0px'>";
						//url for read more link
						$com_content_link = "${site_url_link}community/viewstatus/?view_status=$statcom_id";
						//Function to clean up and shorten com_content and add read more link
						read_more_com_content($com_content, $com_content_link);
					echo "</div>";
				echo "</div>";
				echo "<div class='panel-footer'>";
					//Display how long ago this was posted
					$timestart = "$timestamp_p";  //Time of post
					require_once "models/timediff.inc";
					echo " " . dateDiff("now", "$timestart", 1) . " ago ";
				echo "</div>";
			echo "</div>";

		//Un Set Vars
			unset($timestamp, $id, $com_uid, $com_name, $com_content, $com_id, $ID02);


?>