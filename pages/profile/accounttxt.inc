<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////
?>

<table width=100% border=0 >
<tr><td colspan="2" align="center"><h3>Profile Manager for <?php
echo $profile->userName; ?></h3><br></td></tr>
<tr>
  <td valign="middle">

  	<!-- the pasword changer -->
	<form method="post" action="/?page=editprofilemain&pee=account" autoComplete="off">
	<table border="0" class="mTable" cellspacing="1" align="center" cellpadding="8" width="300">
	<tr class="mTr" ><td colspan=2 align="center">Password Changer</td></tr>
	<tr class="mTr"><td>User Name</td><td><?php
echo $profile->userName; ?></td></tr>
	<tr class="mTr"><td>Password</td><td><input type="password" name="password"></td></tr>
	<tr class="mTr"><td>Password Confirm</td><td><input type="password" name="password1"></td></tr>
	<tr class="mTr"><td colspan=2 align="center">
		<input type="hidden" name="action" value="chgpwd">
		<input type="hidden" name="userId" value="<?php
echo $_REQUEST['userId']; ?>">
		<input type="submit" name="submit" value="Change password"></td></tr>
	</table>
	</form>
	<!-- ends the password changer -->
	
	<br>
	<form method="post" action="/?page=editprofilemain&pee=account">
	<table border="0" class="mTable" cellspacing="1" align="center" cellpadding="8" width="300">
	<tr class="mTr" ><td colspan="2"  align="center">Advertisements</td></tr>
	<tr class="mTr" ><td colspan="2">Do you wish to see Advertisements within <?php
echo "$websiteName"; ?>?</td></tr>
	<tr class="mTr" >
		<td align="center">
			<input type="radio" name="news" value="yes" <?php
if($profile->newsLetter==1) echo 'checked'; ?>>Yes</td>
		<td align="center">
			<input type="radio" name="news" value="donot" <?php
if($profile->newsLetter==0) echo 'checked'; ?> >No</td></tr>
	<tr class="mTr" ><td colspan="3" align="center">
	<input type="hidden" name="action" value="chgnews">
	<input type="hidden" name="userId" value="<?php
echo $_REQUEST['userId']; ?>">
	<input type="submit" name="submit" value="update"></td></tr>
	</table>
	</form>
	<!-- ends newsletter subscription settings -->
	<?php
/* 
		 * user status change is available only to administrators.
		 */
		if(is_admin() != 0)
		{

			$status = get_user_status($userId);
	?>
			<br>
				<center>
						 <?php
if($status == 0) echo ""; ?> 
						<?php
if($status == 1) echo "User"; ?> 
						<?php
if($status == 2) echo "Administrator"; ?>
				</center>
	<?php
} 	?>
  </td>

   </tr>
</table>
<br>	
