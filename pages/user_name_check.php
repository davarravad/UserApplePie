<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Checks to see if username is already in the database
// Also checks to make sure user name is valid
// Used with the AJAX username check in register

if(isSet($_POST['username']))
{
		$username = $_POST['username'];

		require_once "../models/db-settings.inc";

			$stmt = $mysqli->prepare("SELECT * FROM `".$db_table_prefix."users` WHERE user_name=? ");
			$stmt->bind_param("s", $username);
			$stmt->execute();
			$stmt->store_result();
		
			/* determine number of rows result set */
			$ttl_un_rows = $stmt->num_rows;

			/* close result set */
			$stmt->close();
		
		if($ttl_un_rows == "0")
		{
			// Check input to be sure it meets the site standards for usernames
			if(!preg_match("/^[a-zA-Z\p{Cyrillic}0-9]+$/u", $username)){
				echo '<font color="red">User Name can only include alpha-numeric characters. No symbols. No spaces.</font>';
			}else{
				echo 'OK';
			}
		}
		else
		{
			echo '<font color="red">The User Name <strong>'.$username.'</strong> is already in use.</font>';
		}

		unset($username, $ttl_un_rows);
}


?>