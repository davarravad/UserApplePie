<?php
//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

include "auth.php";

   // saving script



   // connect to the server
   ($GLOBALS["___mysqli_ston"] = mysqli_connect( 'localhost',  'root',  'rootld1985' ))
      or die( "Error! Could not connect to database: " . ((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_error($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_error()) ? $___mysqli_res : false)) );
   
   // select the database
   ((bool)mysqli_query($GLOBALS["___mysqli_ston"], "USE bizat"))
      or die( "Error! Could not select the database: " . ((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_error($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_error()) ? $___mysqli_res : false)) );
   
   // get the variables from the URL request string
      $topic = $_REQUEST['topic'];
      $author = $_REQUEST['author'];
      $month = $_REQUEST['month'];
      $day = $_REQUEST['day'];
      $year = $_REQUEST['year'];
      $content1 = $_REQUEST['content1'];
      $content2 = $_REQUEST['content2'];
      $content3 = $_REQUEST['content3'];
      $content4 = $_REQUEST['content4'];
      $content5 = $_REQUEST['content5'];
      $click1 = $_REQUEST['click1'];
      $click1url = $_REQUEST['click1url'];
      $click2 = $_REQUEST['click2'];
      $click2url = $_REQUEST['click2url'];
      $click3 = $_REQUEST['click3'];
      $click3url = $_REQUEST['click3url'];
      $click4 = $_REQUEST['click4'];
      $click4url = $_REQUEST['click4url'];
      $click5 = $_REQUEST['click5'];
      $click5url = $_REQUEST['click5url'];

	$date = "$year-$month-$day";
	 

   {
      $query = "INSERT INTO `archives` SET `topic`='$topic',`author`='$author',`date`='$date',`content1`='$content1',`content2`='$content2',`content3`='$content3',`content4`='$content4',`content5`='$content5',`click1`='$click1',`click1url`='$click1url',`click2`='$click2',`click2url`='$click2url',`click3`='$click3',`click3url`='$click3url',`click4`='$click4',`click4url`='$click4url',`click5`='$click5',`click5url`='$click5url'";
   }
  

 $results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

   // print out the results
   if( $results )
   {
      echo( "Admin Submit<br><br>" );
      echo( "Successfully saved the entry.<br><br>" );

   
   }
 
   else
   {
		//Code used to report mysql error
		$mysql_error_report = "TRUE";
		$sql_query = "$query";
		require "models/mysql_error_report.inc";
   }
    
   
?>


