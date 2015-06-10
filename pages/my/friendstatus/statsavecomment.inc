<?php

if(isUserLoggedIn())
{

	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{

		//Gets today's Date in format for SQL server

		$date = "";

			
			  $statcom_id = $_POST['statcom_id'];
			  $statcom_uid = $_POST['statcom_uid'];
			  $statcom_name = $_POST['statcom_name'];

			  $statcom_content = $_POST['statcom_content'];
			  $offset = $_POST['offset'];

			//Get the owner of status
			$query01 = "SELECT status.com_name FROM status WHERE `id`='$statcom_id' LIMIT 1";

			$result01 = mysqli_query($GLOBALS["___mysqli_ston"], $query01)
				or die ("Couldn't ececute query. 465212");

			while ($row01 = mysqli_fetch_array($result01))
				{
					extract($row01);

					$com_nameAA = $com_name;
					unset($com_name);
				}
			  
			
			if($statcom_content){
					
			$statcom_content = htmlspecialchars($statcom_content);
			$statcom_content = strip_tags($statcom_content);
			$statcom_content = addslashes($statcom_content);
			$statcom_content = nl2br($statcom_content);
			 

			  $query08 = "INSERT INTO `".$db_table_prefix."statcom` SET `statcom_id`='$statcom_id',`statcom_uid`='$statcom_uid',`statcom_name`='$statcom_name',`statcom_content`='$statcom_content', `statcom_date`='$date'";
		  
		  
		 $results08 = mysqli_query($GLOBALS["___mysqli_ston"],  $query08 );

		   // print out the results
		   if( $results08 )
		   {
			  //echo( "$websiteName Submit<br><br>" );
			  //echo( "Successfully saved the entry.<br><br>" );

			//require "pages/my/status/statcommentnew.inc";

				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Commented on $com_nameAA's Status!";
				$_SESSION['success_msg'] = $success_msg;

				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{   
					echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}community/friendstatus/?offset=$offset#status$statcom_id'>";	
				}
		   }
		 
		   else
		   {
				//Code used to report mysql error
				$mysql_error_report = "TRUE";
				$sql_query = "$query08";
				require "models/mysql_error_report.inc";
		   }
			
			//echo "<a href='#' onClick='history.go(-2)'>Click Here to Go Back to Work</a>";  
		 
		} else {

				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}community/friendstatus/#status$statcom_id'>";	
				}
		}
	}
}
else {
	notlogedinmsg();
}

 
?>


