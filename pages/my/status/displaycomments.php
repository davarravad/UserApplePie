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


if(isset($_REQUEST['ID'])){
	$id = $_REQUEST['ID'];
	$ID = $_REQUEST['ID'];
}else{
	$id = "";
	$ID = "";
}

    // get pnum no from user to move user defined pnum    
    if(isset($_GET['offset'])){ $offset = $_GET['offset']; }else{ $offset = ""; }
     
    
    // no of elements per page 
    
	if($offset){
		$limitfriendstatus = "$offset";
	}else{
		$limitfriendstatus = "10"; 
	}

if(isset($view_only_one)){}else{ $view_only_one = ""; }
if($view_only_one == "TRUE"){
	$query01 = "SELECT * FROM ".$db_table_prefix."status WHERE `id`='$view_status' LIMIT 1";
?>
	<script>
	function textAreaAdjust(o) {
    o.style.height = "1px";
    o.style.height = (10+o.scrollHeight)+"px";
}
</script>
<?php
}else{
	$query01 = "SELECT * FROM ".$db_table_prefix."status WHERE `com_id`='$userId' ORDER BY `id` DESC LIMIT $limitfriendstatus";
}

$queryhZ = "SELECT * FROM ".$db_table_prefix."status WHERE `com_id`='$userId' GROUP BY `id` ORDER BY `id` DESC";
$resulthZ = mysqli_query($GLOBALS["___mysqli_ston"], $queryhZ);

$num_rows = mysqli_num_rows($resulthZ);


$result01 = mysqli_query($GLOBALS["___mysqli_ston"], $query01)
	or die ("Couldn't ececute query. 85462163");

while ($row01 = mysqli_fetch_array($result01))
{
				$bgcolor = "epboxa";
				

	extract($row01);

	echo "<a class='anchor' name='status$id'></a>";
	echo "<div class='panel panel-info'>";
		echo "<div class='panel-heading'>";
			$ID02 = $com_id;
			echo "<a href='${site_url_link}member/$ID02/'>";
			require "pages/profile/userimage_small.php";
			echo "</a> Status by ";
			echo "<a href='${site_url_link}member/$ID02/'>";
			echo " $com_name";
			echo "</a>";
		echo "</div>";
		echo "<div class='panel-body'>";
			//Comment Settings
			$ed_com_database = "status"; //Comments database
			$com_type_edit = "reg"; //Sets type of comment reg or stat
			$ed_com_id = $id;  //Gets id of comment
			if(isset($offset)){}else{ $offset = ""; }
			if($view_only_one == "TRUE"){
					$ed_com_url = "$view_status_link&offset=$offset#status$id";
			}else{
					$ed_com_url = "${site_url_link}community/mystatus/?offset=$offset#status$id";
			}
			$com_uid = $com_id;

			echo "<div class='well well-sm'>";
				//Shows comment if not edit, delete, or update.
				require "pages/comments/main.php";
			echo "</div>";
			
			if(isset($ed_but)){ $edit_but = "$ed_but"; }

			//Display edit button
			if(isset($edit_but)){
				echo "<table width='100%'><td align='left'>";
			}

			//Display how long ago this was posted
			$timestart = "$timestamp";  //Time of post
			require_once "external/timediff.php";
			echo " " . dateDiff("now", "$timestart", 1) . " ago ";

			//Start Sweet
			$sweet_location = "status"; //Location on site where sweet is
			$sweet_id = "$id";  //Post Id number
			$sweet_userid = "$userIdme";  //User's Id
				if($view_only_one == "TRUE"){
						$sweet_url = "$view_status_link&offset=$offset#status$id";
				}else{
						$sweet_url = "${site_url_link}community/mystatus/?offset=$offset#status$id";
				}
			$sweet_owner_userid = "$ID02";  //Post owners userid
			require "external/sweets.php";
			//End Sweet 

			if(isset($edit_but)){
				echo "</td><td align='right'>$edit_but</td></table>"; 
			}
			unset($com_uid, $ed_but, $edit_but, $com_id, $ed_com_id, $ed_com_id_form);
			
		echo "</div>";
		echo "<div class='panel-footer'>";
			
			// Display status comments
			$statcom_id = $id;
			require "pages/my/status/statcom.php";

			if(isset($numofcomments)){
				$numofcomments = ($numofcomments + 1);
			}else{
				$numofcomments = "1";
			}
			//echo " ( $numofcomments ) ";
		echo "</div>";
	echo "</div>";	
}


		if( !isset($numofcomments) ){$numofcomments = "0";}else{
		//$plussome = ($num_rows - $numofcomments);
		//echo "<Br>$limitfriendstatus - $num_rows - $numofcomments - $plussome <br>";
		if($limitfriendstatus < $num_rows || $limitfriendstatus < $numofcomments){
			echo "<div class='panel panel-default'>";
			echo " <center><a href=\"${site_url_link}community/friendstatus/?offset=" . ($limitfriendstatus + 10) . "#status$id\">Show Older Friend's Status...</a> </center> "; 
			echo "</div>";
		}

	
}
?>