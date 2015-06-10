 $(document).ready(function() {
 
$('#passwordInput, #confirmPasswordInput').on('keyup', function(e) {
 
if($('#passwordInput').val() != '' && $('#confirmPasswordInput').val() != '' && $('#passwordInput').val() != $('#confirmPasswordInput').val())
{
$('#passwordStrength').removeClass().addClass('alert alert-error').html('Passwords do not match!');
$('#pbar').removeClass().addClass('alert alert-error').width('25%');
$('#pbar').removeClass().addClass('alert alert-error').css('background-color', 'red');
 
return false;
}
 
// Must have capital letter, numbers and lowercase letters
var strongRegex = new RegExp("^(?=.{8,})(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*\\W).*$", "g");
 
// Must have either capitals and lowercase letters or lowercase and numbers
var mediumRegex = new RegExp("^(?=.{7,})(((?=.*[A-Z])(?=.*[a-z]))|((?=.*[A-Z])(?=.*[0-9]))|((?=.*[a-z])(?=.*[0-9]))).*$", "g");
 
// Must be at least 8 characters long
var okRegex = new RegExp("(?=.{8,}).*", "g");
 
if (okRegex.test($(this).val()) === false) {
// If ok regex doesn't match the password
$('#passwordStrength').removeClass().addClass('alert alert-error').html('Password must be at least 8 characters long.');
$('#pbar').removeClass().addClass('alert alert-error').width('25%');
$('#pbar').removeClass().addClass('alert alert-error').css('background-color', 'red');

} else if (strongRegex.test($(this).val())) {
// If reg ex matches strong password
$('#passwordStrength').removeClass().addClass('alert alert-success').html('Strong Password!');
$('#pbar').removeClass().addClass('alert alert-error').width('100%');
$('#pbar').removeClass().addClass('alert alert-error').css('background-color', 'green');
} else if (mediumRegex.test($(this).val())) {
// If medium password matches the reg ex
$('#passwordStrength').removeClass().addClass('alert alert-info').html('Good Password!');
$('#pbar').removeClass().addClass('alert alert-error').width('75%');
$('#pbar').removeClass().addClass('alert alert-error').css('background-color', 'lightgreen');
} else {
// If password is ok
$('#passwordStrength').removeClass().addClass('alert alert-error').html('Weak Password!');
$('#pbar').removeClass().addClass('alert alert-error').width('50%');
$('#pbar').removeClass().addClass('alert alert-error').css('background-color', 'yellow');
}
return true;
});
 
});