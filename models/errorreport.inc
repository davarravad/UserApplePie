<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

	#This script is built to get all possible information about a visitor
	#Shows Current User Information
 	
	#Get the Refering Page if There is one
	if(isset($_SERVER['HTTP_REFERER'])){ $er_refer = $_SERVER['HTTP_REFERER']; }else{ $er_refer = ""; } 

	#Will return the type of web browser or user agent that is being used to access the current script.
	$er_useragent = $_SERVER['HTTP_USER_AGENT']; 
	
	#The filename of the currently executing script, relative to the document root.
	$er_cfile = $_SERVER['PHP_SELF']; 
	
	#Prints the exact path and filename relative to the DOCUMENT_ROOT of your site.
	$er_uri = $_SERVER['REQUEST_URI'];
	
	#Contains the IP address of the user requesting the PHP script from the server.
	$er_ipaddy = $_SERVER['REMOTE_ADDR']; 
	
	#Returns the name of the webserver or virtual host that is processing the request. 
	#For example, if you were visiting http://www.phpfreaks.com then the result would be www.phpfreaks.com.
	$er_server = $_SERVER['SERVER_NAME']; 

	
			//Insert error information to database
			//$query = "INSERT INTO `errors` SET `er_type`='$er_type',`er_location`='$er_location',`er_msg`='$er_msg',`er_user`='$nname',`er_refer`='$er_refer',`er_useragent`='$er_useragent',`er_cfile`='$er_cfile',`er_uri`='$er_uri',`er_ipaddy`='$er_ipaddy',`er_server`='$er_server'";

			$stmt = $mysqli->prepare("INSERT INTO ".$db_table_prefix."errors(er_type, er_location, er_msg, er_user, er_refer, er_useragent, er_cfile, er_uri, er_ipaddy, er_server) 
										VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
			$stmt->bind_param("ssssssssss", $er_type, $er_location, $er_msg, $nname, $er_refer, $er_useragent, $er_cfile, $er_uri, $er_ipaddy, $er_server);
			if ($result = $stmt->execute()){

				echo( "<br><br><center>Error Reported!</center><br><br>" );
				$stmt->free_result();

			} else {
				die( "Error" );
			}
			$stmt->close();
			
    


?>
</center>
