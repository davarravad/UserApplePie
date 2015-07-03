<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

require_once("models/config.inc");
// Build Security for Current Page if Any
$cur_page_get = "pages/".$_GET['page'].".inc";
if (!securePage($cur_page_get)){die();}

//Forms posted
if(!empty($_POST))
{
	$cfgId = array();
	$newSettings = $_POST['settings'];
	
	//Validate new site name
	if ($newSettings[1] != $websiteName) {
		$newWebsiteName = $newSettings[1];
		if(minMaxRange(1,150,$newWebsiteName))
		{
			$errors[] = lang("CONFIG_NAME_CHAR_LIMIT",array(1,150));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 1;
			$cfgValue[1] = $newWebsiteName;
			$websiteName = $newWebsiteName;
		}
	}
	
	//Validate new URL
	if ($newSettings[2] != $websiteUrl) {
		$newWebsiteUrl = $newSettings[2];
		if(minMaxRange(1,150,$newWebsiteUrl))
		{
			$errors[] = lang("CONFIG_URL_CHAR_LIMIT",array(1,150));
		}
		else if (substr($newWebsiteUrl, -1) != "/"){
			$errors[] = lang("CONFIG_INVALID_URL_END");
		}
		else if (filter_var($newWebsiteUrl, FILTER_VALIDATE_URL) === FALSE){
			$errors[] = lang("CONFIG_INVALID_URL_START");
		}
		else if (count($errors) == 0) {
			$cfgId[] = 2;
			$cfgValue[2] = $newWebsiteUrl;
			$websiteUrl = $newWebsiteUrl;
		}
	}
	
	//Validate site_url_link_m
	if ($newSettings[3] != $site_url_link_m) {
		$new_site_url_link_m = $newSettings[3];
		if(minMaxRange(1,255,$new_site_url_link_m))
		{
			$errors[] = lang("CONFIG_URL_M_CHAR_LIMIT",array(1,150));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 3;
			$cfgValue[3] = $new_site_url_link_m;
			$site_url_link_m = $new_site_url_link_m;
		}
	}
	
	//Validate site_dir
	if ($newSettings[4] != $site_dir) {
		$new_site_dir = $newSettings[4];
		if(minMaxRange(1,255,$new_site_dir))
		{
			$errors[] = lang("CONFIG_SITE_DIR_CHAR_LIMIT",array(1,150));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 4;
			$cfgValue[4] = $new_site_dir;
			$site_dir = $new_site_dir;
		}
	}
	
	//Validate site_folder_dir
	if ($newSettings[5] != $site_folder_dir) {
		$new_site_folder_dir = $newSettings[5];
		if(minMaxRange(1,255,$new_site_folder_dir))
		{
			$errors[] = lang("CONFIG_FOLDER_DIR_CHAR_LIMIT",array(1,150));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 5;
			$cfgValue[5] = $new_site_folder_dir;
			$site_folder_dir = $new_site_folder_dir;
		}
	}
	
	//Validate site_debug
	if ($newSettings[6] != $site_debug) {
		$new_site_debug = $newSettings[6];
		if(minMaxRange(1,255,$new_site_debug))
		{
			$errors[] = lang("CONFIG_DEBUG_CHAR_LIMIT",array(1,150));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 6;
			$cfgValue[6] = $new_site_debug;
			$site_debug = $new_site_debug;
		}
	}
	
	//Validate site_gbl_descript
	if ($newSettings[7] != $site_gbl_descript) {
		$new_site_gbl_descript = $newSettings[7];
		if(minMaxRange(1,255,$new_site_gbl_descript))
		{
			$errors[] = lang("CONFIG_DESCRIPT_CHAR_LIMIT",array(1,255));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 7;
			$cfgValue[7] = $new_site_gbl_descript;
			$site_gbl_descript = $new_site_gbl_descript;
		}
	}

	//Validate site_gbl_keywords
	if ($newSettings[8] != $site_gbl_keywords) {
		$new_site_gbl_keywords = $newSettings[8];
		if(minMaxRange(1,255,$new_site_gbl_keywords))
		{
			$errors[] = lang("CONFIG_KEYWORDS_CHAR_LIMIT",array(1,255));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 8;
			$cfgValue[8] = $new_site_gbl_keywords;
			$site_gbl_keywords = $new_site_gbl_keywords;
		}
	}
	
	//Validate new site email address
	if ($newSettings[9] != $emailAddress) {
		$newEmail = $newSettings[9];
		if(minMaxRange(1,150,$newEmail))
		{
			$errors[] = lang("CONFIG_EMAIL_CHAR_LIMIT",array(1,150));
		}
		elseif(!isValidEmail($newEmail))
		{
			$errors[] = lang("CONFIG_EMAIL_INVALID");
		}
		else if (count($errors) == 0) {
			$cfgId[] = 9;
			$cfgValue[9] = $newEmail;
			$emailAddress = $newEmail;
		}
	}
	
	//Validate new email activation resend threshold
	if ($newSettings[10] != $resend_activation_threshold) {
		$newResend_activation_threshold = $newSettings[10];
		if($newResend_activation_threshold > 72 OR $newResend_activation_threshold < 0)
		{
			$errors[] = lang("CONFIG_ACTIVATION_RESEND_RANGE",array(0,72));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 10;
			$cfgValue[10] = $newResend_activation_threshold;
			$resend_activation_threshold = $newResend_activation_threshold;
		}
	}
	
	//Validate new language selection
	if ($newSettings[11] != $language) {
		$newLanguage = $newSettings[11];
		if(minMaxRange(1,150,$language))
		{
			$errors[] = lang("CONFIG_LANGUAGE_CHAR_LIMIT",array(1,150));
		}
		elseif (!file_exists($newLanguage)) {
			$errors[] = lang("CONFIG_LANGUAGE_INVALID",array($newLanguage));				
		}
		else if (count($errors) == 0) {
			$cfgId[] = 11;
			$cfgValue[11] = $newLanguage;
			$language = $newLanguage;
		}
	}
	
	//Validate email activation selection
	if ($newSettings[12] != $emailActivation) {
		$newActivation = $newSettings[12];
		if($newActivation != "true" AND $newActivation != "false")
		{
			$errors[] = lang("CONFIG_ACTIVATION_TRUE_FALSE");
		}
		else if (count($errors) == 0) {
			$cfgId[] = 12;
			$cfgValue[12] = $newActivation;
			$emailActivation = $newActivation;
		}
	}
	
	//Validate new template selection
	if ($newSettings[13] != $template) {
		$newTemplate = $newSettings[13];
		if(minMaxRange(1,150,$template))
		{
			$errors[] = lang("CONFIG_TEMPLATE_CHAR_LIMIT",array(1,150));
		}
		elseif (!file_exists($newTemplate)) {
			$errors[] = lang("CONFIG_TEMPLATE_INVALID",array($newTemplate));				
		}
		else if (count($errors) == 0) {
			$cfgId[] = 13;
			$cfgValue[13] = $newTemplate;
			$template = $newTemplate;
		}
	}
	
	//Validate recap_sitekey
	if ($newSettings[14] != $recap_sitekey) {
		$new_recap_sitekey = $newSettings[14];
		if(minMaxRange(1,255,$new_recap_sitekey))
		{
			$errors[] = lang("CONFIG_RECAP_SITEKEY_CHAR_LIMIT",array(1,150));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 14;
			$cfgValue[14] = $new_recap_sitekey;
			$recap_sitekey = $new_recap_sitekey;
		}
	}
	
	//Validate recap_secretkey
	if ($newSettings[15] != $recap_secretkey) {
		$new_recap_secretkey = $newSettings[15];
		if(minMaxRange(1,255,$new_recap_secretkey))
		{
			$errors[] = lang("CONFIG_RECAP_SECRETKEY_CHAR_LIMIT",array(1,150));
		}
		else if (count($errors) == 0) {
			$cfgId[] = 15;
			$cfgValue[15] = $new_recap_secretkey;
			$recap_secretkey = $new_recap_secretkey;
		}
	}
	
	//Validate site_adds_top
	if ($newSettings[16] != $site_adds_top) {
		$new_site_adds_top = $newSettings[16];
		if (count($errors) == 0) {
			$cfgId[] = 16;
			$cfgValue[16] = $new_site_adds_top;
			$site_adds_top = $new_site_adds_top;
		}
	}
	
	//Validate site_adds_bot
	if ($newSettings[17] != $site_adds_bot) {
		$new_site_adds_bot = $newSettings[17];
		if (count($errors) == 0) {
			$cfgId[] = 17;
			$cfgValue[17] = $new_site_adds_bot;
			$site_adds_bot = $new_site_adds_bot;
		}
	}
	
	//Update configuration table with new settings
	if (count($errors) == 0 AND count($cfgId) > 0) {
		updateConfig($cfgId, $cfgValue);
		$successes[] = lang("CONFIG_UPDATE_SUCCESSFUL");
	}
}

$languages = getLanguageFiles(); //Retrieve list of language files
$templates = getTemplateFiles(); //Retrieve list of template files
$permissionData = fetchAllPermissions(); //Retrieve list of all permission levels
echo "
<div id='main'>";

echo resultBlock($errors,$successes);

echo "
<div id='regbox'>
<form name='adminConfiguration' action='".$site_url_link."YummyAsPie/admin_configuration/' method='post'>
<table><tr>
	<td>
		<label>Website Name:</label>
	</td><td>
		<input size='60' maxlength='150' type='text' name='settings[".$settings['website_name']['id']."]' value='".$websiteName."' />
	</td>
</tr><tr>
	<td>
		<label>Website URL:</label>
	</td><td>
		<input size='60' maxlength='150' type='text' name='settings[".$settings['website_url']['id']."]' value='".$websiteUrl."' />
	</td>
</tr><tr>
	<td>
		<label>Website Mobile URL:</label>
	</td><td>
		<input size='60' maxlength='150' type='text' name='settings[".$settings['site_url_link_m']['id']."]' value='".$site_url_link_m."' />
	</td>
</tr><tr>
	<td>
		<label>Website Main Directory:</label>
	</td><td>
		<input size='60' maxlength='150' type='text' name='settings[".$settings['site_dir']['id']."]' value='".$site_dir."' />
	</td>
</tr><tr>
	<td>
		<label>Website Folder Directory:</label>
	</td><td>
		<input size='60' maxlength='150' type='text' name='settings[".$settings['site_folder_dir']['id']."]' value='".$site_folder_dir."' />
	</td>
</tr><tr>
	<td>
		<label>Website Debug TRUE/FALSE:</label>
	</td><td>
		<select name='settings[".$settings['site_debug']['id']."]'>
			<option value='TRUE' "; 
				if($site_debug == 'TRUE'){ echo "SELECTED"; } 
			echo ">TRUE</option>
			<option value='FALSE' ";
				if($site_debug == 'FALSE'){ echo "SELECTED"; }
			echo ">FALSE</option>
		</select>	
	</td>
</tr><tr>
	<td>
		<label>Website Description:</label>
	</td><td>
		<textarea rows='4' cols='45' type='text' maxlength='255' name='settings[".$settings['site_gbl_descript']['id']."]'>".$site_gbl_descript."</textarea>
	</td>
</tr><tr>
	<td>
		<label>Website Keywords:</label>
	</td><td>
		<textarea rows='4' cols='45' type='text' maxlength='255' name='settings[".$settings['site_gbl_keywords']['id']."]'>".$site_gbl_keywords."</textarea>
	</td>
</tr><tr>
	<td>
		<label>Site Email:</label>
	</td><td>
		<input size='60' maxlength='255' type='text' name='settings[".$settings['email']['id']."]' value='".$emailAddress."' />
	</td>
</tr><tr>
	<td>
		<label>Activation Threshold:</label>
	</td><td>
		<input size='2' maxlength='1' type='text' name='settings[".$settings['resend_activation_threshold']['id']."]' value='".$resend_activation_threshold."' />
	</td>
</tr><tr>
	<td>
		<label>Language:</label>
	</td><td>
		<select name='settings[".$settings['language']['id']."]'>
";
	
//Display language options
foreach ($languages as $optLang){
	if ($optLang == $language){
		echo "<option value='".$optLang."' selected>$optLang</option>";
	}
	else {
		echo "<option value='".$optLang."'>$optLang</option>";
	}
}

echo "
</select>

	</td>
</tr><tr>
	<td>

<label>Email Activation:</label>
</td><td>
<select name='settings[".$settings['activation']['id']."]'>";

//Display email activation options
if ($emailActivation == "true"){
	echo "
	<option value='true' selected>True</option>
	<option value='false'>False</option>
	</select>";
}
else {
	echo "
	<option value='true'>True</option>
	<option value='false' selected>False</option>
	</select>";
}

echo "
	</td>
</tr><tr>
	<td>
<label>Template:</label>
</td><td>
<select name='settings[".$settings['template']['id']."]'>";

//Display template options
foreach ($templates as $temp){
	if ($temp == $template){
		echo "<option value='".$temp."' selected>$temp</option>";
	}
	else {
		echo "<option value='".$temp."'>$temp</option>";
	}
}

echo "
</select>
	</td>
</tr>
<tr><td colspan=2>
<hr>
<strong>Google reCAPTCHA Settings</strong> - <a href='https://www.google.com/recaptcha/' target='_blank'>Google reCAPTCHA</a>
</td></tr>
<tr>
	<td>
		<label>Site Key:</label>
	</td><td>
		<input size='60' maxlength='255' type='text' name='settings[".$settings['recap_sitekey']['id']."]' value='".$recap_sitekey."' />
	</td>
</tr>
<tr>
	<td>
		<label>Secret Key:</label>
	</td><td>
		<input size='60' maxlength='255' type='text' name='settings[".$settings['recap_secretkey']['id']."]' value='".$recap_secretkey."' />
	</td>
</tr>
<tr><td colspan=2>
<hr>
<strong>Advertisement Codes</strong>
</td></tr>
<tr>
	<td>
		<label>Advertisement at top of site:</label>
	</td><td>
		<textarea rows='4' cols='45' type='text' name='settings[".$settings['site_adds_top']['id']."]'>".$site_adds_top."</textarea>
	</td>
</tr>
<tr>
	<td>
		<label>Advertisement at bottom of site:</label>
	</td><td>
		<textarea rows='4' cols='45' type='text' name='settings[".$settings['site_adds_bot']['id']."]'>".$site_adds_bot."</textarea>
	</td>
</tr>
<tr>
	<td colspan=2>
<hr>
<input type='submit' name='Submit' value='Update Site Settings' />
</td></tr>
</table>
</form>
</div>
</div>
<div id='bottom'></div>
</div>
";

?>
