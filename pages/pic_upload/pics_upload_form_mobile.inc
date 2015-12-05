<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if($enable_photos == "FALSE"){
	echo "<font color=red><strong>Sorry.. Photos are Disabled!</strong></font>";
}else{

	echo "<center>";
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
	echo "$puf_title"; 
	echo "</td></tr>";
	echo "<tr><td class='content78'>";

		//Start of User Logged In Check
		if(isUserLoggedIn())
		{	

			if(isset($_POST['fsid'])){ $fsid = $_POST['fsid']; }else{ $fsid = ""; }

			
				echo "<font color=green size=0.5>You are on a mobile device, 1 upload at a time.  <br><Br>";

					
				//Let users know that this may take a while
				echo "<font color=green size=0.5>NOTE:  Depending on the size of the photos you are uploading, 
					this process may take a few minutes.  
					<br>Your Max File Size per photo is 5MB.
					<br>You will get a success message when completed.</font><br><br>";
			
					// initialization  
					$photo_upload_fields = '';  
					$counter = 1;  
				
					//Gets info if user made an error and was sent back
					if(isset($_POST['type'])){ $type = $_POST['type']; }else{ $type = ""; }
					if(isset($_POST['title'])){ $title = $_POST['title']; }else{ $title = ""; }
					if(isset($_POST['content1'])){ $content1 = $_POST['content1']; }else{ $content1 = ""; }
					if(isset($_POST['vehicle_id'])){ $vehicle_id = $_POST['vehicle_id']; }else{ $vehicle_id = ""; }
										
					$title = stripslashes($title);
					$title = stripslashes($title);
					$content1 = stripslashes($content1);
					$content1 = stripslashes($content1);						  
					$content1 = str_replace("<br />", "\n", $content1);   

					//Start the form
					echo "<form enctype=\"multipart/form-data\" action=\"${site_url_link}?page=${return_page}\" method=\"POST\" name=\"upload_form\"onsubmit=\"submit.disabled = true; return true;\">";
					
					//Lets site know we are uploading pics				
					echo "<input type='hidden' name='yes_upload' value='yes_upload'>";

					//Sets fsid if swapmeet
					if($puf_pic_cat == "fs3" || $puf_pic_cat == "show_events_pics"){
						echo "<input type='hidden' name='fsid' value='$fsid'>";
					}

					//Sets club info if club events pic
					if($puf_pic_cat == "club_events_pics" || $puf_pic_cat == "club_pics"){					
						echo "<input type='hidden' name='club_id' value='$club_id'>";
						echo "<input type='hidden' name='fsid' value='$fsid'>";
						echo "<input type='hidden' name='nname' value='$club_id'>";
						echo "<input type='hidden' name='name' value='$club_id'>";
					}
					
					
						//Form token. Place within from tag
						//Give this form more security, blocks refresh and possible attacks
						if(isset($session_token_num)){
							$session_token_num = $session_token_num + 1;
						}else{
							$session_token_num = "1";
						}
						form_token();

					//Gets the users name for img upload
					echo "<input type='hidden' name='name' value='$nname'>";
					echo "<label>Name/Author:</label>";
					echo "$nname";
					echo "<Br><br>";
					
					//Sets photo type for vehicle photos if file is a vehicle photo
					if($puf_pic_cat == "art"){
						//Display buttons for type of vehicle that user is uploading
						//echo "<label>Select the type of Vehicle you are about to submit:</label><br>";
						//echo "-<input name=\"type\" type=\"radio\" value=\"Custom\"  />Custom&nbsp;&nbsp;<br>";
						
						//echo "-<input name=\"type\" type=\"radio\" value=\"Classic\" />Classic&nbsp;&nbsp;<br>";
						
						//echo "-<input name=\"type\" type=\"radio\" value=\"Both\" CHECKED />Classic and Custom&nbsp;&nbsp;<br><br>";
					
						if(isset($_GET['int'])){ $vehicle_id = $_GET['int']; }

						//Displays list of vehicle profiles for current user if any
						require_once "pages/profile/vehicleidlist.inc";
						echo "<a href='${site_url_link}SubmitVehicleProfile/'>Click here to Create New Vehicle Profile</a>";
						echo "<br><br>";
					}

					echo "<hr>";
					//Build the Image Uploading field
						echo "<table><tr><td>";
						
						if($puf_pic_cat == "art"){
							echo "<label>Title:</label><br><input name='title' type='text' size='50' maxlength='50' value='' ><br>";
						}
						
						if($puf_pic_cat == "art" || $puf_pic_cat == "ep3" || $puf_pic_cat == "club_pics"){
							echo "<label>Description:</label><br><textarea name='content1' cols='50' rows='2'></textarea><br>";
						}
						
						echo "
						Upload this Photo: <input name='userfile' type='file' />
						</td></tr></table><hr>";
						
						
						
					
					
					echo "<input type='hidden' name='MAX_FILE_SIZE' value='25000000' />";  //sets max file size
					echo "<input type='submit' value='Upload Files' class='contSubmit' type='image' name='submit' onClick=\"this.value = 'Please Wait....'\" />";
					echo "</form>";

			

		//End of User Logged In Check
		}
		else {
		notlogedinmsg();
		}

	echo "</td></tr></table>";
	echo "</center><br><br>";
	
} // End enable photos

?>