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


// Page style functions 
// Lets make things a little easier for future additions

// Style for top of page content
// Sets the title and description of the page
function style_header_content($stc_page_title, $stc_page_description){

	// Title and Description
	echo "<title>$stc_page_title</title>";
	if(!empty($stc_page_description)){
		echo "<meta name=\"description\" content=\"$stc_page_description\">";
	}
	
	// Start the top of the content
			echo "<div class='col-lg-8'>";
				echo "<div class='panel panel-default'>";
				// Display title of the page in header of page table
					echo "<div class='panel-heading'>";
						echo "<h3 class='jumbotron-heading'>$stc_page_title</h3>"; 
					echo "</div>";
				//echo "(Test Header: This page is using the new style setup!)";
					echo "<div class='panel-body'>";
				

}

// Style for bottom of page content
function style_footer_content(){

	// Close out the table
	//echo "(Test Footer: This page is using the new style setup!)";
					echo "</div>";
				echo "</div>";
			echo "</div>";
}

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

// Get Pager Data// Setup for pagination goods
function display_pagination($db_table, $view_post_name, $view_post_id, $order_by, $cur_page_url_link, $total_limit){
	// DB Table Name - Post Field Name - Post Field ID - Order By id ASC - Current Page URL - Posts Limit
	// Start Get Page Number Stuff
	global $mysqli, $db_table_prefix, $site_url_link;
	global $offset, $limit, $pnum, $total;
	
	// get pnum no from user to move user defined pnum    
	if(isset($_GET['pnum'])){ $pnum = $_GET['pnum']; }else{ $pnum = ""; } 

	// Query to get total num of mem being displayed
	$queryPN = "SELECT * FROM ".$db_table_prefix."$db_table WHERE `$view_post_name`='$view_post_id' ORDER BY $order_by";

	// simple query to get total no of entries
	if ($result = $mysqli->query("$queryPN")) {

		/* determine number of rows result set */
		$total = $result->num_rows;

		// printf("Topics:  %d \n", $total);

		/* close result set */
		$result->close();
	}

	// work out the pager values 
	$pager  = getPagerData($total, $total_limit, $pnum); 
	$offset = $pager->offset; 
	$limit  = $pager->limit; 
	$pnum   = $pager->pnum; 

	// End Get Page Number Stuff
		
			// Display page count and links
			if($total > $limit){
				echo "<div class='panel panel-info'>";
					echo "<div class='panel-heading text-center'>";
						echo "<nav>";
							echo "<ul class='pagination pagination-sm'>";
				
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
									echo "<li> <a href=\"${site_url_link}${cur_page_url_link}?pnum=1\">First</a> </li>";  // First
								}else{
									echo "<li class='disabled'> <a href='#'>First</a> </li>"; 
								}
								
								// output paging system (could also do it before we output the page content) 
								if ($pnum == 1){ // this is the first page - there is no previous page 
									echo "<li class='disabled'> <a href='#'>&laquo;</a> </li>"; 
								}else{            // not the first page, link to the previous page 
									echo "<li> <a href=\"${site_url_link}${cur_page_url_link}?pnum=".($pnum - 1)."\" aria-label='Previous'>&laquo;</a> </li> ";  // Previous
								}
								// If page 1 is not shown then show it here
								if($pnum >= $max){
									echo "<li> <a href=\"${site_url_link}${cur_page_url_link}?pnum=1\" class='epboxa'>1</a> </li>";
								}

								if($pager->numPages > $max){
									// If greater than max display links
									// Show pages close to current page
									for ($i = $sp; $i <= ($sp + $max - 1); $i++) { 
										if ($i == $pager->pnum) 
											echo "<li class='active'> <a href='#'>$i</a> </li>"; 
										else 
											echo "<li> <a href=\"${site_url_link}${cur_page_url_link}?pnum=$i\" class='epboxa'>$i</a> </li>"; 
									}
								}else{
									// If less than max display links
									for ($i = 1; $i <= $pager->numPages; $i++) { 
										if ($i == $pager->pnum) 
											echo "<li class='active'> <a href='#'>$i</a> </li>"; 
										else 
											echo "<li> <a href=\"${site_url_link}${cur_page_url_link}?pnum=$i\" class='epboxa'>$i</a> </li>"; 
									}
								}
								
								// Show last two pages if not close to them
								if($pnum < ($pager->numPages - floor($max / 2))){
									echo "<li> <a href=\"${site_url_link}${cur_page_url_link}?pnum=$pager->numPages\" class='epboxa'>$pager->numPages</a> </li>";
								}
								

								if ($pnum == $pager->numPages){ // this is the last page - there is no next page 
									echo "<li class='disabled'> <a href='#'>&raquo;</a> </li>"; 
								}else{            // not the last page, link to the next page 
									echo "<li> <a href=\"${site_url_link}${cur_page_url_link}?pnum=".($pnum + 1)."\" aria-label='Next'>&raquo;</a> </li> ";  // Next
								}
								// Show last page link if not on it
								if($pnum < $pager->numPages){
									echo "<li> <a href=\"${site_url_link}${cur_page_url_link}?pnum=$pager->numPages\">Last</a> </li>";
								}else{
									echo "<li class='disabled'> <a href='#'>Last</a> </li>"; 
								}
								

							echo "</ul>";
						echo "</nav>";
						
								echo "";
								$thetotal = ($offset + $limit);
								if($thetotal > $total){
									$thetotal2 = ($thetotal - $total);
									$thetotal3 = ($thetotal - $thetotal2);
									$thetotal = "$thetotal3";
								}
								echo "Showing $offset-$thetotal of $total Replys";
						
					echo "</div>";
				echo "</div>";
			} // End of pages check
} // End pagination goods


?>