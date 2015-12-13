<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

require_once("models/config.inc");
// Build Security for Current Page if Any
$cur_page_get = "pages/".$_GET['page'].".inc";
if (!securePage($cur_page_get)){die();}

//Prevent the user visiting the logged in page if he is not logged in
if(!isUserLoggedIn()) { header("Location: /login/"); die(); }

// Show Links for account settings
account_settings_links();

if(!empty($_POST))
{
	$errors = array();
	$successes = array();
	$password_cur = $_POST["password_cur"];
	$password_new = $_POST["passwordc"];
	$password_confirm = $_POST["passwordcheck"];
	
	$errors = array();
	$email = $_POST["email"];
	
	//Perform some validation

	// Remove spaces from begin and end of pass
	$password_cur = trim($password_cur);
	
	if (trim($password_cur) == ""){
		$errors[] = lang("ACCOUNT_SPECIFY_PASSWORD");
	}
	else if(!password_verify($password_cur, $loggedInUser->hash_pw))
	{
		//Password Does not match 
		$errors[] = lang("ACCOUNT_PASSWORD_INVALID");
	}	
	if($email != $loggedInUser->email)
	{
		if(trim($email) == "")
		{
			$errors[] = lang("ACCOUNT_SPECIFY_EMAIL");
		}
		else if(!isValidEmail($email))
		{
			$errors[] = lang("ACCOUNT_INVALID_EMAIL");
		}
		else if(emailExists($email))
		{
			$errors[] = lang("ACCOUNT_EMAIL_IN_USE", array($email));	
		}
		
		//End data validation
		if(count($errors) == 0)
		{
			$loggedInUser->updateEmail($email);
			$successes[] = lang("ACCOUNT_EMAIL_UPDATED");
		}
	}
	
	if ($password_new != "" OR $password_confirm != "")
	{
		if(trim($password_new) == "")
		{
			$errors[] = lang("ACCOUNT_SPECIFY_NEW_PASSWORD");
		}
		else if(trim($password_confirm) == "")
		{
			$errors[] = lang("ACCOUNT_SPECIFY_CONFIRM_PASSWORD");
		}
		else if(minMaxRange(8,50,$password_new))
		{	
			$errors[] = lang("ACCOUNT_NEW_PASSWORD_LENGTH",array(8,50));
		}
		else if($password_new != $password_confirm)
		{
			$errors[] = lang("ACCOUNT_PASS_MISMATCH");
		}
		
		//End data validation
		if(count($errors) == 0)
		{
			//Also prevent updating if someone attempts to update with the same password
			//$entered_pass_new = generateHash($password_new,$loggedInUser->hash_pw);
			
			if (password_verify($password_new, $loggedInUser->hash_pw))
			{
				//Don't update, this fool is trying to update with the same password Â¬Â¬
				$errors[] = lang("ACCOUNT_PASSWORD_NOTHING_TO_UPDATE");
			}
			else
			{
				//This function will create the new hash and update the hash_pw property.
				$loggedInUser->updatePassword($password_new);
				$successes[] = lang("ACCOUNT_PASSWORD_UPDATED");
			}
		}
	}
	if(count($errors) == 0 AND count($successes) == 0){
		$errors[] = lang("NOTHING_TO_UPDATE");
	}
}


?>

    <style>  
      #ppbar{  
       background:#CCC;  
       width:100px;  
       height:10px;  
       margin:0px;  
      }  
      #pbar{  
       margin:0px;  
       width:0px;  
       background:lightgreen;  
       height: 100%;  
      }  
      #passwordStrength{  
       text-align:left;  
       margin:0px;  
      }  
    </style>  
    <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.8.0/jquery.min.js"></script>  
      
	  

<?php

echo "<script src='".$site_url_link."models/jq-pw-strength.js'></script>";

echo resultBlock($errors,$successes);

echo "
<form name='updateAccount' action='/editprofilemain/account/' method='post'>
<table width='100%'><tr><td class=reg_form>
	<label>Password:</label>
</td><td class=reg_form>
	<input type='password' name='password_cur' class='form-control'/>
</td><td class=reg_form>
	Your Current Password
</td></tr>
<tr><td class=reg_form>
	<label>Email:</label>
</td><td class=reg_form>
	<input type='text' name='email' value='".$loggedInUser->email."' class='form-control' />
</td><td class=reg_form>
	Your Email Address
</td></tr>
<tr><td class=reg_form>
	<label>New Pass:</label>
</td><td class=reg_form>
	<input type='password' name='passwordc' id='passwordInput' class='form-control' />
</td><td class=reg_form>
	Your New Password
</td></tr>
<tr><td class=reg_form>
	<label>Confirm Pass:</label>
</td><td class=reg_form>
	<input type='password' name='passwordcheck' id='confirmPasswordInput' class='form-control' />
</td><td class=reg_form>
	Confirm Your New Password
</td></tr>
<tr><td colspan='3'> ";
 
echo "<div class='' id='passwordStrength'></div>";  

echo "
</td></tr>
<tr><td colspan='3' align='center'>
	<input type='submit' value='Update' class='btn btn-success btn-sm' />
</td></tr></table>
</form>


";

?>
