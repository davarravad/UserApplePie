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



	echo "<div class='col-lg-4 col-md-12 col-sm-12 col-xs-12'>";
		//Display Forum Recent Posts
		require "./pages/forum/forum_recent.php";

		//Display site stats and such
		require "./external/total_site_stats.php";
	echo "</div>";
	

	//Site Adds Bottom
	require "./external/adds2.php";

	
	// Footer (sticky)
	echo "<footer class='navbar navbar-default'>";
		echo "<div class='container'>";
			echo "<div class='navbar-text'>";
				
				// Footer links / text
				echo "
					<a href='http://www.userapplepie.com' title='View UserApplePie Website' ALT='UserApplePie' target='_blank'>UserApplePie</a> 
					 | <a href='${site_url_link}'help/' title='Help & FAQ' ALT='Help & FAQ'>Help & FAQ</a>
					 | <a href='${site_url_link}'disclaimer/' title='Site Disclaimer' ALT='Disclaimer'>Disclaimer</a>
					 | <a href='${site_url_link}'privacypolicy/' title='Privacy Policy' alt='Privacy Policy'>Privacy Policy</a>
				";
				// Displays Admin Manage Site links if Admin is logged in
				if(is_admin())
				{
					echo " |  (<a href=\"${site_url_link}UAP_Admin_Panel/\">Manage Site</a>) ";
				}
				// Display Copywrite stuff
				echo "<Br> &copy; 2015 $websiteUrl All Rights Reserved.";
			echo "</div>";
		echo "</div>";
	echo "</footer>";
		
require "./external/report.php";

echo "</div>";
	echo "</div>";
// End of container

	//log user for site stats
	require "./external/sitelogs/showcurrent.php";

echo "
    <!-- Bootstrap core JavaScript ================================================== -->
    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src='https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js'></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src='/".$site_style_sel."/js/bootstrap.min.js'></script>
    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <script src='/".$site_style_sel."/js/ie10-viewport-bug-workaround.js'></script>
";

// End the body and html
echo "</body>";
echo "</html>";



?>