<?

//Triggers debug stuff for the site
$debug_website = "$site_debug";  //TRUE = ON OR FALSE = OFF

if(isset($loggedInUser->username)){
	$username987 = $loggedInUser->username;
}else{
	$username987 = "";
}
	
if($username987 == 'DaVaR'){
	$debug_addsoff = "TRUE";  //TRUE = ON OR FALSE = OFF
}else{
	$debug_addsoff = "FALSE";  //TRUE = ON OR FALSE = OFF
}

//if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{}

//if($debug_addsoff == 'TRUE'){ echo "<br> - DEBUG ADDS SITE ON - <BR>"; }else{}

?>