<?php

if(isUserLoggedIn())
{
	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{

		$query = "INSERT INTO `friend` SET `userId1` = '$userId1', `userId2` = '$userId2', `status1` = '1' ";
		
		$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

			// print out the results
			if( $results )
			{
			
				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Sent a Friend Request!";
				$_SESSION['success_msg'] = $success_msg;
			
				//echo( "Friend Request Sent!!!<br><br>" );
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					echo "<meta HTTP-EQUIV='REFRESH' content='0; url=$uriref'>";	
				}
			}
			else
			{
				//Code used to report mysql error
				$mysql_error_report = "TRUE";
				$sql_query = "$query";
				require "models/mysql_error_report.inc";
			}
	}

}
else {
notlogedinmsg();
}

?>