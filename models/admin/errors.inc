<?php

	if(isUserLoggedIn()){

		if(is_admin()) {


	echo "<center>";
	echo "<strong>Admin Zone - CarTruckClubs.com Errors</strong>"; 
	echo "</center><br><Br>";


$query = "SELECT * FROM ".$db_table_prefix."errors ORDER BY `er_id` DESC";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. Errors 324");


//HTML Stuff


echo "<table cellspacing=2>";

while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);

	echo "<tr>";
	echo "<td class=$bgcolor rowspan=2>($er_id)";
	echo "
		<form method=\"post\" action=\"${site_url_link}YummyAsPie/delete_error/ \">
		<input type=\"hidden\" name=\"er_id\" value=\"$er_id\">
		<label title=\"Delete this Location!\"><input type=\"submit\" value=\"Delete!\" /></label>
		</form>
	";
	echo "</td>";
	echo "<td class=$bgcolor>$er_type</td>";
	echo "<td class=$bgcolor colspan=2>$er_location</td>";
	echo "<td class=$bgcolor colspan=4>$er_uri</td>";
	echo "</tr><tr><td class=$bgcolor>$er_refer</td>";
	echo "<td class=$bgcolor>$er_useragent</td>";
	echo "<td class=$bgcolor>$er_msg</td>";
	echo "<td class=$bgcolor>$er_cfile</td>";
	echo "<td class=$bgcolor>$er_ipaddy</td>";
	echo "<td class=$bgcolor>$er_server</td>";
	echo "<td class=$bgcolor>$er_date";
	echo "</td></tr><tr><td>&nbsp;";		
	echo "</td></tr>";
	
}
echo "</table>";


		}
		else{
			echo "Admin Only.";
			exit();
		}

	}
	else{
		notlogedinmsg();
		exit();
	}


?>


