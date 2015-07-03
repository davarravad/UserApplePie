<center>
<?php
if(isUserLoggedIn())
{

		$view_status_save = "$com_url_addy?offset=$offset#comment$statcom_id";

?>

<?php $statcom_uid = $userIdme; ?>
<?php // echo("ID = $statcom_id"); ?>
<form enctype="multipart/form-data" action="<?php
echo "$view_status_save"; ?>" method="POST" onsubmit="submit.disabled = true; return true;" >
<?php
// create multi sessions
			if(isset($session_token_num)){
				$session_token_num = $session_token_num + 1;
			}else{
				$session_token_num = "1";
			}
			form_token();
?>
<input type="hidden" name="statcom_id" value="<?php echo("$statcom_id") ?>" />
<input type="hidden" name="statcom" value="save" />


<?php require "models/members/getuserinfo.inc"; //echo "$nname"; ?>

<?php echo "<input type='hidden' name='statcom_id' value='$statcom_id'>"; ?>
<?php echo "<input type='hidden' name='statcom_name' value='$nname'>"; ?>
<?php echo "<input type='hidden' name='statcom_uid' value='$statcom_uid'>"; ?>



<textarea style='width:80%;height:14px;font-family:verdana;font-size:12px' id="txt1" name="statcom_content" cols="<?php
echo "$taw"; ?>" onkeyup="textAreaAdjust(this)" style="overflow:hidden"></textarea>

  <br>

<input type="submit" value="Submit Comment" name="submit" class="sweet" onClick="this.value = 'Please Wait....'" />
</form>

<?php
}//end login check
?>

</center>