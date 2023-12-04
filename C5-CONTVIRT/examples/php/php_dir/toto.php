<h1> Je suis pressé</h1>


<form action="./toto.php" method="get">

<input type="text" name="login">
<input type="password" name="pwd">

<input type="submit">


<?php

if($_GET["login"] && $_GET["pwd"])
{
	echo "Salut ". $_GET["login"];
}

?>

</form>
