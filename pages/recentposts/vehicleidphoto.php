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


		$query_vehpic = "SELECT art.imgname FROM art WHERE `vehicle_id`='$int' AND `use`='yes' ORDER BY `id` DESC LIMIT 1";
		
		$result_vehpic = mysqli_query($GLOBALS["___mysqli_ston"], $query_vehpic)
			or die ("Couldn't ececute query.");

		while ($row_vehpic = mysqli_fetch_array($result_vehpic))
		{
			extract($row_vehpic);

		}

?>
