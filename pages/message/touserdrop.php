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


$query = "SELECT * FROM ".$db_table_prefix."users ORDER BY `userId` ASC";
$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query.");

echo '<select name="mto">';

while ($row = mysqli_fetch_array($result))
{

	extract($row);
		
          echo "<option value='$userName' ";
	if($mto == $userId){echo "SELECTED";}
	if($mto == $userName){echo "SELECTED";}
	echo " >$userName</option>";

}

echo '</select>';



?>