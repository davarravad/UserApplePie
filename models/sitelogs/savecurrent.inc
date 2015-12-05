<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

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