<?php
//////////////////////////////////
// UserApplePie Version: 1.1.1  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Security Feature to Disallow File to be opened directly.
// Only allows this file to be include by index.php
if(!defined('Page_Protection')){header("Location: ../");exit();}


//Checks to see if user is loged in
if(isUserLoggedIn())
{

		//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{


		//echo "$com_uid - $com_id - $ed_com_database - $ed_com_id_form - $ed_com_url - $com_content";

		unset($com_content);

		$com_content = $_POST['com_content'];

		if($com_content){

			$com_content = ALB($com_content);
			 
			if($ed_com_database == "profilecomments"){
				$queryUC = "UPDATE `".$db_table_prefix."profilecomments` SET `com_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "profilecomments_b"){
				$queryUC = "UPDATE `".$db_table_prefix."$ed_com_database` SET `statcom_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme'";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "writingcomments"){
				$queryUC = "UPDATE `".$db_table_prefix."writingcomments` SET `com_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "writingcomments_b"){
				$queryUC = "UPDATE `".$db_table_prefix."$ed_com_database` SET `statcom_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme'";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "artcomments"){
				$queryUC = "UPDATE `".$db_table_prefix."artcomments` SET `com_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "artcomments_b"){
				$queryUC = "UPDATE `".$db_table_prefix."$ed_com_database` SET `statcom_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme'";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "clubcomments"){
				$queryUC = "UPDATE `".$db_table_prefix."clubcomments` SET `com_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "clubcomments_b"){
				$queryUC = "UPDATE `".$db_table_prefix."$ed_com_database` SET `statcom_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme'";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "status"){
				$queryUC = "UPDATE `".$db_table_prefix."status` SET `com_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `com_id`='$userIdme' LIMIT 1";
				$comment_type_yeah = "Status";
			}
			if($ed_com_database == "statcom"){
				$queryUC = "UPDATE `".$db_table_prefix."statcom` SET `statcom_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme'";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "club_events_com"){
				$queryUC = "UPDATE `".$db_table_prefix."$ed_com_database` SET `com_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "club_events_com_b"){
				$queryUC = "UPDATE `".$db_table_prefix."$ed_com_database` SET `statcom_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme'";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "location_comments"){
				$queryUC = "UPDATE `".$db_table_prefix."$ed_com_database` SET `com_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `com_uid`='$userIdme' LIMIT 1";
				$comment_type_yeah = "Comment";
			}
			if($ed_com_database == "location_comments_b"){
				$queryUC = "UPDATE `".$db_table_prefix."$ed_com_database` SET `statcom_content`='$com_content' WHERE `id`='$ed_com_id_form' AND `statcom_uid`='$userIdme'";
				$comment_type_yeah = "Comment";
			}
		  
			$resultsUC = mysqli_query($GLOBALS["___mysqli_ston"],  $queryUC );

			// print out the results
			if( $resultsUC ){

				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Updated Your $comment_type_yeah!";
				$_SESSION['success_msg'] = $success_msg;			

				echo "Successfully saved the entry.<br><br>";
				//echo "$com_content";
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $site_url_link;
					$redir_link_url = "";
					
					// Redirect member to their post
					header("Location: $redir_link_url");
					exit;

				}
			}
			else{
				//Code used to report mysql error
				$mysql_error_report = "TRUE";
				$sql_query = "$queryUC";
				require "external/mysql_error_report.php";
			}
		}


				 //End of Token Check
					}			
				 //Ends the token session for better security	
				unset($_SESSION['user_token']);  


}else{
	notlogedinmsg();
}

?>