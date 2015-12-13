<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Displays a message to users that was set by admin

if(isUserLoggedIn())
{
//Shows to logged in users

	//Check to see if user wants this message hidden
	if(isset($_POST['hide_admin_msg_lin'])){ $hide_admin_msg_lin = $_POST['hide_admin_msg_lin']; }else{ $hide_admin_msg_lin = ""; }
	if(isset($_SESSION['hide_admin_msg_lin_SES'])){ $hide_admin_msg_lin_SES = $_SESSION['hide_admin_msg_lin_SES']; }else{ $hide_admin_msg_lin_SES = ""; }
	
	if($hide_admin_msg_lin == 'TRUE'){
		$_SESSION['hide_admin_msg_lin_SES'] = "TRUE";
		$redir_link_url = "";
		
		// Redirect member to their post
		header("Location: $redir_link_url");
		exit;
	}
	if($hide_admin_msg_lin_SES == 'TRUE'){}else{
	
		//Check to see if admin message is set to show.  If TRUE then show it.  Else hide it.
		global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;
		
   		$query = "SELECT * FROM `".$db_table_prefix."admin` WHERE `id`='1' AND `adminshow`='TRUE' ";
		
		// Get all Information from database
		$result = $mysqli->query($query);
		$arr_am = $result->fetch_all(MYSQLI_BOTH);
		foreach($arr_am as $row_am)
		{
			$id = $row_am['id'];
			$adminID = $row_am['adminID'];
			$adminuser = $row_am['adminuser'];
			$admincontent = $row_am['admincontent'];
			$adminshow = $row_am['adminshow'];
			$timestamp = $row_am['timestamp'];
		
			if(!isset($adminID)){ $adminID = ""; }
			if(!isset($adminuser)){ $adminuser = ""; }
			if(!isset($admincontent)){ $admincontent = ""; }
			if(!isset($adminshow)){ $adminshow = ""; }
			
			// Check to make sure we are not showing visitors a blank message.
			if(!empty($admincontent) && $adminshow == "TRUE"){
				echo "<div class='col-lg-12'>";
				echo "<div class='panel panel-info'>";
					echo "<div class='panel-heading'>";
					echo "Admin Message";
					echo "</div>";

					$admincontent = stripslashes($admincontent);
					echo "<div class='panel-body'>";
						echo "$admincontent";
					echo "</div>";
						//Display how long ago this was posted
						$timestart = "$timestamp";  //Time of post
						require_once "models/timediff.inc";
					echo "<div class='panel-footer'>";
						echo "<table width='100%'><tr>";
							echo "<td width='50%' style='text-align: left'>";
								echo " Posted " . dateDiff("now", "$timestart", 1) . " ago ";
							echo "</td>";
							echo "<td width='50%' style='text-align: right'>";
								echo "<form method=\"post\" action=\"\" onsubmit=\"submit.disabled = true; return true;\">";
								echo "<input type='hidden' name='hide_admin_msg_lin' value='TRUE'>"; 
								echo "<input type=\"submit\" class=\"btn btn-info btn-sm\" value=\"Hide This Message\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" />";
								echo "</form>";
							echo "</td>";
						echo "</tr></table>";
					echo "</div>";
				echo "</div>";
				echo "</div>";
			}
			
			//Un Set Vars
			unset($timestamp, $id, $adminID, $adminuser, $admincontent, $adminshow, $A_ID02, $timestart);
		}	
	}
}else{
//Shows to all NOT logged in users

	//Check to see if user wants this message hidden
	if(isset($_POST['hide_admin_msg_lou'])){ $hide_admin_msg_lou = $_POST['hide_admin_msg_lou']; }else{ $hide_admin_msg_lou = ""; }
	if(isset($_SESSION['hide_admin_msg_lou_SES'])){ $hide_admin_msg_lou_SES = $_SESSION['hide_admin_msg_lou_SES']; }else{ $hide_admin_msg_lou_SES = ""; }
	
	if($hide_admin_msg_lou == 'TRUE'){
		$_SESSION['hide_admin_msg_lou_SES'] = "TRUE";
		$redir_link_url = "";
		
		// Redirect member to their post
		header("Location: $redir_link_url");
		exit;
	}
	if($hide_admin_msg_lou_SES == 'TRUE'){}else{
		global $mysqli, $site_url_link, $site_forum_title;
		
		$query = "SELECT * FROM `".$db_table_prefix."admin` WHERE `id`='2' AND `adminshow`='TRUE' ";
		
		// Get all information from database
		$result = $mysqli->query($query);
		$arr_am = $result->fetch_all(MYSQLI_BOTH);
		foreach($arr_am as $row_am)
		{
			$id = $row_am['id'];
			$adminID = $row_am['adminID'];
			$adminuser = $row_am['adminuser'];
			$admincontent = $row_am['admincontent'];
			$adminshow = $row_am['adminshow'];
			$timestamp = $row_am['timestamp'];
		
			if(!isset($adminID)){ $adminID = ""; }
			if(!isset($adminuser)){ $adminuser = ""; }
			if(!isset($admincontent)){ $admincontent = ""; }
			if(!isset($adminshow)){ $adminshow = ""; }
			
			// Check to make sure we are not showing memebers a blank message.
			if(!empty($admincontent) && $adminshow == "TRUE"){
				echo "<div class='col-lg-12'>";
				echo "<div class='panel panel-info'>";
					echo "<div class='panel-heading'>";
					echo "Admin Message";
					echo "</div>";

					$admincontent = stripslashes($admincontent);
					echo "<div class='panel-body'>";
						echo "$admincontent";
					echo "</div>";
						//Display how long ago this was posted
						$timestart = "$timestamp";  //Time of post
						require_once "models/timediff.inc";
					echo "<div class='panel-footer'>";
						echo "<table width='100%'><tr>";
							echo "<td width='50%' align='left' valign='middle'>";
								echo " Posted " . dateDiff("now", "$timestart", 1) . " ago ";
							echo "</td>";
							echo "<td width='50%' align='right' valign='middle'>";
								echo "<form method=\"post\" action=\"\" onsubmit=\"submit.disabled = true; return true;\">";
								echo "<input type='hidden' name='hide_admin_msg_lou' value='TRUE'>"; 
								echo "<input type=\"submit\" class=\"btn btn-info btn-sm\" value=\"Hide This Message\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" />";
								echo "</form>";
							echo "</td>";
						echo "</tr></table>";
					echo "</div>";
				echo "</div>";
				echo "</div>";
			}
			
			//Un Set Vars
			unset($timestamp, $id, $adminID, $adminuser, $admincontent, $adminshow, $A_ID02, $timestart);

		}
	}

}
?>