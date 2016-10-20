<?php

    // configuration
    require("../includes/config.php");
    
    $rows = CS50::query("SELECT user_id, type, symbol, shares, price_at_trans, 
                        DATE_FORMAT(time, '%m/%d/%Y, %h:%m%p') AS ftime
                        FROM transactions WHERE user_id = ? ORDER BY time DESC",
                        $_SESSION["id"]);
    if (count($rows) > 0)
    {
        $history = [];
        foreach ($rows as $row)
        {
            $history[] = [
                "type" => $row["type"],
                "symbol" => $row["symbol"],
                "shares" => $row["shares"],
                "amount" => (empty($row["price_at_trans"])) ? "" : "$".number_format($row["price_at_trans"], 2),
                "time" => $row["ftime"]
                ];
        }
        render("history.php", ["title" => "History", "history" => $history]);
    } else
    {
        apologize("You have no previous transactions.");
    }
?>