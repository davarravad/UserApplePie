<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Loads requested page
	$tazibPH2_dir = "$ph2dir";
	$tazibPH2_ext = ".inc";
	
	$tazibPH2_file = "${tazibPH2_dir}${ph2var}${tazibPH2_ext}";

//echo "$tazibPH2_file<br><br>";
	
	if($ph2var){
		if(file_exists($tazibPH2_file)) {
			$tazibPH2_filerun = "YESRUNPH2";
		} else {
			$tazibPH2_content = "
				<center>
				The page <font color=red>$ph2var</font> does NOT exist!<br>
				<br>
				Go back or go <a href='../'>Home</a></center>
			";
			
			//Reporting page error
			$er_type = "Page Error";
			$er_location = "$ph2var";
			$er_msg = "error - page does not exist";
			$erPH2 = "YESErrorPH2";
		}
	} 


?>