<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isUserLoggedIn())
{

	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{

			$com_id = $_POST['com_id'];
			$com_uid = $_POST['com_uid'];
			$com_name = $_POST['com_name'];
			$com_content = $_POST['com_content'];



		//echo ("ID = $com_id <br>");
		//echo ("ID = $com_name <br>");

		//echo ("ID = $com_content <br><br>");
			
			if($com_content){
					
			$com_content = htmlspecialchars($com_content);
			$com_content = strip_tags($com_content);
			$com_content = addslashes($com_content);
			$com_content = nl2br($com_content);
			 



			  $query = "INSERT INTO `".$db_table_prefix."$com_query_database` SET `com_id`='$com_id',`com_uid`='$com_uid',`com_name`='$com_name',`com_content`='$com_content'";
		  
		  

		 $results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

		   // print out the results
		   if( $results )
		   {
			  //echo( "$site_gbl_title Submit<br><br>" );
			  //echo( "Successfully saved the entry.<br><br>" );

				//require "pages/my/status/commentnew.inc";
				//Disables auto refresh for debug stuff

				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Submitted a Comment!";
				$_SESSION['success_msg'] = $success_msg;
								
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $site_url_link;
					$redir_link_url = "";
					
					// Redirect member to their post
					header("Location: $redir_link_url");
					exit;
  
				}
				unset($_POST['comment']);
				
		   }
		 
		   else
		   {
				//Code used to report mysql error
				$mysql_error_report = "TRUE";
				$sql_query = "$query";
				require "models/mysql_error_report.inc";
		   }
			
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
			//echo "<a href='#' onClick='history.go(-2)'>Click Here to Go Back to Work</a>";  

	}
}else{
	notlogedinmsg();
}	

			
?>


