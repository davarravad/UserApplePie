<?php

//////////////////////////////////
// UserApplePie Version: 1.0.0  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

echo "
			</div>
		</div>
		<div class='right'>
";

			echo "<table width='100%'><tr><td align='CENTER' valign='TOP' class='main_table_right_nav'>";
		
				//Display Forum Recent Posts
				require "pages/forum/forum_recent.inc";

				//Display site stats and such
				require "models/total_site_stats.inc";		
		
			echo "</td></tr></table>";
			
echo "
		</div>

		

	</div>
</div>
		
		

";


		// Footer table setup 
		echo "<table width='100%'><tr><td align=\"CENTER\" valign=\"TOP\" class=\"main_tbl_footer\">";




?>	
			<a href='http://www.thedavar.net' title="View UserApplePie Website" ALT="UserApplePie">UserApplePie</a> 
			 | <a href="<?php echo "${site_url_link}"; ?>help" title="Help & FAQ" ALT="Help & FAQ">Help & FAQ</a>
			 | <a href="<?php echo "${site_url_link}"; ?>disclaimer" title="Site Disclaimer" ALT="Disclaimer">Disclaimer</a>
			 | <a href='<?php echo "${site_url_link}"; ?>privacypolicy' title='Privacy Policy' alt='Privacy Policy'>Privacy Policy</a>
			 
			 
			<?php
//Displays Admin Manage Site links if Admin is logged in
				if(is_admin())
				{
					echo " |  (<a href=\"${site_url_link}YummyAsPie/\">Manage Site</a>) ";
				}
			?>
			 
			<br />	<?php //require("models/sitelogs/showcurrent.inc"); ?>
			
			©2015 <?php echo "$websiteUrl"; ?>. All Rights Reserved.
			<br />
		</td></tr></table>

<div class='page_footer_overflow'>
<?php
//Adds space at bottom of site to keep from hiding stuff behind footer
			echo "
			<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">
			  <tr>
				<td height=\"38\">&nbsp;</td>
			  </tr>
			</table>
			"; 
?>
</div>


<?php
	//log user for site stats
	require "models/sitelogs/showcurrent.inc";



// End the body and html
echo "</body>";
echo "</html>";

?>