<center>
<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isUserLoggedIn())
{

$userIdme = $userId;

	$uriref = $_SERVER['REQUEST_URI'];
	
	$querym = "SELECT * FROM clubmem WHERE `inv_user2`='$userId' AND `status3`='0' AND `inv`='TRUE' AND `inv_approve`='NO'  ";
	$resultm = mysqli_query($GLOBALS["___mysqli_ston"], $querym);
		//or die ("Couldn't ececute query. 8");
	
	$num_rows = mysqli_num_rows($resultm);
	

echo "<table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td class=epbox>";
echo "<strong>Club Invites  ( $num_rows )</strong>";
echo "</td></tr></table>";


	if($num_rows == 0){
		echo "<table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td class=epboxa>";
		echo "No new Club Invites. ";
		echo "</td></tr></table>";
	}
	else{
			
		while ($rowm = mysqli_fetch_array($resultm))
		{
			$bgcolor = "epboxa";

			extract($rowm);	
	
			//echo "$userId1 - $userId2 - $status1 - $status2 <br>";
	
		$ID02 = $inv_user1;
	
		echo "<center><table width=100% border='0' cellspacing='0' cellpadding='0'><tr><td class=$bgcolor>";
		
		
		echo "<strong>";
		require "pages/profile/usernamemem.inc";
		echo "</strong>";
	
		echo " invited you to join the following club: ";
		echo " <a href='/Club/$userId1'>";
		//Display name of club
		
				$query_inv = "SELECT * FROM `club` WHERE `club_id`='$userId1' ";
				$result_inv = mysqli_query($GLOBALS["___mysqli_ston"],  $query_inv );
				// print out the results
				if( $result_inv && $contact_inv = mysqli_fetch_object( $result_inv ) )
				{
					// print out the info
					$club_name = $contact_inv -> club_name;
					$club_name = stripslashes($club_name);
				}
		echo "$club_name";
		echo "</a> ";
		//echo "  (<a href='/?page=invite/addfriend&id=$id&approve=TRUE'>Approve Invite</a>)<br>";	

				echo "
					<form method=\"post\" action=\"${site_url_link}?page=invite/club_approve\">
				";
				// create multi sessions
				if(isset($session_token_num)){
					$session_token_num = $session_token_num + 1;
				}else{
					$session_token_num = "1";
				}
				form_token();
				echo "
						<input type=\"hidden\" name=\"id\" value=\"$id\">
						<input type=\"hidden\" name=\"approve\" value=\"TRUE\">
						<label title=\"Send\"><input type=\"submit\" value=\"Approve Invite\" /></label>
					</form>
				";			
	
		echo "</td></tr></table></center>";	
	
		}
	
	}

//Include club events invite list
require "pages/club/events/attending/cea_invites.inc";
	
}//end mem login check
	
?>
</center>