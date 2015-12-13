<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($_POST['approve'])){ $approve = $_POST['approve']; }else{ $approve = ""; }
	if(isset($_POST['acfriend'])){ $acfriend = $_POST['acfriend']; }else{ $acfriend = ""; }
	if(isset($_POST['addfriend'])){ $addfriend = $_POST['addfriend']; }else{ $addfriend = ""; }
	if(isset($_POST['userId1'])){ $userId1 = $_POST['userId1']; }else{ $userId1 = ""; }
	if(isset($_POST['userId2'])){ $userId2 = $_POST['userId2']; }else{ $userId2 = ""; }
	if(isset($_POST['pnum'])){ $pnum = $_POST['pnum']; }else{ $pnum = ""; }
	if(isset($_POST['uriref'])){ $uriref = $_POST['uriref']; }else{ $uriref = ""; }
	
	if($addfriend == "TRUE"){
		require "pages/friend/fadd.inc";
	}
	if($acfriend == "TRUE"){
		require "pages/friend/acfriend.inc";
	}
	if($approve == "TRUE"){
		require "pages/friend/acfadd.inc";
	}
	
	//Testing Stuff
	//echo "<br><br><br>";
	//echo "userId1 = $userId1 <br>";
	//echo "userId2 = $userId2 <br>";
	//echo "$addfriend";
	//echo "$uriref&pnum=$pnum";

?>