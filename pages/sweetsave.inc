<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Checks to see if user is loged in
if(isUserLoggedIn())
{

	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{




		$sweet_sub88 = $_POST['sweet_sub'];
		$sweet_id88 = $_POST['sweet_id'];
		if(isset($_POST['sweet_sec_id'])){ $sweet_sec_id88 = $_POST['sweet_sec_id']; }else{ $sweet_sec_id = ""; }
		$sweet_location88 = $_POST['sweet_location'];
		$sweet_userid88 = $_POST['sweet_userid'];
		$sweet_url88 = $_POST['sweet_url'];
		if(isset($_POST['sweet_owner_userid'])){ $sweet_owner_userid88 = $_POST['sweet_owner_userid']; }else{ $sweet_owner_userid88 = ""; }


			//Submit New Sweet
			if($sweet_sub88 == "sweet"){


				$querySW = "INSERT INTO `".$db_table_prefix."sweet` SET 
					`sweet_id`='$sweet_id88',
					`sweet_sec_id`='$sweet_sec_id88',
					`sweet_sub`='$sweet_sub88',
					`sweet_location`='$sweet_location88',
					`sweet_userid`='$sweet_userid88',
					`sweet_url`='$sweet_url88', 
					`sweet_owner_userid`='$sweet_owner_userid88' 
					";

				$resultsSW = mysqli_query($GLOBALS["___mysqli_ston"],  $querySW );
		
				// print out the results
				if( $resultsSW )
				{
					//echo( "Successfully saved the entry.<br><br>" );

					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Submitted a Sweet!";
					$_SESSION['success_msg'] = $success_msg;

					//Disables auto refresh for debug stuff
					if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
						
						//Redirects the user
						global $site_url_link;
						$redir_link_url = "$sweet_url88";
						
						// Redirect member to their post
						header("Location: $redir_link_url");
						exit;

					}
				}else{
					//Code used to report mysql error
					$mysql_error_report = "TRUE";
					$sql_query = "$querySW";
					require "models/mysql_error_report.inc";
				}

				//echo "<br> ( $sweet_sub88 $sweet_location88 - $sweet_id88 - $sweet_userid88 - $sweet_url88 ) ";  //for testing

				
			}

			//UnSweet Deletes sweet from table
			if($sweet_sub88 == "unsweet"){
				$queryUS = "DELETE FROM `".$db_table_prefix."sweet` WHERE 
					`sweet_id`='$sweet_id88' AND 
					`sweet_userid`='$sweet_userid88' AND  
					`sweet_location`='$sweet_location88'
					LIMIT 1";
				$resultsUS = mysqli_query($GLOBALS["___mysqli_ston"], $queryUS);

				// print out the results
				if( $resultsUS )
				{
					//echo( "Successfully deleted the entry.<br><br>" );
					//Disables auto refresh for debug stuff
					if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{

						//Redirects the user
						global $site_url_link;
						$redir_link_url = "$sweet_url88";
						
						// Redirect member to their post
						header("Location: $redir_link_url");
						exit;

					}
				}

				//echo "<br> ( $sweet_sub88 $sweet_location88 - $sweet_id88 - $sweet_userid88 - $sweet_url88 ) ";  //for testing

			}

	}

}else{
	notlogedinmsg();
}	
?>