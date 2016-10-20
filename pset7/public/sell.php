<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
        if (count($rows) > 0)
        {
            render("sell.php", ["title" => "Sell", "stocks" => $rows]);
        } else {
            apologize("You have no stocks to sell.");
        }
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["stock"]))
        {
            apologize("You must select a stock to sell.");
        }
        $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["stock"]);
        if (count($rows) == 1 and $rows[0]["shares"] > 0)
        {
            $stock = lookup($rows[0]["symbol"]);
            $shares = $rows[0]["shares"];
            $total = $rows[0]["shares"]*$stock["price"];
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $total, $_SESSION["id"]);
            CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["stock"]);
            CS50::query("INSERT INTO transactions (user_id, type, symbol, shares, price_at_trans, time) VALUES(?, 'SELL', ?, ?, ?, NOW())", 
                            $_SESSION["id"], $stock["symbol"], $shares, $stock["price"]);
            success("You sold {$shares} shares from {$stock["name"]} for \${$total}!");
        } else
        {
            apologize("You don't have any stock from that company.");
        }
    }
?>