<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

$query44 = "SELECT * FROM submit WHERE `int`='$vehicle_id' LIMIT 1";

echo "<strong>Vehicle Profile</strong> : ";

	$tempholder = array();
	$rs = mysqli_query($GLOBALS["___mysqli_ston"], $query44);
	$nr = mysqli_num_rows($rs);
	for ($i=0; $i<$nr; $i++){
    		$r = mysqli_fetch_array($rs);

    		if (!in_array($r['int'], $tempholder)){
        	$tempholder[$i] = $r['int'];
			if($r['veh_type'] == "Both"){ $r['veh_type'] = "Classic and Custom"; }
        	echo "<a href=${site_url_link}VehicleProfile/".$r["int"]."/>".$r["veh_type"]." - ".$r["year"]." ".$r["make"]." ".$r["model"]."</a>";
		}
	}
	unset($tempholder);


		if($nr){
			echo "";
		}else{
			//Checks to see if user is loged in
			if(isUserLoggedIn())
			{
				if($usrida == $userId){
					//echo "$id - $int";
					if(isset($id)){ 
						$veh_id_69 = "$id"; 
					}else{
						$veh_id_69 = "$int";
					}
					echo "<a href='${site_url_link}editprofilemain/editvehicles/#image$veh_id_69'>Add Vehicle Profile</a>";
				}else{
					echo "No Vehicle Profile";
				}
			}else{
				echo "No Vehicle Profile";
			}
		}
	

?>