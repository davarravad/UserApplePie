<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

if(isUserLoggedIn()){

		if(is_admin()) {


if(isset($_REQUEST['view'])){ $view = $_REQUEST['view']; }else{ $view = ""; }

	echo "<center>";
	echo "<strong>Admin Zone - View Recent Comments</strong>"; 
	echo "</center>";

?>



Select the type of comments you would like to review then select "View"!<br>
<form name="${site_url_link}YummyAsPie/viewcomments/" method="post" action="">
  <select name="view" id="view">
	<option value="artcomments" <?php if($view == 'artcomments'){echo "SELECTED";} ?> >Vehicle Pic Comments</option>
	<option value="writingcomments" <?php if($view == 'writingcomments'){echo "SELECTED";} ?> >Vehicle Profile Comments</option>
	<option value="comments" <?php if($view == 'comments'){echo "SELECTED";} ?> >Profile Comments</option>
	<option value="clubcomments" <?php if($view == 'clubcomments'){echo "SELECTED";} ?> >Club Comments</option>
	<option value="club_events_com" <?php if($view == 'club_events_com'){echo "SELECTED";} ?> >Club Events Comments</option>
	<option value="location_comments" <?php if($view == 'location_comments'){echo "SELECTED";} ?> >Location Comments</option>
  </select>
<input type="submit" name="Submit" value="View">
</form>

<?php
if($view == 'writingcomments'){


$query = "SELECT * FROM writingcomments ORDER BY `id` DESC LIMIT 30";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. ViewCom 23309");


while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);


	echo "<div class='$bgcolor'><strong>Name:</strong> ";
	echo " $com_name";
	echo "<br><strong>URL:</strong> ";
	echo " <a href='${site_url_link}VehicleProfile/$com_id/#com$id'>View Vehicle Profile Comment</a>";
	echo "<br><strong>Comment:</strong> ";
	echo " $com_content";
	echo "<br><strong>Submit Date:</strong> ";
	echo " $timestamp";

		//Displays total comment comments
		$queryCOMC = "SELECT * FROM writingcomments_b WHERE `statcom_id`='$id' ORDER BY `id`";
		$resultCOMC = mysqli_query($GLOBALS["___mysqli_ston"], $queryCOMC);
		$num_rows_commentsCOMC = mysqli_num_rows($resultCOMC);
		if($num_rows_commentsCOMC > 0){
			$ttl_num_comments = $num_rows_commentsCOMC;	
		}
		if(isset($ttl_num_comments)){}else{ $ttl_num_comments = "0"; }
			$ttl_num_cmts = $ttl_num_comments; 
		echo "<br><strong>Comment Comments:</strong> $ttl_num_cmts";
		unset($queryCOMC, $resultCOMC, $num_rows_commentsCOMC, $ttl_num_comments, $ttl_num_cmts);
		
	echo "</div><br>";
}

}
?>
<?php
if($view == 'artcomments'){

$query = "SELECT * FROM artcomments ORDER BY `id` DESC LIMIT 30";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. ViewCom 34245");



while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);


	echo "<div class='$bgcolor'><strong>Name:</strong> ";
	echo " $com_name";
	echo "<br><strong>URL:</strong> ";
	echo " <a href='${site_url_link}VehiclePhoto/$com_id/#com$id'>View Vehicle Comment</a>";
	echo "<br><strong>Comment:</strong> ";
	echo " $com_content";
	echo "<br><strong>Submit Date:</strong> ";
	echo " $timestamp";
	
	
		//Displays total comment comments
		$queryCOMC = "SELECT * FROM artcomments_b WHERE `statcom_id`='$id' ORDER BY `id`";
		$resultCOMC = mysqli_query($GLOBALS["___mysqli_ston"], $queryCOMC);
		$num_rows_commentsCOMC = mysqli_num_rows($resultCOMC);
		if($num_rows_commentsCOMC > 0){
			$ttl_num_comments = $num_rows_commentsCOMC;	
		}
		if(isset($ttl_num_comments)){}else{ $ttl_num_comments = "0"; }
			$ttl_num_cmts = $ttl_num_comments; 
		echo "<br><strong>Comment Comments:</strong> $ttl_num_cmts";
		unset($queryCOMC, $resultCOMC, $num_rows_commentsCOMC, $ttl_num_comments, $ttl_num_cmts);
	
	echo "</div><br>";

}

}
?>
<?php
if($view == 'clubcomments'){


$query = "SELECT * FROM clubcomments ORDER BY `id` DESC LIMIT 30";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. VC 56465");



while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);


	echo "<div class='$bgcolor'><strong>Name:</strong> ";
	echo " $com_name";
	echo "<br><strong>URL:</strong> ";
	echo " <a href='/Club/$com_id/#com$id'>View Club Comment</a>";
	echo "<br><strong>Comment:</strong> ";
	echo " $com_content";
	echo "<br><strong>Submit Date:</strong> ";
	echo " $timestamp";
	
	
		//Displays total comment comments
		$queryCOMC = "SELECT * FROM clubcomments_b WHERE `statcom_id`='$id' ORDER BY `id`";
		$resultCOMC = mysqli_query($GLOBALS["___mysqli_ston"], $queryCOMC);
		$num_rows_commentsCOMC = mysqli_num_rows($resultCOMC);
		if($num_rows_commentsCOMC > 0){
			$ttl_num_comments = $num_rows_commentsCOMC;	
		}
		if(isset($ttl_num_comments)){}else{ $ttl_num_comments = "0"; }
			$ttl_num_cmts = $ttl_num_comments; 
		echo "<br><strong>Comment Comments:</strong> $ttl_num_cmts";
		unset($queryCOMC, $resultCOMC, $num_rows_commentsCOMC, $ttl_num_comments, $ttl_num_cmts);
	
	
	echo "</div><br>";
}

}
?>
<?php
if($view == 'club_events_com'){


$query = "SELECT * FROM club_events_com ORDER BY `id` DESC LIMIT 30";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 5843251");



while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);


	echo "<div class='$bgcolor'><strong>Name:</strong> ";
	echo " $com_name";
	echo "<br><strong>URL:</strong> ";
	echo " <a href='/Clubs/?pee=clubs'>View Club Event Comment</a>";
	echo "<br><strong>Comment:</strong> ";
	echo " $com_content";
	echo "<br><strong>Submit Date:</strong> ";
	echo " $timestamp";
	
	
		//Displays total comment comments
		$queryCOMC = "SELECT * FROM club_events_com_b WHERE `statcom_id`='$id' ORDER BY `id`";
		$resultCOMC = mysqli_query($GLOBALS["___mysqli_ston"], $queryCOMC);
		$num_rows_commentsCOMC = mysqli_num_rows($resultCOMC);
		if($num_rows_commentsCOMC > 0){
			$ttl_num_comments = $num_rows_commentsCOMC;	
		}
		if(isset($ttl_num_comments)){}else{ $ttl_num_comments = "0"; }
			$ttl_num_cmts = $ttl_num_comments; 
		echo "<br><strong>Comment Comments:</strong> $ttl_num_cmts";
		unset($queryCOMC, $resultCOMC, $num_rows_commentsCOMC, $ttl_num_comments, $ttl_num_cmts);
	
	
	echo "</div><br>";
}

}
?>
<?php
if($view == 'location_comments'){


$query = "SELECT * FROM location_comments ORDER BY `id` DESC LIMIT 30";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 564213");



while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);


	echo "<div class='$bgcolor'><strong>Name:</strong> ";
	echo " $com_name";
	echo "<br><strong>URL:</strong> ";
	echo " <a href='${site_url_link}location/$com_id/#com$id'>View Location Comment</a>";
	echo "<br><strong>Comment:</strong> ";
	echo " $com_content";
	echo "<br><strong>Submit Date:</strong> ";
	echo " $timestamp";
	
	
		//Displays total comment comments
		$queryCOMC = "SELECT * FROM location_comments_b WHERE `statcom_id`='$id' ORDER BY `id`";
		$resultCOMC = mysqli_query($GLOBALS["___mysqli_ston"], $queryCOMC);
		$num_rows_commentsCOMC = mysqli_num_rows($resultCOMC);
		if($num_rows_commentsCOMC > 0){
			$ttl_num_comments = $num_rows_commentsCOMC;	
		}
		if(isset($ttl_num_comments)){}else{ $ttl_num_comments = "0"; }
			$ttl_num_cmts = $ttl_num_comments; 
		echo "<br><strong>Comment Comments:</strong> $ttl_num_cmts";
		unset($queryCOMC, $resultCOMC, $num_rows_commentsCOMC, $ttl_num_comments, $ttl_num_cmts);
	
	
	echo "</div><br>";
}

}
?>
<?php

if($view == 'comments'){

//$com_id = $id;

$query = "SELECT * FROM profilecomments ORDER BY `id` DESC  LIMIT 30";

$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query.98452");



while ($row = mysqli_fetch_array($result))
{
		$bgcolor = "epboxa";

	extract($row);


	echo "<div class='$bgcolor'><strong>Name:</strong>";
	echo " $com_name  <br>";
	echo "<strong>URL:</strong>";
	echo " <a href='${site_url_link}member/$com_id/#com$id'>View Profile Comment</a>";
	echo "<br><strong>Comment:</strong> ";
	echo " $com_content ";
	echo "<br><strong>Submit Date:</strong> ";
	echo " $timestamp";
	
	
		//Displays total comment comments
		$queryCOMC = "SELECT * FROM profilecomments_b WHERE `statcom_id`='$id' ORDER BY `id`";
		$resultCOMC = mysqli_query($GLOBALS["___mysqli_ston"], $queryCOMC);
		$num_rows_commentsCOMC = mysqli_num_rows($resultCOMC);
		if($num_rows_commentsCOMC > 0){
			$ttl_num_comments = $num_rows_commentsCOMC;	
		}
		if(isset($ttl_num_comments)){}else{ $ttl_num_comments = "0"; }
			$ttl_num_cmts = $ttl_num_comments; 
		echo "<br><strong>Comment Comments:</strong> $ttl_num_cmts";
		unset($queryCOMC, $resultCOMC, $num_rows_commentsCOMC, $ttl_num_comments, $ttl_num_cmts);
	
	
	echo "</div><Br>";

}

}



		}
		else{
			echo "Admin Only.";
			exit();
		}

	}
	else{
		notlogedinmsg();
		exit();
	}

?>