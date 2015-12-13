<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Get users profile image at 18 px height

// Get globals 	
global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix, $enable_photos;

if($enable_photos == "TRUE"){

	if(!empty($A_ID02)){
		$queryx = "SELECT `".$db_table_prefix."userprofile`.`mainPic` FROM ".$db_table_prefix."userprofile WHERE `userId`='$A_ID02' LIMIT 1 ";
	}else{
		$queryx = "SELECT `".$db_table_prefix."userprofile`.`mainPic` FROM ".$db_table_prefix."userprofile WHERE `userId`='$ID02' LIMIT 1 ";
	}

	// Get information from database
	$result = $mysqli->query($queryx);
	$arr_am = $result->fetch_all(MYSQLI_BOTH);
	foreach($arr_am as $row_am)
	{
		$mainPic = $row_am['mainPic'];

		echo "<img class='rounded_5' style='max-height:18px;' border='0' height='18' src='http://".$site_dir."/content/profile/thumb/${mainPic}'>";
		unset($mainPic);
	}

}
?>