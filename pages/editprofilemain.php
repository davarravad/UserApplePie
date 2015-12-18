
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



require("external/communitylinks.php");

//Me Editing Stuff Comment
//echo "<stong>NOTE FROM DAVAR</strong>: I am working on making the profile better.  Most of what you see beyond this point in the profile editor is not working for you.  It is set to only work for me.  Please try back at a later time when this message is gone! Thanks, DaVaR!";

//Displays logged in user pannel
if(isUserLoggedIn()){
	require("external/welcomemem.php");
}

// Page title
$stc_page_title = "$websiteName Profile Editor";
// Page Description
$stc_page_description = " My ".$websiteName." Profile Editor.";

// Run Header of page func
style_header_content($stc_page_title, $stc_page_description);

if(isUserLoggedIn())
{

	if(isset($_REQUEST['pee'])){ $pee = $_REQUEST['pee']; }else{ $pee = ""; }

	//START OF CONTENT
	
	if($pee){
		$pee1 = "pages/profile/";
		$pee2 = ".php";
		$pee_file = "${pee1}${pee}${pee2}";
		
		if($pee){
			if(file_exists($pee_file)) {
				require "$pee_file";
			} else {
				echo "
					The page <font color=red>$pee</font> does NOT exist!<br>
					<br>
					Go back or go <a href='../'>Home</a></center>
				";
				
				//Reporting page error
				$er_type = "Edit Profile Main Page Error";
				$er_location = "?pee=$pee";
				$er_msg = "?pee= error - page $taz does not exist";
				$er = "YESError";
			}
		} else {
			echo "<br>Please select one of the above links corresponding to what you would like to do.<br>";
		}
	
	}
	else {
			require "pages/profile/ep1.php";
	}
	
	
	//END OF CONTENT

	$up_get_show_display_name = get_up_info_mem_disp_name($userIdme);
	global $websiteUrl, $websiteName;
		
	//Display URL info for user's profile
	echo "<div class='panel panel-default'>";
	echo "<table width='100%'><tr><td class=epboxa align=center><center><strong>Your Profile URL by ID</strong><br>";
	echo "<a href='".$websiteUrl."member/$userIdme/'>".$websiteUrl."member/$userIdme/</a><br>";
	echo "<strong>HTML Link Code</strong><br> &lt;a href=&quot;".$websiteUrl."member/$userIdme/&quot; ";
	echo "target=&quot;_blank&quot;&gt;My ".$websiteName." Profile&lt;/a&gt;";
	echo "<br><strong>Your Profile URL by Username</strong><br>";
	echo "<a href='".$websiteUrl."member/$up_get_show_display_name/'>".$websiteUrl."member/$up_get_show_display_name/</a><br>";
	echo "<strong>HTML Link Code</strong><br> &lt;a href=&quot;".$websiteUrl."member/$up_get_show_display_name/&quot; ";
	echo "target=&quot;_blank&quot;&gt;My ".$websiteName." Profile&lt;/a&gt;";
	echo "</center></td></tr></table></center></div>";
	
	//END OF CONTENT
//START OF FOOTER
}
else {
	notlogedinmsg();
}

// Run Footer of page func
style_footer_content();

?>