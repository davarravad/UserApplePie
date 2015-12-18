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


//Displays all of users submits on site

$q_status = "
(SELECT ".$db_table_prefix."status.com_id FROM ".$db_table_prefix."status
WHERE ".$db_table_prefix."status.com_id = '$ID02')
";

$q_status_com = "
(SELECT ".$db_table_prefix."statcom.statcom_uid FROM ".$db_table_prefix."statcom
WHERE ".$db_table_prefix."statcom.statcom_uid = '$ID02')
";


$pc_status = "
(SELECT ".$db_table_prefix."profilecomments.com_uid FROM ".$db_table_prefix."profilecomments
WHERE ".$db_table_prefix."profilecomments.com_uid = '$ID02')
";

$pc_statcom = "
(SELECT ".$db_table_prefix."profilecomments_b.statcom_uid FROM ".$db_table_prefix."profilecomments_b
WHERE ".$db_table_prefix."profilecomments_b.statcom_uid = '$ID02')
";

$ep3 = "
(SELECT ".$db_table_prefix."ep3.userId FROM ".$db_table_prefix."ep3
WHERE ".$db_table_prefix."ep3.userId=$ID02)
";


			$query = "
				$ep3 UNION ALL
				$q_status UNION ALL
				$q_status_com UNION ALL
				$pc_status UNION ALL
				$pc_statcom
			";

			//echo " $query ";
			
		$result2 = mysqli_query($GLOBALS["___mysqli_ston"], $query)
			or die ("Couldn't ececute query. 984652");

		$total_user_submits = mysqli_num_rows($result2);



?>