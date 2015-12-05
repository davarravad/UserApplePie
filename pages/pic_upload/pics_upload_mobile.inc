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

//Check to make sure user is logged in
if(isUserLoggedIn())
{

//Make sure user opened this form within the site
if(is_valid_referer())
{

//Vehicle Image Upload Script

	//Token validation function
	if(!is_valid_token()){ 

		//Token does not match
		err_message('Sorry, Tokens do not match!  Please go back and try again.');

	}else{		
		
		// get the variables from the URL request string
		if(isset($_POST['name'])){ $name = $_POST['name']; }else{ $name = ""; }
		if(isset($_POST['vehicle_id'])){ $vehicle_id = $_POST['vehicle_id']; }else{ $vehicle_id = ""; }
		if(isset($_POST['type'])){ $type = $_POST['type']; }else{ $type = ""; }
		if(isset($_POST['fsid'])){ $fsid = $_POST['fsid']; }else{ $fsid = ""; }
		if(isset($_POST['nname'])){ $nname = $_POST['nname']; }else{ $nname = ""; }
		if(isset($_POST['nname'])){ $club_id = $_REQUEST['nname']; }else{ $club_id = ""; }
	
		if($type == 'Custom'){ $type2 = "Customs"; }
		if($type == 'Both'){ $type2 = "Customs"; }
		if($type == 'Classic'){ $type2 = "Classics"; }
	
				$photo_types = array(    
				  'image/pjpeg' => 'jpg',   
				  'image/jpeg' => 'jpg',   
				  'image/gif' => 'gif',   
				  'image/bmp' => 'bmp',   
				  'image/x-png' => 'png'   
				);

				$photos_uploaded = $_FILES['userfile'];
	
				//This function separates the extension from the rest of the file name and returns it 
				function findexts ($filename) 
				{ 
					$filename = strtolower($filename) ;
					$exts = explode(".", $filename) ;
					$n = count($exts)-1;
					$exts = $exts[$n];
					return $exts;
				} 
					
					
					// Debug Show File Name
					if($debug_website == 'TRUE'){
						echo " File Name:  ";
						echo "{$_FILES['userfile']['name']}";
						echo "<br><br>";
						echo "File Type: ";
						echo findexts($_FILES['userfile']['name']);
						echo "<br><br>";
						echo "File Size: ";
						echo $photos_uploaded['size'];
						echo "<br><br>";
					}
					
					if($photos_uploaded['size'] > 0) {   
  
							//echo " File works <br>";
							// Great the file is an image, we will add this file   

							if(isset($_POST['title'])){ $title = $_POST['title']; }else{ $title = ""; }
							if(isset($_POST['content1'])){ $content1 = $_POST['content1']; }else{ $content1 = ""; }
						
							//Start Random img name gen.
							srand ((double) microtime( )*1000000);
							$random_number = rand( );
							//$ranimgname = "$random_number";
							$ranimgname = genRandomString();
							$ran_taz = "tazib_";
							$ranimgname = $ran_taz.$ranimgname.$random_number;
							//echo "$ranimgname2";
							//End Random img name gen.

							$uploaddirthumb = "${site_folder_dir}${site_dir}/${puf_pic_dir_thumb}";  //This is where image is saved
							$uploaddir = "${site_folder_dir}${site_dir}/${puf_pic_dir}";

							//This applies the function to our file  
							$ext = findexts($_FILES['userfile']['name']) ; 
							//echo " ( $ext ) ";

								//Check file ext
								if(!check_img_ext()){ 

									//File is not the correct extension for upload
									err_message('ERROR: File must be JPEG, JPG, GIF, TIF, or PNG image format to upload!');
									$total_count = "0";

								}else{		
										 
									$uploadfile = "$uploaddir$ranimgname.$ext";
									$uploadfilethumb = "$uploaddirthumb$ranimgname.$ext";
									$uploadfile2 = ".$ext";
									$uploadfilethumb2 = ".$ext";			
			
										if($uploadfile2){

											if (move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile)) {
												$filework = 'yes';
												echo "File is valid, and was successfully uploaded.\n";
												$total_count = "1";
											} else {
												echo "Possible file upload attack!  Image size may be too large.\n";
												$total_count = "0";
											}

											//start of thumb creation
											$im = new imagick( $puf_pic_dir.$ranimgname.$uploadfile2 );
											// resize by 200 width and keep the ratio
											$im->thumbnailImage( 100, 0);
											// write to disk
											$im->writeImage( $puf_pic_dir_thumb.$ranimgname.$uploadfilethumb2 );									
											//end of thumb

											//start of small
											$im = new imagick( $puf_pic_dir.$ranimgname.$uploadfile2 );
											// resize by 200 width and keep the ratio
											$im->thumbnailImage( 500, 0);
											// write to disk
											$im->writeImage( $puf_pic_dir_small.$ranimgname.$uploadfilethumb2 );
											//end of small

											//echo 'Here is some more debugging info:';
											//print_r($_FILES);
											$imgdir = $puf_pic_dir_small;
											$imgname = "$ranimgname$uploadfile2";
											$imgsize = "{$_FILES['userfile']['size']}";

											$myFile = "${site_folder_dir}/${site_dir}/${puf_pic_dir}${imgname}";
											$fh = fopen($myFile, 'w') or die("can't open file");
											fclose($fh) or die("can't get file 1");
											unlink($myFile) or die("can't delete file 1");		
											
											//Testing stuff
											//echo "<br>";
											//echo "Image Name: $imgname";
											//echo "<br>";
											//echo "Image Size: $imgsize";
											//echo "<br><br>";
											//echo "Image: <img src='/$imgdir/$imgname'>";
											
											if($filework == 'yes'){
							
												$content1 = htmlspecialchars($content1);
												$content1 = strip_tags($content1);	
												
												$content1 = addslashes($content1);
												$content1 = nl2br($content1);		
													
												//if profile pics check for main pic
												if($puf_pic_cat == "ep3"){
													require "pages/profile/setpicasmain.inc";
												}

												//if club pics check for main pic
												if($puf_pic_cat == "club_pics"){
													require "pages/club/pics/setpicasmain_club.inc";
												}
												
												//if club events pics check for main pic
												if($puf_pic_cat == "club_events_pics"){
													require "pages/club/events/setpicasmain.inc";
												}
												
												//if show events pics check for main pic
												if($puf_pic_cat == "show_events_pics"){
													require "pages/shows/setpicasmain.inc";
												}
													
												//Run query if vehicle pics
												if($puf_pic_cat == "art"){
													$query = "INSERT INTO `$puf_pic_cat` SET `usrida`='$userId',`vehicle_id`='$vehicle_id',`name`='$name',`type`='$type',`title`='$title',`content1`='$content1',`imgdir`='$imgdir',`imgname`='$imgname',`imgsize`='$imgsize' ";
												}
												
												//Run query if profile pics
												if($puf_pic_cat == "ep3"){
													$query = "INSERT INTO `ep3` SET `userId`='$userId', `nname`='$nname', `content1`='$content1',`imgdir`='$imgdir',`imgname`='$imgname',`imgsize`='$imgsize'";
												}
												
												//Run query if swapmeet pics
												if($puf_pic_cat == "fs3"){
													$query = "INSERT INTO `fs3` SET `userId`='$userId', `nname`='$nname', `fsid`='$fsid',`imgdir`='$imgdir',`imgname`='$imgname',`imgsize`='$imgsize'";
												}
												
												//Run query if club events pics
												if($puf_pic_cat == "club_events_pics"){
													$query = "INSERT INTO `club_events_pics` SET `userId`='$userId', `nname`='$club_id', `fsid`='$fsid',`imgdir`='$imgdir',`imgname`='$imgname',`imgsize`='$imgsize'";
												}

												//Run query if shows events pics
												if($puf_pic_cat == "show_events_pics"){
													$query = "INSERT INTO `show_events_pics` SET `userId`='$userId', `fsid`='$fsid',`imgdir`='$imgdir',`imgname`='$imgname',`imgsize`='$imgsize'";
												}
												
												//Run query if club pics
												if($puf_pic_cat == "club_pics"){
													$query = "INSERT INTO `club_pics` SET `userId`='$userId', `nname`='$club_id', `content1`='$content1', `imgdir`='$imgdir',`imgname`='$imgname',`imgsize`='$imgsize'";
												}
												
												$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );
								
												// print out the results
												if( $results )
												{

													//it works

												} else {
													//Code used to report mysql error
													$mysql_error_report = "FALSE";
													$sql_query = "$query";
													require "models/mysql_error_report.inc";
												}
												
											//End of file work check
											}else{
												echo "<br><Br>".$websiteName." Submit try again?";
											}
	
										}else{
											echo "<center>";
											echo "<font color=red>Error</font>: You did not select photos to upload.";
											echo "<br><br>";
											echo "Go Back and select photos to upload.";
											echo "<br><br>";	
											echo "</center>";
										}	
		
								}//end file ext check
								if(isset($total_count)){
									$total_count = 1;
								}else{
									$total_count = "0";
								}
						 
					}//End ph_up_size_counter
				
				
				
				echo "<br> $total_count Photos Uploaded <br>";
				if($total_count == "0"){
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Did Not Upload Any Photos! Please Try Again!";
					$_SESSION['success_msg'] = $success_msg;				
				
					//Disables auto refresh for debug stuff
					if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
						echo "<meta HTTP-EQUIV='REFRESH' content='0; url=?page=${return_page}'>";
					}				
				}else{
				
					//Sets where to send user when success
					//If vehicle photos use this
					if($puf_pic_cat == "art"){
						$page_after_success = "${site_url_link}community/myvehicles/";
					}
					//If profile photo use this
					if($puf_pic_cat == "ep3"){
						$page_after_success = "${site_url_link}member/$userId/";
					}
					//If swapmeet photo use this
					if($puf_pic_cat == "fs3"){
						$page_after_success = "${site_url_link}SwapMeet/viewlisting/?fsid=$fsid";
					}
					//If club events photo use this
					if($puf_pic_cat == "club_events_pics"){
						$page_after_success = "/Clubs/?pee=events/events_list&club_id=$club_id&club_events_edit=TRUE&fsp=viewEvent&fsid=$fsid";
					}
					//If club photo use this
					if($puf_pic_cat == "club_pics"){
						$page_after_success = "/Club/$club_id/";
					}
					//If show events photo use this
					if($puf_pic_cat == "show_events_pics"){
						$page_after_success = "/Shows/viewEvent/$fsid/";
					}

					
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Uploaded $total_count Photo!";
					$_SESSION['success_msg'] = $success_msg;				
				
					//Disables auto refresh for debug stuff
					if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
						echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${page_after_success}'>";
					}
				}
					
	}//end token check

}//End refer check
	
//End user logged in check				
} else {
	notlogedinmsg();
}

}// End enable photos

?>

