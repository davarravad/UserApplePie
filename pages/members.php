<center>

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



	//$userIdme = $userId;

	//echo "$userIdme - $userId - $ID02";
	
		//Displays logged in user pannel
		if(isUserLoggedIn()){
			require("external/welcomemem.php");
		}
	

			// Page title
			$stc_page_title = "$websiteName Members";
			// Page Description
			$stc_page_description = "Complete list of all ".$websiteName." Site Members.";

			// Run Header of page func
			style_header_content($stc_page_title, $stc_page_description);
				

			if(isUserLoggedIn())
			{



				// get pnum no from user to move user defined pnum    
				if(isset($_GET['pnum'])){ $pnum = $_GET['pnum']; }else{ $pnum = ""; } 
				
				// no of elements per page 
				$limit = 10; 

				// Query to get total num of mem being displayed
				$queryPN = "
				SELECT u.*, up.* FROM ".$db_table_prefix."users u
				LEFT JOIN ".$db_table_prefix."userprofile up
				ON u.id = up.userId
				WHERE NOT u.active = 0 
				GROUP BY u.id
				";
				
				// simple query to get total no of entries
				if ($result = $mysqli->query("$queryPN")) {

					/* determine number of rows result set */
					$total = $result->num_rows;

					// printf("Topics:  %d \n", $total);

					/* close result set */
					$result->close();
				}

				// work out the pager values 
				$pager  = getPagerData($total, $limit, $pnum); 
				$offset = $pager->offset; 
				$limit  = $pager->limit; 
				$pnum   = $pager->pnum; 

				// Query to get member info
				$query = "
				SELECT u.*, up.* FROM ".$db_table_prefix."users u
				LEFT JOIN ".$db_table_prefix."userprofile up
				ON u.id = up.userId
				WHERE NOT u.active = 0 
				GROUP BY u.id
				ORDER BY u.id ASC LIMIT $offset, $limit";

				// Get member info from database
				$result = $mysqli->query($query);
				$arr = $result->fetch_all(MYSQLI_BOTH);


			echo "<center><table width=100% cellpadding='0' cellspacing='0' class='table table-striped'>";
				echo "<tr>";
			echo "<td class=epbox>&nbsp; <strong>Image</strong> </td><td class=epbox> <strong>Basic Info.</strong> </td><td class=epbox> <strong>Connect</strong></td></tr>";

				// Display data
				foreach($arr as $row)
				{
					$id = $row['id'];
					$mem_userId = $row['userId'];
					$mem_userFirstName = $row['userFirstName'];
					$mem_userCity = $row['userCity'];
					$mem_userWeb = $row['userWeb'];
				
					// Table Class
					$bgcolor = "epboxa";

				echo "<tr>";

				echo "<td class=$bgcolor width=$tblw3>";
				$ID02 = $mem_userId;
				
				echo "<a href='${site_url_link}member/$mem_userId/'>";
				require "pages/profile/userimage.php";
				echo "</a>";

				echo "</td><td class=$bgcolor>";
				echo "<strong>Nickname:</strong> ";
				get_user_name($id);

				echo "<br>";

				echo "<strong>Name:</strong> $mem_userFirstName ";

				echo " <br><strong>Location:</strong>&nbsp;";
				//echo " $userCity, $userState, $userCountry";

						$zip = "$mem_userCity";
						if($zip){
							include "external/zip.php";
							$csdisplay = "$city, $state_code";
							echo "$csdisplay";
							unset($csdisplay, $city, $state_code);
						}


				echo " </td><td class=$bgcolor>";
			 echo "<center><a href='${site_url_link}member/$mem_userId/'>View Profile</a>"; 
				echo "<br>";
			if($mem_userWeb){ echo "<a href='http://$mem_userWeb' target='_blank'>View Website</a><br>"; }
				echo " ";
				echo " <a href='${site_url_link}message/?mes=newmessage&mto=$mem_userId'>Send Message</a><br>";

				$userId1 = $userIdme;
				$userId2 = $mem_userId;
				//echo " $userId1 - $userId2 ";
				if($userId1 == $userId2){ echo "This is YOU!"; }else{
				require "pages/friend/friendcheck.php";
				}

				echo "</center></td></tr>";


			}



				echo "</td></tr></table>";

			echo "<center><table width=100% class='epbox'><tr><td align=left>";
			   // use $result here to output page content 

				// output paging system (could also do it before we output the page content) 
				if ($pnum == 1) // this is the first page - there is no previous page 
					; 
				else            // not the first page, link to the previous page 
					echo " < <a href=\"${site_url_link}members/?pnum=".($pnum - 1)."\">Previous</a> | "; 

				if ($pnum == $pager->numPages) // this is the last page - there is no next page 
					; 
				else            // not the last page, link to the next page 
					echo " <a href=\"${site_url_link}members/?pnum=".($pnum + 1)."\">Next</a> > "; 

				echo "</td><td align=center>";
			echo ".";
				for ($i = 1; $i <= $pager->numPages; $i++) { 
					//echo " - "; 
					if ($i == $pager->pnum) 
						echo "<font color=green><strong>$i</strong></font>."; 
					else 
						echo "<a href=\"${site_url_link}members/?pnum=$i\">$i</a>."; 
				} 
				echo "</td><td align=right>";
				$thetotal = ($offset + $limit);
				if($thetotal > $total){
					$thetotal2 = ($thetotal - $total);
					$thetotal3 = ($thetotal - $thetotal2);
					$thetotal = "$thetotal3";
				}
				echo "Showing $offset-$thetotal of $total";

				echo "</td></tr></table>";

			}
			else {
				notlogedinmsg();	
			}

// Run Footer of page func
style_footer_content();

?>
