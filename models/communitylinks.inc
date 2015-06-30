<?

if(isUserLoggedIn())
{

if(isset($pee)){}else{ $pee = ""; }

//Start of Community Links
echo "<table width=100% cellspacing=0 class=index_headertable3tbl><tr><td class=index_headertable3><center>";

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

	if($usemobile == "TRUE"){ echo "<br>"; }else{ echo " - "; } //changes look for mobile
	//friendimages
		if($pee == "friendimages"){
			echo "FriendsImages";
			$ity_title = "My Friend's Profile Images";
		}
		else{
			echo "<a href='${site_url_link}community/friendimages/'>FriendsImages</a>";
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

	if($usemobile == "TRUE"){ echo "<br>"; }else{ echo " - "; } //changes look for mobile
	//myimages
		if($pee == "myimages"){
			echo "MyImages";
			$ity_title = "My Profile Images";
		}
		else{
			echo "<a href='${site_url_link}community/myimages/'>MyImages</a>";
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
echo "</center></td></tr></table><br>";		
//End of Community Links

}

?>