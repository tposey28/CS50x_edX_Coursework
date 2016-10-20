<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy.php", ["title" => "Buy"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["stock"]))
        {
            apologize("You must specify a company to buy shares from.");
        } else if (empty($_POST["shares"]))
        {
            apologize("You must specify how many shares to buy.");
        } else if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Please give a positive integer value for the number of stocks.");
        }
        $stock = lookup($_POST["stock"]);
        if ($stock == false)
        {
            apologize("Could not find company ticker.");
        }
        $price = $_POST["shares"] * $stock["price"];
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        if (count($rows) == 1 and $rows[0]["cash"] >= $price)
        {
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $price, $_SESSION["id"]);
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
                            $_SESSION["id"], $stock["symbol"], $_POST["shares"]);
            CS50::query("INSERT INTO transactions (user_id, type, symbol, shares, price_at_trans, time) VALUES(?, 'BUY', ?, ?, ?, NOW())", 
                            $_SESSION["id"], $stock["symbol"], $_POST["shares"], $stock["price"]);
            success("You bought {$_POST["shares"]} shares from {$stock["name"]} for \${$price}!");
        } else
        {
            apologize("You don't have enough money in your account for this.");
        }
    }
?>