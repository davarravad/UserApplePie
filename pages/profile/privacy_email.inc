<?php

if(isUserLoggedIn())
{
	if(isset($_POST['update_em_pr'])){ $update_em_pr = $_POST['update_em_pr']; }else{ $update_em_pr = ""; }

	if($update_em_pr == 'update'){

			//Token validation function
			if(!is_valid_token()){ 

				//Token does not match
				err_message('Sorry, Tokens do not match!  Please go back and try again.');

			}else{
						if(isset($_POST['userId'])){ $userId = $_POST['userId']; }else{ $userId = ""; }
						if(isset($_POST['userFax'])){ $userFax = $_POST['userFax']; }else{ $userFax = ""; }
						if(isset($_POST['user_email_msg'])){ $user_email_msg = $_POST['user_email_msg']; }else{ $user_email_msg = ""; }
						if(isset($_POST['user_email_profile_com'])){ $user_email_profile_com = $_POST['user_email_profile_com']; }else{ $user_email_profile_com = ""; }
						if(isset($_POST['user_email_vp_com'])){ $user_email_vp_com = $_POST['user_email_vp_com']; }else{ $user_email_vp_com = ""; }
						if(isset($_POST['user_email_veh_pic_com'])){ $user_email_veh_pic_com = $_POST['user_email_veh_pic_com']; }else{ $user_email_veh_pic_com = ""; }
						 
						require "models/members/getuserinfo.inc";
						$userId = $idofuser;
						
					//update script
					$query = "UPDATE `".$db_table_prefix."userprofile` SET 
								`userFax` = '$userFax', 
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
						require "models/mysql_error_report.inc";
					}

			} //end token

		}else{ //if not update then show form

			//If not updating show privacy and email form
			require "models/members/getuserinfo.inc";
			$nname = $nname;
			$userId = $idofuser;

			$query = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$userId' ";

			$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
				or die ("Couldn't ececute query. 56461222");
				
			if( $result && $contact = mysqli_fetch_object( $result ) )
			{
				$userFax = $contact -> userFax;
				$user_email_msg = $contact -> user_email_msg;
				$user_email_profile_com = $contact -> user_email_profile_com;
				$user_email_vp_com = $contact -> user_email_vp_com;
				$user_email_veh_pic_com = $contact -> user_email_veh_pic_com;
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
				<input type='radio' name='userFax' value='public' <?php if($userFax == "public"){echo "checked";} ?>> Public
			</label>
			<label>
				<input type='radio' name='userFax' value='members' <?php if($userFax == "members"){echo "checked";} ?>> Members
			</label><br>
			<label>
				<input type='radio' name='userFax' value='friends' <?php if($userFax == "friends"){echo "checked";} ?>> Friends
			</label>
			<label>
				<input type='radio' name='userFax' value='me' <?php if($userFax == "me"){echo "checked";} ?>> Only Me
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

			<tr class="mTr"><td>Send me an E-Mail when <br> members comment on my vehicle profiles?</td><td>
			<label>
				<input type='radio' name='user_email_vp_com' value='yes' <?php if($user_email_vp_com == "yes"){echo "checked";} ?>> Yes
			</label>
			<label>
				<input type='radio' name='user_email_vp_com' value='no' <?php if($user_email_vp_com == "no"){echo "checked";} ?>> No
			</label>
			</td></tr>

			<tr class="mTr"><td>Send me an E-Mail when <br> members comment on my vehicle photos?</td><td>
			<label>
				<input type='radio' name='user_email_veh_pic_com' value='yes' <?php if($user_email_veh_pic_com == "yes"){echo "checked";} ?>> Yes
			</label>
			<label>
				<input type='radio' name='user_email_veh_pic_com' value='no' <?php if($user_email_veh_pic_com == "no"){echo "checked";} ?>> No
			</label>
			</td></tr>
			
			 <tr class="mTr"><td colspan=2 align="center">
					<input type="hidden" name="update_em_pr" value="update">
					<input type="hidden" name="userId" value="<? echo "$userId"; ?>">
					<input type="submit" name="update_em_pr_button" value="Update Privacy and E-Mail Settings"></td></tr>

			</table>

			</form>
			<br>
			</td></tr></table></center>
	
<?
	}
}else {
	notlogedinmsg();
}

?>