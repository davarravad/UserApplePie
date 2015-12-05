<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

echo "<a class='anchor' name=imgsview></a>";

	//Include popup file
	require "pages/pic_upload/popupimgs/img_header.inc";

$uri = $_SERVER['REQUEST_URI']; 

if(isset($_REQUEST['vimg_display'])){ $vimg_display = $_REQUEST['vimg_display']; }else{ $vimg_display = ""; }
if(isset($_REQUEST['vimg_display_id'])){ $vimg_display_id = $_REQUEST['vimg_display_id']; }else{ $vimg_display_id = ""; }

//Displays image as regular size if thumb was clicked
if($vimg_display == 'yes'){

	// retrieve the row from the database
	$query_pic = "SELECT * FROM `club_pics` WHERE `id`='$vimg_display_id' ";
   
	$result_pic = mysqli_query($GLOBALS["___mysqli_ston"],  $query_pic );

	// print out the results
	if( $result_pic && $contact_pic = mysqli_fetch_object( $result_pic ) )
	{
		// print out the info
		$imgname_club_pic = $contact_pic -> imgname;
		$content1_club_pic = $contact_pic -> content1;
	}
		if(isset($content1_club_pic)){  
			$content1_club_pic = stripslashes($content1_club_pic);
		}
		echo "<center><div>";
		echo "<img class='rounded_10' border='0' width='$tblwimg' src='/${puf_pic_dir_small}${imgname_club_pic}'>";
		if(isset($content1_club_pic)){
			echo "<br><center>$content1_club_pic</center>";
		}
		echo "</div></center><br><br>";

	
}

    // get pnum no from user to move user defined pnum    
    if(isset($_GET['offset_pics'])){ $offset = $_GET['offset_pics']; }else{ $offset = ""; } 
    
    // no of elements per page 
    
	if($offset){
		$limit = $offset;
	}else{
		$limit = 5; 
	}

	//Loads database for Member Profiles 
	if($puf_pic_cat == "ep3"){
		$queryWFC = "SELECT * FROM ".$db_table_prefix."ep3 WHERE `userId`='$ID02' ";
	}
	//Loads database for club_pics 
	if($puf_pic_cat == "club_pics"){
		$queryWFC = "SELECT * FROM club_pics WHERE `nname`='$club_id' ";
	}
	//Loads database for club_events_pics 
	if($puf_pic_cat == "club_events_pics"){
		$queryWFC = "SELECT * FROM club_events_pics WHERE `fsid`='$fsid' ";
	}
	//Loads database for club_events_pics 
	if($puf_pic_cat == "show_events_pics"){
		$queryWFC = "SELECT * FROM show_events_pics WHERE `fsid`='$fsid' ";
	}
	$resulth = mysqli_query($GLOBALS["___mysqli_ston"], $queryWFC);
	if(isset($resulth)){
		$num_rows = mysqli_num_rows($resulth);
	}else{
		$num_rows = "";
	}
	
//Checks if any photos are in database
if($num_rows > 0){	

	//Loads database for club_events_pics 
	if($puf_pic_cat == "ep3"){
		$query = "SELECT * FROM ".$db_table_prefix."ep3 WHERE `userId`='$ID02' ORDER BY 'id' DESC LIMIT $limit ";
	}

	//Loads database for club_pics 
	if($puf_pic_cat == "club_pics"){
		$query = "SELECT * FROM club_pics WHERE `nname`='$club_id' ORDER BY 'id' DESC LIMIT $limit ";
	}
	
	//Loads database for club_events_pics 
	if($puf_pic_cat == "club_events_pics"){
		$query = "SELECT * FROM club_events_pics WHERE `fsid`='$fsid' ORDER BY 'id' DESC LIMIT $limit ";
	}
	
	//Loads database for show_events_pics 
	if($puf_pic_cat == "show_events_pics"){
		$query = "SELECT * FROM show_events_pics WHERE `fsid`='$fsid' ORDER BY 'id' DESC LIMIT $limit ";
	}

	$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
		or die ("Couldn't ececute query. 7788");

	echo "<center>";

	while ($row = mysqli_fetch_array($result))
	{
		extract($row);
		
		//echo " <a href='${puf_pic_view_page}/?vimg_display=yes&vimg_display_id=$id&offset=${limit}#imgsview' title='Click to Enlarge'> ";
		echo "<a href='/${puf_pic_dir_small}${imgname}' data-lightbox='gallery-set' data-title='${puf_popup_title}' title='Click to Enlarge'>";
		echo " <img class='rounded_10' style='max-height:$tblwimg2;' border='0' width='100' src='/${puf_pic_dir_thumb}${imgname}'>";
		echo " </a> ";

	}

	echo "<br><font size='1'>*Click Image to Enlarge*</font>";
	echo "</center>";

		echo "<table width=100%><tr><td>";
		//echo "<Br> $num_rows <br>";
		if($limit < $num_rows){
			if($puf_pic_cat == "club_events_pics"){
				echo " <a href=\"${puf_pic_view_page}&offset_pics=" . ($limit + 20) . "#imgsview\">Show More Photos...</a>  "; 
			}else{
				echo " <a href=\"${puf_pic_view_page}?offset_pics=" . ($limit + 20) . "#imgsview\">Show More Photos...</a>  "; 
			}
		}	
		echo "</td></tr></table><hr>";
}//End rows check

?>