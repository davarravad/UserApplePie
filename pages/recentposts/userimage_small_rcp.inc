<?php

$queryx = "SELECT ".$db_table_prefix."userprofile.mainPic FROM ".$db_table_prefix."userprofile WHERE `userId`='$ID02' LIMIT 1 ";

$resultx = mysqli_query($GLOBALS["___mysqli_ston"], $queryx)
	or die ("Couldn't ececute query.");

while ($row = mysqli_fetch_array($resultx))
{
	extract($row);

	echo "<a href='${site_url_link}member/$ID02/'><img class='rounded_5' border='0' height='18' src='http://".$site_dir."/content/profile/thumb/${mainPic}'></a>";

}

?>