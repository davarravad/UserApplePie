<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Code by David Sargent (DaVaR) davarravad@gmail.com
//Mysql error report 
//This code submits an error to the database if there is a 
//problem with a sql query


//Code used to report mysql error
//$mysql_error_report = "TRUE";
//$sql_query = "$query";
//require "models/mysql_error_report.inc";


if($mysql_error_report == "TRUE"){

	//Setup the error report for database
	//Reporting page error
	$er_type = "Save to mySQL Error: $sql_query";
	$er_location = "mySQL";
	$er_msg = "Database Error: " . ((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_error($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_error()) ? $___mysqli_res : false)) ;
	//Clean up the error display so it will save
	$er_msg = addslashes($er_msg);
	$er_type = addslashes($er_type);

	//Include the file that saves error to database
	require("models/errorreport.inc");

	//Sends error message to session
	//Shows user error when they are redirected
	$success_msg = "<font color=red>There was an Error with your Request, Please try again later. <br><Br> Your previous information was NOT saved to our database.  Sorry for the Inconvenience.  We will look into this issue and get it fixed.</font>";
	$_SESSION['success_msg'] = $success_msg;
	
	//Redirects the user back to the previous page they were on
	$redir_link_url = "$er_refer";
	
	// Redirect member to their post
	header("Location: $redir_link_url");
	exit;
	
	//If there is an error kill the database connection.
	die( "There was an Error with your Request, Please try again later." );

}

?>