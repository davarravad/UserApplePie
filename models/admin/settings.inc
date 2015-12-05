<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){

//Forms posted
	//Check to see if admin is updating site settings
	//If yes then send the update
	if(isset($_POST['site_settings_update'])){ 
		$site_settings_update = $_POST['site_settings_update'];
	}else{
		$site_settings_update = "FALSE";
	}
	if($site_settings_update == "TRUE"){
	//Check to see is site is demo site.  If so disable editing.
	if($cur_server_name_dc != $demo_server_name_dc){
		// get the variables from the URL request string
		$site_dir_settings = $_REQUEST['site_dir_settings'];
		$site_gbl_descript_settings = $_REQUEST['site_gbl_descript'];
		$site_gbl_keywords_settings = $_REQUEST['site_gbl_keywords'];
		$site_gbl_email_settings = $_REQUEST['site_gbl_email'];

		//Clean up $site_gbl_descript_settings
		$site_gbl_descript_settings = htmlspecialchars($site_gbl_descript_settings);
		$site_gbl_descript_settings = strip_tags($site_gbl_descript_settings);	
		$site_gbl_descript_settings = addslashes($site_gbl_descript_settings);
		$site_gbl_descript_settings = nl2br($site_gbl_descript_settings);
		
		//Clean up $site_gbl_keywords_settings
		$site_gbl_keywords_settings = htmlspecialchars($site_gbl_keywords_settings);
		$site_gbl_keywords_settings = strip_tags($site_gbl_keywords_settings);	
		$site_gbl_keywords_settings = addslashes($site_gbl_keywords_settings);
		$site_gbl_keywords_settings = nl2br($site_gbl_keywords_settings);
		
		$query = "UPDATE `site_settings` SET `site_gbl_email`='$site_gbl_email_settings',`site_gbl_keywords`='$site_gbl_keywords_settings',`site_gbl_descript`='$site_gbl_descript_settings'  WHERE `site_dir`='$site_dir_settings' ";

		$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

		// print out the results
		if( $results )
		{
			echo( "$websiteName Submit<br><br>" );
			echo( "Successfully updated the site settings.<br><br>" );
		}
		else
		{
			die( "Trouble saving information to the database: " . ((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_error($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_error()) ? $___mysqli_res : false)) );
		}
	}
	}else{
		//Not submitting an update so show form
		echo "<hr><strong>Web Site Settings for Search Engines. Google, Bing, Yahoo, ets...</strong><br><br>";

		// retrieve the row from the database
		$query_SS = "SELECT * FROM `site_settings` ";
	   
		$result_SS = mysqli_query($GLOBALS["___mysqli_ston"],  $query_SS );

		// print out the results
		if( $result_SS && $contact_SS = mysqli_fetch_object( $result_SS ) )
		{
			// print out the info
			$site_dir_settings = $contact_SS -> site_dir;
			$site_gbl_email_settings = $contact_SS -> site_gbl_email;
			$site_gbl_descript_settings = $contact_SS -> site_gbl_descript;
			$site_gbl_keywords_settings = $contact_SS -> site_gbl_keywords;
		}
		
		if(!isset($site_dir_settings)){ $site_dir_settings = ""; }
		if(!isset($site_gbl_email_settings)){ $site_gbl_email_settings = ""; }
	 	if(!isset($site_gbl_descript_settings)){ $site_gbl_descript_settings = ""; }
		if(!isset($site_gbl_keywords_settings)){ $site_gbl_keywords_settings = ""; }
		
		$site_gbl_descript_settings = stripslashes($site_gbl_descript_settings);
		$site_gbl_descript_settings = stripslashes($site_gbl_descript_settings);
		$site_gbl_descript_settings = stripslashes($site_gbl_descript_settings);
		$site_gbl_descript_settings = str_replace("<br />", "", $site_gbl_descript_settings );
		
		$site_gbl_keywords_settings = stripslashes($site_gbl_keywords_settings);
		$site_gbl_keywords_settings = stripslashes($site_gbl_keywords_settings);
		$site_gbl_keywords_settings = stripslashes($site_gbl_keywords_settings);
		$site_gbl_keywords_settings = str_replace("<br />", "", $site_gbl_keywords_settings );

		echo "
				
		<form method=\"post\" action=\"${site_url_link}YummyAsPie/settings/ \">
		
		<input type='hidden' name='site_settings_update' value='TRUE'>
		<input type='hidden' name='site_dir_settings' value='$site_dir_settings'>
		
		<label>Site Description:</label><br><textarea name=\"site_gbl_descript\" cols=\"50\" rows=\"10\">$site_gbl_descript_settings</textarea><br>
		
		<label>Site keywords:</label><br><textarea name=\"site_gbl_keywords\" cols=\"50\" rows=\"10\">$site_gbl_keywords_settings</textarea><br>
		
		<label>Site From Email Address:</label><Br>
		<input name=\"site_gbl_email\" type=\"text\" size=\"50\" maxlength=\"255\" value=\"$site_gbl_email_settings\"><br>
		
		<Br><Br>
		<label title=\"Update Site Settings\"><input type=\"submit\" value=\"Update Site Settings\" /></label>
		</form>

		";
	}	
		
		
}//End admin check   
?>


