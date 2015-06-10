<?
	echo "<center>";
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
	
	$query = "SELECT * FROM ".$db_table_prefix."loggedusers ORDER BY `userId` ASC";
	$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
	or die ("Couldn't ececute query. 541328");

	//Page Title
	echo "Who's Online?";
	echo "</td></tr><tr><td class='content78'>";

		while ($row = mysqli_fetch_array($result))
		{
			extract($row);

				echo " - ";
				$query2 = "SELECT * FROM ".$db_table_prefix."users WHERE `id` = '$userId' ";
				$result2 = mysqli_query($GLOBALS["___mysqli_ston"], $query2)
				or die ("Couldn't ececute query2.");

					if( $result2 && $contact = mysqli_fetch_object( $result2 ) )
					{
						$userName = $contact -> display_name;
					}

				echo "<a href='${site_url_link}member/$userId/'>$userName</a>";
					
					if($userName == 'DaVaR')
					{
						echo " <font color='green' size='1'>Admin</font>";
					}
					if($userName == 'DaVaRTest')
					{
						echo " <font color='green' size='1'>Tester</font>";
					}

				echo "<br>";

		}

	echo "</td></tr></table>";
?>
