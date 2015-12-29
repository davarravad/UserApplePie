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


require_once("./external/db-settings.php"); //Require DB connection

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
$mail_templates_dir = "external/mail-templates/";
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
$enable_photos = $settings['enable_photos']['value'];

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
	$language = "external/languages/en.php";
}

if(!isset($language)) $language = "external/languages/en.php";

//Pages to require
require_once($language);
require_once("./external/class.mail.php");
require_once("./external/class.user.php");
require_once("./external/class.newuser.php");
require_once("./external/funcs.php");

session_start();

//Global User Object Var
//loggedInUser can be used globally if constructed
if(isset($_SESSION["userCakeUser"]) && is_object($_SESSION["userCakeUser"]))
{
	$loggedInUser = $_SESSION["userCakeUser"];
}

// Build Security for Current Page if Any
if(isset($_GET['page'])){
	$cur_page_get = "pages/".$_GET['page'].".php";
	if (!securePage($cur_page_get)){die();}
}

?>
