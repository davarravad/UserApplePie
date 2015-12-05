<center>
<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
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
	
<textarea style='width:80%;height:14px;font-family:verdana;font-size:12px' name="com_content" cols="<?php
echo "$taw"; ?>" onkeyup="textAreaAdjust(this)" style="overflow:hidden"></textarea>
<br>	
	<input class="sweet" type="submit" value="Update My Status" name="submitmystat" onClick="this.value = 'Please Wait....'" />
	</form>

<?php
}
else {
	notlogedinmsg();
}
?>

</center>