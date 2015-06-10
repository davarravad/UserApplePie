<?

	if(isUserLoggedIn()){

		if(is_admin()) {


	echo "<center>";
	echo "<strong>Admin Zone - Message To ALL!!!</strong>"; 
	echo "</center><br><Br>";

		if(isset($_POST['id'])){ $id = $_REQUEST['id']; }else{ $id = ""; } 
		if(isset($_POST['save'])){ $save = $_REQUEST['save']; }else{ $save = ""; }

if($save == 'save'){

	if($id == '1'){

		if(isset($_POST['adminID'])){ $adminID = $_REQUEST['adminID']; }else{ $adminID = ""; }
		if(isset($_POST['adminuser'])){ $adminuser = $_REQUEST['adminuser']; }else{ $adminuser = ""; }
		if(isset($_POST['admincontent'])){ $admincontent = $_REQUEST['admincontent']; }else{ $admincontent = ""; }
	 	if(isset($_POST['adminshow'])){ $adminshow = $_REQUEST['adminshow']; }else{ $adminshow = ""; }
     
			$admincontent = htmlspecialchars($admincontent);
			$admincontent = strip_tags($admincontent);	
			$admincontent = addslashes($admincontent);
			$admincontent = nl2br($admincontent);	
   
			if(isset($id))
			{
				$query = "UPDATE ".$db_table_prefix."admin SET `adminID`='$adminID',`adminuser`='$adminuser',`admincontent`='$admincontent',`adminshow`='$adminshow' WHERE `id`='$id' ";
			}
			else
			{
				$query = "INSERT INTO ".$db_table_prefix."admin SET `adminID`='$adminID',`adminuser`='$adminuser',`admincontent`='$admincontent',`adminshow`='$adminshow' ";
			}
  
			$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

			if( $results )
			{
				echo( "Admin Submit<br><br>" );
				echo( "Successfully saved the entry." );
			}
 			else
			{
				//Code used to report mysql error
				$mysql_error_report = "TRUE";
				$sql_query = "$query";
				require "models/mysql_error_report.inc";
			}
	}//end check 1


	if($id == '2'){

		if(isset($_POST['adminID'])){ $adminID = $_REQUEST['adminID']; }else{ $adminID = ""; }
		if(isset($_POST['adminuser'])){ $adminuser = $_REQUEST['adminuser']; }else{ $adminuser = ""; }
		if(isset($_POST['admincontent'])){ $admincontent = $_REQUEST['admincontent']; }else{ $admincontent = ""; }
	 	if(isset($_POST['adminshow'])){ $adminshow = $_REQUEST['adminshow']; }else{ $adminshow = ""; }
     
			$admincontent = htmlspecialchars($admincontent);
			$admincontent = strip_tags($admincontent);	
			$admincontent = addslashes($admincontent);
			$admincontent = nl2br($admincontent);	
   
			if(isset($id))
			{
				$query = "UPDATE ".$db_table_prefix."admin SET `adminID`='$adminID',`adminuser`='$adminuser',`admincontent`='$admincontent',`adminshow`='$adminshow' WHERE `id`='$id' ";
			}
			else
			{
				$query = "INSERT INTO ".$db_table_prefix."admin SET `adminID`='$adminID',`adminuser`='$adminuser',`admincontent`='$admincontent',`adminshow`='$adminshow' ";
			}
  
			$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

			if( $results )
			{
				echo( "Admin Submit<br><br>" );
				echo( "Successfully saved the entry." );
			}
 			else
			{
				//Code used to report mysql error
				$mysql_error_report = "TRUE";
				$sql_query = "$query";
				require "models/mysql_error_report.inc";
			}
	}//end check 2

	
}
else{

		echo "<strong>Admin Message for Logged In users!</strong>";
   		$query = "SELECT * FROM ".$db_table_prefix."admin WHERE `id`='1' ";
		$result = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

		if( $result && $contact = mysqli_fetch_object( $result ) )
		{
			$id = $contact -> id;
			$adminID = $contact -> adminID;
			$adminuser = $contact -> adminuser;
			$admincontent = $contact -> admincontent;
			$adminshow = $contact -> adminshow;
		}
		if(!isset($adminID)){ $adminID = ""; }
		if(!isset($adminuser)){ $adminuser = ""; }
		if(!isset($admincontent)){ $admincontent = ""; }
	 	if(!isset($adminshow)){ $adminshow = ""; }
		
			$admincontent = stripslashes($admincontent);
			$admincontent = stripslashes($admincontent);
			$admincontent = stripslashes($admincontent);
			$admincontent = str_replace("<br />", "", $admincontent );

?>

	<form method="post" action="<? echo "${site_url_link}"; ?>YummyAsPie/adminmessage/">
	
	<input type='hidden' name='save' value='save'>
	<input type='hidden' name='id' value='1'>
	
	<label>Admin ID Name:</label><Br>
	<input name="adminID" type="text" size="11" maxlength="10" value="<? echo "$adminID"; ?>"><br>
	<input name="adminuser" type="text" size="40" maxlength="50" value="<? echo "$adminuser"; ?>"><br>
	<label>Message Content:</label><br><textarea name="admincontent" cols="50" rows="10"><?php echo "$admincontent"; ?></textarea><br>
	<select name="adminshow" id="adminshow">
	<option value="yes" <?php if($adminshow == 'yes'){echo "SELECTED";} ?>>Show Message</option>
	<option value="no" <?php if($adminshow == 'no'){echo "SELECTED";} ?>>Hide Message</option>
	</select>
	<Br><Br>
	<label title="Send"><input type="submit" value="Save Message" /></label>
	</form>

	<?

	//Un Set Vars
	unset($id, $adminID, $adminuser, $admincontent, $adminshow);


		echo "<hr><strong>Admin Message for not logged in users!</strong>";
   		$query = "SELECT * FROM ".$db_table_prefix."admin WHERE `id`='2' ";
		$result = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

		if( $result && $contact = mysqli_fetch_object( $result ) )
		{
			$id = $contact -> id;
			$adminID = $contact -> adminID;
			$adminuser = $contact -> adminuser;
			$admincontent = $contact -> admincontent;
			$adminshow = $contact -> adminshow;
		}
		if(!isset($adminID)){ $adminID = ""; }
		if(!isset($adminuser)){ $adminuser = ""; }
		if(!isset($admincontent)){ $admincontent = ""; }
	 	if(!isset($adminshow)){ $adminshow = ""; }
		
			$admincontent = stripslashes($admincontent);
			$admincontent = stripslashes($admincontent);
			$admincontent = stripslashes($admincontent);
			$admincontent = str_replace("<br />", "", $admincontent );


?>

	<form method="post" action="<? echo "${site_url_link}"; ?>YummyAsPie/adminmessage/">
	
	<input type='hidden' name='save' value='save'>
	<input type='hidden' name='id' value='2'>
	
	<label>Admin ID Name:</label><Br>
	<input name="adminID" type="text" size="11" maxlength="10" value="<? echo "$adminID"; ?>"><br>
	<input name="adminuser" type="text" size="40" maxlength="50" value="<? echo "$adminuser"; ?>"><br>
	<label>Message Content:</label><br><textarea name="admincontent" cols="50" rows="10"><?php echo "$admincontent"; ?></textarea><br>
	<select name="adminshow" id="adminshow">
	<option value="yes" <?php if($adminshow == 'yes'){echo "SELECTED";} ?>>Show Message</option>
	<option value="no" <?php if($adminshow == 'no'){echo "SELECTED";} ?>>Hide Message</option>
	</select>
	<Br><Br>
	<label title="Send"><input type="submit" value="Save Message" /></label>
	</form>

	
	
<?

	//Un Set Vars
	unset($id, $adminID, $adminuser, $admincontent, $adminshow);

}

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
