<?php

// UserApplePie 
// www.thedavar.net
// Forum Delete Stuff 

// To Do
// When a user wants to delete a title or category ask
// if they would like to move to another location or
// delete everything within that title or category

// Only Admins can delete stuff
if(userCheckForumAdmin()){
	global $mysqli, $db_table_prefix, $load_page_dir, $session_token_num, $websiteUrl, $site_forum_title;
	//echo "You Are Admin and Can Delete Stuff";
	// Get Data from Post Header to see what user is wanting to do
	if(isset($_POST['DeleteTitle'])){ $DeleteTitle = $_POST['DeleteTitle']; }else{ $DeleteTitle = "FALSE"; }
	if(isset($_POST['DeleteTitleYes'])){ $DeleteTitleYes = $_POST['DeleteTitleYes']; }else{ $DeleteTitleYes = "FALSE"; }
	if(isset($_POST['forum_title'])){ $forum_title = $_POST['forum_title']; }else{ $forum_title = ""; }
	if($DeleteTitle == "TRUE"){
		echo "<br>Are you sure you would like to delete the forum title <strong>$forum_title</strong>?<Br>";
		echo "If you delete the forum title, everything within that title will be deleted as well.";
		//echo "<a href=='${site_url_link}?page=message&mes=delmesinbox&mid=$mid&yes=yes'>Yes?</a> / <a href='../'>No?</a>";
		
				echo "<center>";
				echo "<form enctype=\"multipart/form-data\" action=\"${websiteUrl}${site_forum_title}/forum_delete_stuff/\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo "<input type=\"hidden\" name=\"forum_title\" value=\"$forum_title\" />";
					echo "<input type=\"hidden\" name=\"DeleteTitleYes\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"YES\" name=\"YES\" class=\"unsweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
				echo "</center>";
				$taz_backz = "
					<form method=\"post\" action=\"${websiteUrl}${site_forum_title}/\" onsubmit=\"submit.disabled = true; return true;\">
						<input type=\"hidden\" name=\"mes\" value=\"inbox\">
						<label title=\"Send\"><input type=\"submit\" value=\"NO\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" /></label>
					</form>
				";
				echo "<center>$taz_backz</center>";
	}
	else if($DeleteTitleYes == "TRUE"){
		//Token validation function
		if(!is_valid_token()){ 
			//Token does not match
			err_message('Sorry, Tokens do not match!  Please go back and try again.');
			die;
		}else{
			// Setup feature to move topics and replies if admin wants them moved
			// If not then delete all topics and replies related to this title
			
			// Delete title from the database
			$stmt = $mysqli->prepare("DELETE FROM ".$db_table_prefix."forum_cat WHERE forum_title=?");
			$stmt->bind_param("s", $forum_title);
			if($stmt->execute()){
				$stmt->close();
				
				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Deleted Forum Title!";
				$_SESSION['success_msg'] = $success_msg;
				
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $websiteUrl, $site_forum_title;
					$form_redir_link = "${websiteUrl}${site_forum_title}/";
					// Redirect member to their post
					header("Location: $form_redir_link");
					exit;
				}
			}
			else
			{
				err_message('Oops. There was an error. 546528');
				die;
			}
		}
	}
	
}else{
	// If user is not a site admin then don't let them view this page
	// Auto Redirect back to the forum
	global $websiteUrl, $site_forum_title;
	$form_redir_link = "${websiteUrl}${site_forum_title}/";
	// Redirect member to their post
	header("Location: $form_redir_link");
	exit;
}

?>