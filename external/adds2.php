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
	echo "<div class='panel panel-default'>";
		echo "<div class='panel-body'>";

			echo "$site_adds_bot";
		
		echo "</div>";
	echo "</div>";
}
?>