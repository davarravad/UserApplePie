<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

$query44 = "SELECT * FROM submit WHERE `usrida`='$userId' ORDER BY `int` DESC";

echo "Vehicle Profile : <select name='vehicle_id' size='1' id='vehicle_id'>";
echo "<option value=''>Select Vehicle Profile</option>";

	$tempholder = array();
	$rs = mysqli_query($GLOBALS["___mysqli_ston"], $query44);
	$nr = mysqli_num_rows($rs);
	for ($i=0; $i<$nr; $i++){
    		$r = mysqli_fetch_array($rs);

    		if (!in_array($r['year'], $tempholder)){
        	$tempholder[$i] = $r['int'];
        	echo "<option value=".$r["int"]." ".(($vehicle_id==$r["int"])? ' selected="selected"' : '').">".$r["color"]."-".$r["year"]."-".$r["make"]."-".$r["model"]."</option>";
		}
	}
	unset($tempholder);
echo '</select>';

?>
<br>