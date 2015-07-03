<?php
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