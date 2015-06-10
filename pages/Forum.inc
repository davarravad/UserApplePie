<?php

// Forum for cartruckclubs.com
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
// Run the page function
display_pages_in_pages($load_page_dir, $load_page_req, $load_page_def, $load_cat, $load_id);

?>