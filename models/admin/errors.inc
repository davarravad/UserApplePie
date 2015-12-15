<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// Check to make sure current user is logged in and a site admin	
if(isUserLoggedIn() && is_admin()){

// Page header
echo "
                <!-- Page Heading -->
                <div class='row'>
                    <div class='col-lg-12'>
                        <h1 class='page-header'>
                            $websiteName - Site Errors 
                        </h1>
                        <ol class='breadcrumb'>
                            <li>
                                <i class='glyphicon glyphicon-cog'></i> Admin Panel 
                            </li>
							<li class='active'>
								<i class='glyphicon glyphicon-alert'></i> Site Errors
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

$query = "SELECT * FROM ".$db_table_prefix."errors ORDER BY `er_id` DESC";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. Errors 324");

//HTML Stuff

while ($row = mysqli_fetch_array($result))
{
	extract($row);
	
	echo "<div class='panel panel-body panel-default'>";
		echo "($er_id)";
		echo "<table width='100%'><tr><td><strong>$er_type</strong></td>";
		echo "</tr><tr><td>$er_location</td>";
		echo "</tr><tr><td>$er_uri</td>";
		echo "</tr><tr><td>$er_refer</td>";
		echo "</tr><tr><td>$er_useragent</td>";
		echo "</tr><tr><td>$er_msg</td>";
		echo "</tr><tr><td>$er_cfile</td>";
		echo "</tr><tr><td>$er_ipaddy</td>";
		echo "</tr><tr><td>$er_server</td>";
		echo "</tr><tr><td>$er_date";		
		echo "</td></tr></table>";
		echo "
			<form method=\"post\" action=\"${site_url_link}UAP_Admin_Panel/delete_error/ \">
			<input type=\"hidden\" name=\"er_id\" value=\"$er_id\">
			<input type=\"submit\" value=\"Delete!\" class='btn btn-danger btn-sm'/>
			</form>
		";
	echo "</div>";
}



}

?>


