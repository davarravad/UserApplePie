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

$pages = getPageFiles(); //Retrieve list of pages in root usercake folder
$dbpages = fetchAllPages(); //Retrieve list of pages in pages table
$creations = array();
$deletions = array();

//Check if any pages exist which are not in DB
foreach ($pages as $page){
	if(!isset($dbpages[$page])){
		$creations[] = $page;	
	}
}

//Enter new pages in DB if found
if (count($creations) > 0) {
	createPages($creations)	;
}

if (count($dbpages) > 0){
	//Check if DB contains pages that don't exist
	foreach ($dbpages as $page){
		if(!isset($pages[$page['page']])){
			$deletions[] = $page['id'];	
		}
	}
}

//Delete pages from DB if not found
if (count($deletions) > 0) {
	deletePages($deletions);
}

//Update DB pages
$dbpages = fetchAllPages();

echo "
                <!-- Page Heading -->
                <div class='row'>
                    <div class='col-lg-12'>
                        <h1 class='page-header'>
                            $websiteName - Pages 
                        </h1>
                        <ol class='breadcrumb'>
                            <li>
                                <i class='glyphicon glyphicon-cog'></i> Admin Panel 
                            </li>
							<li class='active'>
								<i class='glyphicon glyphicon-file'></i> Pages
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

echo "
<div id='main'>
<table class='table table-hover'>
<tr><th>Id</th><th>Page</th><th>Access</th></tr>";

//Display list of pages
foreach ($dbpages as $page){
	echo "
	<tr>
	<td>
	".$page['id']."
	</td>
	<td>
	<a href ='".$site_url_link."UAP_Admin_Panel/admin_page/?id=".$page['id']."'>".$page['page']."</a>
	</td>
	<td>";
	
	//Show public/private setting of page
	if($page['private'] == 0){
		echo "Public";
	}
	else {
		echo "<font color='red'>Private</font>";	
	}
	
	echo "
	</td>
	</tr>";
}

echo "
</table>
</div>
<div id='bottom'></div>
</div>
</body>
</html>";

}

?>
