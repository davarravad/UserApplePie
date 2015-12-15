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
                            $websiteName - Support Tickets 
                        </h1>
                        <ol class='breadcrumb'>
                            <li>
                                <i class='glyphicon glyphicon-cog'></i> Admin Panel 
                            </li>
							<li class='active'>
								<i class='glyphicon glyphicon-info-sign'></i> Support Tickets
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

$query = "SELECT * FROM ".$db_table_prefix."report";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. Reports 43666");

//HTML Stuff

while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);

	$report_msg = stripslashes($report_msg);
	
	echo "<div class='panel panel-body panel-default'>";
	echo "<b>Reporter</b>: $report_user ($report_userID) - <b>Type</b>: $report_type";
	echo "<br><a href='$report_pageURL' target='_blank'>$report_pageURL</a>";
	echo "<div class='well well-sm'>$report_msg</div>";
	echo "
		<form method=\"post\" action=\"${site_url_link}UAP_Admin_Panel/delete_report/ \">
		<input type=\"hidden\" name=\"report_id\" value=\"$report_id\">
		<input type=\"submit\" value=\"Delete!\" class='btn btn-danger btn-sm'/>
		</form>
	";
	echo "</div>";		

}

}


?>


