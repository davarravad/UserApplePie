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

	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{
				
		$statcom_id = $_POST['statcom_id'];
		$statcom_uid = $_POST['statcom_uid'];
		$statcom_name = $_POST['statcom_name'];

		$statcom_content = $_POST['statcom_content'];


		//echo ("ID = $statcom_id <br>");
		//echo ("uID = $statcom_uid <br>");
		//echo ("Name = $statcom_name <br>");
		//echo ("Content = $statcom_content <br><br>");
			
		if($statcom_content){
				
		$statcom_content = htmlspecialchars($statcom_content);
		$statcom_content = strip_tags($statcom_content);
		$statcom_content = addslashes($statcom_content);
		$statcom_content = nl2br($statcom_content);


		$query08 = "INSERT INTO `".$db_table_prefix."$com_query_database_b` SET `statcom_id`='$statcom_id',`statcom_uid`='$statcom_uid',`statcom_name`='$statcom_name',`statcom_content`='$statcom_content'";
		  
		$results08 = mysqli_query($GLOBALS["___mysqli_ston"],  $query08 );

		   // print out the results
		   if( $results08 )
		   {
				//echo( "$site_gbl_title Submit<br><br>" );
				//echo( "Successfully saved the entry.<br><br>" );

				//require "content/my/status/statcommentnew.php";


					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Commented on $statcom_name's Comment!";
					$_SESSION['success_msg'] = $success_msg;

					//Disables auto refresh for debug stuff
					if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
						//Redirects the user
						global $site_url_link;
						$redir_link_url = "";
						
						// Redirect member to their post
						header("Location: $redir_link_url");
						exit;

					}
					unset($_POST['statcom']);
				
		   }
		 
		   else
		   {
				//Code used to report mysql error
				$mysql_error_report = "TRUE";
				$sql_query = "$query08";
				require "external/mysql_error_report.php";
		   }
			
			//echo "<a href='#' onClick='history.go(-2)'>Click Here to Go Back to Work</a>";  
		} else {
			//Disables auto refresh for debug stuff
			if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
				//Redirects the user
				global $site_url_link;
				$redir_link_url = "";
				
				// Redirect member to their post
				header("Location: $redir_link_url");
				exit;

			}
		}
	}
}
else {
	notlogedinmsg();
}
 
?>


