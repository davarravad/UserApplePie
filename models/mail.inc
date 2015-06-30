<?php


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

date_default_timezone_set('America/Toronto');

require_once('class.phpmailer.inc');
//include("class.smtp.inc"); // optional, gets called from within class.phpmailer.php if not already loaded


$mail             = new PHPMailer();

$body             = "$usermsg <br><br> $usermsg2 <br><br> $sitemsg";
//$body             = eregi_replace("[\]",'',$body);

$mail->IsSMTP(); // telling the class to use SMTP
$mail->Host       = "mail.website.com"; // SMTP server
$mail->SMTPDebug  = 1;                     // enables SMTP debug information (for testing)
                                           // 1 = errors and messages
                                           // 2 = messages only
$mail->SMTPAuth   = true;                  // enable SMTP authentication
$mail->SMTPSecure = "tls";                 // sets the prefix to the servier
$mail->Host       = "localhost";      // sets Mail Server as the SMTP server
$mail->Port       = 587;                   // set the SMTP port for the Mail Server server
$mail->Username   = "noreply@website.com";  // Mail Server username
$mail->Password   = "password";            // Mail Server password

$mail->SetFrom('noreply@website.com', 'Mail Server Mail No Reply');

//$mail->AddReplyTo("user2@gmail.com', 'First Last");

$mail->Subject    = "$usersub";

//$mail->AltBody    = "To view the message, please use an HTML compatible email viewer!"; // optional, comment out and test

$mail->MsgHTML($body);

$address = "$adminmail";
if(!isset($usernamea)){ $usernamea = ""; }
$mail->AddAddress($address, "$usernamea");

//$mail->AddAttachment("images/phpmailer.gif");      // attachment
//$mail->AddAttachment("images/phpmailer_mini.gif"); // attachment

if(!$mail->Send()) {
  echo "<br><br>Mailer Error: " . $mail->ErrorInfo;
  echo "<br><br>";
} else {


		echo "<br><br>Email sent!<br><br>";

 }



}
?>

