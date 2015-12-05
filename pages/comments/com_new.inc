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

		$view_status_save = "$com_url_addy#comment_new";
		
	?>

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
	<input type="hidden" name="com_id" value="<?php if(isset($com_sel_id)){ echo "$com_sel_id"; } ?>" />
	<input type="hidden" name="com_uid" value="<?php if(isset($userIdme)){ echo "$userIdme"; } ?>" />
	<input type="hidden" name="comment" value="save" />

	<?php echo "<input type='hidden' name='com_name' value='$nname'>"; ?>
	<br>

	
	<script>
function textAreaAdjust(o) {
    o.style.height = "1px";
    o.style.height = (10+o.scrollHeight)+"px";
}
</script>
	
<textarea style='width:80%;height:14px;font-family:verdana;font-size:12px' name="com_content" cols="<?php
echo "$taw"; ?>" onkeyup="textAreaAdjust(this)" style="overflow:hidden"></textarea>

<br>
	<input type="submit" value="Submit Comment" name="submitcomment" class="sweet" onClick="this.value = 'Please Wait....'" />
	</form>

<?php
}//end login check
?>

</center>