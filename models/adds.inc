<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Get current user's advertisement settings if any.
if(isUserLoggedIn()){
	$userprofile = get_user_adds_setting($userId);
	$userAdds = $userprofile['userAdds'];
	if(empty($userAdds)){ $userAdds = "TRUE"; }
	//echo "$userAdds";
}else{
	$userAdds = "TRUE";
}

if(!empty($site_adds_top) && $userAdds == "TRUE"){
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='content78' align='center'>";

	echo "$site_adds_top";
	
	echo "</td></tr></table>";
}
?>