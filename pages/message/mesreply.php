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


$mfrom = $_POST['mto'];
$mto = $_POST['mfrom'];
$msubject = $_POST['msubject'];
$mcontent = $_POST['mcontent'];


	$msubject = stripslashes($msubject);
	$mcontent = stripslashes($mcontent);
	$msubject = stripslashes($msubject);
	$mcontent = stripslashes($mcontent);
		
	$mcontent = str_replace("<br />", "", $mcontent);

?>

<form name="newmessage" method="post" action="/message/?mes=msend" onsubmit="submit.disabled = true; return true;">

<?php
//Form token. Place within from tag
	// create multi sessions
	if(isset($session_token_num)){
		$session_token_num = $session_token_num + 1;
	}else{
		$session_token_num = "1";
	}
	form_token();
?>

<input name="mto" type="hidden" value="<?php echo"$mto"; ?>">

  <table width="" border="0" cellspacing="0" cellpadding="0" class='table'>
    <tr> 
      <td width="10%">TO:</td>
      <td width="90%"> 
     
<?php get_user_name($mto); ?>
        
      </td>
    </tr>
    <tr> 
      <td>FROM:</td>
      <td><?php get_user_name($mfrom); ?></td>
    </tr>
    <tr> 
      <td width="0">SUBJECT: &nbsp;</td>
      <td><input name="msubject" type="text" size="50" value="RE: <?php echo"$msubject"; ?>" class='form-control'></td>
    </tr>
    <tr> 
      <td colspan="2">MESSAGE CONTENT:<br>
          <textarea name="mcontent" cols="80" rows="10" class='form-control'>



###ORIGIONAL MESSAGE###
<?php echo "$mcontent"; ?>
</textarea>
        </td>
    </tr>
<tr><td colspan="2"><input name="submit" type="submit" value="Send Message" class="btn btn-default btn-sm" onClick="this.value = 'Please Wait....'">


</td></tr>
  </table>
</form>