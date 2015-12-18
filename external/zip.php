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


if($zip){

   // retrieve the row from the database
   $queryzip = "SELECT * FROM `".$db_table_prefix."cities_extended` WHERE `zip`='$zip' ";
   
   $resultzip = mysqli_query($GLOBALS["___mysqli_ston"],  $queryzip );

   // print out the results
   if( $resultzip && $contactzip = mysqli_fetch_object( $resultzip ) )
   {
		// print out the info
		$city = $contactzip -> city;
		$state_code = $contactzip -> state_code;
		$latitude = $contactzip -> latitude;
		$longitude = $contactzip -> longitude;
		$county = $contactzip -> county;
   }

}

?>