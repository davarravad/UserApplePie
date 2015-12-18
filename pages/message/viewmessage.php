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


if(isset($_POST['read'])){ $read = $_POST['read']; }else{ $read = ""; }
if(isset($_POST['mid'])){ $mid = $_POST['mid']; }else{ $mid = ""; }

if(isset($_POST['box'])){ $box = $_POST['box']; }else{ $box = ""; }

$query = "SELECT * FROM ".$db_table_prefix."$box WHERE `mid`='$mid' LIMIT 1 ";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query.");



while ($row = mysqli_fetch_array($result))
{
	extract($row);

	if($msubject){
		$msubject2 = $msubject;
	}
	else{
		$msubject2 = "No Subject";
	}

		$taz_sub = stripslashes($msubject2);
		$taz_content = stripslashes($mcontent);
		$taz_content = str_replace( '&lt;br /&gt;', '<br />', $taz_content );

echo "	
<br><Br>
<table width='500' border='0' cellspacing='2' cellpadding='2'>
    <tr> 
	<td width='20%' class='epboxa'>
		<strong>To:</strong>
	</td>
      	<td class='epboxa'>
         		<strong>$mto</strong>
     	</td>
    </tr>
    <tr> 
	<td class='epboxb'>
		<strong>From:</strong>
	</td>
      	<td class='epboxb'>
         		<strong>$mfrom</strong>
     	</td>
    </tr>
    <tr> 
	<td class='epboxa'>
		<strong>Subject:</strong>
	</td>
      	<td class='epboxa'>
         		<strong>$taz_sub</strong>
     	</td>
    </tr>

<tr>
      	<td colspan='2' class='content79'>
         		<strong>$taz_content</strong>
     	</td>
    </tr>

</table>

";

}

if($read){
$mdateread = date("YmdHis");

 mysqli_query($GLOBALS["___mysqli_ston"], "UPDATE `".$db_table_prefix."inbox` SET `mread` = 'read', `mdateread` = '$mdateread' WHERE `mid` = '$mid' LIMIT 1 "); 
 mysqli_query($GLOBALS["___mysqli_ston"], "UPDATE `".$db_table_prefix."outbox` SET `mread` = 'read', `mdateread` = '$mdateread' WHERE `mid` = '$mid' LIMIT 1 "); 

}

?>
<table><tr><td>
<form name="newmessage" method="post" action="/message/" onsubmit="submit.disabled = true; return true;">
<input name="mes" type="hidden" value="mesreply">
<input name="mto" type="hidden" value="<?php echo "$mto"; ?>">
<input name="mfrom" type="hidden" value="<?php echo "$mfrom"; ?>">
<input name="msubject" type="hidden" value="<?php echo "$msubject"; ?>">
<input name="mcontent" type="hidden" value="<?php echo "$mcontent"; ?>">

<label title="Reply"><input name="submit" type="submit" value="Reply" class="contSubmit" onClick="this.value = 'Please Wait....'"></label>
</form>
</td><td>
<?php
$taz_delete = "
					<form method=\"post\" action=\"${site_url_link}message/\">
						<input type=\"hidden\" name=\"mes\" value=\"delmes$box\">
						<input type=\"hidden\" name=\"mid\" value=\"$mid\">
						<label title=\"Delete Message\"><input type=\"submit\" value=\"Delete\" /></label>
					</form>
				";
				echo "$taz_delete";	

?>
</td></tr></table>
</center>