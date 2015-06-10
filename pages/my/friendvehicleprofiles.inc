<center><h3>Friend's Vehicle Profiles</h3></center>
<?php
	

    // get pnum no from user to move user defined pnum    
    if(isset($_GET['offsetVP'])){ $offsetVP = $_GET['offsetVP']; }else{ $offsetVP = ""; } 
    
    // no of elements per page 
    
	if($offsetVP){
		$limitVP = $offsetVP;
	}else{
		$limitVP = 20; 
	}

	$queryCFW = "
	(SELECT submit.int, submit.veh_type, submit.usrida, submit.name, submit.year, 
					submit.make, submit.model, submit.type, submit.engine, submit.color,
					submit.content1, submit.content2, submit.content3, submit.content4,
					submit.youtube1, submit.use, submit.new, submit.timestamp,
					friend.userId1, friend.userId2, friend.status1, friend.status2, 
	'submit' AS post_type FROM submit
	LEFT JOIN friend
	ON (submit.usrida = friend.userId1 AND friend.userId2 = $userIdme)
	OR (submit.usrida = friend.userId2 AND friend.userId1 = $userIdme)
	WHERE friend.status1 = '1' AND friend.status2 = '1'
	GROUP BY submit.int)
	";	
		
		
	$resulth = mysqli_query($GLOBALS["___mysqli_ston"], $queryCFW);
	$num_rowsVP = mysqli_num_rows($resulth);
	


	$query = "$queryCFW ORDER BY `int` DESC LIMIT $limitVP";
	$result = mysqli_query($GLOBALS["___mysqli_ston"], $query);


	if($result){
	
		echo "<table width=100%>";
	
		while ($row = mysqli_fetch_array($result))
		{


				$bgcolor = "epboxa";

			extract($row);

			$com_id = $usrida;
			
			$userId1a = $userIdme;
			if(!isset($com_id)){ $com_id = ""; }
				$userId2a = $com_id;
			
			//Check to see if veh_type is Both and change it to Classic and Custom
			if($veh_type == "Both"){ $veh_type = "Classic and Custom"; }
			if(!empty($color)){ $color_display = "$color - "; }else{ $color_display = ""; }

			echo "<tr><td class='$bgcolor'>";
				echo "<a href='${site_url_link}VehicleProfile/$int/'>";
				//Display Vehicle Photo with most views
				require "pages/profile/veh_top_view_photo.inc";
				echo "</a>";
			echo "&nbsp<span class='title'>$veh_type</span>: ";	
			echo "<a href='${site_url_link}VehicleProfile/$int/'>$color_display $year - $make - $model</a> ";
			echo "</td><td class='$bgcolor'> <strong>Author</strong> : ";
			echo "<a href='${site_url_link}member/$usrida/'>";
			//Get user name from users id
			$ID02 = $usrida;
			get_user_name($ID02);
			echo "</a>";
			echo "</td></tr>";
		}//end of while
		
		echo "</table>";
		
	}//end of result check
	echo "<table width=100%><tr><td>";

 	//echo "<Br> $num_rows <br>";
	if($limitVP < $num_rowsVP){
	echo " <br><br><a href=\"${site_url_link}community/friendvehicles/?offsetVP=" . ($limitVP + 20) . "\">Show More Vehicle Profiles...</a>  "; 
	}

	
	echo "</td></tr></table>";

	echo "<hr>";
?>
