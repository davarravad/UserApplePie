<?php

// Get mainPic for requested user
$query_33 = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$userId' LIMIT 1 ";

// Get information from database
$result_33 = $mysqli->query($query_33);
$arr_33 = $result_33->fetch_all(MYSQLI_BOTH);
foreach($arr_33 as $row_33)
{
	$mainPic = $row_33['mainPic'];

	if($mainPic == "noimg.gif"){
		
			$mainPic = "noimgloggedin.gif";
			$mainPicLinkA = "<a href='${site_url_link}editprofilemain/editimages/'>";
			$mainPicLinkB = "</a>";
		
	}
	if(isset($mainPicLinkA)){ echo "$mainPicLinkA"; }
	echo "<img class='rounded_10' border='0' width='100' src='http://".$site_dir."/content/profile/thumb/${mainPic}'>";
	if(isset($mainPicLinkB)){ echo "$mainPicLinkB"; }

}





?>