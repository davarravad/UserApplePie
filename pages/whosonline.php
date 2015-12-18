<style type="text/css">
#pictures li {
	float:left;
	height:135px;
	list-style:none outside;
	width:110px;
	text-align:center;
}
#img_thumb {
	border:0;
	outline:none;
	max-height:75px;
}
</style>

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


echo "<center>";
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
	
	// Query to get online users
	$query = "SELECT * FROM ".$db_table_prefix."loggedusers ORDER BY `userId` ASC";
	// Get member info from database
	$result = $mysqli->query($query);
	$arr = $result->fetch_all(MYSQLI_BOTH);

	//Page Title
	echo "Who's Online?";
	echo "</td></tr><tr><td class='content78'>";

	echo '<ul id="pictures">';
	
	// Display data
	foreach($arr as $row)
	{
		$userId = $row['userId'];
		$ID02 = $userId;

				$userName = get_user_name_2($userId);

				echo "<li class='epboxa' width='110'>";
				
					echo "<a href='${site_url_link}member/$userId/'>$userName</a><br>";
						
					//Show user's membership status
					echo get_up_info_mem_status($ID02);

					echo "<a href='${site_url_link}member/$userId/'>";
					require "pages/profile/epimagemain.php";
					echo "</a>";
					
				echo "</li>";

	}

	echo "</ul>";
	
	echo "</td></tr></table>";
?>
