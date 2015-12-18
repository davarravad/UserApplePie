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




//Completely sanitizes text
function sanitize($str)
{
	return strtolower(strip_tags(trim(($str))));
}

// Function that creates the admin user
function uap_create_admin_user($email,$username,$displayname,$password){

	global $mysqli,$emailActivation,$websiteUrl,$db_table_prefix;

	//Sanitize
	$clean_email = sanitize($email);
	$clean_password = trim($password);
	$username = sanitize($username);
	$activation_token = "ADFADHH584651";
	$user_active = "1";
			
	//Construct a secure hash for the plain text password
	$secure_pass = password_hash("$clean_password", PASSWORD_DEFAULT);
				
	//Get the user's IP
	$user_ip = $_SERVER['REMOTE_ADDR'];
				
	//echo "$username, $displayname, $secure_pass, $clean_email, $activation_token, $user_active, $user_ip";
				
	//Insert the user into the database providing no errors have been found.
	$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."users (
		user_name,
		display_name,
		password,
		email,
		activation_token,
		last_activation_request,
		lost_password_request, 
		active,
		title,
		userIP,
		sign_up_stamp,
		last_sign_in_stamp
		)
		VALUES (
		?,
		?,
		?,
		?,
		?,
		'".time()."',
		'0',
		?,
		'Administrator',
		?,
		'".time()."',
		'0'
		)");

	// Create user profile
	$stmt->bind_param("sssssis", $username, $displayname, $secure_pass, $clean_email, $activation_token, $user_active, $user_ip);
	$stmt->execute();
	$inserted_id = $mysqli->insert_id;
	echo $stmt->error;
	$stmt->close();

	//Insert user id to userprofile table
	$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."userprofile  (
		userId
		)
		VALUES (
		?
		)");
	$stmt->bind_param("s", $inserted_id);
	$stmt->execute();
	echo $stmt->error;
	$stmt->close();
	
	echo "Admin User Added to Users Database.....<br>";
	
}				

?>