<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($_REQUEST['stat'])){ $stat = $_REQUEST['stat']; }else{ $stat = ""; }

$view_status = $_REQUEST['view_status'];
$view_status_link = "${site_url_link}community/viewstatus/?view_status=$view_status";
$view_only_one = "TRUE";



		require "pages/my/status/displaycomments.inc";


?>