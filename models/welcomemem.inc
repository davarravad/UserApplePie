<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Displays top links for members and links for new stuff
//Welcome Member Display

	require_once "models/communitylinks.inc";

	echo "<div class='col-lg-12'>";
	echo "<div class='panel panel-default'>";
	echo "<div class='panel-body'>";

		echo "<div class='media'>";
			if($enable_photos == "TRUE"){
				echo "<div class='media-left'><a href='${site_url_link}member/$userIdme/'>";
					require "pages/my/mainimage.inc";
				echo "</a></div>";
			}
				echo "<div class='media-body'>";
					echo "Welcome back ";
					require "pages/my/username.inc";
					echo ".";
					echo "<br>";

					require "pages/my/newmess.inc";
					echo "New Messages! <br>";
					require "pages/friend/newrequest.inc";
					echo " Friend Requests! ";


				echo "</div>";
				echo "<div class='media-body' style='text-align: right'>";
					
					echo "<a href='${site_url_link}community/myfriends/' class='btn btn-info btn-xs' role='button' style='margin-bottom: 2px'>";
					echo "<span class='glyphicon glyphicon-heart' aria-hidden='true'></span>";
					echo " Friends ";
					echo "</a><br>";
					
					echo "<a href='${site_url_link}members/' class='btn btn-info btn-xs' role='button' style='margin-bottom: 2px'>";
					echo "<span class='glyphicon glyphicon-cloud' aria-hidden='true'></span>";
					echo " Members ";
					echo "</a><br>";
					
					echo "<a href='${site_url_link}message/' class='btn btn-info btn-xs' role='button' style='margin-bottom: 2px'>";
					echo "<span class='glyphicon glyphicon-inbox' aria-hidden='true'></span>";
					echo " Messages ";
					echo "</a><br>";
					
					echo "<a href='${site_url_link}editprofilemain/account/' class='btn btn-info btn-xs' role='button'>";
					echo "<span class='glyphicon glyphicon-briefcase' aria-hidden='true'></span>";
					echo " Account Settings ";
					echo "</a>";

				echo "</div>";
				echo "<div class=''>";
						echo "<center>";
						echo "<a href='${site_url_link}member/$userIdme/'>View My Profile</a> - ";
						echo "<a href='${site_url_link}editprofilemain/'>Edit My Profile</a> ";
						if($enable_photos == "TRUE"){
							echo " - <a href='${site_url_link}community/myimages/'>Edit/Upload My <b>Profile Photos</b></a>";
						}
						//If user is admin dispaly manage site link
						if(is_admin()){
							echo "<hr>(You are ".$websiteName." Admin - <a href='${site_url_link}UAP_Admin_Panel/'>Manage Site</a>)";
							echo "<br>";
							require "models/admin/admin_new_stuff.inc";
						}
						echo "</center>";
				echo "</div>";
			echo "</div>";
		echo "</div>";

	echo "</div>";
	echo "</div>";
	echo "</div>";


?>