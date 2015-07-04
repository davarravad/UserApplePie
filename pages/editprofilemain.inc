
<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Title and Description
	//echo "<title>".$websiteName." Profile Editor</title>";

	require("models/communitylinks.inc");

//Me Editing Stuff Comment
//echo "<stong>NOTE FROM DAVAR</strong>: I am working on making the profile better.  Most of what you see beyond this point in the profile editor is not working for you.  It is set to only work for me.  Please try back at a later time when this message is gone! Thanks, DaVaR!";

?>

<?php

		//Displays logged in user pannel
		if(isUserLoggedIn()){
			require("models/welcomemem.inc");
		}

	echo "<center>";
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2' align=center>";
	echo "".$websiteName." Profile Editor"; 
	echo "</td></tr>";
	echo "<tr><td class='content78'>";

if(isUserLoggedIn())
{

	echo "<center>";


if(isset($_REQUEST['pee'])){ $pee = $_REQUEST['pee']; }else{ $pee = ""; }

		//START OF CONTENT
		
		if($pee){
			$pee1 = "pages/profile/";
			$pee2 = ".inc";
			$pee_file = "${pee1}${pee}${pee2}";
			
			if($pee){
				if(file_exists($pee_file)) {
					require "$pee_file";
				} else {
					echo "
						<center>
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
				echo "<br><center>Please select one of the above links corresponding to what you would like to do.</center><br>";
			}
		
		}
		else {
				require "pages/profile/ep1.inc";
		}
		
		
		//END OF CONTENT

	$up_get_show_display_name = get_up_info_mem_disp_name($userIdme);
	global $websiteUrl, $websiteName;
		
	//Display URL info for user's profile
	echo "<br>";
	echo "<table width='100%'><tr><td class=epboxa align=center><center><strong>Your Profile URL by ID</strong><br>";
	echo "<a href='".$websiteUrl."member/$userIdme/'>".$websiteUrl."member/$userIdme/</a><br>";
	echo "<strong>HTML Link Code</strong><br> &lt;a href=&quot;".$websiteUrl."member/$userIdme/&quot; ";
	echo "target=&quot;_blank&quot;&gt;My ".$websiteName." Profile&lt;/a&gt;";
	echo "<br><strong>Your Profile URL by Username</strong><br>";
	echo "<a href='".$websiteUrl."member/$up_get_show_display_name/'>".$websiteUrl."member/$up_get_show_display_name/</a><br>";
	echo "<strong>HTML Link Code</strong><br> &lt;a href=&quot;".$websiteUrl."member/$up_get_show_display_name/&quot; ";
	echo "target=&quot;_blank&quot;&gt;My ".$websiteName." Profile&lt;/a&gt;";
	echo "</center></td></tr></table></center><br>";
	
//END OF CONTENT
//START OF FOOTER
}
else {
	notlogedinmsg();
}

echo "</td></tr></table>";

?>