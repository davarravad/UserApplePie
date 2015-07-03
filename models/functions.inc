<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//include debug_settings file
require "models/debug_settings.inc";
	
//Get current page's url for redirect back
$cur_pageURL = (@$_SERVER["HTTPS"] == "on") ? "https://" : "http://";
$cur_pageURL .= $_SERVER["SERVER_NAME"].$_SERVER["REQUEST_URI"];

// If site debug mode is off then...
// Check to see if ip has had multi errors and if they are currently blocked
if($debug_website == 'FALSE'){
	//Run error checker blocker thingy
	require_once "models/error_ip_check_block.inc";
}

if(isset($userId)){
$userIdme = "$userId";
}

date_default_timezone_set('America/Chicago');

// Add user to loggedusers table in database for is online status
function add_user_logged_in_online($aulio_uid){
		global $mysqli,$db_table_prefix; 
	$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."loggedusers (
		userId
		)
		VALUES (
		?
		)");
	$stmt->bind_param("i", $aulio_uid);
	$result = $stmt->execute();
	$stmt->close();	
	return $result;
}

// Update user access time in loggedusers table in database for is online status
function add_user_logged_in_access($aulio_uid){
		global $mysqli,$db_table_prefix; 
	
	$mysql_date_now = date("Y-m-d H:i:s");	
	
	$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."loggedusers SET
		lastAccess = ?
		WHERE
		userId=? ");
	$stmt->bind_param("si", $mysql_date_now, $aulio_uid);
	$result = $stmt->execute();
	$stmt->close();	
	return $result;
}
// Run the above function to update user last access time if logged in
if(isUserLoggedIn()) { $aulio_uid = $userIdme; add_user_logged_in_access($aulio_uid); }else{}

// Delete when logged out loggedusers table in database for is online status
function add_user_logged_in_logout($aulio_uid){
		global $mysqli,$db_table_prefix; 
	
	$stmt = $mysqli->prepare("DELETE FROM ".$db_table_prefix."loggedusers
		WHERE
		userId=? ");
	$stmt->bind_param("i", $aulio_uid);
	$result = $stmt->execute();
	$stmt->close();	
	return $result;
}

// Clean up loggedusers table from users that have not been active for over an hour
// Just in case a user does not use logout button.
function clean_logged_users(){
		global $mysqli,$db_table_prefix; 
	
	$stmt = $mysqli->prepare("DELETE FROM ".$db_table_prefix."loggedusers
		WHERE
		unix_timestamp(date_add(lastAccess, interval 1 hour)) < unix_timestamp(now()) ");
	$result = $stmt->execute();
	$stmt->close();	
	return $result;
}
// Run clean logged users function
clean_logged_users();


// Message to display if user is not logged in and trying to access a member only page
function notlogedinmsg(){

	global $site_url_link;

	echo "<center>";
	echo "<table width=90%><tr><td class=epboxb align=center><h3>Members Only!</h3>";
	echo "";
	echo "This page is for Members Only! <Br> Already a member? (<a href='${site_url_link}login/'>Login!</a>) <br> Not a member? (<a href='${site_url_link}Register/'>Register!</a>)";
	echo "</td></tr></table></center><br><br>";

}
function escape($values) {
	if(is_array($values)) {
		$values = array_map('escape', $values);
	} else {
		/* Quote if not integer */
		if ( !is_numeric($values) || $values{0} == '0' ) {
			$values = ((isset($GLOBALS["___mysqli_ston"]) && is_object($GLOBALS["___mysqli_ston"])) ? mysqli_real_escape_string($GLOBALS["___mysqli_ston"], $values) : ((trigger_error("[MySQLConverterToo] Fix the mysql_escape_string() call! This code does not work.", E_USER_ERROR)) ? "" : ""));
		}
	}
	return $values;
}
function ALB($value) {
	$value = htmlspecialchars($value);
	$value = strip_tags($value);
	$value = addslashes($value);
	$value = nl2br($value);
//	$value = str_replace("\\n", "<br />", $value);
//	$value = str_replace("\\r", "", $value);
	
	return $value;
}



//Settings for Tables for PC and Mobile

	if(isset($usemobile)){}else{ $usemobile = 'FALSE'; } 
	//display
	
	if($usemobile == "TRUE"){ $imgw = "35px"; }else{ $imgw = "100px"; }
	if($usemobile == "TRUE"){ $imgwA = "35px"; }else{ $imgwA = "59px"; }
	
	if($usemobile == "TRUE"){ $tblwimg = "100%"; }else{ $tblwimg = "500px"; }
	if($usemobile == "TRUE"){ $tblwimg2 = "100%"; }else{ $tblwimg2 = "56px"; }
	if($usemobile == "TRUE"){ $tblw = "100%"; }else{ $tblw = "100%"; }
	if($usemobile == "TRUE"){ $tblw3 = "35px"; }else{ $tblw3 = "100px"; }

	//commentnew
	if($usemobile == "TRUE"){ $taw = "30px"; }else{ $taw = "50px"; }
	if($usemobile == "TRUE"){ $taw2 = "20px"; }else{ $taw2 = "40px"; }

	//statdisplay
	if($usemobile == "TRUE"){ $tblw2 = "100%"; }else{ $tblw2 = "100%"; }
	if($usemobile == "TRUE"){ $tblw4 = "35px"; }else{ $tblw4 = "100%"; }

	//statcommentnew
	if($usemobile == "TRUE"){ $tbw = "30px"; }else{ $tbw = "50px"; }


	//width sizes
	if($usemobile == "TRUE"){ $tblw300 = "100%"; }else{ $tblw300 = "100%"; }
	if($usemobile == "TRUE"){ $tblw500 = "100%"; }else{ $tblw500 = "100%"; }
	if($usemobile == "TRUE"){ $tblw600 = "100%"; }else{ $tblw600 = "100%"; }




	//START - Token valid function check
	function is_valid_token()
	{
	
		//Token Script by David (DaVaR) Sargent
		//davarravad@gmail.com
		//This script enables tokens within forms on a web site
		//I designed it to create a large random code
		//To use tokens withn in the form include this page
		//Then tell the script which part of the code goes where
		
		//The submition page
		//Use on pages where information is added to a database

		//Top of Submit Pages	

		//Unset the token just in case another one is on same page
		//unset($ses_taz_token_num);
		
		if(isset($_POST['session_token_num'])){
			$pos_taz_token_num = $_POST['session_token_num'];
			if(isset($_SESSION['user_token'][$pos_taz_token_num]['FT'])){
				$ses_taz_token_num = $_SESSION['user_token'][$pos_taz_token_num]['FT']; 
				global $debug_website;
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; 
					echo $_SESSION['user_token'][$pos_taz_token_num]['FT'];
					echo " - $pos_taz_token_num - $ses_taz_token_num - <br>";
				}
			}
		}else{

			if(isset($_SESSION['user_token'][0]['FT'])){
				$ses_taz_token = $_SESSION['user_token'][0]['FT'];
			}else{
				$ses_taz_token = "NoSesToken";
			}
		
			$pos_taz_token_num = "NoSesTokenNUM";
		}

		if(isset($_POST['user_token'])){
			$pos_taz_token = $_POST['user_token'];
		}else{
			$pos_taz_token = "NoPosToken";
		}

		//Setup site validation and stuff
		//Make sure user is only using this website
		
		//Get the site url setting from config file
		global $site_url;
		
		//Get the site url from server
		$site_url_server = (@$_SERVER["HTTPS"] == "on") ? "https://" : "http://";
		$site_url_server .= $_SERVER['SERVER_NAME'];
		$site_url_server .= "/";
		
		//Send the site url to session
		if(isset($_SESSION['site_url'])){ $site_url_SES = $_SESSION['site_url']; }else{ $site_url_SES = ""; }
		if(isset($_SESSION['site_url_server'])){ $site_url_server_SES = $_SESSION['site_url_server']; }else{ $site_url_server_SES = ""; }		

		
		//Ends the token session for better security	
 		unset($_SESSION['user_token']);
 		unset($_SESSION['site_url']);
 		unset($_SESSION['site_url_server']);
	
		//TESTING Echo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
		if(!isset($ses_taz_token)){ $ses_taz_token = "NoSesTazToken"; }if(!isset($ses_taz_token_num)){ $ses_taz_token_num = "NoSesTazTokenNum"; }
		global $debug_website;
		if($debug_website == 'TRUE'){ 
			echo "<br> - DEBUG SITE ON - <BR>"; 
			echo "<Br><font color=purple size=0.1><br> - Ses: $ses_taz_token <br> Pos: $pos_taz_token <br> Num: $pos_taz_token_num <br> SesNum: $ses_taz_token_num - </font><br>";	
		}
		
		if(($ses_taz_token == $pos_taz_token || $ses_taz_token_num == $pos_taz_token) && ($site_url == $site_url_SES && $site_url_server == $site_url_server_SES) && ($site_url_SES == $site_url_server_SES)) {
			return 1;
		}else{
			return 0;
		}
	
	}
	//END - Token valid function check

	//START - Token form function <form>
	
	//Creats a random string of chars.
	function genRandomString() {
		$length = 15;
		$characters = '0123456789abcdefghijklmnopqrstuvwxyz';
		$maxrnd = strlen($characters)-1;
		$string = str_repeat('0', $length);
		for ($p = $length; $p--;) {
			$string[$p] = $characters[mt_rand(0, $maxrnd)];
		}
		return $string;
	}
	//Creats a random string of chars.
	function genRandomString2() {
		$length = 15;
		$characters = '0123456789abcdefghijklmnopqrstuvwxyz';
		$maxrnd = strlen($characters)-1;
		$string = str_repeat('0', $length);
		for ($p = $length; $p--;) {
			$string[$p] = $characters[mt_rand(0, $maxrnd)];
		}
		return $string;
	}
	
	//Setup session form_token for array
				if(!isset($_SESSION['user_token'])){
					$_SESSION['user_token'] = array();
				}
	
	
	//Token form token function
	function form_token()
	{

		//The form page
		//use with your submition form pages

		//Top of Form Pages	

		//setting the token for this submition

			//Create md5 string for even more security
			$token_md5 = md5(uniqid(rand(), true));
		
			// create unique token
			$form_token = uniqid();
	 
				//making token extra better.
			
				srand ((double) microtime( )*1000000);
				$random_number = rand( );

				$ran_tk = genRandomString2();
				$ranimgname = genRandomString();
				
				//Sets generated randoms strings together	
				$ran_extoken = $ranimgname.$random_number;
				$form_token = $ran_tk.$form_token.$ran_extoken.$token_md5;
	 
			// commit token to session
			//$_SESSION['user_token'] = $form_token;

			global $session_token_num;
	
			if(isset($session_token_num)){
					//echo "Session: $session_token_num";
				$_SESSION['user_token'][$session_token_num] = array('FT' => $form_token);
					//echo $_SESSION['user_token'][$session_token_num]['FT'];
				echo "<input type=\"hidden\" name=\"session_token_num\" value=\"$session_token_num\" />";
					global $debug_website;
					if($debug_website == 'TRUE'){ 
						echo "<br> ($session_token_num) ";
					}
				unset($session_token_num);
			}else{
				$_SESSION['user_token'][0] = array('FT' => $form_token);
				$session_token_num = "";				
			}

			//Setup site validation and stuff
			//Make sure user is only using this website
			
			//Get the site url setting from config file
			global $site_url;
			
			//Get the site url from server
			$site_url_server = (@$_SERVER["HTTPS"] == "on") ? "https://" : "http://";
			$site_url_server .= $_SERVER['SERVER_NAME'];
			$site_url_server .= "/";
			
			//Send the site url to session
			$_SESSION['site_url'] = $site_url;
			$_SESSION['site_url_server'] = $site_url_server;
			
			//TESTING Echo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			global $debug_website;
			if($debug_website == 'TRUE'){ 
				echo " - DEBUG SITE ON - ";
				echo " $site_url - $site_url_server ";
				echo "<font color=purple size=0.1> - $form_token - </font><br>";  //testing
			}
				
		echo "<input type=\"hidden\" name=\"user_token\" value=\"$form_token\" />";	

		//End of Token Process
	}
	//END - Token form function


//Shows success msg function
//Checks to see if user successfully submited something
	
function success_message(){
	if(isset($_SESSION['success_msg'])){
		$success_msg = $_SESSION['success_msg'];
		echo "<table width=100% cellspacing=0 class=index_headertable3tbl><tr><td class=index_headertable3><center><strong><font color=green>$success_msg</font></strong></center></td></tr></table><br>";
		unset($_SESSION['success_msg']);
	}
}



function new_user_message_send($username, $inserted_id){
	global $websiteUrl, $websiteName, $mysqli, $db_table_prefix;
	
	//Testing stuff
	//echo "Sending message to $username!";
	
	//Message Subject
	$msubject = "Welcome to ".$websiteName."!";
	
	//Message Content
	// Get data from database for admin welcome message
	$mcontent = "Welcome to the site!  Enjoy!";
	
	$msubject = htmlspecialchars($msubject);	
	$mcontent = htmlspecialchars($mcontent);
	$msubject = addslashes($msubject);
	$mcontent = addslashes($mcontent);
	
	//Sets current date
	$mdatesent = date("YmdHis");
	
	//Submits welcome msg to users inbox
	$query = "INSERT INTO `".$db_table_prefix."inbox` SET `mto` = '$username', `mfrom` = 'DaVaR', `msubject` = '$msubject', `mcontent` = '$mcontent', `mdatesent`='$mdatesent' ";
	
	//Runs query
	$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );
	
	// print out the results
	if( $results )
	{
		//Testing stuff to show it worked
		//echo "<br> msg sent <br>";
	}

	
}



//Image extension check function
function check_img_ext(){
	global $ext;
	
	if($ext == 'JPEG'||$ext == 'JPG'||$ext == 'GIF'||$ext == 'TIF'||$ext == 'PNG'||$ext == 'jpeg'||$ext == 'jpg'||$ext == 'gif'||$ext == 'tif'||$ext == 'png'){
		//File is correct extension OK to upload
		return 1;
	}else{
		return 0;
	}

}


function check_multi_logins(){

	global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;

	//Check to see if user is blocked

	//Get users information
	$user_ip_check = $_SERVER['REMOTE_ADDR'];
	
	//Get the time for 10 min ago
	$ten_minutes_ago = time() - (60 * 10);
	$datetime = date("Y-m-d H:i:s", $ten_minutes_ago);
		
	// Login Attempts Count
	//Get the total number of attempts to login within the past 10 min
	$queryA = "SELECT ".$db_table_prefix."a_attempts.attempts FROM `".$db_table_prefix."a_attempts` WHERE `attempts_ip`='$user_ip_check'  AND timestamp >= '$datetime' ORDER BY `".$db_table_prefix."a_attempts`.`attempts_id` DESC LIMIT 1";
	// Get information from database
	$result = $mysqli->query($queryA);
	$arr_logcheck = $result->fetch_all(MYSQLI_BOTH);
	foreach($arr_logcheck as $row_logcheck)
	{
		$attempts = $row_logcheck['attempts'];

		//echo "TTL ATT: $attempts ";
		$total_att = $attempts;
	}
	if(empty($total_att)){ $total_att = '0'; }
	//echo "<hr>$total_att<hr>";
	
	//If user has tried to login more than 4 times within the past 10 min
	//Block them from the login form and show a error message
	if($total_att >= "4"){
		return 0;
	}else{
		return 1;
	}	
	
}



// Gets user_name or display_name from $ID02
// Set to echo
function get_user_name($ID02){

	global $mysqli,$db_table_prefix;
	
	$stmt = $mysqli->prepare("SELECT 
		user_name, display_name
		FROM ".$db_table_prefix."users WHERE id=?");

	$stmt->bind_param("i", $ID02);
	$stmt->execute();

	$stmt->bind_result($print_user_name, $print_user_display_name);
	
	$stmt->fetch();
	$stmt->close();
	
	// Displays users user_name if display_name is not set
	if(!empty($print_user_display_name)){
		echo $print_user_display_name;
	}else{
		echo $print_user_name;
	}
	unset($print_user_display_name, $print_user_name);
}

// Gets user_name or display_name from $ID02
// Set to send to var
function get_user_name_2($ID02){

	global $mysqli,$db_table_prefix;
	
	$stmt = $mysqli->prepare("SELECT 
		user_name, display_name
		FROM ".$db_table_prefix."users WHERE id=?");

	$stmt->bind_param("i", $ID02);
	$stmt->execute();

	$stmt->bind_result($print_user_name, $print_user_display_name);
	
	$stmt->fetch();
	$stmt->close();
	
	// Displays users user_name if display_name is not set
	if(!empty($print_user_display_name)){
		return $print_user_display_name;
	}else{
		return $print_user_name;
	}
	unset($print_user_display_name, $print_user_name);
}

// Gets user_name or display_name from $ID02
// Set to send to var
function get_user_email($ID02){

	global $mysqli,$db_table_prefix;
	
	$stmt = $mysqli->prepare("SELECT 
		email
		FROM ".$db_table_prefix."users WHERE id=?");

	$stmt->bind_param("i", $ID02);
	$stmt->execute();

	$stmt->bind_result($print_user_email);
	
	$stmt->fetch();
	$stmt->close();
	
	// Displays users user_name if display_name is not set
	if(!empty($print_user_email)){
		return $print_user_email;
	}
	unset($print_user_email);
}


//Cleans up com_content and shortens it 
//Then displays read more link
function read_more_com_content($com_content, $com_content_link){
	//Shortens the post for better looks
	//Then displays link at end to view full comment
	$com_content = stripslashes($com_content);
	$com_content = str_replace(";","&59;","$com_content");
	$vm_link = " ...[<a href='$com_content_link'>Read_More</a>] ";
	$com_content = strlen($com_content) > 100 ? substr($com_content, 0, 100) . "$vm_link" : $com_content;
	unset($vm_link);
	echo "$com_content";
}


// Check to see if user is admin
function is_admin(){
	//If user is not logged in, deny access
	if(isUserLoggedIn()){
		global $mysqli,$db_table_prefix,$master_account,$userIdme;
		$u_id_check = "$userIdme";
		//echo "(($u_id_check))";
		$check = "2";
		//Grant access if master user
		
		$stmt = $mysqli->prepare("SELECT id 
			FROM ".$db_table_prefix."user_permission_matches
			WHERE user_id = ?
			AND permission_id = ?
			LIMIT 1
			");
		$access = 0;
		
			if ($access == 0){
				$stmt->bind_param("ii", $u_id_check, $check);
				$stmt->execute();
				$stmt->store_result();
				if ($stmt->num_rows > 0){
					$access = 1;
				}
			}
		// Test stuff
		// echo "($userIdme)($access)($master_account)";
		
		
		if ($access == 1)
		{
			return true;
		}
		else
		{
			return false;	
		}
		$stmt->close();
	}else{
		return false;
	}

}



/**
 * check the referer to minimize abuse..
 * todo: a more vigourous check.
 */
function is_valid_referer()
{ 
	global $site_url;
	 return (strstr($_SERVER['HTTP_REFERER'],$site_url));
}


/**
 * shows a formatted error message
 */
global $websiteName;
//Setup the header of err_message
$err_m_head = "<table border='0' width='100%' align='center' cellspacing='0' cellpadding='0'>
				<tr><td class='hr2'>
					$websiteName Error Message
				</td></tr><tr><td class='content78'>
					<font color='#990000'><strong>";

//Setup the footer of err_message
$err_m_foot = "</strong></font>
				</td></tr>
				</table><br>";

function err_message($str)
{
	global $err_m_head, $err_m_foot;
	echo "$err_m_head $str $err_m_foot";
}



// Setup user profile if none exist
// Run script when user logs in

function check_create_user_profile($userIdme){
	// Test make sure we are getting correct userId
	//echo "<font color=red><b> ($userIdme) </b></font>";
	
	// Get global info
	global $mysqli,$db_table_prefix;
	
	// Check to see user already has a profile
	$query_pc = $mysqli->prepare("SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$userIdme' LIMIT 1");
	$query_pc->execute();
	$query_pc->store_result();

	$rows_pc = $query_pc->num_rows;

	// Test show how many rows exist
	//echo $rows_pc;
	
	if($rows_pc == "0"){
		// No User Profile - Creating one
		//echo "Create User Profile";
		$query_pc2 = $mysqli->prepare("INSERT INTO ".$db_table_prefix."userprofile(userId) VALUES (?)");
		$query_pc2->bind_param("i", $userIdme);
		$query_pc2->execute();
		header('Location: /');
		exit;
	}else{
		// Do nothing
		//echo "User Profile Exist";
	}
}


// Function for displaying pages within a page
function display_pages_in_pages($dir, $page, $default, $load_cat, $load_id){

		// Setup page stuff
		$pee = $page;
		$pee1 = "pages/${dir}/";
		$pee2 = ".inc";
		$pee_file = "${pee1}${pee}${pee2}";
		
		if(!empty($pee)){
			
			if(!empty($pee)){
				if(file_exists($pee_file)) {
					require "$pee_file";
				} else {
					echo "
						<center>
						The page <font color=red>$pee</font> does NOT exist!<br>
						<br>
						Go back or go <a href='../'>Home</a></center>
					";
					
					//Reporting page error
					$er_type = "Edit Profile Main Page Error";
					$er_location = "?pee=$pee";
					$er_msg = "?pee= error - page $taz does not exist";
					$er = "YESError";
				}
			} else {
				echo "<br><center>Please select one of the above links corresponding to what you would like to do.</center><br>";
			}
		
		} else {
			$pee_file_2 = "${pee1}${default}${pee2}";
			require "$pee_file_2";
		}

}


// Function to display total number of sweets without buttons
// ex=(sweet_id, sweet_sec_id, sweet_sub, sweet_location)
function total_topic_sweets($sweet_id, $sweet_sec_id, $sweet_sub, $sweet_location){

	global $mysqli, $site_url_link, $site_forum_title;

	// Test to make sure everything is extracted
	//echo "($sweet_id, $sweet_sec_id, $sweet_sub, $sweet_location)";

	if($sweet_sec_id != NULL){
		// Get number of rows from database
		$query_s = "
			SELECT * 
			FROM sweet
			WHERE `sweet_id`='$sweet_id'
			AND `sweet_sec_id`='$sweet_sec_id'
			AND `sweet_sub`='$sweet_sub'
			AND `sweet_location`='$sweet_location'
		";
	}else{
		// Get number of rows from database
		$query_s = "
			SELECT * 
			FROM sweet 
			WHERE `sweet_id`='$sweet_id'
			AND `sweet_sub`='$sweet_sub'
			AND `sweet_location`='$sweet_location'
		";
	}
	
	if ($result = $mysqli->query("$query_s")) {

		/* determine number of rows result set */
		$row_cnt = $result->num_rows;

		// Display total number of sweets
		printf(" Sweets:  %d \n", $row_cnt );

		/* close result set */
		$result->close();
	}else{
		echo " Sweets: 0 ";
	}
}


// Function to display total number of views
function total_topic_views($view_id, $view_sec_id, $view_sub, $view_location){

	global $mysqli, $site_url_link, $site_forum_title, $userIdme;

	// Display and update view count for topic
	//Start View
	$addview = "";  //Enables adding views to post
	$view_location = "$view_location"; //Location on site where sweet is
	$view_id = "$view_id";  //Post Id number
	$view_userid = $_SERVER['REMOTE_ADDR'];  //User's Id
	$view_url = "${site_url_link}${site_forum_title}/display_topic/${view_id}/";
	$view_owner_userid = "$userIdme";  //Post owners userid
	require "models/views.inc";
	//End View 
	
}

// Login Error Attempt Handler
function login_attm_hand(){

	//Now check to see if user has tried to login and failed more than 3 times.
	//If user has failed more than 3 times block them for 15 min and show error message.
	
	global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;
	
	//Get users information
	$user_ip_check = $_SERVER['REMOTE_ADDR'];
	
	//echo "<br><br> Test: $user_ip_check";
	
	//Check to see if user is blocked

	//Get the time for 10 min ago
	$ten_minutes_ago = time() - (60 * 10);
	$datetime = date("Y-m-d H:i:s", $ten_minutes_ago);
	

	//Get the total number of attempts to login within the past 10 min
	$queryA = "SELECT ".$db_table_prefix."a_attempts.attempts FROM `".$db_table_prefix."a_attempts` WHERE `attempts_ip`='$user_ip_check'  AND timestamp >= '$datetime' ORDER BY `".$db_table_prefix."a_attempts`.`attempts_id` DESC LIMIT 1";
	// Get information from database
	$result = $mysqli->query($queryA);
	$arr_logcheck = $result->fetch_all(MYSQLI_BOTH);
	foreach($arr_logcheck as $row_logcheck)
	{
		$attempts = $row_logcheck['attempts'];

		//echo "TTL ATT: $attempts ";
		$total_att = $attempts;
	}
	if(empty($attempts)){ $total_att = '0'; }
	
	//If user has tried to login more than 4 times within the past 10 min
	//Block them from the login form and show a error message
	if($total_att >= "4"){
		//User is blocked for multi logins
		err_message('Sorry, Your have been temporarily blocked for multiple login fails.  Please try again later.
						<br><br>If you just registered for the site, check your email for the activation link.');
		die;
	}else{
		if($total_att >= "1"){
			//If current attempts then add one to row
			//Update attempt to database
			$query = "UPDATE `".$db_table_prefix."a_attempts` SET attempts=attempts+1  WHERE `attempts_ip`='$user_ip_check'  AND timestamp >= '$datetime' ORDER BY `".$db_table_prefix."a_attempts`.`attempts_id` DESC LIMIT 1";
			$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );
			// print out the results
			if( $results ){
				//echo "<br> IP ($user_ip_check) +1 Logged! <br>";
			}	
		}else{
			//If no current attempts then create one
			//Add attempt to database
			$query = "INSERT INTO `".$db_table_prefix."a_attempts` SET `attempts_ip`='$user_ip_check', `attempts`='1' ";
			$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );
			// print out the results
			if( $results ){
				//echo "<br> IP ($user_ip_check) Logged! <br>";
			}	
		}
	}	

}



// Function to check to see if user is logging in and needed to be redirected
// Collects the location user is at if they are not logged in
// Does not do anything if logged in or starting on login page

//Check if user is NOT logged in
if(!isUserLoggedIn()){
	//Check if user is on login or home page
	if(isset($_GET['page'])){ $current_user_page = $_GET['page']; }else{ $current_user_page = "index"; }
	
	//Ignore Index and Login pages
	//Default to home page if page before login is not any of the following pages.
	if($current_user_page == "index" || $current_user_page == "Login" || $current_user_page == "login" || $current_user_page == "register" || $current_user_page == "Register" || $current_user_page == "forgot_password" || $current_user_page == "resend_activation"){
		// Do nothing
	}else{
		// Add page to session
		//echo " $current_user_page ";
		$_SESSION['login_prev_page'] = $_SERVER['REQUEST_URI'];
	}
}


//Added Functions that allow admins to activate or deactivate users based on user id
// Admin - Change a user from inactive to active

function setUserActiveStatus($id)
{
	global $mysqli,$db_table_prefix;
	$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."users
		SET active = 1
		WHERE
		id = ?
		LIMIT 1");
	$stmt->bind_param("i", $id);
	$result = $stmt->execute();
	$stmt->close();	
	return $result;
}

function setUserInactiveStatus($id)
{
	global $mysqli,$db_table_prefix;
	$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."users
		SET active = 0
		WHERE
		id = ?
		LIMIT 1");
	$stmt->bind_param("i", $id);
	$result = $stmt->execute();
	$stmt->close();	
	return $result;
}

?>