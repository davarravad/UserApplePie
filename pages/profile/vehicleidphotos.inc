<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

	echo "<center>";

		$query = "SELECT * FROM art WHERE `vehicle_id`='$int'AND `use`='yes' ORDER BY `id` DESC";
		
		$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
			or die ("Couldn't ececute query. 46541321");
		$num_results = mysqli_num_rows($result);
		if($num_results > 0){ echo "<hr align='center' width='100%' />"; }
		
		while ($row = mysqli_fetch_array($result))
		{
		
				$bgcolor = "epboxa";
		
			extract($row);

				if($usemobile == "TRUE"){ $tblw = "100%"; }else{ $tblw = "500px"; }
				if($usemobile == "TRUE"){ $tblw2 = "100%"; }else{ $tblw2 = "500px"; }
		
				echo "<table width='$tblw' border='0' cellpadding='0' cellspacing='0' class='$bgcolor'>";
				echo "<tr><td valign='top' width='$tblw2'>";
					//echo "Type: <a href='${site_url_link}?page=$type'>$type</a> <br>";
					echo 'Title: ';
				if($title){
					echo "<a href='${site_url_link}VehiclePhoto/$id/'>$title</a><br>";
				}else{
					echo "<a href='${site_url_link}VehiclePhoto/$id/'>No Title</a><br>";
				}
					require "pages/profile/vehicleid.inc";  //Displays Vehicle Profile Link
					
					echo "<br>Author: <a href='${site_url_link}member/$usrida/'>$name</a>";
				echo "<br>";
			//Start Sweet
			$sweet_location = "art"; //Location on site where sweet is
			$sweet_id = "$id";  //Post Id number
			$sweet_userid = "$userIdme";  //User's Id
			$sweet_url = "${site_url_link}VehiclePhoto/$id/";
			$sweet_owner_userid = "$usrida";  //Post owners userid
			require "models/sweets.inc";
			//End Sweet
			
			//Start View
			$addview = "";  //Enables adding views to post
			$view_location = "art"; //Location on site where sweet is
			$view_id = "$id";  //Post Id number
			$view_userid = $_SERVER['REMOTE_ADDR'];  //User's Id
			$view_url = "${site_url_link}VehiclePhoto/$id/";
			$view_owner_userid = "$usrida";  //Post owners userid
			require "models/views.inc";
			//End View 
			
			//Start Comments
			$queryAZ = "SELECT * FROM artcomments WHERE `com_id`='$id' ORDER BY `id` DESC";
			$resultAZ = mysqli_query($GLOBALS["___mysqli_ston"], $queryAZ);
			$num_rows_commentsAZ = mysqli_num_rows($resultAZ);
			echo " <a href='${site_url_link}VehiclePhoto/$id/#comment_new'>$num_rows_commentsAZ Comments</a>";
			//End Comments
			
			echo "</td>";

					echo "</td>";
					echo "<td valign='top'  width='100px'>";
					echo "<a href='${site_url_link}VehiclePhoto/$id/'>";
					echo "<img class='rounded_10' border='0' width='100' style='max-height:60px' src='/content/art/thumb/${imgname}'>";
					
			echo "</td></tr>";
			echo "</table>";

			//Clean up vars
			unset($num_rows_commentsAZ, $resultAZ, $queryAZ, $id);
		
		}
	echo "</center>";

?>
