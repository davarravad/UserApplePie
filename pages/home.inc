<?
	//Sets the title to the home page for website
	//echo "<title>Car Truck Clubs- www.cartruckclubs.com</title>";
	echo "<meta name=\"description\" content=\"$site_gbl_descript\">";
	//Page Content
	
	//Displays logged in user pannel
	if(isUserLoggedIn()){

		require("models/welcomemem.inc");

	}

	if(isUserLoggedIn()){}else{
		//Send member to home page
		$redir_link_home = "$websiteUrl";
		header("Location: $redir_link_home");
		exit;
	}
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='4' align='center'><tr>";
	echo "<td width='100%'  align='center' valign='middle' class='hr2'>";
	echo "Newest Content<br>";

	if(isUserLoggedIn())
	{
		if(isset($_REQUEST['rc_view'])){ $rc_view = $_REQUEST['rc_view']; }else{ $rc_view = ""; }
		if($rc_view == "status"){ echo "<font color=#E89104>Status</font>"; }
		else{ echo "<a href='${site_url_link}rp/status/'>Status</a>"; } echo " - ";
		if($rc_view == "sweets"){ echo "<font color=#E89104>Sweets</font>"; }
		else{ echo "<a href='${site_url_link}rp/sweets/'>Sweets</a>"; } echo " - ";
		if($rc_view == "comments"){ echo "<font color=#E89104>Comments</font>"; }
		else{ echo "<a href='${site_url_link}rp/comments/'>Comments</a>"; } echo "  ";
	}

	echo "</td></tr><tr><td width='100%'  align='center' valign='top' class='content78'>";
	require "pages/recentpost.inc";
	echo "</td></tr></table>";

	//if user is not logged in Show the signup form
	if(isUserLoggedIn())
	{} else {	
		echo "<center><h3>";
		echo "Welcome to CarTruckClubs.com.  Login or Register and Enjoy!";
		echo "</h3></center>";

	}

 ?>