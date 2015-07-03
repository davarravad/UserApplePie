<?php
//Title and Description
	//echo "<title>My Car Truck Clubs Zone</title>";
		//Displays logged in users welcome pannel

if(isUserLoggedIn()){

		if(isset($_REQUEST['pee'])){ $pee = $_REQUEST['pee']; }else{$pee = "";}
		
		if($pee){}
		else { $pee = "friendstatus"; }
		
		

	require("models/communitylinks.inc");


//Content load
	require("models/welcomemem.inc");
	echo "<center><table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
	echo "$ity_title";
	echo "</td></tr><tr><td class='content78'>";

		//START OF CONTENT
		
		if($pee){
			$pee1 = "pages/my/";
			$pee2 = ".inc";
			$pee_file = "${pee1}${pee}${pee2}";
			
			if($pee){
				if(file_exists($pee_file)) {
					require "$pee_file";
				} else {
					echo "
						<center>
						The page <font color=red>$pee</font> does NOT exist!<br>
						<br>
						Go back or go <a href='../'>Home</a></center>
					";
					
					//Reporting page error
					$er_type = "Community Page Error";
					$er_location = "?pee=$pee";
					$er_msg = "?pee= error - page $taz does not exist";
					$er = "YESError";
				}
			} else {
				echo "<br><center>Please select one of the above links corresponding to what you would like to do.</center><br>";
			}
		
		}
		else {
				require "pages/my/friendstatus.inc";
		}
		
		//END OF CONTENT
		





}
else {
	notlogedinmsg();
}
	echo "</td></tr></table></center>";
?>