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


//shows how many new friend request a user has when logged in.

	$querym = "SELECT * FROM ".$db_table_prefix."friend WHERE `userId2`='$userIdme' AND `status2`='0'  ";
	$resultm = mysqli_query($GLOBALS["___mysqli_ston"], $querym);
	
	$num_rows = mysqli_num_rows($resultm);
	
	if ($num_rows >= "1") {
		echo " <a href='${site_url_link}community/myfriends/'><img src='/images/tazib_friends_new.gif'> ";
		echo "<strong>$num_rows</strong>";
		echo "</a> ";
	}else{
		echo " <a href='${site_url_link}community/myfriends/'><img src='/images/tazib_friends.gif'> ";
		echo "<strong>0</strong>";
		echo "</a> ";		
	}

?>