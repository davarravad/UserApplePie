<center>
<?php

$uri = $_SERVER['REQUEST_URI']; 

if(isset($_REQUEST['cimg'])){ $cimg = $_REQUEST['cimg']; }else{ $cimg = ""; }
if(isset($_REQUEST['vimg'])){ $vimg = $_REQUEST['vimg']; }else{ $vimg = ""; }
if(isset($_REQUEST['imgn'])){ $imgn = $_REQUEST['imgn']; }else{ $imgn = ""; }

echo "Your Profile Photos only show up on your Car Truck Clubs Member Profile. <a href='${site_url_link}member/$userId'>My Profile</a>";
echo "<br>If uploading <b>Vehicle Photos</b> <a href='${site_url_link}editprofilemain/editvehicles/#uvp'>Click Here</a>.";
echo "<br><font color=green size=0.5>Note: Profile Photos and Vehicle Photos are not linked within the site.  Profile Photos are only shown within your Member Profile.</font>";
if($vimg == 'yes'){

	echo "<div>";
	echo "<img class='rounded_10' border='0' width='$tblw500' src='/content/profile/small/${imgn}'>";
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

	$queryWFC = "SELECT * FROM ".$db_table_prefix."ep3 WHERE `userId`='$userId'";
	$resulth = mysqli_query($GLOBALS["___mysqli_ston"], $queryWFC);
	if(isset($resulth)){
		$num_rows = mysqli_num_rows($resulth);
	}else{
		$num_rows = "";
	}
	

$query = "SELECT * FROM ".$db_table_prefix."ep3 WHERE `userId`='$userId' LIMIT $limit";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 89452");


echo "<table width=$tblw600 class=epboxb><tr><td align=center>";
while ($row = mysqli_fetch_array($result))
{
	extract($row);
	

	echo " <a href='${site_url_link}community/myimages/?imgn=${imgname}&vimg=yes&cimg=${content1}&offset=${limit}' title='Click to Enlarge'><img class='rounded_10' border='0' width='100' src='/content/profile/thumb/${imgname}'></a> ";

}
echo "</td></tr></table>";

echo "<br><center><font size='1'>*Click Image to Enlarge*</font></center>";

	echo "<table width=100%><tr><td>";
 	//echo "<Br> $num_rows <br>";
	if($limit < $num_rows){
	echo " <a href=\"${site_url_link}community/myimages/?offset=" . ($limit + 20) . "\">Show More Photos...</a>  "; 
	}	
	echo "</td></tr></table>";

	echo " ( <a href='${site_url_link}editprofilemain/picsubmit/'>Upload Profile Photos</a> ) ";
	echo " ( <a href='${site_url_link}editprofilemain/editimages/'>Edit My Profile Photos</a> ) <br>";


?>
</center>