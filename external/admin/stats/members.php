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



$query = "SELECT * FROM `".$db_table_prefix."userprofile` ";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 1231588");


$rows = mysqli_num_rows($result); 




	if ($rows) {
		echo "<b><a href='${site_url_link}members/'>Members</a></b>: $rows";
	}
	else {
		echo "<b>Members</b>: 0";
	}


?>

