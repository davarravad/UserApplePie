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
echo "Welcome to ".$websiteName."'s Member Login"; 
echo "</td></tr>";
echo "<tr><td class='content78' align='center'>";

//Get token param
if(isset($_GET["token"]))
{	
	$token = $_GET["token"];	
	if(!isset($token))
	{
		$errors[] = lang("FORGOTPASS_INVALID_TOKEN");
	}
	else if(!validateActivationToken($token)) //Check for a valid token. Must exist and active must be = 0
	{
		$errors[] = lang("ACCOUNT_TOKEN_NOT_FOUND");
	}
	else
	{
		//Activate the users account
		if(!setUserActive($token))
		{
			$errors[] = lang("SQL_ERROR");
		}
	}
}
else
{
	$errors[] = lang("FORGOTPASS_INVALID_TOKEN");
}

if(count($errors) == 0) {
	$successes[] = lang("ACCOUNT_ACTIVATION_COMPLETE");
}

echo "
<div id='main'>";

echo resultBlock($errors,$successes);

echo "
</div>
<div id='bottom'></div>
</div>
</body>
</html>";

echo "</td></tr></table>";

?>
