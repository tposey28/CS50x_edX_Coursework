<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        if (count($stock) == 3)
        {
            $symbol = $stock["symbol"];
            $name = $stock["name"];
            $price = number_format($stock["price"], 4);
            render("../views/quote.php", ["title" => "Quote", "symbol" => $symbol, "name" => $name, "price" => $price]);
        } else
        {
            apologize("Symbol not found.");
        }
    }
?>
