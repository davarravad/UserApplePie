<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Check to see is site is demo site.  If so disable editing.
if($cur_server_name_dc != $demo_server_name_dc){
// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){

      if(isset($_POST['yes'])){ $yes = $_POST['yes']; }else{$yes = "";}
      $er_id = $_POST['er_id'];

	if($yes == 'yes'){

	
	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{


      $er_id = $_POST['er_id'];

 
      $query = "DELETE FROM `".$db_table_prefix."errors` WHERE `er_id`='$er_id' LIMIT 1";

  

 $results = mysqli_query($GLOBALS["___mysqli_ston"], $query);

   // print out the results
   if( $results )
   {
   
		//Sends success message to session
		//Shows user success when they are redirected
		$success_msg = "You Have Successfully Deleted A Error!";
		$_SESSION['success_msg'] = $success_msg;
   
		//  echo( "<br><br>Delete<br><br>" );
		//  echo( "Successfully Deleted the entry." );
		//Disables auto refresh for debug stuff
		if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
			//Redirects the user
			global $site_url_link;
			$redir_link_url = "${site_url_link}/UAP_Admin_Panel/errors/";
			
			// Redirect member to their post
			header("Location: $redir_link_url");
			exit;

		}

   }
 
   else
   {
		//Code used to report mysql error
		$mysql_error_report = "TRUE";
		$sql_query = "$query";
		require "models/mysql_error_report.inc";
   }
    
  

}


	}
	else {
		echo "<center>Are you sure you would like to delete that?</center><Br>";

				echo "<center>
					<form method=\"post\" action=\"${site_url_link}UAP_Admin_Panel/delete_error/ \">
				";
					// create multi sessions
					if(isset($session_token_num)){
						$session_token_num = $session_token_num + 1;
					}else{
						$session_token_num = "1";
					}
					form_token();
				echo "
						<input type=\"hidden\" name=\"delete\" value=\"yes\">
						<input type=\"hidden\" name=\"er_id\" value=\"$er_id\">
						<input type=\"hidden\" name=\"yes\" value=\"yes\">
						<label title=\"Send\"><input type=\"submit\" value=\"YES\" /></label>
					</form>
				";
				
				$taz_backz = "
					<form method=\"post\" action=\"${site_url_link}UAP_Admin_Panel/errors/?er_id=$er_id\">
						<label title=\"Send\"><input type=\"submit\" value=\"NO\" /></label>
					</form>
				";
				echo "$taz_backz</center>";

	}

}
}
?>