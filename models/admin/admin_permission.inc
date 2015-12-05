<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){

require_once("models/config.inc");

$permissionId = $_GET['id'];

//Check if selected permission level exists
if(!permissionIdExists($permissionId)){
	header("Location: ".$site_url_link."YummyAsPie/admin_permissions/"); die();	
}

$permissionDetails = fetchPermissionDetails($permissionId); //Fetch information specific to permission level

//Check to see is site is demo site.  If so disable editing.
if($cur_server_name_dc != $demo_server_name_dc){
//Forms posted
if(!empty($_POST)){
	
	//Delete selected permission level
	if(!empty($_POST['delete'])){
		$deletions = $_POST['delete'];
		if ($deletion_count = deletePermission($deletions)){
		$successes[] = lang("PERMISSION_DELETIONS_SUCCESSFUL", array($deletion_count));
		}
		else {
			$errors[] = lang("SQL_ERROR");	
		}
	}
	else
	{
		//Update permission level name
		if($permissionDetails['name'] != $_POST['name']) {
			$permission = trim($_POST['name']);
			
			//Validate new name
			if (permissionNameExists($permission)){
				$errors[] = lang("ACCOUNT_PERMISSIONNAME_IN_USE", array($permission));
			}
			elseif (minMaxRange(1, 50, $permission)){
				$errors[] = lang("ACCOUNT_PERMISSION_CHAR_LIMIT", array(1, 50));	
			}
			else {
				if (updatePermissionName($permissionId, $permission)){
					$successes[] = lang("PERMISSION_NAME_UPDATE", array($permission));
				}
				else {
					$errors[] = lang("SQL_ERROR");
				}
			}
		}
		
		//Update permission level font color
		if($permissionDetails['color'] != $_POST['color']) {
			$permission = trim($_POST['color']);
			
			if (updatePermissionColor($permissionId, $permission)){
				$successes[] = lang("PERMISSION_COLOR_UPDATE", array($permission));
			}
			else {
				$errors[] = lang("SQL_ERROR");
			}
		}
		
		//Update permission level font weight
		if($permissionDetails['weight'] != $_POST['weight']) {
			$permission = trim($_POST['weight']);
			
			if (updatePermissionWeight($permissionId, $permission)){
				$successes[] = lang("PERMISSION_WEIGHT_UPDATE", array($permission));
			}
			else {
				$errors[] = lang("SQL_ERROR");
			}
		}
		
		//Remove access to pages
		if(!empty($_POST['removePermission'])){
			$remove = $_POST['removePermission'];
			if ($deletion_count = removePermission($permissionId, $remove)) {
				$successes[] = lang("PERMISSION_REMOVE_USERS", array($deletion_count));
			}
			else {
				$errors[] = lang("SQL_ERROR");
			}
		}
		
		//Add access to pages
		if(!empty($_POST['addPermission'])){
			$add = $_POST['addPermission'];
			if ($addition_count = addPermission($permissionId, $add)) {
				$successes[] = lang("PERMISSION_ADD_USERS", array($addition_count));
			}
			else {
				$errors[] = lang("SQL_ERROR");
			}
		}
		
		//Remove access to pages
		if(!empty($_POST['removePage'])){
			$remove = $_POST['removePage'];
			if ($deletion_count = removePage($remove, $permissionId)) {
				$successes[] = lang("PERMISSION_REMOVE_PAGES", array($deletion_count));
			}
			else {
				$errors[] = lang("SQL_ERROR");
			}
		}
		
		//Add access to pages
		if(!empty($_POST['addPage'])){
			$add = $_POST['addPage'];
			if ($addition_count = addPage($add, $permissionId)) {
				$successes[] = lang("PERMISSION_ADD_PAGES", array($addition_count));
			}
			else {
				$errors[] = lang("SQL_ERROR");
			}
		}
			$permissionDetails = fetchPermissionDetails($permissionId);
	}
}
}

$pagePermissions = fetchPermissionPages($permissionId); //Retrieve list of accessible pages
$permissionUsers = fetchPermissionUsers($permissionId); //Retrieve list of users with membership
$userData = fetchAllUsers(); //Fetch all users
$pageData = fetchAllPages(); //Fetch all pages

echo "
<div id='main'>";

echo resultBlock($errors,$successes);

echo "
<form name='adminPermission' action='".$site_url_link."YummyAsPie/admin_permission/?id=".$permissionId."' method='post'>
<table class='admin'>
<tr><td>
<h3>Permission Information</h3>
<div id='regbox'>
<p>
<label>ID:</label>
".$permissionDetails['id']."
</p>
<p>
<label>Name:</label>
<input type='text' name='name' value='".$permissionDetails['name']."' />
</p>
<p>
<label>Font Color:</label>
<input type='text' name='color' maxlength='20' value='".$permissionDetails['color']."' />
</p>
<p>
<label>Bold Font:</label>
<select name='weight'>
	<option value='TRUE'";
if($permissionDetails['weight'] == "TRUE"){ echo "SELECTED"; }
echo "/>Bold</option>
	<option value='FALSE'";
if($permissionDetails['weight'] == "FALSE"){ echo "SELECTED"; }
echo "/>Normal</option>
</select>
</p>
<label>Delete:</label>
<input type='checkbox' name='delete[".$permissionDetails['id']."]' id='delete[".$permissionDetails['id']."]' value='".$permissionDetails['id']."'>
</p>
</div></td><td>
<h3>Permission Membership</h3>
<div id='regbox'>
<p>
Remove Members:";

//List users with permission level
foreach ($userData as $v1) {
	if(isset($permissionUsers[$v1['id']])){
		echo "<br><input type='checkbox' name='removePermission[".$v1['id']."]' id='removePermission[".$v1['id']."]' value='".$v1['id']."'> ".$v1['display_name'];
	}
}

echo"
</p><p>Add Members:";

//List users without permission level
foreach ($userData as $v1) {
	if(!isset($permissionUsers[$v1['id']])){
		echo "<br><input type='checkbox' name='addPermission[".$v1['id']."]' id='addPermission[".$v1['id']."]' value='".$v1['id']."'> ".$v1['display_name'];
	}
}

echo"
</p>
</div>
</td>
<td>
<h3>Permission Access</h3>
<div id='regbox'>
<p>
Public Access:";

//List public pages
foreach ($pageData as $v1) {
	if($v1['private'] != 1){
		echo "<br>".$v1['page'];
	}
}

echo"
</p>
<p>
Remove Access:";

//List pages accessible to permission level
foreach ($pageData as $v1) {
	if(isset($pagePermissions[$v1['id']]) AND $v1['private'] == 1){
		echo "<br><input type='checkbox' name='removePage[".$v1['id']."]' id='removePage[".$v1['id']."]' value='".$v1['id']."'> ".$v1['page'];
	}
}

echo"
</p><p>Add Access:";

//List pages inaccessible to permission level
foreach ($pageData as $v1) {
	if(!isset($pagePermissions[$v1['id']]) AND $v1['private'] == 1){
		echo "<br><input type='checkbox' name='addPage[".$v1['id']."]' id='addPage[".$v1['id']."]' value='".$v1['id']."'> ".$v1['page'];
	}
}

echo"
</p>
</div>
</td>
</tr>
</table>
<p>
<label>&nbsp;</label>
<input type='submit' value='Update' class='submit' />
</p>
</form>
</div>
<div id='bottom'></div>
</div>
</body>
</html>";

}

?>
