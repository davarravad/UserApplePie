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


//Title and Description
		//Displays logged in users welcome pannel

if(isUserLoggedIn()){

		if(isset($_REQUEST['pee'])){ $pee = $_REQUEST['pee']; }else{$pee = "";}
		
		if($pee){}
		else { $pee = "friendstatus"; }
		
		

	require("external/communitylinks.php");


//Content load
	require("external/welcomemem.php");
	
	// Page title
	$stc_page_title = "$ity_title";
	// Page Description
	$stc_page_description = "Complete list of all ".$websiteName." Site Members.";

	// Run Header of page func
	style_header_content($stc_page_title, $stc_page_description);

		//START OF CONTENT
		
		if($pee){
			$pee1 = "pages/my/";
			$pee2 = ".php";
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
				require "pages/my/friendstatus.php";
		}
		
		//END OF CONTENT
		

// Run Footer of page func
style_footer_content();



}
else {
	notlogedinmsg();
}

?>