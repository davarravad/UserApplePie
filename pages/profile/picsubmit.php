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


//Title of pic upload form
	$puf_title = "Submit Profile Photos to ".$websiteName;
	//Catagory and database photos are being uploaded to
	$puf_pic_cat = "ep3";
	//Where to send user if no photos are uploaded
	$return_page = "editprofilemain/picsubmit/";
	//Sets the directory images are uploaded to
	$puf_pic_dir = "content/profile/images/";
	//Sets the directory for thumbnails
	$puf_pic_dir_thumb = "content/profile/thumb/";
	//Sets the directory for small images
	$puf_pic_dir_small = "content/profile/small/";

	if(isset($_POST['yes_upload'])){ $yes_upload = $_POST['yes_upload']; }else{ $yes_upload = ""; }
	
	if($yes_upload == "yes_upload"){
		if($usemobile == "TRUE"){
			require "pages/pic_upload/pics_upload_mobile.php";
		}else{
			require "pages/pic_upload/pics_upload.php";
		}
	}else{
		if($usemobile == "TRUE"){
			require "pages/pic_upload/pics_upload_form_mobile.php";
		}else{
			require "pages/pic_upload/pics_upload_form.php";
		}
	}

?>