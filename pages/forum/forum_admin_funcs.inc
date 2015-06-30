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
// Cleans up forum_order_title for selected title
// Just to make sure everything is in order and missing or deleted rows
// are not creating gaps in the display order
//////////////////////////////////////////////////
//$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_title=? WHERE forum_order_title=?");
function forumCleanOrderTitle(){
	// Make sure only mods or Admins are using this feature
	if(userCheckForumAdmin() || userCheckForumMod()){
		global $mysqli, $db_table_prefix, $session_token_num, $debug_website;
		// Check to see what the total number of rows in table are
		$query = "SELECT forum_order_title FROM uc_forum_cat";
		$query_group = $query." GROUP BY forum_title";
		if ($stmt = $mysqli->prepare($query_group)) {
			$stmt->execute();
			$stmt->store_result();
			$total_rows = $stmt->num_rows;
			$stmt->close();
		}
		// Get the id of the last row to make sure nothing has been skipped
		$query_order = $query." ORDER BY forum_order_title DESC LIMIT 1";
		$result = $mysqli->query($query_order);
		$arr = $result->fetch_all(MYSQLI_BOTH);
		foreach($arr as $row)
		{
			$last_row = $row['forum_order_title'];
		}
		$result->close();
		//echo " ( $total_rows - $last_row ) ";
		// Only Clean up the table if it needs it
		if($total_rows != $last_row){
			// Will have to come up with an automatic feature for this to work
			// The goal is to keep in order without skipping any deleted rows
			err_message('Forums Are Not In Order.  Admin Must Fix This in SQL!  Otherwise mess with order.  Reason for this message: Admin deleted a title.');
		}
	}
}

//////////////////////////////////////////////////
// Cleans up forum_order_title for selected title
// Just to make sure everything is in order and missing or deleted rows
// are not creating gaps in the display order
//////////////////////////////////////////////////
//$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_title=? WHERE forum_order_title=?");
function forumCleanOrderCat($forum_title){
	// Make sure only mods or Admins are using this feature
	if(userCheckForumAdmin() || userCheckForumMod()){
		global $mysqli, $db_table_prefix, $session_token_num, $debug_website;
		// Check to see what the total number of rows in table are
		$query = "SELECT forum_order_cat FROM uc_forum_cat WHERE forum_title = '$forum_title'";
		if ($stmt = $mysqli->prepare($query)) {
			$stmt->execute();
			$stmt->store_result();
			$total_rows = $stmt->num_rows;
			$stmt->close();
		}
		// Get the id of the last row to make sure nothing has been skipped
		$query_order = $query." ORDER BY forum_order_cat DESC LIMIT 1";
		$result = $mysqli->query($query_order);
		$arr = $result->fetch_all(MYSQLI_BOTH);
		foreach($arr as $row)
		{
			$last_row = $row['forum_order_cat'];
		}
		$result->close();
		
		// Only Clean up the table if it needs it
		if($total_rows != $last_row){
			echo "<br><br>Please Wait While Forum Is Cleaned Up!";
			$query = "SET @count := 0;";
			$query .= "UPDATE `uc_forum_cat` SET `uc_forum_cat`.`forum_order_cat` = @count := (@count + 1) WHERE forum_title = '$forum_title' ORDER BY forum_order_cat";
			if (!$mysqli->multi_query($query))
			 echo "Multi query failed: (" . $mysqli->errno . ") " . $mysqli->error;

			do {
			 if ($res = $mysqli->store_result()) {
			  var_dump($res->fetch_all(MYSQLI_ASSOC));
			  $res->free();
			 }
			} while ($mysqli->more_results() && $mysqli->next_result());
			
			//Sends success message to session
			//Shows user success when they are redirected
			$success_msg = "A Forum Category Was Out of Order.  It Has been cleaned!";
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
}
	
//////////////////////////////////////////////////
// Check current Forum Title Order and display link
// If at top only show move down button
// If at bottom only show move up button
// Anywhere else show both move up or down buttons
//////////////////////////////////////////////////
function forumMoveTitleOrder($fot_id){
	global $mysqli, $db_table_prefix, $site_forum_title, $session_token_num, $debug_website;
	// Check to see if admin or mod wants to move the cat up or down
	if(isset($_POST['MoveTitleUp'])){ $MoveTitleUp = $_POST['MoveTitleUp']; }else{ $MoveTitleUp = "FALSE"; }
	if(isset($_POST['MoveTitleDown'])){ $MoveTitleDown = $_POST['MoveTitleDown']; }else{ $MoveTitleDown = "FALSE"; }
	if(isset($_POST['forum_order_id'])){ $forum_order_id = $_POST['forum_order_id']; }else{ $forum_order_id = "FALSE"; }
	// Make sure to hide if admin or mod is not doing anything
	if($MoveTitleUp == "TRUE" || $MoveTitleDown == "TRUE"){
		//Token validation function
		if(!is_valid_token()){ 
			//Token does not match
			err_message('Sorry, Tokens do not match!  Please go back and try again.');
			die;
		}else{
			// Check is user is moving cat up
			if($MoveTitleUp == "TRUE"){
				echo " User Wants to Move Title Up - $forum_order_id ";
				
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
			if($MoveTitleDown == "TRUE"){
				echo " User Wants to Move Title Down - $forum_order_id ";
				
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
		$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_name`='$site_forum_title' GROUP BY `forum_title` ORDER BY `forum_order_title` DESC LIMIT 1 ";
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
					echo "<input type=\"hidden\" name=\"MoveTitleDown\" value=\"TRUE\" />";
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
					echo "<input type=\"hidden\" name=\"MoveTitleUp\" value=\"TRUE\" />";
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
					echo "<input type=\"hidden\" name=\"MoveTitleUp\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Move Up\" name=\"Move Up\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
				
				// Form button to move cat down
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo "<input type=\"hidden\" name=\"forum_order_id\" value=\"$fot_id\" />";
					echo "<input type=\"hidden\" name=\"MoveTitleDown\" value=\"TRUE\" />";
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
	global $mysqli, $db_table_prefix, $load_page_dir, $session_token_num, $debug_website;
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
		global $mysqli, $websiteUrl, $db_table_prefix, $session_token_num, $site_forum_title, $debug_website;
		if($AdminCreateTitle == "TRUE"){
			//Token validation function
			if(!is_valid_token()){ 
				//Token does not match
				err_message('Sorry, Tokens do not match!  Please go back and try again.');
				die;
			}else{
				// Get highest number listed in title order
				$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_name`='$site_forum_title' GROUP BY `forum_title` ORDER BY `forum_order_title` DESC LIMIT 1 ";
				$result = $mysqli->query($query);
				$arr = $result->fetch_all(MYSQLI_BOTH);
				foreach($arr as $row)
				{
					$f_order_title = $row['forum_order_title'];
					$next_order_number = $f_order_title + 1;
				}
				if(empty($next_order_number)){ $next_order_number = "1"; }
				
				// Update Database with new title
				$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."forum_cat SET forum_name=?, forum_title=?, forum_order_title=?");
				$stmt->bind_param("ssi", $site_forum_title, $forum_title_create, $next_order_number);
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
					echo " <label>Create New Title:</label> ";
					echo "<input name=\"forum_title_create\" type=\"text\" value=\"New Title\" style='width:200px;font-family:verdana;font-size:12px;font-weight:bold'>";
					echo "<input type=\"hidden\" name=\"AdminCreateTitle\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Create Title\" name=\"Create Title\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
			echo "</td></tr></table>";
		}
	}
}

//////////////////////////////////////////////////
// Check current Forum Category Order and display link
// If at top only show move down button
// If at bottom only show move up button
// Anywhere else show both move up or down buttons
//////////////////////////////////////////////////
function forumMoveCatOrder($fot_id,$f_title,$cat_order_id){
	global $mysqli, $db_table_prefix, $site_forum_title, $session_token_num, $debug_website;
	// Check to see if admin or mod wants to move the cat up or down
	if(isset($_POST['MoveCatUp'])){ $MoveCatUp = $_POST['MoveCatUp']; }else{ $MoveCatUp = "FALSE"; }
	if(isset($_POST['MoveCatDown'])){ $MoveCatDown = $_POST['MoveCatDown']; }else{ $MoveCatDown = "FALSE"; }
	if(isset($_POST['forum_order_id'])){ $forum_order_id = $_POST['forum_order_id']; }else{ $forum_order_id = "FALSE"; }
	if(isset($_POST['forum_title'])){ $forum_title = $_POST['forum_title']; }else{ $forum_title = ""; }
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
				echo " User Wants to Move Cat Up - $forum_order_id - $forum_title ";
				
					// Using the following to change the order of the forum categories for now
					// Will look into a better way of handling this function in the future
				
					// First Lets Change the Rows we want to move to default 999999999
					$new_value = "999999999";
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_cat=? WHERE forum_order_cat=? AND forum_title=?");
					$stmt->bind_param("iis", $new_value, $forum_order_id, $forum_title);
					if($stmt->execute()){ $no_f_m_errors = "TRUE"; }
					$stmt->close();

					// Ok now we set the swap value for the cat we are swapping with
					$change_count = 1;
					$change_value = $forum_order_id - $change_count;
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_cat=? WHERE forum_order_cat=? AND forum_title=?");
					$stmt->bind_param("iis", $forum_order_id, $change_value, $forum_title);
					if($stmt->execute()){ $no_f_m_errors = "TRUE"; }
					$stmt->close();
					
					// Set the moved target to new value
					$change_count = 1;
					$minus_one = $forum_order_id - $change_count;
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_cat=? WHERE forum_order_cat=? AND forum_title=?");
					$stmt->bind_param("iis", $minus_one, $new_value, $forum_title);
					if($stmt->execute()){ $no_f_m_errors = "TRUE"; }
					$stmt->close();
					
					if($no_f_m_errors == "TRUE"){
						//Sends success message to session
						//Shows user success when they are redirected
						$success_msg = "You Have Successfully Moved Forum Category!";
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
						err_message('There Was an Error Moving Forum Category!');
						die;
					}
			}
			// Check if user is moving cat down
			if($MoveCatDown == "TRUE"){
				echo " User Wants to Move Cat Down - $forum_order_id - $forum_title";
				
					// Using the following to change the order of the forum categories for now
					// Will look into a better way of handling this function in the future
				
					// First Lets Change the Rows we want to move to default 999999999
					$new_value = "999999999";
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_cat=? WHERE forum_order_cat=? AND forum_title=?");
					$stmt->bind_param("iis", $new_value, $forum_order_id, $forum_title);
					if($stmt->execute()){ $no_f_m_errors = "TRUE"; }
					$stmt->close();

					// Ok now we set the swap value for the cat we are swapping with
					$change_count = 1;
					$change_value = $forum_order_id + $change_count;
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_cat=? WHERE forum_order_cat=? AND forum_title=?");
					$stmt->bind_param("iis", $forum_order_id, $change_value, $forum_title);
					if($stmt->execute()){ $no_f_m_errors = "TRUE"; }
					$stmt->close();
					
					// Set the moved target to new value
					$change_count = 1;
					$minus_one = $forum_order_id + $change_count;
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_cat=? WHERE forum_order_cat=? AND forum_title=?");
					$stmt->bind_param("iis", $minus_one, $new_value, $forum_title);
					if($stmt->execute()){ $no_f_m_errors = "TRUE"; }
					$stmt->close();
					
					if($no_f_m_errors == "TRUE"){
						//Sends success message to session
						//Shows user success when they are redirected
						$success_msg = "You Have Successfully Moved Forum Category!";
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
						err_message('There Was an Error Moving Forum Category!');
						die;
					}
			}
		}
	}else{
		// Get highest number listed in cat order
		$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_name`='$site_forum_title' AND `forum_title`='$f_title' ORDER BY `forum_order_cat` DESC LIMIT 1";
		$result = $mysqli->query($query);
		$arr = $result->fetch_all(MYSQLI_BOTH);
		foreach($arr as $row)
		{
			$f_order_cat = $row['forum_order_cat'];
			//echo " $fot_id - $cat_order_id of $f_order_cat - $f_title ";
			if($cat_order_id == 1)
			{
				// Form button to move cat down
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo "<input type=\"hidden\" name=\"forum_order_id\" value=\"$cat_order_id\" />";
					echo "<input type=\"hidden\" name=\"forum_title\" value=\"$f_title\" />";
					echo "<input type=\"hidden\" name=\"MoveCatDown\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Move Down\" name=\"Move Down\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
			}
			else if($cat_order_id == $f_order_cat)
			{
				// Form button to move cat up
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo "<input type=\"hidden\" name=\"forum_order_id\" value=\"$cat_order_id\" />";
					echo "<input type=\"hidden\" name=\"forum_title\" value=\"$f_title\" />";
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
					echo "<input type=\"hidden\" name=\"forum_order_id\" value=\"$cat_order_id\" />";
					echo "<input type=\"hidden\" name=\"forum_title\" value=\"$f_title\" />";
					echo "<input type=\"hidden\" name=\"MoveCatUp\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Move Up\" name=\"Move Up\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
				
				// Form button to move cat down
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo "<input type=\"hidden\" name=\"forum_order_id\" value=\"$cat_order_id\" />";
					echo "<input type=\"hidden\" name=\"forum_title\" value=\"$f_title\" />";
					echo "<input type=\"hidden\" name=\"MoveCatDown\" value=\"TRUE\" />";
					echo "<input type=\"submit\" value=\"Move Down\" name=\"Move Down\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
			}
		}
	}
}

//////////////////////////////////////////////////
// Allow Admin to Create New Forum Categories
//////////////////////////////////////////////////
function forumCatNew($f_title){
	// Check to see if admin or mod is viewing forum. 
	// Only show new cat form if admin or mod.
	if(userCheckForumAdmin() || userCheckForumMod()){
		// Check is user is creating a new cat
		if(isset($_POST['AdminCreateCat'])){ $AdminCreateCat = $_POST['AdminCreateCat']; }else{ $AdminCreateCat = "FALSE"; }
		if(isset($_POST['forum_cat_create'])){ $forum_cat_create = $_POST['forum_cat_create']; }else{ $forum_cat_create = ""; }
		if(isset($_POST['forum_des_create'])){ $forum_des_create = $_POST['forum_des_create']; }else{ $forum_des_create = ""; }
		if(isset($_POST['forum_title'])){ $forum_title = $_POST['forum_title']; }else{ $forum_title = ""; }
		global $mysqli, $websiteUrl, $db_table_prefix, $session_token_num, $site_forum_title, $debug_website;
		if($AdminCreateCat == "TRUE"){
			//Token validation function
			if(!is_valid_token()){ 
				//Token does not match
				err_message('Sorry, Tokens do not match!  Please go back and try again.');
				die;
			}else{
				// Check to see if this is the first forum cat submitted to the forum title
				// If so then update the existing row for the title
				$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_name`='$site_forum_title' AND `forum_title`='$forum_title' AND forum_cat<>'' ";
				if ($stmt = $mysqli->prepare($query)) {
					$stmt->execute();
					$stmt->store_result();
					$total_rows = $stmt->num_rows;
				}
				$stmt->close();
				echo " ( $total_rows ) ";
				
				if($total_rows == '0'){
					// Update the existing title row
					// Update Database with new cat
					$number_one = "1";
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_order_cat=?, forum_cat=?, forum_des=? WHERE forum_name=? AND forum_title=?");
					$stmt->bind_param("issss", $number_one, $forum_cat_create, $forum_des_create, $site_forum_title, $forum_title);
					$stmt->execute();
					$stmt->close();
				}else{
					// Create a new title row
					// Get highest number listed in cat order
					$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_name`='$site_forum_title' AND `forum_title`='$forum_title' GROUP BY `forum_title` ORDER BY `forum_order_cat` DESC LIMIT 1 ";
					$result = $mysqli->query($query);
					$arr = $result->fetch_all(MYSQLI_BOTH);
					foreach($arr as $row)
					{
						$f_order_cat = $row['forum_order_cat'];
						$next_order_number = $f_order_cat + 1;
					}
					
					// Update Database with new cat
					$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."forum_cat SET forum_name=?, forum_title=?, forum_order_cat=?, forum_cat=?, forum_des=?");
					$stmt->bind_param("ssiss", $site_forum_title, $forum_title, $next_order_number, $forum_cat_create, $forum_des_create);
					$stmt->execute();
					$stmt->close();
				}
					
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Created Forum Cat!";
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
		}else{
			// Show create cat form
			echo "<table width='100%'><tr><td>";
				echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
					// Setup token in form // create multi sessions
					if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
					form_token();
					echo " <label>Create New Category:</label> ";
					echo "<input name=\"forum_cat_create\" type=\"text\" value=\"New Category\" style='width:50%;font-family:verdana;font-size:12px;font-weight:bold'><br>";
					echo " <label>Category Description:</label> ";
					echo "<input name=\"forum_des_create\" type=\"text\" value=\"Description\" style='width:75%;font-family:verdana;font-size:12px;font-weight:normal'>";
					echo "<input type=\"hidden\" name=\"AdminCreateCat\" value=\"TRUE\" />";
					echo "<input type=\"hidden\" name=\"forum_title\" value=\"$f_title\" />";
					echo "<input type=\"submit\" value=\"Create Category\" name=\"Create Category\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form>";
			echo "</td></tr></table>";
		}
	}
}

//////////////////////////////////////////////////
// Allow admin to edit forum cats
//////////////////////////////////////////////////
function forumEditCatCheck($f_cat,$f_des,$f_id2){
	global $mysqli, $db_table_prefix, $load_page_dir, $session_token_num, $debug_website, $websiteUrl, $site_forum_title;
	// Check to see if mod is updating a forum cat
	if(isset($_POST['AdminEditCat'])){ $AdminEditCat = $_POST['AdminEditCat']; }else{ $AdminEditCat = "FALSE"; }
	if(isset($_POST['forum_cat_old'])){ $forum_cat_old = $_POST['forum_cat_old']; }else{ $forum_cat_old = ""; }
	if(isset($_POST['forum_cat_new'])){ $forum_cat_new = $_POST['forum_cat_new']; }else{ $forum_cat_new = ""; }
	if(isset($_POST['forum_des_old'])){ $forum_des_old = $_POST['forum_des_old']; }else{ $forum_des_old = ""; }
	if(isset($_POST['forum_des_new'])){ $forum_des_new = $_POST['forum_des_new']; }else{ $forum_des_new = ""; }
	if(isset($_POST['forum_id_edit'])){ $forum_id_edit = $_POST['forum_id_edit']; }else{ $forum_id_edit = ""; }
	if($AdminEditCat == "TRUE"){
		//Token validation function
		if(!is_valid_token()){ 
			//Token does not match
			err_message('Sorry, Tokens do not match!  Please go back and try again.');
			die;
		}else{
			// Update Database with new cat
			$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_cat SET forum_cat=?, forum_des=? WHERE forum_id=?");
			$stmt->bind_param("ssi", $forum_cat_new, $forum_des_new, $forum_id_edit);
			if($stmt->execute()){
				$stmt->close();
				
				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Updated Forum Cat!";
				$_SESSION['success_msg'] = $success_msg;
				
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $websiteUrl, $site_forum_cat;
					$form_redir_link = "${websiteUrl}${site_forum_title}/";
					// Redirect member to their post
					header("Location: $form_redir_link");
					exit;
				}
			}
			else
			{
				err_message('Oops. There was an error. 5468');
				die;
			}
		}
	}else{
		if(isset($_POST['EditCat'])){ $EditCat = $_POST['EditCat']; }else{ $EditCat = "FALSE"; }
		if(isset($_POST['forum_cat'])){ $forum_cat = $_POST['forum_cat']; }else{ $forum_cat = ""; }
		if(isset($_POST['forum_des'])){ $forum_des = $_POST['forum_des']; }else{ $forum_des = ""; }
		if(isset($_POST['forum_id_edit'])){ $forum_id_edit = $_POST['forum_id_edit']; }else{ $forum_id_edit	= ""; }
		// Make sure user has permission to edit this cat
		if((userCheckForumAdmin() || userCheckForumMod()) && ($EditCat == "TRUE" && $forum_cat == $f_cat && $f_id2 == $forum_id_edit)){
			// Mod or Admin would like to edit a cat
			// Show edit forum in place of cat
			echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
				// Setup token in form // create multi sessions
				if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
				form_token();
				echo "<input name=\"forum_cat_new\" type=\"text\" value=\"${f_cat}\" style='width:200px;font-family:verdana;font-size:12px;font-weight:bold'><BR>";
				echo "<input name=\"forum_des_new\" type=\"text\" value=\"${f_des}\" style='width:300px;font-family:verdana;font-size:12px;font-weight:normal'>";
				echo "<input type=\"hidden\" name=\"forum_cat_old\" value=\"$f_cat\" />";
				echo "<input type=\"hidden\" name=\"forum_des_old\" value=\"$f_des\" />";
				echo "<input type=\"hidden\" name=\"forum_id_edit\" value=\"$f_id2\" />";
				echo "<input type=\"hidden\" name=\"AdminEditCat\" value=\"TRUE\" />";
				echo "<input type=\"submit\" value=\"Update\" name=\"Update\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
			echo "</form>";
		}
		else
		{
			global $websiteUrl, $site_forum_cat;
			echo "<h3><a href='${websiteUrl}${site_forum_title}/forum_display/$f_cat/$f_id2/' title='$f_cat' ALT='$f_cat'>$f_cat</a></h3>";
			echo " - $f_des";
		}
	}
}

//////////////////////////////////////////////////
// Allow admin to edit and delete forum Cats
//////////////////////////////////////////////////
function forumEditCat($f_cat,$f_des,$f_id2){
	global $mysqli, $db_table_prefix, $load_page_dir, $session_token_num, $websiteUrl, $site_forum_title;
	// Form button to edit forum cat
	echo "<form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
		// Setup token in form // create multi sessions
		if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
		form_token();
		echo "<input type=\"hidden\" name=\"forum_cat\" value=\"$f_cat\" />";
		echo "<input type=\"hidden\" name=\"forum_id_edit\" value=\"$f_id2\" />";
		echo "<input type=\"hidden\" name=\"EditCat\" value=\"TRUE\" />";
		echo "<input type=\"submit\" value=\"Edit\" name=\"Edit\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
	echo "</form>";
	
	// Only Admins Can Delete Forum Cats
	if(userCheckForumAdmin()){
		// Form button to delete forum cat
		echo "<form enctype=\"multipart/form-data\" action=\"${websiteUrl}${site_forum_title}/forum_delete_stuff/\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" class='sweetform' >";
			// Setup token in form // create multi sessions
			if(isset($session_token_num)){$session_token_num = $session_token_num + 1;}else{$session_token_num = "1";}
			form_token();
			echo "<input type=\"hidden\" name=\"forum_cat\" value=\"$f_cat\" />";
			echo "<input type=\"hidden\" name=\"forum_id_edit\" value=\"$f_id2\" />";
			echo "<input type=\"hidden\" name=\"DeleteCat\" value=\"TRUE\" />";
			echo "<input type=\"submit\" value=\"Delete\" name=\"Delete\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
		echo "</form>";
	}
}

//////////////////////////////////////////////////
// Forum Edit and Delete Function
//////////////////////////////////////////////////
function forumCatEditDelete($f_cat,$f_des,$f_id2){
	// Double check to make sure user is admin or mod
	if(userCheckForumAdmin() || userCheckForumMod()){
		// Table to make forum look neat
		echo "</td><td width='100px' align='right'>";
		// Forum Cat Edit
		// Check to see if user wants to edit or delete a cat.
		forumEditCat($f_cat,$f_des,$f_id2);
	}
}

//////////////////////////////////////////////////
// Display the edit delete button for forum categories
//////////////////////////////////////////////////
function forumCatEdit($fot_id,$f_title,$cat_order_id,$f_cat,$f_des,$f_id2){
	if(userCheckForumAdmin() || userCheckForumMod()){
		// Display Edit, Delete, and Move Buttons
		echo "</td></tr><tr><td colspan=2 align=right>";
		// Display Edit and Move buttons to mods and admins
		forumMoveCatOrder($fot_id,$f_title,$cat_order_id);
		// Display Edit and Delete buttons to mods and admins
		forumCatEditDelete($f_cat,$f_des,$f_id2);
	}
}

//////////////////////////////////////////////////
// Forum Topic Status - Open(1) - Locked(2)
//////////////////////////////////////////////////
function forumTopicStatus($fs_setting, $f_status, $f_p_id){
	global $mysqli, $db_table_prefix, $site_url_link, $site_forum_title, $session_token_num;	
	// If display_note just show a message that says locked if locked
	if($fs_setting == "display_note" && $f_status == "2"){
		echo " <strong><font color='red'>Topic Locked</font></strong> ";
	}
	// If admin or mod logged in let them lock or unlock the topic
	if($fs_setting == "admin_topic"){
		if(userCheckForumAdmin() || userCheckForumMod()){
			// If topic is locked then show unlock button
			if($f_status == "2"){
				if(isset($_POST['forum_post_id'])){ $forum_post_id = $_POST['forum_post_id']; }else{ $forum_post_id = ""; }
				if(isset($_POST['unlock_topic'])){ $unlock_topic = $_POST['unlock_topic']; }else{ $unlock_topic = ""; }
				// Check to see if admin or mod is unlocking this topic
				if($unlock_topic == "TRUE"){	
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_posts SET forum_status=1 WHERE forum_post_id=? LIMIT 1");
					$stmt->bind_param("i", $forum_post_id);
					$stmt->execute();				
					//echo $stmt->error;
					$stmt->close();	
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully UnLocked this Topic!";
					$_SESSION['success_msg'] = $success_msg;
				
					//Disables auto refresh for debug stuff
					if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
						// Redirect member to their post
						header("Location: ");
						exit;
					}
				}else{
					echo "<br><br><form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" >";
						// Setup forum token
						if(isset($session_token_num)){ $session_token_num = $session_token_num + 1; }else{ $session_token_num = "1"; }
						form_token();				
						echo "<input type=\"hidden\" name=\"forum_post_id\" value=\"$f_p_id\" />";
						echo "<input type=\"hidden\" name=\"unlock_topic\" value=\"TRUE\" />";
						echo "<input type=\"submit\" value=\"UnLock Topic\" name=\"UnLock Topic\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
					echo "</form>";
				}
			}
			// Otherwise show lock button
			else{
				if(isset($_POST['forum_post_id'])){ $forum_post_id = $_POST['forum_post_id']; }else{ $forum_post_id = ""; }
				if(isset($_POST['lock_topic'])){ $lock_topic = $_POST['lock_topic']; }else{ $lock_topic = ""; }
				// Check to see if admin or mod is unlocking this topic
				if($lock_topic == "TRUE"){	
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_posts SET forum_status=2 WHERE forum_post_id=? LIMIT 1");
					$stmt->bind_param("i", $forum_post_id);
					$stmt->execute();				
					//echo $stmt->error;
					$stmt->close();	
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Locked this Topic!";
					$_SESSION['success_msg'] = $success_msg;
				
					//Disables auto refresh for debug stuff
					if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
						// Redirect member to their post
						header("Location: ");
						exit;
					}
				}else{
					echo "<br><br><form enctype=\"multipart/form-data\" action=\"\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" >";
						// Setup forum token
						if(isset($session_token_num)){ $session_token_num = $session_token_num + 1; }else{ $session_token_num = "1"; }
						form_token();				
						echo "<input type=\"hidden\" name=\"forum_post_id\" value=\"$f_p_id\" />";
						echo "<input type=\"hidden\" name=\"lock_topic\" value=\"TRUE\" />";
						echo "<input type=\"submit\" value=\"Lock Topic\" name=\"Lock Topic\" class=\"unsweet\" onClick=\"this.value = 'Please Wait....'\" />";
					echo "</form>";
				}
			}
		}
	}
}

?>