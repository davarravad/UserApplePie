# UserApplePie v.1.1.1
UserApplePie is a web site portal based on UserCake

Features:
- Bootstrap Responsive Design.
- Forum.
- User Profiles with Photos. (Photos Optional)
- Friends.
- Status Updates.
- Status Comments.
- Clean URL Links.
- Smart Registration with recapcha.
- Sweets feature.  Identical to Like button.
- Advanced User Account Settings.
- User Messages. Members can message each other in site with email notifications.
- Member profile comments.
- Added Security Functions.
- Admin Panel.
- And Much More!

Need Help or Want to Help with UserApplePie visit http://www.userapplepie.com/

Demo Website:
http://demo.userapplepie.com/

Copyright (c) 2015

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


Thank you for downloading UserApplePie, the simple user management package.

//--Installation.

Step #1. Before proceeding please open up models/db-settings.inc

Step #2. Create a database on your server / web hosting package.

Step #3. Fill out the connection details in db-settings.inc

Step #4. UserApplePie supports MySQLi and requires MySQL server version 4.1.3 or newer.

Step #5. Enable/Install ImageMagic (Optional)

Step #6. Make images, small, and thumb folders that are in /content/profile/ folder writeable by Web Server.

Step #7. Enable/Install Apache mod_rewrite and add the following to your sites Apache Config (global config, or vhost/directory, or .htaccess):
<pre>
	RewriteEngine On
	RewriteBase /
	RewriteRule ^([A-Za-z0-9\_\s]+)$ /index.php?page=$1 [QSA,L,NC]
	RewriteRule ^([A-Za-z0-9\_\s]+)/$ /index.php?page=$1 [QSA,L,NC]
	RewriteRule ^YummyAsPie/([A-Za-z0-9\_\s]+)/$ /index.php?page=admin/admin&adp=$1 [QSA,L,NC]
	RewriteRule ^YummyAsPie/locations/([A-Za-z0-9\_\s]+)/$ /index.php?page=admin/admin&adp2=$1 [QSA,L,NC]
	RewriteRule ^rp/([A-Za-z0-9\_\s]+)$ /index.php?rc_view=$1 [QSA,L,NC]
	RewriteRule ^rp/([A-Za-z0-9\_\s]+)/$ /index.php?rc_view=$1 [QSA,L,NC]
	RewriteRule ^member/([A-Za-z0-9\_\s]+)$ /index.php?profile=$1 [QSA,L,NC]
	RewriteRule ^member/([A-Za-z0-9\_\s]+)/$ /index.php?profile=$1 [QSA,L,NC]
	RewriteRule ^([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)$ /index.php?page=$1&pee=$2&fsp=$2 [QSA,L,NC]
	RewriteRule ^([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)/$ /index.php?page=$1&pee=$2&fsp=$2 [QSA,L,NC]
	RewriteRule ^([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)$ /index.php?page=$1&pee=$2&fsp=$2&fsid=$3 [QSA,L,NC]
	RewriteRule ^([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)/$ /index.php?page=$1&pee=$2&fsp=$2&fsid=$3 [QSA,L,NC]
	RewriteRule ^([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)$ /index.php?page=$1&pee=$2&fsp=$2&fsid=$3&fsid2=$4 [QSA,L,NC]
	RewriteRule ^([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)/([A-Za-z0-9\_\s]+)/$ /index.php?page=$1&pee=$2&fsp=$2&fsid=$3&fsid2=$4 [QSA,L,NC]
</pre>
The Above will enable your site url links to look better than http://www.website.com/index.php?page=login
The urls will be much like http://www.website.com/login/

Step #8. To use the installer visit http://yourdomain.com/install/ in your browser. UserApplePie will attempt to build the database for you. After completion
   delete the install folder.  The install script checks to make sure all requirements match UserApplePie's needs.  Also has links if not.

Step #9. Import the install/cities.sql file into your database.  
If not using default table prefix "uc_" you will need to change it after import. 
(uc_cities, uc_cities_extended)
   
- UserApplePie was tested with a Ubuntu Linux server with all the latest updates.  

-  For further documentation visit http://www.userapplepie.com/ or http://usercake.com

//--Credits for UserApplePie

UserApplePie created by: David Sargent aka DaVaR
Vers: 1.1.1
http://www.userapplepie.com/
   
//--Credits for UserCake Backbone

UserCake created by: Adam Davis
UserCake V2.0 designed by: Jonathan Cassels

---------------------------------------------------------------

Vers: 2.0.2
http://usercake.com
http://usercake.com/LICENCE.txt

---------------------------------------------------------------


Error Notes
NOTE:
If you get the following error when you open the forum, you will need to instal mysqlnd:
 Fatal error: Call to undefined method mysqli_result::fetch_all() in forum_admin_funcs.php on line 72
You can find information on how to install here: http://www.php.net/manual/en/mysqlnd.install.php
