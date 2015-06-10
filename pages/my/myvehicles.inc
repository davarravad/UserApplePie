<center><b>
<a href='<? echo "${site_url_link}"; ?>editprofilemain/editvehicles/'>Edit My Vehicles</a>
</b></center>

<?
	require_once "pages/my/myvehicleprofiles.inc";
?>
<br><center><a href='<? echo "${site_url_link}"; ?>SubmitVehicleProfile/'>Create New Vehicle Profile</a></center><hr>

<center><h3>My Vehicle Photos</h3></center>
<?php


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
    if(isset($_GET['pnum'])){ $pnum = $_GET['pnum']; }else{ $pnum = ""; } 
    
    // no of elements per page 
    $limit = 20; 
    
    // simple query to get total no of entries
    $queryPN = "select count(*) from art WHERE `name` = '$nname' "; 
	// simple query to get total no of entries
	$resultPN = $mysqli->query("$queryPN");
	/* determine number of rows result set */
	$totalPN = $resultPN->fetch_row();
	$total = $totalPN['0'];
	/* close result set */
	$resultPN->close();

    // work out the pager values 
    $pager  = getPagerData($total, $limit, $pnum); 
    $offset = $pager->offset; 
    $limit  = $pager->limit; 
    $pnum   = $pager->pnum; 



$query = "SELECT * FROM art WHERE `name` = '$nname' ORDER BY `id` DESC LIMIT $offset, $limit";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query);
	//or die ("");

//HTML Stuff



if($result){

		echo "<a class='anchor' name=tiptop></a>";

		while ($row = mysqli_fetch_array($result))
		{

				$bgcolor = "epboxa";

			extract($row);

					$title = stripslashes($title);

			echo "<table width=100%><tr><td class='$bgcolor' width=100>";
			echo "<a href='${site_url_link}VehiclePhoto/$id'>";
			echo "<img class='rounded_10' border='0' width='100' src='/content/art/thumb/${imgname}'>";
			echo "</a>";
			echo "</td><td class='$bgcolor'>";	
			echo "&nbsp; <span class='title'>Title</span>: ";

		if($title){	
			echo "<a href='${site_url_link}VehiclePhoto/$id'>$title</a>";
		}else{
			echo "<a href='${site_url_link}VehiclePhoto/$id'>No Title</a>";
		}	
			echo "<br>";
		require "pages/profile/vehicleid.inc";
			echo "<br> <span class='title'>Author</span>: ";
			echo "$name";
					//Checks to see if user is loged in and if the post is the logged in users
					//Displays link to edit post if belongs to user
					if(isUserLoggedIn())
					{
						if($usrida == $userId){
							echo " - (<a href='${site_url_link}editprofilemain/editvehicles/#image$id'>Edit Vehicle</a>)";
						}
					}
			echo "<br>";
			echo "<a href='${site_url_link}editprofilemain/editvehicles/#image$id'>Edit Vehicle Information</a>";
			echo "</td></tr></table>";

		}

	//Start Display Page Numbers
		echo "<center><table width=100% class='epbox'><tr><td align=left>";

	   // use $result here to output page content 

		// output paging system (could also do it before we output the page content) 
		if ($pnum == 1) // this is the first page - there is no previous page 
			; 
		else            // not the first page, link to the previous page 
			echo " < <a href=\"${site_url_link}community/myvehicles/?pnum=".($pnum - 1)."#tiptop\">Previous</a> | "; 

		if ($pnum == $pager->numPages) // this is the last page - there is no next page 
			; 
		else            // not the last page, link to the next page 
			echo " <a href=\"${site_url_link}community/myvehicles/?pnum=".($pnum + 1)."#tiptop\">Next</a> > "; 

		echo "</td><td align=center>";
	echo ".";
		for ($i = 1; $i <= $pager->numPages; $i++) { 
			//echo " - "; 
			if ($i == $pager->pnum) 
				echo "<font color=green><strong>$i</strong></font>."; 
			else 
				echo "<a href='${site_url_link}community/myvehicles/?pnum=$i#tiptop'>$i</a>."; 
		} 
		echo "</td><td align=right>";
		$thetotal = ($offset + $limit);
		if($thetotal > $total){
			$thetotal2 = ($thetotal - $total);
			$thetotal3 = ($thetotal - $thetotal2);
			$thetotal = "$thetotal3";
		}
		echo "Showing $offset-$thetotal of $total";


	echo "</td></tr></table></center>";

	//End Display Page Number
		
}

	echo "<br><center><a href='${site_url_link}SubmitVehiclePhoto/'>Submit Vehicle Photos</a></center>";



?>