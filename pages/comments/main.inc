<?php
echo "<div class='comt_cnt'>";

if(isset($_POST['ed_com'])){ $ed_com = $_POST['ed_com']; }
if(isset($_POST['ed_com_id_form'])){ $ed_com_id_form = intval($_POST['ed_com_id_form']); }
if(isset($com_id)){}else{ $com_id = ""; }
if(isset($com_uid)){}else{ $com_uid = ""; }
if(isset($_POST['com_type_edit'])){ $com_type_edit_b = $_POST['com_type_edit']; }else{ $com_type_edit_b = ""; }
//echo "($ed_com - $userIdme - $com_uid - $ed_com_id - $ed_com_id_form - $com_type_edit - $com_type_edit_b)<Br>";

if(empty($ed_com)){

	//Displays comment content

	$com_content = stripslashes($com_content);
	echo "$com_content";

	if(isUserLoggedIn())
	{
		if($userIdme == $com_uid){
			$ed_com_id_form = $id;
			$ed_but = '


			<form enctype="multipart/form-data" action="'.$ed_com_url.'" method="POST" class="sweetform" onsubmit="edit.disabled = true; return true;">
		
			<input type="hidden" name="ed_com" value="edit" >
			<input type="hidden" name="ed_com_database" value="'.$ed_com_database.'" >
			<input type="hidden" name="ed_com_id_form" value="'.$ed_com_id_form.'" >
			<input type="hidden" name="ed_com_url" value="'.$ed_com_url.'" >
			<input type="hidden" name="com_uid" value="'.$com_uid.'" >
			<input type="hidden" name="com_type_edit" value="'.$com_type_edit.'" >
			<input type="hidden" name="com_id" value="'.$com_id.'" >
			<input type="hidden" name="com_content" value="'.$com_content.'" >
			<input type="submit" value="Edit" name="edit" class="sweet" onClick="this.value = "Please Wait...."" >

			</form>



			<form enctype="multipart/form-data" action="'.$ed_com_url.'" method="POST" class="sweetform" onsubmit="edit.disabled = true; return true;">

			<input type="hidden" name="ed_com" value="delete" >
			<input type="hidden" name="ed_com_database" value="'.$ed_com_database.'" >
			<input type="hidden" name="ed_com_id_form" value="'.$ed_com_id_form.'" >
			<input type="hidden" name="ed_com_url" value="'.$ed_com_url.'" >
			<input type="hidden" name="com_uid" value="'.$com_uid.'" >
			<input type="hidden" name="com_id" value="'.$com_id.'" >
			<input type="hidden" name="com_type_edit" value="'.$com_type_edit.'" >
			<input type="hidden" name="com_content" value="'.$com_content.'" >

			<input type="submit" value="Delete" name="edit" class="sweet" onClick="this.value = "Please Wait...."">

			</form>


			';
		}
	}

}else{ 
	if(isUserLoggedIn())
	{

		$ed_com = $_POST['ed_com'];

		//Gathers comment info if update or delte
		if($ed_com == "update" || $ed_com == "delete" || $ed_com == "edit"){
			if(isset($_POST['com_uid'])){ $ed_com_uid = $_POST['com_uid']; }else{ $ed_com_uid = ""; }
			$ed_com_content = $_POST['com_content'];
			$ed_com_id_form = $_POST['ed_com_id_form'];
		}

		//Displays the edit form
		if($ed_com == "edit" && $userIdme == $com_uid && $ed_com_id == $ed_com_id_form && $com_type_edit == $com_type_edit_b){
			require "pages/comments/edit.inc";
		}else{
	 		//Displays comment content
			$com_content = stripslashes($com_content);
			echo "$com_content";
		}

		//Runs the update page
		if($ed_com == "update" && $userIdme == $com_uid && $ed_com_id == $ed_com_id_form && $com_type_edit == $com_type_edit_b){ 
			if(isset($_POST['com_uid'])){ $com_uid = intval($_POST['com_uid']); }else{ $com_uid = ""; }
			if(isset($_POST['com_id'])){ $com_id = intval($_POST['com_id']); }else{ $com_id = ""; }

			$com_content = $_POST['com_content'];
			require "pages/comments/update.inc"; 
		}

		//Runs the delete page
		if($ed_com == "delete" && $userIdme == $com_uid && $ed_com_id == $ed_com_id_form && $com_type_edit == $com_type_edit_b){ 
			$com_uid = intval($_POST['com_uid']);
			$com_id = intval($_POST['com_id']);
			$com_content = $_POST['com_content'];
			require "pages/comments/delete.inc"; 
		}
	}
}

echo "</div>";

//Used in comments to display buttons and comments



?>