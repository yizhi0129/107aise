<html>

<body>

<?php

$redis = new Redis();
$redis->connect('leredis', 6379);


if( $_POST["login"] && $_POST["password"]) {

	$hash = md5($_POST["password"]); 
	$redis->hset("users", $_POST["login"], $hash);

	echo "Adding ". $_POST["login"] . " md5 " . $hash;
}




?>

<form action="index.php" method="post">
	<label for="login">Login :</label>
	<input type="text" name="login">
	<label for="Password">Password :</label>
	<input type="password" name="password">
	<input type="submit" value="Register">
</form>

</html>
