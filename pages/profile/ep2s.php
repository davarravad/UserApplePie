
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


if(isUserLoggedIn())
{


	if(isset($_POST['new'])){ $new = $_POST['new']; }else{ $new = ""; }

	$userId = $_POST['userId'];


	if(isset($_POST['textfield'])){ 
		$textfield = $_POST['textfield'];
	}else{ $textfield = ""; }
	if(isset($_POST['textarea'])){ 
		$textarea = $_POST['textarea'];
	}else{ $textarea = ""; }

	if(isset($_POST['textfield2'])){ 
		$textfield2 = $_POST['textfield2'];
	}else{ $textfield2 = ""; }
	if(isset($_POST['textarea2'])){ 
		$textarea2 = $_POST['textarea2'];
	}else{ $textarea2 = ""; }

	if(isset($_POST['textfield3'])){ 
		$textfield3 = $_POST['textfield3'];
	}else{ $textfield3 = ""; }
	if(isset($_POST['textarea3'])){ 
		$textarea3 = $_POST['textarea3'];
	}else{ $textarea3 = ""; }

	if(isset($_POST['textfield4'])){ 
		$textfield4 = $_POST['textfield4'];
	}else{ $textfield4 = ""; }
	if(isset($_POST['textarea4'])){ 
		$textarea4 = $_POST['textarea4'];
	}else{ $textarea4 = ""; }

	if(isset($_POST['textfield5'])){ 
		$textfield5 = $_POST['textfield5'];
	}else{ $textfield5 = ""; }
	if(isset($_POST['textarea5'])){ 
		$textarea5 = $_POST['textarea5'];
	}else{ $textarea5 = ""; }

	if(isset($_POST['textfield6'])){ 
		$textfield6 = $_POST['textfield6'];
	}else{ $textfield6 = ""; }
	if(isset($_POST['textarea6'])){ 
		$textarea6 = $_POST['textarea6'];
	}else{ $textarea6 = ""; }

	if(isset($_POST['textfield7'])){ 
		$textfield7 = $_POST['textfield7'];
	}else{ $textfield7 = ""; }
	if(isset($_POST['textarea7'])){ 
		$textarea7 = $_POST['textarea7'];
	}else{ $textarea7 = ""; }

	if(isset($_POST['textfield8'])){ 
		$textfield8 = $_POST['textfield8'];
	}else{ $textfield8 = ""; }
	if(isset($_POST['textarea8'])){ 
		$textarea8 = $_POST['textarea8'];
	}else{ $textarea8 = ""; }


			$textarea = addslashes($textarea);
			$textarea = htmlspecialchars($textarea);
			$textarea = strip_tags($textarea);	
			$textarea = nl2br($textarea);
				
			$textarea2 = addslashes($textarea2);
			$textarea2 = htmlspecialchars($textarea2);
			$textarea2 = strip_tags($textarea2);	
			$textarea2 = nl2br($textarea2);

			$textarea3 = addslashes($textarea3);
			$textarea3 = htmlspecialchars($textarea3);
			$textarea3 = strip_tags($textarea3);	
			$textarea3 = nl2br($textarea3);

			$textarea4 = addslashes($textarea4);
			$textarea4 = htmlspecialchars($textarea4);
			$textarea4 = strip_tags($textarea4);	
			$textarea4 = nl2br($textarea4);

			$textarea5 = addslashes($textarea5);
			$textarea5 = htmlspecialchars($textarea5);
			$textarea5 = strip_tags($textarea5);	
			$textarea5 = nl2br($textarea5);

			$textarea6 = addslashes($textarea6);
			$textarea6 = htmlspecialchars($textarea6);
			$textarea6 = strip_tags($textarea6);	
			$textarea6 = nl2br($textarea6);

			$textarea7 = addslashes($textarea7);
			$textarea7 = htmlspecialchars($textarea7);
			$textarea7 = strip_tags($textarea7);	
			$textarea7 = nl2br($textarea7);

			$textarea8 = addslashes($textarea8);
			$textarea8 = htmlspecialchars($textarea8);
			$textarea8 = strip_tags($textarea8);	
			$textarea8 = nl2br($textarea8);


//echo "$new";
	
   // saving script   
   // get the variables from the URL request string

if($new == 'yes'){
      $query = "INSERT INTO `".$db_table_prefix."ep2` SET   `userId`='$userId', `textfield` = '$textfield', `textarea` = '$textarea', `textfield2` = '$textfield2', `textarea2` = '$textarea2', `textfield3` = '$textfield3', `textarea3` = '$textarea3', `textfield4` = '$textfield4', `textarea4` = '$textarea4', `textfield5` = '$textfield5', `textarea5` = '$textarea5', `textfield6` = '$textfield6', `textarea6` = '$textarea6', `textfield7` = '$textfield7', `textarea7` = '$textarea7', `textfield8` = '$textfield8', `textarea8` = '$textarea8' ";
}
else{
      $query = "UPDATE `".$db_table_prefix."ep2` SET `textfield` = '$textfield', `textarea` = '$textarea', `textfield2` = '$textfield2', `textarea2` = '$textarea2', `textfield3` = '$textfield3', `textarea3` = '$textarea3', `textfield4` = '$textfield4', `textarea4` = '$textarea4', `textfield5` = '$textfield5', `textarea5` = '$textarea5', `textfield6` = '$textfield6', `textarea6` = '$textarea6', `textfield7` = '$textfield7', `textarea7` = '$textarea7', `textfield8` = '$textfield8', `textarea8` = '$textarea8' WHERE `userId`='$userId' ";
}
  

 $results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

   // print out the results
   if( $results )
   {
      //echo( "Profile Saved!<br><br>" );
      //echo( "Successfully saved the entry.<br><br><a href='${site_url_link}?page=editprofilemain&pee=ep2'>Back to Profile Editor</a>" );

			//Sends success message to session
			//Shows user success when they are redirected
			$success_msg = "You Have Successfully Updated Your Profile!";
			$_SESSION['success_msg'] = $success_msg;
	  
		//Disables auto refresh for debug stuff
		if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
			echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}editprofilemain/'>";	
		}
   }
 
   else
   {
		//Code used to report mysql error
		$mysql_error_report = "TRUE";
		$sql_query = "$query";
		require "external/mysql_error_report.php";
   }
    
   
?>

<?php
}
else {
	notlogedinmsg();
}



?>



