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


	global $site_forum_title, $websiteName;
	// Page title
	$stc_page_title = "$websiteName - ".$site_forum_title;
	// Page Description
	$stc_page_description = "Welcome to the Forum.  Ask questions and get answers from fellow Forum members.";
	// Run Top of page func
	style_header_content($stc_page_title, $stc_page_description);

	// Main Page for forum
	
	// Check database for sections
	
	global $mysqli, $site_url_link, $site_forum_title, $db_table_prefix;
	global $session_token_num, $stc_page_sel;
	
	// Make sure all forum titles are in order
	forumCleanOrderTitle();
	
	// Get all Categories from database
	$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_name`='$stc_page_sel' GROUP BY forum_title ORDER BY `".$db_table_prefix."forum_cat`.`forum_order_title` ASC ";
	$result = $mysqli->query($query);
	$arr = $result->fetch_all(MYSQLI_BOTH);
	foreach($arr as $row)
	{
		$f_title = $row['forum_title'];
		$f_id = $row['forum_id'];
		$f_order_title = $row['forum_order_title'];
		
		// If Admin or mod is logged in check to 
		// see if categories are in order.
		// If not then fix it.
		forumCleanOrderCat($f_title);
		
		echo "<div class='panel panel-default'>";
			echo "<div class='panel-heading' style='font-weight: bold'>";
			
				//Display title or edit title field if mod and requested
				forumEditTitleCheck($f_title);

				// Display Forum Title Edit Funcs.
				if((userCheckForumAdmin() || userCheckForumMod()) && forumSHAF()){
					// Show admin feature if is admin
					// Display current order id
					//echo "Order Id: $f_order_title ";
					echo "";
						//Display Move Buttons
						forumMoveTitleOrder($f_order_title);
					echo "";
						//Display Edit/Delete Buttons
						forumEditTitle($f_title);
					echo "";
				}

			echo "</div>";
			echo "<ul class='list-group'>";
				$f_title_2 = addslashes($f_title);
				// Get all Sub Categories for current category
				$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_title`='$f_title_2' GROUP BY forum_cat ORDER BY forum_order_cat";
				$result = $mysqli->query($query);
				$arr2 = $result->fetch_all(MYSQLI_BOTH);
				foreach($arr2 as $row2)
				{
					echo "<ul class='list-group-item'>";
						$f_cat = $row2['forum_cat'];
						$f_des = $row2['forum_des'];
						$f_id2 = $row2['forum_id'];
						$cat_order_id = $row2['forum_order_cat'];
						
						$f_des = stripslashes($f_des);
						$f_cat = stripslashes($f_cat);
						
						echo "<div class='media'>";
							echo "<div class='media-body'>";
								forumEditCatCheck($f_cat,$f_des,$f_id2);
							echo "</div>";
								
								
								// Displays when on mobile device
								echo "<button href='#Bar$f_id2' class='btn btn-default btn-sm visible-xs' data-toggle='collapse' style='position: absolute; top: 3px; right: 3px'>";
									echo "<span class='glyphicon glyphicon-plus' aria-hidden='true'></span>";
								echo "</button>";

								echo "<div id='Bar$f_id2' class='collapse hidden-sm hidden-md hidden-lg'>";
								echo "<div style='text-align: center'>";
									// Display total number of topics for this category
									total_topics_display($f_id2);
									echo " ";
									// Display total number of topic replys for this category
									total_topic_replys_display($f_id2);
									// Display Edit, Delete, and Move Buttons
									forumCatEdit($f_id2,$f_title,$cat_order_id,$f_cat,$f_des,$f_id2);
								echo "</div>";
								echo "</div>";
								
								// Displays when not on mobile device
								echo "<div class='media-right hidden-xs' style='text-align: right'>";
									// Display total number of topics for this category
									total_topics_display($f_id2);
									echo "<br>";
									// Display total number of topic replys for this category
									total_topic_replys_display($f_id2);
									// Display Edit, Delete, and Move Buttons
									forumCatEdit($f_id2,$f_title,$cat_order_id,$f_cat,$f_des,$f_id2);
								echo "</div>";
							
						echo "</div>";
					echo "</ul>";
				}
				// Display Create New Category Form
				forumCatNew($f_title);
			echo "</ul>";
		echo "</div>";
	}
	forumCreateNewTopic();
	
// Show Current Forum Permissions
forumDisplayUserPerms();

// Run Footer of page func
style_footer_content();

?>