<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("deposit.php", ["title" => "Deposit"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["deposit"]))
        {
            apologize("You must specify an amount to deposit.");
        } else if (empty($_POST["card"]))
        {
            apologize("You must specify a credit card number to use.");
        } else if (!preg_match("/^\d+$/", $_POST["card"]))
        {
            apologize("That is not a valid credit card number.");
        } else if (!preg_match("/^[$]?\d+$/", $_POST["deposit"]))
        {
            apologize("Please enter a valid amount to deposit.");
        }
        $file = getcwd();
        exec("{$file}/../includes/credit {$_POST["card"]}", $out, $status);
        if ($status !== 0)
        {
            apologize("That is not a valid credit card number.");
        }
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["deposit"], $_SESSION["id"]);
        CS50::query("INSERT INTO transactions (user_id, type, price_at_trans, time) 
                        VALUES(?, 'DEPOSIT', ?, NOW())", $_SESSION["id"], $_POST["deposit"]);
        success("Your deposit of \${$_POST["deposit"]} was successful!");
    }
?>