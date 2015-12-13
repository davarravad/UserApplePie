 <script type=\"text/javascript\">
 var RecaptchaOptions = {
    theme : 'clean'
 };
 </script>

<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Build Security for Current Page if Any
$cur_page_get = "pages/".$_GET['page'].".inc";
if (!securePage($cur_page_get)){die();}

//Prevent the user visiting the logged in page if he/she is already logged in
if(isUserLoggedIn()) { header("Location: /"); die(); }


// Page title
$stc_page_title = "$websiteName Member Registration";
// Page Description
$stc_page_description = "Member Registration Form - Sign up and enjoy all that $websiteName has to offer - $site_url_link";



// Run Header of page func
style_header_content($stc_page_title, $stc_page_description);



/////////////////////////
//Check to see if ip address already exist
$ipchecker = $_SERVER['REMOTE_ADDR'];	
//echo "$ipchecker";

$ipqueryec = "SELECT * FROM `".$db_table_prefix."users` WHERE `userIP`='$ipchecker' ";

global $mysqli, $site_url_link, $site_forum_title;

if ($result = $mysqli->query("$ipqueryec")) {

	/* determine number of rows result set */
	$iprowsec = $result->num_rows;

	/* close result set */
	$result->close();
}

//echo " $ipchecker - $iprowsec ";

if($iprowsec < 2){
	$reg_ipok = TRUE;
	//echo "OK Go";
}else{
	$reg_ipok = FALSE;
	//echo "No Go";
}
				
if($reg_ipok == FALSE){ 
	err_message('Sorry, Your IP address has been used before! We can not allow you to register for this website. Contact Administrator for more info.');
	die;
}
//End ip check
///////////////////////////


//Forms posted
if(!empty($_POST))
{
	global $captcha;
	$errors = array();
	$email = trim($_POST["email"]);
	$username = trim($_POST["username"]);
	$displayname = trim($_POST["displayname"]);
	$password = trim($_POST["password"]);
	$confirm_pass = trim($_POST["passwordc"]);
	
	//Token validation function
	if(!is_valid_token()){ 
		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');
		die;
	}
	// Google Captcha Check
	$privatekey = $recap_secretkey;
	if(isset($_POST['g-recaptcha-response'])){
		$captcha=$_POST['g-recaptcha-response'];
	}
	if(!$captcha){
		//What happens when the CAPTCHA was entered incorrectly
		//err_message("Sorry, The reCAPTCHA was not entered correctly! Please try again!");
		//die;	
		$errors[] = lang("CAPTCHA_FAIL");
	}
	$response=file_get_contents("https://www.google.com/recaptcha/api/siteverify?secret=".$privatekey."&response=".$captcha."&remoteip=".$_SERVER['REMOTE_ADDR']);
	if($response.'success'==false)
	{
		$errors[] = lang("CAPTCHA_FAIL");
	}
	if(minMaxRange(5,25,$username))
	{
		$errors[] = lang("ACCOUNT_USER_CHAR_LIMIT",array(5,25));
	}
	if(!preg_match("/^[a-zA-Z\p{Cyrillic}0-9]+$/u", $username)){
		$errors[] = lang("ACCOUNT_USER_INVALID_CHARACTERS");
	}
	if(minMaxRange(5,25,$displayname))
	{
		$errors[] = lang("ACCOUNT_DISPLAY_CHAR_LIMIT",array(5,25));
	}
	if(!preg_match("/^[a-zA-Z\p{Cyrillic}0-9\s\-\_]+$/u", $displayname)){
		$errors[] = lang("ACCOUNT_DISPLAY_INVALID_CHARACTERS");
	}
	if(minMaxRange(8,50,$password) && minMaxRange(8,50,$confirm_pass))
	{
		$errors[] = lang("ACCOUNT_PASS_CHAR_LIMIT",array(8,50));
	}
	else if($password != $confirm_pass)
	{
		$errors[] = lang("ACCOUNT_PASS_MISMATCH");
	}
	if(!isValidEmail($email))
	{
		$errors[] = lang("ACCOUNT_INVALID_EMAIL");
	}
	//End data validation
	if(count($errors) == 0)
	{	
		//Construct a user object
		$user = new User($username,$displayname,$password,$email);
		
		//Checking this flag tells us whether there were any errors such as possible data duplication occured
		if(!$user->status)
		{
			if($user->username_taken) $errors[] = lang("ACCOUNT_USERNAME_IN_USE",array($username));
			if($user->displayname_taken) $errors[] = lang("ACCOUNT_DISPLAYNAME_IN_USE",array($displayname));
			if($user->email_taken) 	  $errors[] = lang("ACCOUNT_EMAIL_IN_USE",array($email));		
		}
		else
		{
			//Attempt to add the user to the database, carry out finishing  tasks like emailing the user (if required)
			if(!$user->userCakeAddUser())
			{
				if($user->mail_failure) $errors[] = lang("MAIL_ERROR");
				if($user->sql_failure)  $errors[] = lang("SQL_ERROR");
			}
		}
	}
	if(count($errors) == 0) {
		$successes[] = $user->success;
	}
}


echo resultBlock($errors,$successes);

echo "<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";

?>

<script type="text/javascript">
$(document).ready(function()
{    
 $("#username").keyup(function()
 {  
  var name = $(this).val(); 
  
  if(name.length > 4)
  {  
   $("#resultun").html('');
   
   /*$.post("username-check.php", $("#reg-form").serialize())
    .done(function(data){
    $("#result").html(data);
   });*/
   
   $.ajax({
    
    type : 'POST',
    url  : '/pages/user_name_check.php',
    data : $(this).serialize(),
    success : function(data)
        {
              /*$("#resultun").html(data);*/
			if(data == 'OK')
			{
			   $("#resultun").html("<i class='glyphicon glyphicon-ok text-success'></i>");
			   $("#resultun2").html("");	
			}
			if(data == 'CHAR')
			{
			   $("#resultun").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultun2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>User Name Invalid!</div>");	
			}
			if(data == 'INUSE')
			{
			   $("#resultun").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultun2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>User Name is already in use.</div>");	
			}
        }
    });
    return false;
   
  }
  else
  {
   $("#resultun").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
   $("#resultun2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>User Name must be at least <strong>5</strong> characters.</div>");
  }
 });
 
});
</script>

<script type="text/javascript">
$(document).ready(function()
{    
 $("#displayname").keyup(function()
 {  
  var name = $(this).val(); 
  
  if(name.length > 4)
  {  
   $("#resultdn").html('');
   
   /*$.post("username-check.php", $("#reg-form").serialize())
    .done(function(data){
    $("#result").html(data);
   });*/
   
   $.ajax({
    
    type : 'POST',
    url  : '/pages/user_display_name_check.php',
    data : $(this).serialize(),
    success : function(data)
        {
              /*$("#resultun").html(data);*/
			if(data == 'OK')
			{
			   $("#resultdn").html("<i class='glyphicon glyphicon-ok text-success'></i>");
			   $("#resultdn2").html("");	
			}
			if(data == 'CHAR')
			{
			   $("#resultdn").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultdn2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>Display Name Invalid.</div>");	
			}
			if(data == 'INUSE')
			{
			   $("#resultdn").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultdn2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>Display Name is already in use.</div>");	
			}
			if(data == 'SAME')
			{
			   $("#resultdn").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultdn2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>This is already your Display Name.</div>");	
			}
        }
    });
    return false;
   
  }
  else
  {
   $("#resultdn").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
   $("#resultdn2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>Display Name must be at least <strong>5</strong> characters.</div>");
  }
 });
 
});
</script>

<script type="text/javascript">
$(document).ready(function()
{    
 $("#email").keyup(function()
 {  
  var name = $(this).val(); 
  
  if(name.length > 4)
  {  
   $("#resultemail").html('');
   
   /*$.post("username-check.php", $("#reg-form").serialize())
    .done(function(data){
    $("#result").html(data);
   });*/
   
   $.ajax({
    
    type : 'POST',
    url  : '/pages/user_email_check.php',
    data : $(this).serialize(),
    success : function(data)
        {
              /*$("#resultun").html(data);*/
			if(data == 'OK')
			{
			   $("#resultemail").html("<i class='glyphicon glyphicon-ok text-success'></i>");
			   $("#resultemail2").html("");	
			}
			if(data == 'BAD')
			{
			   $("#resultemail").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultemail2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>Email Address Invalid!</div>");	
			}
			if(data == 'INUSE')
			{
			   $("#resultemail").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultemail2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>Email is already in use.</div>");	
			}
        }
    });
    return false;
   
  }
  else
  {
   $("#resultemail").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
   $("#resultemail2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>Email must be at least <strong>5</strong> characters.</div>");
  }
 });
 
});
</script>

<script src="../models/jq-pw-strength.js"></script>
 
<?php

	if(empty($username)){$username = "";}
	if(empty($displayname)){$displayname = "";}
	if(empty($email)){$email = "";}

echo"
<center>
<div class='panel panel-info' style='max-width: 500px'>
<div class='panel-heading'>
	<div class='panel-title'>Register</div>
</div>
<div class='pannel-body' style='padding-top:10px'>
	<form name='newUser' action='".$site_url_link."register/' method='post'>

		<div class='input-group' style='width: 80%; margin-bottom: 5px'>
			<span class='input-group-addon'><i class='glyphicon glyphicon-user'></i></span>
			<input id='username' type='text' name='username' value='$username' class='form-control' placeholder='User Name' aria-describedby='basic-addon1' />
			<span id='resultun' class='input-group-addon'></span>
		</div>
		<div class='form-group' style='width: 75%; margin-bottom: 5px'>
			
			<font size=1>Pick a username you will remember.</font>
		</div>
			
		<div class='input-group' style='width: 80%; margin-bottom: 5px'>
			<span class='input-group-addon'><i class='glyphicon glyphicon-user'></i></span>
			<input id='displayname' type='text' name='displayname' value='$displayname' class='form-control' placeholder='Display Name' aria-describedby='basic-addon1' />
			<span id='resultdn' class='input-group-addon'></span>
		</div>
		<div class='form-group' style='width: 75%; margin-bottom: 5px'>
			<font size=1>Your Display Name can be changed at any time.</font>
		</div>

		<div class='input-group' style='width: 80%; margin-bottom: 5px'>
			<span class='input-group-addon'><i class='glyphicon glyphicon-lock'></i></span>
			<input type='password' name='password' id='passwordInput' class='form-control' placeholder='Password' aria-describedby='basic-addon1'/>
			<span id='password01' class='input-group-addon'></span>
		</div>
		<div class='form-group' style='width: 75%; margin-bottom: 5px'>
			<font size=1>Pick a password you will remember.</font>
		</div>
			
		<div class='input-group' style='width: 80%; margin-bottom: 5px'>
			<span class='input-group-addon'><i class='glyphicon glyphicon-lock'></i></span>
			<input type='password' name='passwordc' id='confirmPasswordInput' class='form-control' placeholder='Confirm Password' aria-describedby='basic-addon1'/>
			<span id='password02' class='input-group-addon'></span>
		</div>
		<div class='form-group' style='width: 75%; margin-bottom: 5px'>
			<font size=1>Confirm Your Password.</font>
		</div>
			
		<div class='input-group' style='width: 80%; margin-bottom: 5px'>
			<span class='input-group-addon'><i class='glyphicon glyphicon-envelope'></i></span>
			<input type='text' id='email' name='email' value='$email' class='form-control' placeholder='Email' aria-describedby='basic-addon1'/>
			<span id='resultemail' class='input-group-addon'></span>
		</div>
		<div class='form-group' style='width: 75%; margin-bottom: 5px'>
			<font size=1>Please use Current Working Email so you can activate your ".$websiteName." account.  Check your Email and click the link provided.</font>
		</div>
	";

		// Form token. Place within from tag
		// create multi sessions
		if(isset($session_token_num)){
			$session_token_num = $session_token_num + 1;
		}else{
			$session_token_num = "1";
		}
		form_token();

		// Setup Google Captcha
		$publickey = $recap_sitekey; // you got this from the signup page
		echo "
			<div class=\"g-recaptcha\" data-sitekey=\"".$publickey."\"></div>
			<script type=\"text/javascript\" src=\"https://www.google.com/recaptcha/api.js?hl=en\">
			</script>
		";
		
	echo "<div class='panel'>
			<span id='resultun2' class='label'></span>
			<span id='resultdn2' class='label'></span>
			<span class='label' id='passwordStrength'></span>
			<span id='resultemail2' class='label'></span>
		  </div>
	
		<button type='submit' class='btn btn-success btn-lg'  data-loading-text='Please wait...' >
			Register
		</button>
	</form>
</div>
</div>
</center>
";

// Run Footer of page func
style_footer_content();

?>
