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


global $websiteUrl, $websiteName;

echo "<center>";
	echo "<table width='100%' border='0' cellspacing='0' cellpadding='0'><tr><td class='hr2'>";
    ###Page Title###
	//echo "<title>".$websiteName." Privacy Policy</title>";
	echo "<meta name=\"description\" content=\"".$websiteName." Web Site Member Privacy Policy.\">";
	echo "Privacy Policy"; 

	echo "</td></tr>";
	echo "<tr><td class='content78'>";

	echo "

This Privacy Policy governs the manner in which ".$websiteName." collects, uses, maintains and discloses information collected from users (each, a User) of the <a href='".$websiteUrl."'>".$websiteUrl."</a> website (Site). This privacy policy applies to the Site and all products and services offered by ".$websiteName.".<br><br>

<b>Personal identification information</b><br><br>

We may collect personal identification information from Users in a variety of ways, including, but not limited to, when Users visit our site, register on the site, fill out a form, and in connection with other activities, services, features or resources we make available on our Site. Users may be asked for, as appropriate, name, email address. Users may, however, visit our Site anonymously. We will collect personal identification information from Users only if they voluntarily submit such information to us. Users can always refuse to supply personally identification information, except that it may prevent them from engaging in certain Site related activities.<br><br>

<b>Non-personal identification information</b><br><br>

We may collect non-personal identification information about Users whenever they interact with our Site. Non-personal identification information may include the browser name, the type of computer and technical information about Users means of connection to our Site, such as the operating system and the Internet service providers utilized and other similar information.<br><br>

<b>Web browser cookies</b><br><br>

Our Site may use cookies to enhance User experience. User's web browser places cookies on their hard drive for record-keeping purposes and sometimes to track information about them. User may choose to set their web browser to refuse cookies, or to alert you when cookies are being sent. If they do so, note that some parts of the Site may not function properly.<br><br>

<b>How we use collected information</b><br><br>

".$websiteName." may collect and use Users personal information for the following purposes:<br>
<ul>
<li><i>- To improve customer service</i><br>
	Information you provide helps us respond to your customer service requests and support needs more efficiently.</li>
<li><i>- To personalize user experience</i><br>
	We may use information in the aggregate to understand how our Users as a group use the services and resources provided on our Site.</li>
<li><i>- To improve our Site</i><br>
	We may use feedback you provide to improve our products and services.</li>
<li><i>- To run a promotion, contest, survey or other Site feature</i><br>
	To send Users information they agreed to receive about topics we think will be of interest to them.</li>
<li><i>- To send periodic emails</i><br>
We may use the email address to respond to their inquiries, questions, and/or other requests. </li>
</ul>
<b>How we protect your information</b><br><br>

We adopt appropriate data collection, storage and processing practices and security measures to protect against unauthorized access, alteration, disclosure or destruction of your personal information, username, password, transaction information and data stored on our Site.<br><br>

<b>Sharing your personal information</b><br><br>

We do not sell, trade, or rent Users personal identification information to others. We may share generic aggregated demographic information not linked to any personal identification information regarding visitors and users with our business partners, trusted affiliates and advertisers for the purposes outlined above.<br><br>

<b>Third party websites</b><br><br>

Users may find advertising or other content on our Site that link to the sites and services of our partners, suppliers, advertisers, sponsors, licensors and other third parties. We do not control the content or links that appear on these sites and are not responsible for the practices employed by websites linked to or from our Site. In addition, these sites or services, including their content and links, may be constantly changing. These sites and services may have their own privacy policies and customer service policies. Browsing and interaction on any other website, including websites which have a link to our Site, is subject to that website's own terms and policies.<br><br>

<b>Google Adsense</b><br><br>

Some of the ads may be served by Google. Google's use of the DART cookie enables it to serve ads to Users based on their visit to our Site and other sites on the Internet. DART uses (non personally identifiable information) and does NOT track personal information about you, such as your name, email address, physical address, etc. You may opt out of the use of the DART cookie by visiting the Google ad and content network privacy policy at <a href='http://www.google.com/privacy_ads.html'>http://www.google.com/privacy_ads.html</a><br><br>

<b>Changes to this privacy policy</b><br><br>

".$websiteName." has the discretion to update this privacy policy at any time. When we do, we will revise the updated date at the bottom of this page. We encourage Users to frequently check this page for any changes to stay informed about how we are helping to protect the personal information we collect. You acknowledge and agree that it is your responsibility to review this privacy policy periodically and become aware of modifications.<br><br>

<b>Your acceptance of these terms</b><br><br>

By using this Site, you signify your acceptance of this policy. If you do not agree to this policy, please do not use our Site. Your continued use of the Site following the posting of changes to this policy will be deemed your acceptance of those changes.<br><br>

<b>Contacting us</b><br><br>

If you have any questions about this Privacy Policy, the practices of this site, or your dealings with this site, please contact us at:<br>
<a href='".$websiteUrl."'>".$websiteName."</a><br>
<a href='".$websiteUrl."'>".$websiteUrl."</a><br>
<br>
This document was last updated on July 03, 2015<br><br>

<div style='font-size:10px;color:gray;'>Privacy policy created by <a style='font-size:10px;color:gray;text-decoration:none;cursor:default;' href='http://www.generateprivacypolicy.com' target='_blank'>Generate Privacy Policy</a></div>

";

	echo "</td></tr></table>";
	echo "</center>";

?>