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


if(!empty($site_adds_bot && $userAdds == "TRUE")){
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='content78' align='center'>";

	echo "$site_adds_bot";
	
	echo "</td></tr></table>";
}
?>