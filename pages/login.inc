<?php
/*
UserCake Version: 2.0.2
http://usercake.com
*/

require_once("models/config.inc");
// Build Security for Current Page if Any
$cur_page_get = "pages/".$_GET['page'].".inc";
if (!securePage($cur_page_get)){die();}

//Prevent the user visiting the logged in page if he/she is already logged in
if(isUserLoggedIn()) { header("Location: /"); die(); }

//Displays the page title
//echo "<title>Car Truck Clubs Login</title>";
echo "<meta name='Description' content='Member Login Form - Login and enjoy all that Car Truck Clubs has to offer members - CarTruckClubs.com' />";

//Displays table for content
echo "<center>";
echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
echo "Welcome to $websiteName Member Login"; 
echo "</td></tr>";
echo "<tr><td class='content78'>";
		
	// Login Error check limiter
	if(!check_multi_logins()){ 

		//User is blocked for multi logins
		err_message('Sorry, Your have been temporarily blocked for multiple login fails.  Please try again later.
						<br><br>If you just registered for the site, check your email for the activation link.');
		die;
	}
		
//Forms posted
if(!empty($_POST))
{

	// Check to see if token is valid
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');
		die;
	}
	
	$errors = array();
	$username = sanitize(trim($_POST["username"]));
	$password = trim($_POST["password"]);
	
	//Perform some validation
	//Feel free to edit / change as required
	if($username == "")
	{
		$errors[] = lang("ACCOUNT_SPECIFY_USERNAME");
	}
	if($password == "")
	{
		$errors[] = lang("ACCOUNT_SPECIFY_PASSWORD");
	}

	if(count($errors) == 0)
	{
		//A security note here, never tell the user which credential was incorrect
		if((!usernameExists($username))&&(!emailExists($username)))
		{
			// Login Error Attempt Handler
			login_attm_hand();
			$errors[] = lang("ACCOUNT_USER_OR_PASS_INVALID");
		}
		else
		{
			//Check to see if username is an email or not
			if(emailExists($username)){
				$email = TRUE;
			}else{
				$email = FALSE;
			}
			
			// If email is true we are searching via email instead of username
			if($email){
				//echo "Getting email stuff";
				$userdetails = fetchUserDetails(NULL, NULL, NULL, $username);
			}else{
				$userdetails = fetchUserDetails($username);
			}

			//See if the user's account is activated
			if($userdetails["active"]==0)
			{
				$errors[] = lang("ACCOUNT_INACTIVE");
			}
			else
			{
			
				// Use built in PHP password hashing
				if (!password_verify($password, $userdetails["password"])) {
					// Login Error Attempt Handler
					login_attm_hand();
					//Again, we know the password is at fault here, but lets not give away the combination incase of someone bruteforcing
					$errors[] = lang("ACCOUNT_USER_OR_PASS_INVALID");
				}
				else
				{
					//Passwords match! we're good to go'
					
					//Construct a new logged in user object
					//Transfer some db data to the session object
					$loggedInUser = new loggedInUser();
					$loggedInUser->email = $userdetails["email"];
					$loggedInUser->user_id = $userdetails["id"];
					$loggedInUser->hash_pw = $userdetails["password"];
					$loggedInUser->title = $userdetails["title"];
					$loggedInUser->displayname = $userdetails["display_name"];
					$loggedInUser->username = $userdetails["user_name"];
					
					//Update last sign in
					$loggedInUser->updateLastSignIn();
					$_SESSION["userCakeUser"] = $loggedInUser;

					//Add the user to logged in table for is online status
					$aulio_uid = $userdetails["id"];
					add_user_logged_in_online($aulio_uid);
					
					//Login Success
					//Redirect to user
					//Check to see if user came from another page within the site
					if(isset($_SESSION['login_prev_page'])){ $login_prev_page = $_SESSION['login_prev_page']; }else{ $login_prev_page = ""; }
					
					if(!empty($login_prev_page)){
						//Remove the extra forward slash from link
						$login_prev_page = ltrim($login_prev_page, '/');
					
						//Send member to previous page
						//echo " ${site_url_link}${login_prev_page} ";
						
						//Redirects the user
						global $site_url_link;
						$redir_link_url = "${site_url_link}${login_prev_page}";
						
						//Clear the prev page session if set
						if(isset($_SESSION['login_prev_page'])){
							unset($_SESSION['login_prev_page']);
						}
						
						// Redirect member to their post
						header("Location: $redir_link_url");
					}else{
						//No previous page, send member to home page
						//echo " send user to home page ";
						
						//Redirects the user
						global $site_url_link;
						$redir_link_url = "${site_url_link}";
						
						//Clear the prev page session if set
						if(isset($_SESSION['login_prev_page'])){
							unset($_SESSION['login_prev_page']);
						}
						
						// Redirect member to their post
						header("Location: $redir_link_url");
					}
					die();
				}
			}
		}
	}
}



echo "
<center>
";

echo resultBlock($errors,$successes);

echo "

<form name='login' action='/login/' method='post'>

<table border=0><tr><td align='right'>
	<label>Username or Email:</label>
</td><td>
	<input type='text' name='username' size='30' />
</td><tr><tr><td align='right'>
	<label>Password:</label>
</td><td>
	<input type='password' name='password' size='30' />
</td></tr><tr><td colspan='2' align='center'>
	<input type='submit' value='Login' class='submit' />
</td></tr></table>";

	//Form token. Place within from tag
	// create multi sessions
	if(isset($session_token_num)){
		$session_token_num = $session_token_num + 1;
	}else{
		$session_token_num = "1";
	}
	form_token();

echo "
</form>


<br>";

echo "<a href='${site_url_link}register/'>Register</a> - ";
echo "<a href='${site_url_link}forgot_password/'>Forgot Password</a> - ";
echo "<a href='${site_url_link}resend_activation/'>Resend Activation Email</a>";

echo "
</center>
</body>
</html>";

	echo "</td></tr></table>";
	echo "</center>";

?>
