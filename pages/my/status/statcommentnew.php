<center>
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


if(isUserLoggedIn())
{

	if($view_only_one == "TRUE"){

		$view_status_save = "${site_url_link}community/viewstatus/?view_status=$view_status";

	}else{

		$view_status_save = "${site_url_link}community/mystatus/";

	}
?>

<?php $statcom_uid = $userId; ?>
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

<?php echo "<input type='hidden' name='statcom_id' value='$statcom_id'>"; ?>
<?php echo "<input type='hidden' name='statcom_name' value='$nname'>"; ?>
<?php echo "<input type='hidden' name='statcom_uid' value='$statcom_uid'>"; ?>


<textarea style='width:80%;height:14px;font-family:verdana;font-size:12px' id="txt1" name="statcom_content" cols="<?php
echo "$taw"; ?>" onkeyup="textAreaAdjust(this)" style="overflow:hidden" class='form-control'></textarea>
<br>
<button type='submit' class='btn btn-success btn-xs' value='Update My Status' name='submitmystat' style='' data-loading-text='Please wait...' >Submit Comment</button>
</form>

<?php
}
else {
	notlogedinmsg();
}
?>

</center>