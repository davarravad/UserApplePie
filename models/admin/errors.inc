<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){

	echo "<center>";
	echo "<strong>Admin Zone - ".$websiteName." Errors</strong>"; 
	echo "</center><br><Br>";


$query = "SELECT * FROM ".$db_table_prefix."errors ORDER BY `er_id` DESC";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. Errors 324");


//HTML Stuff




while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);

	echo "<table cellspacing=2 width='100%'>";
	echo "<tr>";
	echo "<td class=$bgcolor rowspan=2 width='50px'>($er_id)";
	echo "
		<form method=\"post\" action=\"${site_url_link}YummyAsPie/delete_error/ \">
		<input type=\"hidden\" name=\"er_id\" value=\"$er_id\">
		<label title=\"Delete this Location!\"><input type=\"submit\" value=\"Delete!\" /></label>
		</form>
	";
	echo "</td><td>";
		echo "<table width='100%'><tr><td class=$bgcolor>$er_type</td>";
		echo "</tr><tr><td class=$bgcolor>$er_location</td>";
		echo "</tr><tr><td class=$bgcolor>$er_uri</td>";
		echo "</tr><tr><td class=$bgcolor>$er_refer</td>";
		echo "</tr><tr><td class=$bgcolor>$er_useragent</td>";
		echo "</tr><tr><td class=$bgcolor>$er_msg</td>";
		echo "</tr><tr><td class=$bgcolor>$er_cfile</td>";
		echo "</tr><tr><td class=$bgcolor>$er_ipaddy</td>";
		echo "</tr><tr><td class=$bgcolor>$er_server</td>";
		echo "</tr><tr><td class=$bgcolor>$er_date";		
		echo "</td></tr></table>";
	echo "</td></tr>";
	echo "</table><hr>";
}



}

?>


