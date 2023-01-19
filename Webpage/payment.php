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
    $method = "";
    if($row1['ShippingMethod'] != "")
    {
        $method = $row1['ShippingMethod'];   
    }
    if($_SESSION["shipping_price"] != "")
    {
        $shipping = $_SESSION["shipping_price"];
    }
    $discount="";
    if($row1['discount'] != "")
    {
        $discount = $row1['discount'];
    }
    
    $card_number = "";
    if(isset($_GET["card_num"]))
    {
        $card_number = $_GET["card_num"];
    }
    $card_name = "";
    if(isset($_GET["card_name"]))
    {
        $card_name = $_GET["card_name"];
    }
    
    $exp_date = "";
    if(isset($_GET["exp_date"]))
    {
        $exp_date = $_GET["exp_date"];
    }
    $code = "";   
    if(isset($_GET["security_code"]))
    {
        $code = $_GET["security_code"];
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
    <title>Checkout - Payment</title>
    <link rel="stylesheet" href="style.css"> 
</head>
<body>
    <div class="left_split">
        <h1 id="page_title">Payment</h1>

        <div class="input_section">
            <h3>Contact/Shipping</h3>
            
            <div class="information_holder">
            <p class="information">Contact: <span id="email"><?php echo htmlspecialchars($email); ?></span> </p>  
                
                <!-- Show the address -->
                <p class="information">Ship to: 
                    <span id="street"><?php echo htmlspecialchars($address); ?></span>
                    <span id="city"><?php echo htmlspecialchars($city); ?></span>
                    <span id="state"><?php echo htmlspecialchars($state); ?></span>
                    <span id="zip"><?php echo htmlspecialchars($zip); ?></span> 
                </p> 
                <p class="information" id="ship">Method: <br> <span id="method"><?php echo htmlspecialchars($method); ?></span></p> <!-- Shipping method -->

            </div>
            
            <h3>Card</h3>

            <form action="" method="GET">
              <input type="text" name="card_num" placeholder="Card number" style="width: 5in;">
              <input type="text" name="card_name" placeholder="Name on card" style="width: 5in;">
              <input type="text" name="exp_date" placeholder="Expiration date">
              <input type="text" name="security_code" placeholder="Security code">
            
                <input type="submit" class="button" name="order_placed" value=" Place order " style="margin-left: 3.65in; margin-top: 10px;">
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
                <input type="submit" class="button" name="discount" style="margin-left: 0px;" value="Apply Discount"></div><br>
            </form>

        </div>

        <p id="payment_total">SUBTOTAL: $<?php echo htmlspecialchars((float)$price * (int)$quantity);?></p>
        <p id="discount_price">DISCOUNT: $<?php echo htmlspecialchars($discount); ?></p>
        <p id="payment_total">SHIPPING: $<?PHP echo htmlspecialchars($shipping);?></p>
        <p id="payment_total_text">TOTAL: $<?php echo htmlspecialchars((float)$price * (int)$quantity + $shipping);?></p>
    </div>
    <?php
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
                    $new_price = (float)$price * $quantity - (int)$discount_value + $shipping;
                    $price = sprintf("%.2f", $new_price);
                    $update_table_discount = "UPDATE Orders SET discount='$discount_value' WHERE ID='$id';";
                    $pdo->exec($update_table_discount);
                    $_SESSION['discount'] = (int)$discount_value;
                    echo "<script>document.getElementById('discount_price').textContent='DISCOUNT: $$discount_value'</script>";
                    echo "<script>document.getElementById('payment_total_text').textContent='TOTAL: $$new_price'</script>";
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
        if(isset($_GET["order_placed"]))
        { 
            if($card_number != "" && $exp_date != "" && $code != "")
            {
                $update_sql = "UPDATE Information SET CardNumber='$card_number' WHERE order_id=$id;";
                $pdo->exec($update_sql);
                echo "<script> window.open('http://localhost:8888/Project/confirmation.php','_self');</script>";
            }
            else
            {
                echo '<script>alert("You have to input all the field")</script>';
                echo "<script> window.open('http://localhost:8888/Project/payment.php','_self');</script>";
            }
        }
    ?>
</body>
</html>