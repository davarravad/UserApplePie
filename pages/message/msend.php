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

// Make sure user is logged in
if(isUserLoggedIn())
{

	// Token validation function
	if(!is_valid_token()){ 
		// Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');
	}else{					
		
		// Get Message Data
		$mto = $_POST['mto'];
		$mfrom = $_POST['mfrom'];
		$msubject = $_POST['msubject'];
		$mcontent = $_POST['mcontent'];
		
		// Make sure mto is not already an integer - for replys
		if (!ctype_digit($_POST['mto'])) {
			// Convert mto user display_name to user's id
			$result = $DBH->prepare("SELECT id FROM ".$db_table_prefix."users WHERE display_name = :mto ");
			$result->bindParam(':mto', $mto, PDO::PARAM_STR);
			$result->execute();
			$fetch = $result->fetch();
			$mto = $fetch['id'];
		}

		// Clear the result
		unset($result);
		
		// Clean up any HTML Stuffs
		$mcontent = htmlspecialchars($mcontent);
		$mcontent = strip_tags($mcontent);
		$msubject = addslashes($msubject);
		$mcontent = addslashes($mcontent);
		$mcontent = nl2br($mcontent);

		// Create Message into the mto user's inbox
		$result = $DBH->prepare("INSERT INTO ".$db_table_prefix."inbox SET mto = :mto, mfrom = :mfrom, msubject = :msubject, mcontent = :mcontent ");
		$result->bindParam(':mto', $mto, PDO::PARAM_INT);
		$result->bindParam(':mfrom', $mfrom, PDO::PARAM_INT);
		$result->bindParam(':msubject', $msubject);
		$result->bindParam(':mcontent', $mcontent);
		$result->execute();
		
		// Get Id of inbox message just submitted
		$mid = $DBH->lastInsertId();
		
		// Check for success or error
		if($result !== FALSE){
			//Sends success message to session
			//Shows user success when they are redirected
			$success_msg = "You Have Successfully Sent a Message!";
			$_SESSION['success_msg'] = $success_msg;
			
			//Email send
			require_once "external/mailglobal.php";
			mailmessage();
		}else{
			// Display error
			$error = $result->errorInfo();
			//echo 'MySQL Error: ' . $error[2];
			
			// Save the error to database
			$mysql_error_report = "TRUE";
			$sql_query = "$query" . $error[2];
			require "external/mysql_error_report.php";
			
			// Display Error Message
			err_message("Oops! Something went wrong. Please try again later.");
		}
		
		// Clear the result
		unset($result);
		
		// Create Message into the mfrom user's inbox
		$result = $DBH->prepare("INSERT INTO ".$db_table_prefix."outbox SET mid = :mid, mto = :mto, mfrom = :mfrom, msubject = :msubject, mcontent = :mcontent ");
		$result->bindParam(':mid', $mid, PDO::PARAM_INT);
		$result->bindParam(':mto', $mto, PDO::PARAM_INT);
		$result->bindParam(':mfrom', $mfrom, PDO::PARAM_INT);
		$result->bindParam(':msubject', $msubject);
		$result->bindParam(':mcontent', $mcontent);
		$result->execute();
		
		// Check for success or error
		if($result !== FALSE){
			//Disables auto refresh for debug stuff
			if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
				$redir_link_884 = "${site_url_link}message/";
				// Redirect member to their post
				header("Location: $redir_link_884");
				exit;
			}
		}else{
			// Display error
			$error = $result->errorInfo();
			//echo 'MySQL Error: ' . $error[2];
			
			// Save the error to database
			$mysql_error_report = "TRUE";
			$sql_query = "$query" . $error[2];
			require "external/mysql_error_report.php";
			
			// Display Error Message
			err_message("Oops! Something went wrong. Please try again later.");
		}
		
		// Clear the result
		unset($result);

	} // End of Token Check

}else{
	// Display User Not Logged In message
	notlogedinmsg();
}

?>