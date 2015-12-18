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


global $websiteName, $websiteUrl, $emailAddress;

//Disables Email to user
$email_setting = "ON";  //ON or OFF


if($email_setting == 'OFF'){ echo "<br> - EMAIL OFF - <BR>"; }else{


	$sitemsg = "	<br>
					<br>
						This email was sent from $websiteName as a form of notification.
					<Br>
					<br>
						Visit and Login to $websiteUrl for more information!
					<br>
					<br>
						Please do not reply to this email.
					<br>
						Thank you and enjoy $websiteName
				";


	$body = "$usermsg <br><br> $usermsg2 <br><br> $sitemsg";

	$email = $adminmail;
	$email = $username . " <" . $email . ">\r\n";
	$subject = $usersub;
	$message = $body;
	
	// Send the email	
	$header = "MIME-Version: 1.0\r\n";
	$header .= "Content-type: text/html; charset=iso-8859-1\r\n";
	$header .= "From: ". $websiteName . " <" . $emailAddress . ">\r\n";
	
	$message = wordwrap($message, 70);
	
	return mail($email,$subject,$message,$header);

}
?>

