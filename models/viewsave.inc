<?

global $mysqli, $site_url_link, $db_table_prefix;

if(!isset($view_sub)){ $view_sub = ""; }
if(!isset($view_sec_id)){ $view_sec_id = ""; }	

			$querySW = "INSERT INTO `".$db_table_prefix."views` SET 
				`view_id`='$view_id',
				`view_sec_id`='$view_sec_id',
				`view_sub`='$view_sub',
				`view_location`='$view_location',
				`view_userid`='$view_userid',
				`view_url`='$view_url', 
				`view_owner_userid`='$view_owner_userid' 
				";

			$resultsSW = mysqli_query($GLOBALS["___mysqli_ston"],  $querySW );
	
			// print out the results
   			if( $resultsSW )
   			{
				//echo( "Successfully saved view entry.<br><br>" );
   
			}else{
				//Code used to report mysql error
				$mysql_error_report = "TRUE";
				$sql_query = "$query";
				require "models/mysql_error_report.inc";
			}

			//echo "<br> ( $view_sub $view_location - $view_id - $view_userid - $view_url ) ";  //for testing


?>