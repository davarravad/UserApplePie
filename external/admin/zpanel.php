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


ob_start();

require_once("./external/config.php");

// Get user information
if(isset($loggedInUser->user_id)){
	$get_loggedin_uid = $loggedInUser->user_id;
}else{
	$get_loggedin_uid = "0";
}
$userId = $get_loggedin_uid;
$userIdme = $userId;

require("./external/members/funcs_user_info.php");
require("./external/functions.php");
require("./external/design/funcs_styles.php");

// Html Stuff
echo "
<!DOCTYPE html>
<html lang='en'>

<head>

    <meta charset='utf-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <meta name='description' content='$websiteName Administrator Panel'>
    <meta name='author' content=''>

    <title>$websiteName Admin Panel</title>

    <!-- Bootstrap Core CSS -->
    <link href='/external/admin/css/bootstrap.min.css' rel='stylesheet'>

    <!-- Custom CSS -->
    <link href='/external/admin/css/sb-admin.css' rel='stylesheet'>

    <!-- Morris Charts CSS -->
    <link href='/external/admin/css/plugins/morris.css' rel='stylesheet'>

    <!-- Custom Fonts -->
    <link href='/external/admin/font-awesome/css/font-awesome.min.css' rel='stylesheet' type='text/css'>

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src='https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js'></script>
        <script src='https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js'></script>
    <![endif]-->
	
</head>

<body>

";

if(isUserLoggedIn() && is_admin()) {

// If demo server, editing of configs is disabled.
// Current Server Name
$cur_server_name_dc = $_SERVER['SERVER_NAME'];
// Demo Server Name: 
$demo_server_name_dc = "demo.userapplepie.com";
	
// Get Current User's Display Name
$user_displayname = get_up_info_mem_disp_name($userIdme);


//START OF CONTENT

		//Page Error Handler
		if(isset($_REQUEST['pee'])){ 
			$adp = $_REQUEST['pee']; 
			$ph2var = "$adp";
			$ph2dir = "external/admin/";
		}
		
		if(isset($adp)){}else{ $adp = ""; }
		if(isset($adp2)){}else{ $adp2 = ""; }
		if(isset($ph2var)){}else{ $ph2var = ""; }
		if(isset($ph2dir)){}else{ $ph2dir = ""; }
		
		require("./external/pagehand2.php");
		//End page Error Stuff

		//Navigation Stuff
		echo "
			<div id='wrapper'>

				<!-- Navigation -->
				<nav class='navbar navbar-inverse navbar-fixed-top' role='navigation'>
					<!-- Brand and toggle get grouped for better mobile display -->
					<div class='navbar-header'>
						<button type='button' class='navbar-toggle' data-toggle='collapse' data-target='.navbar-ex1-collapse'>
							<span class='sr-only'>Toggle navigation</span>
							<span class='icon-bar'></span>
							<span class='icon-bar'></span>
							<span class='icon-bar'></span>
						</button>
						<a class='navbar-brand' href='{$websiteUrl}UAP_Admin_Panel/'><i class='glyphicon glyphicon-cog'></i> Admin Panel</a>
					</div>
					<!-- Top Menu Items -->
					<ul class='nav navbar-right top-nav'>
						<li class='dropdown'>
							<a href='#' class='dropdown-toggle' data-toggle='dropdown'><i class='fa fa-user'></i> $user_displayname <b class='caret'></b></a>
							<ul class='dropdown-menu'>
								<li>
									<a href='$websiteUrl'><i class='fa fa-fw fa-power-off'></i> Main Site</a>
								</li>
							</ul>
						</li>
					</ul>
					<!-- Sidebar Menu Items - These collapse to the responsive navigation menu on small screens -->
					<div class='collapse navbar-collapse navbar-ex1-collapse'>
						<ul class='nav navbar-nav side-nav'>
							<li "; if($ph2var == ""){echo "class='active'";} echo " >
								<a href='{$websiteUrl}UAP_Admin_Panel/'><i class='fa fa-fw fa-dashboard'></i> Dashboard</a>
							</li>
							<li "; if($ph2var == "reports"){echo "class='active'";} echo " >
								<a href='${site_url_link}UAP_Admin_Panel/reports/'><i class='glyphicon glyphicon-info-sign'></i> Support Tickets</a>
							</li>
							<li "; if($ph2var == "errors"){echo "class='active'";} echo " >
								<a href='${site_url_link}UAP_Admin_Panel/errors/'><i class='glyphicon glyphicon-alert'></i> Site Errors</a>
							</li>
							<li "; if($ph2var == "admin_configuration"){echo "class='active'";} echo " >
								<a href='${site_url_link}UAP_Admin_Panel/admin_configuration/'><i class='glyphicon glyphicon-wrench'></i> Site Configuration</a>
							</li>
							<li "; if($ph2var == "admin_users"){echo "class='active'";} echo " >
								<a href='${site_url_link}UAP_Admin_Panel/admin_users/'><i class='glyphicon glyphicon-user'></i> Users</a>
							</li>
							<li "; if($ph2var == "admin_permissions"){echo "class='active'";} echo " >
								<a href='${site_url_link}UAP_Admin_Panel/admin_permissions/'><i class='glyphicon glyphicon-book'></i> Groups</a>
							</li>
							<li "; if($ph2var == "admin_pages"){echo "class='active'";} echo " >
								<a href='${site_url_link}UAP_Admin_Panel/admin_pages/'><i class='glyphicon glyphicon-file'></i> Pages</a>
							</li>
							<li "; if($ph2var == "adminmessage"){echo "class='active'";} echo " >
								<a href='${site_url_link}UAP_Admin_Panel/adminmessage/'><i class='fa fa-fw fa-desktop'></i> Site Message</a>
							</li>
							<li "; if($ph2var == "admin_wm"){echo "class='active'";} echo " >
								<a href='${site_url_link}UAP_Admin_Panel/admin_wm/'><i class='glyphicon glyphicon-envelope'></i> Register Message</a>
							</li>
							<li>
								<a href='javascript:;' data-toggle='collapse' data-target='#demo'><i class='fa fa-fw fa-arrows-v'></i> Forum <i class='fa fa-fw fa-caret-down'></i></a>
								<ul id='demo' class='collapse'>
									<li>
										<a href='#'>Coming Soon!</a>
									</li>
									<li>
										<a href='#'>Coming Soon!</a>
									</li>
								</ul>
							</li>
						</ul>
					</div>
					<!-- /.navbar-collapse -->
				</nav>
				
		        <div id='page-wrapper'>

					<div class='container-fluid'>
		";
		
		//Shows a success_message if there is one.
		success_message();

		//This is the Main content table.  All pages will be loaded here.
		if(!isset($tazibPH2_filerun)){ $tazibPH2_filerun = ""; }
		if($tazibPH2_filerun == 'YESRUNPH2'){
			require("./$tazibPH2_file"); 
		} else {
			require("./external/admin/dashboard.php");	
		}
		if(isset($erPH2)){
			if($erPH2 == 'YESErrorPH2'){
				require("./external/errorreport.php");	
			}
		}
		//End of Main Content table
		
		// Closing of wrapper and other open divs
		echo "
					</div> <!-- /.container-fluid -->
				</div> <!-- /.page-wrapper -->
			</div> <!-- /.wrapper -->
		";
//END OF CONTENT



}
else{
	err_message("Admin Only");
	exit();
}

echo "

    <!-- jQuery -->
    <script src='/external/admin/js/jquery.js'></script>

    <!-- Bootstrap Core JavaScript -->
    <script src='/external/admin/js/bootstrap.min.js'></script>

    <!-- Morris Charts JavaScript -->
    <script src='/external/admin/js/plugins/morris/raphael.min.js'></script>
    <script src='/external/admin/js/plugins/morris/morris.min.js'></script>
    <script src='/external/admin/js/plugins/morris/morris-data.js'></script>

</body>

</html>

";

?>
