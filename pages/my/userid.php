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


// Delete this file I think
$queryw = "SELECT * FROM ".$db_table_prefix."users WHERE `userName`='$name' ";
$resultw = mysqli_query($GLOBALS["___mysqli_ston"], $queryw)
	or die ("Couldn't ececute query. my/userid 3983");


		
while ($row = mysqli_fetch_array($resultw))
{
	extract($row);	
		
	$com_id = $userId;

	//echo "$com_id";

}

?>