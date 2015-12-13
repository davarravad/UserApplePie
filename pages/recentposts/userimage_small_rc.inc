<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if($enable_photos == "TRUE"){
	$queryx = "SELECT ".$db_table_prefix."userprofile.mainPic FROM ".$db_table_prefix."userprofile WHERE `userId`='$sw_un_id' LIMIT 1 ";

	$resultx = mysqli_query($GLOBALS["___mysqli_ston"], $queryx)
		or die ("Couldn't ececute query.");

	while ($row = mysqli_fetch_array($resultx))
	{
		extract($row);

		echo "<a href='${site_url_link}member/$sw_un_id'><img class='rounded_5' border='0' height='18' src='http://".$site_dir."/content/profile/thumb/${mainPic}'></a>";

	}
}

?>