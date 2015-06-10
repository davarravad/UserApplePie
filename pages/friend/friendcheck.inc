<?

$uriref = $_SERVER['REQUEST_URI'];

$querym = "SELECT * FROM friend WHERE ((`userId1`='$userId1' AND `userId2`='$userId2') OR (`userId1`='$userId2' AND `userId2`='$userId1')) LIMIT 1";
$resultm = mysqli_query($GLOBALS["___mysqli_ston"], $querym);
	//or die ("Couldn't ececute query.");

$num_rows = mysqli_num_rows($resultm);


	//echo "$num_rows -";
if($num_rows == 0){
	//echo " <a href='${site_url_link}?page=friend/addfriend&userId1=$userId1&userId2=$userId2&uriref=$uriref&addfriend=TRUE'>Add to Friends</a> ";
				echo "<center>
					<form method=\"post\" action=\"${site_url_link}?page=friend/addfriend\">
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
		
	while ($rowm = mysqli_fetch_array($resultm))
	{
		extract($rowm);	

		//echo "$userId1 - $userId2 - $status1 - $status2 <br>";
		if($status1 == "1"){
			if($status2 == "1"){
				echo "Your Friend";
			}else{
				echo "Friend Requested";
			}
		}
		

	}

}
		
		



?>