<center>
<?php
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

    
$queryh = "SELECT * FROM ".$db_table_prefix."status WHERE NOT `com_id`='$userId' GROUP BY `id` ORDER BY `id` DESC";
$resulth = mysqli_query($GLOBALS["___mysqli_ston"], $queryh);

$num_rows = mysqli_num_rows($resulth);



$query01 = "SELECT * FROM ".$db_table_prefix."status WHERE NOT `com_id`='$userId' GROUP BY `id` ORDER BY `id` DESC LIMIT $limitfriendstatus";

$result01 = mysqli_query($GLOBALS["___mysqli_ston"], $query01)
	or die ("Couldn't ececute query. 4621235");



while ($row01 = mysqli_fetch_array($result01))
{

				$bgcolor = "epboxa";	
	
	extract($row01);

	$userId1a = $userId;
	$userId2a = $com_id;
	require "pages/friend/friendcheckstatus.inc";
	//echo "$statfriend - $userId1 - $userId2";

if($statfriend == "YES"){

				


	echo "<a class='anchor' name='status$id'></a>";
	echo "<table width='$tblw500' border=0 cellpadding=2 cellspacing=2>";
	echo "<tr>";
	echo "<td valign=top class=$bgcolor>";
		$ID02 = $com_id;
	echo "<div class='comt_nm2'><a href='${site_url_link}member/$ID02/'>";
		require "pages/profile/userimage_small.inc";
	echo "</a>";
	echo " Status by <a href='${site_url_link}member/$ID02/'>";
	echo " $com_name</div>";
	echo "</a>";
	echo "<br>";
	$com_content = stripslashes($com_content);
	echo "<div class='comt_cnt'>$com_content</div>";
	
		//Display how long ago this was posted
		$timestart = "$timestamp";  //Time of post
		require_once "models/timediff.inc";
		echo " " . dateDiff("now", "$timestart", 1) . " ago ";
	
		//Start Sweet
		$sweet_location = "status"; //Location on site where sweet is
		$sweet_id = "$id";  //Post Id number
		$sweet_userid = "$userIdme";  //User's Id
		$sweet_url = "${site_url_link}community/friendstatus/?offset=$offset#status$id";
		$sweet_owner_userid = "$ID02";  //Post owners userid
		require "models/sweets.inc";
		//End Sweet 

	echo "</tr></td><tr>";
	echo "<td class=$bgcolor>";
	$statcom_id = $id;
	require "pages/my/friendstatus/statcom.inc";
	echo "</td></tr></table><br><br>";
	if(isset($numofcomments)){
		$numofcomments = ($numofcomments + 1);
	}else{
		$numofcomments = "1";
	}
	//echo " ( $numofcomments ) ";
}

}

	if( !isset($numofcomments) ){$numofcomments = "0";}else{
	//$plussome = ($num_rows - $numofcomments);
 	//echo "<Br>$limitfriendstatus - $num_rows - $numofcomments - $plussome <br>";
	if($limitfriendstatus < $num_rows || $limitfriendstatus < $numofcomments){
		echo "<table width=100%><tr><td>";
		echo " <center><a href=\"${site_url_link}community/friendstatus/?offset=" . ($limitfriendstatus + 10) . "#status$id\">Show Older Friend's Status...</a> </center> "; 
		echo "</td></tr></table><br><br>";
	}
	}

?>
</center>