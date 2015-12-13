<center>

<?php 
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isset($_REQUEST['mto'])){ $mto = $_REQUEST['mto']; }else{ $mto = ""; }
if(isset($_REQUEST['msub'])){ $msub = $_REQUEST['msub']; }else{ $msub = ""; }
if(isset($_REQUEST['mbod'])){ $mbod = $_REQUEST['mbod']; }else{ $mbod = ""; }


$nname = $nname;
$userId = $userIdme;

//Testing... shows user name and id
//echo "(DN=$nname|uID=$userId)";
	
?>

<form name="newmessage" method="post" action="/message/?mes=msend" onsubmit="submit.disabled = true; return true;">

<?php
// create multi sessions
	if(isset($session_token_num)){
		$session_token_num = $session_token_num + 1;
	}else{
		$session_token_num = "1";
	}
	form_token();
?>

  <table width="" border="0" cellspacing="0" cellpadding="0">
    <tr><td colspan=2>
	<font size=1 color=green>Type Name of member, and select their name from the dropdown. The selected name will autofill.</font>
	</td></tr><tr>
      <td width="10%">TO:</td>
      <td width="90%"> 
     
<?php require "pages/message/member_lookup.inc"; ?> 
        
      </td>
    </tr>
    <tr> 
      <td>FROM:</td>
      <td><?php echo"$nname"; ?></td>
    </tr>
    <tr> 
      <td width="0">SUBJECT: &nbsp;</td>
      <td><input name="msubject" type="text" value="<?php
echo "$msub"; ?>" size="50"></td>
    </tr>
    <tr> 
      <td colspan="2">MESSAGE CONTENT:<br>
          <textarea name="mcontent" cols="80" rows="10"><?php
if($mbod){echo "This post relates to your post in Swap Meet
*$mbod*
-------------------------------------------------
";} ?></textarea>
        </td>
    </tr>
<tr><td colspan="2">


<input name="mfrom" type="hidden" value="<?php echo"$nname"; ?>" size="50">
<input name="submit" type="submit" value="Send Message" onClick="this.value = 'Please Wait....'">
</td></tr>
  </table>
</form>
</center>