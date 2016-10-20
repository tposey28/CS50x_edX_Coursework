<table>
    <tr>
        <th>Transaction</th>
        <th>Time</th>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Amount</th>
    </tr>
    <?php foreach ($history as $transaction): ?>
        <tr>
            <td><?=$transaction["type"]?></td>
            <td><?=$transaction["time"]?></td>
            <td><?=$transaction["symbol"]?></td>
            <td><?=$transaction["shares"]?></td>
            <td><?=$transaction["amount"]?></td>
        </tr>
    <?php endforeach ?>
</table>