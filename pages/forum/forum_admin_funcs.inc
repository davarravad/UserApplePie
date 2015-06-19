<?php

// UserApplePie
// www.thedavar.net
// Forum Design By DaVaR

// Forum Admin Functions

//////////////////////////////////////////////////
// Check for current user's Mod or Admin Rights
//////////////////////////////////////////////////
function userCheckForumAdmin(){
	// Check if user is logged in
	if(isUserLoggedIn())
	{
		// Admin users permissions id is 2
		global $loggedInUser;
		if ($loggedInUser->checkPermission(array(2)) == true){
			// User is Admin
			return 1;
		}
		else
		{
			// User is NOT Admin
			return 0;
		}
	}
}
function userCheckForumMod(){
	// Check if user is logged in
	if(isUserLoggedIn())
	{
		// Moderator users permissions id is 4
		global $loggedInUser;
		if ($loggedInUser->checkPermission(array(4)) == true){
			// User is Mod
			return 1;
		}
		else
		{
			// User is NOT Mod
			return 0;
		}
	}
}

//////////////////////////////////////////////////
// Check current Forum Title Order and display link
// If at top only show move down button
// If at bottom only show move up button
// Anywhere else show both move up or down buttons
//////////////////////////////////////////////////
function forumMoveTitleOrder($fot_id){
	global $mysqli, $db_table_prefix, $stc_page_sel, $session_token_num;
	// Check to see if admin or mod wants to move the cat up or down
	if(isset($_POST['MoveCatUp'])){ $MoveCatUp = $_POST['MoveCatUp']; }else{ $MoveCatUp = "FALSE"; }
	if(isset($_POST['MoveCatDown'])){ $MoveCatDown = $_POST['MoveCatDown']; }else{ $MoveCatDown = "FALSE"; }
	if(isset($_POST['forum_order_id'])){ $forum_order_id = $_POST['forum_order_id']; }else{ $forum_order_id = "FALSE"; }
	// Make sure to hide if admin or mod is not doing anything
	if($MoveCatUp == "TRUE" || $MoveCatDown == "TRUE"){
		//Token validation function
		if(!is_valid_token()){ 
			//Token does not match
			err_message('Sorry, Tokens do not match!  Please go back and try again.');
			die;
		}else{
			// Check is user is moving cat up
			if($MoveCatUp == "TRUE"){
				echo " User Wants to Move Cat Up - $forum_order_id ";
				
					// Using the following to change the order of the forum categories for now
					// Will look into a better way of handling this function in the future
				
					// First Lets Change the Rows we want to move to default 999999999
					$new_value = "999999999";
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_title=? WHERE forum_order_title=?");
					$stmt->bind_param("ii", $new_value, $forum_order_id);
					$stmt->execute();
					$stmt->close();

					// Ok now we set the swap value for the cat we are swapping with
					$change_count = 1;
					$change_value = $forum_order_id - $change_count;
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_title=? WHERE forum_order_title=?");
					$stmt->bind_param("ii", $forum_order_id, $change_value);
					$stmt->execute();
					$stmt->close();
					
					// Set the moved target to new value
					$change_count = 1;
					$minus_one = $forum_order_id - $change_count;
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_title=? WHERE forum_order_title=?");
					$stmt->bind_param("ii", $minus_one, $new_value);
					$stmt->execute();
					$stmt->close();
					
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Moved Forum Title!";
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
			// Check if user is moving cat down
			if($MoveCatDown == "TRUE"){
				echo " User Wants to Move Cat Down - $forum_order_id ";
				
					// Using the following to change the order of the forum categories for now
					// Will look into a better way of handling this function in the future
				
					// First Lets Change the Rows we want to move to default 999999999
					$new_value = "999999999";
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_title=? WHERE forum_order_title=?");
					$stmt->bind_param("ii", $new_value, $forum_order_id);
					$stmt->execute();
					$stmt->close();

					// Ok now we set the swap value for the cat we are swapping with
					$change_count = 1;
					$change_value = $forum_order_id + $change_count;
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_title=? WHERE forum_order_title=?");
					$stmt->bind_param("ii", $forum_order_id, $change_value);
					$stmt->execute();
					$stmt->close();
					
					// Set the moved target to new value
					$change_count = 1;
					$minus_one = $forum_order_id + $change_count;
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_title=? WHERE forum_order_title=?");
					$stmt->bind_param("ii", $minus_one, $new_value);
					$stmt->execute();
					$stmt->close();
					
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Moved Forum Title!";
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
		}
	}else{
		// Get highest number listed in title order
		$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_name`='$stc_page_sel' GROUP BY `forum_title` ORDER BY `forum_order_title` DESC LIMIT 1 ";
		$result = $mysqli->query($query);
		$arr = $result->fetch_all(MYSQLI_BOTH);
		foreach($arr as $row)
		{
			$f_order_title = $row['forum_order_title'];
			//echo " - $fot_id of $f_order_title - ";
			if($fot_id == 1)
			{
				// Form button to move cat down
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo "<input type=\"hidden\" name=\"forum_order_id\" value=\"$fot_id\" />";
					echo "<input type=\"hidden\" name=\"MoveCatDown\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Move Down\" name=\"Move Down\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
			}
			else if($fot_id == $f_order_title)
			{
				// Form button to move cat up
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo "<input type=\"hidden\" name=\"forum_order_id\" value=\"$fot_id\" />";
					echo "<input type=\"hidden\" name=\"MoveCatUp\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Move Up\" name=\"Move Up\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
			}
			else
			{
				// Form button to move cat up
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo "<input type=\"hidden\" name=\"forum_order_id\" value=\"$fot_id\" />";
					echo "<input type=\"hidden\" name=\"MoveCatUp\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Move Up\" name=\"Move Up\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
				
				// Form button to move cat down
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo "<input type=\"hidden\" name=\"forum_order_id\" value=\"$fot_id\" />";
					echo "<input type=\"hidden\" name=\"MoveCatDown\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Move Down\" name=\"Move Down\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
			}
		}
	}
}

//////////////////////////////////////////////////
// Allow admin to edit and delete forum Titles
//////////////////////////////////////////////////
function forumEditTitle($f_title){
	global $mysqli, $db_table_prefix, $load_page_dir, $session_token_num, $websiteUrl, $site_forum_title;
	// Form button to edit forum title
	echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
		// Setup token in form // create multi sessions
		if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
		form_token();
		echo "<input type=\"hidden\" name=\"forum_title\" value=\"$f_title\" />";
		echo "<input type=\"hidden\" name=\"EditTitle\" value=\"TRUE\" />";
		echo "<input type=\"submit\" value=\"Edit\" name=\"Edit\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
	echo "</form>";
	
	// Only Admins Can Delete Forum Titles
	if(userCheckForumAdmin()){
		// Form button to delete forum title
		echo "<form enctype=\"multipart/form-data\" action=\"${websiteUrl}${site_forum_title}/forum_delete_stuff/\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
			// Setup token in form // create multi sessions
			if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
			form_token();
			echo "<input type=\"hidden\" name=\"forum_title\" value=\"$f_title\" />";
			echo "<input type=\"hidden\" name=\"DeleteTitle\" value=\"TRUE\" />";
			echo "<input type=\"submit\" value=\"Delete\" name=\"Delete\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
		echo "</form>";
	}
}

//////////////////////////////////////////////////
// Allow admin to edit forum titles
//////////////////////////////////////////////////
function forumEditTitleCheck($f_title){
	global $mysqli, $db_table_prefix, $load_page_dir, $session_token_num;
	// Check to see if mod is updating a forum title
	if(isset($_POST['AdminEditTitle'])){ $AdminEditTitle = $_POST['AdminEditTitle']; }else{ $AdminEditTitle = "FALSE"; }
	if(isset($_POST['forum_title_old'])){ $forum_title_old = $_POST['forum_title_old']; }else{ $forum_title_old = ""; }
	if(isset($_POST['forum_title_new'])){ $forum_title_new = $_POST['forum_title_new']; }else{ $forum_title_new = ""; }
	if($AdminEditTitle == "TRUE"){
		//Token validation function
		if(!is_valid_token()){ 
			//Token does not match
			err_message('Sorry, Tokens do not match!  Please go back and try again.');
			die;
		}else{
			// Update Database with new title
			$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_title=? WHERE forum_title=?");
			$stmt->bind_param("ss", $forum_title_new, $forum_title_old);
			if($stmt->execute()){
				$stmt->close();
				
				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Updated Forum Title!";
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
	}else{
		if(isset($_POST['EditTitle'])){ $EditTitle = $_POST['EditTitle']; }else{ $EditTitle = "FALSE"; }
		if(isset($_POST['forum_title'])){ $forum_title = $_POST['forum_title']; }else{ $forum_title = ""; }
		// Make sure user has permission to edit this title
		if((userCheckForumAdmin() || userCheckForumMod()) && ($EditTitle == "TRUE" && $forum_title == $f_title)){
			// Mod or Admin would like to edit a title
			// Show edit forum in place of title
			echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
				// Setup token in form // create multi sessions
				if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
				form_token();
				echo "<input name=\"forum_title_new\" type=\"text\" value=\"${f_title}\" style='width:200px;font-family:verdana;font-size:12px;font-weight:bold'>";
				echo "<input type=\"hidden\" name=\"forum_title_old\" value=\"$f_title\" />";
				echo "<input type=\"hidden\" name=\"AdminEditTitle\" value=\"TRUE\" />";
				echo "<input type=\"submit\" value=\"Update\" name=\"Update\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
			echo "</form>";
		}
		else
		{
			echo "<strong>$f_title</strong>";
		}
	}
}
//////////////////////////////////////////////////
// Setup User Forum Permissions Display
//////////////////////////////////////////////////
function forumDisplayUserPerms(){
	// Displays Current User's Status if they are Visitor, Member, Mod, or Admin
	if(userCheckForumAdmin()){ $forum_perm_level = "Admin"; }
	else if(userCheckForumMod()){ $forum_perm_level = "Moderator"; }
	else if(isUserLoggedIn()){ $forum_perm_level = "Member"; }
	else{ $forum_perm_level = "Visitor"; }
	// If Admin or Mod Show settings to edit forum
	echo "<table width='100%' class='content78'><tr><td>";
		echo "Permission Level: $forum_perm_level";
	echo "</td></tr></table>";
}

//////////////////////////////////////////////////
// Allow Admin to Create New Forum Titles
//////////////////////////////////////////////////
function forumCreateNewTopic(){
	// Check to see if admin or mod is viewing forum. 
	// Only show new title form if admin or mod.
	if(userCheckForumAdmin() || userCheckForumMod()){
		// Check is user is creating a new title
		if(isset($_POST['AdminCreateTitle'])){ $AdminCreateTitle = $_POST['AdminCreateTitle']; }else{ $AdminCreateTitle = "FALSE"; }
		if(isset($_POST['forum_title_create'])){ $forum_title_create = $_POST['forum_title_create']; }else{ $forum_title_create = ""; }
		global $mysqli, $websiteUrl, $db_table_prefix, $session_token_num, $stc_page_sel;
		if($AdminCreateTitle == "TRUE"){
			//Token validation function
			if(!is_valid_token()){ 
				//Token does not match
				err_message('Sorry, Tokens do not match!  Please go back and try again.');
				die;
			}else{
				// Get highest number listed in title order
				$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_name`='$stc_page_sel' GROUP BY `forum_title` ORDER BY `forum_order_title` DESC LIMIT 1 ";
				$result = $mysqli->query($query);
				$arr = $result->fetch_all(MYSQLI_BOTH);
				foreach($arr as $row)
				{
					$f_order_title = $row['forum_order_title'];
					$next_order_number = $f_order_title + 1;
				}
				
				// Update Database with new title
				$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."forum_cat SET forum_name=?, forum_title=?, forum_order_title=?");
				$stmt->bind_param("ssi", $stc_page_sel, $forum_title_create, $next_order_number);
				if($stmt->execute()){
					$stmt->close();
					
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Created Forum Title!";
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
				}else{
					err_message('Oops. There was an error. 54528');
					die;
				}
			}
		}else{
			// Show create title form
			echo "<table width='100%'><tr><td>";
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo " <label>Create new topic:</label> ";
					echo "<input name=\"forum_title_create\" type=\"text\" value=\"\" style='width:200px;font-family:verdana;font-size:12px;font-weight:bold'>";
					echo "<input type=\"hidden\" name=\"AdminCreateTitle\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Create Title\" name=\"Create Title\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
			echo "</td></tr></table>";
		}
	}
}

//////////////////////////////////////////////////
// Display the edit delete button for forum categories
//////////////////////////////////////////////////
function forumCatEdit(){
	if(userCheckForumAdmin() || userCheckForumMod()){
		// Display Edit, Delete, and Move Buttons
		echo "</td></tr><tr><td colspan=2 align=right>";
		// Display Edit and Move buttons to mods and admins
		echo "Move Up Move Down Edit ";
		// Only display delete button to admins
		if(userCheckForumAdmin()){
			echo " Delete ";
		}
	}
}

//////////////////////////////////////////////////
// Allow Mods and Admin to create new categories
//////////////////////////////////////////////////
function forumCatNew(){
	if(userCheckForumAdmin() || userCheckForumMod()){
		echo "Create New Category";
	}
}


?>