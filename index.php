<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

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
