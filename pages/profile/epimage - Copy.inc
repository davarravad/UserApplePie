<?php

echo "<a class='anchor' name=imgs></a>";

$uri = $_SERVER['REQUEST_URI']; 

if(isset($_REQUEST['cimg'])){ $cimg = $_REQUEST['cimg']; }else{ $cimg = ""; }
if(isset($_REQUEST['vimg'])){ $vimg = $_REQUEST['vimg']; }else{ $vimg = ""; }
if(isset($_REQUEST['imgn'])){ $imgn = $_REQUEST['imgn']; }else{ $imgn = ""; }

if($vimg == 'yes'){


	echo "<div>";
	echo "<img class='rounded_10' border='0' width='$tblwimg' src='/content/profile/small/${imgn}'>";
	echo "<br><center>$cimg</center>";
	echo "</div><br><br>";

}

    // get pnum no from user to move user defined pnum    
    if(isset($_GET['offset'])){ $offset = $_GET['offset']; }else{ $offset = ""; } 
    
    // no of elements per page 
    
	if($offset){
		$limit = $offset;
	}else{
		$limit = 10; 
	}

	$queryWFC = "SELECT * FROM ep3 WHERE `userId`='$ID02' ";
	$resulth = mysqli_query($GLOBALS["___mysqli_ston"], $queryWFC);
	if(isset($resulth)){
		$num_rows = mysqli_num_rows($resulth);
	}else{
		$num_rows = "";
	}
	

$query = "SELECT * FROM ep3 WHERE `userId`='$ID02' ORDER BY 'id' DESC LIMIT $limit ";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 7788");



while ($row = mysqli_fetch_array($result))
{
	extract($row);
	

	echo " <a href='${site_url_link}member/$ID02/?imgn=${imgname}&vimg=yes&cimg=${content1}&offset=${limit}#imgs' title='Click to Enlarge'><img class='rounded_10' style='max-height:$tblwimg2;' border='0' width='100' src='/content/profile/thumb/${imgname}'></a> ";

}

echo "<br><center><font size='1'>*Click Image to Enlarge*</font>";

if(isUserLoggedIn() && $userIdme == $ID02){
	echo "<br><br>";
	echo "(<a href='${site_url_link}community/myimages/'>Edit/Upload My Member Profile Photos!</a>)";
}
echo "</center>";

	echo "<table width=100%><tr><td>";
 	//echo "<Br> $num_rows <br>";
	if($limit < $num_rows){
	echo " <a href=\"${site_url_link}member/$ID02/?offset=" . ($limit + 20) . "#imgs\">Show More Photos...</a>  "; 
	}	
	echo "</td></tr></table>";


?>