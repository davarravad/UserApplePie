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




class User 
{
	public $user_active = 0;
	private $clean_email;
	public $status = false;
	private $clean_password;
	private $username;
	private $displayname;
	public $sql_failure = false;
	public $mail_failure = false;
	public $email_taken = false;
	public $username_taken = false;
	public $displayname_taken = false;
	public $activation_token = 0;
	public $success = NULL;
	
	function __construct($user,$display,$pass,$email)
	{
		//Used for display only
		$this->displayname = $display;
		
		//Sanitize
		$this->clean_email = sanitize($email);
		$this->clean_password = trim($pass);
		$this->username = sanitize($user);
		
		if(usernameExists($this->username))
		{
			$this->username_taken = true;
		}
		else if(displayNameExists($this->displayname))
		{
			$this->displayname_taken = true;
		}
		else if(emailExists($this->clean_email))
		{
			$this->email_taken = true;
		}
		else
		{
			//No problems have been found.
			$this->status = true;
		}
	}
	
	public function userCakeAddUser()
	{
		global $mysqli,$emailActivation,$websiteUrl,$db_table_prefix;
		
		//Prevent this function being called if there were construction errors
		if($this->status)
		{
			//Construct a secure hash for the plain text password
			$secure_pass = password_hash("$this->clean_password", PASSWORD_DEFAULT);
			
			//Construct a unique activation token
			$this->activation_token = generateActivationToken();
			
			//Do we need to send out an activation email?
			if($emailActivation == "true")
			{
				//User must activate their account first
				$this->user_active = 0;
				
				$mail = new userCakeMail();
				
				//Build the activation message
				$activation_message = lang("ACCOUNT_ACTIVATION_MESSAGE",array($websiteUrl,$this->activation_token));
				
				//Define more if you want to build larger structures
				$hooks = array(
					"searchStrs" => array("#ACTIVATION-MESSAGE","#ACTIVATION-KEY","#USERNAME#"),
					"subjectStrs" => array($activation_message,$this->activation_token,$this->displayname)
					);
				
				/* Build the template - Optional, you can just use the sendMail function 
				Instead to pass a message. */
				
				if(!$mail->newTemplateMsg("new-registration.txt",$hooks))
				{
					
				}
				else
				{
					//Send the mail. Specify users email here and subject. 
					//SendMail can have a third parementer for message if you do not wish to build a template.
					
					if(!$mail->sendMail($this->clean_email,"Welcome To ".$websiteUrl." - Account Activation"))
					{
						
					}
				}
				$this->success = lang("ACCOUNT_REGISTRATION_COMPLETE_TYPE2");
			}
			else
			{
				//Instant account activation
				$this->user_active = 1;
				$this->success = lang("ACCOUNT_REGISTRATION_COMPLETE_TYPE1");
			}	
			
			
			if(!$this->mail_failure)
			{
				//Insert the user into the database providing no errors have been found.
				$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."users (
					user_name,
					display_name,
					password,
					email,
					activation_token,
					last_activation_request,
					lost_password_request, 
					active,
					title,
					userIP,
					sign_up_stamp,
					last_sign_in_stamp
					)
					VALUES (
					?,
					?,
					?,
					?,
					?,
					'".time()."',
					'0',
					?,
					'New Member',
					?,
					'".time()."',
					'0'
					)");
				
				$stmt->bind_param("sssssis", $this->username, $this->displayname, $secure_pass, $this->clean_email, $this->activation_token, $this->user_active, $_SERVER['REMOTE_ADDR']);
				$stmt->execute();
				$inserted_id = $mysqli->insert_id;
				$stmt->close();

				//Insert user id to userprofile table
				$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."userprofile  (
					userId
					)
					VALUES (
					?
					)");
				$stmt->bind_param("s", $inserted_id);
				$stmt->execute();
				$stmt->close();
				
				//Insert default permission into matches table
				$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."user_permission_matches  (
					user_id,
					permission_id
					)
					VALUES (
					?,
					'1'
					)");
				$stmt->bind_param("s", $inserted_id);
				$stmt->execute();
				$stmt->close();
				
				//How about we send this new user a message within the site.
				//New User Message
				new_user_message_send($this->username, $inserted_id);
							
				//Now get this users ID and make them friends with DaVaR ID=1
				$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."friend  (
					userId1,
					userId2,
					status1,
					status2
					)
					VALUES (
					'1',
					?,
					'1',
					'1'
					)");
				$stmt->bind_param("s", $inserted_id);
				$stmt->execute();
				$stmt->close();	
				
			}
		}
	}
}

?>