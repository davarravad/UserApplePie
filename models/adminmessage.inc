<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Displays a message to users that was set by admin

if(isUserLoggedIn())
{
//Shows to logged in users

	//Check to see if user wants this message hidden
	if(isset($_POST['hide_admin_msg'])){ $hide_admin_msg = $_POST['hide_admin_msg']; }else{ $hide_admin_msg = ""; }
	if(isset($_SESSION['hide_admin_msg_SES'])){ $hide_admin_msg_SES = $_SESSION['hide_admin_msg_SES']; }else{ $hide_admin_msg_SES = ""; }
	
	if($hide_admin_msg == 'yes'){
		$_SESSION['hide_admin_msg_SES'] = "yes";
		$redir_link_url = "";
		
		// Redirect member to their post
		header("Location: $redir_link_url");
		exit;
	}
	if($hide_admin_msg_SES == 'yes'){}else{
	
		//Check to see if admin message is set to show.  If yes then show it.  Else hide it.
		global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;
		
   		$query = "SELECT * FROM `".$db_table_prefix."admin` WHERE `id`='1' AND `adminshow`='yes' ";
		
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
			
			echo "<table width='100%' border='0' cellspacing='0' cellpadding='4' align='center'><tr>";
			echo "<td width='100%'  align='center' valign='middle' class='hr2'>";
			echo "Admin Message<br>";
			echo "</td></tr><tr><td width='100%'  align='center' valign='middle' class='content78'>";

			
			echo "<table width='$tblw500' border=0 cellpadding=2 cellspacing=2>";
			echo "<tr>";
			echo "<td valign=top class=epboxa>";
				$A_ID02 = $adminID;
			echo "<div class='comt_nm2'><a href='${site_url_link}member/$A_ID02/'>";
				require "pages/profile/userimage_small.inc";
			echo "</a> Admin Message by ";
			echo "<a href='${site_url_link}member/$A_ID02/'>";
			echo " $adminuser </div>";
			echo "</a>";
			echo "<br>";
			$admincontent = stripslashes($admincontent);
			echo "<div class='comt_cnt'>$admincontent</div>";
				//Display how long ago this was posted
				$timestart = "$timestamp";  //Time of post
				require_once "models/timediff.inc";
			echo "<table width=100%><tr><td>";
				echo " " . dateDiff("now", "$timestart", 1) . " ago ";
			echo "</td><td align=right>";
			echo "<form method=\"post\" action=\"\" onsubmit=\"submit.disabled = true; return true;\">";
			echo "<input type='hidden' name='hide_admin_msg' value='yes'>"; 
			echo "<input type=\"submit\" class=\"sweet\" value=\"Hide This Admin Message\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" />";
			echo "</form>";
			echo "</td></tr></table>";
			
			echo "</td></tr></table>";

			echo "</td></tr></table><br>";
			
			//Un Set Vars
			unset($timestamp, $id, $adminID, $adminuser, $admincontent, $adminshow, $A_ID02, $timestart);
			
		}	
	}
}else{
//Shows to all not logged in users

		//Check to see if admin message is set to show.  If yes then show it.  Else hide it.

		global $mysqli, $site_url_link, $site_forum_title;
		
		$query = "SELECT * FROM `".$db_table_prefix."admin` WHERE `id`='2' AND `adminshow`='yes' ";
		
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
			
			echo "<table width='100%' border='0' cellspacing='0' cellpadding='4' align='center'><tr>";
			echo "<td width='100%'  align='center' valign='middle' class='hr2'>";
			echo "Admin Message<br>";
			echo "</td></tr><tr><td width='100%'  align='center' valign='middle' class='content78'>";

			
			echo "<table width='$tblw500' border=0 cellpadding=2 cellspacing=2>";
			echo "<tr>";
			echo "<td valign=top class=epboxa>";
				$A_ID02 = $adminID;
			echo "<div class='comt_nm2'><a href='${site_url_link}member/$A_ID02/'>";
				require "pages/profile/userimage_small.inc";
			echo "</a> Admin Message by ";
			echo "<a href='${site_url_link}member/$A_ID02/'>";
			echo " $adminuser </div>";
			echo "</a>";
			echo "<br>";
			$admincontent = stripslashes($admincontent);
			echo "<div class='comt_cnt'>$admincontent</div>";
				//Display how long ago this was posted
				$timestart = "$timestamp";  //Time of post
				require_once "models/timediff.inc";
				echo " " . dateDiff("now", "$timestart", 1) . " ago ";

			echo "</td></tr></table>";

			echo "</td></tr></table><br>";
			
			//Un Set Vars
			unset($timestamp, $id, $adminID, $adminuser, $admincontent, $adminshow, $A_ID02, $timestart);

		}


}
?>