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


// Checks to see if username is already in the database
// Also checks to make sure user name is valid
// Used with the AJAX username check in register

if(isSet($_POST['username']))
{
		$username = $_POST['username'];

		require_once "../db-settings.php";

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
				//echo "<div class='alert alert-danger' role='alert'>User Name can only include alpha-numeric characters. No symbols. No spaces.</div>";
				//echo "<i class='glyphicon glyphicon-remove'></i>";
				echo "CHAR";
			}else{
				//echo "<div class='alert alert-success' role='alert'>Available!</div>";
				//echo "<i class='glyphicon glyphicon-ok'></i>";
				echo "OK";
			}
		}
		else
		{
			//echo "<div class='alert alert-danger' role='alert'>The User Name <strong>".$username."</strong> is already in use.</div>";
			//echo "<i class='glyphicon glyphicon-remove'></i>";
			echo "INUSE";
		}

		unset($username, $ttl_un_rows);
}


?>