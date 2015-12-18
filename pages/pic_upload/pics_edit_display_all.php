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


if($enable_photos == "FALSE"){
	echo "<font color=red><strong>Sorry.. Photos are Disabled!</strong></font>";
}else{

echo "
<style type='text/css'>
#pictures li {
	float:left;
	height:110px;
	list-style:none outside;
	width:110px;
	text-align:center;
}
img {
	border:0;
	outline:none;
	max-height:75px;
}
#tooltip1 { 
	position: relative; 
}
#tooltip1 a span {
	display: none;
	color: #FFFFFF;
}
#tooltip1 a:hover span {
	display: block; 
	position: absolute; 
	width: 200px; 
	background: #aaa; 
	border: 1px SOLID #000; 
	left: 110px; 
	top: -20px; 
	color: #FFFFFF; 
	padding: 5px;
	z-index: 6000;
}
</style>
";

//Display all images uploaded to tazib for section

	echo "<center>";
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
    ###Page Title###
	echo "$puf_title_edit";

	echo "</td></tr>";
	echo "<tr><td class='content78'>";
    ###Page Content###


		// get pnum no from user to move user defined pnum    
		if(isset($_GET['pnum'])){ $pnum = $_GET['pnum']; }else{$pnum = "";} 
		
		// no of elements per page 
		$limit = 30; 
		
		// simple query to get total no of entries
		$result = mysqli_query($GLOBALS["___mysqli_ston"], "
			SELECT COUNT(*) FROM (
			(SELECT id,imgname,timestamp, 'club_pics' AS pic_type FROM club_pics  WHERE `nname`='$club_id')
			) AS total_count
		"); 
		$total = mysqli_num_rows($result); 

		// work out the pager values 
		$pager  = getPagerData($total, $limit, $pnum); 
		$offset = $pager->offset; 
		$limit  = $pager->limit; 
		$pnum   = $pager->pnum; 


		$query = "
			SELECT * FROM (
			(SELECT id,imgname,timestamp,nname,content1, 'club_pics' AS pic_type FROM club_pics WHERE `nname`='$club_id')
			) AS total_count
			ORDER BY `timestamp` DESC LIMIT $offset, $limit
		";
		
		$result = mysqli_query($GLOBALS["___mysqli_ston"], $query);
		

		
		echo '<ul id="pictures">';
		
		if($result){
			while ($row = mysqli_fetch_array($result))
			{
				$bgcolor = 'epboxa';
				extract($row);

					if(!empty($content1)){
						$content1 = stripslashes($content1);
						$content1 = ":<strong>Description</strong>: <br>$content1";
					}else{ $content1 = ""; }
					if(!empty($title)){
						$title = stripslashes($title);
						$title = ":<strong>Title</strong>: <br>$title<br>";
					}else{ $title = ""; }

					echo "<li class='epboxa' width='110'>";
						
						//Displays Vehicle Photos with correct link
						if($pic_type == "art"){
							echo "<center>";
							echo "Vehicle Photo<br>";
							echo "<a href='${site_url_link}VehiclePhoto/$id'>";
							echo "<img class='rounded_10' border='0' width='100' src='/content/art/thumb/${imgname}'>";					
							echo "</a>";
						}
						//Displays Club Events Photos with correct link
						if($pic_type == "club_events_pics"){
							echo "<center>";
							echo "Club Event<br>";
							echo "<a href='/Club/$nname/?fsid=$fsid&imgn=$imgname&vimg=yes#imgs'>";
							echo "<img class='rounded_10' border='0' width='100' src='/content/club/events/thumb/${imgname}'>";					
							echo "</a>";
						}
						//Displays Show Events Photos with correct link
						if($pic_type == "show_events_pics"){
							echo "<center>";
							echo "Show Event<br>";
							echo "<a href='/Shows/viewEvent/$fsid/&imgn=$imgname&vimg=yes#imgs'>";
							echo "<img class='rounded_10' border='0' width='100' src='/content/shows/thumb/${imgname}'>";					
							echo "</a>";
						}
						//Displays Club Photos with correct link
						if($pic_type == "club_pics"){
							echo "<center>";
							echo "Club Photo<br>";
							echo "<div id=\"tooltip1\">";
							echo "<a href='/Club/$nname/?vimg_display_id=$id&vimg_display=yes#imgsview'> ";
							echo "<img class='rounded_10' border='0' width='100' src='/content/club/thumb/${imgname}'>";					
							echo "<span>";
							echo "$title $content1";
							echo "</span></a></div>";
						}
						
						//Show Edit Image Button
						echo "<form enctype=\"multipart/form-data\" action=\"${site_url_link}?page=${return_page}&yes_edit=TRUE\" method=\"POST\" name=\"upload_form\"onsubmit=\"submit.disabled = true; return true;\">";
							//Let the form know we are about to edit an image
							echo "<input type='hidden' name='edit_photo_please' value='TRUE'>";
							echo "<input type='hidden' name='id' value='$id'>";
							echo "<input type='submit' value='Edit Photo' class='contSubmit' type='image' name='submit' onClick=\"this.value = 'Please Wait....'\" />";
						echo "</form>";
						
						echo "</center>";
						
					echo "</li>";
					//echo "</td></tr>";
					//echo "</table>";
					//echo "<br>";
					unset($timestamp, $timestart);
			
			}//End of while
		//End of result check
		}else{
			echo "This Club does not have any photos yet, ";
			echo "<a href='/Clubs/?pee=pics/pic_submit_club&club_id=$club_id'>Upload Photos</a>.";
		}
		
		echo "</ul>";
		echo "</td></tr></table>";

		if($result){
			//Start Display Page Numbers
			echo "<center><table width=100% class='epbox'><tr><td align=left>";
			// use $result here to output page content 
			// output paging system (could also do it before we output the page content) 
			if ($pnum == 1) // this is the first page - there is no previous page 
				; 
			else            // not the first page, link to the previous page 
				echo " < <a href=\"${site_url_link}?page=${return_page}&yes_edit=TRUE&pnum=".($pnum - 1)."\">Previous</a> | "; 

			if ($pnum == $pager->numPages) // this is the last page - there is no next page 
				; 
			else            // not the last page, link to the next page 
				echo " <a href=\"${site_url_link}?page=${return_page}&yes_edit=TRUE&pnum=".($pnum + 1)."\">Next</a> > "; 

			echo "</td><td align=center>";
			echo ".";
			for ($i = 1; $i <= $pager->numPages; $i++) { 
				//echo " - "; 
				if ($i == $pager->pnum) 
					echo "<font color=green><strong>$i</strong></font>."; 
				else 
					echo "<a href='${site_url_link}?page=${return_page}&yes_edit=TRUE&pnum=$i'>$i</a>."; 
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
		}
	
	echo "</center><br><br>";
}// End enable photos
?>



