<?php
# Rad User Manager Version 2.00
# Copyright (C) Rad Inks (Pvt) Ltd. 2003-2004
# http://www.radinks.net/

# Licence:
# The contents of this file are subject to the Mozilla Public
# License Version 1.1 (the "License"); you may not use this file
# except in compliance with the License. You may obtain a copy of
# the License at http://www.mozilla.org/MPL/
# 
# Software distributed under the License is distributed on an "AS
# IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
# implied. See the License for the specific language governing
# rights and limitations under the License.
# 
# The Initial Developer of the Original Code is Rad Inks (Pvt) Ltd.
# Portions created by Rad Inks are Copyright (C) 2003
# Rad Inks (Pvt) Ltd. All Rights Reserved.
# 


//include("../inc/header.php");

//create_header();

/**
 * display a generic error message
 */
function err_message2($str)
{
	echo "<table border='0' width='100%' align='center' cellspacing='0' cellpadding='0'>
			<tr><td class='hr2'>
				Car Truck Clubs Error Message
			</td></tr><tr><td class='content78'>
				<font color='#990000'><strong>$str</strong></font>
			</td></tr>
			</table><br>";
	require "members/signup.inc";
}


/**
 * Is the specified validation key ok?
 * returns userId on success. 0 on failure.
 */
function is_valid_key($key,$con)
{
	$query = "select userId from userProfile where userValidationKey = '$key' and userValidated = 0";
	$result = mysqli_query($con, $query);
	
	if($result && mysqli_num_rows($result) ==1)
	{
		$row = mysqli_fetch_row($result);
		return $row[0];

	}
	return 0;
}

/**
 * generally called when the user clicks on the link given in the
 * account verification email.
 */
function set_validated($userId, $con)
{
	$query = "update userProfile set userValidated=1 where userId = $userId";

	$result = mysqli_query($con, $query);
	return (((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_errno($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_errno()) ? $___mysqli_res : false)) == 0);
}

/**
 * if validate_email==1, accounts are created in the disabled state, call
 * this method to enable such accounts.
 */
function enable_account($userId,$con)
{
	$query = "update users set userStatus=1 where userId = $userId";
	$result = mysqli_query($con, $query);
	return (((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_errno($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_errno()) ? $___mysqli_res : false)) == 0);
}

if(!isset($_REQUEST['key']))
{
	header("Location: ${site_url_link}register/");
}
else
{

	$key = $_REQUEST['key'];
	require	("inc/config.inc");
	
	if(($userId = is_valid_key($key,$con)) != 0)
	{
		if(set_validated($userId,$con))
		{
			if(enable_account($userId,$con))
			{
				echo $msg_validated;
			}
			else
			{
				err_message("There was an error in activating your account");
			}
		}
		else
		{
			err_message("There was an error in validating your account");
		}
	}
	else
	{
		err_message("The validation key you have entered was not found in our database");
	}
}


//create_footer();
?>

