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



	#This script is built to get all possible information about a visitor
	#Shows Current User Information

 	
	#Get the Refering Page if There is one

		if(isset($_SERVER['HTTP_REFERER'])){ $refer = $_SERVER['HTTP_REFERER']; }else{ $refer = ""; } 


		if($refer) {
			#echo "<b>Referer:</b> $refer";
 		}
		else {
			#echo "<b>Referer:</b> None, Came Right to Us!";
		}

#echo "<br>";

	#Will return the type of web browser or user agent that is being used to access the current script.

		$useragent = $_SERVER['HTTP_USER_AGENT']; 


		if($useragent) {
			#echo "<b>Web Browser:</b> $useragent";
 		}
		else {
			#echo "<b>Web Browser:</b> Unknown!";
		}    

#echo "<br>";

	#The filename of the currently executing script, relative to the document root.

		$cfile = $_SERVER['PHP_SELF']; 


		if($cfile) {
			#echo "<b>Page Name:</b> $cfile";
 		}
		else {
			#echo "<b>Page Name:</b> Unknown!";
		}    

#echo "<br>";

	#Prints the exact path and filename relative to the DOCUMENT_ROOT of your site.

		$uri = $_SERVER['REQUEST_URI']; 


		if($uri) {
			#echo "<b>Page Name2:</b> $uri";
 		}
		else {
			#echo "<b>Page Name2:</b> Unknown!";
		}    

#echo "<br>";

	#Contains the IP address of the user requesting the PHP script from the server.

		$ipaddy = $_SERVER['REMOTE_ADDR']; 


		if($ipaddy) {
			#echo "<b>User IP:</b> $ipaddy";
 		}
		else {
			#echo "<b>User IP:</b> Unknown!";
		}    

#echo "<br>";


		$server = $_SERVER['SERVER_NAME']; 


		if($server) {
			#echo "<b>Server Name:</b> $server";
 		}
		else {
			#echo "<b>Server Name:</b> Unknown!";
		}    

#echo "<br>";


	require "./external/sitelogs/savecurrent.php";


?>