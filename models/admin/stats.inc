<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isUserLoggedIn()){

		if(is_admin()) {


			echo "<center>";
			echo "<strong>Admin Zone - ".$websiteName." Stats</strong>"; 
			echo "</center><br><Br>";

			require "models/admin/stats/online.inc";
			echo "<br>";
			require "models/admin/stats/members.inc";

		}
		else{
			echo "Admin Only.";
			exit();
		}

	}
	else{
		notlogedinmsg();
		exit();
	}
	
?>