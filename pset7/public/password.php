<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("password.php", ["title" => "Change Password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["curr_password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["new_password"]))
        {
            apologize("You must provide a new password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("Your passwords didn't match.");
        }

        // query database for user
        $rows = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        // first (and only) row
        $row = $rows[0];

        // compare hash of user's input against hash that's in database
        if (password_verify($_POST["curr_password"], $row["hash"]))
        {
            // update the password
            CS50::query("UPDATE users SET hash = ? WHERE id = ?",
                        password_hash($_POST["new_password"], PASSWORD_DEFAULT), $_SESSION["id"]);
            CS50::query("INSERT INTO transactions (user_id, type, time) 
                        VALUES(?, 'PASSWORD CHANGE', NOW())", $_SESSION["id"]);
            success("Your password was changed successfully!");
        }
        else
        {
            apologize("Your current password was incorrect.");
        }
    }

?>
