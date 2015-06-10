<?

//Left Navigation Bar Code Stuff
//Created by David Sargent (DaVaR)
//davarravad@gmail.com

?>



<?

	if(isset($_REQUEST['page'])){ $taz = $_REQUEST['page']; }else{ $taz = ""; }
		
		echo "<div class='nav-container'><nav>";
		echo "<table border='0' cellspacing='0' cellpadding='0' width='150'>";
		
		echo "<tr><td class='main_tbl_nav_links_title'><a href='${site_url_link}' title='Car Truck Clubs Home' alt='Car Truck Clubs Home'>Home</a></td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}Museums/' title='View Museum List' alt='Museum List'>Museums</a> </td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}RoadCourse/' title='View Road Course List' alt='Road Course List'>Road Courses</a> </td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}DirtTracks/' title='Dirt Track List' alt='Dirt Track List'>Dirt Tracks</a> </td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}PavedTracks/' title='Paved Track List' alt='Paved Track List'>Paved Tracks</a> </td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}DragStrips/' title='Drag Strip List' alt='Drag Strip List'>Drag Strips</a> </td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}MudTracks/' title='Mud Track Park List' alt='Mud Track Park List'>Mud Track Parks</a></td></tr>
		";
		
		echo "<tr><td class='main_tbl_nav_links_title2'><a href='${site_url_link}Vehicles/' title='View all Vehicle Profiles' alt='Vehicle Profiles'>Vehicles</a></td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}Customs/' title='View all Custom Vehicles' alt='Custom Vehicles'>Customs</a> </td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}Classics/' title='View all Classic Vehicles' alt='Classic Vehicles'>Classics</a> </td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}CustomsandClassics/' title='View all Custom and Classic Vehicles' alt='Custom and Classic Vehicles'>C<font size=0.5>ustoms and Classics</font></a> </td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}Vehicles/' title='View all Vehicle Profiles' alt='Vehicle Profiles'>Vehicle Profiles</a>";
				if(isUserLoggedIn())
				{
					echo "  </td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}community/myvehicles/' title='View Your Vehicle Profiles' alt='My Vehicle Profiles'>My Vehicles</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}SubmitVehiclePhoto/' title='Upload a Vehicle Photo' alt='Upload Vehicle Photo'>U<font size=0.5>pload Vehicle Photos</font></a> ";
				}
		echo "</td></tr>";

		echo "<tr><td class='main_tbl_nav_links_title2'><a href='${site_url_link}SwapMeet/' title='Swap Meet' alt='Swap Meet'>Swap Meet</a></td></tr>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}SwapMeet/' title='View Open Swap Meet Listings' alt='All Open Swap Meet Listings'>Open Listings</a>
			<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}SwapMeet/closed_listings/' title='View Closed Swap Meet Listings' alt='All Closed Swap Meet Listings'>Closed Listings</a>";
				if(isUserLoggedIn())
				{
					echo " </td></tr>
						<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}SwapMeet/mylistings/' title='View Your Swap Meet Listings' alt='My Swap Meet Listings'>My Listings</a> </td></tr>
						<tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}SwapMeet/fsnew/' title='Create a New Swap Meet Listing' alt='Create Swap Meet Listing'>Create New Listing</a>";
				}
		echo "</td></tr>";
		
		echo "<tr><td class='main_tbl_nav_links_title2'><a href='${site_url_link}Clubs/' title='Clubs' alt='Clubs'>Clubs</a>
			</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}Clubs/clubs/' title='View All Clubs' alt='All Clubs'>All Clubs</a>";
				if(isUserLoggedIn())
				{
					echo "</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}Clubs/myclubs/' title='View Clubs You are a Member of' alt='My Clubs'>My Clubs</a> 
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}Clubs/submitclub/' title='Create a New Club' alt='Create New Club'>Create Club</a> ";
				}
		echo "</td></tr>";
			
				if(isUserLoggedIn())
				{
					echo "<tr><td class='main_tbl_nav_links_title2'><a href='${site_url_link}community/' title='View Your Friends Status' alt='Community'>Community</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}members/' title='View All Site Members' alt='Members'>Members</a>
						</td></tr><tr><td class='main_tbl_nav_links_subB'>My Content
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}message/' title='View Your Site Mail' alt='My Messages'>My Messages</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}community/mystatus/' title='View Your Status Updates' alt='My Status'>My Status</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}community/myvehicles/' title='View All Your Vehicle Profiles and Photos' alt='My Vehicles'>My Vehicles</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}community/myimages/' title='View Your Profile Photos' alt='My Profile Images'>My Images</a>
						</td></tr><tr><td class='main_tbl_nav_links_subB'>Friends
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}community/myfriends/' title='View Your Friends and Friend Requests' alt='My Friends'>Friends</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}community/friendstatus/' title='View Your Friends Status Updates' alt='Friends Status'>Friends Status</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}community/friendvehicles/' title='View Your Friends Vehicle Profiles and Photos' alt='Friends Vehicles'>Friends Vehicles</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}community/friendimages/' title='View Your Friends Profile Photos' alt='Friends Images'>Friends Images</a>
						
						</td></tr><tr><td class='main_tbl_nav_links_title2'><a href='${site_url_link}member/$userIdme/' title='View Your Member Profile' alt='My Profile'>My Profile</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}member/$userIdme/' title='View Your Member Profile' alt='My Profile'>View My Profile</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}editprofilemain/' title='Edit Your Member Profile' alt='Edit Profile'>Edit Profile</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}editprofilemain/editimages/' title='Edit Your Profile Photos' alt='Edit Images'>Edit Images</a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}editprofilemain/picsubmit/' title='Upload Photos to Your Member Profile' alt='Upload Profile Photos'>U<font size=0.5>pload Profile Photos</font></a>
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}editprofilemain/editvehicles/' title='Edit Your Vehicle Profiles and Photos' alt='Edit Vehicles'>Edit Vehicles</a> 
						</td></tr><tr><td class='main_tbl_nav_links_sub'>-<a href='${site_url_link}editprofilemain/account/' title='Edit Your Site Account Settings' alt='Account Settings'>Account Settings</a>";
					echo "</td></tr>";	
				}
		
		echo "<tr><td class='main_tbl_nav_links_title2'>Site Stats</td></tr>";
		
			require "models/total_site_stats.inc";		
		
		echo "<tr><td class='main_tbl_nav_links_subC'></td></tr>";
		echo "</table>"; //End of table
		echo "</nav></div>";
		
		echo "<div class='nav-container2'></div>";

		
?>