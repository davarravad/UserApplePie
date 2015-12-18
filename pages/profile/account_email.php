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



if(isUserLoggedIn())
{

	// Show Links for account settings
	account_settings_links();

	echo "<center><table width='50%' border='0' cellspacing='0' cellpadding='0'><tr><td class='epboxb'>";
	

	if(isset($_POST['update_em_pr'])){ $update_em_pr = $_POST['update_em_pr']; }else{ $update_em_pr = ""; }

	if($update_em_pr == 'update'){

			//Token validation function
			if(!is_valid_token()){ 

				//Token does not match
				err_message('Sorry, Tokens do not match!  Please go back and try again.');

			}else{
						if(isset($_POST['userId'])){ $userId = $_POST['userId']; }else{ $userId = ""; }
						if(isset($_POST['profile_privacy'])){ $profile_privacy = $_POST['profile_privacy']; }else{ $profile_privacy = ""; }
						if(isset($_POST['user_email_msg'])){ $user_email_msg = $_POST['user_email_msg']; }else{ $user_email_msg = ""; }
						if(isset($_POST['user_email_profile_com'])){ $user_email_profile_com = $_POST['user_email_profile_com']; }else{ $user_email_profile_com = ""; }
					
						$userId = $idofuser;
						
					//update script
					$query = "UPDATE `".$db_table_prefix."userprofile` SET 
								`profile_privacy` = '$profile_privacy', 
								`user_email_msg` = '$user_email_msg',
								`user_email_profile_com` = '$user_email_profile_com',
								`user_email_vp_com` = '$user_email_vp_com',
								`user_email_veh_pic_com` = '$user_email_veh_pic_com'
								WHERE `userId`='$userId' ";

					$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

					// print out the results
					if( $results )
					{
								
						//Sends success message to session
						//Shows user success when they are redirected
						$success_msg = "You Have Successfully Updated Your Privacy and E-Mail Settings!";
						$_SESSION['success_msg'] = $success_msg;
						
						if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
							$redir_link_884 = "${site_url_link}editprofilemain/account_email/";
							// Redirect member to their post
							header("Location: $redir_link_884");
							exit;
						}
					}else{
						//Code used to report mysql error
						$mysql_error_report = "TRUE";
						$sql_query = "$query";
						require "external/mysql_error_report.php";
					}

			} //end token

		}else{ //if not update then show form

			//If not updating show privacy and email form
			$userId = $idofuser;

			$query = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$userId' ";

			$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
				or die ("Couldn't ececute query. 56461222");
				
			if( $result && $contact = mysqli_fetch_object( $result ) )
			{
				$profile_privacy = $contact -> profile_privacy;
				$user_email_msg = $contact -> user_email_msg;
				$user_email_profile_com = $contact -> user_email_profile_com;
			}
			else {echo "Error!";}



			echo "<form method='post' action='${site_url_link}editprofilemain/account_email/'>";


					// create multi sessions
					if(isset($session_token_num)){
						$session_token_num = $session_token_num + 1;
					}else{
						$session_token_num = "1";
					}
					form_token();
?>
			<center><table width='450' border='0' cellspacing='0' cellpadding='0'><tr><td class='epboxb'>			
			<br>
			<table border="0" class="mTable" cellspacing="1" align="center" cellpadding="8" width="400">

			<tr><td colspan=2 class=mTr><strong>Privacy Settings</strong></td></tr>
			<tr class="mTr"><td>Who Can View Your Profile?</td><td>
			<label>
				<input type='radio' name='profile_privacy' value='public' <?php if($profile_privacy == "public"){echo "checked";} ?>> Public
			</label>
			<label>
				<input type='radio' name='profile_privacy' value='members' <?php if($profile_privacy == "members"){echo "checked";} ?>> Members
			</label><br>
			<label>
				<input type='radio' name='profile_privacy' value='friends' <?php if($profile_privacy == "friends"){echo "checked";} ?>> Friends
			</label>
			<label>
				<input type='radio' name='profile_privacy' value='me' <?php if($profile_privacy == "me"){echo "checked";} ?>> Only Me
			</label>
			</td></tr>

			</table><br>
			<table border="0" class="mTable" cellspacing="1" align="center" cellpadding="8" width="400">
			
			<tr><td colspan=2 class=mTr><strong>Email Settings</strong></td></tr>
			<tr class="mTr"><td>Send me an E-Mail when <br> members send me a message?</td><td>
			<label>
				<input type='radio' name='user_email_msg' value='yes' <?php if($user_email_msg == "yes"){echo "checked";} ?>> Yes
			</label>
			<label>
				<input type='radio' name='user_email_msg' value='no' <?php if($user_email_msg == "no"){echo "checked";} ?>> No
			</label>
			</td></tr>

			<tr class="mTr"><td>Send me an E-Mail when <br> members comment on my profile?</td><td>
			<label>
				<input type='radio' name='user_email_profile_com' value='yes' <?php if($user_email_profile_com == "yes"){echo "checked";} ?>> Yes
			</label>
			<label>
				<input type='radio' name='user_email_profile_com' value='no' <?php if($user_email_profile_com == "no"){echo "checked";} ?>> No
			</label>
			</td></tr>
			
			 <tr class="mTr"><td colspan=2 align="center">
					<input type="hidden" name="update_em_pr" value="update">
					<input type="hidden" name="userId" value="<?php
echo "$userId"; ?>">
					<input type="submit" name="update_em_pr_button" value="Update Privacy and E-Mail Settings"></td></tr>

			</table>

			</form>
			<br>
			</td></tr></table></center>
	
<?php
}



	echo "</td></tr></table>";
	echo "</center><br>";
	
}
else {
	notlogedinmsg();	
}


?>
