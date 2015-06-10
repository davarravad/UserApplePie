<?

if(isset($_POST['statcom'])){ $statcom = $_POST['statcom']; }else{ $statcom = ""; }


		require "pages/my/status/statdisplaycomments.inc";

	if($statcom == 'save'){
	
		require_once "pages/my/status/statsavecomment.inc";
		
	
	}else{
	
	
		require "pages/my/status/statcommentnew.inc";


	}
		
		




?>