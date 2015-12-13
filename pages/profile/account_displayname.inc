<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

	// This script allows user to change their display name.
	// Also checks to see if display name is already taken.

	// Check to make sure user is logged in
	//Prevent the user visiting the logged in page if he is not logged in
	if(!isUserLoggedIn()) { header("Location: /login/"); die(); }
			
		// Show Links for account settings
		account_settings_links();

		// Get Current user's info
		$user_id = $userIdme;
		$user_displayname = get_up_info_mem_disp_name($user_id);
		
		// Test information
		//echo " DisplayNameTest(ID=$user_id-=-DN=$user_displayname) ";

		echo "<strong>Your Display Name Update Form</strong><br>";
		
		// Check to see if user wants to update their displayname
		if(!empty($_POST))
		{
		
			//Token validation function
			if(!is_valid_token()){ 
				//Token does not match
				err_message('Sorry, Tokens do not match!  Please go back and try again.');
				die;
			}
		
			$errors = array();
			$successes = array();
			$user_displayname_update = trim($_POST["user_displayname_update"]);

			// Checks to see if displayname is formatted ok
			if(minMaxRange(5,25,$user_displayname_update))
			{
				$errors[] = lang("ACCOUNT_DISPLAY_CHAR_LIMIT",array(5,25));
			}
			if(!preg_match("/^[a-zA-Z\p{Cyrillic}0-9\s\-\_]+$/u", $user_displayname_update)){
				$errors[] = lang("ACCOUNT_DISPLAY_INVALID_CHARACTERS");
			}	

			// Check to see if display name is already in use
				global $mysqli, $site_url_link, $site_forum_title;

				$query = "SELECT * FROM ".$db_table_prefix."users WHERE `display_name`='$user_displayname_update' ";
				
				if ($result = $mysqli->query("$query")) {

					/* determine number of rows result set */
					$row_cnt = $result->num_rows;

					/* close result set */
					$result->close();
					
				}

				// Let user know if the display name is already taken or not
				if($row_cnt != "0"){
					$errors[] = lang("ACCOUNT_DISPLAYNAME_IN_USE",array($user_displayname_update));
				}
				
				// If no errors lets update this user's display name in database
				if(count($errors) == 0) {
					$stmt = $mysqli->prepare("UPDATE ".$db_table_prefix."users SET display_name=? WHERE id=? LIMIT 1");
					$stmt->bind_param("si", $user_displayname_update, $user_id);
					$stmt->execute();
					
					echo $stmt->error;
					
					$stmt->close();	
					$redir_link_884 = "${site_url_link}editprofilemain/account_displayname/";

					//Sends success message to session
					//Shows user success when they are redirected
					$success_msg = "You Have Successfully Updated Your Display Name!";
					$_SESSION['success_msg'] = $success_msg;
					$_SESSION['success_msg2'] = $success_msg;
					
					// Redirect member to their post
					header("Location: $redir_link_884");
					exit;
				}
				
		} // End empty post check
	
				if(isset($_SESSION['success_msg2'])){
					echo "<strong>".$_SESSION['success_msg2']."</strong>";
					unset($_SESSION['success_msg2']);
				}
				
echo "<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
?>


<script type="text/javascript">
$(document).ready(function()
{    
 $("#user_displayname_update").keyup(function()
 {  
  var name = $(this).val(); 
  
  if(name.length > 4)
  {  
   $("#resultdn").html('');
   
   /*$.post("username-check.php", $("#reg-form").serialize())
    .done(function(data){
    $("#result").html(data);
   });*/
   
   $.ajax({
    
    type : 'POST',
    url  : '/pages/user_display_name_check.php',
    data : $(this).serialize(),
    success : function(data)
        {
              /*$("#resultun").html(data);*/
			if(data == 'OK')
			{
			   $("#resultdn").html("<i class='glyphicon glyphicon-ok text-success'></i>");
			   $("#resultdn2").html("");	
			}
			if(data == 'CHAR')
			{
			   $("#resultdn").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultdn2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>Display Name Invalid.</div>");	
			}
			if(data == 'INUSE')
			{
			   $("#resultdn").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultdn2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>Display Name is already in use.</div>");	
			}
			if(data == 'SAME')
			{
			   $("#resultdn").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
			   $("#resultdn2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>This is already your Display Name.</div>");	
			}
        }
    });
    return false;
   
  }
  else
  {
   $("#resultdn").html("<i class='glyphicon glyphicon-remove text-danger'></i>");
   $("#resultdn2").html("<div class='alert alert-danger alert-dismissible' role='alert'><button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>Display Name must be at least <strong>5</strong> characters.</div>");
  }
 });
 
});
</script>

<?php
				
				echo resultBlock($errors,$successes);
				
				echo "

				<form name='updateAccount' action='/editprofilemain/account_displayname/' method='post'>
				<br>
				<label>Your Current Display Name:</label>
				<div class='input-group' style='width: 80%; margin-bottom: 5px'>
					<span class='input-group-addon'><i class='glyphicon glyphicon-user'></i></span>
					<input id='user_displayname_update' type='text' name='user_displayname_update' value='$user_displayname' class='form-control' placeholder='Display Name' aria-describedby='basic-addon1' />
					<span id='resultdn' class='input-group-addon'></span>
				</div>
				";
				
					// Form token. Place within from tag
					// create multi sessions
					if(isset($session_token_num)){
						$session_token_num = $session_token_num + 1;
					}else{
						$session_token_num = "1";
					}
					form_token();
					
				echo "<span id='resultdn2' class='label'></span>
				
				
				<input type='submit' value='Update DisplayName' class='btn btn-success btn-sm' />
				
				</form>

				";
	
	
	
?>