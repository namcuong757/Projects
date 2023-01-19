<?php
    session_start();
    require_once("config.php");
    $id = $_SESSION['id'];
    $sql_select = "SELECT * FROM Orders WHERE ID='$id';";
    $temp = $pdo->query($sql_select);
    $row = $temp->fetch();
    if($row['ITEM'] != false)
    {
        $item = $row['ITEM'];
    }
    if($row['Price'] != false)
    {
        $price = $row['Price'];
    }
    if($row['Quantity'] != false)
    {
        $quantity = $row['Quantity'];
    }
    if($row['discount'] != false)
    {
        $discount = $row['discount'];
    }
    $fname = "";
    if(isset($_GET["fname"]))
    {
        $fname = $_GET["fname"];
    }
    $lname = "";
    if(isset($_GET["lname"]))
    {
        $lname = $_GET["lname"];
    }
    $phonenumber = "";
    if(isset($_GET["phonenumber"]))
    {
        $phonenumber = $_GET["phonenumber"];
    }
    $email = "";   
    if(isset($_GET["email"]))
    {
        $email = $_GET["email"];
    }
    $street = "";
    if(isset($_GET["street"]))
    {
        $street = $_GET["street"];
    }
    $city = "";
    if(isset($_GET["city"]))
    {
        $city = $_GET["city"];
    }
    $state = "";
    if(isset($_GET["state"]))
    {
        $state = $_GET["state"];
    }
    $zip = "";
    if(isset($_GET["zip"]))
    {
        $zip = $_GET["zip"];
    }
    $discount = "0";
    $discount_input = "";
    if(isset($_GET["discount_code"]))
    {
        $discount_input = $_GET["discount_code"];
    }
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Checkout</title>
    <link rel="stylesheet" href="style.css"> 
</head>
<body>

    <div class="left_split">
        <h1 id="page_title">Checkout</h1>

        <div class="input_section">
            <h3>Contact Information</h3>
            
            <form action="" method="GET"> 
                <input type="text" id="fname" name="fname" placeholder="First Name">
                <input type="text" id="lname" name="lname" placeholder="Last Name"><br>

                <input type="text" id="phonenumber" name="phonenumber" placeholder="Phone">
                <input type="text" id="email" name="email" placeholder="Email">
                
                <h3>Shipping Address</h3>
                <input type="text" id="street" name="street" placeholder="Address" style="width: 5in;">
                <input type="text" id="city" name="city" placeholder="City">
                <input type="text" id="state" name="state" placeholder="State"><br>
                <input type="text" id="zip" name="zip" placeholder="Zip code"><br>

                <button type="submit" class="button" name="go_to_ship" style="margin-left: 3in" id="submitBtn"> Continue to Shipping</button>

            </form>
        </div>
    </div>

    <div class="right_split">
        <br><br>
        <div class="summary_section">
            <div class="item_table">
                <table>
                    <tr>
                        <th>Item</th>
                        <th>Quantity</th>
                        <th>Price</th>
                    </tr>

                    <tr>
                        <td>
                            <?php   
                                echo $item;
                            ?>                        
                        </td>
                        <td>
                             <?php
                                echo $quantity;

                            ?>
                        </td>
                        <td>
                            <?php
                                echo $price;

                            ?>
                        </td>
                    </tr>
                </table>
                <br>
            </div>
        </div>

        <div class="summary_section">
            <form method="GET" action="<?php echo $_SERVER['PHP_SELF']; ?>">
            <div class="summary_item"><input class="summary_item" type="text" name="discount_code" placeholder="Discount Code">
                <input type="submit" class="button" name="discount" style="margin-left: 0px;" value="Apply Discount"></div><br>
            </form>
            <form method="GET" action="<?php echo $_SERVER['PHP_SELF']; ?>">
                <input type="submit" class="button" name="update" style="margin-left: 0px;" value="Update Cart">
            </form>
        </div>
        <p id="discount_price"></p>
        <p id="payment_total_text">SUBTOTAL: $<?php echo htmlspecialchars($price*$quantity)?></p>
    </div>

<?php 

    
    require_once("config.php");
    if(isset($_GET["update"]))
    {
        echo "<script> window.open('http://localhost:8888/Project/store.php','_self');</script>";
        $delete_sql = "DELETE FROM Orders WHERE ID=$id";
        $pdo->exec($delete_sql);
    }
    if(isset($_GET["discount"]))
    {
        if($discount_input != "")
        {
            $discount_code_query = "SELECT value FROM discount_code WHERE code='$discount_input';";
            $discount_code_return = $pdo->query($discount_code_query);
            $code = $discount_code_return->fetch();
            $discount_value = "";
            $discount_value = $code['value'] ??= '0';
            if($discount_value != "" ||$discount_value != "0")
            {
                $new_price = (float)$price * $quantity - (int)$discount_value;
                $price = sprintf("%.2f", $new_price);
                $update_table_discount = "UPDATE Orders SET discount='$discount_value' WHERE ID='$id';";
                $pdo->exec($update_table_discount);
                $_SESSION['discount'] = (int)$discount_value;
                echo "<script>document.getElementById('discount_price').textContent='DISCOUNT: $$discount_value'</script>";
                echo "<script>document.getElementById('payment_total_text').textContent='SUBTOTAL: $$new_price'</script>";
            }
            else
            {
                $discount = "0";
            }
        }
        else
        {
            $discount = "0";
        }
    }
    if(isset($_GET["go_to_ship"]))
    {
        if($fname != "" && $lname != "" && $phonenumber != "" && $email != "" && $street != "" && $city != "" && $state != "" && $zip != "")
        {
            $update1_table = "INSERT INTO Information(order_id, FirstName, LastName, phoneNumber, Email, Address, City, State, Zip) VALUES('$id','$fname','$lname','$phonenumber','$email','$street', '$city','$state','$zip');";
            $pdo->exec($update1_table);
            echo "<script> window.open('http://localhost:8888/Project/shipping.php','_self');</script>";
        }
        else
        {
            echo '<script>alert("You have to input all the field")</script>';
            echo "<script> window.open('http://localhost:8888/Project/checkout.php','_self');</script>";
        }
    }
?>

</body>
</html>