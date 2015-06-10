<?php


if(isUserLoggedIn())
{

if(isset($_POST['delete'])){ $delete = $_POST['delete']; }else{ $delete = ""; }
if(isset($_POST['update'])){ $update = $_POST['update']; }else{ $update = ""; }
if(isset($_POST['comment'])){ $comment = $_POST['comment']; }else{ $comment = ""; }
if(isset($_POST['mainPic'])){ $mainPic = $_POST['mainPic']; }else{ $mainPic = ""; }

	if($comment == 'yes'){
		
		//Token validation function
		if(!is_valid_token()){ 

			//Token does not match
			err_message('Sorry, Tokens do not match!  Please go back and try again.');

		}else{  //token
		
		
				$title = $_POST['title'];
				$vehicle_id = $_POST['vehicle_id'];
				$content1 = $_POST['content1'];
				$id = $_POST['id'];

				$content1 = htmlspecialchars($content1);
				$content1 = strip_tags($content1);	
				
				$content1 = addslashes($content1);
				$content1 = nl2br($content1);	

				$title = htmlspecialchars($title);
				$title = strip_tags($title);	
				
				$title = addslashes($title);


				$query = "UPDATE `art` SET `title`='$title',`content1`='$content1', `vehicle_id`='$vehicle_id' WHERE `id`='$id' ";

				$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query )
					or die ("Couldn't ececute query.");

					if( $results ){
						//Sends success message to session
						//Shows user success when they are redirected
						$success_msg = "You Have Successfully Updated a Vehicle Photo!";
						$_SESSION['success_msg'] = $success_msg;
						//echo "Image comment updated!";
						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}editprofilemain/editvehicles/#image$id'>";
						}  //end debug
					}  //end results	
					else{
						//Code used to report mysql error
						$mysql_error_report = "TRUE";
						$sql_query = "$query";
						require "models/mysql_error_report.inc";
					}
		}  //end token
	}  //end comment

	if($mainPic == true){

	$mainPic = $_POST['mainPic'];
	$id = $_POST['id'];



			$query = "UPDATE `".$db_table_prefix."userprofile` SET `mainPic`='$mainPic' WHERE `userId`='$userId' ";

			$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query )
				or die ("Couldn't ececute query.");
			if( $results ){
				echo "Image set to Main Profile Pic!";
				//Disables auto refresh for debug stuff
				if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
					echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}editprofilemain/editvehicles/#image$id'>";
				}  //end debug
			}	//end results
			else{
				//Code used to report mysql error
				$mysql_error_report = "TRUE";
				$sql_query = "$query";
				require "models/mysql_error_report.inc";
			}

	}  //end mainpic

	if($update == 'yes'){

			echo "Change your image comment here!<br><br>";

			$id = $_POST['id'];



			$query = "SELECT * FROM art WHERE `id`='$id' ";

			$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
				or die ("Couldn't ececute query.");

			while ($row = mysqli_fetch_array($result))
			{
				extract($row);

				echo "
					<form method='post' action='${site_url_link}editprofilemain/editvehicles/?comment=yes&id=$id'>
				";
					// create multi sessions
					if(isset($session_token_num)){
						$session_token_num = $session_token_num + 1;
					}else{
						$session_token_num = "1";
					}
					form_token();
				echo "
					<input type='text' name='content1' value='$content1' size='40'>
					<input type='submit' name='submit' value='Update Image Comment'>
					</form>
				";
			}  //end while


	}  //end update


	if($delete == 'yes'){

		  $id = $_POST['id'];
		  if(isset($_POST['yes'])){ $yes = $_POST['yes']; }else{$yes = "";}

		if($yes == 'yes'){

			//Token validation function
			if(!is_valid_token()){ 

				//Token does not match
				err_message('Sorry, Tokens do not match!  Please go back and try again.');

			}else{  //token


					require "models/members/getuserinfo.inc";
					$userone = '$nname';



					  $id = $_POST['id'];

				 

					$query = "SELECT * FROM `art` WHERE `id`='$id' ";

					$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
					or die ("Couldn't ececute query.");
						
					while ($row = mysqli_fetch_array($result))
					{
						extract($row);
						//echo "<br>Owner = $userId<br>";
						//echo "Image = $imgname";
					}  //end while



					if($userId == $idofuser) {
				 
						$query = "DELETE FROM `art` WHERE `id`='$id' LIMIT 1";
						$results = mysqli_query($GLOBALS["___mysqli_ston"], $query);

						// print out the results
						if( $results )
						{
							// echo( "<br><br>Delete<br><br>" );
							// echo( "Successfully Deleted the entry." );

							$myFile2 = "${site_folder_dir}/${site_dir}/content/art/thumb/${imgname}";
							$fh2 = fopen($myFile2, 'w') or die("can't open file");
							fclose($fh2) or die("can't get file 2");
							unlink($myFile2) or die("can't delete file 2");   

							$myFile3 = "${site_folder_dir}/${site_dir}/content/art/small/${imgname}";
							$fh3 = fopen($myFile3, 'w') or die("can't open file");
							fclose($fh3) or die("can't get file 3");
							unlink($myFile3) or die("can't delete file 3");   

							//Sends success message to session
							//Shows user success when they are redirected
							$success_msg = "You Have Successfully Deleted a Vehicle Photo!";
							$_SESSION['success_msg'] = $success_msg;							
							
							//Disables auto refresh for debug stuff
							if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
								echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}editprofilemain/editvehicles/'>";
							}  //end debug

						}else{  //results
							//Code used to report mysql error
							$mysql_error_report = "TRUE";
							$sql_query = "$query";
							require "models/mysql_error_report.inc";
						} //end results
						
					}else{  //idofusers
						echo "<Br><br>The content you are trying to request is not yours!";
					} //end idofuser
			}  //end token
			//} //end yes check


	}else {  // delete yes check
		echo "<br>Are you sure you would like to delete that?<Br>";
		//echo "<a href='${site_url_link}?page=editprofilemain&pee=editvehicles&delete=yes&id=$id&yes=yes'>Yes?</a> / <a href='../'>No?</a>";
				echo "
					<form method=\"post\" action=\"${site_url_link}?page=editprofilemain&pee=editvehicles\">
				";
					//Form token. Place within from tag
					// create multi sessions
					if(isset($session_token_num)){
						$session_token_num = $session_token_num + 1;
					}else{
						$session_token_num = "1";
					}
					form_token();
				echo"
						<input type=\"hidden\" name=\"delete\" value=\"yes\">
						<input type=\"hidden\" name=\"id\" value=\"$id\">
						<input type=\"hidden\" name=\"yes\" value=\"yes\">
						<label title=\"Send\"><input type=\"submit\" value=\"YES\" /></label>
					</form>
				";
				
				$taz_backz = "
					<form method=\"post\" action=\"${site_url_link}editprofilemain/editvehicles/\">
						<label title=\"Send\"><input type=\"submit\" value=\"NO\" /></label>
					</form>
				";
				echo "<center>$taz_backz</center>";
			

	} //end yes check


}else {

		
		echo "<center><h3>Edit My Vehicle Profiles</h3></center>";
		
		echo "<center>( <a href='${site_url_link}SubmitVehiclePhoto/'>Upload Vehicle Photos</a> )</center>";

		require "pages/profile/editvehicleprofiles.inc";
	
echo "<a name='uvp' class='anchor'></a>";
echo "<hr><center><h3>Edit My Vehicle Photos</h3></center>";

$query = "SELECT * FROM art WHERE `usrida`='$userId' ";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query.");

	echo " <center>( <a href='${site_url_link}SubmitVehiclePhoto/'>Upload Vehicle Photos</a> ) <br><br>";


while ($row = mysqli_fetch_array($result))
{

	$bgcolor = "epboxa";
	

	extract($row);

	$content1 = stripslashes($content1);
	$content1 = stripslashes($content1);	

	$title = stripslashes($title);
	$title = stripslashes($title);
		  
	$content1 = str_replace("<br />", "", $content1); 

		echo "<a class='anchor' name='image$id'></a>";
		echo "<table><tr><td class=$bgcolor width='200' align=center><a href='${site_url_link}VehiclePhoto/$id/' target=''>";
		echo "<img class='rounded_10' border='0' width='100' src='/content/art/thumb/${imgname}'></a><br>";
		echo "</td><td class=$bgcolor align=center width=300>";

		//echo " <Br> (<a href='${site_url_link}?page=editprofilemain&pee=editvehicles&update=yes&id=$id'>Edit Description!</a>) <br>";
				echo "
					<form method=\"post\" action=\"${site_url_link}?page=editprofilemain&pee=editvehicles\">
					";
					//Form token. Place within from tag
					// create multi sessions
					if(isset($session_token_num)){
						$session_token_num = $session_token_num + 1;
					}else{
						$session_token_num = "1";
					}
					form_token();					
					echo "
						<strong>Title</strong><br><input name=\"title\" type=\"text\" size=\"30\" maxlength=\"50\" value=\"${title}\">
						<br><strong>Description</strong>
						<textarea name=\"content1\" cols=\"50\" rows=\"2\">$content1</textarea>
						<input type=\"hidden\" name=\"comment\" value=\"yes\">
						<input type=\"hidden\" name=\"id\" value=\"$id\">
				";
				require "pages/profile/vehicleidlist.inc";

				
		echo "</td><td class=$bgcolor align=center width=200>";
		require "pages/profile/epimagemaincheck.inc";
	


				echo "<a href='${site_url_link}VehiclePhoto/$id/'>View Vehicle</a><br><br>";
				echo "<font size=1px>Only updates one photo at a time.</font><Br>";
				echo "
					<label title=\"Send\"><input type=\"submit\" value=\"Update This Description\" /></label>
					</form>
				";

				$taz_b1 = "
					<form method=\"post\" action=\"${site_url_link}?page=editprofilemain&pee=editvehicles\">
						<input type=\"hidden\" name=\"delete\" value=\"yes\">
						<input type=\"hidden\" name=\"id\" value=\"$id\">
						<label title=\"Send\"><input type=\"submit\" value=\"Delete This Image\" /></label>
					</form>
				";
				echo "$taz_b1";
				echo "</td></tr></table><br>";

}

echo " ( <a href='${site_url_link}SubmitVehiclePhoto/'>Upload Vehicle Photos</a> ) <br><br>";
echo "</center>";

}



}else{
	notlogedinmsg();
}
?>