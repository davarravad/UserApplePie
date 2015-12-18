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


$query = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$ID02' LIMIT 1 ";

// Get information from database
$result = $mysqli->query($query);
$arr_am = $result->fetch_all(MYSQLI_BOTH);

echo "<table><tr>";

foreach($arr_am as $row_am)
{

	$mainPic = $row_am['mainPic'];

	if($mainPic == "noimg.gif"){
		if($userIdme == $ID02){
			$mainPic = "noimgloggedin.gif";
			$mainPicLinkA = "<a href='${site_url_link}editprofilemain/editimages/'>";
			$mainPicLinkB = "</a>";
		}else{
			$mainPic = "noimg.gif";
		}
	}

	echo "<td>";
	if(isset($mainPicLinkA)){ echo "$mainPicLinkA"; }
	echo "<img class='rounded_10' border='0' width='100' src='/content/profile/thumb/${mainPic}'>";
	if(isset($mainPicLinkB)){ echo "$mainPicLinkB"; }
	//echo "<br><center>$content1</center>";
	echo "</td>";


}

echo "</tr></table>";



?>