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

// Admin Message Script
// Allows admin to display a
// Message to all users

// Make sure user is Logged In and an Admin
if(isUserLoggedIn() && is_admin()){
	
// Page header
echo "
                <!-- Page Heading -->
                <div class='row'>
                    <div class='col-lg-12'>
                        <h1 class='page-header'>
                            $websiteName - Site Message 
                        </h1>
                        <ol class='breadcrumb'>
                            <li>
                                <i class='glyphicon glyphicon-cog'></i> Admin Panel 
                            </li>
							<li class='active'>
								<i class='fa fa-fw fa-desktop'></i> Site Message
							</li>
                        </ol>
                    </div>
                </div>
                <!-- /.row -->
";

//Check to see is site is demo site.  If so disable editing.
if($cur_server_name_dc == $demo_server_name_dc){
	err_message("Demo Site : Editing Disabled"); 
}

	if(isset($_POST['id1'])){ $id1 = $_REQUEST['id1']; }else{ $id1 = ""; } 
	if(isset($_POST['id2'])){ $id2 = $_REQUEST['id2']; }else{ $id2 = ""; } 
	if(isset($_POST['save'])){ $save = $_REQUEST['save']; }else{ $save = ""; }

	global $mysqli, $db_table_prefix, $websiteUrl;
	
	if($save == 'save'){
	//Check to see is site is demo site.  If so disable editing.
	if($cur_server_name_dc != $demo_server_name_dc){
		
		if(isset($_POST['adminID'])){ $adminID = $_REQUEST['adminID']; }else{ $adminID = ""; }
		if(isset($_POST['adminuser'])){ $adminuser = $_REQUEST['adminuser']; }else{ $adminuser = ""; }
		if(isset($_POST['admincontent'])){ $admincontent = $_REQUEST['admincontent']; }else{ $admincontent = ""; }
		if(isset($_POST['adminshow'])){ $adminshow = $_REQUEST['adminshow']; }else{ $adminshow = ""; }
		
		if(isset($_POST['adminID2'])){ $adminID2 = $_REQUEST['adminID2']; }else{ $adminID2 = ""; }
		if(isset($_POST['adminuser2'])){ $adminuser2 = $_REQUEST['adminuser2']; }else{ $adminuser2 = ""; }
		if(isset($_POST['admincontent2'])){ $admincontent2 = $_REQUEST['admincontent2']; }else{ $admincontent2 = ""; }
		if(isset($_POST['adminshow2'])){ $adminshow2 = $_REQUEST['adminshow2']; }else{ $adminshow2 = ""; }
	 
		$admincontent = htmlspecialchars($admincontent);
		$admincontent = strip_tags($admincontent);	
		$admincontent = addslashes($admincontent);
		$admincontent = nl2br($admincontent);	
		
		$admincontent2 = htmlspecialchars($admincontent2);
		$admincontent2 = strip_tags($admincontent2);	
		$admincontent2 = addslashes($admincontent2);
		$admincontent2 = nl2br($admincontent2);	
		
		//echo "<hr>$id1 = $id2<hr>";
		
		// First Set
		if(!empty($id1))
		{
			$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."admin SET adminID=?, adminuser=?, admincontent=?, adminshow=? WHERE id=?");
			$stmt->bind_param("isssi", $adminID, $adminuser, $admincontent, $adminshow, $id1);
			if (!$stmt->execute()) {
			   err_message("Error Saving Information to Database!");
			   die;
			}
			$stmt->close();
		}
		else
		{
			$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."admin SET adminID=?, adminuser=?, admincontent=?, adminshow=?");
			$stmt->bind_param("isss", $adminID, $adminuser, $admincontent, $adminshow);
			if (!$stmt->execute()) {
			   err_message("Error Saving Information to Database!");
			   die;
			}
			$stmt->close();
		}

		// Second set
		if(!empty($id2))
		{
			$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."admin SET adminID=?, adminuser=?, admincontent=?, adminshow=? WHERE id=?");
			$stmt->bind_param("isssi", $adminID2, $adminuser2, $admincontent2, $adminshow2, $id2);
			if (!$stmt->execute()) {
			   err_message("Error Saving Information to Database!");
			   die;
			}
			$stmt->close();
		}
		else
		{
			$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."admin SET adminID=?, adminuser=?, admincontent=?, adminshow=?");
			$stmt->bind_param("isss", $adminID2, $adminuser2, $admincontent2, $adminshow2);
			if (!$stmt->execute()) {
			   err_message("Error Saving Information to Database!");
			   die;
			}
			$stmt->close();
		}
		// No errors, lets redirect admin back
		//Sends success message to session
		//Shows user success when they are redirected
		$success_msg = "Successfully Updated Admin Messages!";
		$_SESSION['success_msg'] = $success_msg;
		
		//Disables auto refresh for debug stuff
		if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
			//Redirects the user
			$form_redir_link = "${websiteUrl}UAP_Admin_Panel/adminmessage/";
			// Redirect member to their post
			header("Location: $form_redir_link");
			exit;
		}
	}else{ err_message("Demo Site : Editing Disabled"); }
	}else{
	
		$user_disp_name = get_up_info_mem_disp_name($userId);
		
		echo "<div class='panel panel-info'>";
			echo "<div class='panel-heading'>";
				echo "Admin Message for Logged In users!";
			echo "</div>";
			echo "<div class='panel-body'>";
				echo "<font color='green' size='1'>";
				echo "This message is displayed to all members that are logged into this website.  Members can hide this message after they read it.";
				echo "</font><hr>";

				$query = "SELECT * FROM ".$db_table_prefix."admin WHERE `id`='1' ";
				if($result = $mysqli->query($query)){
					while ($row = $result->fetch_assoc()) {
						$id1 = $row['id'];
						$adminID = $row['adminID'];
						$adminuser = $row['adminuser'];
						$admincontent = $row['admincontent'];
						$adminshow = $row['adminshow'];
					}
				}
				if(!isset($adminID)){ $adminID = "$userId"; }
				if(!isset($adminuser)){ $adminuser = "$user_disp_name"; }
				if(!isset($admincontent)){ $admincontent = ""; }
				if(!isset($adminshow)){ $adminshow = ""; }
			
				$admincontent = stripslashes($admincontent);
				$admincontent = stripslashes($admincontent);
				$admincontent = stripslashes($admincontent);
				$admincontent = str_replace("<br />", "", $admincontent );

				echo "<form method='post' action='${site_url_link}UAP_Admin_Panel/adminmessage/'>";
					echo "<input type='hidden' name='save' value='save'>";
					echo "<input type='hidden' name='adminID' value='${adminID}'>";
					echo "<input type='hidden' name='adminuser' value='${adminuser}'>";
					// See if this is first time admin is using this func
					if(!empty($id1)){
						echo "<input type='hidden' name='id1' value='1'>";
					}
					echo "<label>Message Content:</label><br>";
					echo "<textarea name='admincontent' cols='50' rows='10' class='form-control'>${admincontent}</textarea><br>";
					echo "<select name='adminshow' id='adminshow' class='form-control'>";
						if(empty($adminshow)){
							$as1 = "";
							$as2 = "SELECTED";
						}else{
							if($adminshow == 'TRUE'){$as1 = "SELECTED";}else{$as1 = "";}
							if($adminshow == 'FALSE'){$as2 = "SELECTED";}else{$as2 = "";}
						}
						echo "<option value='TRUE' $as1>Show Message</option>";
						echo "<option value='FALSE' $as2>Hide Message</option>";
					echo "</select>";
			echo "</div>";
			echo "<div class='panel-footer' style='text-align: right'>";
				echo "<button type='submit' class='btn btn-success btn-md'  data-loading-text='Please wait...' >Save</button>";
			echo "</div>";
		echo "</div>";
		
		echo "<div class='panel panel-info'>";
			echo "<div class='panel-heading'>";
				echo "Admin Message for NOT Logged in users!";
			echo "</div>";
			echo "<div class='panel-body'>";
				echo "<font color='green' size='1'>";
				echo "This message is displayed to all visitors that are NOT Logged into this website. ";
				echo "</font><br>";
				echo "<br>";
				$query2 = "SELECT * FROM ".$db_table_prefix."admin WHERE `id`='2' ";
				if($result2 = $mysqli->query($query2)){
					while ($row2 = $result2->fetch_assoc()) {
						$id2 = $row2['id'];
						$adminID2 = $row2['adminID'];
						$adminuser2 = $row2['adminuser'];
						$admincontent2 = $row2['admincontent'];
						$adminshow2 = $row2['adminshow'];
					}
				}
				if(!isset($adminID2)){ $adminID2 = "$userId"; }
				if(!isset($adminuser2)){ $adminuser2 = "$user_disp_name"; }
				if(!isset($admincontent2)){ $admincontent2 = ""; }
				if(!isset($adminshow2)){ $adminshow2 = ""; }
				
				$admincontent2 = stripslashes($admincontent2);
				$admincontent2 = stripslashes($admincontent2);
				$admincontent2 = stripslashes($admincontent2);
				$admincontent2 = str_replace("<br />", "", $admincontent2 );

					if(!empty($id2)){
						echo "<input type='hidden' name='id2' value='2'>";
					}
					echo "<input type='hidden' name='adminID2' value='${adminID2}'>";
					echo "<input type='hidden' name='adminuser2' value='${adminuser2}'>";
					echo "<label>Message Content:</label><br><textarea name='admincontent2' cols='50' rows='10' class='form-control'>${admincontent2}</textarea><br>";
					echo "<select name='adminshow2' id='adminshow2' class='form-control'>";
						if(empty($adminshow2)){
							$as12 = "";
							$as22 = "SELECTED";
						}else{
							if($adminshow2 == 'TRUE'){$as12 = "SELECTED";}else{$as12 = "";}
							if($adminshow2 == 'FALSE'){$as22 = "SELECTED";}else{$as22 = "";}
						}
						echo "<option value='TRUE' $as12>Show Message</option>";
						echo "<option value='FALSE' $as22>Hide Message</option>";
					echo "</select>";
				
			echo "</div>";
			echo "<div class='panel-footer' style='text-align: right'>";
				echo "<button type='submit' class='btn btn-success btn-md'  data-loading-text='Please wait...' >Save</button>";
			echo "</div>";
		echo "</div>";
		
		// End form
		echo "</form>";
		
		//Un Set Vars
		unset($id, $adminID, $adminuser, $admincontent, $adminshow, $id2, $adminID2, $adminuser2, $admincontent2, $adminshow2);

	}
}else{
	echo "Admin Only.";
	exit();
}

?>
