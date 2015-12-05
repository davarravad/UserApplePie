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



?>

<?php $com_id = $userId; ?>
<?php // echo("ID = $com_id"); ?>
<form enctype="multipart/form-data" action="/?page=community&pee=mystatus&stat=save" method="POST" onsubmit="submitfriend.disabled = true; return true;">

<?php
// create multi sessions
			if(isset($session_token_num)){
				$session_token_num = $session_token_num + 1;
			}else{
				$session_token_num = "1";
			}
			form_token();
?>

<input type="hidden" name="com_id" value="<?php echo("$com_id") ?>" />

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

	<input type="hidden" name="stat" value="save" />
<input class="sweet" type="submit" value="Update My Status" name="submitfriend" onClick="this.value = 'Please Wait....'" />
</form>

<?php
}
else {
	notlogedinmsg();
}
?>

</center>