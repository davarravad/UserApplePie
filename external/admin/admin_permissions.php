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


// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){

require_once("./external/config.php");

//Check to see is site is demo site.  If so disable editing.
if($cur_server_name_dc != $demo_server_name_dc){
//Forms posted
if(!empty($_POST))
{
	//Delete permission levels
	if(!empty($_POST['delete'])){
		$deletions = $_POST['delete'];
		if ($deletion_count = deletePermission($deletions)){
		$successes[] = lang("PERMISSION_DELETIONS_SUCCESSFUL", array($deletion_count));
		}
	}
	
	//Create new permission level
	if(!empty($_POST['newPermission'])) {
		$permission = trim($_POST['newPermission']);
		
		//Validate request
		if (permissionNameExists($permission)){
			$errors[] = lang("PERMISSION_NAME_IN_USE", array($permission));
		}
		elseif (minMaxRange(1, 50, $permission)){
			$errors[] = lang("PERMISSION_CHAR_LIMIT", array(1, 50));	
		}
		else{
			if (createPermission($permission)) {
			$successes[] = lang("PERMISSION_CREATION_SUCCESSFUL", array($permission));
		}
			else {
				$errors[] = lang("SQL_ERROR");
			}
		}
	}
}
}

echo "
                <!-- Page Heading -->
                <div class='row'>
                    <div class='col-lg-12'>
                        <h1 class='page-header'>
                            $websiteName - Groups 
                        </h1>
                        <ol class='breadcrumb'>
                            <li>
                                <i class='glyphicon glyphicon-cog'></i> Admin Panel 
                            </li>
							<li class='active'>
								<i class='glyphicon glyphicon-book'></i> Groups
							</li>
                        </ol>
                    </div>
                </div>
                <!-- /.row -->
";

//Check to see is site is demo site.  If so disable editing.
if($cur_server_name_dc == $demo_server_name_dc){
	err_message("Demo Site : Editing Disabled"); 
}

$permissionData = fetchAllPermissions(); //Retrieve list of all permission levels

echo "
<div id='main'>";

echo resultBlock($errors,$successes);

echo "
<form name='adminPermissions' action='".$site_url_link."UAP_Admin_Panel/admin_permissions/' method='post'>
<table class='table table-hover'>
<tr>
<th>Delete</th><th>Permission Name</th>
</tr>";

//List each permission level
foreach ($permissionData as $v1) {
	echo "
	<tr>
	<td><input type='checkbox' name='delete[".$v1['id']."]' id='delete[".$v1['id']."]' value='".$v1['id']."'></td>
	<td><a href='".$site_url_link."UAP_Admin_Panel/admin_permission/?id=".$v1['id']."'>".$v1['name']."</a></td>
	</tr>";
}

echo "
</table>
<p>
<label>Permission Name:</label>
<input class='form-control input-sm' type='text' name='newPermission' placeholder='New Group Name' />
</p>                                
<input type='submit' name='Submit' value='Submit' class='btn btn-success btn-sm'/>
</form>
</div>
<div id='bottom'></div>
</div>
</body>
</html>";

}

?>
