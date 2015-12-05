<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Checks to see if user is loged in
if(isUserLoggedIn())
{

$com_content = stripslashes($com_content);
$com_content = str_replace("<br />", "", $com_content);

//echo "$com_uid - $com_id - $ed_com_database - $ed_com_id_form - $ed_com_url - $com_content";

?>

<form enctype="multipart/form-data" action="<?php
echo("$ed_com_url") ?>" method="POST" onsubmit="submit.disabled = true; return true;">

<?php
//Setup token in form
			// create multi sessions
			if(isset($session_token_num)){
				$session_token_num = $session_token_num + 1;
			}else{
				$session_token_num = "1";
			}
			form_token();

?>

<input type='hidden' name='ed_com' value='update' />
<input type='hidden' name='ed_com_database' value='<?php echo("$ed_com_database") ?>' />
<input type='hidden' name='ed_com_id_form' value='<?php echo("$ed_com_id_form") ?>' />
<input type='hidden' name='ed_com_url' value='<?php echo("$ed_com_url") ?>' />
<input type="hidden" name="com_type_edit" value="<?php echo("$com_type_edit") ?>" >

<textarea name="com_content" cols="<?php
echo "$taw2"; ?>" rows="3"><?php echo("$com_content") ?></textarea><br>    

<input type="submit" value="Update Comment" name="submit" class="sweet" onClick="this.value = 'Please Wait....'" />
</form>


<?php
}else{
	notlogedinmsg();
}
 ?>