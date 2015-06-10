<?php



$query = "SELECT * FROM `".$db_table_prefix."loggedusers`";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 56132188");

$rows = mysqli_num_rows($result); 

	if ($rows) {
		echo "<b><a href='${site_url_link}whosonline/'>Members Online</a></b>: $rows";
	}
	else {
		echo "<b>Members Online</b>: 0";
	}

?>

