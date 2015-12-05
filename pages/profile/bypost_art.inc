<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

$query = "SELECT * FROM art WHERE `name` = '$nname'";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 5612888");


//HTML Stuff

echo "<span class='title'>Art</span><br>";

while ($row = mysqli_fetch_array($result))
{

	extract($row);
	
		//Displays the title of the Art
		
		
	echo "&nbsp; <span class='title'>Title</span>: ";
	
	echo "<a href='${site_url_link}VehiclePhoto/$id'>$title</a>";
	
	echo "&nbsp; <span class='title'>Type</span>: ";
	echo "<a href='${site_url_link}$type/'>$type</a>";
	echo "<br>";

	

}

?>