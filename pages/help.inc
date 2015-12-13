<?php
//////////////////////////////////
// UserApplePie Version: 1.1.0  //
// http://www.userapplepie.com  //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////


	echo "<meta name=\"description\" content=\"".$websiteName." Help and FAQ.\">";

	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0' align='center'><tr><td class='hr2'>";
	echo $websiteName." Help and FAQ"; 
	echo "</td></tr>";

echo "<tr><td class='content78'>";

?>
<div align="left"><strong>How do I login to the web site?</strong><br>
  Click &#8220;Login&#8221; at the top of the site to enter your username and password then 
  select &#8220;Login&#8221;.<br>
  <br>
  <strong>How do I sign up for the site?</strong><br>
  Select the <a href="<?php
echo "${site_url_link}"; ?>register/">Register</a> link at the top of the 
  site, then fill out your information. Make sure you use a valid working e-mail address.</div>

<p align="left"><strong>I lost/forgot my password, how do I change/get a new one?</strong><br>
  If you have forgotten or lost your password click <a href="<?php
echo "${site_url_link}"; ?>login/">Login</a> then click &#8220;Forgot Password?&#8221; or 
  <a href="<?php
echo "${site_url_link}"; ?>reminder/">Click Here</a>. Enter your username and select &#8220;Fetch Password&#8221;.  Your password
  will be changed and e-mailed to you.  Once you get your new password login to the site and make sure to change 
  your password.</p>

<?php
if(isUserLoggedIn()){
?>
  
<p align="left"><strong>How do I view all of the members of <?php echo "$websiteName"; ?>?</strong><br>
  Select <a href="<?php
echo "${site_url_link}"; ?>community/">Community</a> then select <a href="<?php
echo "${site_url_link}"; ?>members/">Members</a> 
  link at the top of the site while logged in. </p>

<p align="left"><strong>How do I check my messages from other members?</strong><br>
  Select <a href="<?php
echo "${site_url_link}"; ?>community/">Community</a> then select <a href="<?php
echo "${site_url_link}"; ?>message/">My Messages</a> link at 
  the top of the site while logged in. You can then open messages sent to you 
  from other members. You may also reply and delete your messages within the
  <a href="<?php
echo "${site_url_link}"; ?>message/?mes=inbox">Inbox</a>. 
</p>
<p align="left"><strong>How do I send messages to other members?</strong><br>
  Select <a href="<?php
echo "${site_url_link}"; ?>community/">Community</a> then select <a href="<?php
echo "${site_url_link}"; ?>message/">My Messages</a> at the top 
  of the site while logged in. Then select the <a href="<?php
echo "${site_url_link}"; ?>message/?mes=newmessage">Create 
  New Message</a> link within the message center. Select the user you would like 
  to send a message to then type your message and send it. </p>

<p align="left"><strong>How do I check messages that I have sent? </strong><br>
  Select <a href="<?php
echo "${site_url_link}"; ?>community/">Community</a> then select <a href="<?php
echo "${site_url_link}"; ?>message/">My Messages</a>
  at the top of 
  the site while logged in. Then select <a href="<?php
echo "${site_url_link}"; ?>message/?mes=outbox">Outbox</a> 
  and you can view or delete your sent messages.</p>

<p align="left"><strong>How do I change my password?</strong><br>
  Select <a href="<?php
echo "${site_url_link}"; ?>editprofilemain/">Edit Profile</a> then select
  <a href="<?php
echo "${site_url_link}"; ?>editprofilemain/account/">Account Settings</a> at the top of the 
  site while logged in. Then type your new password in the Password Changer form.</p>

<p align="left">
  <strong>How do I upload images to my profile?</strong><br>
  Select <a href="<?php
echo "${site_url_link}"; ?>editprofilemain/">Edit Profile</a> at the top 
  of the site while logged in. Select <a href="<?php
echo "${site_url_link}"; ?>editprofilemain/editimages/">Edit Images</a>
  and select <a href="<?php
echo "${site_url_link}"; ?>editprofilemain/picsubmit/">Upload 
  Image</a> in the profile editor section. You can then browse your computer for 
  the image you would like to upload and select it. Then select the upload button 
  to submit the image to your profile.</p>

<p align="left"><strong>How do I edit or delete the images within my profile?</strong><br>
  Select the <a href="<?php
echo "${site_url_link}"; ?>editprofilemain/">Edit Profile</a> link at 
  the top of the site while logged in. Then select the <a href="<?php
echo "${site_url_link}"; ?>editprofilemain/editimages/">Edit 
  Images</a> link within the profile editor section of the site. You can then 
  edit and delete the images you have already uploaded to your profile.<br>
  <br>
  More help and faq on <a href='<?php echo "$site_url_link"; ?>Forum/'>Site Forum</a>...</p>
<?php
}
	echo "</td></tr></table>";
	echo "</center><br><br>";

?>
