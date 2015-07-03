<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//This function checks to see if user's IP has created multi errors
//If user has reached the max number of errors they will be blocked
//And unable to view any and all content within the site
//User will not be able to get anything from sql either
//HoooHah!  My attempt to block users from hacking

function check_multi_errors(){

	global $mysqli, $site_url_link, $db_table_prefix;

	//Check to see if user is blocked

	//Get users information
	$user_ip_check = $_SERVER['REMOTE_ADDR'];
	
	//Set the ammount of time user is blocked
	//Get the time for 1 hour ago if set at 60
	$check_back_min = "120";  //Sets how many min back to check
	$minutes_ago = time() - (60 * $check_back_min);  //sets the time user is blocked
	$datetime = date("Y-m-d H:i:s", $minutes_ago);
	
	//Get the total number of attempts to login within the past 10 min
	$query_err = "SELECT er.* FROM `".$db_table_prefix."errors` `er` WHERE `er`.`er_ipaddy`='$user_ip_check'  AND `er`.`er_date` >= '$datetime' ORDER BY `er`.`er_id` DESC LIMIT 30";

	// Get row count from database
	if ($result = $mysqli->query("$query_err")) {

		/* determine number of rows result set */
		$row_cnt = $result->num_rows;

		/* close result set */
		$result->close();
	}
	
	$total_user_err = $row_cnt;
	
	//Test Display
	//echo " Total_Err($total_user_err)-User_IP($user_ip_check)-Back_Date($datetime)-Back_Min($check_back_min) ";
	
	if(empty($total_user_err)){ $total_user_err = '0'; }
	
	//If user has tried to login more than 4 times within the past 10 min
	//Block them from the login form and show a error message
	if($total_user_err >= '5'){
		return 0;
	}else{
		return 1;
	}	
	
}


//Run the function and kill user access

			//Token validation function
			if(!check_multi_errors()){ 

				//User is blocked for multi logins
				echo "<font color=red><h1>";
				echo('Sorry, Your have been temporarily blocked for multiple site errors. 
								<br><br>Contact us on our Facebook page for more information.');
				echo "</h1></font><br><br>";
				echo "<a href='https://www.facebook.com/tazibcustoms'>www.facebook.com/tazibcustoms</a>";
				((is_null($___mysqli_res = mysqli_close($GLOBALS["___mysqli_ston"]))) ? false : $___mysqli_res);
				die;

			}

?>
