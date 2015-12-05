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
				
		
		$mto = $_POST['mto'];
		$mfrom = $_POST['mfrom'];
		$msubject = $_POST['msubject'];
		$mcontent = $_POST['mcontent'];

		$mcontent = htmlspecialchars($mcontent);
		$mcontent = strip_tags($mcontent);

		$msubject = addslashes($msubject);
		$mcontent = addslashes($mcontent);
		$msubject = nl2br($msubject);
		$mcontent = nl2br($mcontent);
	
		$mdatesent = date("YmdHis");
	
		// get the variables from the post request string
	
		$query = "INSERT INTO `".$db_table_prefix."inbox` SET `mto` = '$mto', `mfrom` = '$mfrom', `msubject` = '$msubject', `mcontent` = '$mcontent', `mdatesent`='$mdatesent' ";
		
		$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

		// Get $mid based on what mid would be for this post
		$mid = mysqli_insert_id($GLOBALS["___mysqli_ston"]);
		
		// Test to see if mid is produced
		echo "(MID=$mid) ";
		
		// print out the results
		if( $results )
		{
			//Sends success message to session
			//Shows user success when they are redirected
			$success_msg = "You Have Successfully Sent a Message!";
			$_SESSION['success_msg'] = $success_msg;
			
				//Email send
				require_once "models/mailglobal.inc";
				mailmessage();

		}
		else
		{
		  die( "Trouble saving information to the database 96332: " . ((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_error($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_error()) ? $___mysqli_res : false)) );
		}
	

	
		$query = "INSERT INTO `".$db_table_prefix."outbox` SET `mid`='$mid', `mto` = '$mto', `mfrom` = '$mfrom', `msubject` = '$msubject', `mcontent` = '$mcontent', `mdatesent`='$mdatesent' ";
	
		$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );
	
		// print out the results
		if( $results )
		{
			//echo( "<br><br>Your message has been sent!!!" );
			//echo( "" );
			//Disables auto refresh for debug stuff

			if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
				$redir_link_884 = "${site_url_link}message/";
				// Redirect member to their post
				header("Location: $redir_link_884");
				exit;
			}
		}

		else
		{
			//Code used to report mysql error
			$mysql_error_report = "TRUE";
			$sql_query = "$query";
			require "models/mysql_error_report.inc";
		}
	
		//Bottom of Submit Pages	

	}//End of Token Check


}
else {
notlogedinmsg();
}

?>