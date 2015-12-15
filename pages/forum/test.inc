<html>
<head>
	<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
	<style>
		#wrap{
			width: 730px;
			margin: 0 auto;
		}
		.form_wrap{
			float:left;
			width: 330px;
			height: 160px;
			border: dotted 1px gray;
			padding: 10px;
		}
		.form_wrap label{
			width: 90px;
			float: left;
			margin-bottom: 10px;
		}
		.form_wrap input[type=text]{
			width: 190px;
			margin-bottom: 10px;
		}
		.form_wrap textarea{
			width: 190px;
			height: 75px;
			margin-bottom: 10px;
		}
		.preview_area{
			width: 330px;
			height: 160px;
			border: dotted 1px gray;
			float:right;
			padding: 10px;
		}
		.preview_area h3{
			color: blue;
			height: 10px;
		}
		.preview_area p{
			font-size: 14px;
			color: gray;
			height: 30px;
		}
	</style>
	<script>
		$(function(){
			
			//change title dynamically
			$( '#title' ).keyup( function(){
				var title = $( this ).val();
				$( '.preview_area h3' ).text( title );
			});
			
			//change description dynamically
			$( '#desc' ).keyup(function(){
				var desc = $( this ).val();
				$( '.preview_area p' ).text( desc );
			});
			
			//change website link dynamically
			$( '#link' ).keyup(function(){
				var desc = 'http://' + $( this ).val();
				$( '.preview_area a' ).text( desc );
				$( '.preview_area a' ).attr( 'href', desc );
			});			
		});
	</script>
</head>
<body>
	<div id="wrap">
 
		<h3 align="center">Live Preview jQuery Example by <a href="http://www.tutorialsmade.com">Tutorialsmade.com</a></h3>
 
		<div class="form_wrap">
		<form action="" method="post">
			<label>Title</label><input type="text" id="title" name="title" maxlength="25" placeholder="Enter title" />
			<label>Description</label><textarea placeholder="Description" maxlength="100" id="desc" name="desc"></textarea>
			<label>Link</label><input type="text" id="link" name="link" placeholder="Your website link" />
		</form>
		</div>
 
		<div class="preview_area">
			<h3>Your Title</h3>
			<p>Lorem Ipsum is simply dummy text of the printing and typesetting industry. </p>
			<a href="http://www.tutorialsmade.com" target="_blank">http://www.tutorialsmade.com</a>
		</div>
	</div>
</body>
</html>