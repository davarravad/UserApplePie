

		</td>
		<td width="150" align="CENTER" valign="TOP" class="main_table_right_nav">
		
		
			<?php
//Display Forum Recent Posts
				require "pages/forum/forum_recent.inc";
			?>

		
			<?php
//Display site stats and such
				require "models/total_site_stats.inc";		
			?>
		
		</td>
	</tr>
	
<?php
// Footer table setup 
		echo "<tr><td colspan=\"3\" align=\"CENTER\" valign=\"TOP\" class=\"main_tbl_footer\">";




?>	
			Web Design and Graphics by: <a href='<?php
echo "${site_url_link}"; ?>member/1' title="View DaVaRs Profile" ALT="DaVaR Profile">DaVaR</a> 
			 | <a href="<?php
echo "${site_url_link}"; ?>help" title="Help & FAQ" ALT="Help & FAQ">Help & FAQ</a>
			 | <a href="<?php
echo "${site_url_link}"; ?>disclaimer" title="Car Truck Clubs Site Disclaimer" ALT="Disclaimer">Disclaimer</a>
			 | <a href='<?php
echo "${site_url_link}"; ?>privacypolicy' title='Privacy Policy' alt='Privacy Policy'>Privacy Policy</a>
			 | <a href='<?php echo "$site_url_link_m" ?>' title='Mobile Version' alt='Mobile Version'>Mobile Version</a>
			 
			<?php
//Displays Admin Manage Site links if Admin is logged in
				if(is_admin())
				{
					echo " |  (<a href=\"${site_url_link}YummyAsPie/\">Manage Site</a>) ";
				}
			?>
			 
			<br />	<?php //require("models/sitelogs/showcurrent.inc"); ?>
			
			©2013 cartruckclubs.com. All Rights Reserved.
			<br />


		
		</td>
	</tr>
</table>

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

</body>
</html>


<?php
	//log user for site stats
	require "models/sitelogs/showcurrent.inc";
?>

