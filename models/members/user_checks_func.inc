<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Created by David "DaVaR" Sargent
// These functions check to see if users have or have not 
// updated basic information about themselves then 
// displays message with link to update stuff

// Only use this feature when a user is logged in
if(isUserLoggedIn()){

	//** User Profile Info Check **//

	// Checks to see if user has added their first name to profile
	// Shows message if they have not done so with link to edit profile

		// Gets user's first name
		$up_get_firstname_check = get_up_info($userIdme, 'userFirstName');
		// Test output vars
		//echo " (UID=$userIdme----FirstName=$up_get_firstname_check) ";
		
	// Checks to see if user has added their sex to profile
	// Shows message if they have not done so with link to edit profile
		
		// Gets user's sex
		$up_get_sex_check = get_up_info($userIdme, 'userAddr2');
		// Test output vars
		//echo " (UID=$userIdme----Sex=$up_get_sex_check) ";
		
	// Checks to see if user has added their first name to profile
	// Shows message if they have not done so with link to edit profile
		
		// Gets user's zip
		$up_get_location_check = get_up_info($userIdme, 'userCity');
		// Test output vars
		//echo " (UID=$userIdme----ZIP=$up_get_location_check) ";

	// Checks to see if user has added their photo to profile
	// Shows message if they have not done so with link to upload profile pic
		
		// Gets user's zip
		$up_get_mainpic_check = get_up_info($userIdme, 'mainPic');
		// Test output vars
		//echo " (UID=$userIdme----ZIP=$up_get_mainpic_check) ";
		
	// Run the global checks then display message accordingly 
		if(empty($up_get_firstname_check)){
			$check_message_output = "Please add your First Name to your profile.  <a href='${site_url_link}editprofilemain/'>Click Here to Edit Profile</a>.";
		}
		else if(empty($up_get_location_check)){
			$check_message_output =  "Please add your Location to your profile.  <a href='${site_url_link}editprofilemain/'>Click Here to Edit Profile</a>.";
		}
		else if(empty($up_get_sex_check)){
			$check_message_output = "Please add your Sex to your profile.  <a href='${site_url_link}editprofilemain/'>Click Here to Edit Profile</a>.";
		}
		else if(empty($up_get_mainpic_check) || $up_get_mainpic_check == 'noimg.gif'){
			$check_message_output = "Please upload your photo to your profile.  <Br><a href='${site_url_link}editprofilemain/picsubmit/'>Click Here to Upload Profile Photo</a>.";
		}
		else{
			// Do Nothing
			$check_message_output = "";
		}
		
	// Check to see if a message is being displayed
	// If Yes then show formatted message
	if(!empty($check_message_output)){
		echo " <table width=100% cellspacing=0 class=index_headertable3tbl><tr><td class=index_headertable3><center> ";
		echo " <br> ";
		echo " $check_message_output ";
		echo " <br><br> ";
		echo " </center></td></tr></table><br> ";
	}
		

// End of Login check
}
		
?>