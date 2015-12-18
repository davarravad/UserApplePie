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

// Checks to see if email is already in the database
// Also checks to make sure user name is valid
// Used with the AJAX email check in register

if(isSet($_POST['email']))
{
		$email = $_POST['email'];

		require_once "../db-settings.php";

			$stmt = $mysqli->prepare("SELECT * FROM `".$db_table_prefix."users` WHERE email=? ");
			$stmt->bind_param("s", $email);
			$stmt->execute();
			$stmt->store_result();
		
			/* determine number of rows result set */
			$ttl_un_rows = $stmt->num_rows;

			/* close result set */
			$stmt->close();
		
		if($ttl_un_rows == "0")
		{
			// Check input to be sure it meets the site standards for emails
			if(filter_var($email, FILTER_VALIDATE_EMAIL)) {
				echo "OK";
			}else{
				echo "BAD";
			}
		}
		else
		{
			echo "INUSE";
		}

		unset($email, $ttl_un_rows);
}


?>