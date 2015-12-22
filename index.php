<?php
//////////////////////////////////
// UserApplePie Version: 1.1.1  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Security Feature to Disallow File to be opened directly.
// Sets this page (index.php) as the main file that is allowed
// to include protected files
define('Page_Protection', TRUE);

// Check to see if Admin is viewing admin panel
if(isset($_REQUEST['page'])){$page_check = $_REQUEST['page'];}else{$page_check = "";}
if($page_check == 'UAP_Admin_Panel'){
	// Run the admin page
	require "external/admin/zpanel.php";
}else{
	// Run the website 

	// Header of the site
	require_once("external/design/header.php");
		
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
						require("external/errorreport.php");	
					}
				}

	// Footer of the site
	require_once("external/design/footer.php");
}// End of admin check

?>
