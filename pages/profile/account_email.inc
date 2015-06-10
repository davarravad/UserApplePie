
<?php 




if(isUserLoggedIn())
{

	// Show Links for account settings
	account_settings_links();

	echo "<center><table width='50%' border='0' cellspacing='0' cellpadding='0'><tr><td class='epboxb'>";
	
	require "pages/profile/privacy_email.inc";

	echo "</td></tr></table>";
	echo "</center><br>";
	
}
else {
	notlogedinmsg();	
}


?>
