<?php
//////////////////////////////////
// UserApplePie Version: 1.1.1  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Security Feature to Disallow File to be opened directly.
// Only allows this file to be include by index.php
if(!defined('Page_Protection')){header("Location: ../");exit();}


// Displays user's main pic

$query_mp = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$userId' LIMIT 1 ";

// Get information from database
$result_mp = $mysqli->query($query_mp);
$arr_mp = $result_mp->fetch_all(MYSQLI_BOTH);
foreach($arr_mp as $row_mp)
{
	$mainPic = $row_mp['mainPic'];

		if($mainPic == "noimg.gif"){
			
				$mainPic = "noimgloggedin.gif";
				$mainPicLinkA = "<a href='${site_url_link}editprofilemain/editimages/'>";
				$mainPicLinkB = "</a>";
			
		}

}

?>