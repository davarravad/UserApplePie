<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){


			echo "<center>";
			echo "<strong>Admin Zone - ".$websiteName." Stats</strong>"; 
			echo "</center><br><Br>";

			require "models/admin/stats/online.inc";
			echo "<br>";
			require "models/admin/stats/members.inc";

}

	
?>