<?php
global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;

$uriref = $_SERVER['REQUEST_URI'];

$querym = "SELECT * FROM ".$db_table_prefix."friend WHERE ((`userId1`='$userId1' AND `userId2`='$userId2') OR (`userId1`='$userId2' AND `userId2`='$userId1')) LIMIT 1";
// Get total number of rows
	if($result = $mysqli->query("$querym")) {
		$num_rows = $result->num_rows;
		// Get current status from database
		$arr = $result->fetch_all(MYSQLI_BOTH);
		foreach($arr as $row)
		{
			$status1 = $row['status1'];
			$status2 = $row['status2'];
		}
		$result->close();
	}

	//echo "$num_rows -";
if($num_rows == "0"){
	//echo " <a href='${site_url_link}?page=friend/addfriend&userId1=$userId1&userId2=$userId2&uriref=$uriref&addfriend=TRUE'>Add to Friends</a> ";
				echo "<center>
					<form method=\"post\" action=\"${site_url_link}addfriend\">
				";
				// create multi sessions
				if(isset($session_token_num)){
					$session_token_num = $session_token_num + 1;
				}else{
					$session_token_num = "1";
				}
				form_token();
				echo "
						<input type=\"hidden\" name=\"userId1\" value=\"$userId1\">
						<input type=\"hidden\" name=\"userId2\" value=\"$userId2\">
						<input type=\"hidden\" name=\"uriref\" value=\"$uriref\">
						<input type=\"hidden\" name=\"addfriend\" value=\"TRUE\">
						<label title=\"Send\"><input type=\"submit\" value=\"Add Friend\" /></label>
					</form>
				";
				echo "</center>";
}
else{
		// Display Current Friend Status
		if($status1 == "1" || $status2 == "1"){
			if($status1 == "1" && $status2 == "1"){
				echo "Your Friend";
			}else{
				echo "Friend Requested";
			}
		}
}
		
		



?>