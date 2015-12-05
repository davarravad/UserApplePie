<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

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
		
		echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class=hr2>";
		echo "<table width='100%'><tr><td>";
		
		//Display title or edit title field if mod and requested
		forumEditTitleCheck($f_title);
		
		// Display Forum Title Edit Funcs.
		if((userCheckForumAdmin() || userCheckForumMod()) && forumSHAF()){
			// Show admin feature if is admin
			// Display current order id
			echo "</td><td align='right'>";
			//echo "Order Id: $f_order_title ";
			echo "<table><tr><td width='140px' align='right'>";
				//Display Move Buttons
				forumMoveTitleOrder($f_order_title);
			echo "</td><td width='100px' align='right'>";
				//Display Edit/Delete Buttons
				forumEditTitle($f_title);
			echo "</td></tr></table>";
		}
		
		echo "</td></tr></table>";
		echo "</td></tr><tr><td class='content78'>";

			$f_title_2 = addslashes($f_title);
		
			// Get all Sub Categories for current category
			$query = "SELECT * FROM ".$db_table_prefix."forum_cat WHERE `forum_title`='$f_title_2' GROUP BY forum_cat ORDER BY forum_order_cat";
			$result = $mysqli->query($query);
			$arr2 = $result->fetch_all(MYSQLI_BOTH);
			foreach($arr2 as $row2)
			{
				$f_cat = $row2['forum_cat'];
				$f_des = $row2['forum_des'];
				$f_id2 = $row2['forum_id'];
				$cat_order_id = $row2['forum_order_cat'];
				
				$f_des = stripslashes($f_des);
				$f_cat = stripslashes($f_cat);
				
				echo "<table width='100%' border='0' cellspacing='0' cellpadding='0' class='epboxc'><tr><td width=''>";
					forumEditCatCheck($f_cat,$f_des,$f_id2);
				echo "</td><td width='75'>";
					// Display total number of topics for this category
					total_topics_display($f_id2);
					echo "<br>";
					// Display total number of topic replys for this category
					total_topic_replys_display($f_id2);
					// Display Edit, Delete, and Move Buttons
					forumCatEdit($f_id2,$f_title,$cat_order_id,$f_cat,$f_des,$f_id2);
				echo "</td></tr></table>";
			}
			// Display Create New Category Form
			forumCatNew($f_title);
			
		echo "</td></tr></table><br>";
			
	}
	forumCreateNewTopic();

// Run Footer of page func
style_footer_content();

?>