<center><h3>Edit My Profile Images</h3></center>
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


if($enable_photos == "FALSE"){
	echo "<font color=red><strong>Sorry.. Photos are Disabled!</strong></font>";
}else{

if(isUserLoggedIn())
{

if(isset($_POST['delete'])){ $delete = $_POST['delete']; }else{ $delete = ""; }  
if(isset($_POST['update'])){ $update = $_POST['update']; }else{ $update = ""; }
if(isset($_POST['comment'])){ $comment = $_POST['comment']; }else{ $comment = ""; }
if(isset($_POST['setmainPic'])){ $setmainPic = $_POST['setmainPic']; }else{ $setmainPic = ""; }

if($comment == 'yes'){
	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{
		if(isset($_POST['content1'])){ $content1 = $_POST['content1']; }else{ $content1 = ""; }
		if(isset($_POST['id'])){ $id = $_POST['id']; }else{ $id = ""; }

			$content1 = htmlspecialchars($content1);
			$content1 = strip_tags($content1);	
			
			$content1 = addslashes($content1);
			$content1 = nl2br($content1);	


		$query = "UPDATE `$puf_pic_cat` SET `content1`='$content1' WHERE `id`='$id' ";

		$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query )
			or die ("Couldn't ececute query.");
		if( $results ){
		
			//Sends success message to session
			//Shows user success when they are redirected
			$success_msg = "You Have Successfully Updated Photo Comment!";
			$_SESSION['success_msg'] = $success_msg;
		
			//echo "Image comment updated!";
			//Disables auto refresh for debug stuff
			if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
				echo "<meta HTTP-EQUIV='REFRESH' content='0; url=?page=${return_page}&yes_edit=TRUE'>";
			}
		}else{
			//Code used to report mysql error
			$mysql_error_report = "TRUE";
			$sql_query = "$query";
			require "external/mysql_error_report.php";
		}
	}
}

if($setmainPic == 'true'){
	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{

			$mainPic = $_POST['mainPic'];
			$id = $_POST['id'];


					if($puf_pic_cat == "ep3"){
						$query = "UPDATE `userprofile` SET `mainPic`='$mainPic' WHERE `userId`='$userId' ";
					}
					if($puf_pic_cat == "club_pics"){
						$query = "UPDATE `club` SET `mainPic`='$mainPic' WHERE `club_id`='$club_id' ";
					}

					$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query )
						or die ("Couldn't ececute query.");
					if( $results ){
						//echo "Image set to Main Profile Pic!";
						
						//Sends success message to session
						//Shows user success when they are redirected
						$success_msg = "You Have Successfully Set Photo as Main!";
						$_SESSION['success_msg'] = $success_msg;
						
							//Disables auto refresh for debug stuff
							if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
								echo "<meta HTTP-EQUIV='REFRESH' content='0; url=?page=${return_page}&yes_edit=TRUE'>";
							}
					}	
	}
}

if($update == 'yes'){

		echo "Change your image comment here!<br><br>";

		$id = $_POST['id'];



		$query = "SELECT * FROM $puf_pic_cat WHERE `id`='$id' ";

		$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
			or die ("Couldn't ececute query.");

		while ($row = mysqli_fetch_array($result))
		{
			extract($row);

			echo "
				<form method='post' action='${site_url_link}?page=${return_page}&yes_edit=TRUE&comment=yes&id=$id'>
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
		}


}


if($delete == 'yes'){

      $id = $_POST['id'];
      if(isset($_POST['yes'])){ $yes = $_POST['yes']; }else{ $yes = ""; }

	if($yes == 'yes'){

	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{

					$userone = $nname;

					  $id = $_POST['id'];

					$query = "SELECT * FROM `$puf_pic_cat` WHERE `id`='$id' ";

					$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
					or die ("Couldn't ececute query.");
						
					while ($row = mysqli_fetch_array($result))
					{
						extract($row);
						//echo "<br>Owner = $userId<br>";
						//echo "Image = $imgname";
					}

					if($userId == $idofuser || $club_id == $nname) {
				 
						$query = "DELETE FROM `$puf_pic_cat` WHERE `id`='$id' LIMIT 1";

						$results = mysqli_query($GLOBALS["___mysqli_ston"], $query);

						// print out the results
						if( $results )
						{

							//Check to see if this image is users main pic
							//If it is, change back to noimg.gif
							//$imgname
							
							if($puf_pic_cat == "ep3"){
								$queryMP = "SELECT userprofile.mainPic FROM `userprofile` WHERE `userId`='$userId' ";
							}
							if($puf_pic_cat == "club_pics"){
								$queryMP = "SELECT club.mainPic FROM `club` WHERE `club_id`='$club_id' ";
							}

							$resultMP = mysqli_query($GLOBALS["___mysqli_ston"], $queryMP) or die ("Couldn't ececute query.");

								while ($rowMP = mysqli_fetch_array($resultMP))
								{
									extract($rowMP);

									$mainPicMP = $mainPic;
								}
								
								if(isset($mainPicMP)){
									$imgnameMP = $imgname;
									if($mainPicMP == $imgnameMP){
										//Update mainPic to noimg.gif
										if($puf_pic_cat == "ep3"){
											$queryMPU = "UPDATE `userprofile` SET `mainPic`='noimg.gif' WHERE `userId`='$userId' ";
										}
										if($puf_pic_cat == "club_pics"){
											$queryMPU = "UPDATE `club` SET `mainPic`='' WHERE `club_id`='$club_id' ";
										}
										$resultsMPU = mysqli_query($GLOBALS["___mysqli_ston"],  $queryMPU )
											or die ("Couldn't ececute query.");
										if( $resultsMPU ){
											//echo "mainPic should be noimg.gif";
										}
									}
								}
								
						  //echo( "<br><br>Delete<br><br>" );
						  //echo( "Successfully Deleted the entry." );


					$myFile2 = "${site_folder_dir}/${site_dir}/${puf_pic_dir_thumb}${imgname}";
					$fh2 = fopen($myFile2, 'w') or die("can't open file");
					fclose($fh2) or die("can't get file 2");
					unlink($myFile2) or die("can't delete file 2");   

					$myFile3 = "${site_folder_dir}/${site_dir}/${puf_pic_dir_small}${imgname}";
					$fh3 = fopen($myFile3, 'w') or die("can't open file");
					fclose($fh3) or die("can't get file 3");
					unlink($myFile3) or die("can't delete file 3");   

								//Sends success message to session
								//Shows user success when they are redirected
								$success_msg = "You Have Successfully Deleted A Photo!";
								$_SESSION['success_msg'] = $success_msg;

						//Disables auto refresh for debug stuff
						if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
							echo "<meta HTTP-EQUIV='REFRESH' content='0; url=?page=${return_page}&yes_edit=TRUE'>";
						}

				   }
				 
				   else
				   {
						//Code used to report mysql error
						$mysql_error_report = "TRUE";
						$sql_query = "$query";
						require "external/mysql_error_report.php";
				   }
					
				  

					}
					else {
						echo "<Br><br>The content you are trying to request is not yours!";
					}
	}


	}
	else {
		echo "<br>Are you sure you would like to delete that?<Br>";
		//echo "<a href='${site_url_link}?page=${return_page}&yes_edit=TRUE&delete=yes&id=$id&yes=yes'>Yes?</a> / <a href='../'>No?</a>";
				echo "<center>
					<form method=\"post\" action=\"${site_url_link}?page=${return_page}&yes_edit=TRUE\">
				";
				// create multi sessions
				if(isset($session_token_num)){
					$session_token_num = $session_token_num + 1;
				}else{
					$session_token_num = "1";
				}
				form_token();
				echo "
						<input type=\"hidden\" name=\"delete\" value=\"yes\">
						<input type=\"hidden\" name=\"id\" value=\"$id\">
						<input type=\"hidden\" name=\"yes\" value=\"yes\">
						<input type='hidden' name='edit_photo_please' value='TRUE'>
						<label title=\"Send\"><input type=\"submit\" value=\"YES\" /></label>
					</form>
				";
				echo "</center>";
				$taz_backz = "
					<form method=\"post\" action=\"${site_url_link}?page=${return_page}&yes_edit=TRUE\">
						<label title=\"Send\"><input type=\"submit\" value=\"NO\" /></label>
					</form>
				";
				echo "<center>$taz_backz</center>";
		

	}


}
else {


$query = "SELECT * FROM $puf_pic_cat WHERE `id`='$id' LIMIT 1 ";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query);

while ($row = mysqli_fetch_array($result))
{

	$bgcolor = "epboxa";
	

	extract($row);

	$content1 = stripslashes($content1);
	$content1 = stripslashes($content1);	
		  
	$content1 = str_replace("<br />", "", $content1); 

		echo "<a class='anchor' name='image$id'></a>";
		echo "<table><tr><td class=$bgcolor width='200' align=center><a href='content/profile/small/${imgname}' target='_blank'>";
		echo "<img class='rounded_10' border='0' width='100' src='/${puf_pic_dir_thumb}${imgname}'></a><br>";
		echo "</td><td class=$bgcolor align=center width=300>";
		//echo "$content1";
		//echo " <Br> (<a href='${site_url_link}?page=${return_page}&yes_edit=TRUE&update=yes&id=$id'>Edit Description!</a>) <br>";
				echo "
					<form method=\"post\" action=\"${site_url_link}?page=${return_page}&yes_edit=TRUE\">
				";
				echo "<input type='hidden' name='edit_photo_please' value='TRUE'>";
				echo "<input type='hidden' name='id' value='$id'>";
				// create multi sessions
				if(isset($session_token_num)){
					$session_token_num = $session_token_num + 1;
				}else{
					$session_token_num = "1";
				}
				form_token();
				if(!empty($title)){
					
				}
				if($puf_pic_cat == "club_pics"){
					echo "
							<textarea name=\"content1\" cols=\"50\" rows=\"5\">$content1</textarea>
							<input type=\"hidden\" name=\"comment\" value=\"yes\">				
					";
				}
				echo "<label title=\"Send\"><input type=\"submit\" value=\"Update Photo Info\" /></label></form>";
		echo "</td><td class=$bgcolor align=center width=200>";
		
		if($puf_pic_cat == "ep3"){
			require "pages/profile/epimagemaincheck.php";
		}
		if($puf_pic_cat == "club_pics"){
			require "pages/club/pics/epimagemaincheck.php";
		}
		if(!isset($mymainPic)){ $mymainPic = ""; }
		//echo "$mymainPic - $imgname";

			if($mymainPic == $imgname){
				echo "(<strong>Main Profile Pic!</strong>)<br><br>";
			}
			else{
				echo "
					<form method=\"post\" action=\"${site_url_link}?page=${return_page}&yes_edit=TRUE\">
				";
				// create multi sessions
				if(isset($session_token_num)){
					$session_token_num = $session_token_num + 1;
				}else{
					$session_token_num = "1";
				}
				form_token();
				echo "<input type='hidden' name='edit_photo_please' value='TRUE'>";
				echo "<input type='hidden' name='id' value='$id'>";
				echo "
						<input type=\"hidden\" name=\"mainPic\" value=\"$imgname\">
						<input type=\"hidden\" name=\"setmainPic\" value=\"true\">
						<input type=\"hidden\" name=\"UserId\" value=\"$userId\">
						<label title=\"Send\"><input type=\"submit\" value=\"Set as Main Profile Pic\" /></label>
					</form>
				";

			}
				$taz_b1 = "
					<form method=\"post\" action=\"${site_url_link}?page=${return_page}&yes_edit=TRUE\">
						<input type='hidden' name='edit_photo_please' value='TRUE'>
						<input type='hidden' name='id' value='$id'>
						<input type=\"hidden\" name=\"delete\" value=\"yes\">
						<input type=\"hidden\" name=\"id\" value=\"$id\">
						<label title=\"Send\"><input type=\"submit\" value=\"Delete Image\" /></label>
					</form>
				";
				echo "$taz_b1";
				echo "</td></tr></table><br><br>";

}

echo "</center>";

}

}
else {
	notlogedinmsg();
}

}// End enable photos
?>