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
	echo "<div class='panel panel-default'>";
		echo "<div class='panel-body'>";

			echo "$site_adds_top";
		
		echo "</div>";
	echo "</div>";
}
?>