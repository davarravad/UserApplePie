<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////


// Build Security for Current Page if Any
$cur_page_get = "pages/".$_GET['page'].".inc";
if (!securePage($cur_page_get)){die();}

//Displays table for content
echo "<center>";
echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
echo "Welcome to ".$websiteName."'s Member Forgot Password Reset"; 
echo "</td></tr>";
echo "<tr><td class='content78' align='center'>";

//User has confirmed they want their password changed 
if(!empty($_GET["confirm"]))
{
	$token = trim($_GET["confirm"]);
	
	if($token == "" || !validateActivationToken($token,TRUE))
	{
		$errors[] = lang("FORGOTPASS_INVALID_TOKEN");
	}
	else
	{
		$rand_pass = getUniqueCode(15); //Get unique code
		$secure_pass = password_hash("$rand_pass", PASSWORD_DEFAULT); //Generate random hash
		$userdetails = fetchUserDetails(NULL,$token); //Fetchs user details
		$mail = new userCakeMail();		
		
		//Setup our custom hooks
		$hooks = array(
			"searchStrs" => array("#GENERATED-PASS#","#USERNAME#"),
			"subjectStrs" => array($rand_pass,$userdetails["display_name"])
			);
		
		if(!$mail->newTemplateMsg("your-lost-password.txt",$hooks))
		{
			$errors[] = lang("MAIL_TEMPLATE_BUILD_ERROR");
		}
		else
		{	
				$mail->sendMail($userdetails["email"],"Your new password");
				
				if(!updatePasswordFromToken($secure_pass,$token))
				{
					$errors[] = lang("SQL_ERROR");
				}
				else
				{	
					if(!flagLostPasswordRequest($userdetails["user_name"],0))
					{
						$errors[] = lang("SQL_ERROR");
					}
					else {
						$successes[]  = lang("FORGOTPASS_NEW_PASS_EMAIL");
					}
				}
			
		}
	}
}

//User has denied this request
if(!empty($_GET["deny"]))
{
	$token = trim($_GET["deny"]);
	
	if($token == "" || !validateActivationToken($token,TRUE))
	{
		$errors[] = lang("FORGOTPASS_INVALID_TOKEN");
	}
	else
	{
		
		$userdetails = fetchUserDetails(NULL,$token);
		
		if(!flagLostPasswordRequest($userdetails["user_name"],0))
		{
			$errors[] = lang("SQL_ERROR");
		}
		else {
			$successes[] = lang("FORGOTPASS_REQUEST_CANNED");
		}
	}
}

//Forms posted
if(!empty($_POST))
{
	$email = $_POST["email"];
	
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
	
	if(count($errors) == 0)
	{
		

			//Check if the user has any outstanding lost password requests
			//Add 3 nulls before email for this function to work with email only.
			$userdetails = fetchUserDetails(NULL,NULL,NULL,$email);
			if($userdetails["lost_password_request"] == 1)
			{
				$errors[] = lang("FORGOTPASS_REQUEST_EXISTS");
			}
			else
			{
				//Email the user asking to confirm this change password request
				//We can use the template builder here
				
				//We use the activation token again for the url key it gets regenerated everytime it's used.
				
				$mail = new userCakeMail();
				$confirm_url = lang("CONFIRM")." <a href='".$websiteUrl."forgot_password/?confirm=".$userdetails["activation_token"]."'>".$websiteUrl."forgot_password/?confirm=".$userdetails["activation_token"]."</a>";
				$deny_url = lang("DENY")." <a href='".$websiteUrl."forgot_password/?deny=".$userdetails["activation_token"]."'>".$websiteUrl."forgot_password/?deny=".$userdetails["activation_token"]."</a>";
				
				//Setup our custom hooks
				$hooks = array(
					"searchStrs" => array("#CONFIRM-URL#","#DENY-URL#","#USERNAME#"),
					"subjectStrs" => array($confirm_url,$deny_url,$userdetails["user_name"])
					);
				
				if(!$mail->newTemplateMsg("lost-password-request.txt",$hooks))
				{
					$errors[] = lang("MAIL_TEMPLATE_BUILD_ERROR");
				}
				else
				{

					$mail->sendMail($userdetails["email"],"Lost password request");
				
						//Update the DB to show this account has an outstanding request
						if(!flagLostPasswordRequest($userdetails["user_name"],1))
						{
							$errors[] = lang("SQL_ERROR");
						}
						else {
							
							$successes[] = lang("FORGOTPASS_REQUEST_SUCCESS");
						}
					
				}
			}
		
	}
}

echo "
<div id='main'>";

echo resultBlock($errors,$successes);

// Check to see if user name is in address bar
// If not show it blank
if(!empty($_GET["un"])){
	$usr_nm = $_GET["un"];
}else{
	$usr_nm = "";
}
	
echo "
<div id='regbox'>
<form name='newLostPass' action='/forgot_password/' method='post'>
<p>    
<label>Email:</label>
<input type='text' name='email' />
</p>
<p>
<label>&nbsp;</label>
<input type='submit' value='Submit' class='submit' />
</p>
</form>
</div>
</div>
<div id='bottom'></div>
</div>
</body>
</html>";

echo "</td></tr></table>";

?>
