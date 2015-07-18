<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

require_once("models/db-settings.inc"); //Require DB connection

//Retrieve settings
$stmt = $mysqli->prepare("SELECT id, name, value
	FROM ".$db_table_prefix."configuration");	
$stmt->execute();
$stmt->bind_result($id, $name, $value);

while ($stmt->fetch()){
	$settings[$name] = array('id' => $id, 'name' => $name, 'value' => $value);
}
$stmt->close();

//Set Settings
$emailActivation = $settings['activation']['value'];
$mail_templates_dir = "models/mail-templates/";
$websiteName = $settings['website_name']['value'];
$websiteUrl = $settings['website_url']['value'];
$emailAddress = $settings['email']['value'];
$resend_activation_threshold = $settings['resend_activation_threshold']['value'];
$emailDate = date('dmy');
$language = $settings['language']['value'];
$template = $settings['template']['value'];
$site_gbl_descript = $settings['site_gbl_descript']['value'];
$site_gbl_keywords = $settings['site_gbl_keywords']['value'];
$site_url_link_m = $settings['site_url_link_m']['value'];
$recap_sitekey = $settings['recap_sitekey']['value'];
$recap_secretkey = $settings['recap_secretkey']['value'];
$site_adds_top = $settings['site_adds_top']['value'];
$site_adds_bot = $settings['site_adds_bot']['value'];
$site_style_sel = $settings['template']['value'];

$site_url_link = $websiteUrl;

// Check for mobile request for site_url
if(!empty($usemobile)){
	if($usemobile == "TRUE"){
		$site_url = $site_url_link_m;
		unset($site_url_link);
		$site_url_link = $site_url_link_m;
		$site_gbl_link_m = $site_url_link;
	}else{
		$site_url = $websiteUrl;
	}
}else{
	$site_url = $websiteUrl;
}
	
$site_dir = $settings['site_dir']['value'];
$site_folder_dir = $settings['site_folder_dir']['value'];
$site_debug = $settings['site_debug']['value'];

$master_account = -1;

$default_hooks = array("#WEBSITENAME#","#WEBSITEURL#","#DATE#");
$default_replace = array($websiteName,$websiteUrl,$emailDate);

if (!file_exists($language)) {
	$language = "models/languages/en.php";
}

if(!isset($language)) $language = "models/languages/en.php";

//Pages to require
require_once($language);
require_once("models/class.mail.inc");
require_once("models/class.user.inc");
require_once("models/class.newuser.inc");
require_once("models/funcs.inc");

session_start();

//Global User Object Var
//loggedInUser can be used globally if constructed
if(isset($_SESSION["userCakeUser"]) && is_object($_SESSION["userCakeUser"]))
{
	$loggedInUser = $_SESSION["userCakeUser"];
}

?>
