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


//This script gets all new information for admin and displays it in the welcome member section of main page

// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){
	echo " ( ";

		
	//Get total number of error reports

	$query_errors = "SELECT * FROM `".$db_table_prefix."errors` ";
	$result_errors = mysqli_query($GLOBALS["___mysqli_ston"], $query_errors);
	$num_rows_errors = mysqli_num_rows($result_errors);
		
		echo " <a href='${site_url_link}UAP_Admin_Panel/errors/'>$num_rows_errors Errors</a>";

		
	//Get total number of reports

	$query_reports = "SELECT * FROM `".$db_table_prefix."report` ";
	$result_reports = mysqli_query($GLOBALS["___mysqli_ston"], $query_reports);
	$num_rows_reports = mysqli_num_rows($result_reports);
		
		echo " | <a href='${site_url_link}UAP_Admin_Panel/reports/'>$num_rows_reports Reports</a>";

		
		
	echo " ) ";
}//End Admin check
?>