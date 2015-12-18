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


//Displays Status updates

			//reset vars to status
			$timestamp = $timestamp;
			$id = $int;
			$com_uid = $usrida;
			$com_name = $name;
			$com_content = $color;
			$com_id = $year;

			echo "<a class='anchor' name='status$id'></a>";
			
			echo "<div class='panel panel-info'>";
				echo "<div class='panel-heading' style='font-weight: bold'>";
					$ID02 = $com_id;
					echo "<a href='${site_url_link}member/$ID02/'>";
						require "pages/profile/userimage_small.php";
					echo "</a> Status by ";
					echo "<a href='${site_url_link}member/$ID02/'>";
					echo " $com_name ";
					echo "</a>";
				echo "</div>";
				echo "<div class='panel-body'>";
					echo "<div class='well well-sm' style='margin-top: 5px; margin-bottom: 0px'>";
						//url for read more link
						$com_content_link = "${site_url_link}community/viewstatus/?view_status=$id";
						//Function to clean up and shorten com_content and add read more link
						read_more_com_content($com_content, $com_content_link);
					echo "</div>";
				echo "</div>";
				echo "<div class='panel-footer'>";
					//Display how long ago this was posted
					$timestart = "$timestamp_p";  //Time of post
					require_once "external/timediff.php";
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
						require "external/sweets.php";
						//End Sweet 
						echo " <div class='btn btn-default btn-xs' style='margin-bottom: 5px'><a href='${site_url_link}community/viewstatus/?view_status=$id'>$num_rowsAZ Comments</a></div> ";
					}else{
						//Start Sweet
						$sweet_location = "status"; //Location on site where sweet is
						$sweet_id = "$id";  //Post Id number
						$sweet_userid = "$userIdme";  //User's Id
						$sweet_url = "${site_url_link}community/viewstatus/?view_status=$id";
						//$sweet_url = "${site_url_link}?page=community&pee=friendstatus&rc_view=$rc_view&offset=$offset#viewmore$vm_id_a";
						$sweet_owner_userid = "$ID02";  //Post owners userid
						require "external/sweets.php";
						//End Sweet 
						echo " <div class='btn btn-default btn-xs' style='margin-bottom: 5px'><a href='${site_url_link}community/viewstatus/?view_status=$id'>$num_rowsAZ Comments</a></div> ";
					}

					//	echo "</td></tr><tr>";
					//	echo "<td class=$bgcolor>";
					//	$statcom_id = $id;
					//	require_once "pages/my/status/statcom.php";
				echo "</div>";
			echo "</div>";

		//Un Set Vars
			unset($timestamp, $id, $com_uid, $com_name, $com_content, $com_id, $ID02);


?>