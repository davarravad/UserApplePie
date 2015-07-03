

<?php

require "models/members/getuserinfo.inc";
$nname = $nname;
$userId = $idofuser;


$query = "SELECT * FROM ".$db_table_prefix."userprofile WHERE `userId`='$userId' ";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 8432651");
		
   if( $result && $contact = mysqli_fetch_object( $result ) )
   {
      
		$userFirstName = $contact -> userFirstName;
		$userLastName = $contact -> userLastName;
		$userEmail = $contact -> userEmail;
		$userAddr1 = $contact -> userAddr1;
		$userAddr2 = $contact -> userAddr2;
		$userCity = $contact -> userCity;
		$userState = $contact -> userState;
		$userCountry = $contact -> userCountry;
		$userTel = $contact -> userTel;
		$userMobiTel = $contact -> userMobiTel;
		$userHomeTel = $contact -> userHomeTel;
		$userFacebook = $contact -> userFacebook;
		$userTwitter = $contact -> userTwitter;
		$userWeb = $contact -> userWeb;
		$userFax = $contact -> userFax;
		$userZip = $contact -> userZip;

}
else {echo "Error! EP3928383";}


?>

	<form method="post" action="/editprofilemain/ep1s/">

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
	
	<table border="0" class="mTable" cellspacing="1" align="center" cellpadding="8" width="$tblw"
 	 <tr  class="mTr"><td colspan=2 align="center">Update Profile</td></tr>
	 <tr class="mTr"><td>First Name:</td>

		<td><input type="text" name="userFirstName" value="<?php echo "$userFirstName"; ?>" size="40"></td></tr>

	 <tr class="mTr"><td>Last Name:</td>

		<td><input type="text" name="userLastName" value="<?php echo "$userLastName"; ?>" size="40"></td></tr>


	
	 <tr class="mTr"><td>Nicknames:</td>

	  <td class="mTr" >

	<input type="text" name="userAddr1" value="<?php echo "$userAddr1"; ?>" size="40">

	</td></tr>

	 <tr  class="mTr"><td>Sex:</td>

	  <td class="mTr">
  <label>
  <input type='radio' name='userAddr2' value='Male' <?php if($userAddr2 == "Male"){echo "checked";} ?>>
  Male</label>
<br>
  <label>
  <input type='radio' name='userAddr2' value='Female' <?php if($userAddr2 == "Female"){echo "checked";} ?>>
  Female</label>
</td></tr>

	 <tr class="mTr" ><td>City, State or Zip Code:</td>

	  <td><?php
require "pages/city_lookup.inc"; ?></td></tr>


	 <tr class="mTr"><td>AIM SN:</td><td>

	  <input type="text" name="userTel" value="<?php echo "$userTel"; ?>" size="40"></td></tr>
	  
	<tr class="mTr"><td>Yahoo SN:</td><td>
	  <input type="text" name="userMobiTel" value="<?php echo "$userMobiTel"; ?>" size="40"></td></tr>	
	    
	<tr class="mTr"><td>Facebook:</td><td>
	  https://facebook.com/<input type="text" name="userFacebook" value="<?php echo "$userFacebook"; ?>" size="17"></td></tr>	

	<tr class="mTr"><td>Twitter:</td><td>
	  https://twitter.com/<input type="text" name="userTwitter" value="<?php echo "$userTwitter"; ?>" size="19"></td></tr>		  
	 
	<tr class="mTr"><td>Web site:</td><td>
	  http://<input type="text" name="userWeb" value="<?php echo "$userWeb"; ?>" size="32"></td></tr>		  
	
	<tr><td colspan=2 class=epboxa>Privacy Settings</td></tr>
	<tr class="mTr"><td class=epboxb>Who Can View Your Profile?</td><td class=epboxb>
	<label>
		<input type='radio' name='userFax' value='public' <?php if($userFax == "public"){echo "checked";} ?>> Public
	</label>
	<label>
  		<input type='radio' name='userFax' value='members' <?php if($userFax == "members"){echo "checked";} ?>> Members
	</label><br>
	<label>
  		<input type='radio' name='userFax' value='friends' <?php if($userFax == "friends"){echo "checked";} ?>> Friends
	</label>
	<label>
  		<input type='radio' name='userFax' value='me' <?php if($userFax == "me"){echo "checked";} ?>> Only Me
	</label>





	</td></tr>

	 <tr class="mTr"><td colspan=2 align="center">
	 		<input type="hidden" name="action" value="update">
			<input type="hidden" name="userId" value="<?php
echo $_REQUEST['userId']; ?>">
			<input type="submit" name="submit" value="Update profile"></td></tr>

	</table>

	




<br>

<?php
require "pages/profile/ep2.inc"; ?>



