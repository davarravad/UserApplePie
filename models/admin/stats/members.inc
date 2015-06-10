<?php





$query = "SELECT * FROM `".$db_table_prefix."userprofile` ";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 1231588");


$rows = mysqli_num_rows($result); 




	if ($rows) {
		echo "<b><a href='${site_url_link}members/'>Members</a></b>: $rows";
	}
	else {
		echo "<b>Members</b>: 0";
	}


?>

