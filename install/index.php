<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////


require_once("../models/db-settings.inc");

// Current Version
$uap_ver = "v1.1.0";

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

// Check to make sure database is not already installed.  If so then remind user to delete the install folder.
$tableExists = $DBH->query("SHOW TABLES LIKE '".$db_table_prefix."views'");
if($tableExists->rowCount()>0){
	echo 'It looks like your database is already installed!';
	echo "<br><br>";
	echo "Make sure to delete the install folder!";
	echo "<hr>";
	echo "<strong>Reminder</strong>:";
	echo "Make sure to import the install/cities.sql file to your database.  
	Aslo add the table prefix for the two tables it has (cities, cities_exteneded). 
	The site uses this data to display where a user is from based on their zip code.<hr>";
	echo "<p><h1><strong>Database setup complete, please delete the install folder.</h1></strong></p>";
}else{

	// Get Data from form request
	if(isset($_POST['pass_requirements'])){ $pass_requirements = $_POST['pass_requirements']; }else{ $pass_requirements = "FALSE"; }
	if(isset($_POST['install'])){ $install = $_POST['install']; }else{ $install = "FALSE"; }
	if(isset($_POST['enable_photos'])){ $enable_photos = $_POST['enable_photos']; }else{ $enable_photos = "FALSE"; }

	if($install == "TRUE")
	{
		$db_issue = false;
		$config_issue = false;
		
		// Lets make sure that the admin's input is good before we continue.
		$email = trim($_POST["email"]);
		$username = trim($_POST["username"]);
		$displayname = trim($_POST["displayname"]);
		$password = trim($_POST["password"]);
		$confirm_pass = trim($_POST["passwordc"]);
		
		if($password != $confirm_pass){
			echo "<strong>**Admin Passwords Do Not Match!</strong><Br>";
			$config_issue = true;
		}
		if(empty($password)){
			echo "<strong>**Admin Password Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(empty($email)){
			echo "<strong>**Admin Email Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(empty($username)){
			echo "<strong>**Admin UserName Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(empty($displayname)){
			echo "<strong>**Admin DisplayName Was Blank!</strong><Br>";
			$config_issue = true;
		}
		
		if(isset($_POST['website_name'])){ $website_name = $_POST['website_name']; }else{ $website_name = ""; }
		if(empty($website_name)){
			echo "<strong>**Config Setting Error - Website Name Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(isset($_POST['website_url'])){ $website_url = $_POST['website_url']; }else{ $website_url = ""; }
		if(empty($website_url)){
			echo "<strong>**Config Setting Error - Website URL Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(isset($_POST['site_url_link_m'])){ $site_url_link_m = $_POST['site_url_link_m']; }else{ $site_url_link_m = ""; }
		if(empty($site_url_link_m)){
			echo "<strong>**Config Setting Error - Website Mobile URL Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(isset($_POST['site_dir'])){ $site_dir = $_POST['site_dir']; }else{ $site_dir = ""; }
		if(empty($site_dir)){
			echo "<strong>**Config Setting Error - Website Main Directory Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(isset($_POST['site_folder_dir'])){ $site_folder_dir = $_POST['site_folder_dir']; }else{ $site_folder_dir = ""; }
		if(empty($site_folder_dir)){
			echo "<strong>**Config Setting Error - Website Root Folder Directory Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(isset($_POST['site_gbl_descript'])){ $site_gbl_descript = $_POST['site_gbl_descript']; }else{ $site_gbl_descript = ""; }
		if(isset($_POST['site_gbl_keywords'])){ $site_gbl_keywords = $_POST['site_gbl_keywords']; }else{ $site_gbl_keywords = ""; }
		if(isset($_POST['site_email'])){ $site_email = $_POST['site_email']; }else{ $site_email = ""; }
		if(empty($site_email)){
			echo "<strong>**Config Setting Error - Site Email Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(isset($_POST['recap_sitekey'])){ $recap_sitekey = $_POST['recap_sitekey']; }else{ $recap_sitekey = ""; }
		if(empty($recap_sitekey) || $recap_sitekey == "Get Site Key From Google"){
			echo "<strong>**Config Setting Error - Google Site Key Was Blank!</strong><Br>";
			$config_issue = true;
		}
		if(isset($_POST['recap_secretkey'])){ $recap_secretkey = $_POST['recap_secretkey']; }else{ $recap_secretkey = ""; }
		if(empty($recap_secretkey) || $recap_secretkey == "Get Secret Key From Google"){
			echo "<strong>**Config Setting Error - Google Secret Key Was Blank!</strong><Br>";
			$config_issue = true;
		}
		
		// If there is an empty field then give user option to return back
		if(!$config_issue){
			echo "Starting Install!";
		}else{
			echo "<br><br><font color=red><strong>The Previous Config Form was NOT filled out completely.</strong></font><br>";
			echo "<form method='post' action='' onsubmit='submit.disabled = true; return true;'>";
				echo "<input type='hidden' name='pass_requirements' value='TRUE'>";
				echo "<input type='hidden' name='email' value='$email'>";
				echo "<input type='hidden' name='username' value='$username'>";
				echo "<input type='hidden' name='displayname' value='$displayname'>";
				echo "<input type='hidden' name='password' value='$password'>";
				echo "<input type='hidden' name='confirm_pass' value='$confirm_pass'>";
				echo "<input type='hidden' name='website_name' value='$website_name'>";
				echo "<input type='hidden' name='website_url' value='$website_url'>";
				echo "<input type='hidden' name='site_url_link_m' value='$site_url_link_m'>";
				echo "<input type='hidden' name='site_dir' value='$site_dir'>";
				echo "<input type='hidden' name='site_folder_dir' value='$site_folder_dir'>";
				echo "<input type='hidden' name='site_gbl_descript' value='$site_gbl_descript'>";
				echo "<input type='hidden' name='site_gbl_keywords' value='$site_gbl_keywords'>";
				echo "<input type='hidden' name='site_email' value='$site_email'>";
				echo "<input type='hidden' name='recap_sitekey' value='$recap_sitekey'>";
				echo "<input type='hidden' name='recap_secretkey' value='$recap_secretkey'>";
				echo "<input type='hidden' name='enable_photos' value='$enable_photos'>";
				echo "<input type=\"submit\" value=\"Click Here to Go Back and Try Again\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" />";
			echo "</form></center>";
			die;
		}
		
		$permissions_sql = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."permissions` (
		`id` int(11) NOT NULL AUTO_INCREMENT,
		`name` varchar(150) NOT NULL,
		`color` varchar(20) DEFAULT NULL,
		`weight` varchar(20) DEFAULT 'FALSE',
		PRIMARY KEY (`id`)
		) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;
		";
		
		$permissions_entry = "
		INSERT INTO `".$db_table_prefix."permissions` (`id`, `name`) VALUES
		(1, 'New Member'),
		(2, 'Administrator'),
		(3, 'Moderator');
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
		`userIP` varchar(100) NOT NULL,
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
		`value` text NOT NULL,
		PRIMARY KEY (`id`)
		) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=19 ;
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

		$sessions_sql = "CREATE TABLE IF NOT EXISTS `".$db_table_prefix."sessions` (
		`sessionStart` int(11) NOT NULL,
		`sessionData` text NOT NULL,
		`sessionID` varchar(255) NOT NULL,
		PRIMARY KEY (`sessionID`)
		) ENGINE=MyISAM DEFAULT CHARSET=latin1;
		";
		
		//Forum Tables to create
		$table_forum_cat = "CREATE TABLE IF NOT EXISTS `".$db_table_prefix."forum_cat` (
		  `forum_id` int(20) NOT NULL AUTO_INCREMENT COMMENT 'id of form thingy',
		  `forum_name` varchar(255) NOT NULL COMMENT 'name of the full forum',
		  `forum_title` varchar(255) NOT NULL COMMENT 'title of the forum sections',
		  `forum_cat` varchar(255) NOT NULL COMMENT 'title of forum category',
		  `forum_des` text NOT NULL COMMENT 'forum section description',
		  `forum_perm` int(20) NOT NULL DEFAULT '1' COMMENT 'user permissions',
		  `forum_order_title` int(11) NOT NULL,
		  `forum_order_cat` int(11) NOT NULL,
		  PRIMARY KEY (`forum_id`)
		) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";
		
		$table_forum_cat_data = "INSERT INTO `".$db_table_prefix."forum_cat` 
			(`forum_id`, `forum_name`, `forum_title`, `forum_cat`, `forum_des`, `forum_perm`, `forum_order_title`, `forum_order_cat`)
			VALUES
			(1, 'Forum', 'Forum', 'Welcome', 'Welcome to the Forum.', 1, 1, 1);";
		
		$table_forum_posts = "CREATE TABLE IF NOT EXISTS `".$db_table_prefix."forum_posts` (
		  `forum_post_id` int(20) NOT NULL AUTO_INCREMENT,
		  `forum_id` int(20) NOT NULL,
		  `forum_user_id` int(20) NOT NULL,
		  `forum_title` varchar(255) NOT NULL,
		  `forum_content` text NOT NULL,
		  `forum_edit_date` varchar(20) DEFAULT NULL,
		  `forum_status` int(11) NOT NULL DEFAULT '1',
		  `subcribe_email` varchar(10) NOT NULL,
		  `forum_timestamp` varchar(20) DEFAULT NULL,
		  PRIMARY KEY (`forum_post_id`)
		) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";
		
		$table_forum_posts_replys = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."forum_posts_replys` (
		  `id` int(20) NOT NULL AUTO_INCREMENT,
		  `fpr_post_id` int(20) NOT NULL,
		  `fpr_id` int(20) NOT NULL,
		  `fpr_user_id` int(20) NOT NULL,
		  `fpr_title` varchar(255) NOT NULL,
		  `fpr_content` text NOT NULL,
		  `subcribe_email` varchar(10) NOT NULL,
		  `fpr_edit_date` varchar(20) DEFAULT NULL,
		  `fpr_timestamp` varchar(20) DEFAULT NULL,
		  PRIMARY KEY (`id`)
		) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";
		
		$table_a_attempts = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."a_attempts` (
		  `attempts_id` int(11) NOT NULL AUTO_INCREMENT,
		  `attempts_ip` varchar(50) NOT NULL,
		  `attempts` int(1) NOT NULL,
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`attempts_id`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";

		$table_ep2 = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."ep2` (
		  `userId` int(11) NOT NULL DEFAULT '0',
		  `textfield` varchar(255) NOT NULL DEFAULT '',
		  `textarea` text NOT NULL,
		  `textfield2` varchar(255) NOT NULL DEFAULT '',
		  `textarea2` text NOT NULL,
		  `textfield3` varchar(255) NOT NULL DEFAULT '',
		  `textarea3` text NOT NULL,
		  `textfield4` varchar(255) NOT NULL DEFAULT '',
		  `textarea4` text NOT NULL,
		  `textfield5` varchar(255) NOT NULL DEFAULT '',
		  `textarea5` text NOT NULL,
		  `textfield6` varchar(255) NOT NULL DEFAULT '',
		  `textarea6` text NOT NULL,
		  `textfield7` varchar(255) NOT NULL DEFAULT '',
		  `textarea7` text NOT NULL,
		  `textfield8` varchar(255) NOT NULL DEFAULT '',
		  `textarea8` text NOT NULL,
		  PRIMARY KEY (`userId`)
		) ENGINE=MyISAM DEFAULT CHARSET=latin1;
		";

		$table_ep3 = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."ep3` (
		  `id` int(11) NOT NULL AUTO_INCREMENT,
		  `userId` varchar(255) NOT NULL DEFAULT '',
		  `nname` varchar(255) NOT NULL DEFAULT '',
		  `content1` text NOT NULL,
		  `imgdir` varchar(255) NOT NULL DEFAULT '',
		  `imgname` varchar(255) NOT NULL DEFAULT '',
		  `imgsize` varchar(255) NOT NULL DEFAULT '',
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`id`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";

		$table_errors = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."errors` (
		  `er_id` int(11) NOT NULL AUTO_INCREMENT,
		  `er_type` varchar(255) NOT NULL,
		  `er_location` varchar(255) NOT NULL,
		  `er_msg` varchar(255) NOT NULL,
		  `er_user` varchar(255) NOT NULL,
		  `er_refer` varchar(255) NOT NULL,
		  `er_useragent` varchar(255) NOT NULL,
		  `er_cfile` varchar(255) NOT NULL,
		  `er_uri` varchar(255) NOT NULL,
		  `er_ipaddy` varchar(255) NOT NULL,
		  `er_server` varchar(255) NOT NULL,
		  `er_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`er_id`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";

		$table_friend = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."friend` (
		  `id` int(15) NOT NULL AUTO_INCREMENT,
		  `userId1` int(15) NOT NULL,
		  `userId2` int(15) NOT NULL,
		  `status1` varchar(4) NOT NULL DEFAULT '0',
		  `status2` varchar(4) NOT NULL DEFAULT '0',
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`id`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";

		$table_inbox = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."inbox` (
		  `mid` int(11) NOT NULL AUTO_INCREMENT,
		  `mdatesent` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  `mdateread` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  `mfrom` varchar(255) NOT NULL DEFAULT '',
		  `mto` varchar(255) NOT NULL DEFAULT '',
		  `mcontent` text NOT NULL,
		  `msubject` varchar(255) NOT NULL DEFAULT '',
		  `mread` varchar(6) NOT NULL DEFAULT 'unread',
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`mid`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;
		";

		$table_loggedusers = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."loggedusers` (
		  `userId` int(11) NOT NULL DEFAULT '0',
		  `sessionId` char(32) NOT NULL DEFAULT '',
		  `loginTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  `lastAccess` datetime DEFAULT NULL,
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
		  PRIMARY KEY (`userId`,`sessionId`),
		  KEY `lastAccess` (`lastAccess`)
		) ENGINE=MyISAM DEFAULT CHARSET=latin1;
		";

		$table_outbox = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."outbox` (
		  `id` int(10) NOT NULL AUTO_INCREMENT,
		  `mid` int(11) NOT NULL,
		  `mdatesent` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  `mdateread` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  `mfrom` varchar(255) NOT NULL DEFAULT '',
		  `mto` varchar(255) NOT NULL DEFAULT '',
		  `mcontent` text NOT NULL,
		  `msubject` varchar(255) NOT NULL DEFAULT '',
		  `mread` varchar(6) NOT NULL DEFAULT 'unread',
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`id`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;
		";

		$table_profilecomments = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."profilecomments` (
		  `id` int(10) NOT NULL AUTO_INCREMENT,
		  `com_uid` int(11) NOT NULL,
		  `com_id` int(10) NOT NULL DEFAULT '0',
		  `com_name` varchar(255) NOT NULL DEFAULT '',
		  `com_content` text NOT NULL,
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`id`)
		) ENGINE=MyISAM DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;
		";

		$table_profilecomments_b = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."profilecomments_b` (
		  `id` int(10) NOT NULL AUTO_INCREMENT,
		  `statcom_id` int(10) NOT NULL DEFAULT '0',
		  `statcom_uid` int(15) NOT NULL,
		  `statcom_name` varchar(255) NOT NULL DEFAULT '',
		  `statcom_content` text NOT NULL,
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`id`)
		) ENGINE=MyISAM DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;
		";

		$table_report = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."report` (
		  `report_id` int(11) NOT NULL AUTO_INCREMENT,
		  `report_type` varchar(255) NOT NULL,
		  `report_msg` text NOT NULL,
		  `report_user` varchar(255) NOT NULL,
		  `report_userID` int(15) NOT NULL,
		  `report_refer` varchar(255) NOT NULL,
		  `report_useragent` varchar(255) NOT NULL,
		  `report_cfile` varchar(255) NOT NULL,
		  `report_uri` varchar(255) NOT NULL,
		  `report_ipaddy` varchar(255) NOT NULL,
		  `report_server` varchar(255) NOT NULL,
		  `report_pageURL` varchar(255) NOT NULL,
		  `admin_checked` varchar(255) NOT NULL,
		  `report_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`report_id`)
		) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";

		$table_sitelogs = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."sitelogs` (
		  `id` int(10) NOT NULL AUTO_INCREMENT,
		  `membername` varchar(255) NOT NULL DEFAULT '',
		  `refer` varchar(255) NOT NULL DEFAULT '',
		  `useragent` varchar(255) NOT NULL DEFAULT '',
		  `cfile` varchar(255) NOT NULL DEFAULT '',
		  `uri` varchar(255) NOT NULL DEFAULT '',
		  `ipaddy` varchar(255) NOT NULL DEFAULT '',
		  `server` varchar(255) NOT NULL DEFAULT '',
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`id`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;
		";

		$table_statcom = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."statcom` (
		  `id` int(10) NOT NULL AUTO_INCREMENT,
		  `statcom_id` int(10) NOT NULL DEFAULT '0',
		  `statcom_uid` int(15) NOT NULL,
		  `statcom_name` varchar(255) NOT NULL DEFAULT '',
		  `statcom_content` text NOT NULL,
		  `statcom_date` date NOT NULL DEFAULT '0000-00-00',
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`id`)
		) ENGINE=MyISAM DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;
		";

		$table_status = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."status` (
		  `id` int(10) NOT NULL AUTO_INCREMENT,
		  `com_id` int(10) NOT NULL DEFAULT '0',
		  `com_uid` int(15) NOT NULL,
		  `com_name` varchar(255) NOT NULL DEFAULT '',
		  `com_content` text NOT NULL,
		  `com_date` date NOT NULL DEFAULT '0000-00-00',
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`id`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 PACK_KEYS=0 AUTO_INCREMENT=1 ;
		";

		$table_sweet = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."sweet` (
		  `sid` int(10) NOT NULL AUTO_INCREMENT,
		  `sweet_id` int(10) NOT NULL,
		  `sweet_sec_id` int(10) NOT NULL,
		  `sweet_sub` varchar(255) NOT NULL,
		  `sweet_location` varchar(255) NOT NULL,
		  `sweet_userid` int(10) NOT NULL,
		  `sweet_url` varchar(255) NOT NULL,
		  `sweet_owner_userid` int(10) NOT NULL,
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`sid`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";

		$table_userprofile = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."userprofile` (
		  `userId` int(11) NOT NULL DEFAULT '0',
		  `userFirstName` varchar(64) NOT NULL DEFAULT '',
		  `userEmail` varchar(64) NOT NULL DEFAULT '',
		  `userLastName` varchar(64) NOT NULL DEFAULT '',
		  `userCompany` varchar(15) NOT NULL DEFAULT '',
		  `userAddr1` varchar(64) NOT NULL DEFAULT '',
		  `userAddr2` varchar(64) NOT NULL DEFAULT '',
		  `userCity` varchar(64) NOT NULL DEFAULT '',
		  `userAdds` varchar(5) NOT NULL DEFAULT 'TRUE',
		  `userCountry` varchar(64) NOT NULL DEFAULT '',
		  `userTel` varchar(255) NOT NULL,
		  `userMobiTel` varchar(255) NOT NULL,
		  `userHomeTel` varchar(255) NOT NULL,
		  `profile_privacy` varchar(20) NOT NULL DEFAULT 'public',
		  `userZip` varchar(20) NOT NULL DEFAULT 'public',
		  `userWeb` varchar(128) NOT NULL DEFAULT '',
		  `userFacebook` varchar(255) NOT NULL,
		  `userTwitter` varchar(255) NOT NULL,
		  `userValidationKey` varchar(32) NOT NULL DEFAULT '',
		  `userIP` varchar(32) NOT NULL DEFAULT '',
		  `userSignUp` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  `userValidated` tinyint(1) NOT NULL DEFAULT '0',
		  `userNewsLetter` tinyint(1) NOT NULL DEFAULT '0',
		  `mainPic` varchar(255) NOT NULL DEFAULT 'noimg.gif',
		  `user_email_msg` varchar(10) NOT NULL DEFAULT 'yes',
		  `user_email_profile_com` varchar(10) NOT NULL DEFAULT 'yes',
		  `user_email_vp_com` varchar(10) NOT NULL DEFAULT 'yes',
		  `user_email_veh_pic_com` varchar(10) NOT NULL DEFAULT 'yes',
		  `userLastLogin` datetime NOT NULL,
		  PRIMARY KEY (`userId`)
		) ENGINE=MyISAM DEFAULT CHARSET=latin1;
		";

		$table_users = "
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
		  `userIP` varchar(100) NOT NULL,
		  `sign_up_stamp` int(11) NOT NULL,
		  `last_sign_in_stamp` int(11) NOT NULL,
		  PRIMARY KEY (`id`)
		) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
		";

		$table_views = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."views` (
		  `vid` int(10) NOT NULL AUTO_INCREMENT,
		  `view_id` int(10) NOT NULL,
		  `view_sec_id` int(10) NOT NULL,
		  `view_sub` varchar(255) NOT NULL,
		  `view_location` varchar(255) NOT NULL,
		  `view_userid` varchar(50) NOT NULL,
		  `view_url` varchar(255) NOT NULL,
		  `view_owner_userid` int(10) NOT NULL,
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`vid`)
		) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";
		
		$table_admin = "
		CREATE TABLE IF NOT EXISTS `".$db_table_prefix."admin` (
		  `id` int(10) NOT NULL AUTO_INCREMENT,
		  `adminID` int(10) NOT NULL,
		  `adminuser` varchar(255) NOT NULL DEFAULT '',
		  `admincontent` text NOT NULL,
		  `adminshow` varchar(255) NOT NULL DEFAULT '',
		  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
		  PRIMARY KEY (`id`)
		) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
		";
		
		$configuration_entry = "
		INSERT INTO `".$db_table_prefix."configuration` (`id`, `name`, `value`) VALUES
		(1, 'website_name', '$website_name'),
		(2, 'website_url', '$website_url'),
		(3, 'site_url_link_m', '$site_url_link_m'),
		(4, 'site_dir', '$site_dir'),
		(5, 'site_folder_dir', '$site_folder_dir'),
		(6, 'site_debug', 'FALSE'),
		(7, 'site_gbl_descript', '$site_gbl_descript'),
		(8, 'site_gbl_keywords', '$site_gbl_keywords'),
		(9, 'email', '$site_email'),
		(10, 'resend_activation_threshold', '0'),
		(11, 'language', 'models/languages/en.php'),
		(12, 'activation', 'false'),
		(13, 'template', 'style/default'),
		(14, 'recap_sitekey', '$recap_sitekey'),
		(15, 'recap_secretkey', '$recap_secretkey'),
		(16, 'site_adds_top', ''),
		(17, 'site_adds_bot', ''),
		(18, 'enable_photos', '$enable_photos');
		";
		
		$stmt = $DBH->prepare($configuration_sql);

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
		
		// Run Forum Tables Creation
		$stmt = $mysqli->prepare($table_forum_cat);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."forum_cat table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."forum_cat table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_forum_cat_data);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."forum_cat data added to table.....</p>";
		}
		else
		{
			echo "<p>Error adding data to ".$db_table_prefix."forum_cat table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_forum_posts);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."forum_posts table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."forum_posts table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_forum_posts_replys);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."forum_posts_replys table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."forum_posts_replys table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_a_attempts);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."a_attempts table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."a_attempts table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_ep2);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."ep2 table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."ep2 table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_ep3);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."ep3 table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."ep3 table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_errors);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."errors table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."errors table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_friend);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."friend table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."friend table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_inbox);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."inbox table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."inbox table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_loggedusers);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."loggedusers table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."loggedusers table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_outbox);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."outbox table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."outbox table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_profilecomments);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."profilecomments table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."profilecomments table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_profilecomments_b);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."profilecomments_b table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."profilecomments_b table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_report);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."report table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."report table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_sitelogs);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."sitelogs table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."sitelogs table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_statcom);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."statcom table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."statcom table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_status);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."status table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."status table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_sweet);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."sweet table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."sweet table.....</p>";
			$db_issue = true;
		}	
		
		$stmt = $mysqli->prepare($table_userprofile);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."userprofile table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."userprofile table.....</p>";
			$db_issue = true;
		}	
		
		$stmt = $mysqli->prepare($table_users);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."users table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."users table.....</p>";
			$db_issue = true;
		}	
		
		$stmt = $mysqli->prepare($table_views);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."views table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."views table.....</p>";
			$db_issue = true;
		}
		
		$stmt = $mysqli->prepare($table_admin);
		if($stmt->execute())
		{
			echo "<p>".$db_table_prefix."admin table created.....</p>";
		}
		else
		{
			echo "<p>Error constructing ".$db_table_prefix."admin table.....</p>";
			$db_issue = true;
		}
		
		
		// Database is now setup.  Lets add config to database.
		
		// Add admin user to database
		// Include config to setup new user
		require_once("adminuser.inc");
		uap_create_admin_user($email,$username,$displayname,$password);
		
		// Include the cities file for database
		echo "<hr>NOTE: Make sure to import the install/cities.sql file to your database.  
		Aslo add the table prefix for the two tables it has (cities, cities_exteneded). 
		The site uses this data to display where a user is from based on their zip code.<hr>";
		
		if(!$db_issue){
			echo "<p><h1><strong>Database setup complete, please delete the install folder.</h1></strong></p>";
		} else {
			echo "<p><a href=\"\">Try again</a></p>";
		}
	}
	else if($pass_requirements == 'TRUE')
	{
		
		function substrAfter($str, $last) {
			$startPos = strrpos($str, $last);
			if ($startPos !== false) {
				$startPos++;
				return ($startPos < strlen($str)) ? substr($str, $startPos) : '';
			}
			return $str;
		}
		
		// Get information to attempt to fill out the forum for the user
		$base_dir  = __DIR__; // Absolute path to your installation, ex: /var/www/mywebsite
		$doc_root  = preg_replace("!{$_SERVER['SCRIPT_NAME']}$!", '', $_SERVER['SCRIPT_FILENAME']); # ex: /var/www
		$base_url  = preg_replace("!^{$doc_root}!", '', $base_dir); # ex: '' or '/mywebsite'
		$protocol  = empty($_SERVER['HTTPS']) ? 'http' : 'https';
		$port      = $_SERVER['SERVER_PORT'];
		$disp_port = ($protocol == 'http' && $port == 80 || $protocol == 'https' && $port == 443) ? '' : ":$port";
		$domain    = $_SERVER['SERVER_NAME'];
		$full_url  = "$protocol://{$domain}{$disp_port}{$base_url}"; # Ex: 'http://example.com', 'https://example.com/mywebsite', etc.
		
		$site_folder = substrAfter($doc_root, '/');
		$full_url = str_replace('/install', '', $full_url);
		$root_dir = str_replace($site_folder, '', $doc_root);
		
		if(isset($_POST['enable_photos'])){ $enable_photos = $_POST['enable_photos']; }else{ $enable_photos = "FALSE"; }
		if(isset($_POST['email'])){ $email = $_POST['email']; }else{ $email = ""; }
		if(isset($_POST['username'])){ $username = $_POST['username']; }else{ $username = "Admin"; }
		if(isset($_POST['displayname'])){ $displayname = $_POST['displayname']; }else{ $displayname = "Admin"; }
		if(isset($_POST['password'])){ $password = $_POST['password']; }else{ $password = ""; }
		if(isset($_POST['confirm_pass'])){ $confirm_pass = $_POST['confirm_pass']; }else{ $confirm_pass = ""; }
		if(isset($_POST['website_name'])){ $website_name = $_POST['website_name']; }else{ $website_name = "UserApplePie"; }
		if(isset($_POST['website_url'])){ $website_url = $_POST['website_url']; }else{ $website_url = $full_url."/"; }
		if(isset($_POST['site_url_link_m'])){ $site_url_link_m = $_POST['site_url_link_m']; }else{ $site_url_link_m = $full_url."/"; }
		if(isset($_POST['site_dir'])){ $site_dir = $_POST['site_dir']; }else{ $site_dir = $site_folder; }
		if(isset($_POST['site_folder_dir'])){ $site_folder_dir = $_POST['site_folder_dir']; }else{ $site_folder_dir = $root_dir; }
		if(isset($_POST['site_gbl_descript'])){ $site_gbl_descript = $_POST['site_gbl_descript']; }else{ $site_gbl_descript = "My Website and Stuff"; }
		if(isset($_POST['site_gbl_keywords'])){ $site_gbl_keywords = $_POST['site_gbl_keywords']; }else{ $site_gbl_keywords = "UserApplePie, UserCake"; }
		if(isset($_POST['site_email'])){ $site_email = $_POST['site_email']; }else{ $site_email = "admin@website.com"; }
		if(isset($_POST['recap_sitekey'])){ $recap_sitekey = $_POST['recap_sitekey']; }else{ $recap_sitekey = "Get Site Key From Google"; }
		if(isset($_POST['recap_secretkey'])){ $recap_secretkey = $_POST['recap_secretkey']; }else{ $recap_secretkey = "Get Secret Key From Google"; }
		
		echo "
			<strong>Update the following information to match your server settings.  Make sure you replace the default text or your website may have issues.</strong><hr>
			<form name='adminConfiguration' action='' method='post'>
			<table width=100%><tr>
				<td>
					<label>Website Name:</label>
				</td><td>
					<input size='60' maxlength='150' type='text' name='website_name' value='$website_name' />
				</td>
				<td>
					EX: UserApplePie
				</td>
			</tr><tr>
				<td>
					<label>Website URL:</label>
				</td><td>
					<input size='60' maxlength='150' type='text' name='website_url' value='$website_url' />
				</td>
				<td>
					EX: http://www.website.com/
				</td>
			</tr><tr>
				<td>
					<label>Website Mobile URL:</label>
				</td><td>
					<input size='60' maxlength='150' type='text' name='site_url_link_m' value='$site_url_link_m' />
				</td>
				<td>
					EX: http://m.website.com/
				</td>
			</tr><tr>
				<td>
					<label>Website Main Directory:</label>
				</td><td>
					<input size='60' maxlength='150' type='text' name='site_dir' value='$site_dir' />
				</td>
				<td>
					EX: websitefolder
				</td>
			</tr><tr>
				<td>
					<label>Website Root Folder Directory:</label>
				</td><td>
					<input size='60' maxlength='150' type='text' name='site_folder_dir' value='$site_folder_dir' />
				</td>
				<td>
					EX: /var/www/html/
				</td>
			</tr><tr>
				<td>
					<label>Website Description:</label>
				</td><td>
					<textarea rows='4' cols='45' type='text' maxlength='255' name='site_gbl_descript'>$site_gbl_descript</textarea>
				</td>
				<td>
				</td>
			</tr><tr>
				<td>
					<label>Website Keywords:</label>
				</td><td>
					<textarea rows='4' cols='45' type='text' maxlength='255' name='site_gbl_keywords'>$site_gbl_keywords</textarea>
				</td>
				<td>
				</td>
			</tr><tr>
				<td>
					<label>Site Email:</label>
				</td><td>
					<input size='60' maxlength='255' type='text' name='site_email' value='$site_email' />
				</td>
				<td>
				</td>
			</tr>
			<tr><td colspan=3>
			<hr>
			<strong>Google reCAPTCHA Settings</strong> - <a href='https://www.google.com/recaptcha/' target='_blank'>Google reCAPTCHA</a>
			</td></tr>
			<tr>
				<td>
					<label>Site Key:</label>
				</td><td>
					<input size='60' maxlength='255' type='text' name='recap_sitekey' value='$recap_sitekey' />
				</td>
				<td>
				</td>
			</tr>
			<tr>
				<td>
					<label>Secret Key:</label>
				</td><td>
					<input size='60' maxlength='255' type='text' name='recap_secretkey' value='$recap_secretkey' />
				</td>
				<td>
				</td>
			</tr>
			<tr><td colspan=3>
			<hr>
			<strong>Admin Login Username/Password</strong><Br>
			We are now going to create the Admin's account so that you can get right to work on your website after install.
			</td></tr>
			<tr>
				<td>
					<label>Admin User Name:</label>
				</td><td>
					<input id='username' type='text' name='username' value='$username' /> 
				</td>
				<td>
				</td>
			</tr>
			<tr>
				<td>
					<label>Admin Display Name:</label>
				</td><td>
					<input id='displayname' type='text' name='displayname' value='$displayname' /> 
				</td>
				<td>
				</td>
			</tr>
			<tr>
				<td>
					<label>Admin Password:</label>
				</td><td>
					<input type='password' name='password' id='passwordInput' value='$password' />
				</td>
				<td>
				</td>
			</tr>
			<tr>
				<td>
					<label>Confirm Password:</label>
				</td><td>
					<input type='password' name='passwordc' id='confirmPasswordInput' value='$confirm_pass' />
				</td>
				<td>
				</td>
			</tr>
			<tr>
				<td>
					<label>Admin E-Mail:</label>
				</td><td>
					<input type='text' name='email' value='$email' />
				</td>
				<td>
				</td>
			</tr>
			<tr>
				<td colspan=3>
			<hr><center>
			<input type='hidden' name='install' value='TRUE'>
			<input type='hidden' name='enable_photos' value='$enable_photos'>
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
					$server_check_imagemagic = "FALSE";
				} else {
					echo " - <font color=green><strong>Good To Go!</strong></font>";
					$server_check_imagemagic = "TRUE";
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
		if($server_check_imagemagic == "FALSE"){
			echo "<hr>";
			echo "ImageMagic is not installed or not working properly.  You can still install UserApplePie, but Image uploads will be disabled.";
		}else{
			$server_check_imagemagic == "TRUE";
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
		}
		if(empty($server_check_status)){ $server_check_status = ""; }
			
		// Check to see current server status and if installation can continue
		if($server_check_status == "FALSE"){
			echo "<hr><center><font color=red><strong>Sorry, Your server is not properly configured to install UserApplePie $uap_ver!</strong></font></center>";
			echo "<br><br><center>Please correct the above issues and <a href='.'>try again</a>.</center>";
		}else{
			echo "<hr><center><font color=green><strong>Congratulations!  Your server is ready to install UserApplePie $uap_ver</strong></font>";
			echo "<form method='post' action='' onsubmit='submit.disabled = true; return true;'>";
				echo "<input type='hidden' name='pass_requirements' value='TRUE'>";
				echo "<input type='hidden' name='enable_photos' value='$server_check_imagemagic'>";
				echo "<input type=\"submit\" value=\"Start Install\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" />";
			echo "</form></center>";
		}


	}
} // End database table check

echo "
</body>
</html>";

?>