<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

$userIdme = $userId;

    // get pnum no from user to move user defined pnum    
    $offset = $_GET['offset']; 
    
    // no of elements per page 
    
	if($offset){
		$limit = $offset;
	}else{
		$limit = 10; 
	}
    
$queryh = "SELECT * FROM submit ORDER BY `int` DESC";
$resulth = mysqli_query($GLOBALS["___mysqli_ston"], $queryh);

$num_rows = mysqli_num_rows($resulth);

$query = "SELECT * FROM submit ORDER BY `int` DESC LIMIT $limit";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query);
	//or die ("Couldn't ececute query. 2285");


//HTML Stuff



if($result){
while ($row = mysqli_fetch_array($result))
{


		$bgcolor = ($i % 2) ?epboxa : epboxb;
		$i++;

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
	
	$title = stripslashes($title);

	require "pages/my/userid.inc";
	//echo "$com_id - $userIdme <br>";	

	$userId1a = $userIdme;
	$userId2a = $com_id;
	require "pages/friend/friendcheckstatus.inc";
	//echo "$statfriend - $userId1a - $userId2a";

if($statfriend == "YES"){


	echo "<table width=100%><tr><td class='$bgcolor' width=40%>";
	echo "&nbsp<span class='title'>Title</span>: ";	
	echo "<a href='${site_url_link}VehicleProfile/$int'>$title</a> ";
	echo "</td><td class='$bgcolor' width=30%>";
	echo "&nbsp; <span class='title'>Author</span>: ";
	echo "<a href='${site_url_link}member/$usrida'>$name</a>"; 
	echo "</td><td class='$bgcolor' width=30%>";
	echo "&nbsp; <span class='title'>Type</span>: ";
	echo "<a href='${site_url_link}$taz_type/'>$type</a> <br>";
	echo "</td></tr></table>";


}	

}
}
else{
	echo "No Content Found.  <a href='${site_url_link}SubmitVehicleProfile/'>Submit Vehicle Profile</a><br><Br>";
}

	echo "<table width=100%><tr><td>";

 	//echo "<Br> $num_rows <br>";
	if($limit < $num_rows){
	echo " <a href=\"${site_url_link}community/friendwritings/?offset=" . ($limit + 20) . "\">Show More Writings...</a>  "; 
	}
	
	echo "</td></tr></table>";


?>