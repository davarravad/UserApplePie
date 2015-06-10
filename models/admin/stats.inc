<?php

	if(isUserLoggedIn()){

		if(is_admin()) {


			echo "<center>";
			echo "<strong>Admin Zone - CarTruckClubs.com Stats</strong>"; 
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