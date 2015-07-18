<?php
if(isUserLoggedIn())
{
	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{
	
				if(isset($_POST['userFirstName'])){ $userFirstName = $_POST['userFirstName']; }else{ $userFirstName = ""; }
				if(isset($_POST['userLastName'])){ $userLastName = $_POST['userLastName']; }else{ $userLastName = ""; }
				if(isset($_POST['userEmail'])){ $userEmail = $_POST['userEmail']; }else{ $userEmail = ""; }
				if(isset($_POST['userAddr1'])){ $userAddr1 = $_POST['userAddr1']; }else{ $userAddr1 = ""; }
				if(isset($_POST['userAddr2'])){ $userAddr2 = $_POST['userAddr2']; }else{ $userAddr2 = ""; }
				if(isset($_POST['userCity'])){ $userCity = $_POST['userCity']; }else{ $userCity = ""; }
				if(isset($_POST['userState'])){ $userState = $_POST['userState']; }else{ $userState = ""; }
				if(isset($_POST['userCountry'])){ $userCountry = $_POST['userCountry']; }else{ $userCountry = ""; }
				if(isset($_POST['userTel'])){ $userTel = $_POST['userTel']; }else{ $userTel = ""; }
				if(isset($_POST['userMobiTel'])){ $userMobiTel = $_POST['userMobiTel']; }else{ $userMobiTel = ""; }
				if(isset($_POST['userHomeTel'])){ $userHomeTel = $_POST['userHomeTel']; }else{ $userHomeTel = ""; }
				if(isset($_POST['userFacebook'])){ $userFacebook = $_POST['userFacebook']; }else{ $userFacebook = ""; }
				if(isset($_POST['userTwitter'])){ $userTwitter = $_POST['userTwitter']; }else{ $userTwitter = ""; }
				if(isset($_POST['userWeb'])){ $userWeb = $_POST['userWeb']; }else{ $userWeb = ""; }
				if(isset($_POST['profile_privacy'])){ $profile_privacy = $_POST['profile_privacy']; }else{ $profile_privacy = ""; }
				if(isset($_POST['userZip'])){ $userZip = $_POST['userZip']; }else{ $userZip = ""; }
				 
				require "models/members/getuserinfo.inc";
				$userId = $idofuser;

				$userWeb = preg_replace('/(http:\/\/)/i', '', $userWeb);
				
			   // saving script



				  $query = "UPDATE `".$db_table_prefix."userprofile` SET `userFirstName` = '$userFirstName', `userLastName` = '$userLastName', 
							`userEmail` = '$userEmail', `userAddr1` = '$userAddr1', `userAddr2` = '$userAddr2', 
							`userCity` = '$userCity', `userAdds` = '$userState', `userCountry` = '$userCountry', 
							`userTel` = '$userTel', `userMobiTel` = '$userMobiTel', `userHomeTel` = '$userHomeTel', 
							`userWeb` = '$userWeb', `profile_privacy` = '$profile_privacy', `userZip` = '$userZip',
							`userFacebook`='$userFacebook', `userTwitter`='$userTwitter' WHERE `userId`='$userId' ";

			  

			 $results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

			   // print out the results
			   if( $results )
			   {
			   
			   
			   
			 //     echo( "Profile Update Submit<br><br>" );
			 //     echo( "Successfully saved the entry.<br><br><a href='${site_url_link}?page=editprofilemain&pee=ep1'>Back to Profile Editor</a>" );
						//echo "<meta HTTP-EQUIV='REFRESH' content='0; url=?page=editprofilemain'>";	
			   
			   }
			 
			   else
			   {
					//Code used to report mysql error
					$mysql_error_report = "TRUE";
					$sql_query = "$query";
					require "models/mysql_error_report.inc";
			   }
				
			   
			require "pages/profile/ep2s.inc";

	} //end token
}else {
	notlogedinmsg();
}


?>