<?php 
    $db_user = 'root';
    $db_password = 'root';
    $conn_string = "mysql:host=localhost; dbname=client";
    $pdo = new PDO($conn_string, $db_user,$db_password );
    $sql_create_order_table = "CREATE TABLE IF NOT EXISTS Orders(ID int NOT NULL AUTO_INCREMENT, ITEM varchar(255), Price varchar(255), Quantity varchar(255), ShippingMethod varchar(255), discount varchar(255), PRIMARY KEY(ID))";
    $sql_create_information_table = "CREATE TABLE IF NOT EXISTS Information(order_id int, FirstName varchar(255), LastName varchar(255), phoneNumber varchar(255), Email varchar(255), Address varchar(255), City varchar(255), State varchar(255), Zip varchar(255), CardNumber varchar(255), FOREIGN KEY (order_id) REFERENCES Orders(ID));";
    $sql_create_discount_table = "CREATE TABLE IF NOT EXISTS discount_code(code varchar(255), value varchar(255))";
    $sql_add_code_1 = "REPLACE INTO discount_code SET code = '10OFF', value = '10';";
    $sql_add_code_2 = "REPLACE INTO discount_code SET code = 'WINTERTIME', value = '50';";
    $sql_add_code_3 = "REPLACE INTO discount_code SET code = 'YELLOW', value = '30';";
    $pdo->exec($sql_create_order_table);
    $pdo->exec($sql_create_information_table);
    $pdo->exec($sql_create_discount_table);
    $pdo->exec($sql_add_code_1);
    $pdo->exec($sql_add_code_2);
    $pdo->exec($sql_add_code_3);
    $pdo->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
    //echo "Successful to Insert the data into database";
?>