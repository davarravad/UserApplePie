<center>
<?php

$main_com_id = $id;
//echo "$statcom_id";

//Get total rows of comments
$queryhZA = "SELECT * FROM ".$db_table_prefix."$com_query_database_b WHERE `statcom_id`='$statcom_id' GROUP BY `id` ORDER BY `id` ASC";
$resulthZA = mysqli_query($GLOBALS["___mysqli_ston"], $queryhZA);
$num_rowsZA = mysqli_num_rows($resulthZA);

$sub_rows_a = ($num_rowsZA - 2);

	if(isset($_GET['show_main_com_id'])){ 
		$show_main_com_id = $_GET['show_main_com_id'];
	}else{
		$show_main_com_id = "";
	}
    
	//echo "$show_main_com_id == $main_com_id";
	
	if($show_main_com_id == $main_com_id){
		$limit_com_com_amt = "";
	}else{
		if($num_rowsZA <= "2"){
			$limit_com_com_amt = "";
			$limit_com_com = "2";
		}else{
			$limit_com_com = "2";
			$limit_com_com_amt = "LIMIT $sub_rows_a , 2"; 
		}
	}
	
$query02 = "SELECT * FROM ".$db_table_prefix."$com_query_database_b WHERE `statcom_id`='$statcom_id' ORDER BY `id` ASC $limit_com_com_amt";

//echo "$query02";

$result02 = mysqli_query($GLOBALS["___mysqli_ston"], $query02)
	or die ("Couldn't ececute query. Com Com.");

while ($row02 = mysqli_fetch_array($result02))
{
				$bgcolor = "epboxa";
				
	
	extract($row02);
	
	$statcom_content = stripslashes($statcom_content);
	echo "<a class='anchor' name='statcom$id'></a>";
	echo "<table width='99%' border=0 cellpadding=2 cellspacing=2>";
	echo "<tr>";
	echo "<td valign=top class=$bgcolor>";
		$ID02 = $statcom_uid;
	echo "<div class='comt_nm2'><a href='${site_url_link}member/$ID02/'>";
		require "pages/profile/userimage_small.inc";
	echo "</a> Comment by ";
	echo "<a href='${site_url_link}member/$ID02/'>";
	echo " $statcom_name</div>";
	echo "</a>";
	echo "<br>";

//Comment Settings
$ed_com_database = "$com_query_database_b"; //Comments database
$ed_com_id = $id;  //Gets id of comment
$com_type_edit = "stat"; //Sets type of comment reg or stat

//echo "($ed_com_id)";

	if(!isset($show_main_com_id)){ $show_main_com_id = ""; }
	if(!isset($offset)){ $offset = ""; }
	
		$ed_com_url = "$com_url_addy?show_main_com_id=$show_main_com_id&offset=$offset#statcom$id";

$com_uid = $statcom_uid;
$com_content = $statcom_content;

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
		$sweet_location = "$com_query_database_b"; //Location on site where sweet is
		$sweet_id = "$id";  //Post Id number
		$sweet_userid = "$userIdme";  //User's Id

		$sweet_url = "$com_url_addy?offset=$offset#statcom$id";

		$sweet_owner_userid = "$ID02";  //Post owners userid
		require "models/sweets.inc";
		//End Sweet 

	if(isset($edit_but)){
		echo "</td><td align='right'>$edit_but</td></table>"; 
	}
	unset($com_uid, $ed_but, $edit_but, $com_id, $ed_com_id, $ed_com_id_form);


	echo "</td></tr></table>";
}

	if(!isset($limit_com_com)){ $limit_com_com = ""; }
	if(($limit_com_com < $num_rowsZA) && ($show_main_com_id != $main_com_id)){
		$how_many_to_show = ($num_rowsZA - $limit_com_com);
		echo "<table width=100%><tr><td>";
		echo " <center>$how_many_to_show More Comments - <a href=\"$com_url_addy?show_main_com_id=$main_com_id#comment$main_com_id\">Show All Comments...</a> </center> "; 
		echo "</td></tr></table>";
	}

?>
</center>