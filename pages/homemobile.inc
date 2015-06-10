<?php
	//Displays logged in user pannel
	if(isUserLoggedIn()){

		require("models/welcomemem.inc");

	}

if(isUserLoggedIn()){}else{
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='4' align='center'><tr>";
	echo "<td width='100%' valign='top'>";
		echo "<center>";
		echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2' width='100%'>";

		//Display random art
		$query = "SELECT * FROM art WHERE `new`='yes' ORDER BY RAND() DESC LIMIT 1";

			//echo "<center><table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";

				$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
					or die ("Couldn't ececute query. 5413211058");

			echo "<center>:<strong>Random Vehicle</strong>:</center>";
			//echo "</td></tr></table></center>";
			
		echo "</td></tr><tr><td class='content78' height='125' valign='center'><center>";

		while ($row = mysqli_fetch_array($result))
		{
			extract($row);

				//echo "&nbsp;-<a href='?page=bn/art/view&id=$id'>$title</a> - $name - <a href='?page=bn/art/${type}'>$type</a> <br>";
				echo "<a href='${site_url_link}VehiclePhoto/$id/'><img class='rounded_10' src='/content/art/thumb/${imgname}' border='0' height='75'></a>&nbsp;";
				$id_AA = "$id";
		}
		
			echo "</center>";
		echo "</td></tr></table>";
		echo "</center>";

	echo "</td></tr><tr><td width='100%' valign='top'>";		
	

		echo "<center>";
		echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2' width='100%'>";

		if(!isset($id_AA)){ $id_AA = ""; }
		//Display random art
		$query = "SELECT * FROM art WHERE `new`='yes' AND NOT `id`='$id_AA' ORDER BY RAND() DESC LIMIT 1";

		$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
			or die ("Couldn't ececute query. 4213258");

		echo "<center>:<strong>Random Vehicle</strong>:</center>";

		echo "</td></tr><tr><td class='content78' height='125' valign='center'><center>";

		while ($row = mysqli_fetch_array($result))
		{
			extract($row);
				//echo "&nbsp;-<a href='?page=bn/art/view&id=$id'>$title</a> - $name - <a href='?page=bn/art/${type}'>$type</a> <br>";
				echo "<a href='${site_url_link}VehiclePhoto/$id/'><img class='rounded_10' src='/content/art/thumb/${imgname}' border='0' height='75'></a>&nbsp;";
				$id_BB = "$id";
		}
		
			echo "</center>";


		echo "</td></tr></table>";
		echo "</center>";
		
		
	echo "</td></tr><tr><td width='100%' valign='top'>";
	
		echo "<center>";
		echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2' width='100%'>";

		if(!isset($id_BB)){ $id_BB = ""; }
		//Display random art
		$query = "SELECT * FROM art WHERE `new`='yes' AND NOT `id`='$id_AA' AND NOT `id`='$id_BB' ORDER BY RAND() DESC LIMIT 1";

		$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
			or die ("Couldn't ececute query. 5412185");

		echo "<center>:<strong>Random Vehicle</strong>:</center>";

		echo "</td></tr><tr><td class='content78' height='125' valign='center'><center>";

		while ($row = mysqli_fetch_array($result))
		{
			extract($row);
				//echo "&nbsp;-<a href='?page=bn/art/view&id=$id'>$title</a> - $name - <a href='?page=bn/art/${type}'>$type</a> <br>";
				echo "<a href='${site_url_link}VehiclePhoto/$id/'><img class='rounded_10' src='/content/art/thumb/${imgname}' border='0' height='75'></a>&nbsp;";
		}
		
			echo "</center>";


		echo "</td></tr></table>";
		echo "</center>";
	echo "</td></tr><tr><td><br><center><b>Not a member yet?  <a href=${site_url_link}register/>Sign Up</a>!</b></center>";
	echo "</td></tr></table>";
	echo "<br>";
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
		else{ echo "<a href='${site_url_link}rp/comments/'>Comments</a>"; } echo " <br> ";
		if($rc_view == "clubs"){ echo "<font color=#E89104>Clubs</font>"; }
		else{ echo "<a href='${site_url_link}rp/clubs/'>Clubs</a>"; } echo " - ";
		if($rc_view == "vehpro"){ echo "<font color=#E89104>Vehicle Profiles</font>"; }
		else{ echo "<a href='${site_url_link}rp/vehpro/'>Vehicle Profiles</a>"; } echo " - ";
		if($rc_view == "vehpic"){ echo "<font color=#E89104>Vehicle Photos</font>"; }
		else{ echo "<a href='${site_url_link}rp/vehpic/'>Vehicle Photos</a>"; } echo "  ";
	}

	echo "</td></tr><tr><td width='100%'  align='center' valign='top' class='content78'>";
	require "pages/recentpost.inc";
	echo "</td></tr></table>";
	echo "<br>";

	
	//if user is not logged in Show the signup form
	if(isUserLoggedIn())
	{} else {	
		echo "<center><h3>";
		echo "Welcome to CarTruckClubs.com.  Login or Register and Enjoy!";
		echo "</h3></center>";

	}

 ?>