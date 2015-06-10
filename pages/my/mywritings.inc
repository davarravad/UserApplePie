<?php

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

    // get pnum no from user to move user defined pnum    
    if(isset($_GET['pnum'])){ $pnum = $_GET['pnum']; }else{ $pnum = ""; }
    
    // no of elements per page 
    $limit = 10; 
    
    // simple query to get total no of entries
    $result = mysqli_query($GLOBALS["___mysqli_ston"], "select count(*) from submit WHERE `name`='$nname' "); 
    $total = mysql_result($result, 0, 0); 

    // work out the pager values 
    $pager  = getPagerData($total, $limit, $pnum); 
    $offset = $pager->offset; 
    $limit  = $pager->limit; 
    $pnum   = $pager->pnum; 



$query = "SELECT * FROM submit WHERE `name` = '$nname' ORDER BY `int` DESC LIMIT $offset, $limit";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query);
	//or die ("Couldn't ececute query. 2285");


//HTML Stuff



if($result){
while ($row = mysqli_fetch_array($result))
{


		$bgcolor = ($i % 2) ?epboxa : epboxb;
		$i++;

	extract($row);

	if($type == Poem){
		$taz_type = "poems";
	}
	if($type == Story){
		$taz_type = "stories";
	}
	if($type == Quote){
		$taz_type = "quotes";
	}
	
	$title = stripslashes($title);

	echo "<table width=100%><tr><td class='$bgcolor' width=40%>";
	echo "&nbsp<span class='title'>Title</span>: ";	
	echo "<a href='${site_url_link}VehicleProfile/$int'>$title</a> ";
	echo "</td><td class='$bgcolor' width=30%>";
	echo "&nbsp; <span class='title'>Author</span>: ";
	echo "$name"; 
	echo "</td><td class='$bgcolor' width=30%>";
	echo "&nbsp; <span class='title'>Type</span>: ";
	echo "<a href='${site_url_link}$taz_type/'>$type</a> <br>";
	echo "</td></tr></table>";


	

}
}
else{
	echo "No Content Found.  <a href='${site_url_link}?page=st/submit'>Submit Vehicle Profile</a><br><Br>";
}

echo "<table width=100%><tr><td>";

 // use $result here to output page content 

    // output paging system (could also do it before we output the page content) 
    if ($pnum == 1) // this is the first page - there is no previous page 
        ; 
    else            // not the first page, link to the previous page 
        echo " < <a href=\"${site_url_link}?page=my/mytazib&pee=mywritings&pnum=".($pnum - 1)."\">Previous</a> | "; 

    if ($pnum == $pager->numPages) // this is the last page - there is no next page 
        ; 
    else            // not the last page, link to the next page 
        echo " <a href=\"${site_url_link}?page=my/mytazib&pee=mywritings&pnum=".($pnum + 1)."\">Next</a> > "; 

	echo "</td><td align=center>";
echo ".";
    for ($i = 1; $i <= $pager->numPages; $i++) { 
        //echo " - "; 
        if ($i == $pager->pnum) 
            echo "<font color=green><strong>$i</strong></font>."; 
        else 
            echo "<a href=\"${site_url_link}?page=my/mytazib&pee=mywritings&pnum=$i\">$i</a>."; 
    } 
	echo "</td><td align=right>";
	$thetotal = ($offset + $limit);
	if($thetotal > $total){
		$thetotal2 = ($thetotal - $total);
		$thetotal3 = ($thetotal - $thetotal2);
		$thetotal = "$thetotal3";
	}
	echo "Showing $offset-$thetotal of $total";
	
	echo "</td></tr></table>";


?>