<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Save visitor information to database to build a view count

global $mysqli, $site_url_link, $db_table_prefix;

if(!isset($view_sub)){ $view_sub = ""; }
if(!isset($view_sec_id)){ $view_sec_id = ""; }	

	$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."views SET view_id=?, view_sec_id=?, view_sub=?, view_location=?, view_userid=?, view_url=?, view_owner_userid=? ");
	$stmt->bind_param("iissssi", $view_id, $view_sec_id, $view_sub, $view_location, $view_userid, $view_url, $view_owner_userid);
	$stmt->execute();
	$newId = $stmt->insert_id;
	//echo $stmt->error;
	$stmt->close();	

	//echo "<br> ( $view_sub $view_location - $view_id - $view_userid - $view_url ) ";  //for testing

?>

