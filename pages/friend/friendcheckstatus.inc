<?php
$query31 = "SELECT status1, status2 FROM ".$db_table_prefix."friend WHERE ((`userId1`='$userId1a' AND `userId2`='$userId2a') OR (`userId1`='$userId2a' AND `userId2`='$userId1a')) LIMIT 1";
$result31 = mysqli_query($GLOBALS["___mysqli_ston"], $query31);
	//or die ("Couldn't ececute query.");

$num_rows31 = mysqli_num_rows($result31);


	//echo "$num_rows31 -";
if($num_rows31 == 0){
	$statfriend = "NO";
}
else{
		
	while ($row31 = mysqli_fetch_array($result31))
	{
		extract($row31);	

		//echo "$userId1 - $userId2 - $status1 - $status2 <br>";
		if($status1 == "1"){
			if($status2 == "1"){
				$statfriend = "YES";
			}else{
				$statfriend = "NO";
			}
		}
	}
}
		
?>