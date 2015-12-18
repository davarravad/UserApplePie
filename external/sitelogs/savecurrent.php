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


if(isset($userName)){
	$nname_log = "$userName-($userIdme)";
}else{
	$nname_log = "Visitor";
}

      $query_SS = "INSERT INTO `".$db_table_prefix."sitelogs` SET `membername`='$nname_log', `refer`='$refer', `useragent`='$useragent', `cfile`='$cfile', `uri`='$uri', `ipaddy`='$ipaddy', `server`='$server' ";
  
  

 $results_SS = mysqli_query($GLOBALS["___mysqli_ston"],  $query_SS );

   // print out the results
   if( $results_SS )
   {
     // echo( "<br><CENTER>Logged for Stats</CENTER>" );
   }
 
   else
   {
     // die( "<br><CENTER><font color=red>NOT Logged for Stats</font></CENTER>" );
   }

   
   
?>