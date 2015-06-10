<center><h3>My Vehicle Profiles</h3></center>
<?php


$query = "SELECT * FROM submit WHERE `usrida` = '$userId' ORDER BY `int` DESC";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query);
	//or die ("Couldn't ececute query. 2285");

if($result){
	while ($row = mysqli_fetch_array($result))
	{

		$bgcolor = "epboxa";

		extract($row);

		if(isset($title)){ $title = stripslashes($title); }
		if($veh_type == "Both"){ $veh_type = "Classic and Custom"; }
		if(!empty($color)){ $color_display = "$color - "; }else{ $color_display = ""; }
		
		echo "<table width=100%><tr><td class='$bgcolor' width=40%>";
			echo "<a href='${site_url_link}VehicleProfile/$int'>";
			//Display Vehicle Photo with most views
			require "pages/profile/veh_top_view_photo.inc";
			echo "</a>";
		echo "&nbsp<span class='title'>$veh_type</span>: ";	
		echo "<a href='${site_url_link}VehicleProfile/$int'>$color_display $year - $make - $model</a> ";
		echo "(<a href='${site_url_link}editprofilemain/editvehicles/#profile$int'>Edit Vehicle Profile</a>)";
		echo "</td></tr></table>";


	}
}

?>
