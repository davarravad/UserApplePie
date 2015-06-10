<?
	unset($user_name);

	// retrieve the row from the database
	$query = "SELECT user_name FROM `".$db_table_prefix."users` WHERE `id`='$mto'";
   
	$result = mysqli_query($GLOBALS["___mysqli_ston"],  $query );

	// print out the results
	if( $result && $contact = mysqli_fetch_object( $result ) )
	{
		// print out the info
		$user_name = $contact -> user_name;
	}

?>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
<script type="text/javascript">
	function lookup(inputString) {
		if(inputString.length == 0) {
			// Hide the suggestion box.
			$('#suggestions').hide();
		} else {
			$.post("/models/autoComplete/members.php", {queryString: ""+inputString+""}, function(data){
				if(data.length >0) {
					$('#suggestions').show();
					$('#autoSuggestionsList').html(data);
				}
			});
		}
	} // lookup
	
	function fill(thisValue) {
		$('#inputString').val(thisValue);
		setTimeout("$('#suggestions').hide();", 200);
	}
</script>


			<div>
			<label>
				<input autocomplete="off" name="mto" type="text" size="30" id="inputString" value="<? if(isset($user_name)){echo "$user_name";} ?>" onkeyup="lookup(this.value);" onblur="fill();" />
			</label>
			</div>
			
			<div class="suggestionsBox" id="suggestions" style="display: none;">
				<img src="/models/autoComplete/upArrow.png" style="position: relative; top: -12px; left: 30px;" alt="upArrow" />
				<center><font color=#090><h3>Please Select User<br> From This Drop Down<br></h3></font></center>
				<div class="suggestionList" id="autoSuggestionsList">
					&nbsp;
				</div>
			</div>