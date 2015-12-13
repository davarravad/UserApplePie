<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isUserLoggedIn())
{
   // saving script
   // get the variables from the URL POST string

	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{

		global $websiteName;
	
		// Page title
		$stc_page_title = "$websiteName Forum";
		// Page Description
		$stc_page_description = "Welcome to $websiteName Forum.  Ask questions and get answers from fellow members.";
		// Run Top of page func
		style_header_content($stc_page_title, $stc_page_description);
		// Which database do we use
		$stc_page_sel = "Forum";
	
			if(isset($_POST['forum_id'])){ $forum_id = $_POST['forum_id']; }else{ $forum_id = ""; }
			if(isset($_POST['forum_post_id'])){ $forum_post_id = $_POST['forum_post_id']; }else{ $forum_post_id = ""; }
			if(isset($_POST['forum_title'])){ $forum_title = $_POST['forum_title']; }else{ $forum_title = ""; }
			if(isset($_POST['forum_content'])){ $forum_content = $_POST['forum_content']; }else{ $forum_content = ""; }
			if(isset($_POST['id'])){ $id = $_POST['id']; }else{ $id = ""; }
			if(isset($_POST['edit_forum_reply'])){ $edit_forum_reply = $_POST['edit_forum_reply']; }else{ $edit_forum_reply = ""; }
			if(isset($_POST['edit_forum_topic'])){ $edit_forum_topic = $_POST['edit_forum_topic']; }else{ $edit_forum_topic = ""; }
			if(isset($_POST['pnum'])){ $pnum = $_POST['pnum']; }else{ $pnum = ""; }
			if(isset($_POST['forum_year'])){ $forum_year = $_POST['forum_year']; }else{ $forum_year = ""; }
			if(isset($_POST['forum_make'])){ $forum_make = $_POST['forum_make']; }else{ $forum_make = ""; }
			if(isset($_POST['forum_model'])){ $forum_model = $_POST['forum_model']; }else{ $forum_model = ""; }
			if(isset($_POST['forum_engine'])){ $forum_engine = $_POST['forum_engine']; }else{ $forum_engine = ""; }
			
			global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;
			global $session_token_num;
			
			// Test
			//echo " (ID=$id) ";

				// Get all Categories from database
				$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_id`='$forum_id' LIMIT 1";
				$result = $mysqli->query($query);
				$arr = $result->fetch_all(MYSQLI_BOTH);
				foreach($arr as $row)
				{
					$f_cat = $row['forum_cat'];
					$f_des = $row['forum_des'];
					$f_id = $row['forum_id'];
					
					$f_des = stripslashes($f_des);
					$f_des = stripslashes($f_des);

					// Display Link of where we are at on the forum
					echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td>";
						echo "<a href='${site_url_link}${site_forum_title}/'>Forum Home</a> / ";
						echo "<a href='${site_url_link}${site_forum_title}/forum_display/$f_cat/$f_id/'>$f_cat</a>";
					echo "</td></tr></table>";
				}
			
			echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class=hr2>";
			if($edit_forum_reply == "TRUE"){
				echo "<strong>Edit Reply</strong>";
				
					// Get main post from database
					$query3 = "SELECT * FROM ".$db_table_prefix."forum_posts_replys WHERE `id`='$id' LIMIT 1";
					$result3 = $mysqli->query($query3);
					$arr3 = $result3->fetch_all(MYSQLI_BOTH);
					foreach($arr3 as $row3)
					{
						$owner_uid = $row3['fpr_user_id'];
						$forum_content = $row3['fpr_content'];
					}
					// Check to see if user owns the content they are trying to edit
					global $site_url_link, $site_forum_title, $userIdme;
	
					// Test
					//echo " ($owner_uid-$userIdme) ";
					
					if($owner_uid != $userIdme){
						$redir_link_884 = "${site_url_link}${site_forum_title}/display_topic/${forum_post_id}/";

						// Redirect member to their post
						header("Location: $redir_link_884");
						exit;
					}
					
			}else if($edit_forum_topic == "TRUE"){
				echo "<strong>Edit Topic</strong>";
					// Get main post from database
					$query3 = "SELECT * FROM ".$db_table_prefix."forum_posts WHERE `forum_post_id`='$id' LIMIT 1";
					$result3 = $mysqli->query($query3);
					$arr3 = $result3->fetch_all(MYSQLI_BOTH);
					foreach($arr3 as $row3)
					{
						$owner_uid = $row3['forum_user_id'];
						$forum_title = $row3['forum_title'];
						$forum_content = $row3['forum_content'];
						$forum_year = $row3['forum_year'];
						$forum_make = $row3['forum_make'];
						$forum_model = $row3['forum_model'];
						$forum_engine = $row3['forum_engine'];
					}
					// Check to see if user owns the content they are trying to edit
					global $site_url_link, $site_forum_title, $userIdme;
	
					// Test
					//echo " ($owner_uid-$userIdme) ";
					
					if($owner_uid != $userIdme){
						$redir_link_884 = "${site_url_link}${site_forum_title}/display_topic/${forum_post_id}/";

						// Redirect member to their post
						header("Location: $redir_link_884");
						exit;
					}				
			}else{
				echo "<strong>New Topic</strong>";
			}
			echo "</td></tr><tr><td class='content78'>";
				
			echo "<form enctype=\"multipart/form-data\" action=\"${site_url_link}${site_forum_title}/save_topic/${forum_id}/\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" >";
				
				// create multi sessions
				if(isset($session_token_num)){
					$session_token_num = $session_token_num + 1;
				}else{
					$session_token_num = "1";
				}
				form_token();

				// Hides the title if this is an edit for topic reply
				if(empty($edit_forum_reply)){
					// Cleans up the content
					if(!empty($forum_title)){
						$forum_title = stripslashes($forum_title);
					}
					echo "<strong>Topic Title</strong><br>";
					echo "<input name=\"forum_title\" type=\"text\" value=\"${forum_title}\" style='width:100%;font-family:verdana;font-size:12px'><br>";
					

					
					echo "<strong>Topic Content</strong><br>";
				}
				
				// Cleans up the content
				if(!empty($forum_content)){
					$forum_content = stripslashes($forum_content);
				}
				
				echo "<textarea style='width:100%;height:200px;font-family:verdana;font-size:12px' name='forum_content' id='forum_content'>${forum_content}</textarea>";
				echo "<br>";
				echo "<input type=\"hidden\" name=\"forum_id\" value=\"$forum_id\" />";
				
				if($edit_forum_reply == "TRUE"){
					echo "<input type=\"hidden\" name=\"edit_forum_reply\" value=\"TRUE\" />";	
					echo "<input type=\"hidden\" name=\"pnum\" value=\"$pnum\" />";
					echo "<input type=\"hidden\" name=\"id\" value=\"$id\" />";
					echo "<input type=\"hidden\" name=\"forum_post_id\" value=\"$forum_post_id\" />";
					echo "<br><center>";
					echo "<input type=\"submit\" value=\"Update Reply\" name=\"updatereply\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
					echo "</center>";				
				}else if($edit_forum_topic == "TRUE"){
					echo "<input type=\"hidden\" name=\"edit_forum_topic\" value=\"TRUE\" />";	
					echo "<input type=\"hidden\" name=\"id\" value=\"$id\" />";
					echo "<input type=\"hidden\" name=\"forum_post_id\" value=\"$forum_post_id\" />";
					echo "<br><center>";
					echo "<input type=\"submit\" value=\"Update Topic\" name=\"updatetopic\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
					echo "</center>";				
				}else{
					echo "<input type=\"hidden\" name=\"insert_new_topic\" value=\"TRUE\" />";				
					echo "<br><center>";
					echo "<input type=\"checkbox\" name=\"subcribe_email\" value=\"YES\" checked=\"checked\"> Subscribe to E-Mail Notifications for this Topic<br>";
					echo "<input type=\"submit\" value=\"Create Topic\" name=\"createtopic\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
					echo "</center>";
				}
				
			echo "</form>";
			
			echo "
				<center><strong>Your Reply Preview</strong></center>
				<pre class='forum'>
				<DIV id=preview class=scroll style=\"BORDER-RIGHT: #c0c0c0 1px solid; PADDING-RIGHT: 3px;
				BORDER-TOP: #c0c0c0 1px solid; PADDING-LEFT: 3px; PADDING-BOTTOM: 3px; BORDER-LEFT: #c0c0c0 1px solid; WIDTH: 98%;
				PADDING-TOP: 3px; BORDER-BOTTOM: #c0c0c0 1px solid; HEIGHT: 150px; overflow:scroll\"></DIV>
				</pre>
			";
			
			echo "</td></tr></table>";

				
		// Run Footer of page func
		style_footer_content();
?>

	<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.3.2/jquery.min.js" type="text/javascript"></script>
	<script src='/models/jquery.bbcode.js' type='text/javascript'></script>
	<script type=text/javascript>
	  $(document).ready(function(){
		$("#forum_content").bbcode({tag_bold:true,tag_italic:true,tag_underline:true,tag_link:true,tag_image:true,button_image:true});
		process();
	  });
	 
	  var bbcode="";
	  function process()
	  {
		if (bbcode != $("#forum_content").val())
		  {
			bbcode = $("#forum_content").val();
			$.get('/models/bbParser.php',
			{
			  bbcode: bbcode
			},
			function(txt){
			  $("#preview").html(txt);
			})
		  }
		setTimeout("process()", 2000);
	  }
	</script>


<?php		
	} // End of token check
} // End of log in check
?>