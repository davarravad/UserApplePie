<?php
//////////////////////////////////
// UserApplePie Version: 1.0.1  //
// http://www.thedavar.com      //
// UserCake Version: 2.0.2      //
// http://usercake.com          //
//////////////////////////////////

// PHP5 Implementation - uses MySQLi.
	require_once("../db-settings.inc");
	global $db_host, $db_name, $db_user, $db_pass, $db_table_prefix;
	
	$db = new mysqli($db_host, $db_user, $db_pass, $db_name);
	
	if(!$db) {
		// Show error if we cannot connect.
		echo 'ERROR: Could not connect to the database.';
	} else {
		// Is there a posted query string?
		if(isset($_POST['queryString'])) {
			$queryString = $db->real_escape_string($_POST['queryString']);
			
			// Is the string length greater than 0?
			
			if(strlen($queryString) >0) {
				// Run the query: We use LIKE '$queryString%'
				// The percentage sign is a wild-card, in my example of countries it works like this...
				// $queryString = 'Uni';
				// Returned data = 'United States, United Kindom';
				
				// YOU NEED TO ALTER THE QUERY TO MATCH YOUR DATABASE.
				// eg: SELECT yourColumnName FROM yourTable WHERE yourColumnName LIKE '$queryString%' LIMIT 10
				
				$query = $db->query("
					SELECT u.id, u.user_name, u.display_name, u.active, p.userId, p.userFirstName, p.userLastName 
					FROM ".$db_table_prefix."users u
					LEFT JOIN ".$db_table_prefix."userprofile p
					ON u.id = p.userId
					WHERE NOT u.active=0
					AND u.user_name 
					LIKE '%$queryString%'
					OR NOT u.active=0
					AND p.userFirstName
					LIKE '%$queryString%'
					OR NOT u.active=0
					AND p.userLastName
					LIKE '%$queryString%'
					GROUP BY u.id 
					LIMIT 20
				");
				if($query) {
					// While there are results loop through them - fetching an Object (i like PHP5 btw!).
					while ($result = $query ->fetch_object()) {
						// Format the results, im using <li> for the list, you can change it.
						// The onClick function fills the textbox with the result.
						
						// YOU MUST CHANGE: $result->value to $result->your_colum
	         			echo '<li onClick="fill(\''.$result->id.'\');">'.$result->display_name.'-('.$result->userFirstName.')</li>';
	         		}
				} else {
					echo 'ERROR: There was a problem with the query.';
				}
			} else {
				// Dont do anything.
			} // There is a queryString.
		} else {
			echo 'There should be no direct access to this script!';
		}
	}
?>