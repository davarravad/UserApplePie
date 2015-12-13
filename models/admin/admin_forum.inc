<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// UserApplePie Forum Admin Page
// Allows Admins to edit the site forum

// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){

	// Title of page
	echo "<center>";
	echo "<strong>Admin Zone - $websiteName Site Forum</strong>"; 
	echo "</center><br><Br>";
	
	// Display Current Forum Titles and Categories
	
	// Allow admin to rearrange forum order
	
	// Allow admin to edit or delete titles and categories
	
	// Allow admin to Create Titles
	
	// Allow admin to Create Category
	
	// Allow admin to Set Permissions
	
	// Allow admin to Close Topics and Replies
	
	// Allow admin to Block Topics and Replies
	
	// Check to see if admin is doing anything
	if(!empty($_POST))
	{
		
	} 
	else
	{
		// Default display if no functions are requested
		echo "This is a temp page for notes.";
		echo "Open the <a href='".$websiteUrl."Forum/'>Forum</a> to Do Admin Stuff";
	}
	
}

?>