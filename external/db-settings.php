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

//Database Information
$db_host = "localhost"; //Host address (most likely localhost)
$db_name = "uap_database"; //Name of Database
$db_user = "uap_user"; //Name of database user
$db_pass = "uap_password"; //Password for database user
$db_table_prefix = "uap_";

// Sets globals for sql with updated sql
$conn=($GLOBALS["___mysqli_ston"] = mysqli_connect("$db_host",  "$db_user",  "$db_pass", "$db_name", "3306")) or die ('Cannot connect to the database because: ' . ((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_error($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_error()) ? $___mysqli_res : false)));
// Work the above sql connection out in time ^^^

GLOBAL $errors;
GLOBAL $successes;

$errors = array();
$successes = array();

/* Create a new mysqli object with database connection parameters */
$mysqli = new mysqli($db_host, $db_user, $db_pass, $db_name);
GLOBAL $mysqli;

if(mysqli_connect_errno()) {
	echo "Connection Failed: " . mysqli_connect_errno();
	exit();
}

/*PDO Settings*/
try {
     $DBH = new PDO("mysql:host={$db_host};dbname={$db_name}",$db_user,$db_pass);
     $DBH->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
}
catch(PDOException $e) {
     echo $e->getMessage();
}

//Direct to install directory, if it exists
if(is_dir("install/"))
{
	header("Location: ../install/");
	die();

}

?>