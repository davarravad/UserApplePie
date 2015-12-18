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


// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){

// Page header
echo "
                <!-- Page Heading -->
                <div class='row'>
                    <div class='col-lg-12'>
                        <h1 class='page-header'>
                            $websiteName - Register Message 
                        </h1>
                        <ol class='breadcrumb'>
                            <li>
                                <i class='glyphicon glyphicon-cog'></i> Admin Panel 
                            </li>
							<li class='active'>
								<i class='fa fa-fw fa-envelope'></i> Register Message
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

	if(isset($_POST['save'])){ $save = $_REQUEST['save']; }else{ $save = ""; }

	global $mysqli, $db_table_prefix, $websiteUrl;
	
	if($save == 'save'){
	//Check to see is site is demo site.  If so disable editing.
	if($cur_server_name_dc != $demo_server_name_dc){
		
		if(isset($_POST['id'])){ $id = $_REQUEST['id']; }else{ $id = ""; }
		if(isset($_POST['sub'])){ $sub = $_REQUEST['sub']; }else{ $sub = ""; }
		if(isset($_POST['con'])){ $con = $_REQUEST['con']; }else{ $con = ""; }
	 
		$con = htmlspecialchars($con);
		$con = strip_tags($con);	
		$con = addslashes($con);
		$con = nl2br($con);		
		
		//echo "<hr>$id1 = $id2<hr>";
		
		// First Set
		if(!empty($id))
		{
			$stmt = $DBH->prepare("UPDATE ".$db_table_prefix."admin_message SET sub=?, con=? WHERE id=?");
			$stmt->bindParam(1, $sub);
			$stmt->bindParam(2, $con);
			$stmt->bindParam(3, $id);
			if (!$stmt->execute()) {
			   err_message("Error Saving Information to Database!");
			   die;
			}
			$DBH = null;
		}
		else
		{
			$stmt = $DBH->prepare("INSERT INTO ".$db_table_prefix."admin_message SET sub=?, con=?");
			$stmt->bindParam(1, $sub);
			$stmt->bindParam(2, $con);
			if (!$stmt->execute()) {
			   err_message("Error Saving Information to Database!");
			   die;
			}
			$DBH = null;
		}


		// No errors, lets redirect admin back
		//Sends success message to session
		//Shows user success when they are redirected
		$success_msg = "Successfully Updated New Member Messages!";
		$_SESSION['success_msg'] = $success_msg;
		
		//Disables auto refresh for debug stuff
		if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
			//Redirects the user
			$form_redir_link = "${websiteUrl}UAP_Admin_Panel/admin_wm/";
			// Redirect member to their post
			header("Location: $form_redir_link");
			exit;
		}
	}
	}else{
		echo "<div class='panel panel-info'>";
			echo "<div class='panel-heading'>";
				echo "Admin Message for New Members at Registration!";
			echo "</div>";
			echo "<div class='panel-body'>";
				echo "<font color='green' size='1'>";
				echo "Admin Welcome Message to users when they sign up for site.  This message will be sent to their messaging inboxes at time of registration.";
				echo "</font><Br><br>";
				$query = "SELECT * FROM ".$db_table_prefix."admin_message WHERE `id`='1' ";
				if($result = $DBH->query($query)){
					while ($row = $result->fetch(PDO::FETCH_ASSOC)) {
						$id = $row['id'];
						$sub = $row['sub'];
						$con = $row['con'];
					}
				}
				if(!isset($sub)){ $sub = ""; }
				if(!isset($con)){ $con = ""; }
			
				$con = stripslashes($con);
				$con = stripslashes($con);
				$con = stripslashes($con);
				$con = str_replace("<br />", "", $con );

				echo "<form method='post' action='${site_url_link}UAP_Admin_Panel/admin_wm/'>";
				echo "<input type='hidden' name='save' value='save'>";
				// See if this is first time admin is using this func
				if(!empty($id)){
					echo "<input type='hidden' name='id' value='1'>";
				}
				echo "<label>Subject:</label>";
				echo "<input name='sub' type='text' size='40' maxlength='50' value='${sub}' class='form-control input-sm'><br>";
				echo "<label>Message Content:</label><br>";
				echo "<textarea name='con' cols='50' rows='10' class='form-control'>${con}</textarea><br>";
				echo "<Br><Br>";
				echo "<input type='submit' value='Save Message' class='btn btn-success btn-sm'/>";
				echo "</form>";
			echo "</div>";
		echo "</div>";

		//Un Set Vars
		unset($id, $sub, $con);

	}
}else{
	echo "Admin Only.";
	exit();
}

?>
