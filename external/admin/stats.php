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


// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){


			echo "<center>";
			echo "<strong>Admin Zone - ".$websiteName." Stats</strong>"; 
			echo "</center><br><Br>";

			require "./external/admin/stats/online.php";
			echo "<br>";
			require "./external/admin/stats/members.php";

}

	
?>