
<?php


if(isUserLoggedIn())
{

$nname = $nname;
$userId = $idofuser;


$query = "SELECT * FROM ".$db_table_prefix."ep2 WHERE `userId`='$userId' ";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 456112");
		
   if( $result && $contact = mysqli_fetch_object( $result ) )
   {
	$userId = $contact -> userId;
	$textfield = $contact -> textfield;
	$textarea = $contact -> textarea;
	$textfield2 = $contact -> textfield2;
	$textarea2 = $contact -> textarea2;
	$textfield3 = $contact -> textfield3;
	$textarea3 = $contact -> textarea3;
	$textfield4 = $contact -> textfield4;
	$textarea4 = $contact -> textarea4;
	$textfield5 = $contact -> textfield5;
	$textarea5 = $contact -> textarea5;
	$textfield6 = $contact -> textfield6;
	$textarea6 = $contact -> textarea6;
	$textfield7 = $contact -> textfield7;
	$textarea7 = $contact -> textarea7;
	$textfield8 = $contact -> textfield8;
	$textarea8 = $contact -> textarea8;

$new = 'no';

}
else {
$new = "yes";
//echo "$new";
}


	if(isset($textfield)){ 
		$textfield = stripslashes($textfield);
		$textfield = str_replace("<br />", "", $textfield);
	}else{ $textfield = ""; }
	if(isset($textarea)){ 
		$textarea = stripslashes($textarea);
		$textarea = str_replace("<br />", "", $textarea);
	}else{ $textarea = ""; }

	if(isset($textfield2)){ 
		$textfield2 = stripslashes($textfield2);
		$textfield2 = str_replace("<br />", "", $textfield2);
	}else{ $textfield2 = ""; }
	if(isset($textarea2)){ 
		$textarea2 = stripslashes($textarea2);
		$textarea2 = str_replace("<br />", "", $textarea2);
	}else{ $textarea2 = ""; }

	if(isset($textfield3)){ 
		$textfield3 = stripslashes($textfield3);
		$textfield3 = str_replace("<br />", "", $textfield3);
	}else{ $textfield3 = ""; }
	if(isset($textarea3)){ 
		$textarea3 = stripslashes($textarea3);
		$textarea3 = str_replace("<br />", "", $textarea3);
	}else{ $textarea3 = ""; }

	if(isset($textfield4)){ 
		$textfield4 = stripslashes($textfield4);
		$textfield4 = str_replace("<br />", "", $textfield4);
	}else{ $textfield4 = ""; }
	if(isset($textarea4)){ 
		$textarea4 = stripslashes($textarea4);
		$textarea4 = str_replace("<br />", "", $textarea4);
	}else{ $textarea4 = ""; }

	if(isset($textfield5)){ 
		$textfield5 = stripslashes($textfield5);
		$textfield5 = str_replace("<br />", "", $textfield5);
	}else{ $textfield5 = ""; }
	if(isset($textarea5)){ 
		$textarea5 = stripslashes($textarea5);
		$textarea5 = str_replace("<br />", "", $textarea5);
	}else{ $textarea5 = ""; }

	if(isset($textfield6)){ 
		$textfield6 = stripslashes($textfield6);
		$textfield6 = str_replace("<br />", "", $textfield6);
	}else{ $textfield6 = ""; }
	if(isset($textarea6)){ 
		$textarea6 = stripslashes($textarea6);
		$textarea6 = str_replace("<br />", "", $textarea6);
	}else{ $textarea6 = ""; }

	if(isset($textfield7)){ 
		$textfield7 = stripslashes($textfield7);
		$textfield7 = str_replace("<br />", "", $textfield7);
	}else{ $textfield7 = ""; }
	if(isset($textarea7)){ 
		$textarea7 = stripslashes($textarea7);
		$textarea7 = str_replace("<br />", "", $textarea7);
	}else{ $textarea7 = ""; }

	if(isset($textfield8)){ 
		$textfield8 = stripslashes($textfield8);
		$textfield8 = str_replace("<br />", "", $textfield8);
	}else{ $textfield8 = ""; }
	if(isset($textarea8)){ 
		$textarea8 = stripslashes($textarea8);
		$textarea8 = str_replace("<br />", "", $textarea8);
	}else{ $textarea8 = ""; }


?>



	
  <table width="100%" border="0" cellspacing="0" cellpadding="0">
    <tr> 
      <td colspan="2"><div align="center">Use this part of the profile editor 
          to make your profile say what you want!<br>
          Select a Title or Topic that sums up what your content is about. <br>
          For example: &quot;Title: Interest&quot; and &quot;Content: I enjoy 
          going fishing, hunting, swimming, etc...&quot;.<br>
          Make it your way and be creative!</div><bR><br></td>
    </tr>
    <tr> 
      <td><div align="center"> 
          <label>:Title / Topic: </label>
          <br>
          <input name="textfield" type="text" size="<?php
echo "$taw"; ?>" value="<?php if(isset($textfield)){ echo "$textfield"; } ?>">
          <br>
          <label>:Content of Title / Topic:</label>
          <br>
          <textarea name="textarea" cols="<?php
echo "$taw"; ?>" rows="10"><?php echo "$textarea"; ?></textarea>
        </div></td></tr><tr>
      <td><div align="center"> 
          <label>:Title / Topic: </label>
          <br>
          <input name="textfield2" type="text" size="<?php
echo "$taw"; ?>" value="<?php echo "$textfield2"; ?>">
          <br>
          <label>:Content of Title / Topic:</label>
          <br>
          <textarea name="textarea2" cols="<?php
echo "$taw"; ?>" rows="10"><?php echo "$textarea2"; ?></textarea>
        </div></td>
    </tr>
    <tr> 
      <td><div align="center"> 
          <label>:Title / Topic: </label>
          <br>
          <input name="textfield3" type="text" size="<?php
echo "$taw"; ?>" value="<?php echo "$textfield3"; ?>">
          <br>
          <label>:Content of Title / Topic:</label>
          <br>
          <textarea name="textarea3" cols="<?php
echo "$taw"; ?>" rows="10"><?php echo "$textarea3"; ?></textarea>
        </div></td></tr><tr>
      <td><div align="center"> 
          <label>:Title / Topic: </label>
          <br>
          <input name="textfield4" type="text" size="<?php
echo "$taw"; ?>" value="<?php echo "$textfield4"; ?>">
          <br>
          <label>:Content of Title / Topic:</label>
          <br>
          <textarea name="textarea4" cols="<?php
echo "$taw"; ?>" rows="10"><?php echo "$textarea4"; ?></textarea>
        </div></td>
    </tr>
    <tr> 
      <td><div align="center"> 
          <label>:Title / Topic: </label>
          <br>
          <input name="textfield5" type="text" size="<?php
echo "$taw"; ?>" value="<?php echo "$textfield5"; ?>">
          <br>
          <label>:Content of Title / Topic:</label>
          <br>
          <textarea name="textarea5" cols="<?php
echo "$taw"; ?>" rows="10"><?php echo "$textarea5"; ?></textarea>
        </div></td></tr><tr>
      <td><div align="center"> 
          <label>:Title / Topic: </label>
          <br>
          <input name="textfield6" type="text" size="<?php
echo "$taw"; ?>" value="<?php echo "$textfield6"; ?>">
          <br>
          <label>:Content of Title / Topic:</label>
          <br>
          <textarea name="textarea6" cols="<?php
echo "$taw"; ?>" rows="10"><?php echo "$textarea6"; ?></textarea>
        </div></td>
    </tr>
    <tr> 
      <td><div align="center"> 
          <label>:Title / Topic: </label>
          <br>
          <input name="textfield7" type="text" size="<?php
echo "$taw"; ?>" value="<?php echo "$textfield7"; ?>">
          <br>
          <label>:Content of Title / Topic:</label>
          <br>
          <textarea name="textarea7" cols="<?php
echo "$taw"; ?>" rows="10"><?php echo "$textarea7"; ?></textarea>
        </div></td></tr><tr>
      <td><div align="center"> 
          <label>:Title / Topic: </label>
          <br>
          <input name="textfield8" type="text" size="<?php
echo "$taw"; ?>" value="<?php echo "$textfield8"; ?>">
          <br>
          <label>:Content of Title / Topic:</label>
          <br>
          <textarea name="textarea8" cols="<?php
echo "$taw"; ?>" rows="10"><?php echo "$textarea8"; ?></textarea>
        </div></td>
    </tr>
    <tr> 
      <td colspan="2"><div align="center"> 
<br>
<?php 
if($new == 'yes'){ 
echo "<input type='hidden' name='new' value='yes'>";
 } 
else{
$new = 'no';
}
?>
			<input type="hidden" name="userId" value="<?php
echo "$userId"; ?>">
          <input type="submit" name="Submit" value="Save Your Information">
        </div></td>
    </tr>
  </table>
  
</form>


<?php
}
else {
	notlogedinmsg();	
}



?>



