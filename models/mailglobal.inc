<?php

//Start of mailmessage function
function mailmessage() {

	//Function mailmessage(); is set up to get userEmail for sending message alerts

	global $mysqli, $site_url_link, $db_table_prefix;
	
	$mto = $_POST['mto'];
	$mfrom = $_POST['mfrom'];
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
			$usersub = "NEW message from $mfrom on CarTruckClubs.com";
			$usermsg = ":<strong> $mfrom </strong>: has sent you a NEW message.";
			$usermsg2 = "You may check your message at www.cartruckclubs.com. &gt; Community &gt; My Messages";
			$username = "$mto";
							
			require_once "models/mail.inc";
	
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

		global $mysqli, $site_url_link, $db_table_prefix;

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
			$usersub = "NEW profile comment on www.cartruckclubs.com";
			$usermsg = ": <strong>$com_name</strong> : has sent you a NEW profile comment.";
			$usermsg2 = "You may check your new comment at http://www.cartruckclubs.com/member/$com_id.";
			$username = "$com_name";
			
			
			require_once "models/mail.inc";
			
			}
				else{
					echo "<br><br>Error : ?Email?";
				}
	}
}
//End of mailprofilecomment function





//Start of mailcomment function
function mailcomment() {

//Function mailcomment(); is set up to get userEmail for sending message alerts

		global $mysqli, $site_url_link, $db_table_prefix;

		$usrida = $_POST['usrida'];
		$com_type = $_POST['com_type'];
		$com_id = $_POST['com_id'];
		$com_name = $_POST['com_name'];
		
		//echo "<br>-- $usrida -- $com_type --<br>";
		
		$query = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId` = '$usrida' LIMIT 1";
		$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
			or die ("Couldn't ececute query.");
		
		   if( $result && $contact = mysqli_fetch_object( $result ) )
		   {
			  $userEmail = $contact -> userEmail;
  			  $user_email_vp_com = $contact -> user_email_vp_com;
		   }
		
			else {echo "Error : ?userEmail?";}

	if($user_email_vp_com == 'yes'){			
			
		$query = "SELECT * FROM ".$db_table_prefix."users WHERE `userId` = '$usrida' LIMIT 1";
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
		
		require_once "models/members/getuserinfo.inc";
		
		$com_type = "Vehicle Profile";
		$adminmail = $touserEmail;
		$usersub = "NEW comment on your Vehicle Profile at www.cartruckclubs.com";
		$usermsg = "You have a NEW vehicle profile comment from <strong>$com_name</strong>.";
		$usermsg2 = "You may check your comment at http://www.cartruckclubs.com/writingview/?int=$com_id";
		$username = "$com_name";
		
		
		require_once "models/mail.inc";
		
		}
			else{
				echo "<br><br>Error : ?Email?";
			}
	}
}
//End of mailcomment function




//Start of mailcommentart function
function mailcommentart() {

//Function mailcommentart(); is set up to get userEmail for sending message alerts

		global $mysqli, $site_url_link, $db_table_prefix;

		$usrida = $_POST['usrida'];
		//$com_type = $_POST['com_type'];
		$com_id = $_POST['com_id'];
		$com_name = $_POST['com_name'];
		
		//echo "<br>-- $usrida -- $com_type --<br>";
		
		$query = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId` = '$usrida' LIMIT 1";
		$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
			or die ("Couldn't ececute query.");
		
		   if( $result && $contact = mysqli_fetch_object( $result ) )
		   {
			  $userEmail = $contact -> userEmail;
			  $user_email_veh_pic_com = $contact -> user_email_veh_pic_com;
		   }
		
			else {echo "Error : ?userEmail?";}

	if($user_email_veh_pic_com == 'yes'){
			
		$query = "SELECT * FROM ".$db_table_prefix."users WHERE `userId` = '$usrida' LIMIT 1";
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
		
		require_once "models/members/getuserinfo.inc";
		
		$adminmail = $touserEmail;
		$usersub = "NEW comment on your Vehicle Photo at www.cartruckclubs.com";
		$usermsg = "You have a NEW vehicle photo comment from <strong>$com_name</strong>.";
		$usermsg2 = "You may check your comment at http://www.cartruckclubs.com/artview/?id=$com_id";
		$username = "$com_name";
		
		
		require_once "models/mail.inc";
		
		}
			else{
				echo "<br><br>Error : ?Email?";
			}
	}
}
//End of mailcommentart function


?>