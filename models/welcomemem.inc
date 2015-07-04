<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Displays top links for members and links for new stuff
//Welcome Member Display

	require_once "models/communitylinks.inc";

	echo "<center><table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='epboxc'>";

		echo "<table width=100%><tr><td width=100><a href='${site_url_link}member/$userIdme/'>";
			require "pages/my/mainimage.inc";
		echo "</a></td><td align=left>";
			echo "Welcome back ";
			require "pages/my/username.inc";
			echo ".";
			echo "<br>";

			require "pages/my/newmess.inc";
			echo "New Messages! <br>";
			require "pages/friend/newrequest.inc";
			echo " Friend Requests! ";


			echo "</td><td align=right>"; 
			
				echo "<a href='${site_url_link}community/myfriends/'>Friends</a><br>";
				echo "<a href='${site_url_link}members/'>Members</a><br>";
				echo "<a href='${site_url_link}message/'>Messages</a><br>";
				echo "<a href='${site_url_link}editprofilemain/account/'>Account Settings</a>";

			echo "<br></td></tr>";
			echo "<tr><td colspan=3>";
				echo "<center>";

					echo "<a href='${site_url_link}member/$userIdme/'>View My Profile</a> - ";
					echo "<a href='${site_url_link}editprofilemain/'>Edit My Profile</a> - ";
					echo "<a href='${site_url_link}community/myimages/'>Edit/Upload My <b>Profile Photos</b></a>";

					//If user is admin dispaly manage site link
					if(is_admin()){
						echo "<hr>(You are ".$websiteName." Admin - <a href='${site_url_link}YummyAsPie/'>Manage Site</a>)";
						echo "<br>";
						require "models/admin/admin_new_stuff.inc";
					}
				echo "</center>";
			
		echo "</td></tr></table>";

	echo "</td></tr></table></center><br>";


?>