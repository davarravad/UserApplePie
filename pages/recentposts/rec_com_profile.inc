<?php
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
			$sw_user_sweeted =  "<table width=100% height=18><tr><td align=left>
					$sw_user_sweeted_pic <strong> $sw_usernameB <a href='$sweet_url'>commented</a> on... </strong> 
					</td><td align=right></td></tr></table><hr>";

			//Get the user that was sweeted name
		    $sw_username88 = get_user_name_2($sweet_id);
			$sw_username888 = "<a href='${site_url_link}member/$sweet_id/'>$sw_username88</a>";


			echo "<table width=$tblw500>";
			echo "<tr><td class='$bgcolor'>";
			echo "$sw_user_sweeted";

				$ID02 = $com_id;
			echo "<div class='comt_nm2'><a href='${site_url_link}member/$ID02/'>";
				require "pages/recentposts/userimage_small_rcp.inc";
			echo "</a>";
			echo " $sw_username888";
			echo "'s Profile";
			echo "</div><br>";
			echo "<div class='comt_cnt'><strong><a href='$sweet_url'>Comment</a></strong><br>";
				//url for read more link
				$com_content_link = "$sweet_url";
				//Function to clean up and shorten com_content and add read more link
				read_more_com_content($com_content, $com_content_link);
			echo "</div>";

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



			echo "</td></tr></table><br>";
		
?>