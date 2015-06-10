
<center>
<?php

//echo "$statcom_id";

$query02 = "SELECT * FROM ".$db_table_prefix."statcom WHERE `statcom_id`='$statcom_id' ORDER BY `id` ASC";

$result02 = mysqli_query($GLOBALS["___mysqli_ston"], $query02)
	or die ("Couldn't ececute query. 5643212");


while ($row02 = mysqli_fetch_array($result02))
{
				$bgcolor = "content79";
				

	extract($row02);

	echo "<a class='anchor' name='statcom$id'></a>";
	echo "<table width='99%' border=0 cellpadding=2 cellspacing=2>";
	echo "<tr>";
	echo "<td valign=top class=$bgcolor>";
		$ID02 = $statcom_uid;
	echo "<div class='comt_nm'><a href='${site_url_link}member/$ID02/'>";
		require "pages/profile/userimage_small.inc";
	echo "</a> Comment by ";
	echo "<a href='${site_url_link}member/$ID02/'>";
	echo " $statcom_name</div>";
	echo "</a>";

//Comment Settings
$ed_com_database = "statcom"; //Comments database
$ed_com_id = $id;  //Gets id of comment
$ed_com_url = "${site_url_link}community/friendstatus/?offset=$offset#statcom$id";
$com_uid = $statcom_uid;
$statcom_content = stripslashes($statcom_content);
$com_content = $statcom_content;
$com_type_edit = "stat"; //Sets type of comment reg or stat

//Shows comment if not edit, delete, or update.
require "pages/comments/main.inc";


if(isset($ed_but)){ $edit_but = "$ed_but"; }

	//Display edit button
	if(isset($edit_but)){
		echo "<table width='100%'><td align='left'>";
	}


			//Display how long ago this was posted
		$timestart = "$timestamp";  //Time of post
		require_once "models/timediff.inc";
		echo " " . dateDiff("now", "$timestart", 1) . " ago ";

		//Start Sweet
		$sweet_location = "statuscom"; //Location on site where sweet is
		$sweet_id = "$id";  //Post Id number
		$sweet_userid = "$userIdme";  //User's Id
		$sweet_url = "${site_url_link}community/friendstatus/?offset=$offset#statcom$id";
		$sweet_owner_userid = "$ID02";  //Post owners userid
		require "models/sweets.inc";
		//End Sweet 

	if(isset($edit_but)){
		echo "</td><td align='right'>$edit_but</td></table>"; 
	}
	unset($com_uid, $ed_but, $edit_but, $com_id, $ed_com_id, $ed_com_id_form);


	echo "</td></tr></table>";



}
?>
</center>