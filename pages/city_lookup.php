<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
<script type="text/javascript">
	function lookup(inputString) {
		if(inputString.length == 0) {
			// Hide the suggestion box.
			$('#suggestions').hide();
		} else {
			$.post("./external/autoComplete/rpc.php", {queryString: ""+inputString+""}, function(data){
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
				<input autocomplete="off" name="userCity" type="text" size="20" id="inputString" value="<?php
echo "$userCity"; ?>" onkeyup="lookup(this.value);" onblur="fill();" />
			</label>
			</div>
			
			<div class="suggestionsBox" id="suggestions" style="display: none;">
				<img src="./external/autoComplete/upArrow.png" style="position: relative; top: -12px; left: 30px;" alt="upArrow" />
				<center><font color=#090><h3>Please Select City, State<br> From This Drop Down<br></h3></font></center>
				<div class="suggestionList" id="autoSuggestionsList">
					&nbsp;
				</div>
			</div>