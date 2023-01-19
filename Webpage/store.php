<?php
    session_start();
    $item = "";
    if(isset($_POST["item"]))
    {
        $item = $_POST["item"];
    }
    $price = "";
    if(isset($_POST["price"]))
    {
        $price = $_POST["price"];
    }
    $quantity = "";
    if(isset($_POST["quantity"]))
    {
        $quantity = $_POST["quantity"];
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Store</title>
    <link rel="stylesheet" href="storestyle.css"> 
</head>
<body>
    <h1 id="page_title">Welcome to the Store!</h1>
    <form method="POST" action="<?php echo $_SERVER['PHP_SELF']; ?>">
        <div class="item">
            <div id="iphone">
                <img src="iphone.jpeg"><br>
                <input type="hidden" name="item" value="iPhone">iPhone<br>
                <input type="hidden" name="price" value="999.99">$999.99<br>
                <input type="number" id="quantity" name="quantity" value="0" placeholder="How Many?"><br>
                <button type="submit" class="button" name="Click" id="add2Cart">Add to Cart</button>
            </div>
        </div>
    </form>
    <?php
        require_once("config.php");
        if(isset($_POST["Click"]))
        {
            
            $update_table = "INSERT INTO Orders(ITEM, Price, Quantity, discount) VALUES('$item', '$price', '$quantity', 0);";
            $pdo->exec($update_table);
            $find_id = "SELECT ID FROM Orders ORDER BY id DESC LIMIT 1;";
            $temp = $pdo->query($find_id);
            $row = $temp->fetch();
            $id = $row['ID'];
            $_SESSION['id'] = $id;
            echo "<script> window.open('http://localhost:8888/Project/checkout.php','_self');</script>";
        }
    ?>
</body>
</html>