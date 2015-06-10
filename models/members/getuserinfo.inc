<?php

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