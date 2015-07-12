<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Get globals
	global $mysqli, $site_url_link, $site_forum_title;

	// get the id of content from the URL request
	if(!empty($ID02)){
		// Show user profile by userId
		$query_PC = "SELECT count(*) as total FROM ".$db_table_prefix."userprofile WHERE userId=$ID02";
		if ($result_PC = $mysqli->query("$query_PC")) {
			/* determine number of rows result set */
			$total_PC = $result_PC->fetch_row();
			$totalPC = $total_PC['0'];
			/* close result set */
			$result_PC->close();
		}
	}
	if(!empty($USR02)){

		//Show profile by userName
		$USR02 = $mysqli->real_escape_string($USR02);
		$query_PC1 = "SELECT * FROM ".$db_table_prefix."users WHERE `display_name`='$USR02' ";
		$query_PC2 = "SELECT count(*) as total FROM ".$db_table_prefix."users WHERE `display_name`='$USR02' ";
		if ($result_PC2 = $mysqli->query("$query_PC2")) {
			/* determine number of rows result set */
			$total_PC2 = $result_PC2->fetch_row();
			$totalPC = $total_PC2['0'];
			/* close result set */
			$result_PC2->close();
		}
		
		// Get information from database
		$result_PC1 = $mysqli->query($query_PC1);
		$arr_PC1 = $result_PC1->fetch_all(MYSQLI_BOTH);
		foreach($arr_PC1 as $row_PC1)
		{
			$ID02 = $row_PC1['id'];	
		}
		
	}
	
	//echo "($ID02 - $USR02 - $totalPC)";	

	//Checks to see if profile requested is an int and if it exist
	if(intval($ID02) && ($totalPC > 0)){
	


	if($ID02 == $userIdme){
		require("models/communitylinks.inc");

		//Displays logged in user pannel
		if(isUserLoggedIn()){
			require("models/welcomemem.inc");
		}
	}else{
	}

//Start of Top Table
echo "<center>";
echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>"; 

					echo "<table><tr><td align=center>";

					require "pages/profile/epimagemain.inc";

					echo "</td><td>";

					get_user_name($ID02);

				//Title and Description
					echo "<title>";
					get_user_name($ID02);
					echo "'s Profile - $websiteName</title>";
					echo "<meta name=\"description\" content=\"";
					get_user_name($ID02);
					echo "'s $websiteName Member Profile.\">";

					echo " <br> ";

				//Show user's membership status
					$up_get_mem_status = get_up_info_mem_status($ID02);
					echo " $up_get_mem_status ";
					
				//start is user online
							if(!isset($ID02)){ $ID = $_REQUEST['ID']; }else{ $ID = $ID02; }
							
							if($ID){
							$ID = $ID;
							}
							else {
							$ID = $userId;
							}
							
							// Check to see if requested user is online
							$query_online = "SELECT * FROM ".$db_table_prefix."loggedusers WHERE `userId`='$ID' LIMIT 1";
							// Get information from database
							$result_online = $mysqli->query($query_online);
							$arr_online = $result_online->fetch_all(MYSQLI_BOTH);
							foreach($arr_online as $row_online)
							{
								$online_userId = $row_online['userId'];
								$onlineId = $online_userId;
							}
							
							//Check to see if user is online or not
							if(isset($onlineId)){
								echo "( <font color=green>ON</font>LINE )<br>";
							}
							else{
								echo "( <font color=RED>OFF</font>LINE )<br>";
							}
				//End is user online
					

				if(isUserLoggedIn())
				{
				 
					echo "<a href='${site_url_link}message/?mes=newmessage&mto=$ID'>Send Me a Message</a>";


					//echo "$ID02 - $userId";
					if($ID02 == $userId){
						echo "<br><a href='${site_url_link}editprofilemain/'>Edit Profile</a>";
					}
					echo "<Br>";
					$userId1 = $userIdme;
					$userId2 = $ID02;
					//echo " $userId1 - $userId2 ";
					if($userId1 == $userId2){ echo "This is YOU!"; }else{
					require "pages/friend/friendcheck.inc";
					}
				}
					echo "</td></tr></table>";

echo "</td></tr>";
echo "<tr><td class='content78'>";

			//Check privacy settings
			require "pages/profile/profileprivacy.inc";

			//Use privacy settings to hide or show profile
			if($allowPV == "TRUE"){

			?>

			<center>


			  
			<Br>
			<strong>Basic Information About <?php
get_user_name($ID02); ?>!</strong>
			</center>

			<?php

				// Get user profile information
				$get_info_id = $ID02;
				// get_user_profile_info_uid($get_info_id);

				// Call database for user profile information
				$up_get_firstname = get_up_info($get_info_id, 'userFirstName');
				$up_get_nickname = get_up_info($get_info_id, 'userAddr1');
				$up_get_sex = get_up_info($get_info_id, 'userAddr2');
				$up_get_location = get_up_info($get_info_id, 'userCity');
				$up_get_aim = get_up_info($get_info_id, 'userTel');
				$up_get_yahoo = get_up_info($get_info_id, 'userMobiTel');
				$up_get_fb = get_up_info($get_info_id, 'userFacebook');
				$up_get_twt = get_up_info($get_info_id, 'userTwitter');
				$up_get_website = get_up_info($get_info_id, 'userWeb');
				
				// Call for user signup date
				$up_get_userSignUp2 = get_up_info_usr_signup2($get_info_id);
				$up_get_userLastLogin = get_up_info_usr_lastlogin($get_info_id);
				
				
				
				echo "<table width='100%' cellspacing='0' cellpadding='0'><tr><td width='50%'>";
				echo "<table width='100%'>";
				
				if(!empty($up_get_firstname)){
					echo "<tr><td class='epboxb'>&nbsp; First Name: </td><td class='epboxb'>&nbsp; $up_get_firstname </td></tr>";
				}
				if(!empty($up_get_nickname)){
					echo "<tr><td class='epboxa'>&nbsp; Nicknames: </td><td class='epboxa'>&nbsp; $up_get_nickname </td></tr>";
				}
				if(!empty($up_get_sex)){
					echo "<tr><td class='epboxa'>&nbsp; Sex: </td><td class='epboxa'>&nbsp; $up_get_sex </td></tr>";
				}
				if(!empty($up_get_location)){
					echo "<tr><td class='epboxa'>&nbsp; City/Town: </td><td class='epboxa'>&nbsp; ";
					//echo " $up_get_location";

						$zip = "$up_get_location";
						if($zip){
							include "models/zip.inc";
							$csdisplay = "$city, $state_code";
							echo "$csdisplay";
							unset($csdisplay, $city, $state_code);
						}

					echo " </td></tr>";
				}
				if(!empty($up_get_aim)){
					echo "<tr><td class='epboxa'>&nbsp; AIM SN: </td><td class='epboxa'>&nbsp; <a href='aim:GoIM?screenname=$up_get_aim'>
						<img src='http://api.oscar.aol.com/SOA/key=da18c0y71JbCNJTq/presence/$up_get_aim' border='0'/> $up_get_aim</a></td></tr>";
				}
				if(!empty($up_get_yahoo)){
					echo "<tr><td class='epboxa'>&nbsp; Yahoo! SN: </td><td class='epboxa'>&nbsp; $up_get_yahoo </td></tr>";
				}
				if(!empty($up_get_fb)){
					echo "<tr><td class='epboxa'>&nbsp; Facebook: </td><td class='epboxa'>&nbsp; 
						<a href='https://www.facebook.com/$up_get_fb' target='_blank'>https://www.facebook.com/$up_get_fb</a> </td></tr>";
				}
				if(!empty($up_get_twt)){
					echo "<tr><td class='epboxa'>&nbsp; Twitter: </td><td class='epboxa'>&nbsp; 
						<a href='https://twitter.com/$up_get_twt' target='_blank'>https://twitter.com/$up_get_twt</a> </td></tr>";
				}
				if(!empty($up_get_website)){
					echo "<tr><td class='epboxa'>&nbsp; Website: </td><td class='epboxa'>&nbsp; 
						<a href='http://$up_get_website' target='_blank'>http://$up_get_website</a></td></tr>";
				}
			

				echo "<tr><td class='epboxa'>&nbsp; SignUp Date: </td><td class='epboxa'>&nbsp; $up_get_userSignUp2 </td></tr>";
			

			//Check to see if user is online, if not show how long ago was last login
			if($up_get_userLastLogin == '0000-00-00 00:00:00' || $up_get_userLastLogin == '1901-12-13 14:45:52'){
				$userLastLogin_ago = "It's been a while.";
			}else{
				if(isset($onlineId)){
					$userLastLogin_ago = "<font color=green>ON</font>LINE NOW";
				}
				else{
					//Display how long ago user last logged in
					unset($timestart);
					$timestart = "$up_get_userLastLogin";  //Time of post
					require_once "models/timediff.inc";
					$userLastLogin_ago = " " . dateDiff("now", "$timestart", 1) . " ago ";
				}
			}
			
			echo "<tr><td class='epboxa'>&nbsp; Last Login: </td><td class='epboxa'>&nbsp; $userLastLogin_ago </td></tr>";
			
			//Display total number of post to site
			require "models/total_user_submits.inc";
			echo "<tr><td class='epboxa'>&nbsp; Total Submitions: </td><td class='epboxa'>&nbsp; $total_user_submits </td></tr>";			
			
						echo "</table>";
						echo "</td></tr>";


							//Check to see if there are any profile images
							$queryCKPI = "SELECT * FROM ".$db_table_prefix."ep3 WHERE `userId`='$ID02' ";
							$resultCKPI = mysqli_query($GLOBALS["___mysqli_ston"], $queryCKPI);
				
							$num_rowsCKPI = mysqli_num_rows($resultCKPI);
				
							//echo "$num_rowsCKPI";
			if($num_rowsCKPI != 0){


						echo "<tr><td width='50%'>";
						echo "<hr align='center' width='100%' />";
						echo "<div align='center'><strong>Images</strong><br>";
				
				require "pages/profile/epimage.inc";

				echo "</div></td></tr>";
			}elseif(isUserLoggedIn() && $userIdme == $ID02){
				echo "<tr><td width='100%'>";
				echo "<div align='center'><strong>:Images:</strong><br>";
				echo "(<a href='${site_url_link}editprofilemain/picsubmit/'>Add Photos to Your Member Profile!</a>)";
				echo "</div></td></tr>";
			}
				echo "<tr><td>";
				require "pages/profile/part2.inc";

				
				echo "<hr align='center' width='100%' />";

				//Display comments
				//Settings needed for comments to work
				$com_top_title = "Profile Comments";  //Displays the title of comments at top of comments
				$com_query_database = "profilecomments"; //Comments database
				$com_query_database_b = "profilecomments_b"; //Comments comments database
				$com_url_addy = "${site_url_link}member/$ID/"; //Url Location of comments
				$com_sel_id = "$ID"; //Id of post that comments are related to
				require "pages/comments/com_display.inc";

				echo "</td></tr></table>";
				
	//End show or hide profile
	}
				
echo "</td></tr></table>";

	}else{ 
		//Requested profile does not exist, show error message
		err_message("The Profile requested does not exist."); 
	}
?>