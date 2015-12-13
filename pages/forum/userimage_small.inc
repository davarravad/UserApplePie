<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

	global $mysqli, $db_table_prefix, $websiteUrl, $enable_photos;

if($enable_photos == "TRUE"){
	$query_uis = "SELECT up.mainPic FROM ".$db_table_prefix."userprofile up WHERE `userId`='$ID02' LIMIT 1 ";

	if($result_uis = $mysqli->query($query_uis)){
		while ($row_uis = $result_uis->fetch_assoc()) {
			$mainPic = $row_uis['mainPic'];
			echo "<a href='${websiteUrl}member/$ID02/'><img class='rounded_5' border='0' height='20' src='${websiteUrl}content/profile/thumb/${mainPic}'></a>";
		}
		$result_uis->close();
	}
}
?>