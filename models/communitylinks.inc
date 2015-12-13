<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isUserLoggedIn())
{

if(isset($pee)){}else{ $pee = ""; }

//Start of Community Links
echo "<div class='col-lg-12'>";
echo "<div class='alert alert-info' role='alert' style='text-align: center; font-weight: bold'>";

	//view one status
		if($pee == "viewstatus"){
			$ity_title = "Viewing Status";
		}
	//friendstatus
		if($pee == "friendstatus"){
			echo "FriendsStatus";
			$ity_title = "My Friend's Status Updates";
		}
		else{
			echo "<a href='${site_url_link}community/friendstatus/'>FriendsStatus</a>";
		}

	//friendimages
		if($enable_photos == "TRUE"){
			if($usemobile == "TRUE"){ echo "<br>"; }else{ echo " - "; } //changes look for mobile
			if($pee == "friendimages"){
				echo "FriendsImages";
				$ity_title = "My Friend's Profile Images";
			}
			else{
				echo "<a href='${site_url_link}community/friendimages/'>FriendsImages</a>";
			}
		}
	//echo "</td><td  class=index_headertable3>";
		echo "<br>";
	//echo "</td><td  class=index_headertable3 align=right>";
	//mystatus
		if($pee == "mystatus"){
			echo "MyStatus";
			$ity_title = "My Status Updates";
		}
		else{
			echo "<a href='${site_url_link}community/mystatus/'>MyStatus</a>";
		}

	if($enable_photos == "TRUE"){
		if($usemobile == "TRUE"){ echo "<br>"; }else{ echo " - "; } //changes look for mobile
		//myimages
			if($pee == "myimages"){
				echo "MyImages";
				$ity_title = "My Profile Images";
			}
			else{
				echo "<a href='${site_url_link}community/myimages/'>MyImages</a>";
			}
	}
	if($usemobile == "TRUE"){ echo "<br>"; }else{ echo " - "; } //changes look for mobile
	//myfriends
		if($pee == "myfriends"){
			echo "MyFriends";
			$ity_title = "My Friends";
		}
		else{
			echo "<a href='${site_url_link}community/myfriends/'>MyFriends</a>";
		}
echo "</div>";		
echo "</div>";
//End of Community Links

}

?>