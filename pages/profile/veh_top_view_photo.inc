<?php

		$query_vtvp = "SELECT * FROM art WHERE `vehicle_id`='$int' AND `use`='yes' ORDER BY `id` DESC LIMIT 1";
		
		$result_vtvp = mysqli_query($GLOBALS["___mysqli_ston"], $query_vtvp)
			or die ("Couldn't ececute query. 561321");
		
		// print out the results
		if( $result_vtvp && $contact_vtvp = mysqli_fetch_object( $result_vtvp ) )
		{
			// print out the info
			$imgname = $contact_vtvp -> imgname;
		}
		
		if(!empty($imgname)){
			echo "<img class='rounded_5' border='0' width='50' style='max-height:50px;' src='/content/art/thumb/${imgname}'>";
		}
		unset($imgname);
?>
