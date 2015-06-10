<?php

if(isset($GET_USR_ID)){}else{$GET_USR_ID = "";}
$query_GUI = "SELECT * FROM ".$db_table_prefix."users WHERE `id` = '$GET_USR_ID'";
$result_GUI = mysqli_query($GLOBALS["___mysqli_ston"], $query_GUI);

// print out the results
if( $result_GUI && $contact_GUI = mysqli_fetch_object( $result_GUI ) )
{
    // print out the info
    $GET_USR_NAME = $contact_GUI -> display_name;

}

if(!empty($GET_USR_NAME)){
	$GET_USR_NAME = "$GET_USR_NAME";
}else{
	$GET_USR_NAME = "";
}

?>