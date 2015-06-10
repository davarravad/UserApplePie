<center>
<?

$userIdme = $userId;

	$uriref = $_SERVER['REQUEST_URI'];
	
	$querym = "SELECT * FROM friend WHERE `userId2`='$userIdme' AND `status2`='0'  ";
	$resultm = mysqli_query($GLOBALS["___mysqli_ston"], $querym);
	
	$num_rows = mysqli_num_rows($resultm);
	

echo "<table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td class=epbox>";
echo "<strong>Friend Requests  ( $num_rows )</strong>";
echo "</td></tr></table>";


	if($num_rows == 0){
		echo "<table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td class=epboxa>";
		echo "No new friend requests. ";
		echo "</td></tr></table>";
	}
	else{
			
		while ($rowm = mysqli_fetch_array($resultm))
		{
			$bgcolor = "epboxa";

			extract($rowm);	
	
			//echo "$userId1 - $userId2 - $status1 - $status2 <br>";
	
		$ID02 = $userId1;
	
		echo "<center><table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td width=100 class=$bgcolor>";
		
		echo "<a href='${site_url_link}member/$ID02/'>";
		require "pages/profile/userimage.inc";
		echo "</a>";
	
		echo "</td><td class=$bgcolor>";
	
		echo "<strong>";
		require "pages/profile/usernamemem.inc";
		echo "</strong>";
	
		echo " wants to be your friend. ";
		//echo "  (<a href='${site_url_link}?page=friend/addfriend&id=$id&approve=TRUE'>Approve Friendship</a>)<br>";	

				echo "
					<form method=\"post\" action=\"${site_url_link}?page=friend/addfriend\">
				";
				// create multi sessions
				if(isset($session_token_num)){
					$session_token_num = $session_token_num + 1;
				}else{
					$session_token_num = "1";
				}
				form_token();
				echo "
						<input type=\"hidden\" name=\"id\" value=\"$id\">
						<input type=\"hidden\" name=\"approve\" value=\"TRUE\">
						<label title=\"Send\"><input type=\"submit\" value=\"Approve Friendship\" /></label>
					</form>
				";			
	
		echo "</td></tr></table></center>";	
	
		}
	
	}

echo "<br><br>";

	$query414 = "SELECT * FROM friend WHERE ((`userId1`='$userIdme' AND `status2`='1') OR (`userId2`='$userIdme' AND `status2`='1'))";
	$result414 = mysqli_query($GLOBALS["___mysqli_ston"], $query414);
	
	$num_rows44 = mysqli_num_rows($result414);

echo "<a class='anchor' name=tiptop></a>";	
echo "<table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td class=epbox>";
echo "<strong>My Friends ( $num_rows44 ) </strong>";
echo "</td></tr></table>";

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
    $limit = 20; 
    
    // simple query to get total no of entries
    $queryPN = "select count(*) from friend WHERE ((`userId1`='$userIdme' AND `status2`='1') OR (`userId2`='$userIdme' AND `status2`='1')) "; 
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

//Check to see if user has any friends
if($total > 0){
	
	$query44 = "SELECT * FROM friend WHERE ((`userId1`='$userIdme' AND `status2`='1') OR (`userId2`='$userIdme' AND `status2`='1'))  ORDER BY `id` DESC LIMIT $offset, $limit ";
	$result44 = mysqli_query($GLOBALS["___mysqli_ston"], $query44);
	
		echo "<center>";
				
		while ($row44 = mysqli_fetch_array($result44))
		{
	
			$bgcolor = "epboxa";
	
			extract($row44);	
	
			//echo "$userId1 - $userId2 - $status1 - $status2 <br>";
			if($userId2 == $userIdme){  
				$ID02 = $userId1;
			}else{
				$ID02 = $userId2;
			}
			echo "<table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td width=100 class=$bgcolor>";
			
			echo "<a href='${site_url_link}member/$ID02/'>";
			require "pages/profile/userimage.inc";
			echo "</a>";
		
			echo "</td><td class=$bgcolor>";
		
			echo "<strong>";
			require "pages/profile/usernamemem.inc";
			echo "</strong>";
		
			echo " is your friend.  (<a href='${site_url_link}member/$ID02/'>View Profile</a>)<br>";		
			
			require "pages/friend/unfriend.inc";
			
			echo "</td></tr></table>";	
		
		}
		

			echo "<table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td class=epbox>";
			echo "<table width=100%><tr><td>";
				// use $result here to output page content 

				// output paging system (could also do it before we output the page content) 
				if ($pnum == 1) // this is the first page - there is no previous page 
					; 
				else            // not the first page, link to the previous page 
					echo " < <a href=\"${site_url_link}community/myfriends/?pnum=".($pnum - 1)."#tiptop\">Previous</a> | "; 

				if ($pnum == $pager->numPages) // this is the last page - there is no next page 
					; 
				else            // not the last page, link to the next page 
					echo " <a href=\"${site_url_link}community/myfriends/?pnum=".($pnum + 1)."#tiptop\">Next</a> > "; 

			echo "</td><td align=center>";
				echo ".";
				for ($i = 1; $i <= $pager->numPages; $i++) { 
					//echo " - "; 
					if ($i == $pager->pnum) 
						echo "<font color=green><strong>$i</strong></font>."; 
					else 
						echo "<a href=\"${site_url_link}community/myfriends/?pnum=$i#tiptop\">$i</a>."; 
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
			echo "</td></tr></table>";
}else{
	echo "<table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td class=epboxa>";
	echo "You Currently Don't Have any Friends.";
	echo "</td></tr></table>";
}
				
			
	
echo "</center>";


?>
</center>