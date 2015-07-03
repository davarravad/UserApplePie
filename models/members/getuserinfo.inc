<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($loggedInUser->displayname) && isset($loggedInUser->user_id)){		
	$nname = $loggedInUser->displayname;
	$idofuser = $loggedInUser->user_id;	
}else{
	$nname = "Visitor";
	$idofuser = "0";
}

if(isset($nname)){
	$nname = "$nname";
	$qthing = "nickname = '$nname'";
}else{
	$nname = "";
}

?>