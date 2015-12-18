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

if($enable_photos == "TRUE"){
	if($usemobile == "TRUE"){ $imgw = "35"; }else{ $imgw = "100"; }

	$queryx = "SELECT `".$db_table_prefix."userprofile`.`mainPic` FROM ".$db_table_prefix."userprofile WHERE `userId`='$ID02' LIMIT 1 ";

	$resultx = mysqli_query($GLOBALS["___mysqli_ston"], $queryx)
		or die ("Couldn't ececute query. 5416412");


	echo "<table><tr>";

	while ($row = mysqli_fetch_array($resultx))
	{
		extract($row);

		echo "<td>";
		echo "<img class='rounded_10' style='max-height:$imgwA;' border='0' width='$imgw' src='http://".$site_dir."/content/profile/thumb/${mainPic}'>";
		//echo "<br><center>$content1</center>";
		echo "</td>";
	}

	echo "</tr></table>";
}

?>