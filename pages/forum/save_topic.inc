<?php

if(isUserLoggedIn())
{
	// saving script
	// get the variables from the URL POST string

	// Get info from post for save or back script
	if(isset($_POST['forum_id'])){ $forum_id = $_POST['forum_id']; }else{ $forum_id = ""; }
	if(isset($_POST['forum_post_id'])){ $forum_post_id = $_POST['forum_post_id']; }else{ $forum_post_id = ""; }
	if(isset($_POST['forum_title'])){ $forum_title = $_POST['forum_title']; }else{ $forum_title = ""; }
	if(isset($_POST['forum_content'])){ $forum_content = $_POST['forum_content']; }else{ $forum_content = ""; }
	if(isset($_POST['insert_new_topic'])){ $insert_new_topic = $_POST['insert_new_topic']; }else{ $insert_new_topic = ""; }
	if(isset($_POST['insert_reply_topic'])){ $insert_reply_topic = $_POST['insert_reply_topic']; }else{ $insert_reply_topic = ""; }
	if(isset($_POST['id'])){ $id = $_POST['id']; }else{ $id = ""; }
	if(isset($_POST['edit_forum_reply'])){ $edit_forum_reply = $_POST['edit_forum_reply']; }else{ $edit_forum_reply = ""; }
	if(isset($_POST['edit_forum_topic'])){ $edit_forum_topic = $_POST['edit_forum_topic']; }else{ $edit_forum_topic = ""; }
	if(isset($_POST['pnum'])){ $pnum = $_POST['pnum']; }else{ $pnum = ""; }
	if(isset($_POST['forum_year'])){ $forum_year = $_POST['forum_year']; }else{ $forum_year = ""; }
	if(isset($_POST['make'])){ $forum_make = $_POST['make']; }else{ $forum_make = ""; }
	if(isset($_POST['model'])){ $forum_model = $_POST['model']; }else{ $forum_model = ""; }
	if(isset($_POST['forum_engine'])){ $forum_engine = $_POST['forum_engine']; }else{ $forum_engine = ""; }
	if(isset($_POST['subcribe_email'])){ $subcribe_email = $_POST['subcribe_email']; }else{ $subcribe_email = "NO"; }
	if(isset($_POST['unsubscribe_topic'])){ $unsubscribe_topic = $_POST['unsubscribe_topic']; }else{ $unsubscribe_topic = ""; }
   
	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		
		// Show Form back button
		echo "
			
		";
		
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{
			
		// Format the text area for database
		$forum_content = htmlspecialchars(addslashes($forum_content));
		// Format the text box for database
		$forum_title = htmlspecialchars(strip_tags(addslashes($forum_title)));
		
		global $mysqli, $site_url_link, $userIdme, $site_forum_title, $db_table_prefix, $debug_website, $websiteName, $websiteUrl;
		
		echo "save now - $forum_id - $forum_title - $forum_content - $insert_new_topic - $userIdme";
		echo " (ID=$id) ";
		echo "<br> Subcribe to email: $subcribe_email";
		
		// Setup current time for timestamps
		$date_time = new DateTime();
		$cur_date_time = $date_time->format('Y-m-d H:i:s');
		
		// Create new topic
		// Save the information to the database
		if($insert_new_topic == "TRUE"){
				$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."forum_posts(forum_id, forum_user_id, forum_title, forum_content, forum_timestamp, forum_year, forum_make, forum_model, forum_engine, subcribe_email) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
				$stmt->bind_param("iissssssss", $forum_id, $userIdme, $forum_title, $forum_content, $cur_date_time, $forum_year, $forum_make, $forum_model, $forum_engine, $subcribe_email);
				$stmt->execute();
				$newId = $stmt->insert_id;
				
				//echo $stmt->error;
				
				$stmt->close();	
				$redir_link_url = "${site_url_link}${site_forum_title}/display_topic/${newId}/";
				
				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Created a Topic!";
				$_SESSION['success_msg'] = $success_msg;
				
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $site_url_link;
					
					// Redirect member to their post
					header("Location: $redir_link_url");
					exit;

				}
		}
		
		// Edit topic
		// Save the information to the database
		if($edit_forum_topic == "TRUE"){		
				$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_posts SET forum_title=?, forum_content=?, forum_year=?, forum_make=?, forum_model=?, forum_engine=?, forum_edit_date=? WHERE forum_post_id=? LIMIT 1");
				$stmt->bind_param("sssssssi", $forum_title, $forum_content, $forum_year, $forum_make, $forum_model, $forum_engine, $cur_date_time, $id);
				$stmt->execute();
				$newId = $stmt->insert_id;
				
				//echo $stmt->error;
				
				$stmt->close();	
				$redir_link_url = "${site_url_link}${site_forum_title}/display_topic/${forum_post_id}/";

				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Updated a Topic!";
				$_SESSION['success_msg'] = $success_msg;
				
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $site_url_link;
					
					
					// Redirect member to their post
					header("Location: $redir_link_url");
					exit;

				}
		}
		
		// Quick reply for topic
		// Save the information to the database
		if($insert_reply_topic == "TRUE"){
				$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."forum_posts_replys(fpr_id, fpr_post_id, fpr_user_id, fpr_content, subcribe_email, fpr_timestamp) VALUES (?, ?, ?, ?, ?, ?)");
				$stmt->bind_param("iiisss", $forum_id, $forum_post_id, $userIdme, $forum_content, $subcribe_email, $cur_date_time);
				$stmt->execute();
				$newId = $stmt->insert_id;
				
				//echo $stmt->error;
				
				$stmt->close();	
				
				// Check to see how many pages there are
				// If less than or equal to 10 then don't show pnum in link
				if($newId <= '10'){
					$setup_pnum = "#topicreply$newId";
				}else{
					// If id is greater than 10 show a pnum link
					// Get page number for post
					$ttl_posts = "$newId";
					$ttl_posts = ($ttl_posts - 1);
					$ttl_limit = "5";
					$page_num_yo = ($ttl_posts / $ttl_limit);
					$page_num_yo = floor($page_num_yo);
					$page_num_yo = ($page_num_yo + 1);
					$setup_pnum = "?pnum=99999999#topicreply$newId";
				}
				
				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Created a Topic Reply!";
				$_SESSION['success_msg'] = $success_msg;
				
				$redir_link_url = "${site_url_link}${site_forum_title}/display_topic/${forum_post_id}/$setup_pnum";
				
				//Update all current user's email sub status if any for this topic
				//forum_posts database
				$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_posts SET subcribe_email=? WHERE forum_post_id=? AND forum_user_id=? ");
				$stmt->bind_param("sii", $subcribe_email, $forum_post_id, $userIdme);
				$stmt->execute();
				//echo $stmt->error;
				$stmt->close();	
				//forum_posts_replys database
				$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_posts_replys SET subcribe_email=? WHERE fpr_post_id=? AND fpr_user_id=? ");
				$stmt->bind_param("sii", $subcribe_email, $forum_post_id, $userIdme);
				$stmt->execute();
				//echo $stmt->error;
				$stmt->close();	
				
				//Sends email to all users that posted in the topic
				
				//Topic Id
				$f_topic_id = $forum_post_id;
				echo "<br>Topic Id: $f_topic_id<br>"; //Test
				
				//Topic Category Id
				$f_topic_cat_id = $forum_id;
				echo "<br>Topic Category Id: $f_topic_cat_id<br>"; //Test
				
				//Current User ID
				$f_cur_usr_id = $userIdme;
				echo "<br>Current User Id: $f_cur_usr_id<br>"; //Test
			
				//Topic Category for email output
				// Get Category Title from database
				$stmt = $mysqli->prepare("SELECT 
					forum_cat, forum_title
					FROM ".$db_table_prefix."forum_cat WHERE forum_id=?");
				$stmt->bind_param("i", $f_topic_cat_id);
				$stmt->execute();
				$stmt->bind_result($forum_cat, $forum_title);
				$stmt->fetch();
				$stmt->close();
				$forum_title = stripslashes($forum_title);
				$forum_cat = stripslashes($forum_cat);
				$f_cur_topic_cat = "$forum_title - $forum_cat";
				
				//Topic Title for email output 
				// Get Post Title from database
				$stmt = $mysqli->prepare("SELECT 
					forum_title
					FROM ".$db_table_prefix."forum_posts WHERE forum_post_id=?");
				$stmt->bind_param("i", $f_topic_id);
				$stmt->execute();
				$stmt->bind_result($forum_title);
				$stmt->fetch();
				$stmt->close();
				$forum_title = stripslashes($forum_title);
				$f_cur_topic_title = $forum_title;
				
				echo "<hr>"; //For Testing				
				
				echo "List of users that have posted in this topic along with thier emails<br><br>";
				
				//Get User Ids based on forum topic id
				//Only sends one email per user except the user currently posting
				//Use Join to get the original posters email
				
				$query_get_uids = "
					SELECT * FROM (
						(
						SELECT fpr_user_id AS F_UID
						FROM ".$db_table_prefix."forum_posts_replys 
						WHERE fpr_post_id = '$f_topic_id' 
						AND subcribe_email = 'YES'
						AND NOT fpr_user_id = '$f_cur_usr_id'
						GROUP BY fpr_user_id
						ORDER BY fpr_timestamp DESC
						)
						UNION ALL
						(
						SELECT forum_user_id AS F_UID
						FROM ".$db_table_prefix."forum_posts
						WHERE forum_post_id = '$f_topic_id'
						AND subcribe_email = 'YES'
						AND NOT forum_user_id = '$f_cur_usr_id'
						GROUP BY forum_user_id
						ORDER BY forum_timestamp DESC
						) 
                    ) AS uniontable
					GROUP BY `F_UID`
                    ORDER BY `F_UID` ASC
				";
					

					
				if($result_get_uids = $mysqli->query($query_get_uids)){
					$arr_get_uids = $result_get_uids->fetch_all(MYSQLI_BOTH);
						foreach($arr_get_uids as $row_get_uids)
						{
							$f_topic_get_user_id = $row_get_uids['F_UID']; 
							$f_topic_get_user_name = get_user_name_2($f_topic_get_user_id);	
							$f_topic_get_email = get_user_email($f_topic_get_user_id);
							$f_cur_user_name = get_user_name_2($userIdme);
							
							//Format the content with bbcode
							require_once('models/bbParser.php');
							$parser = new bbParser();
							$forum_content = $parser->getHtml($forum_content);
							
							echo "Username: $f_topic_get_user_name AND UserID: $f_topic_get_user_id AND UserEmail: OK";
							
							//Send user an email notification
							//Start of mail

									$adminmail = $f_topic_get_email;
									$usersub = "$websiteName - Forum - $f_cur_user_name replied to $f_cur_topic_title";
									$usermsg = "$websiteName - Forum Notification
															<br><br>
															Category: $f_cur_topic_cat
															<br>
															Topic: $f_cur_topic_title
															<br>
															Reply by: $f_cur_user_name
															<br><br>
															Reply Content:
															<br>
															************************<br>
															$forum_content
															<br>************************";
									$usermsg2 = " You may check the reply at <a href=$redir_link_url>$redir_link_url</a>";
									$username = "$f_cur_user_name";
									
									//Mail file that setup the email and sends it based on input above
									require "models/mail.inc";
							
							//End of mail
							
							
							echo "<br>";
						}
				}else{
					if($debug_website == 'TRUE'){}{
						// Displays query if debug is enabled
						echo "<br>No Results<br>";
						echo "<font color=red>";
						echo "$query_get_uids";
						echo "</font>";
					}
				}
				
				echo "<hr>"; //For Testing
				
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $site_url_link;
					
					
					// Redirect member to their post
					header("Location: $redir_link_url");
					exit;

				}
		}
		
		// Quick reply update edit for topic
		// Save the information to the database
		if($edit_forum_reply == "TRUE"){
				$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_posts_replys SET fpr_content=?, fpr_edit_date=? WHERE id=?");
				$stmt->bind_param("ssi", $forum_content, $cur_date_time, $id);
				$stmt->execute();
				
				echo $stmt->error;
				
				// Check to see how many pages there are
				// If less than or equal to 10 then don't show pnum in link
				if(!empty($pnum)){
					// If id is greater than 10 show a pnum link
					// Get page number for post					
					$setup_pnum = "?pnum=$pnum#topicreply$id";
				}
				
				$stmt->close();	
				$redir_link_url = "${site_url_link}${site_forum_title}/display_topic/${forum_post_id}/${setup_pnum}";
				
				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully Updated a Topic Reply!";
				$_SESSION['success_msg'] = $success_msg;
				
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $site_url_link;
					
					
					// Redirect member to their post
					header("Location: $redir_link_url");
					exit;

				}
		}
		
		// User unsubscribe request
		// Update the information in the database
		if($unsubscribe_topic == "TRUE"){
				//Update all current user's email sub status if any for this topic
				//forum_posts database
				$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_posts SET subcribe_email=? WHERE forum_post_id=? AND forum_user_id=? ");
				$stmt->bind_param("sii", $subcribe_email, $forum_post_id, $userIdme);
				$stmt->execute();
				//echo $stmt->error;
				$stmt->close();	
				//forum_posts_replys database
				$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."forum_posts_replys SET subcribe_email=? WHERE fpr_post_id=? AND fpr_user_id=? ");
				$stmt->bind_param("sii", $subcribe_email, $forum_post_id, $userIdme);
				$stmt->execute();
				//echo $stmt->error;
				$stmt->close();	
				
				$redir_link_url = "${site_url_link}${site_forum_title}/display_topic/${forum_post_id}/$setup_pnum";
				
				//Sends success message to session
				//Shows user success when they are redirected
				$success_msg = "You Have Successfully UnSubscribed from this Topic!";
				$_SESSION['success_msg'] = $success_msg;
				
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					//Redirects the user
					global $site_url_link;
					
					
					// Redirect member to their post
					header("Location: $redir_link_url");
					exit;

				}
		}
		
		// For edit date update
		// $mysql_date_now = date("Y-m-d H:i:s");

	} // End of token check
	
} // End of log in check
		
?>