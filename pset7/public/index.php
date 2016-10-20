<?php

    // configuration
    require("../includes/config.php"); 
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $stocks = [];
    if (count($rows) > 0)
    {
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $stocks[] = [
                    "name" => $stock["name"],
                    "price" => number_format($stock["price"], 2),
                    "shares" => $row["shares"],
                    "symbol" => $stock["symbol"],
                    "total" => number_format(($row["shares"] * $stock["price"]), 2)
                ];
            }
        }
    }
    $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = [];
    if (count($rows) == 1)
    {
        $cash["cash"] = "$".number_format($rows[0]["cash"], 2);
    }
    render("portfolio.php", ["title" => "Portfolio", "stocks" => $stocks, "cash" => $cash]);
?>
