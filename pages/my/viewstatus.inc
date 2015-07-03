<?php
if(isset($_REQUEST['stat'])){ $stat = $_REQUEST['stat']; }else{ $stat = ""; }

$view_status = $_REQUEST['view_status'];
$view_status_link = "${site_url_link}community/viewstatus/?view_status=$view_status";
$view_only_one = "TRUE";



		require "pages/my/status/displaycomments.inc";


?>