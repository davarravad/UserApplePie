<?php

	$userIdme = $userId;


	require_once "pages/my/friendvehicleprofiles.inc";

	echo "<center><h3>Friend's Vehicles</h3></center>";

    // get pnum no from user to move user defined pnum    
    if(isset($_GET['offset'])){ $offset = $_GET['offset']; }else{ $offset = ""; } 
    
    // no of elements per page 
    
	if($offset){
		$limit = $offset;
	}else{
		$limit = 20; 
	}

	$queryWFC = "
	(SELECT art.id, art.vehicle_id, art.usrida, art.name, art.type, art.title, art.imgdir, art.imgname, art.use, art.new, art.timestamp,
					friend.userId1, friend.userId2, friend.status1, friend.status2, 
	'art' AS post_type FROM art
	LEFT JOIN friend
	ON (art.usrida = friend.userId1 AND friend.userId2 = $userIdme)
	OR (art.usrida = friend.userId2 AND friend.userId1 = $userIdme)
	WHERE friend.status1 = '1' AND friend.status2 = '1'
	GROUP BY art.id)
	";
		
    // simple query to get total no of entries
	if ($result = $mysqli->query("$queryWFC")) {

		/* determine number of rows result set */
		$num_rows = $result->num_rows;

		// printf("Topics:  %d \n", $total);

		/* close result set */
		$result->close();
	}
		
	$query = "$queryWFC ORDER BY `id` DESC LIMIT $limit";
	$result = mysqli_query($GLOBALS["___mysqli_ston"], $query);


	//HTML Stuff
	//echo "<br> $offset - LIMIT = $limit <br>";


	if($result){

		while ($row = mysqli_fetch_array($result))
		{

			extract($row);

				$bgcolor = "epboxa";

			$title = stripslashes($title);

			$com_id = $usrida;	

			if(!isset($com_id)){ $com_id = ""; }
			
			$userId1a = $userIdme;
			$userId2a = $com_id;

			echo "<table width=100%><tr><td class='$bgcolor' width=100>";
			echo "<a href='${site_url_link}VehiclePhoto/$id/'>";
			echo "<img class='rounded_10' border='0' width='100' style='max-height:60px' src='/content/art/thumb/${imgname}'>";
			echo "</a>";
			echo "</td><td class='$bgcolor'>";	
			echo "<strong>Title</strong> : ";
			
			if($title){
				echo "<a href='${site_url_link}VehiclePhoto/$id/'>$title</a>";
			}else{
				echo "<a href='${site_url_link}VehiclePhoto/$id/'>No Title</a>";
			}
			echo "<br>";	
			require "pages/profile/vehicleid.inc";
			echo "<br> <strong>Author</strong> : ";
			echo "<a href='${site_url_link}member/$usrida/'>$name</a>";
			echo "</td></tr></table>";

		}

	}


	echo "<table width=100%><tr><td>";

 	//echo "<Br> $num_rows <br>";
	if($limit < $num_rows){
	echo " <br><br><a href=\"${site_url_link}community/friendvehicles/?offset=" . ($limit + 20) . "\">Show More Vehicle Photos...</a>  "; 
	}

	
	echo "</td></tr></table>";

?>