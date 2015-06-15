<?php

// Forum Admin Functions

// Check for current user's Mod or Admin Rights
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

// Check current Forum Title Order and display link
// If at top only show move down button
// If at bottom only show move up button
// Anywhere else show both move up or down buttons
function forumMoveTitleOrder($fot_id){
	global $mysqli, $db_table_prefix, $load_page_dir, $session_token_num;
	// Get highest number listed in title order
	$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_name`='$load_page_dir' GROUP BY `forum_title` ORDER BY `forum_order_title` DESC LIMIT 1 ";
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

// Allow admin to edit and delete forum Categories
function forumEditTitle($f_title){
	global $mysqli, $db_table_prefix, $load_page_dir, $session_token_num;
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
		echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
			// Setup token in form // create multi sessions
			if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
			form_token();
			echo "<input type=\"hidden\" name=\"forum_title\" value=\"$f_title\" />";
			echo "<input type=\"hidden\" name=\"DeleteTitle\" value=\"TRUE\" />";
			echo "<input type=\"submit\" value=\"Delete\" name=\"Delete\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
		echo "</form>";
	}
}

// Allow admin to edit forum titles
function forumEditTitleCheck($f_title){
	global $mysqli, $db_table_prefix, $load_page_dir, $session_token_num;
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
				$success_msg = "You Have Successfully Moved Forum Category!";
				$_SESSION['success_msg'] = $success_msg;
				
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $websiteUrl;
					$form_redir_link = "${websiteUrl}Forum/";
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
				$success_msg = "You Have Successfully Moved Forum Category!";
				$_SESSION['success_msg'] = $success_msg;
				
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $websiteUrl;
					$form_redir_link = "${websiteUrl}Forum/";
					// Redirect member to their post
					header("Location: $form_redir_link");
					exit;
				}
		}
	}
}

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
			$success_msg = "You Have Successfully Updated Forum Category!";
			$_SESSION['success_msg'] = $success_msg;
			
			//Disables auto refresh for debug stuff
			if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
				//Redirects the user
				global $websiteUrl;
				$form_redir_link = "${websiteUrl}Forum/";
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
?>