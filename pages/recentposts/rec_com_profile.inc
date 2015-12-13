<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

$timestamp = $timestamp;
			$id = $int;
			$com_uid = $usrida;
			$com_id = $year;
			$com_name = $name;
			$com_content = $color;

			//echo "Profile Comment New - $timestamp - $id - $com_uid - $com_id - $com_name - $com_content<br>";

			$sweet_userid = $com_uid;
			$sweet_id = $com_id;
			$sweet_url = "${site_url_link}member/$sweet_id/#comment$id";

	//Get the user that sweeted post name
	// retrieve the row from the database
    $sw_username = get_user_name_2($sweet_userid);
	$sw_usernameB = "<a href='${site_url_link}member/$sweet_userid/'>$sw_username</a>";

			
			$ID02 = $sweet_userid;
			require('pages/recentposts/userimage_small.inc');
			$sw_user_sweeted =  " $sw_user_sweeted_pic <strong> $sw_usernameB <a href='$sweet_url'>commented</a> on... </strong> ";

			//Get the user that was sweeted name
		    $sw_username88 = get_user_name_2($sweet_id);
			$sw_username888 = "<a href='${site_url_link}member/$sweet_id/'>$sw_username88</a>";


			echo "<div class='panel panel-info'>";
				echo "<div class='panel-heading'>";
					echo "$sw_user_sweeted";
				echo "</div>";
				
				$ID02 = $com_id;
				
				echo "<div class='panel-body'>";
					echo "<a href='${site_url_link}member/$ID02/'>";
						require "pages/recentposts/userimage_small_rcp.inc";
					echo "</a>";
					echo " $sw_username888";
					echo "'s Profile <br>";
					echo "<a href='$sweet_url'>Comment</a></strong>";
					echo "<div class='well well-sm' style='margin-top: 5px; margin-bottom: 0px'>";
						//url for read more link
						$com_content_link = "$sweet_url";
						//Function to clean up and shorten com_content and add read more link
						read_more_com_content($com_content, $com_content_link);
					echo "</div>";
				echo "</div>";
				echo "<div class='panel-footer'>";
					//Display how long ago this was posted
					$timestart = "$timestamp_p";  //Time of post
					require_once "models/timediff.inc";
					echo " " . dateDiff("now", "$timestart", 1) . " ago ";
					
					//Start Sweet
					$sweet_location = "profile"; //Location on site where sweet is
					$sweet_sec_id = "$ID02";
					$sweet_id = "$id";  //Post Id number
					$sweet_userid = "$userIdme";  //User's Id
					$sweet_url = "$sweet_url";
					//$sweet_url = "${site_url_link}?page=community&pee=friendstatus&rc_view=$rc_view&offset=$offset#viewmore$vm_id_a";
					$sweet_owner_userid = "$ID02";  //Post owners userid
					require "models/sweets.inc";
					//End Sweet 
				echo "</div>";
			echo "</div>";
		
?>