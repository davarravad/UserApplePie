<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
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




?>