<?php
    require_once("config.php");
    if(isset($_GET["fname"]))
    {
        $fname = $_GET["fname"];
    }
    if(isset($_GET["lname"]))
    {
        $lname = $_GET["lname"];
    }
    if(isset($_GET["phonenumber"]))
    {
        $phonenumber = $_GET["phonenumber"];
    }
    if(isset($_GET["email"]))
    {
        $email = $_GET["email"];
    }
    if(isset($_GET["street"]))
    {
        $street = $_GET["street"];
    }
    if(isset($_GET["city"]))
    {
        $city = $_GET["city"];
    }
    if(isset($_GET["state"]))
    {
        $state = $_GET["state"];
    }
    if(isset($_GET["zip"]))
    {
        $zip = $_GET["zip"];
    }
    $update_table = "INSERT INTO Information(FirstName, LastName, Email, Address, City, State, Zip) VALUES($fname, $lname, $email, $street, $city, $state, $zip);";
    $pdo->exec(update_table);
    echo 'Success: Saved information into Database';
    echo '<br>';

?>