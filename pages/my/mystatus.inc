<?php
if(isset($_POST['stat'])){ $stat = $_POST['stat']; }else{ $stat = ""; }


	if($stat == 'save'){
	
		require "pages/my/status/savecomment.inc";
		
	
	}else{
	
	
		require "pages/my/status/commentnew.inc";


	}
		
		echo "<br><Br>";

		require "pages/my/status/displaycomments.inc";



?>