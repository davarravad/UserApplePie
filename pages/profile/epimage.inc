<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

echo "<a class='anchor' name=imgs></a>";

	//Photo Popup Title
	$puf_popup_title = "Profile Photos";
	//Title of pic upload form
	$puf_title = "Submit Profile Photos to ".$websiteName;
	//Title of pic upload edit form
	$puf_title_edit = "Edit Profile Photos";
	//Catagory and database photos are being uploaded to
	$puf_pic_cat = "ep3";
	//Where to send user if no photos are uploaded
	$return_page = "editprofilemain&pee=picsubmit";
	//Sets the directory images are uploaded to
	$puf_pic_dir = "content/profile/images/";
	//Sets the directory for thumbnails
	$puf_pic_dir_thumb = "content/profile/thumb/";
	//Sets the directory for small images
	$puf_pic_dir_small = "content/profile/small/";
	//Sets the id of the page content for pics
	$puf_pic_con_id = "$ID02";
	//Sets the page that photos are being viewed on
	$puf_pic_view_page = "/member/$ID02";

require_once "pages/pic_upload/display_images.inc";


?>