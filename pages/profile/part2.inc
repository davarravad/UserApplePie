<style type="text/css">
#img_thumb {
	border:0;
	outline:none;
	max-height:75px;
}
</style>

<?php
// Extened profile information
// Display profile textboxes if they are set

//Check to see if there are any extended profiles
$queryCKP2 = "SELECT `".$db_table_prefix."ep2`.`textfield` FROM ".$db_table_prefix."ep2 WHERE `userId`='$ID02' AND NOT `textfield`='' OR `textfield`='NULL' ";
//$resultCKP2 = mysql_query($queryCKP2);

//$num_rowsCKP2 = mysql_num_rows($resultCKP2);

$query_CKP2 = $mysqli->prepare("$queryCKP2");
$query_CKP2->execute();
$query_CKP2->store_result();

$num_rowsCKP2 = $query_CKP2->num_rows;

// Test - Show how many rows for queryCKP2
//echo "($num_rowsCKP2)";

if($num_rowsCKP2 != 0){

	$query = "SELECT * FROM ".$db_table_prefix."ep2 WHERE `userId`='$ID02' ";

	$result = $mysqli->query($query);
	
	$arr = $result->fetch_all(MYSQLI_BOTH);
	
	
	
	foreach($arr as $row)
	{

		// Add BR thingy somewhere
		if(!empty($row['textfield'])){
			$textfield = stripslashes($row['textfield']);
		}else{}
			$textarea = stripslashes($row['textarea']);
			$textfield2 = stripslashes($row['textfield2']);
			$textarea2 = stripslashes($row['textarea2']);
			$textfield3 = stripslashes($row['textfield3']);
			$textarea3 = stripslashes($row['textarea3']);
			$textfield4 = stripslashes($row['textfield4']);
			$textarea4 = stripslashes($row['textarea4']);
			$textfield5 = stripslashes($row['textfield5']);
			$textarea5 = stripslashes($row['textarea5']);
			$textfield6 = stripslashes($row['textfield6']);
			$textarea6 = stripslashes($row['textarea6']);
			$textfield7 = stripslashes($row['textfield7']);
			$textarea7 = stripslashes($row['textarea7']);
			$textfield8 = stripslashes($row['textfield8']);
			$textarea8 = stripslashes($row['textarea8']);

		if(!empty($textfield)){
				echo "<hr align='center' width='100%' />";
				echo "<center>";
				echo "<table width='100%'><tr><td align='center'>";
				
				echo "<strong>More Information About ";
				get_user_name($ID02);
				echo "</strong>";
				
				echo "</td></tr><tr><td align='center'>";

				echo "
					<div align='center' class='epboxb'><strong>$textfield</strong></div>
					<div class='epboxa' width='100%'>
						  $textarea
					</div><br>
			";
		}
		if(!empty($textarea2)){
			echo "
				
					<div align='center' class='epboxb'><strong>$textfield2</strong></div>
					<div class='epboxa' width='100%'> 
					  $textarea2
					</div><br>
			";
		}
		if(!empty($textarea3)){
			echo "	
					<div align='center' class='epboxb'><strong>$textfield3</strong></div>
					<div class='epboxa' width='100%'> 
					  $textarea3
					</div><br>
			";
		}
		if(!empty($textarea4)){
			echo "
					<div align='center' class='epboxb'><strong>$textfield4</strong></div>
					<div class='epboxa' width='100%'>
					  $textarea4
					</div><br>
			";
		}
		if(!empty($textarea5)){
			echo "
				<div align='center' class='epboxb'><strong>$textfield5</strong></div>
				<div class='epboxa' width='100%'>
				  $textarea5
				</div><br>
			";
		}
		if(!empty($textarea6)){
			echo "
				
				<div align='center' class='epboxb'><strong>$textfield6</strong></div>
				<div class='epboxa' width='100%'>
				  $textarea6
				</div><br>
			";
		}
		if(!empty($textarea7)){
			echo "
				<div align='center' class='epboxb'><strong>$textfield7</strong></div>
				<div class='epboxa' width='100%'>
				  $textarea7
				</div><br>
			";
		}
		if(!empty($textarea8)){
			echo "
				<div align='center' class='epboxb'><strong>$textfield8</strong></div>
				<div class='epboxa' width='100%'>
				  $textarea8
				</div>
			";
		}
		if(!empty($textfield)){
			echo "</td></tr></table>";
			echo "</center>";
		}

	}
	
	
	
} 

?>