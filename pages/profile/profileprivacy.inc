<?php
//Profile Privacy

//Checks for users profile privacy settings

//echo "Profile User Id : $ID02<br>"; //Testing - Displays profile ID #
//echo "My User Id : $userIdme<br>"; //Testing - Displays current user's ID #

$queryPPS = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$ID02' ";

// Get information from database
$result_PPS = $mysqli->query($queryPPS);
$arr_PPS = $result_PPS->fetch_all(MYSQLI_BOTH);
foreach($arr_PPS as $row_PPS)
{
	$userFax = $row_PPS['userFax'];
}

//echo "Profile Privacy Setting : $userFax<br>"; //Testing - Displays Privacy Settings

if(isUserLoggedIn())
{

//Start Friend Check
$querym = "SELECT * FROM ".$db_table_prefix."friend WHERE ((`userId1`='$userId1' AND `userId2`='$userId2') OR (`userId1`='$userId2' AND `userId2`='$userId1')) LIMIT 1";
$resultm = mysqli_query($GLOBALS["___mysqli_ston"], $querym);
$num_rows = mysqli_num_rows($resultm);
		
	while ($rowm = mysqli_fetch_array($resultm))
	{
		extract($rowm);	

			if($status2 == "1"){ $isfriend = "yesfriend"; }else{ $isfriend = "FALSE"; }
	}

//End Friend Check

}
if(isset($isfriend)){}else{ $isfriend = "FALSE"; }

//Checks to see if profile is logged in user
if($ID02 == $userIdme){ $PPtype = "me"; }

//Checks to see if user is a friend
elseif($isfriend == "yesfriend"){ $PPtype = "friends"; }

//Checks to see if user is a member
elseif(isUserLoggedIn()){ $PPtype = "members"; }

//Checks to see if user is public
elseif($userIdme = !0){ $PPtype = "public"; }

//echo "User Type : $PPtype<br>"; //Testing - Displays user type. public, member, friend, or me


	if($userFax == "me"){
		if($PPtype == "me"){ $allowPV = "TRUE"; }
	}
	if($userFax == "public"){
		if($PPtype == "me"){ $allowPV = "TRUE"; }
		if($PPtype == "public"){ $allowPV = "TRUE"; }
		if($PPtype == "members"){ $allowPV = "TRUE"; }
		if($PPtype == "friends"){ $allowPV = "TRUE"; }
	}
	if($userFax == "members"){
		if($PPtype == "me"){ $allowPV = "TRUE"; }
		if($PPtype == "members"){ $allowPV = "TRUE"; }
		if($PPtype == "friends"){ $allowPV = "TRUE"; }
	}
	if($userFax == "friends"){
		if($PPtype == "me"){ $allowPV = "TRUE"; }
		if($PPtype == "friends"){ $allowPV = "TRUE"; }
	}
	

if(isset($allowPV)){}else{ $allowPV = "FALSE"; }
if($allowPV == "FALSE"){
	if($userFax == "me"){
		echo "This user has requested that only they can view this profile.";
	}
	if($userFax == "public"){
		echo "This user has requested that the public can view this profile.";
	}
	if($userFax == "members"){
		echo "This user has requested that only members can view this profile.";
	}
	if($userFax == "friends"){
		echo "This user has requested that only friends can view this profile.";
	}
}

//echo "<br>Allow User? : $allowPV<br>"; //Testing - Allow current user to view profile T or F

?>