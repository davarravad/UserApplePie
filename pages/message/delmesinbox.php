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


if(isUserLoggedIn())
{

	if(isset($_POST['mid'])){ $mid = $_POST['mid']; }else{ $mid = ""; }
	if(isset($_POST['yes'])){ $yes = $_POST['yes']; }else{ $yes = ""; }

	if($yes == 'yes'){


		//Token validation function
		if(!is_valid_token()){ 

			//Token does not match
			err_message('Sorry, Tokens do not match!  Please go back and try again.');

		}else{
		
			$userone = $userIdme;
			//echo "$userone";
			
			$mid = $_POST['mid'];
		
			$query = "SELECT * FROM `".$db_table_prefix."inbox` WHERE `mid`='$mid' ";
		
			$result = mysqli_query($GLOBALS["___mysqli_ston"], $query)
			or die ("Couldn't ececute query.");
				
			while ($row = mysqli_fetch_array($result))
			{
				extract($row);
				//echo "Owner = $mto";
			}
		
			if($mto == $userone) {
			 
				$query = "DELETE FROM `".$db_table_prefix."inbox` WHERE `mid`='$mid' LIMIT 1"; 

				$results = mysqli_query($GLOBALS["___mysqli_ston"], $query);

				// print out the results
				if( $results )
				{
					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Deleted a Message!";
					$_SESSION['success_msg'] = $success_msg;

					//Disables auto refresh for debug stuff
					if($debug_website == 'TRUE'){ echo "<br> - DEBUG SITE ON - <BR>"; }else{
						echo "<meta HTTP-EQUIV='REFRESH' content='0; url=${site_url_link}message/?mes=inbox'>"; 
					}
				}
				else
				{
					//Code used to report mysql error
					$mysql_error_report = "TRUE";
					$sql_query = "$query";
					require "external/mysql_error_report.php";
				}
		
			}
			else {
				echo "<Br><br>The content you are trying to request is not yours!";
			}
		
//Bottom of Submit Pages	
	
		 	//End of Token Check
			}
	
		 	//Ends the token session for better security	
 			unset($_SESSION['user_token']);  
		
//End bottom of submit page	

	}
	else {
		
		
		echo "<br>Are you sure you would like to delete that?<Br>";
		//echo "<a href=='${site_url_link}?page=message&mes=delmesinbox&mid=$mid&yes=yes'>Yes?</a> / <a href='../'>No?</a>";
		
				echo "<center>
					<form method=\"post\" action=\"${site_url_link}message\" onsubmit=\"submit.disabled = true; return true;\">
						<input type=\"hidden\" name=\"mes\" value=\"delmesinbox\">
						<input type=\"hidden\" name=\"mid\" value=\"$mid\">
						<input type=\"hidden\" name=\"yes\" value=\"yes\">
				";
				
			// create multi sessions
			if(isset($session_token_num)){
				$session_token_num = $session_token_num + 1;
			}else{
				$session_token_num = "1";
			}
			form_token();

				
				echo "
						<label title=\"Send\"><input type=\"submit\" value=\"YES\" onClick=\"this.value = 'Please Wait....'\" /></label>
					</form>
				";
				echo "</center>";
				$taz_backz = "
					<form method=\"post\" action=\"${site_url_link}message\" onsubmit=\"submit.disabled = true; return true;\">
						<input type=\"hidden\" name=\"mes\" value=\"inbox\">
						<label title=\"Send\"><input type=\"submit\" value=\"NO\" onClick=\"this.value = 'Please Wait....'\" /></label>
					</form>
				";
				echo "<center>$taz_backz</center>";
				

		
	}


		}
		else {
			notlogedinmsg();
		}


?> 
