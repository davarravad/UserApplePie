<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Check to see if Admin is viewing admin panel
if(isset($_REQUEST['page'])){$page_check = $_REQUEST['page'];}else{$page_check = "";}
if($page_check == 'UAP_Admin_Panel'){
	// Run the admin page
	require "models/admin/zpanel.inc";
}else{
	// Run the website 

	// Header of the site
	require_once("models/design/header.inc");
		
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

	// Footer of the site
	require_once("models/design/footer.inc");
}// End of admin check

?>
