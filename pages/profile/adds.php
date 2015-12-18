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



if(isUserLoggedIn()){
	
	// Update User's Advertisement setting
	if(isset($_POST['userAdds']) && isset($_POST['update_adds_button'])){
		//Token validation function
		if(!is_valid_token()){ 

			//Token does not match
			err_message('Sorry, Tokens do not match!  Please go back and try again.');

		}else{
			if (update_user_adds_setting($userId, $_POST['userAdds'])){
				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You have updated your Advertisement setting!";
				$_SESSION['success_msg'] = $success_msg;
				// Refresh the page
				header("Location: ");
				exit;
			}
			else {
				err_message('Sorry, There was an error updating your Advertisement setting.');
				exit;
			}
		}
	}

	// Show Links for account settings
	account_settings_links();

	echo "<form method='post' action=''>";

	// create multi sessions
	if(isset($session_token_num)){
		$session_token_num = $session_token_num + 1;
	}else{
		$session_token_num = "1";
	}
	form_token();
	
	echo "<center><table width='50%' border='0' cellspacing='0' cellpadding='0'><tr><td class='epboxb'>";
		echo "<strong>Advertisement Settings</strong>";
		echo "<br><br>";
		echo "Show me advertisements on this web site?";
		echo "<label><input type='radio' name='userAdds' value='TRUE' ";
			if($userAdds == "TRUE"){echo "checked";} 
		echo "> YES</label>";
		echo "<label><input type='radio' name='userAdds' value='FALSE' ";
			if($userAdds == "FALSE"){echo "checked";} 
		echo "> NO</label><br><br>";
		echo "<center><input type='submit' name='update_adds_button' value='Update Advertisement Setting'></center>";
	echo "</td></tr></table></center>";
	
	echo "</form>";
	
}else{ notlogedinmsg();	}
	
?>