<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){

echo "<center>";
	echo "<strong>Admin Zone - ".$websiteName." Reports</strong>"; 
	echo "</center><br><Br>";


$query = "SELECT * FROM ".$db_table_prefix."report";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. Reports 43666");


//HTML Stuff


echo "<table cellspacing=4 width=100%>";

while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);

	$report_msg = stripslashes($report_msg);
	
	echo "<tr><td class=$bgcolor>";
	echo "<b>Reporter</b>: $report_user ($report_userID) - <b>Type</b>: $report_type";
	echo "<br><a href='$report_pageURL' target='_blank'>$report_pageURL</a>";
	echo "<hr><font color=gray>$report_msg</font>";
	echo "
		<form method=\"post\" action=\"${site_url_link}UAP_Admin_Panel/delete_report/ \">
		<input type=\"hidden\" name=\"report_id\" value=\"$report_id\">
		<label title=\"Delete this Location!\"><input type=\"submit\" value=\"Delete!\" /></label>
		</form>
	";
	echo "</td></tr>";		

}
echo "</table>";


}


?>


