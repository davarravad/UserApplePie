<style type="text/css">
#pictures li {
	float:left;
	height:110px;
	list-style:none outside;
	width:110px;
	text-align:center;
}
#img_thumb {
	border:0;
	outline:none;
	max-height:75px;
}
</style>

<?php
//Include popup file
	require "pages/pic_upload/popupimgs/img_header.inc";

	//Display all images uploaded to tazib
	
	//Title and Description
	//echo "<title>Photo Gallery</title>";
	echo "<meta name=\"description\" content=\"Listing of All Photos Uploaded to Car Truck Clubs\">";

	echo "<center>";
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
    ###Page Title###
	echo "<h3>Photo Gallery</h3>";

	echo "</td></tr>";
	echo "<tr><td class='content78'>";
    ###Page Content###

		//Start Page Number Math
		function getPagerData($numHits, $limit, $pnum) 
		{ 
			   $numHits  = (int) $numHits; 
			   $limit    = max((int) $limit, 1); 
			   $pnum     = (int) $pnum; 
			   $numPages = ceil($numHits / $limit); 
	
			   $pnum = max($pnum, 1); 
			   $pnum = min($pnum, $numPages); 
	
			   $offset = ($pnum - 1) * $limit; 
	
			   $ret = new stdClass; 
	
			   $ret->offset   = $offset; 
			   $ret->limit    = $limit; 
			   $ret->numPages = $numPages; 
			   $ret->pnum     = $pnum; 
	
			   return $ret; 
		} 
		//End Page Number Math


		// get pnum no from user to move user defined pnum    
		if(isset($_GET['pnum'])){ $pnum = $_GET['pnum']; }else{$pnum = "";} 
		
		// no of elements per page 
		$limit = 30; 
		
		// simple query to get total no of entries
		$query_gal = "
			SELECT COUNT(*) FROM (
			(SELECT id,imgname,timestamp, 'art' AS pic_type FROM art)
			UNION
			(SELECT id,imgname,timestamp, 'club_event_pics' AS pic_type FROM club_events_pics)
			UNION
			(SELECT id,imgname,timestamp, 'show_event_pics' AS pic_type FROM show_events_pics)
			UNION
			(SELECT id,imgname,timestamp, 'club_pics' AS pic_type FROM club_pics)
			) AS total_count
		"; 
		if ($result_gal = $mysqli->query("$query_gal")) {
			/* determine number of rows result set */
			$total_gal = $result_gal->fetch_row();
			$total = $total_gal['0'];
			/* close result set */
			$result_gal->close();
		}

		// work out the pager values 
		$pager  = getPagerData($total, $limit, $pnum); 
		$offset = $pager->offset; 
		$limit  = $pager->limit; 
		$pnum   = $pager->pnum; 


		$query = "
			SELECT * FROM (
			(SELECT id,imgname,timestamp,nname,fsid, 'club_events_pics' AS pic_type FROM club_events_pics)
			UNION
			(SELECT id,imgname,timestamp,nname,fsid, 'show_events_pics' AS pic_type FROM show_events_pics)
			UNION
			(SELECT id,imgname,timestamp,nname,null, 'club_pics' AS pic_type FROM club_pics)
			UNION
			(SELECT id,imgname,timestamp,null,null, 'art' AS pic_type FROM art)
			) AS total_count
			ORDER BY `timestamp` DESC LIMIT $offset, $limit
		";

// Check for results if any
if ($result = $mysqli->query("$query")) {
		
		echo '<ul id="pictures">';
		
		$arr_gal = $result->fetch_all(MYSQLI_BOTH);
		foreach($arr_gal as $row_gal)
		{
			$pic_type = $row_gal['pic_type'];
			$id = $row_gal['id'];
			$fsid = $row_gal['fsid'];
			$nname = $row_gal['nname'];
			$imgname = $row_gal['imgname'];
			$timestamp = $row_gal['timestamp'];
			
			// Table Class
			$bgcolor = 'epboxa';

				echo "<li class='epboxa' width='110'>";
					
					//Displays Vehicle Photos with correct link
					if($pic_type == "art"){
						echo "<center>";
						echo "<a href='${site_url_link}VehiclePhoto/$id/'>";
						echo "Vehicle Photo";
						echo "</a><br>";
						echo "<a href='/content/art/small/${imgname}' data-lightbox='gallery-set' data-title='Vehicle Photo'>";
						echo "<img class='rounded_10' id='img_thumb' border='0' width='100' src='/content/art/thumb/${imgname}'>";					
						echo "</a>";
					}
					//Displays Club Events Photos with correct link
					if($pic_type == "club_events_pics"){
						echo "<center>";
						echo "<a href='${site_url_link}Club/$fsid/'>";
						echo "Club Event";
						echo "</a><br>";
						echo "<a href='/content/club/events/small/${imgname}' data-lightbox='gallery-set' data-title='Club Event Photo'>";
						echo "<img class='rounded_10' id='img_thumb' border='0' width='100' src='/content/club/events/thumb/${imgname}'>";					
						echo "</a>";
					}
					//Displays Shows Events Photos with correct link
					if($pic_type == "show_events_pics"){
						echo "<center>";
						echo "<a href='${site_url_link}Shows/viewEvent/$fsid/'>";
						echo "Show Event";
						echo "</a><br>";
						echo "<a href='/content/shows/small/${imgname}' data-lightbox='gallery-set' data-title='Show Event Photo'>";
						echo "<img class='rounded_10' id='img_thumb' border='0' width='100' src='/content/shows/thumb/${imgname}'>";					
						echo "</a>";
					}
					//Displays Club Photos with correct link
					if($pic_type == "club_pics"){
						echo "<center>";
						echo "<a href='${site_url_link}Club/$nname/'>";
						echo "Club Photo";
						echo "</a><br>";
						echo "<a href='/content/club/small/${imgname}' data-lightbox='gallery-set' data-title='Club Photo'>";
						echo "<img class='rounded_10' id='img_thumb' border='0' width='100' src='/content/club/thumb/${imgname}'>";					
						echo "</a>";
					}
					
					//Display how long ago this was posted
					$timestart = "$timestamp";  //Time of post
					require_once "models/timediff.inc";
					echo " <br><font color=green>Age: " . dateDiff("now", "$timestart", 1) . "</font> ";
					echo "</center>";
					
				echo "</li>";
				//echo "</td></tr>";
				//echo "</table>";
				//echo "<br>";
				unset($timestamp, $timestart);
		
		}//End of while
		
		echo "</ul>";
		echo "</td></tr></table>";

	//Start Display Page Numbers
	echo "<center><table width=100% class='epbox'><tr><td align=left>";
		// use $result here to output page content 
		// output paging system (could also do it before we output the page content) 
		if ($pnum == 1) // this is the first page - there is no previous page 
			; 
		else            // not the first page, link to the previous page 
			echo " < <a href=\"${site_url_link}Gallery/?pnum=".($pnum - 1)."\">Previous</a> | "; 

		if ($pnum == $pager->numPages) // this is the last page - there is no next page 
			; 
		else            // not the last page, link to the next page 
			echo " <a href=\"${site_url_link}Gallery/?pnum=".($pnum + 1)."\">Next</a> > "; 

		echo "</td><td align=center>";
		echo ".";
		for ($i = 1; $i <= $pager->numPages; $i++) { 
			//echo " - "; 
			if ($i == $pager->pnum) 
				echo "<font color=green><strong>$i</strong></font>."; 
			else 
				echo "<a href='${site_url_link}Gallery/?pnum=$i'>$i</a>."; 
		} 
		echo "</td><td align=right>";
		$thetotal = ($offset + $limit);
		if($thetotal > $total){
			$thetotal2 = ($thetotal - $total);
			$thetotal3 = ($thetotal - $thetotal2);
			$thetotal = "$thetotal3";
		}
		echo "Showing $offset-$thetotal of $total";
	echo "</td></tr></table><center>";
	//End Display Page Number
	
	echo "</center><br><br>";

}else{
	echo "No Photos in Gallery!";
	echo "</td></tr></table>";
}//End result check
	


?>