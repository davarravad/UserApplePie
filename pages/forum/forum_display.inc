<?php

	// Main Page for forum
	//echo "Welcome to the forum for diy stuff. ($load_cat)($load_id)<hr>";
	
	// Check database for sections
	
	global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix, $websiteName;

	// Get all Categories from database
	$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_cat`='$load_cat' LIMIT 1";
	$result = $mysqli->query($query);
	$arr = $result->fetch_all(MYSQLI_BOTH);
	foreach($arr as $row)
	{
		$f_cat = $row['forum_cat'];
		$f_des = $row['forum_des'];
		$f_id = $row['forum_id'];

		$f_cat = stripslashes($f_cat);
		$f_des = stripslashes($f_des);

		// Page title
		$stc_page_title = "$websiteName - Forum - $f_cat";
		// Page Description
		$stc_page_description = "$f_des";
		// Run Top of page func
		style_header_content($stc_page_title, $stc_page_description);
		// Which database do we use
		$stc_page_sel = "diy";
		
		// Display Link of where we are at on the forum
		echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td>";
			echo "<a href='${site_url_link}${site_forum_title}/'>Forum Home</a> / ";
			echo "<a href='${site_url_link}${site_forum_title}/forum_display/$f_cat/$f_id/'>$f_cat</a>";
		echo "</td></tr></table>";
		
		echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class=hr2>";
		echo "<strong>$f_cat</strong><br>";
		echo "</td></tr><tr><td class='content78'>";
		echo "$f_des";

			// Get all Sub Categories for current category
			//$query = "SELECT * FROM forum_posts WHERE `forum_id`='$f_id' ORDER BY forum_timestamp DESC";
			$query = "
				SELECT sub.*
				FROM
				(SELECT 
					fp.forum_post_id as forum_post_id, fp.forum_id as forum_id, 
					fp.forum_user_id as forum_user_id, fp.forum_title as forum_title, 
					fp.forum_content as forum_content, fp.forum_edit_date as forum_edit_date,
					fp.forum_timestamp as forum_timestamp, fpr.id as id,
					fpr.fpr_post_id as fpr_post_id, fpr.fpr_id as fpr_id,
					fpr.fpr_user_id as fpr_user_id, fpr.fpr_title as fpr_title,
					fpr.fpr_content as fpr_content, fpr.fpr_edit_date as fpr_edit_date,
					fpr.fpr_timestamp as fpr_timestamp,		
					GREATEST(fp.forum_timestamp, COALESCE(fpr.fpr_timestamp, '00-00-00 00:00:00')) AS tstamp
					FROM ".$db_table_prefix."forum_posts fp
					LEFT JOIN ".$db_table_prefix."forum_posts_replys fpr
					ON fp.forum_post_id = fpr.fpr_post_id
					WHERE fp.forum_id=$f_id
					ORDER BY tstamp DESC
				) sub
				
				GROUP BY forum_post_id
				ORDER BY tstamp DESC
			";

		// Start Get Page Number Stuff
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

		// Query to get total num of mem being displayed
		$queryPN = "$query";
		
		// simple query to get total no of entries
		if ($result = $mysqli->query("$queryPN")) {

			/* determine number of rows result set */
			$total = $result->num_rows;

			// printf("Topics:  %d \n", $total);

			/* close result set */
			$result->close();
		}

		// work out the pager values 
		$pager  = getPagerData($total, $limit, $pnum); 
		$offset = $pager->offset; 
		$limit  = $pager->limit; 
		$pnum   = $pager->pnum; 
		
		// Global link to this page for page nums
		$cur_page_url_link = "${site_forum_title}/forum_display/$f_cat/$f_id/";
		
		// End Get Page Number Stuff
			
			$query_b = "${query} LIMIT $offset, $limit";
			
			if($result = $mysqli->query($query_b)){
				$arr2 = $result->fetch_all(MYSQLI_BOTH);
				foreach($arr2 as $row2)
				{
					$f_p_id = $row2['forum_post_id'];
					$f_p_id_cat = $row2['forum_id'];
					$f_p_title = $row2['forum_title'];
					$f_p_timestamp = $row2['forum_timestamp'];
					$f_p_user_id = $row2['forum_user_id'];
					$tstamp = $row2['tstamp'];
					$f_p_user_name = get_user_name_2($f_p_user_id);
					
					$f_p_title = stripslashes($f_p_title);
					
					echo "<table width='100%' border='0' cellpadding='0' cellspacing='0'><tr><td valign='top' width='100%' class='epboxc'>";
						echo "<table width='100%' border='0' cellpadding='0' cellspacing='0'><tr><td align='left'>";
							//echo "($tstamp)"; // Test timestamp
							echo "<strong><font size='2'>";
							echo "<a href='${site_url_link}${site_forum_title}/display_topic/$f_p_id/' title='$f_p_title' ALT='$f_p_title'>$f_p_title</a>";
							echo "</font></strong>";
							echo "<br>";
							echo "&nbsp; Created by <a href='${site_url_link}member/$f_p_user_id/'>$f_p_user_name</a> - ";
							//Display how long ago this was posted
							$timestart = "$f_p_timestamp";  //Time of post
							require_once "models/timediff.inc";
							echo " <font color=green> " . dateDiff("now", "$timestart", 1) . " ago</font> ";
							//echo "($f_p_timestamp)"; // Test timestamp
				
							echo "</td><td align='left' width='275'>";
							
								// Display total replys
								echo " <table border='0' cellpadding='0' cellspacing='0'><tr><td width='100px'> ";
									// Display total topic replys
									total_topic_replys_display_a($f_p_id);
								echo " </td><td> ";
									// Display total sweets
									// ex=(sweet_id, sweet_sec_id, 'sweet_sub', 'sweet_location')
									total_topic_sweets($f_p_id, NULL, 'sweet', 'forum_posts');
								echo " </td><td align='right'> &nbsp; ";
									// Display total views
									total_topic_views($f_p_id, NULL, 'views', 'diy');
								echo "</td></tr></table>";
								
							
								// Get last reply date from database
								$query33 = "SELECT * FROM ".$db_table_prefix."forum_posts_replys WHERE `fpr_post_id`='$f_p_id' ORDER BY id DESC LIMIT 1";
								$result33 = $mysqli->query($query33);
								$arr33 = $result33->fetch_all(MYSQLI_BOTH);
								foreach($arr33 as $row33)
								{
									$rp_user_id2 = $row33['fpr_user_id'];
									$rp_timestamp2 = $row33['fpr_timestamp'];
									
									$rp_user_name2 = get_user_name_2($rp_user_id2);
									
									//Display how long ago this was posted
									$timestart = "$rp_timestamp2";  //Time of post
									require_once "models/timediff.inc";
									echo " Last Reply By <a href='${site_url_link}member/$rp_user_id2/'>$rp_user_name2</a> <font color=green> " . dateDiff("now", "$timestart", 1) . " ago</font> ";
									//echo "($rp_timestamp2)"; // Test timestamp
									unset($timestart, $rp_timestamp2);
								}
								
						echo "</td></tr></table>";
					echo "</td></tr></table>";
					
				} // End query
			} // End query check
				
		echo "</td></tr></table>";
		
		// Display page count and links
		if($total > $limit){
			echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td align='center' valign='top' class='content78'>";
				echo "<center><table width=100%><tr><td align=left width='25%'>";
				// use $result here to output page content 

				// output paging system (could also do it before we output the page content) 
				if ($pnum == 1) // this is the first page - there is no previous page 
					; 
				else            // not the first page, link to the previous page 
					echo " < <a href=\"${site_url_link}${cur_page_url_link}?pnum=".($pnum - 1)."\">Previous</a> | "; 

				if ($pnum == $pager->numPages) // this is the last page - there is no next page 
					; 
				else            // not the last page, link to the next page 
					echo " <a href=\"${site_url_link}${cur_page_url_link}?pnum=".($pnum + 1)."\">Next</a> > "; 

				echo "</td><td align=center width='50%'>";
				
				// Setup page links display
				// Max Num Of Page Links
				$max = "5";
				if($pnum < $max){
					$sp = 1;
				}elseif($pnum >= ($pager->numPages - floor($max / 2)) ){
					$sp = $pager->numPages - $max + 1;
				}elseif($pnum >= $max){
					$sp = $pnum  - floor($max/2);
				}
				
				// Display page num links
				
				// Display link for first page if not currently viewing it
				if($pnum >= 2){
					echo " &lt;  <a href=\"${site_url_link}${cur_page_url_link}?pnum=1\">First</a>  ";
				}
				
				// If page 1 is not shown then show it here
				if($pnum >= $max){
					echo "<a href=\"${site_url_link}${cur_page_url_link}?pnum=1\" class='epboxa'>1</a>...";
				}

				if($pager->numPages > $max){
					// If greater than max display links
					// Show pages close to current page
					for ($i = $sp; $i <= ($sp + $max - 1); $i++) { 
						if ($i == $pager->pnum) 
							echo "<font color=green class='epbox'><strong>$i</strong></font>"; 
						else 
							echo "<a href=\"${site_url_link}${cur_page_url_link}?pnum=$i\" class='epboxa'>$i</a>"; 
					}
				}else{
					// If less than max display links
					for ($i = 1; $i <= $pager->numPages; $i++) { 
						if ($i == $pager->pnum) 
							echo "<font color=green class='epbox'><strong>$i</strong></font>"; 
						else 
							echo "<a href=\"${site_url_link}${cur_page_url_link}?pnum=$i\" class='epboxa'>$i</a>"; 
					}
				}
				
				// Show last two pages if not close to them
				if($pnum < ($pager->numPages - floor($max / 2))){
					echo "...<a href=\"${site_url_link}${cur_page_url_link}?pnum=$pager->numPages\" class='epboxa'>$pager->numPages</a>";
				}
				
				// Show last page link if not on it
				if($pnum < $pager->numPages){
					echo "  <a href=\"${site_url_link}${cur_page_url_link}?pnum=$pager->numPages\">Last</a> &gt;  ";
				}
				
				echo "</td><td align=right width='25%'>";
				$thetotal = ($offset + $limit);
				if($thetotal > $total){
					$thetotal2 = ($thetotal - $total);
					$thetotal3 = ($thetotal - $thetotal2);
					$thetotal = "$thetotal3";
				}
				echo "Showing $offset-$thetotal of $total Topics";
				echo "</td></tr></table>";
			echo "</td></tr></table>";
		} // End of pages check
			
		echo "<br>";
		if(isUserLoggedIn()){
			echo "<form enctype=\"multipart/form-data\" action=\"${site_url_link}${site_forum_title}/new_topic/${f_id}/\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" >";
				
				// create multi sessions
				if(isset($session_token_num)){
					$session_token_num = $session_token_num + 1;
				}else{
					$session_token_num = "1";
				}
				form_token();
				
				echo "<input type=\"hidden\" name=\"forum_id\" value=\"$f_id\" />";
				echo "<input type=\"submit\" value=\"Create Topic\" name=\"createtopic\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				
			echo "</form>";
		} // End Log in check
		
		// Run Footer of page func
		style_footer_content();
		
	}


?>