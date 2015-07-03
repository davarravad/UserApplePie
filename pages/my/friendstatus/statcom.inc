
<?php
if(isset($_POST['statcom'])){ $statcom = $_POST['statcom']; }else{ $statcom = ""; }


		require "pages/my/friendstatus/statdisplaycomments.inc";

	if($statcom == 'save'){
	
		require_once "pages/my/friendstatus/statsavecomment.inc";
		
	
	}else{
	
	
		require "pages/my/friendstatus/statcommentnew.inc";


	}
		
		




?>