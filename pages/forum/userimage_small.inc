<?php

$queryx = "SELECT up.mainPic FROM ".$db_table_prefix."userprofile up WHERE `userId`='$ID02' LIMIT 1 ";

$resultx = mysqli_query($GLOBALS["___mysqli_ston"], $queryx)
	or die ("Couldn't ececute query. 1298251");

while ($row = mysqli_fetch_array($resultx))
{
	extract($row);

	$sw_user_sweeted_pic = "<a href='${site_url_link}member/$ID02/'><img class='rounded_5' border='0' height='50' src='http://".$site_dir."/content/profile/thumb/${mainPic}'></a>";

}

?>