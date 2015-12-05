 <script type=\"text/javascript\">
 var RecaptchaOptions = {
    theme : 'clean'
 };
 </script>

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


echo "

<div style='main'>";

echo resultBlock($errors,$successes);

echo "<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.8.0/jquery.min.js\"></script>";

?>

<SCRIPT type="text/javascript">
<!--
 
pic1 = new Image(16, 16);
pic1.src = "/images/loader.gif";
 
$(document).ready(function(){
 
$("#username").on('keyup',function() {  
 
var usr = $("#username").val();
 
if(usr.length >= 5)
{
$("#status").html('<img src="/images/loader.gif" align="absmiddle">&nbsp;Checking availability...');
 
    $.ajax({  
    type: "POST",  
    url: "/pages/user_name_check.php",  
    data: "username="+ usr,  
    success: function(msg){  
  
   $("#status").ajaxComplete(function(event, request, settings){
 
    if(msg == 'OK')
    {
        $("#username").removeClass('object_error'); // if necessary
        $("#username").addClass("object_ok");
        $(this).html('&nbsp;<img src="/images/tick.gif" align="absmiddle"> <font color=green>User Name is Good!</font>');
    }  
    else  
    {  
        $("#username").removeClass('object_ok'); // if necessary
        $("#username").addClass("object_error");
        $(this).html(msg);
    }  
  
   });
 
}
  
  });
 
}
else
    {
    $("#status").html('<font color="red">User Name must be at least <strong>5</strong> characters.</font>');
    $("#username").removeClass('object_ok'); // if necessary
    $("#username").addClass("object_error");
    }
 
});
 
});
 
//-->
</SCRIPT>

<SCRIPT type="text/javascript">
<!--
 
pic1 = new Image(16, 16);
pic1.src = "/images/loader.gif";
 
$(document).ready(function(){
 
$("#displayname").on('keyup',function() {  
 
var usr = $("#displayname").val();
 
if(usr.length >= 5)
{
$("#status2").html('<img src="/images/loader.gif" align="absmiddle">&nbsp;Checking availability...');
 
    $.ajax({  
    type: "POST",  
    url: "/pages/user_display_name_check.php",  
    data: "displayname="+ usr,  
    success: function(msg){  
  
   $("#status2").ajaxComplete(function(event, request, settings){
 
    if(msg == 'OK')
    {
        $("#displayname").removeClass('object_error'); // if necessary
        $("#displayname").addClass("object_ok");
        $(this).html('&nbsp;<img src="/images/tick.gif" align="absmiddle"> <font color=green>Display Name is Good!</font>');
    }  
    else  
    {  
        $("#displayname").removeClass('object_ok'); // if necessary
        $("#displayname").addClass("object_error");
        $(this).html(msg);
    }  
  
   });
 
}
  
  });
 
}
else
    {
    $("#status2").html('<font color="red">User Name must be at least <strong>5</strong> characters.</font>');
    $("#displayname").removeClass('object_ok'); // if necessary
    $("#displayname").addClass("object_error");
    }
 
});
 
});
 
//-->
</SCRIPT>

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

 <script src="../models/jq-pw-strength.js"></script>
 
<?php

	if(empty($username)){$username = "";}
	if(empty($displayname)){$displayname = "";}
	if(empty($email)){$email = "";}

echo"



<div id='regbox'>
<form name='newUser' action='".$site_url_link."register/' method='post'>

<table width='80%' align='center' class='index_headertable3tbl'>
<tr><td class='epboxb'>
		<label>User Name:</label>
</td><td class='epboxa'>
		<input id='username' type='text' name='username' value='$username' /> 
</td></tr><tr><td class='epboxa' colspan='2'>
		<font size=1>Pick a username you will remember.</font>
		<br><span id='status'></span>
		
</td></tr><tr><td class='epboxb'>
		<label>Display Name:</label>
</td><td class='epboxa'>
		<input id='displayname' type='text' name='displayname' value='$displayname' /> 
</td></tr><tr><td class='epboxa' colspan='2'>
		<font size=1>Your Display Name can be changed at any time.</font>
		<br><span id='status2'></span>
		
</td></tr><tr><td class='epboxb'>
		<label>Password:</label>
</td><td class='epboxa'>
		<input type='password' name='password' id='passwordInput' />
</td></tr><tr><td class='epboxa' colspan='2'>
		<font size=1>Pick a password you will remember.</font>
		
	<table width=100% border=0><tr><td width=102px>
		<div id='ppbar' title='Strength'><div id='pbar'></div></div>
	</td><td>
		<div class='' id='passwordStrength'></div>
	</td></tr></table>
		
</td></tr><tr><td class='epboxb'>
		<label>Confirm:</label>
</td><td class='epboxa'>
		<input type='password' name='passwordc' id='confirmPasswordInput' />
</td></tr><tr><td class='epboxa' colspan='2'>
		<font size=1>Confirm Your Password.</font>
		
</td></tr><tr><td class='epboxb'>
		<label>Email:</label>
</td><td class='epboxa'>
		<input type='text' name='email' value='$email' />
</td></tr><tr><td class='epboxa' colspan='2'>
		<font size=1>Please use Current Working Email so you can activate your ".$websiteName." account.  Check your Email and click the link provided.</font>
</td></tr><tr><td colspan='2' align='center'>
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
	
echo "
</td></tr><tr><td align=center colspan='2'>
		<input type='submit' value='Register'/>
</td></tr></table>
</form>
</div>

</div>

</div>
";

// Run Footer of page func
style_footer_content();

?>
