<table>
    <tr>
        <th>Symbol</th>
        <th>Name</th>
        <th>Shares</th>
        <th>Price</th>
        <th>Total</th>
    </tr>
    <?php foreach ($stocks as $stock): ?>
        <tr>
            <td><?=$stock["symbol"]?></td>
            <td><?=$stock["name"]?></td>
            <td><?=$stock["shares"]?></td>
            <td><?=$stock["price"]?></td>
            <td><?=$stock["total"]?></td>
        </tr>
    <?php endforeach ?>
</table>
<hr>
<p class="balance">
    Current balance: <?=$cash["cash"]?>
</p>