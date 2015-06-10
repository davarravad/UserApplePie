<?php

	// Check to see if user's IP is already registered in database
	// Blocks user from registration if there is an IP match
	function check_reg_ip_inuse(){
		/////////////////////////
		//Check to see if ip address already exist
		$ipchecker = $_SERVER['REMOTE_ADDR'];	
		//echo "$ipchecker";

		$ipqueryec = "SELECT * FROM `".$db_table_prefix."userprofile` WHERE `userIP`='$ipchecker' ";
		$ipresultec = mysqli_query($GLOBALS["___mysqli_ston"], $ipqueryec);
		$iprowsec = mysqli_num_rows($ipresultec); 
		
		//echo " - $iprowsec ";

		if($iprowsec < 2){
			$ipok = TRUE;
			///echo "OK Go";
		}else{
			$ipok = FALSE;
			///echo "No Go";
		}
						
		//End ip check
		///////////////////////////
		if($ipok == TRUE){
			// IP is not in user database
			// Allow user to continue
			return 1;
		}else{
			// IP is already in user database
			// Block user from registering
			return 0;
			err_message('Sorry, Your IP address has been used before! We can not allow you to register for this website. Contact Administrator for more info.  admin(at)cartruckclubs.com');
		}
	}
		
				
?>