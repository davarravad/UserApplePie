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
				
				for($counter=0;$counter<count($_FILES['userfile']['name']);$counter++){
					if(!isset($total_count)){ $total_count = "0"; }
					
					echo "{$_FILES['userfile']['name'][$counter]}";
					
					if($photos_uploaded['size'][$counter] > 0) {   
						if(!array_key_exists($photos_uploaded['type'][$counter], $photo_types)) {   
							$result_final .= 'File ' . ($counter + 1) .   
							' is not a photo<br />';   
						} else {   
							//echo " File works <br>";
							// Great the file is an image, we will add this file   

							if(isset($_POST['title'][$counter])){ $title = $_POST['title'][$counter]; }else{ $title = ""; }
							if(isset($_POST['content1'][$counter])){ $content1 = $_POST['content1'][$counter]; }else{ $content1 = ""; }
						
							//Start Random img name gen.
							srand ((double) microtime( )*1000000);
							$random_number = rand( );
							//$ranimgname = "$random_number";
							$ranimgname = genRandomString();
							global $websiteName;
							$new_img_name_start = trim($websiteName); // Removes spaces
							$new_img_name_start = preg_replace('/[^A-Za-z0-9\-]/', '', $new_img_name_start);  // Cleans out any chars
							$ran_taz = "${new_img_name_start}_${userIdme}_";
							$ranimgname = $ran_taz.$ranimgname.$random_number;
							//echo "$ranimgname2";
							//End Random img name gen.

							$uploaddirthumb = "${site_folder_dir}${site_dir}/${puf_pic_dir_thumb}";  //This is where image is saved
							$uploaddir = "${site_folder_dir}${site_dir}/${puf_pic_dir}";

							//This applies the function to our file  
							$ext = findexts($_FILES['userfile']['name'][$counter]) ; 
							//echo " ( $ext ) ";

								//Check file ext
								if(!check_img_ext()){ 

									//File is not the correct extension for upload
									err_message('ERROR: File must be JPEG, JPG, GIF, TIF, or PNG image format to upload!');

								}else{		
										 
									$uploadfile = "$uploaddir$ranimgname.$ext";
									$uploadfilethumb = "$uploaddirthumb$ranimgname.$ext";
									$uploadfile2 = ".$ext";
									$uploadfilethumb2 = ".$ext";			
			
										if($uploadfile2){

											if (move_uploaded_file($_FILES['userfile']['tmp_name'][$counter], $uploadfile)) {
												$filework = 'yes';
												echo "File is valid, and was successfully uploaded.\n";
											} else {
												echo "Possible file upload attack!  Image size may be too large.\n";
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
											
											// Open the watermark
											$watermark = new Imagick();
											$watermark->readImage("${site_folder_dir}${site_dir}/images/ctc_watermark.png");
											
											// Overlay the watermark on the original image
											$im->compositeImage($watermark, imagick::COMPOSITE_OVER, 2, 2); // specify the x, y co-ordinates of watermark image.
											
											// write to disk
											$im->writeImage( $puf_pic_dir_small.$ranimgname.$uploadfilethumb2 );
											//end of small

											//echo 'Here is some more debugging info:';
											//print_r($_FILES);
											$imgdir = $puf_pic_dir_small;
											$imgname = "$ranimgname$uploadfile2";
											$imgsize = "{$_FILES['userfile']['size'][$counter]}";

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
												
												//Run query if profile pics
												if($puf_pic_cat == "ep3"){
													//$query = "INSERT INTO `".$db_table_prefix."ep3` SET `userId`='$userId', `nname`='$nname', `content1`='$content1',`imgdir`='$imgdir',`imgname`='$imgname',`imgsize`='$imgsize'";
													$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."ep3(userId, nname, content1, imgdir, imgname, imgsize) VALUES (?, ?, ?, ?, ?, ?)");
													$stmt->bind_param("isssss", $userId, $nname, $content1, $imgdir, $imgname, $imgsize);
													$stmt->execute();
													//echo $stmt->error;
													$stmt->close();	
												}
								
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
												echo "<br><Br>Submit try again?";
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
									$total_count++;
								}else{
									$total_count = "0";
								}
						}//End array_key_exists   
					}//End ph_up_size_counter
				}//End while
				
				
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
					//If profile photo use this
					if($puf_pic_cat == "ep3"){
						$page_after_success = "/member/$userId/";
					}
					
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Uploaded $total_count Photos!";
					$_SESSION['success_msg'] = $success_msg;				
				
					//Disables auto refresh for debug stuff
					if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{		
		
						//Redirects the user
						global $site_url_link;
						$redir_link_url = "${site_url_link}${page_after_success}";
						
						// Redirect member to their post
						header("Location: $redir_link_url");
						exit;

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

