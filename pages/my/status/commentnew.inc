
<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isUserLoggedIn())
{

	if(isset($view_only_one)){}else{ $view_only_one = "FALSE"; }
	if($view_only_one == "TRUE"){

		$view_status_save = "${site_url_link}community/viewstatus/";

	}else{

		$view_status_save = "${site_url_link}community/mystatus/";

	}

	?>

	<?php 
	if(isset($id)){
		$com_id = $id; 
	}
	if(empty($com_uid)){
		$com_uid = $userIdme;
	}
	?>
	<?php // echo("ID = $com_id"); ?>
	<div class='panel panel-primary'><div class='panel-body' style='text-align: center'>
	<form enctype="multipart/form-data" action="<?php
echo "$view_status_save"; ?>" method="POST" onsubmit="submitmystat.disabled = true; return true;" >
	<?php
// create multi sessions
			if(isset($session_token_num)){
				$session_token_num = $session_token_num + 1;
			}else{
				$session_token_num = "1";
			}
			form_token();
	?>
	<input type="hidden" name="com_id" value="<?php if(isset($com_id)){ echo "$com_id"; } ?>" />
	<input type="hidden" name="com_uid" value="<?php if(isset($com_id)){ echo "$com_uid"; } ?>" />
	<input type="hidden" name="stat" value="save" />

	<?php echo "<input type='hidden' name='com_name' value='$nname'>"; ?>

	<script>
function textAreaAdjust(o) {
    o.style.height = "1px";
    o.style.height = (10+o.scrollHeight)+"px";
}
</script>
	
<textarea style='width:100%;height:14px;font-family:verdana;font-size:12px' name="com_content" cols="<?php
echo "$taw"; ?>" onkeyup="textAreaAdjust(this)" style="overflow:hidden" class='form-control'></textarea>
	
	<button type='submit' class='btn btn-success btn-sm' value='Update My Status' name='submitmystat' style='margin-top: 5px; margin-bottom: 0px' data-loading-text='Please wait...' >Update My Status</button>
	</form></div></div>

<?php
}
else {
	notlogedinmsg();
}
?>