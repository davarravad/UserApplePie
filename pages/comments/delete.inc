<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Checks to see if user is loged in
if(isUserLoggedIn())
{

if(isset($_POST['ed_com_delete'])){
	$ed_com_delete = $_POST['ed_com_delete'];
}else{
	$ed_com_delete = "";
}

if($ed_com_delete == "yesdelete"){


	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{ 


	if($ed_com_database == "profilecomments"){
		$queryDC = "DELETE FROM `".$db_table_prefix."profilecomments` WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1 ";
		$queryDC2 = "DELETE FROM `".$db_table_prefix."profilecomments_b` WHERE `statcom_id`='$ed_com_id_form' ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "profilecomments_b"){
		$queryDC = "DELETE FROM `".$db_table_prefix."profilecomments_b` WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme' LIMIT 1 ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "writingcomments"){
		$queryDC = "DELETE FROM `".$db_table_prefix."writingcomments` WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1 ";
		$queryDC2 = "DELETE FROM `".$db_table_prefix."writingcomments_b` WHERE `statcom_id`='$ed_com_id_form' ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "writingcomments_b"){
		$queryDC = "DELETE FROM `".$db_table_prefix."writingcomments_b` WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme' LIMIT 1 ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "artcomments"){
		$queryDC = "DELETE FROM `".$db_table_prefix."artcomments` WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1 ";
		$queryDC2 = "DELETE FROM `".$db_table_prefix."artcomments_b` WHERE `statcom_id`='$ed_com_id_form' ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "artcomments_b"){
		$queryDC = "DELETE FROM `".$db_table_prefix."artcomments_b` WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme' LIMIT 1 ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "clubcomments"){
		$queryDC = "DELETE FROM `".$db_table_prefix."clubcomments` WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1 ";
		$queryDC2 = "DELETE FROM `".$db_table_prefix."clubcomments_b` WHERE `statcom_id`='$ed_com_id_form' ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "clubcomments_b"){
		$queryDC = "DELETE FROM `".$db_table_prefix."clubcomments_b` WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme' LIMIT 1 ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "status"){
		$queryDC = "DELETE FROM `".$db_table_prefix."status` WHERE `id`='$ed_com_id_form' AND `com_id`='$userIdme' LIMIT 1 ";
		$queryDC2 = "DELETE FROM `".$db_table_prefix."statcom` WHERE `statcom_id`='$ed_com_id_form' ";
		$comment_type_yeah = "Status";
	}
	if($ed_com_database == "statcom"){
		$queryDC = "DELETE FROM `".$db_table_prefix."statcom` WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme' LIMIT 1 ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "club_events_com"){
		$queryDC = "DELETE FROM `".$db_table_prefix."club_events_com` WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1 ";
		$queryDC2 = "DELETE FROM `".$db_table_prefix."club_events_com_b` WHERE `statcom_id`='$ed_com_id_form' ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "club_events_com_b"){
		$queryDC = "DELETE FROM `".$db_table_prefix."club_events_com_b` WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme' LIMIT 1 ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "location_comments"){
		$queryDC = "DELETE FROM `".$db_table_prefix."location_comments` WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1 ";
		$queryDC2 = "DELETE FROM `".$db_table_prefix."location_comments_b` WHERE `statcom_id`='$ed_com_id_form' ";
		$comment_type_yeah = "Comment";
	}
	if($ed_com_database == "location_comments_b"){
		$queryDC = "DELETE FROM `".$db_table_prefix."location_comments_b` WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme' LIMIT 1 ";
		$comment_type_yeah = "Comment";
	}
	
	
	if(isset($queryDC2)){
		$resultsDC2 = mysqli_query($GLOBALS["___mysqli_ston"],  $queryDC2 );

		// print out the results
		if( $resultsDC2 ){
		
			//echo "Successfully saved the entry.<br><br>";
			//Disables auto refresh for debug stuff
			if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
				//echo "<meta HTTP-EQUIV='REFRESH' content='0; url=$ed_com_url'>";  
			}
		}
		else{
			die( "22Trouble saving information to the database: " . ((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_error($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_error()) ? $___mysqli_res : false)) );
		}	
	}	
  
	$resultsDC = mysqli_query($GLOBALS["___mysqli_ston"],  $queryDC );

	// print out the results
	if( $resultsDC ){

		//Sends success message to session
		//Shows user success when they are redirected
		$success_msg = "You Have Successfully Deleted Your $comment_type_yeah!";
		$_SESSION['success_msg'] = $success_msg;		
	
		//echo "Successfully saved the entry.<br><br>";
		//Disables auto refresh for debug stuff
		if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
			
			//Redirects the user
			global $site_url_link;
			$redir_link_url = "${ed_com_url}";
			
			// Redirect member to their post
			header("Location: $redir_link_url");
			exit;
  
		}
	}
	else{
		//Code used to report mysql error
		$mysql_error_report = "TRUE";
		$sql_query = "$queryDC";
		require "models/mysql_error_report.inc";
	}


	
	 //End of Token Check
			}
	
		 //Ends the token session for better security	
 		unset($_SESSION['user_token']);  



}else{

		echo '
			<hr><center>
			Are you sure you want to delete this comment?<br>
			
			<form enctype="multipart/form-data" action="'.$ed_com_url.'" method="POST" class="sweetform" onsubmit="edit.disabled = true; return true;">
		';
		//Setup token in form
			// create multi sessions
			if(isset($session_token_num)){
				$session_token_num = $session_token_num + 1;
			}else{
				$session_token_num = "1";
			}
			form_token();
		echo '
			<input type="hidden" name="ed_com" value="delete" />
			<input type="hidden" name="ed_com_delete" value="yesdelete" />
			<input type="hidden" name="ed_com_database" value="'.$ed_com_database.'" />
			<input type="hidden" name="ed_com_id_form" value="'.$ed_com_id_form.'" />
			<input type="hidden" name="ed_com_url" value="'.$ed_com_url.'" />
			<input type="hidden" name="com_uid" value="'.$com_uid.'" />
			<input type="hidden" name="com_id" value="'.$com_id.'" />
			<input type="hidden" name="com_type_edit" value="'.$com_type_edit.'" >
			<input type="hidden" name="com_content" value="'.$com_content.'" />

			<input type="submit" value="Yes" name="edit" class="sweet" onClick="this.value = "Please Wait...."">

			</form>

			<form enctype="multipart/form-data" action="'.$ed_com_url.'" method="POST" class="sweetform" onsubmit="edit.disabled = true; return true;">

			<input type="submit" value="No" name="edit" class="sweet" onClick="this.value = "Please Wait...."">

			</form>


			</center>
		';

}

}else{
	notlogedinmsg();
}
?>