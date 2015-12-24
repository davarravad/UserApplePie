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


//Start of mailmessage function
function mailmessage() {

	//Function mailmessage(); is set up to get userEmail for sending message alerts

	global $mysqli, $site_url_link, $db_table_prefix, $websiteUrl, $websiteName, $userIdme;
	
	$mto = $_POST['mto'];
	$mfrom = $userIdme;
	
	$mto = get_up_info_mem_disp_name($mto);
	$mfrom = get_up_info_mem_disp_name($mfrom);
	//echo "$mto";

	$query = "SELECT * FROM ".$db_table_prefix."users WHERE `display_name` = '$mto' LIMIT 1";
	$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
		or die ("Couldn't ececute query. MailGlobal 465");
		
	if( $result && $contact = mysqli_fetch_object( $result ) )
	{			  
		$userId_email = $contact -> id;
	}
	else 
	{
		echo "Error : ?userId_email?";
	}
		
	// Test display userId
	//echo "$userId_email";

	// Get user email privacy setting for messages
	$query = "SELECT `".$db_table_prefix."userprofile`.`user_email_msg` FROM ".$db_table_prefix."userprofile WHERE `userId` = '$userId_email' LIMIT 1";
	$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
		or die ("Couldn't ececute query.");
	if( $result && $contact = mysqli_fetch_object( $result ) )
	{
		$user_email_msg = $contact -> user_email_msg;
	}
	
	// Get users email address
	$query = "SELECT `".$db_table_prefix."users`.`email` FROM ".$db_table_prefix."users WHERE `id` = '$userId_email' LIMIT 1";
	$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
		or die ("Couldn't ececute query.");
	if( $result && $contact = mysqli_fetch_object( $result ) )
	{
		$email = $contact -> email;
	}	

		
	if($user_email_msg == 'yes'){
			
		$query = "SELECT * FROM ".$db_table_prefix."users WHERE `id` = '$userId_email' LIMIT 1";
		$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
		or die ("Couldn't ececute query.");

		if( $result && $contact = mysqli_fetch_object( $result ) )
		{
			$usernamea = $contact -> display_name;
		}else {echo "Error : ?display_name?";}

		$touserEmail = $email;
			
		if($email){
		
			$adminmail = $touserEmail;
			$usersub = "NEW message from $mfrom";
			$usermsg = ":<strong> $mfrom </strong>: has sent you a NEW message.";
		$usermsg2 = "You may check your message at ${websiteUrl}message/";
			$username = "$mto";
							
			require_once "./external/mail.php";
	
		}
		else{
			echo "<br><br>Error : ?Email?";
		}
	}//end mail settings check
}//End of mailmessage function

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Start of mailmessage function
function mailprofilecomment() {

//Function mailprofilecomment(); is set up to get userEmail for sending message alerts

		global $mysqli, $site_url_link, $db_table_prefix, $websiteUrl, $websiteName;

		$com_id = $_REQUEST['com_id'];
		$com_name = $_REQUEST['com_name'];
		//echo "$com_id and $com_name";

		$query = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId` = '$com_id' LIMIT 1";
		$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
			or die ("Couldn't ececute query.");
		
		   if( $result && $contact = mysqli_fetch_object( $result ) )
		   {
				$userEmail = $contact -> userEmail;
				$user_email_profile_com = $contact -> user_email_profile_com;
		   }
		   
			else {echo "Error : ?userEmail?";}

	if($user_email_profile_com == 'yes'){
			
			$query = "SELECT * FROM ".$db_table_prefix."users WHERE `userId` = '$com_id' LIMIT 1";
			$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
				or die ("Couldn't ececute query.");
			
			   if( $result && $contact = mysqli_fetch_object( $result ) )
			   {
				  $usernamea = $contact -> userName;
			   }
			
			else {echo "Error : ?userName?";}
			
			//echo "$userEmail";
			
			$touserEmail = $userEmail;
			
			if($userEmail){
			
			$adminmail = $touserEmail;
			$usersub = "NEW profile comment on $websiteUrl";
			$usermsg = ": <strong>$com_name</strong> : has sent you a NEW profile comment.";
			$usermsg2 = "You may check your new comment at $websiteUrl/member/$com_id.";
			$username = "$com_name";
			
			
			require_once "./external/mail.php";
			
			}
				else{
					echo "<br><br>Error : ?Email?";
				}
	}
}
//End of mailprofilecomment function




?>