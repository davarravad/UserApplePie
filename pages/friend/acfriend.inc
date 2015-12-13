<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

$uriref = $_SERVER['REQUEST_URI'];

$querym = "SELECT * FROM ".$db_table_prefix."friend WHERE `userId2`='$userId' AND `status2`='0' ";
$resultm = mysqli_query($GLOBALS["___mysqli_ston"], $querym);
	//or die ("Couldn't ececute query. 56141205");

$num_rows = mysqli_num_rows($resultm);


	echo " ( $num_rows )";
if($num_rows == 0){
	echo "<br> No new requests. ";
}
else{
		
	while ($rowm = mysqli_fetch_array($resultm))
	{
		$bgcolor = "epboxa";
		

		extract($rowm);	

		//echo "$userId1 - $userId2 - $status1 - $status2 <br>";

	$ID02 = $userId1;

	echo "<table width=500><tr><td width=100 class=$bgcolor>";
	
	echo "<a href='/?ID=$ID02'>";
	require "content/profile/userimage.php";
	echo "</a>";

	echo "</td><td class=$bgcolor>";

	echo "<strong>";
	require "content/profile/usernamemem.php";
	echo "</strong>";

	echo " wants to be your friend.  (<a href='${site_url_link}?page=friend/addfriend&id=$id&approve=TRUE'>Approve Friendship</a>)<br>";		

	echo "</td></tr></table>";	

	}

}
		



?>