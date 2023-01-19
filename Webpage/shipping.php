<?php
    session_start();
    $id = $_SESSION['id'];
    require_once("config.php");
    $sql_select_order = "SELECT * FROM Orders WHERE ID='$id';";
    $temp1 = $pdo->query($sql_select_order);
    $row1 = $temp1->fetch();
    $sql_select = "SELECT * FROM INFORMATION WHERE order_id='$id';";
    $temp = $pdo->query($sql_select);
    $row = $temp->fetch();
    $email="";
    $temp = "";
    if($row['Email'] != "")
    {
        $email = $row['Email'];
    }
    $address="";
    if($row['Address'] != "")
    {
        $address = $row['Address'];
    }
    $city="";
    if($row['City'] != "")
    {
        $city = $row['City'];
    }
    $state="";
    if($row['State'] != "")
    {
        $state = $row['State'];
    }
    $zip="";
    if($row['Zip'] != "")
    {
        $zip = $row['Zip'];
    }
    $item="";
    if($row1['ITEM'] != "")
    {
        $item = $row1['ITEM'];
    }
    $price="";
    if($row1['Price'] != "")
    {
        $price = $row1['Price'];
    }
    $quantity="";
    if($row1['Quantity'] != "")
    {
        $quantity = $row1['Quantity'];
    }
    $discount="";
    if($row1['discount'] != "")
    {
        $discount = $row1['discount'];
    }
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
    <title>Checkout - Shipping</title>
    <link rel="stylesheet" href="style.css"> 
</head>
<body>
    <div class="left_split">
        <h1 id="page_title">Shipping</h1>

        <div class="input_section">
            <h3>Contact/Shipping</h3>
            
            <div class="information_holder">
                <!-- Show the email -->
                <p class="information">Contact: <span id="email"><?php echo htmlspecialchars($email); ?></span> </p>  
                
                <!-- Show the address -->
                <p class="information">Ship to: 
                    <span id="street"><?php echo htmlspecialchars($address); ?></span>
                    <span id="city"><?php echo htmlspecialchars($city); ?></span>
                    <span id="state"><?php echo htmlspecialchars($state); ?></span>
                    <span id="zip"><?php echo htmlspecialchars($zip); ?></span> 
                </p> 

            </div>
            
            <h3>Shipping Method</h3>

            <form action="" method="POST">
                <div class="information_holder" style="padding: 10px;">
                    <label><input id="std_ship" type="radio" name="shippingMethod1" value=10.00>Expedited Shipping $10.00</label><br>
                    <label><input id="fast_ship" type="radio" name="shippingMethod2" value=5.00>Standard Shipping $5.00</label><br>
                </div>
            

                <input type="submit" class="button" name="ship_cont" value=" Continue to Payment " style="margin-left: 3in; margin-top: 1.55in;">
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
                            <?php echo $item;?>                        
                        </td>
                        <td>
                            <?php echo $quantity;?>   
                        </td>
                        <td>
                            <?php echo $price;?>   
                        </td>
                    </tr>
                </table>
                <br>
            </div>
        </div>

        <div class="summary_section">
            <form method="GET" action="<?php echo $_SERVER['PHP_SELF'];?>">
            <div class="summary_item"><input class="summary_item" type="text" name="discount_code" placeholder="Discount Code">
                <input type="submit" class="button" name="discount" style="margin-left: 0px;" value="Apply Discount">
            </div><br>
            </form>
            <form method="POST" action="">
                <button type="submit" class="button" name="update_ship" style="margin-left: 0px;" value="Update Cart">Update Cart</button>
            </form>

        </div>
        <p id="discount_price">DISCOUNT: $<?php echo htmlspecialchars($discount) ?></p>
        <p id="payment_total_text">SUBTOTAL: $<?php echo htmlspecialchars((float)$price * (int)$quantity)?></p>
    </div>
    <?php
        require_once("config.php");
        if(isset($_POST["update_ship"]))
        {
            echo "<script> window.open('http://localhost:8888/Project/store.php','_self');</script>";
            $delete_sql = "DELETE FROM Information WHERE order_id='$id'";
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
        if(isset($_POST["shippingMethod1"]))
        {
            $temp = "Expedited Shipping $10.00";
            $_SESSION["shipping_method"] = $temp;
            $_SESSION["shipping_price"] = 10;
        }
        else if(isset($_POST["shippingMethod2"]))
        {
            $temp = "Standard Shipping $5.00";
            $_SESSION['shipping_method'] = $temp;
            $_SESSION["shipping_price"] = 5;
        }
        if(isset($_POST["ship_cont"]))
        {
            if($temp != "")
            {
                $update_sql = "UPDATE Orders SET ShippingMethod='$temp' WHERE ID='$id';";
                $pdo->exec($update_sql);
                echo "<script> window.open('http://localhost:8888/Project/payment.php','_self');</script>";
            }
            else
            {
                echo '<script>alert("You have to input all the field")</script>';
                echo "<script> window.open('http://localhost:8888/Project/shipping.php','_self');</script>";
            }
        }
    ?>
</body>
</html>