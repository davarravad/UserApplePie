<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
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

			$com_id = $userId;
			  $com_id = $_POST['com_id'];
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
			 



			  $query = "INSERT INTO `".$db_table_prefix."status` SET `com_id`='$userId',`com_name`='$com_name',`com_content`='$com_content'";
		  
		  

		 $results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

		   // print out the results
		   if( $results )
		   {
			  //echo( "$websiteName Submit<br><br>" );
			  //echo( "Successfully saved the entry.<br><br>" );

				//require "pages/my/status/commentnew.inc";
				//Disables auto refresh for debug stuff

				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Updated Your Status!";
				$_SESSION['success_msg'] = $success_msg;
								
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}community/mystatus/'>";   
				}
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
					echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}community/mystatus/'>";
				}
		}
			//echo "<a href='#' onClick='history.go(-2)'>Click Here to Go Back to Work</a>";  

	}
}else{
	notlogedinmsg();
}	

			
?>


