<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($_REQUEST['profile'])){
	if(intval($_REQUEST['profile'])){
		$ID02 = intval($_REQUEST['profile']);
	}else{
		$USR02 = $_REQUEST['profile'];
	}
	if(!isset($ID02)){ $ID02 = ""; };
	if(!isset($USR02)){ $USR02 = ""; };
	//echo "($ID02)-($USR02)";
	$tazib_filerun = "YESRUN";
	$tazib_file = "pages/profile.inc";
}else{

	//Get the Page the user has requested to view
	if(isset($_REQUEST['page']) || isset($_REQUEST['taz'])){
		if(isset($_REQUEST['page'])){ $taz = $_REQUEST['page']; }
		if(isset($_REQUEST['taz'])){ $taz = $_REQUEST['taz']; }
	
		//Cleans up the url if there is a forward slash at end of requested page
		$taz = rtrim($taz,'/');
	
		//Loads requested page
		$tazib_dir = "pages/";
		$tazib_ext = ".inc";
		
		//Checks to see if taz is a known file that does not exist but is same as one that does exist
		if($taz == "bn/privacypolicy"){ $taz = "privacypolicy"; }
		if($taz == "bn/disclaimer"){ $taz = "disclaimer"; }
		if($taz == "YummyAsPie"){ $taz = "admin/admin"; }
		if($taz == "gallery"){ $taz = "Gallery"; }
		if($taz == "forum"){ $taz = "Forum"; }
		if($taz == "reminder"){ $taz = "forgot_password"; }
		
		//Case sensitive stuff
		if($taz == "diy"){ $taz = "Forum"; }
		if($taz == "Register"){ $taz = "register"; }
		if($taz == "Login"){ $taz = "login"; }
		
		//Common Error Stuff
		if($taz == "style"){ $taz = ""; }
		if($taz == "addfriend"){ $taz = "friend/addfriend"; }
		
		
		//	if($taz == ""){$taz = ""; }

		$tazib_file = "${tazib_dir}${taz}${tazib_ext}";
	}
	if(!empty($taz)){
		if(file_exists($tazib_file)) {
			$tazib_filerun = "YESRUN";
		} else {
			$tazib_content = "$err_m_head
				<center>
				The page <font color=red>$taz</font> does NOT exist!<br>
				<br>
				Go back or go <a href='../'>Home</a></center>
				$err_m_foot
			";
			
			//Reporting page error
			$er_type = "Page Error";
			$er_location = "?page=$taz";
			$er_msg = "?page= error - page $taz does not exist";
			$er = "YESError";
		}
	} else {
		if(isUserLoggedIn()){
			$tazib_filerun = "YESRUN";
			$tazib_file = "pages/home.inc";	
		}else{
			$tazib_filerun = "YESRUN";
			$tazib_file = "pages/home_main.inc";	
		}
	}
	
}//End of club check
?>
