<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////



ob_start();

require_once("models/config.inc");
	//Get the Page the user has requested to view
	if(isset($_REQUEST['page']) || isset($_REQUEST['taz'])){
		if(isset($_REQUEST['page'])){ $taz = $_REQUEST['page']; }
		if(isset($_REQUEST['taz'])){ $taz = $_REQUEST['taz']; }
		if (!securePage($taz)){die();}
	}else{
		if (!securePage($_SERVER['PHP_SELF'])){die();}
	}


// Get user information
if(isset($loggedInUser->user_id)){
	$get_loggedin_uid = $loggedInUser->user_id;
}else{
	$get_loggedin_uid = "0";
}
$userId = $get_loggedin_uid;

require("models/members/funcs_user_info.inc");
require("models/functions.inc");
require("models/sublinks.inc");
require("models/funcs_styles.inc");

// Run the page handler
require("models/pagehand.inc");

// Header of the site
require_once("models/design/header.inc");
	
	//Displays all the main content stuff

	//Site adds
	if($debug_addsoff == 'TRUE'){}else{
		require "models/adds.inc"; 
	}
	
	//Shows a success_message if there is one.
	success_message();

	//Admin Message
	require "models/adminmessage.inc";
	//This is the Main content table.  All pages will be loaded here.
	//
	
			if(isset($tazib_filerun)){}else{ $tazib_filerun = "";}
			if($tazib_filerun == 'YESRUN'){
				require("$tazib_file"); 
			} else {
				if(!empty($tazib_content)){ echo "$tazib_content"; }else{ }	
			}
			if(isset($er)){
				if($er == 'YESError'){
					require("models/errorreport.inc");	
				}
			}
			
	//Shows adds if FALSE
	if($debug_addsoff == 'TRUE'){}else{
		require "models/adds2.inc"; 
	}
			
	require "models/report.inc";
	
// Footer of the site
require_once("models/design/footer.inc");
?>
