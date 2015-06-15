<?php
	if(isUserLoggedIn()){

		if(is_admin()) {


	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
	echo "Admin Manage Site System"; 
	echo "</td></tr>";
	echo "<tr><td class='content78'><center>";

//START OF CONTENT


		//Page Error Handler
		if(isset($_REQUEST['adp'])){ 
			$adp = $_REQUEST['adp']; 
			$ph2var = "$adp";
			$ph2dir = "models/admin/";
		}
		if(isset($_REQUEST['adp2'])){ 
			$adp2 = $_REQUEST['adp2']; 
			$ph2var = "$adp2";
			$ph2dir = "pages/locations/";
		}
		
		if(isset($adp)){}else{ $adp = ""; }
		if(isset($adp2)){}else{ $adp2 = ""; }
		if(isset($ph2var)){}else{ $ph2var = ""; }
		if(isset($ph2dir)){}else{ $ph2dir = ""; }
		
		require("models/pagehand2.inc");

			echo "<table width='100%'><tr><td class='epbox'>";
			echo "<strong>Welcome Back Admin!</strong>
					<hr><center>
				<a href='${site_url_link}YummyAsPie/stats/'>Stats</a>  
				| <a href='${site_url_link}YummyAsPie/reports/'>Reports</a> 
				| <a href='${site_url_link}YummyAsPie/errors/'>Errors</a>
				| <a href='${site_url_link}YummyAsPie/adminmessage/'>Admin Message</a>";
			echo "<hr>";
			echo "
				<a href='${site_url_link}YummyAsPie/admin_configuration/'>Admin Configuration</a> | 
				<a href='${site_url_link}YummyAsPie/admin_users/'>Admin Users</a> | 
				<a href='${site_url_link}YummyAsPie/admin_permissions/'>Admin Permissions</a> | 
				<a href='${site_url_link}YummyAsPie/admin_pages/'>Admin Pages</a>";
			echo "<hr>";
			echo "
				<a href='${site_url_link}YummyAsPie/admin_forum/'>Admin Forum</a>";
			echo "</center></td></tr></table><br>";


				//This is the Main content table.  All pages will be loaded here.
				//
				
						if(!isset($tazibPH2_filerun)){ $tazibPH2_filerun = ""; }
						if(!isset($tazibPH2_content)){ $tazibPH2_content = ""; }
						if($tazibPH2_filerun == 'YESRUNPH2'){
							require("$tazibPH2_file"); 
						} else {
							echo "$tazibPH2_content";	
						}
						if(isset($erPH2)){
							if($erPH2 == 'YESErrorPH2'){
								require("models/errorreport.inc");	
							}
						}

//END OF CONTENT

	echo "</center></td></tr></table>";
	echo "</center><br>";

		}
		else{
			echo "Admin Only.";
			exit();
		}

	}
	else{
		notlogedinmsg();
		exit();
	}


?>
