<?

	if(isset($_REQUEST['profile'])){ $profile = intval($_REQUEST['profile']); }else{ $profile = ""; }
	if(!isset($_REQUEST['page'])){ $taz = ""; }
	
	if(!empty($_REQUEST['page'])){
		
		if(empty($taz)){ $taz = $_REQUEST['page']; }
		
		if($taz == "login"){
			$tazib_sublinks = "Welcome back to CarTruckClubs.com! Login, Enjoy, and Happy posting!";
		}
		if($taz == 'register'){
			$tazib_sublinks = "Thank you for joining us at CarTruckClubs.com!  Enjoy and Happy posting!";
		}
		if($taz == 'help'){
			$tazib_sublinks = "So you need help?  Well you have found it.";
		}
		
		if(($taz == 'stories') || ($taz == 'poems') || ($taz == 'quotes') || ($taz == 'submitwriting')){
			$tazib_sublinks = "Glad to see you are adding a vehicle profile to the site.  Can't wait to see photos!";
		}

		if($taz == 'swapmeet'){
			$tazib_sublinks = "<strong>Swap Meet</strong>";
		}
		if(($taz == 'writings') || ($taz == 'art') || ($taz == 'Custom') || ($taz == 'Classic') || ($taz == 'graphics') || ($taz == 'submitart') || ($taz == 'artview') || ($taz == 'writingview')){
			$tazib_sublinks = "<strong>Vehicles</strong>";	
		}
		if(isset($_GET['club'])){ $is_club = "yes"; }else{ $is_club = ""; }
		if(($taz == 'club') || ($is_club == 'yes')){
			$tazib_sublinks = "<strong>Clubs</strong>";
		}
		if(($taz == 'community') || ($taz == 'members') || ($taz == 'friends')){
			$tazib_sublinks = "<strong>Community</strong>";
		}
		if($taz == 'message') {
				if(isUserLoggedIn())
				{
						require "models/members/getuserinfo.inc";

						$query = "SELECT * FROM `".$db_table_prefix."inbox` WHERE `mto` = '$nname' AND `mread` = 'unread' ";
						$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
							or die ("Couldn't ececute query. 564");
						
						$rows = mysqli_num_rows($result); 

							if ($rows) {
								$row_pr = " <strong><a href='${site_url_link}message'>$rows</a></strong> ";
							}
							else {
								$row_pr = " <strong><a href='${site_url_link}message'>0</a></strong> ";
							}
							
					//Display links if user is logged in
					$tazib_sublinks = "
						Message > $row_pr New - 
						<a href='${site_url_link}message/?mes=inbox'>Inbox</a> - 
						<a href='${site_url_link}message/?mes=newmessage'>Create NEW Message</a> - 
						<a href='${site_url_link}message/?mes=outbox'>Outbox</a>
					";
				}else{
					$tazib_sublinks = "Login to send messages to Car Truck Clubs members!";
				}
			
		}
		
		if(($taz == 'profile') || ($taz == 'viewprofile') || ($taz == 'editprofilemain') || ($profile > 0)){
		
			if(isset($_REQUEST['ID'])){ $taz_id = $_REQUEST['ID']; }else{ $taz_id = ""; }
			if(isset($_REQUEST['profile'])){ $taz_id = $_REQUEST['profile']; }else{ $taz_id = ""; }

				if(isUserLoggedIn())
				{
					if($taz_id == '$userIdme'  || ($taz == 'editprofilemain')){
						//Display links if user is logged in
						$tazib_sublinks = "<strong>My Profile</strong>";
					
					}else{
						$taz_pro_1 = "You are currently viewing";
							$query = "SELECT * FROM ".$db_table_prefix."users WHERE `userId`='$taz_id' ";
							$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
								or die ("Couldn't ececute query. 6546");
														
							while ($row = mysqli_fetch_array($result))
							{
								extract($row);	
									
								$taz_pro = " $userName";
							
							}
						$taz_pro_2 = "'s Profile";
						$tazib_sublinks = "$taz_pro_1$taz_pro$taz_pro_2";				
						
					}
				}else{
						$taz_pro_1 = "You are currently viewing";
							$query = "SELECT * FROM ".$db_table_prefix."users WHERE `userId`='$taz_id' ";
							$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
								or die ("Couldn't ececute query. Sublinks 58465");
														
							while ($row = mysqli_fetch_array($result))
							{
								extract($row);	
									
								$taz_pro = " $userName";
							
							}
						$taz_pro_2 = "'s Profile";
						if(!isset($taz_pro)){ $taz_pro = ""; }
						$tazib_sublinks = "$taz_pro_1$taz_pro$taz_pro_2";				
						
				}
		}		
	} else {
		$tazib_sublinks = "Welcome to Car Truck Clubs!  Home to Custom and Classic Vehicles!";
	}

	
if(isset($tazib_sublinks)){}else{ $tazib_sublinks = "Welcome to Car Truck Clubs!  Home to Custom and Classic Vehicles!"; }

?>