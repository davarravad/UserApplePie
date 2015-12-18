<?php
//////////////////////////////////
// UserApplePie Version: 1.1.1  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Security Feature to Disallow File to be opened directly.
// Only allows this file to be include by index.php
if(!defined('Page_Protection')){header("Location: ../");exit();}


// Get user profile information from database based on id
	function get_up_info($get_info_id, $field){

		// echo "Getting user info ($get_info_id-$field)";

		// Get info from userprofile
			
		global $mysqli,$db_table_prefix;
		
		$stmt = $mysqli->prepare("SELECT 
			".$field."
			FROM ".$db_table_prefix."userprofile WHERE userId=? LIMIT 1");

		$stmt->bind_param("i", $get_info_id);
		$stmt->execute();

		$stmt->bind_result($val);
		
		$stmt->fetch();
		$stmt->close();
		
		// Clean up the data
		$val = stripslashes($val);
		
		return "$val";
		unset($val);

	}

	// Get user sign up stamp from database based on id
	function get_up_info_usr_signup2($get_info_id){

		// echo "Getting user info ($get_info_id)";

		// Get info from users
			
		global $mysqli,$db_table_prefix;
		
		$stmt = $mysqli->prepare("SELECT sign_up_stamp FROM ".$db_table_prefix."users WHERE id=? LIMIT 1");

		$stmt->bind_param("i", $get_info_id);
		$stmt->execute();

		$stmt->bind_result($val);
		
		$stmt->fetch();
		$stmt->close();

		// Format Time stamp to date time stamp thingy
		$val = date("M d, Y", $val);
		
		return "$val";

		unset($val);
		
	}

	
	// Get user sign up stamp from database based on id
	function get_up_info_usr_lastlogin($get_info_id){

		// echo "Getting user info ($get_info_id)";

		// Get info from users
			
		global $mysqli,$db_table_prefix;
		
		$stmt = $mysqli->prepare("SELECT last_sign_in_stamp FROM ".$db_table_prefix."users WHERE id=? LIMIT 1");

		$stmt->bind_param("i", $get_info_id);
		$stmt->execute();

		$stmt->bind_result($val);
		
		$stmt->fetch();
		$stmt->close();

		// Format Time stamp to date time stamp thingy
		$val = date("Y-m-d H:i:s", $val);
		
		return "$val";
		
		unset($val);
		
	}
	
	// Get users status from database based on id
	function get_up_info_mem_status($get_info_id){
	
		// echo "Getting user info ($get_info_id)";

		// Get info from users
			
		global $mysqli,$db_table_prefix;
		
		$userPermission = fetchUserPermissions($get_info_id);
		$permissionData = fetchAllPermissions();
		
		//List of permission levels user is apart of
		foreach ($permissionData as $v1) {
			if(isset($userPermission[$v1['id']])){
				echo " <font style='";
					if(isset($v1['color'])){ echo "color:".$v1['color'].";"; }
					if($v1['weight'] == "TRUE"){ echo "font-weight:bold"; }
				echo "'>";
				echo $v1['name'];
				echo "</font><br>";
			}
		}
		
		//return "$val";
		
		//unset($val);
	
	}
	

	// Get users password from database based on id
	function get_up_info_mem_password($get_info_id){
	
		// echo "Getting user info ($get_info_id)";

		// Get info from users
			
		global $mysqli,$db_table_prefix;
		
		$stmt = $mysqli->prepare("SELECT password FROM ".$db_table_prefix."users WHERE id=? LIMIT 1");

		$stmt->bind_param("i", $get_info_id);
		$stmt->execute();

		$stmt->bind_result($val);
		
		$stmt->fetch();
		$stmt->close();
		
		return "$val";
		
		unset($val);
	
	}
	
	// Get users display name from database based on id
	function get_up_info_mem_disp_name($get_info_id){
	
		// echo "Getting user info ($get_info_id)";

		// Get info from users
			
		global $mysqli,$db_table_prefix;
		
		$stmt = $mysqli->prepare("SELECT display_name FROM ".$db_table_prefix."users WHERE id=? LIMIT 1");

		$stmt->bind_param("i", $get_info_id);
		$stmt->execute();

		$stmt->bind_result($val);
		
		$stmt->fetch();
		$stmt->close();
		
		// Clean up the data
		$val = stripslashes($val);
		
		return "$val";
		
		unset($val);
	
	}
	
	// Shows account settings links
	function account_settings_links(){
		global $websiteUrl;
		// DisplayName, Password, and Email update page
		echo "<a href='${websiteUrl}editprofilemain/account_displayname/' name='Update Display Name'>Update Display Name</a> <hr> ";
		echo "<a href='${websiteUrl}editprofilemain/account/' name='Update Pass/Email'>Update Password/Email</a> | ";
		echo "<a href='${websiteUrl}editprofilemain/account_email/' name='Privacy and Email Settings'>Privacy and Email Settings</a><br>";
		echo "<a href='${websiteUrl}editprofilemain/adds/'>Advertisement Settings</a>";
		echo "<hr>";
	}
	
	// Get's current user's name if logged in, otherwise marks them as visitor
	if(isset($loggedInUser->displayname) && isset($loggedInUser->user_id)){		
		$nname = $loggedInUser->displayname;
		$idofuser = $loggedInUser->user_id;	
	}else{
		$nname = "Visitor";
		$idofuser = "0";
	}

	if(isset($nname)){
		$nname = "$nname";
		$qthing = "nickname = '$nname'";
	}else{
		$nname = "";
	}
	
	
?>