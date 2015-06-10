<center>
<?php
if(isUserLoggedIn())
{


?>

<?php $statcom_uid = $userId; ?>
<?php // echo("ID = $statcom_id"); ?>
<form enctype="multipart/form-data" action="/?page=community&pee=friendstatus" method="POST" onsubmit="submit.disabled = true; return true;">
<?
			// create multi sessions
			if(isset($session_token_num)){
				$session_token_num = $session_token_num + 1;
			}else{
				$session_token_num = "1";
			}
			form_token();
?>
<input type="hidden" name="statcom_id" value="<?php echo("$statcom_id") ?>" />
<input type="hidden" name="offset" value="<?php echo("$offset") ?>" />
	<input type="hidden" name="statcom" value="save" />



<?php require "models/members/getuserinfo.inc"; //echo "$nname"; ?>

<?php echo "<input type='hidden' name='statcom_id' value='$statcom_id'>"; ?>
<?php echo "<input type='hidden' name='statcom_name' value='$nname'>"; ?>
<?php echo "<input type='hidden' name='statcom_uid' value='$statcom_uid'>"; ?>

<textarea style='width:80%;height:14px;font-family:verdana;font-size:12px' id="txt1" name="statcom_content" cols="<? echo "$taw"; ?>" onkeyup="textAreaAdjust(this)" style="overflow:hidden"></textarea>
<br>

<input class="sweet" type="submit" value="Submit Comment" name="submit" onClick="this.value = 'Please Wait....'" />
</form>

<?php
}
else {
	notlogedinmsg();
}
?>

</center>