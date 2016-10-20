<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <input list="stocks" autocomplete="off" autofocus name="stock" class="form-control" placeholder="Symbol">
            <datalist id="stocks">
                <?php foreach ($stocks as $stock): ?>
                    <option value=<?=$stock["symbol"]?>><?=$stock["symbol"]?></option>
                <?php endforeach ?>
            </datalist> 
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Sell
            </button>
        </div>
    </fieldset>
</form>