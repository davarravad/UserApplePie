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

	if(isset($_POST['remove_friend'])){ $remove_friend = $_POST['remove_friend']; }else{ $remove_friend = ""; }
	if(isset($_POST['remove_friend_id'])){ $remove_friend_id = $_POST['remove_friend_id']; }else{ $remove_friend_id = ""; }
	if($remove_friend == 'TRUE'){

			//Token validation function
			if(!is_valid_token()){ 

				//Token does not match
				err_message('Sorry, Tokens do not match!  Please go back and try again.');

			}else{
			
				//echo "Remove Friend Yes";
				$query = "DELETE FROM `".$db_table_prefix."friend` WHERE `id`='$remove_friend_id' LIMIT 1 "; 
				
				$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

					// print out the results
					if( $results )
					{
					
						//Sends success message to session
						//Shows user success when they are redirected
						$success_msg = "You Have Successfully UnFriended!";
						$_SESSION['success_msg'] = $success_msg;
					
						//echo( "Friend Request Sent!!!<br><br>" );
						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url='>";	
						}
					}
					else
					{
						//Code used to report mysql error
						$mysql_error_report = "TRUE";
						$sql_query = "$query";
						require "external/mysql_error_report.php";
					}
			}
	}else{
		//Show form to remove friend
		//echo "Remove friend form!";
		echo "<form method=\"post\" action=\"\">";
		// create multi sessions
		if(isset($session_token_num)){
			$session_token_num = $session_token_num + 1;
		}else{
			$session_token_num = "1";
		}
		form_token();
		echo "
				<input type=\"hidden\" name=\"remove_friend_id\" value=\"$id\">
				<input type=\"hidden\" name=\"remove_friend\" value=\"TRUE\">
				<label title=\"Send\"><input type=\"submit\" value=\"End Friendship\" class='btn btn-danger'/></label>
			</form>
		";			
		
	}
}
else {
notlogedinmsg();
}

?>