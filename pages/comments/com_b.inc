<?php
if(isset($_POST['statcom'])){ $statcom = $_POST['statcom']; }else{ $statcom = ""; }

		require "pages/comments/com_b_display.inc";

	if($statcom == 'save'){
	
		//Do nothing
		
	}else{
	
		require "pages/comments/com_b_new.inc";
		
	}

?>