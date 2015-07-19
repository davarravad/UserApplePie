<?php
if(isUserLoggedIn())
{

if(isset($_POST['delete_vp'])){ $delete_vp = $_POST['delete_vp']; }else{$delete_vp = "";}
if(isset($_POST['update_vp'])){ $update_vp = $_POST['update_vp']; }else{$update_vp = "";}


if($update_vp == 'yes'){

	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{

if(isset($_POST['vehicle_id'])){ $vehicle_id = $_POST['vehicle_id']; }else{ $vehicle_id = ""; }
$type = $_POST['type'];
$veh_type = $_POST['veh_type'];
$year = $_POST['year'];
$make = $_POST['make'];
$model = $_POST['model'];
$engine = $_POST['engine'];
$color = $_POST['color'];
$content1 = $_POST['content1'];
$content2 = $_POST['content2'];
$content3 = $_POST['content3'];
$content4 = $_POST['content4'];
if(isset($_POST['youtube1'])){ $youtube1 = $_POST['youtube1']; }else{ $youtube1 = ""; }
$int = $_POST['int'];

			$content1 = htmlspecialchars($content1);
			$content1 = strip_tags($content1);	
			$content1 = addslashes($content1);
			$content1 = nl2br($content1);	

			$content2 = htmlspecialchars($content2);
			$content2 = strip_tags($content2);	
			$content2 = addslashes($content2);
			$content2 = nl2br($content2);	

			$content3 = htmlspecialchars($content3);
			$content3 = strip_tags($content3);	
			$content3 = addslashes($content3);
			$content3 = nl2br($content3);	

			$content4 = htmlspecialchars($content4);
			$content4 = strip_tags($content4);	
			$content4 = addslashes($content4);
			$content4 = nl2br($content4);	

			//$youtube1 = str_replace('<iframe width="420" height="315" src="', "", "$youtube1");
			//$youtube1 = str_replace('" frameborder="0" allowfullscreen></iframe>', "", "$youtube1");

		$query = "UPDATE `submit` SET `veh_type`='$veh_type',`type`='$type',`year`='$year',`make`='$make',`model`='$model',`engine`='$engine',`color`='$color',`content1`='$content1',`content2`='$content2',`content3`='$content3',`content4`='$content4', `youtube1`='$youtube1' WHERE `int`='$int' ";

		$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query )
			or die ("Couldn't ececute query. 852");
		if( $results ){
			//echo "Vehicle Profile Updated!";
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Updated a Vehicle Profile!";
					$_SESSION['success_msg'] = $success_msg;
			echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}editprofilemain/editvehicles/#profile$int'>";
		}else{
			//Code used to report mysql error
			$mysql_error_report = "TRUE";
			$sql_query = "$query";
			require "models/mysql_error_report.inc";
		}
}
}



if($delete_vp == 'yes'){

      $int = $_POST['int'];
      if(isset($_POST['yes'])){ $yes = $_POST['yes']; }else{ $yes = ""; }

	if($yes == 'yes'){

	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{


	$userone = $nname;



      $int = $_POST['int'];

 

	$query = "SELECT * FROM `submit` WHERE `int`='$int' ";

	$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 564512");
		
	while ($row = mysqli_fetch_array($result))
	{
		extract($row);
		//echo "<br>Owner = $userId<br>";
		//echo "Image = $imgname";
	}



	if($userId == $idofuser) {


 
      $query = "DELETE FROM `submit` WHERE `int`='$int' LIMIT 1";

 $results = mysqli_query($GLOBALS["___mysqli_ston"], $query);

   // print out the results
   if( $results )
   {

					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Deleted a Vehicle Profile!";
					$_SESSION['success_msg'] = $success_msg;
   
		if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
			echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}editprofilemain/editvehicles/'>";
		}

   }
 
   else
   {
		//Code used to report mysql error
		$mysql_error_report = "TRUE";
		$sql_query = "$query";
		require "models/mysql_error_report.inc";
   }
    
  

	}
	else {
		echo "<Br><br>The content you are trying to request is not yours!";
	}
	}  //end token

	}
	else {
		echo "<br>Are you sure you would like to delete that?<Br>";

				echo "<center>
					<form method=\"post\" action=\"${site_url_link}editprofilemain/editvehicles/\">
				";
					//Form token. Place within from tag
					// create multi sessions
					if(isset($session_token_num)){
						$session_token_num = $session_token_num + 1;
					}else{
						$session_token_num = "1";
					}
					form_token();
				echo "
						<input type=\"hidden\" name=\"delete_vp\" value=\"yes\">
						<input type=\"hidden\" name=\"int\" value=\"$int\">
						<input type=\"hidden\" name=\"yes\" value=\"yes\">
						<label title=\"Send\"><input type=\"submit\" value=\"YES\" /></label>
					</form>
				";
				echo "</center>";
				$taz_backz = "
					<form method=\"post\" action=\"${site_url_link}editprofilemain/editvehicles/\">
						<label title=\"Send\"><input type=\"submit\" value=\"NO\" /></label>
					</form>
				";
				echo "<center>$taz_backz</center>";
		

	}


}
else {



$query = "SELECT * FROM submit WHERE `usrida`='$userId' ";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query.  5641321");

	echo " <center>( <a href='${site_url_link}SubmitVehicleProfile/'>Create New Vehicle Profile</a> ) <br><br>";


while ($row = mysqli_fetch_array($result))
{

	$bgcolor = "epboxa";

	extract($row);

	$content1 = stripslashes($content1);
	$content1 = stripslashes($content1);
	$content1 = str_replace("<br />", "", $content1); 

	$content2 = stripslashes($content2);
	$content2 = stripslashes($content2);
	$content2 = str_replace("<br />", "", $content2); 

	$content3 = stripslashes($content3);
	$content3 = stripslashes($content3);
	$content3 = str_replace("<br />", "", $content3); 

	$content4 = stripslashes($content4);
	$content4 = stripslashes($content4);
	$content4 = str_replace("<br />", "", $content4); 

		echo "<a class='anchor' name='profile$int'></a>";
			$vehicle_id = "$int";
		echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td colspan='3' class='epbox'>";
		echo "<center>";
			require "pages/profile/vehicleid.inc";
		echo "</center>";
		echo "</td></tr><tr><td class=$bgcolor width='200' align=center>";
		echo "<form method=\"post\" action=\"${site_url_link}editprofilemain/editvehicles/\">";
					//Form token. Place within from tag
					// create multi sessions
					if(isset($session_token_num)){
						$session_token_num = $session_token_num + 1;
					}else{
						$session_token_num = "1";
					}
					form_token();
				echo "
					<table><tr><td>
						<strong>Type</strong></td><td><input name=\"type\" type=\"text\" size=\"25\" maxlength=\"50\" value=\"$type\"></td></tr><tr><td>				
						<strong>Year</strong></td><td><input name=\"year\" type=\"text\" size=\"25\" maxlength=\"50\" value=\"$year\"></td></tr><tr><td>
						<strong>Make</strong></td><td><input name=\"make\" type=\"text\" size=\"25\" maxlength=\"50\" value=\"$make\"></td></tr><tr><td>
						<strong>Model</strong></td><td><input name=\"model\" type=\"text\" size=\"25\" maxlength=\"50\" value=\"$model\"></td></tr><tr><td>
						<strong>Engine</strong></td><td><input name=\"engine\" type=\"text\" size=\"25\" maxlength=\"50\" value=\"$engine\"></td></tr><tr><td>
						<strong>Color</strong></td><td><input name=\"color\" type=\"text\" size=\"25\" maxlength=\"50\" value=\"$color\">				
					</td></tr></table>	
				";

				echo "<input name=\"veh_type\" type=\"radio\" value=\"Custom\"  "; 
				if($veh_type == "Custom"){ echo "CHECKED"; }
				echo "/>Custom - ";
				echo "<input name=\"veh_type\" type=\"radio\" value=\"Classic\" ";
				if($veh_type == "Classic"){ echo "CHECKED"; }
				echo "/>Classic<br>";
				echo "<input name=\"veh_type\" type=\"radio\" value=\"Both\" ";
				if($veh_type == "Both"){ echo "CHECKED"; }
				echo "/>Classic and Custom";
				
		echo "</td><td class=$bgcolor align=center width=300>";

				echo "

						<textarea name=\"content1\" cols=\"50\" rows=\"2\">$content1</textarea>
						<textarea name=\"content2\" cols=\"50\" rows=\"2\">$content2</textarea>
						<textarea name=\"content3\" cols=\"50\" rows=\"2\">$content3</textarea>
						<textarea name=\"content4\" cols=\"50\" rows=\"2\">$content4</textarea>
				";
						//YouTube Video Embed Code
						//<textarea name=\"youtube1\" cols=\"50\" rows=\"2\">$youtube1</textarea>
				echo "
						<input type=\"hidden\" name=\"update_vp\" value=\"yes\">
						<input type=\"hidden\" name=\"int\" value=\"$int\">
				";


				
		echo "</td><td class=$bgcolor align=center width=200>";
	
				echo "<a href='${site_url_link}VehicleProfile/$int/'>View Vehicle Profile</a><br><br>";
				echo "<font size=1px>Only updates one profile at a time.</font><Br>";
				echo "
						<label title=\"Send\"><input type=\"submit\" value=\"Update This Profile\" /></label>
					</form>
				";
				$taz_b1 = "
					<form method=\"post\" action=\"${site_url_link}?page=editprofilemain&pee=editvehicles\">
						<input type=\"hidden\" name=\"delete_vp\" value=\"yes\">
						<input type=\"hidden\" name=\"int\" value=\"$int\">
						<label title=\"Send\"><input type=\"submit\" value=\"Delete This Profile\" /></label>
					</form>
				";
				echo "$taz_b1";
				echo "</td></tr></table><br>";

}
				echo " ( <a href='${site_url_link}SubmitVehicleProfile/'>Create New Vehicle Profile</a> ) </center>";
}


}
else {
	notlogedinmsg();
}

?>