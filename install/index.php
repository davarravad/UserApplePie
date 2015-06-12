<?php 
/*
UserApple Pie Version: 0.0.1
http://www.thedavar.net
UserCake Version: 2.0.2
http://usercake.com
*/
require_once("../models/db-settings.inc");

// Current Version
$uap_ver = "v0.0.1";

echo "
<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>
<html xmlns='http://www.w3.org/1999/xhtml'>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />
<title>UserApplePie $uap_ver Installer</title>
<style type='text/css'>
body {
	font-family: Verdana, Geneva, sans-serif;
	font-size: 12px;
	background-color: #C1DDFF;
}
hr {
	color: #069;
	border-bottom-width: 1px;
	border-bottom-style: solid;
	border-bottom-color: #0CF;
	margin: 4px;
	width: 100%;
}
h1 {
	margin: 2px;
	 text-shadow: 1px 1px #0074E8;
}
h2 {
	margin: 2px;	
}
#content {
	font-family: Verdana, Geneva, sans-serif;
	font-size: 12px;
	color: #003333;
}
</style>
<script src='../models/funcs.js' type='text/javascript'>
</script>
</head>
<body>
<div id='top'><div id='logo'></div></div>
<div id='content'>
<h1>UserApplePie $uap_ver</h1>
<hr>
<h2>Installer</h2>
<hr>";	

// Get Data from form request
if(isset($_POST['pass_requirements'])){ $pass_requirements = $_POST['pass_requirements']; }else{ $pass_requirements = "FALSE"; }
if(isset($_POST['install'])){ $install = $_POST['install']; }else{ $install = "FALSE"; }


if($install == "TRUE")
{
	$db_issue = false;
	
	$permissions_sql = "
	CREATE TABLE IF NOT EXISTS `".$db_table_prefix."permissions` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(150) NOT NULL,
	PRIMARY KEY (`id`)
	) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;
	";
	
	$permissions_entry = "
	INSERT INTO `".$db_table_prefix."permissions` (`id`, `name`) VALUES
	(1, 'New Member'),
	(2, 'Administrator');
	";
	
	$users_sql = "
	CREATE TABLE IF NOT EXISTS `".$db_table_prefix."users` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`user_name` varchar(50) NOT NULL,
	`display_name` varchar(50) NOT NULL,
	`password` varchar(225) NOT NULL,
	`email` varchar(150) NOT NULL,
	`activation_token` varchar(225) NOT NULL,
	`last_activation_request` int(11) NOT NULL,
	`lost_password_request` tinyint(1) NOT NULL,
	`active` tinyint(1) NOT NULL,
	`title` varchar(150) NOT NULL,
	`sign_up_stamp` int(11) NOT NULL,
	`last_sign_in_stamp` int(11) NOT NULL,
	PRIMARY KEY (`id`)
	) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
	";
	
	$user_permission_matches_sql = "
	CREATE TABLE IF NOT EXISTS `".$db_table_prefix."user_permission_matches` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`user_id` int(11) NOT NULL,
	`permission_id` int(11) NOT NULL,
	PRIMARY KEY (`id`)
	) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;
	";
	
	$user_permission_matches_entry = "
	INSERT INTO `".$db_table_prefix."user_permission_matches` (`id`, `user_id`, `permission_id`) VALUES
	(1, 1, 2);
	";
	
	$configuration_sql = "
	CREATE TABLE IF NOT EXISTS `".$db_table_prefix."configuration` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(150) NOT NULL,
	`value` varchar(150) NOT NULL,
	PRIMARY KEY (`id`)
	) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;
	";
	
	$configuration_entry = "
	INSERT INTO `".$db_table_prefix."configuration` (`id`, `name`, `value`) VALUES
	(1, 'website_name', 'UserCake'),
	(2, 'website_url', 'localhost/'),
	(3, 'email', 'noreply@ILoveUserCake.com'),
	(4, 'activation', 'false'),
	(5, 'resend_activation_threshold', '0'),
	(6, 'language', 'models/languages/en.php'),
	(7, 'template', 'models/site-templates/default.css'),
	(8, 'remember_me_length', '1wk');
	";
	
	$pages_sql = "CREATE TABLE IF NOT EXISTS `".$db_table_prefix."pages` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`page` varchar(150) NOT NULL,
	`private` tinyint(1) NOT NULL DEFAULT '0',
	PRIMARY KEY (`id`)
	) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=18 ;
	";
	
	$pages_entry = "INSERT INTO `".$db_table_prefix."pages` (`id`, `page`, `private`) VALUES
	(1, 'account.php', 1),
	(2, 'activate-account.php', 0),
	(3, 'admin_configuration.php', 1),
	(4, 'admin_page.php', 1),
	(5, 'admin_pages.php', 1),
	(6, 'admin_permission.php', 1),
	(7, 'admin_permissions.php', 1),
	(8, 'admin_user.php', 1),
	(9, 'admin_users.php', 1),
	(10, 'forgot-password.php', 0),
	(11, 'index.php', 0),
	(12, 'left-nav.php', 0),
	(13, 'login.php', 0),
	(14, 'logout.php', 1),
	(15, 'register.php', 0),
	(16, 'resend-activation.php', 0),
	(17, 'user_settings.php', 1);
	";
	
	$permission_page_matches_sql = "CREATE TABLE IF NOT EXISTS `".$db_table_prefix."permission_page_matches` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`permission_id` int(11) NOT NULL,
	`page_id` int(11) NOT NULL,
	PRIMARY KEY (`id`)
	) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=23 ;
	";
	
	$permission_page_matches_entry = "INSERT INTO `".$db_table_prefix."permission_page_matches` (`id`, `permission_id`, `page_id`) VALUES
	(1, 1, 1),
	(2, 1, 14),
	(3, 1, 17),
	(4, 2, 1),
	(5, 2, 3),
	(6, 2, 4),
	(7, 2, 5),
	(8, 2, 6),
	(9, 2, 7),
	(10, 2, 8),
	(11, 2, 9),
	(12, 2, 14),
	(13, 2, 17);
	";

	$sessions_sql = "CREATE TABLE IF NOT EXISTS `".$db_table_prefix."sessions (
	`sessionStart` int(11) NOT NULL,
	`sessionData` text NOT NULL,
	`sessionID` varchar(255) NOT NULL,
	PRIMARY KEY (`sessionID`)
	) ENGINE=MyISAM DEFAULT CHARSET=latin1;
	";
	
	$stmt = $mysqli->prepare($configuration_sql);
	if($stmt->execute())
	{
		$cfg_result = "<p>".$db_table_prefix."configuration table created.....</p>";
	}
	else
	{
		$cfg_result = "<p>Error constructing ".$db_table_prefix."configuration table.</p>";
		$db_issue = true;
	}
	
	echo $cfg_result;
	$stmt = $mysqli->prepare($configuration_entry);
	if($stmt->execute())
	{
		echo "<p>Inserted basic config settings into ".$db_table_prefix."configuration table.....</p>";
	}
	else
	{
		echo "<p>Error inserting config settings access.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($permissions_sql);
	if($stmt->execute())
	{
		echo "<p>".$db_table_prefix."permissions table created.....</p>";
	}
	else
	{
		echo "<p>Error constructing ".$db_table_prefix."permissions table.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($permissions_entry);
	if($stmt->execute())
	{
		echo "<p>Inserted 'New Member' and 'Admin' groups into ".$db_table_prefix."permissions table.....</p>";
	}
	else
	{
		echo "<p>Error inserting permissions.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($user_permission_matches_sql);
	if($stmt->execute())
	{
		echo "<p>".$db_table_prefix."user_permission_matches table created.....</p>";
	}
	else
	{
		echo "<p>Error constructing ".$db_table_prefix."user_permission_matches table.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($user_permission_matches_entry);
	if($stmt->execute())
	{
		echo "<p>Added 'Admin' entry for first user in ".$db_table_prefix."user_permission_matches table.....</p>";
	}
	else
	{
		echo "<p>Error inserting admin into ".$db_table_prefix."user_permission_matches.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($pages_sql);
	if($stmt->execute())
	{
		echo "<p>".$db_table_prefix."pages table created.....</p>";
	}
	else
	{
		echo "<p>Error constructing ".$db_table_prefix."pages table.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($pages_entry);
	if($stmt->execute())
	{
		echo "<p>Added default pages to ".$db_table_prefix."pages table.....</p>";
	}
	else
	{
		echo "<p>Error inserting pages into ".$db_table_prefix."pages.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($permission_page_matches_sql);
	if($stmt->execute())
	{
		echo "<p>".$db_table_prefix."permission_page_matches table created.....</p>";
	}
	else
	{
		echo "<p>Error constructing ".$db_table_prefix."permission_page_matches table.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($permission_page_matches_entry);
	if($stmt->execute())
	{
		echo "<p>Added default access to ".$db_table_prefix."permission_page_matches table.....</p>";
	}
	else
	{
		echo "<p>Error adding default access to ".$db_table_prefix."user_permission_matches.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($users_sql);
	if($stmt->execute())
	{
		echo "<p>".$db_table_prefix."users table created.....</p>";
	}
	else
	{
		echo "<p>Error constructing users table.</p>";
		$db_issue = true;
	}
	
	$stmt = $mysqli->prepare($sessions_sql);
	if($stmt->execute())
	{
		echo "<p>".$db_table_prefix."sessions table created.....</p>";
	}
	else
	{
		echo "<p>Error constructing ".$db_table_prefix."sessions table.....</p>";
		$db_issue = true;
	}
	
	if(!$db_issue){
		echo "<p><strong>Database setup complete, please delete the install folder.</strong></p>";
	} else {
		echo "<p><a href=\"?install=true\">Try again</a></p>";
	}
}
else if($pass_requirements == 'TRUE')
{
	echo "
		<strong>Update the following information to match your server settings.  Make sure you replace the default text or your website may have issues.</strong><hr>
		<form name='adminConfiguration' action='' method='post'>
		<table width=100%><tr>
			<td>
				<label>Website Name:</label>
			</td><td>
				<input size='60' maxlength='150' type='text' name='website_name' value='UserApplePie' />
			</td>
		</tr><tr>
			<td>
				<label>Website URL:</label>
			</td><td>
				<input size='60' maxlength='150' type='text' name='website_url' value='http://www.website.com' />
			</td>
		</tr><tr>
			<td>
				<label>Website Mobile URL:</label>
			</td><td>
				<input size='60' maxlength='150' type='text' name='site_url_link_m' value='http://m.website.com' />
			</td>
		</tr><tr>
			<td>
				<label>Website Main Directory:</label>
			</td><td>
				<input size='60' maxlength='150' type='text' name='site_dir' value='websitefolder' />
			</td>
		</tr><tr>
			<td>
				<label>Website Folder Directory:</label>
			</td><td>
				<input size='60' maxlength='150' type='text' name='site_folder_dir' value='/var/www/html/' />
			</td>
		</tr><tr>
			<td>
				<label>Website Description:</label>
			</td><td>
				<textarea rows='4' cols='45' type='text' maxlength='255' name='site_gbl_descript'>My Website and Stuff</textarea>
			</td>
		</tr><tr>
			<td>
				<label>Website Keywords:</label>
			</td><td>
				<textarea rows='4' cols='45' type='text' maxlength='255' name='site_gbl_keywords'>UserApplePie, UserCake</textarea>
			</td>
		</tr><tr>
			<td>
				<label>Site Email:</label>
			</td><td>
				<input size='60' maxlength='255' type='text' name='email' value='admin@website.com' />
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
				<input size='60' maxlength='255' type='text' name='recap_sitekey' value='Get Site Key From Google' />
			</td>
		</tr>
		<tr>
			<td>
				<label>Secret Key:</label>
			</td><td>
				<input size='60' maxlength='255' type='text' name='recap_secretkey' value='Get Secret Key From Google' />
			</td>
		</tr>
		<tr>
			<td colspan=2>
		<hr><center>
		<strong>Please make sure information above is correct before installing.</strong><br>
		<input type='submit' name='Submit' value='Install UserApplePie' />
		</center>
		</td></tr>
		</table>
		</form>
	";
}else{
	echo "
		UserApplePie requires the following to be installed and working before installation can continue.<hr>
		PHP
	";
			// Check to make sure php is version is good enough
			if (version_compare(phpversion(), '5.3.10', '<')) {
				// php version isn't high enough
				echo " - <font color=red><strong>Out of Date, Update to 5.3.10 or greater to continue.</strong></font>";
				echo " - <a href='http://php.net/' target='_blank'>PHP Website</a>";
				$server_check_status = "FALSE";
			} else {
				echo " - <font color=green><strong>Good To Go!</strong></font>";
			}
	echo "
		<br>
		MySQL
	";
			// Check to make sure php is version is good enough
			if (!function_exists('mysqli_connect')) {
				// php version isn't high enough
				echo " - <font color=red><strong>MySQLi does not seem to be installed.</strong></font>";
				echo " - <a href='https://www.mysql.com/' target='_blank'>MySQLi Website</a>";
				$server_check_status = "FALSE";
			} else {
				echo " - <font color=green><strong>Good To Go!</strong></font>";
			}
	echo " <br>
		ImageMagic
	";
			// Check to make sure php is version is good enough
			if (!extension_loaded('imagick')) {
				// php version isn't high enough
				echo " - <font color=red><strong>ImageMagick does not seem to be installed.</strong></font>";
				echo " - <a href='http://www.imagemagick.org' target='_blank'>ImageMagick Website</a>";
				$server_check_status = "FALSE";
			} else {
				echo " - <font color=green><strong>Good To Go!</strong></font>";
			}
	echo " 
		<Br>
		mod_rewrite
	";
		// Check to see if mod_rewrite is enabled on server
		$isEnabled = in_array('mod_rewrite', apache_get_modules());
			if($isEnabled){
				echo " - <font color=green><strong>Good To Go!</strong></font>";
			} else {
				echo " - <font color=red><strong>Not Enabled.</strong></font>";
				$server_check_status = "FALSE";
			}
	echo "
		<hr>
		Image upload folders need to be writeable for profile images to work.<br>
		Status for folders in /content/profile/<hr>
		images
	";
		// Checks the images folder to see if server can write photos to it
		$dir_check = '../content/profile/images/';
		if (is_dir($dir_check) && is_writable($dir_check)) {
			echo " - <font color=green><strong>Good To Go!</strong></font>";
		} else {
			echo " - <font color=red><strong>Server does NOT have permission to write to this folder!</strong></font>";
			$server_check_status = "FALSE";
		}
	echo "
		<Br>
		small
	";
		// Checks the images folder to see if server can write photos to it
		$dir_check = '../content/profile/small/';
		if (is_dir($dir_check) && is_writable($dir_check)) {
			echo " - <font color=green><strong>Good To Go!</strong></font>";
		} else {
			echo " - <font color=red><strong>Server does NOT have permission to write to this folder!</strong></font>";
			$server_check_status = "FALSE";
		}
	echo "
		<br>
		thumb
	";
		// Checks the images folder to see if server can write photos to it
		$dir_check = '../content/profile/thumb/';
		if (is_dir($dir_check) && is_writable($dir_check)) {
			echo " - <font color=green><strong>Good To Go!</strong></font>";
		} else {
			echo " - <font color=red><strong>Server does NOT have permission to write to this folder!</strong></font>";
			$server_check_status = "FALSE";
		}
		
		
	// Check to see current server status and if installation can continue
	if($server_check_status == "FALSE"){
		echo "<hr><center><font color=red><strong>Sorry, Your server is not properly configured to install UserApplePie $uap_ver!</strong></font></center>";
		echo "<br><br><center>Please correct the above issues and <a href='.'>try again</a>.</center>";
	}else{
		echo "<hr><center><font color=green><strong>Congratulations!  Your server is ready to install UserApplePie $uap_ver</strong></font>";
		echo "<form method='post' action='' onsubmit='submit.disabled = true; return true;'>";
			echo "<input type='hidden' name='pass_requirements' value='TRUE'>";
			echo "<input type=\"submit\" value=\"Start Install\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" />";
		echo "</form></center>";
	}
}

echo "
</body>
</html>";

?>