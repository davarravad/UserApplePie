<center>
<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

$uri = $_SERVER['REQUEST_URI']; 

if(isset($_REQUEST['cimg'])){ $cimg = $_REQUEST['cimg']; }else{ $cimg = ""; }
if(isset($_REQUEST['vimg'])){ $vimg = $_REQUEST['vimg']; }else{ $vimg = ""; }
if(isset($_REQUEST['imgn'])){ $imgn = $_REQUEST['imgn']; }else{ $imgn = ""; }

	if($vimg == 'yes'){
		echo "<div>";
		echo "<img class='rounded_10' border='0' width='500' src='/content/profile/small/${imgn}'>";
		echo "<br><center>$cimg</center>";
		echo "</div><br><br>";
	}

    // get pnum no from user to move user defined pnum    
    if(isset($_GET['offset'])){ $offset = $_GET['offset']; }else{ $offset = ""; } 
    
    // no of elements per page 
    
	if($offset){
		$limit = $offset;
	}else{
		$limit = 20; 
	}
		
	$queryWFC = "
	(SELECT ep3.id, ep3.userId, ep3.nname, ep3.content1, ep3.imgdir, ep3.imgname, ep3.timestamp,
					friend.userId1, friend.userId2, friend.status1, friend.status2, 
	'ep3' AS post_type FROM ".$db_table_prefix."ep3 ep3
	LEFT JOIN ".$db_table_prefix."friend friend
	ON (ep3.userId = friend.userId1 AND friend.userId2 = $userIdme)
	OR (ep3.userId = friend.userId2 AND friend.userId1 = $userIdme)
	WHERE friend.status1 = '1' AND friend.status2 = '1'
	GROUP BY ep3.id)
	";
	
	$resulth = mysqli_query($GLOBALS["___mysqli_ston"], $queryWFC);
	if(isset($resulth)){
		$num_rows = mysqli_num_rows($resulth);
	}else{
		$num_rows = "";
	}
	
	$query = "$queryWFC ORDER BY `id` DESC LIMIT $limit";

	$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
		or die ("Couldn't ececute query. 84465158");


	echo "<table width=600 class=epboxb><tr><td align=center>";

		while ($row = mysqli_fetch_array($result))
		{
			extract($row);
			
			$userId1a = $userIdme;
			$userId2a = $userId;

			echo " <a href='${site_url_link}community/friendimages/?imgn=${imgname}&vimg=yes&cimg=${content1}&offset=${limit}' title='Click to Enlarge'><img class='rounded_10' border='0' width='100' style='max-height:60px' src='/content/profile/thumb/${imgname}'></a> ";

		}
		
	echo "</td></tr></table>";

	echo "<br><center><font size='1'>*Click Image to Enlarge*</font></center>";

	echo "<table width=100%><tr><td>";
 	//echo "<Br> $num_rows <br>";
	if($limit < $num_rows){
	echo " <a href=\"${site_url_link}community/friendimages/?offset=" . ($limit + 20) . "\">Show More Photos...</a>  "; 
	}	
	echo "</td></tr></table>";

?>
</center>