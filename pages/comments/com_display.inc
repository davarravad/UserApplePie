
<?

//Settings needed for comments to work
//$com_top_title = "Event Comments";  //Displays the title of comments at top of comments
//$com_query_database = "club_events_com"; //Comments database
//$com_query_database_b = "club_events_com_b"; //Comments comments database
//$com_url_addy = "/Clubs/?pee=events/events_list&club_id=$club_id&club_events_edit=TRUE&fsp=viewEvent&fsid=$fsid"; //Url Location of comments
//$com_sel_id = "$fsid"; //Id of post that comments are related to

    // get pnum no from user to move user defined pnum    
    if(isset($_GET['offset'])){ $offset = $_GET['offset']; }else{ $offset = ""; }

if(isset($_REQUEST['ID'])){
	$id = $_REQUEST['ID'];
	$ID = $_REQUEST['ID'];
}else{
	$id = "";
	$ID = "";
}

//Get number of comments

	$queryCOMC = "SELECT * FROM ".$db_table_prefix."$com_query_database WHERE `com_id`='$com_sel_id' ORDER BY `id`";
	$resultCOMC = mysqli_query($GLOBALS["___mysqli_ston"], $queryCOMC);
	$num_rows_commentsCOMC = mysqli_num_rows($resultCOMC);
	if($num_rows_commentsCOMC > 0){
		$ttl_num_comments = $num_rows_commentsCOMC;	
	}
	if(isset($ttl_num_comments)){}else{ $ttl_num_comments = "0"; }
		$display_com_amt = $ttl_num_comments; 

	if($num_rows_commentsCOMC == 0){
		$display_com_msg = "No comments yet, be the first to leave a comment!";	
	}

echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='epboxy' colspan=2>";
echo "<center><strong>$display_com_amt $com_top_title</strong></center>";
echo "</td></tr><tr><td class='epboxz' colspan=2>";
echo "<center>";
	if(isset($display_com_msg)){ echo "<center>$display_com_msg</center>"; }
//check to see if new comment
if(isset($_POST['comment'])){ 
	$com_new = $_POST['comment']; 
	if($com_new == "save"){
		require "pages/comments/com_save.inc";
	}
}elseif(isset($_POST['statcom'])){
	$statcom = $_POST['statcom']; 
	if($statcom == "save"){
		require_once "pages/comments/com_b_save.inc";
	}
}else{
	//show box for creating new comment
	require "pages/comments/com_new.inc"; 
	echo "<br>";
}
echo "<a class='anchor' name='comment_new'></a>";

    
    // no of elements per page 
    
	if($offset){
		$limitfriendstatus = "$offset";
	}else{
		$limitfriendstatus = "10"; 
	}


	$query01 = "SELECT * FROM ".$db_table_prefix."$com_query_database WHERE `com_id`='$com_sel_id' ORDER BY `id` DESC LIMIT $limitfriendstatus";


$queryhZ = "SELECT * FROM ".$db_table_prefix."$com_query_database WHERE `com_id`='$com_sel_id' GROUP BY `id` ORDER BY `id` DESC";
$resulthZ = mysqli_query($GLOBALS["___mysqli_ston"], $queryhZ);

$num_rows = mysqli_num_rows($resulthZ);


$result01 = mysqli_query($GLOBALS["___mysqli_ston"], $query01)
	or die ("Couldn't ececute query.");

while ($row01 = mysqli_fetch_array($result01))
{
				$bgcolor = "epboxb";
				

	extract($row01);

	echo "<a class='anchor' name='com$id'></a>";
	echo "<a class='anchor' name='comment$id'></a>";
	
	echo "<table width='$tblw500' border=0 cellpadding=0 cellspacing=0>";
	echo "<tr>";
	echo "<td valign=top width=$tblw3 class=epboxb>";
		$ID02 = $com_uid;
	echo "<a href='${site_url_link}member/$ID02/'>";
		require "pages/profile/userimage.inc";
	echo "</a>";
	echo "</td> ";
	echo "<td class='$bgcolor' valign=top>";
	echo "<a href='${site_url_link}member/$ID02/'>";
	echo "<font class='comt_nm'>$com_name</font>";
	echo "</a>";
	echo "<br>";


//Comment Settings
//echo "(id = $id)";
$ed_com_database = "$com_query_database"; //Comments database
$ed_com_id = $id;  //Gets id of comment
$com_type_edit = "reg"; //Sets type of comment reg or stat

//echo "($ed_com_id)";

	if(!isset($show_main_com_id)){ $show_main_com_id = ""; }
	if(!isset($offset)){ $offset = ""; }

		$ed_com_url = "$com_url_addy?show_main_com_id=$show_main_com_id&offset=$offset#comment$id";

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
		$sweet_location = "$com_query_database"; //Location on site where sweet is
		$sweet_id = "$id";  //Post Id number
		$sweet_userid = "$userIdme";  //User's Id
		$sweet_url = "$com_url_addy?offset=$offset#comment$id";
		$sweet_owner_userid = "$ID02";  //Post owners userid
		require "models/sweets.inc";
		//End Sweet 

	if(isset($edit_but)){
		echo "</td><td align='right'>$edit_but</td></table>"; 
	}
	unset($com_uid, $ed_but, $edit_but, $com_id, $ed_com_id, $ed_com_id_form);


	echo "</td></tr><tr>";
	echo "<td class=$bgcolor colspan=2>";
	$statcom_id = $id;
	require "pages/comments/com_b.inc";
	echo "</td></tr></table><br>";

	if(isset($numofcomments)){
		$numofcomments = ($numofcomments + 1);
	}else{
		$numofcomments = "1";
	}
	//echo " ( $numofcomments ) ";

}


	if( !isset($numofcomments) ){$numofcomments = "0";}else{
	//$plussome = ($num_rows - $numofcomments);
 	//echo "<Br>$limitfriendstatus - $num_rows - $numofcomments - $plussome <br>";
	if($limitfriendstatus < $num_rows || $limitfriendstatus < $numofcomments){
		echo "<table width=100%><tr><td>";
		echo " <center><a href=\"$com_url_addy?offset=" . ($limitfriendstatus + 10) . "#comment$id\">Show More Comments...</a> </center> "; 
		echo "</td></tr></table>";
	}
	
	
}
echo "</center>";
echo "</td></tr></table>";

?>
