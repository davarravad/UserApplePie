<?php

if(isUserLoggedIn())
{


				
			global $mysqli, $site_url_link, $site_forum_title, $userIdme, $db_table_prefix;
			
			echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='forum_content' valign='top' width='100'>";
				echo "<table width='100%' border='0' cellpadding='0' cellspacing='0'><tr>";
				echo "<td align='center'>";
					// Show user main pic
					global $site_dir;
					$ID02 = $userIdme;
					require('pages/forum/userimage_small.inc');
					$get_user_name_323 = get_user_name_2($userIdme);
					echo "<br><a href='${site_url_link}member/$userIdme/'>$get_user_name_323</a> ";

					//Show user's membership status
					echo "<br>";
					get_up_info_mem_status($ID02);
					
					echo "<br>";
				echo "</td></tr></table>";
			echo "</td><td class='forum_content' valign='top'>";
			
			echo "<form enctype=\"multipart/form-data\" action=\"${site_url_link}${site_forum_title}/save_topic/${f_p_id_cat}/\" method=\"POST\" onsubmit=\"submitmystat.disabled = true; return true;\" >";
				
				// create multi sessions
				if(isset($session_token_num)){
					$session_token_num = $session_token_num + 1;
				}else{
					$session_token_num = "1";
				}
				form_token();
				
				//echo "<br>-($usr_email_subcribe)-<br>";

				//Checks if user is subscribed to email or not
				//Then checks or un-checks box
				if($usr_email_subcribe == "NO"){
					$usr_subsc_check = "";
				}else{
					$usr_subsc_check = "checked=checked";
				}
				
				echo "<textarea style='width:100%;height:100px;font-family:verdana;font-size:12px;border: 1px solid #333' name='forum_content' id='forum_content'></textarea>";
				echo "<br>";
				echo "<input type=\"hidden\" name=\"forum_id\" value=\"$f_p_id_cat\" />";
				echo "<input type=\"hidden\" name=\"forum_post_id\" value=\"$f_p_id\" />";
				echo "<input type=\"hidden\" name=\"insert_reply_topic\" value=\"TRUE\" />";
				echo "<br><center>";
				echo "<input type=\"checkbox\" name=\"subcribe_email\" value=\"YES\" $usr_subsc_check> Subscribe to E-Mail Notifications for this Topic<br>";
				echo "<input type=\"submit\" value=\"Submit Quick Reply\" name=\"Quick Reply\" class=\"sweet\" onClick=\"this.value = 'Please Wait....'\" />";
				echo "</center>";
				
			echo "</form>";

			echo "
				<center><strong>Your Reply Preview</strong></center>
				<pre class='forum'>
				<DIV id=preview class=scroll style=\"BORDER-RIGHT: #c0c0c0 1px solid; PADDING-RIGHT: 3px;
				BORDER-TOP: #c0c0c0 1px solid; PADDING-LEFT: 3px; PADDING-BOTTOM: 3px; BORDER-LEFT: #c0c0c0 1px solid; WIDTH: 98%;
				PADDING-TOP: 3px; BORDER-BOTTOM: #c0c0c0 1px solid; HEIGHT: 100px; overflow:scroll\"></DIV>
				</pre>
			";
			
			echo "</td></tr></table>";

?>

	<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.3.2/jquery.min.js" type="text/javascript"></script>
	<script src='/models/jquery.bbcode.js' type='text/javascript'></script>
	<script type=text/javascript>
	  $(document).ready(function(){
		$("#forum_content").bbcode({tag_bold:true,tag_italic:true,tag_underline:true,tag_link:true,tag_image:true,button_image:true});
		process();
	  });
	 
	  var bbcode="";
	  function process()
	  {
		if (bbcode != $("#forum_content").val())
		  {
			bbcode = $("#forum_content").val();
			$.get('/models/bbParser.php',
			{
			  bbcode: bbcode
			},
			function(txt){
			  $("#preview").html(txt);
			})
		  }
		setTimeout("process()", 2000);
	  }
	</script>


<?php

} // End of log in check

?>