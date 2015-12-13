<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Check to see if user has a main pic
//echo "(MainPic - $imgname - $userIdme)";

$queryx = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$userIdme' LIMIT 1 ";

$resultx = mysqli_query($GLOBALS["___mysqli_ston"], $queryx)
	or die ("Couldn't ececute query. 4651222");

while ($row = mysqli_fetch_array($resultx))
{
	extract($row);

	//echo "($mainPic)";

}

//If user does not have a main pic set this one as their main
if($mainPic == "noimg.gif"){
		$query = "UPDATE `".$db_table_prefix."userprofile` SET `mainPic`='$imgname' WHERE `userId`='$userIdme' ";

		$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );
		if( $results ){
			echo "Image set as your Main Profile Pic!";
		}else{
			//Code used to report mysql error
			$mysql_error_report = "TRUE";
			$sql_query = "$query";
			require "models/mysql_error_report.inc";
		}
}
?>