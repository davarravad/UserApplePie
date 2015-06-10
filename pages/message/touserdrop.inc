<?php


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