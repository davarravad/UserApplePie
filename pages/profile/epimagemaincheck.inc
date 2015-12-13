<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

$query2 = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$userId' LIMIT 1 ";

$result2 = mysqli_query($GLOBALS["___mysqli_ston"], $query2)
	or die ("Couldn't ececute query. 98465152");

   if( $result2 && $contact2 = mysqli_fetch_object( $result2 ) )
   {
      
	$mainPic = $contact2 -> mainPic;

   }


	$mymainPic = $mainPic;	

	//echo "$mymainPic";
?>