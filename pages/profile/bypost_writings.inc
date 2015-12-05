<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

$query = "SELECT * FROM submit WHERE `name` = '$nname'";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 8465132");


//HTML Stuff

echo "<br><span class='title'>Writings</span><br>";

while ($row = mysqli_fetch_array($result))
{

	extract($row);

	if($type == Poem){
		$taz_type = "poems";
	}
	if($type == Story){
		$taz_type = "stories";
	}
	if($type == Quote){
		$taz_type = "quotes";
	}

		echo "&nbsp - <span class='title'>Title</span>: ";	
		echo "<a href='${site_url_link}VehicleProfile/$int/'>$title</a> "; 
		echo "&nbsp; <span class='title'>Type</span>: ";
		echo "<a href='${site_url_link}$taz_type/'>$type</a> <br>";



	

}

?>