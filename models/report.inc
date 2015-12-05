<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

//Report Abuse, Error, Suggestion button

if(isUserLoggedIn())
{
	
	echo "<table><tr><td width=700 align=right>";
	if(isset($_POST['report_form'])){ $report_form = $_POST['report_form']; }else{ $report_form = ""; }
	if(isset($_POST['report_submit'])){ $report_submit = $_POST['report_submit']; }else{ $report_submit = ""; }

	if($report_form == 'yes' || $report_submit == 'yes'){

		if($report_form == 'yes'){
			//Checks to see if site shows report_form
			
			if(isset($_POST['report_type'])){ $report_type = $_POST['report_type']; }else{ $report_type = ""; }
			if(isset($_POST['report_msg'])){ $report_msg = $_POST['report_msg']; }else{ $report_msg = ""; }

			$report_msg = stripslashes($report_msg);
			$report_msg = stripslashes($report_msg);
			$report_msg = stripslashes($report_msg);
			$report_msg = str_replace("<br />", "", $report_msg );
			
			echo "<a class='anchor' name=report></a>";
			
			#Get the Refering Page if There is one
			if(isset($_SERVER['HTTP_REFERER'])){ $report_refer = $_SERVER['HTTP_REFERER']; }else{ $report_refer = ""; } 

			#Will return the type of web browser or user agent that is being used to access the current script.
			$report_useragent = $_SERVER['HTTP_USER_AGENT']; 
			
			#The filename of the currently executing script, relative to the document root.
			$report_cfile = $_SERVER['PHP_SELF']; 
			
			#Prints the exact path and filename relative to the DOCUMENT_ROOT of your site.
			$report_uri = $_SERVER['REQUEST_URI'];
			
			#Contains the IP address of the user requesting the PHP script from the server.
			$report_ipaddy = $_SERVER['REMOTE_ADDR']; 
			
			#Returns the name of the webserver or virtual host that is processing the request. 
			#For example, if you were visiting http://www.phpfreaks.com then the result would be www.phpfreaks.com.
			$report_server = $_SERVER['SERVER_NAME']; 

			#Gets current url
			$report_pageURL = $cur_pageURL;
			
			echo "<form method=\"post\" action=\"\" onsubmit=\"submit.disabled = true; return true;\">";
			// create multi sessions
			if(isset($session_token_num)){
				$session_token_num = $session_token_num + 1;
			}else{
				$session_token_num = "1";
			}
			form_token();
			
			//Testing info
			if($debug_website == 'TRUE'){ 
				echo "<br> - DEBUG SITE ON - <BR>"; 
				echo " (UID = $userIdme) ";
				echo " (UName = $nname) "; 
				echo "<br> $report_useragent - $report_cfile - $report_uri - $report_ipaddy - $report_server - $report_pageURL <br>";
			}
			
			echo "<input type='hidden' name='report_user' value='$nname'>";
			echo "<input type='hidden' name='report_useragent' value='$report_useragent'>";
			echo "<input type='hidden' name='report_cfile' value='$report_cfile'>";
			echo "<input type='hidden' name='report_uri' value='$report_uri'>";
			echo "<input type='hidden' name='report_ipaddy' value='$report_ipaddy'>";
			echo "<input type='hidden' name='report_server' value='$report_server'>";
			echo "<input type='hidden' name='report_pageURL' value='$report_pageURL'>";
			echo "<input type='hidden' name='report_userID' value='$userIdme'>"; 
			echo "<input type='hidden' name='report_submit' value='yes'>"; 
			echo"
					<table>
					<tr><td colspan=2 valign=top class=content78>
						Please Select Report Type and Provide Report Details. <br>  Thank You For Your Help!
					</tr><tr><td valign=top class=content78>
						<strong>Select Report Type</strong>
						<br>
						<input name=\"report_type\" type=\"radio\" value=\"Abuse\" "; if($report_type == "Abuse"){echo "checked";} echo "> Abuse
						<br>
						<input name=\"report_type\" type=\"radio\" value=\"Error\" "; if($report_type == "Error"){echo "checked";} echo "> Error
						<br>
						<input name=\"report_type\" type=\"radio\" value=\"Suggestion\" "; if($report_type == "Suggestion"){echo "checked";} echo "> Suggestion
					</td><td valign=top class=content78>
						<label><strong>Report Details</strong></label><br><textarea name=\"report_msg\" cols=\"50\" rows=\"3\">$report_msg</textarea><br>
						<label title=\"Send\"><input type=\"submit\" value=\"Submit Report\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" /></label>
					</td></tr></table>
				</form>
			"; 
		}//End of show report_form

		//Check to see if report_submit is yes
		if($report_submit == 'yes'){

			if(isset($_POST['report_type'])){ $report_type = $_POST['report_type']; }else{ $report_type = ""; }
			if(isset($_POST['report_msg'])){ $report_msg = $_POST['report_msg']; }else{ $report_msg = ""; }

			$report_msg = htmlspecialchars($report_msg);
			$report_msg = strip_tags($report_msg);	
			$report_msg = addslashes($report_msg);
			$report_msg = nl2br($report_msg);
			$report_msg = ((isset($GLOBALS["___mysqli_ston"]) && is_object($GLOBALS["___mysqli_ston"])) ? mysqli_real_escape_string($GLOBALS["___mysqli_ston"], $report_msg) : ((trigger_error("[MySQLConverterToo] Fix the mysql_escape_string() call! This code does not work.", E_USER_ERROR)) ? "" : ""));
			
			//Check to see if report form is filled out.
			if(!$report_type){ 
				echo "<a class='anchor' name=report></a>";
				echo "<table><tr><td><font color=red><strong>You did not select a report type.  Please go back and select one.</strong></font>";
				echo "</td><td><form method=\"post\" action=\"#report\" onsubmit=\"submit.disabled = true; return true;\">";
				echo "<input type=\"hidden\" name=\"report_form\" value=\"yes\">"; 
				echo "<input type=\"hidden\" name=\"report_type\" value=\"$report_type\">";
				echo "<input type=\"hidden\" name=\"report_msg\" value=\"$report_msg\">"; 
				echo "<input class=\"sweet\" type=\"submit\" value=\"Click Here to Go Back\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</form></td></tr></table>";
			}else{
				if(!$report_msg){ 
					echo "<a class='anchor' name=report></a>";
					echo "<table><tr><td><font color=red><strong>You did not Provide Report Details.  Please go back and Provide Report Detials.</strong></font>";
					echo "</td><td><form method=\"post\" action=\"#report\" onsubmit=\"submit.disabled = true; return true;\">";
					echo "<input type=\"hidden\" name=\"report_form\" value=\"yes\">"; 
					echo "<input type=\"hidden\" name=\"report_type\" value=\"$report_type\">";
					echo "<input type=\"hidden\" name=\"report_msg\" value=\"$report_msg\">"; 
					echo "<input class=\"sweet\" type=\"submit\" value=\"Click Here to Go Back\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" />";
					echo "</form></td></tr></table>";
				}else{

					//Token validation function
					if(!is_valid_token()){ 

						//Token does not match
						err_message('Sorry, Tokens do not match!  Please go back and try again.');

					}else{

						if(isset($_POST['report_user'])){ $report_user = $_POST['report_user']; }else{ $report_user = ""; }
						if(isset($_POST['report_refer'])){ $report_refer = $_POST['report_refer']; }else{ $report_refer = ""; }
						if(isset($_POST['report_useragent'])){ $report_useragent = $_POST['report_useragent']; }else{ $report_useragent = ""; }
						if(isset($_POST['report_cfile'])){ $report_cfile = $_POST['report_cfile']; }else{ $report_cfile = ""; }
						if(isset($_POST['report_uri'])){ $report_uri = $_POST['report_uri']; }else{ $report_uri = ""; }
						if(isset($_POST['report_ipaddy'])){ $report_ipaddy = $_POST['report_ipaddy']; }else{ $report_ipaddy = ""; }
						if(isset($_POST['report_server'])){ $report_server = $_POST['report_server']; }else{ $report_server = ""; }
						if(isset($_POST['report_userID'])){ $report_userID = $_POST['report_userID']; }else{ $report_userID = ""; }
						if(isset($_POST['report_pageURL'])){ $report_pageURL = $_POST['report_pageURL']; }else{ $report_pageURL = ""; }
						
						//Insert error information to database
						$query = "INSERT INTO `".$db_table_prefix."report` SET 
									`report_type`='$report_type',`report_msg`='$report_msg',`report_user`='$report_user',
									`report_refer`='$report_refer',`report_useragent`='$report_useragent',`report_cfile`='$report_cfile',
									`report_uri`='$report_uri',`report_ipaddy`='$report_ipaddy',`report_server`='$report_server',
									`report_userID`='$report_userID',`report_pageURL`='$report_pageURL'
									";
							$results = mysqli_query($GLOBALS["___mysqli_ston"],  $query );
						
								// print out the results
								if( $results )
								{
									//Sends success message to session
									//Shows user success when they are redirected
									$success_msg = "You Have Successfully Reported $report_type!";
									$_SESSION['success_msg'] = $success_msg;

									if($debug_website == 'TRUE'){ 
										echo "<br> - DEBUG SITE ON - <BR>"; 
										echo( "<br><center>Error Reported!</center>" );
									}else{
										//Redirects the user back to the previous page they were on
										$redir_link_url = "";
										
										// Redirect member to their post
										header("Location: $redir_link_url");
										exit;

									}
								}else{
									die( "Trouble saving information to the database: " . ((is_object($GLOBALS["___mysqli_ston"])) ? mysqli_error($GLOBALS["___mysqli_ston"]) : (($___mysqli_res = mysqli_connect_error()) ? $___mysqli_res : false)) );
								}

					}//End token check
				}//End report_msg check
			}//End report_type check
		}

	//If no form or submit show button
	}else{
		echo "<form method=\"post\" action=\"#report\" onsubmit=\"submit.disabled = true; return true;\">";
		echo "<input type='hidden' name='report_form' value='yes'>"; 
		echo "<input class=\"sweet\" type=\"submit\" value=\"Report Abuse, Error, or Suggestion\" name=\"submit\" onClick=\"this.value = 'Please Wait....'\" />";
		echo "</form>";
	}
	echo "</td></tr></table>";
}//End of user logged in check

?>