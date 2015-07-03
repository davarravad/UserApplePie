<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////


// This forum allows users to chat about issues with their vehicles

// Add Forum Functions
require("pages/forum/forum_funcs.inc");

// Run page content

// Get which page user is requesting
if(isset($_REQUEST['pee'])){ $load_page = $_REQUEST['pee']; }else{ $load_page = ""; }
if(isset($_REQUEST['fsid'])){ $load_cat = $_REQUEST['fsid']; }else{ $load_cat = ""; }
if(isset($_REQUEST['fsid2'])){ $load_id = $_REQUEST['fsid2']; }else{ $load_id = ""; }

// Sets forum title
$site_forum_title = "Forum";

// Set the dir where pages are loaded from
$load_page_dir = "forum";
// Set the page requested
$load_page_req = $load_page;
// Set the default page
$load_page_def = "main";
// Which database table do we use
$stc_page_sel = "forum";

// Add Forum Admin Functions
require("pages/forum/forum_admin_funcs.inc");

// Run the page function
display_pages_in_pages($load_page_dir, $load_page_req, $load_page_def, $load_cat, $load_id);

// Show Current Forum Permissions
forumDisplayUserPerms();

?>