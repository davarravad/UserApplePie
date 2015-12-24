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


    // get pnum no from user to move user defined pnum    
    if(isset($_GET['pnum'])){ $pnum = $_GET['pnum']; }else{ $pnum = ""; } 
    
    // no of elements per page 
    $limit = 20; 
    
    // simple query to get total no of entries
    $queryPN = "select * from ".$db_table_prefix."inbox WHERE `mto`='$userIdme' "; 
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

//echo "($total)";
	
if($total > '0'){

				//GETTING INFORMATION FROM DATABASE

			$query = "SELECT * FROM ".$db_table_prefix."inbox WHERE `mto`='$userIdme' ORDER BY `mid` DESC LIMIT $offset, $limit";
			$result = mysqli_query($GLOBALS["___mysqli_ston"], $query);
				//or die ("Couldn't ececute query.");

				//TABLE SETUP FOR CONTENT

			echo "<table class='table'>";
				echo "<tr>";
			echo "<td valign=bottom> <strong>From</strong></td><td valign=bottom><strong>Subject</strong></td><td valign=bottom><strong>Status</strong> </td><td valign=bottom><strong>Date Read</strong></td><td valign=bottom><strong>Date Sent</strong> </td><td valign=bottom><strong>Other</strong></td></tr>";

				//PRINT OUT CONTENT FROM DATABASE

			while ($row = mysqli_fetch_array($result))
			{
					$bgcolor = "epboxa";
					

				extract($row);
				
				if($msubject){
					$msubject2 = $msubject;
				}
				else{
					$msubject2 = "No Subject";
				}
					$msubject2 = stripslashes($msubject2);
				echo "<tr>";
				echo "<td class='$bgcolor' valign=bottom>";
					// Display from user's display name
					get_user_name($mfrom);
				echo "</td>";
				echo "<td class='$bgcolor' valign=bottom>";
				echo "$msubject2";
				echo " </td>";
				echo "<td class='$bgcolor' valign=bottom>";
				if($mread == 'read'){ echo "Read"; }
				if($mread == 'unread'){ echo "<font color=green><strong>Unread</strong></font>"; }
				echo "</td>";
				echo "<td class='$bgcolor' valign=bottom>$mdateread</td>";
				echo "<td class='$bgcolor' valign=bottom>$timestamp</td>";
				echo "<td class='$bgcolor'>";
				//echo "<a href=='${site_url_link}?page=message&mes=delmesinbox&mid=$mid'>DELETE</a>";
							if(isset($mread)){}else{$mread = "";}
							if(isset($taz_read)){}else{$taz_read = "";}


							if ($mread == 'unread'){$taz_read = "read";}
							
							$taz_reada = "
								<form method=\"post\" action=\"${site_url_link}message/\">
									<input type=\"hidden\" name=\"mes\" value=\"viewmessage\">
									<input type=\"hidden\" name=\"mid\" value=\"$mid\">
									<input type=\"hidden\" name=\"box\" value=\"inbox\">
									<input type=\"hidden\" name=\"read\" value=\"$taz_read\">
									<input type=\"submit\" value=\"Read Message\" class='btn btn-default btn-sm'>
								</form>
							";
				
							$taz_delete = "
								<form method=\"post\" action=\"${site_url_link}message/\">
									<input type=\"hidden\" name=\"mes\" value=\"delmesinbox\">
									<input type=\"hidden\" name=\"mid\" value=\"$mid\">
									<input type=\"submit\" value=\"Delete\" class='btn btn-default btn-sm'>
								</form>
							";

								echo " $taz_reada ";

								echo "$taz_delete";

				

				echo "</td>";
				echo "</tr>";


			}

			echo "</table>";


			echo "</td></tr></table>";

				//CLOSE TABLE SETUP / END OF CONTENT

			//Start Display Page Numbers
				echo "<center><table width=100% class='epbox'><tr><td align=left>";

			   // use $result here to output page content 

				// output paging system (could also do it before we output the page content) 
				if ($pnum == 1) // this is the first page - there is no previous page 
					; 
				else            // not the first page, link to the previous page 
					echo " < <a href=\"${site_url_link}message/?pnum=".($pnum - 1)."\">Previous</a> | "; 

				if ($pnum == $pager->numPages) // this is the last page - there is no next page 
					; 
				else            // not the last page, link to the next page 
					echo " <a href=\"${site_url_link}message/?pnum=".($pnum + 1)."\">Next</a> > "; 

				echo "</td><td align=center>";
			echo ".";
				for ($i = 1; $i <= $pager->numPages; $i++) { 
					//echo " - "; 
					if ($i == $pager->pnum) 
						echo "<font color=green><strong>$i</strong></font>."; 
					else 
						echo "<a href='${site_url_link}message/?pnum=$i'>$i</a>."; 
				} 
				echo "</td><td align=right>";
				$thetotal = ($offset + $limit);
				if($thetotal > $total){
					$thetotal2 = ($thetotal - $total);
					$thetotal3 = ($thetotal - $thetotal2);
					$thetotal = "$thetotal3";
				}
				echo "Showing $offset-$thetotal of $total";


			echo "<center>";

			//End Display Page Number	

}else{ 
	echo "No Messages to display!";
}

?>