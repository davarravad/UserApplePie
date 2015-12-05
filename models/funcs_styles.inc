<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

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
	echo "<center>";
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
    
	// Display title of the page in header of page table
	echo "<h3>$stc_page_title</h3>"; 
	//echo "(Test Header: This page is using the new style setup!)";

	echo "</td></tr>";
	echo "<tr><td class='content78' align=center>";

}

// Style for bottom of page content
function style_footer_content(){

	// Close out the table
	//echo "(Test Footer: This page is using the new style setup!)";
	echo "</td></tr></table>";
	echo "</center>";

}




?>