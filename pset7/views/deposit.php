<form action="deposit.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="deposit" placeholder="Dollar Amount" type="text"/>
        </div>
        <div class="form-group">
            <input autocomplete="off" class="form-control" name="card" placeholder="Credit Card Number" type="text"/>*
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Deposit
            </button>
        </div>
    </fieldset>
</form>
<hr>
<p class="notice">
    *Don't worry. You won't actually be charged anything and your credit card number won't be stored anywhere. It will only be used 
    to pass a checksum. If you still don't believe me, use this fake American Express number: 378282246310005
</p>