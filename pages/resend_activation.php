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

//Displays table for content
echo "<center>";
echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
echo "Welcome to ".$websiteName."'s Member Resend Activation Token Link Form"; 
echo "</td></tr>";
echo "<tr><td class='content78' align='center'>";

//Forms posted
if(!empty($_POST) && $emailActivation)
{
	$email = $_POST["email"];
	$username = $_POST["username"];
	
	//Perform some validation
	//Feel free to edit / change as required
	if(trim($email) == "")
	{
		$errors[] = lang("ACCOUNT_SPECIFY_EMAIL");
	}
	//Check to ensure email is in the correct format / in the db
	else if(!isValidEmail($email) || !emailExists($email))
	{
		$errors[] = lang("ACCOUNT_INVALID_EMAIL");
	}
	
	if(trim($username) == "")
	{
		$errors[] =  lang("ACCOUNT_SPECIFY_USERNAME");
	}
	else if(!usernameExists($username))
	{
		$errors[] = lang("ACCOUNT_INVALID_USERNAME");
	}
	
	if(count($errors) == 0)
	{
		//Check that the username / email are associated to the same account
		if(!emailUsernameLinked($email,$username))
		{
			$errors[] = lang("ACCOUNT_USER_OR_EMAIL_INVALID");
		}
		else
		{
			$userdetails = fetchUserDetails($username);
			
			//See if the user's account is activation
			if($userdetails["active"]==1)
			{
				$errors[] = lang("ACCOUNT_ALREADY_ACTIVE");
			}
			else
			{
				if ($resend_activation_threshold == 0) {
					$hours_diff = 0;
				}
				else {
					$last_request = $userdetails["last_activation_request"];
					$hours_diff = round((time()-$last_request) / (3600*$resend_activation_threshold),0);
				}
				
				if($resend_activation_threshold!=0 && $hours_diff <= $resend_activation_threshold)
				{
					$errors[] = lang("ACCOUNT_LINK_ALREADY_SENT",array($resend_activation_threshold));
				}
				else
				{
					//For security create a new activation url;
					$new_activation_token = generateActivationToken();
					
					if(!updateLastActivationRequest($new_activation_token,$username,$email))
					{
						$errors[] = lang("SQL_ERROR");
					}
					else
					{
						$mail = new userCakeMail();
						
						$activation_url = "<a href='http://".$websiteUrl."activate_account/?token=".$new_activation_token."'>http://".$websiteUrl."activate_account/&token=".$new_activation_token."</a>";
						
						//Setup our custom hooks
						$hooks = array(
							"searchStrs" => array("#ACTIVATION-URL","#USERNAME#"),
							"subjectStrs" => array($activation_url,$userdetails["display_name"])
							);
						
						if(!$mail->newTemplateMsg("resend_activation.txt",$hooks))
						{
							$errors[] = lang("MAIL_TEMPLATE_BUILD_ERROR");
						}
						else
						{
							$mail->sendMail($userdetails["email"],"Activate your ".$websiteName." Account");

								//Success, user details have been updated in the db now mail this information out.
								$successes[] = lang("ACCOUNT_NEW_ACTIVATION_SENT");
							
						}
					}
				}
			}
		}
	}
}

//Prevent the user visiting the logged in page if he/she is already logged in
if(isUserLoggedIn()) { header("Location: /"); die(); }


echo "
<div id='main'>";

echo resultBlock($errors,$successes);

echo "<div id='regbox'>";

//Show disabled if email activation not required
if(!$emailActivation)
{ 
        echo lang("FEATURE_DISABLED");
}
else
{
	echo "<form name='resendActivation' action='/resend_activation/' method='post'>
	<p>
	<label>Username:</label>
	<input type='text' name='username' />
        </p>     
        <p>
        <label>Email:</label>
        <input type='text' name='email' />
        </p>    
        <p>
        <label>&nbsp;</label>
        <input type='submit' value='Submit' class='submit' />
        </p>
        </form>";
}

echo "
</div>           
</div>
<div id='bottom'></div>
</div>
</body>
</html>";

echo "</td></tr></table>";

?>
