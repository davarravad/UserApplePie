<?php
//////////////////////////////////
// UserApplePie Version: 1.1.1  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Security Feature to Disallow File to be opened directly.
// Sets this page as the main file that is allowed
// to include protected files
define('Page_Protection', TRUE);

// Checks to see if displayname is already in the database
// Also checks to make sure user name is valid
// Used with the AJAX displayname check in register


if(isSet($_POST['displayname']) || isSet($_POST['user_displayname_update']))
{
		if(isSet($_POST['displayname'])){
			$displayname = $_POST['displayname'];
		}
		if(isSet($_POST['user_displayname_update'])){
			$displayname = $_POST['user_displayname_update'];
		}
		require_once "../db-settings.php";
		
		if(isSet($_POST['userIdme']))
		{
			$userIdme = $_POST['userIdme'];
			require_once "../members/funcs_user_info.php";

			$user_displayname = get_up_info_mem_disp_name($userIdme);
			//echo '<strong>U_IDM='.$userIdme.' - U_DN='.$user_displayname.'</strong><Br>';		
		}else{
			$user_displayname = "Visitor";
		}
		
			$stmt = $mysqli->prepare("SELECT * FROM `".$db_table_prefix."users` WHERE display_name=? ");
			$stmt->bind_param("s", $displayname);
			$stmt->execute();
			$stmt->store_result();
		
			/* determine number of rows result set */
			$ttl_un_rows = $stmt->num_rows;

			/* close result set */
			$stmt->close();
		
		if($ttl_un_rows == "0")
		{
			// Check input to be sure it meets the site standards for displaynames
			if(!preg_match("/^[a-zA-Z\p{Cyrillic}0-9\s\-\_]+$/u", $displayname)){
				echo 'CHAR';
			}else{
				echo 'OK';
			}
		}
		else
		{
			//Check to see if user is logged in and trying to update their username. 
			//If username is already the same as what they have set then tell them so.

			if($displayname == $user_displayname)
			{
				echo 'SAME';
			}else{
				echo 'INUSE';
			}
		}

		unset($displayname, $ttl_un_rows);
}


?>