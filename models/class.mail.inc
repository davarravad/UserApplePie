<?php
/*
UserCake Version: 2.0.2
http://usercake.com
*/

class userCakeMail {
	//UserCake uses a text based system with hooks to replace various strs in txt email templates
	public $contents = NULL;
	
	//Function used for replacing hooks in our templates
	public function newTemplateMsg($template,$additionalHooks)
	{
		global $mail_templates_dir,$debug_mode;
		
		$this->contents = file_get_contents($mail_templates_dir.$template);
		
		//Check to see we can access the file / it has some contents
		if(!$this->contents || empty($this->contents))
		{
			return false;
		}
		else
		{
			//Replace default hooks
			$this->contents = replaceDefaultHook($this->contents);
			
			//Replace defined / custom hooks
			$this->contents = str_replace($additionalHooks["searchStrs"],$additionalHooks["subjectStrs"],$this->contents);
			
			return true;
		}
	}
	
	public function sendMail($email,$subject,$msg = NULL)
	{
		global $websiteName,$emailAddress, $websiteUrl;
		
		
		// Custom mail setup (gmail)
		$header = "MIME-Version: 1.0\r\n";
		$header .= "Content-type: text/plain; charset=iso-8859-1\r\n";
		$header .= "From: ". $websiteName . " <" . $emailAddress . ">\r\n";
		
		//Check to see if we sending a template email.
		if($msg == NULL)
			$msg = $this->contents; 
		
		$message = $msg;
		
		$message = wordwrap($message, 70);
		
		//Old mail function
		//return mail($email,$subject,$message,$header);
		
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

			require_once('models/class.phpmailer.inc');
			
			$mail             = new PHPMailer();

			$body             = "$message <br><br> $sitemsg";
			//$body             = eregi_replace("[\]",'',$body);

			$mail->IsSMTP(); // telling the class to use SMTP
			$mail->Host       = "mail.cartruckclubs.com"; // SMTP server
			$mail->SMTPDebug  = 1;                     // enables SMTP debug information (for testing)
													   // 1 = errors and messages
													   // 2 = messages only
			$mail->SMTPAuth   = true;                  // enable SMTP authentication
			$mail->SMTPSecure = "tls";                 // sets the prefix to the servier
			$mail->Host       = "localhost";      // sets Car Truck Clubs as the SMTP server
			$mail->Port       = 587;                   // set the SMTP port for the Car Truck Clubs server
			$mail->Username   = "noreply@cartruckclubs.com";  // Car Truck Clubs username
			$mail->Password   = "WAhts1596";            // Car Truck Clubs password

			$mail->SetFrom('noreply@cartruckclubs.com', 'Car Truck Clubs Mail');

			$mail->Subject    = "$subject";

			$mail->MsgHTML($body);

			$address = "$email";
			$mail->AddAddress($address, "Car Truck Clubs Member");

			if(!$mail->Send()) {
				echo "<br><br>Mailer Error: " . $mail->ErrorInfo;
				echo "<br><br>";
			} else {
				echo "<br><br>Email sent!<br><br>";
			}
		
	}
}

?>