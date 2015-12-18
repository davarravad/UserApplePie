<center>
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


require("external/communitylinks.php");

		//Displays logged in user pannel
		if(isUserLoggedIn()){
			require("external/welcomemem.php");
		}

		if(isset($_REQUEST['mes'])){ $mes = $_REQUEST['mes']; }else{$mes = "";}

// Page title
$stc_page_title = "My Private Messages";
// Page Description
$stc_page_description = "My Private Messages";
	
// Run Header of page func
style_header_content($stc_page_title, $stc_page_description);

	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";	
		if($mes == 'inbox'){
			echo "&gt; My Inbox";	
		}
		if($mes == 'newmessage'){
			echo "&gt; Sending new message";	
		}
		if($mes == 'outbox'){
			echo "&gt; My Outbox";	
		}
	$tazib_sublinks_mes = str_replace( 'Message > ', '', $tazib_sublinks );
	echo "<br><br><center>$tazib_sublinks_mes</center>";	 
	echo "<tr><td class='content78' align=center>";
		if(isUserLoggedIn())
		{
				//START OF CONTENT
				if($mes){
					$mes1 = "pages/message/";
					$mes2 = ".php";
					$mes_file = "${mes1}${mes}${mes2}";
					
					if($mes){
						if(file_exists($mes_file)) {
							require "$mes_file";
						} else {
							echo "
								<center>
								The page <font color=red>$mes</font> does NOT exist!<br>
								<br>
								Go back or go <a href='../'>Home</a></center>
							";
							//Reporting page error
							$er_type = "Message Page Error";
							$er_location = "?mes=$mes";
							$er_msg = "?mes= error - page $taz does not exist";
							$er = "YESError";
						}
					} else {
						echo "<br><center>Please select one of the above links corresponding to what you would like to do.</center><br>";
					}
				}
				else {
						require "pages/message/inbox.php";
				}
				//END OF CONTENT
		}
		else {
			notlogedinmsg();	
		}
	echo "</td></tr></table>";
	echo "</center><br>";
	
// Run Footer of page func
style_footer_content();

?>