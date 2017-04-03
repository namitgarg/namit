<?php
/**
 * @file
 * This file is the default admin notification template for Ubercart.
 */
?>
<p>
    <?php print t('Order number:'); ?> <?php print $order_admin_link; ?><br />
    <?php print t('Customer:'); ?> <?php print $order_first_name; ?> <?php print $order_last_name; ?> - <?php print $order_email; ?><br />
    <?php print t('Order total:'); ?> <?php print $order_total; ?><br />
    <?php print t('Shipping method:'); ?> <?php print $order_shipping_method; ?>
</p>
<table>
    <tr>
        <td nowrap="nowrap">
            <?php print t('Products Subtotal:'); ?>&nbsp;
        </td>
        <td width="98%">
            <?php print $order_subtotal; ?>
        </td>
    </tr>

    <?php foreach ($line_items as $item): ?>
        <?php if ($item['type'] == 'subtotal' || $item['type'] == 'total') continue; ?>

        <tr>
            <td nowrap="nowrap">
                <?php print $item['title']; ?>:
            </td>
            <td>
                <?php print $item['formatted_amount']; ?>
            </td>
        </tr>

    <?php endforeach; ?>

    <tr>
        <td>&nbsp;</td>
        <td>------</td>
    </tr>

    <tr>
        <td nowrap="nowrap">
            <b><?php print t('Total for this Order:'); ?>&nbsp;</b>
        </td>
        <td>
            <b><?php print $order_total; ?></b>
        </td>
    </tr>

    <tr>
        <td colspan="2">
            <br /><br /><b><?php print t('Products on order:'); ?>&nbsp;</b>

            <table width="100%" style="font-family: verdana, arial, helvetica; font-size: small;">

                <?php foreach ($products as $product): ?>
                    <tr>
                        <td valign="top" nowrap="nowrap">
                            <b><?php print $product->qty; ?> x </b>
                        </td>
                        <td width="98%">
                            <b><?php print $product->title; ?> - <?php print $product->total_price; ?></b>
                            <?php print $product->individual_price; ?><br />
                            <?php print t('SKU'); ?>: <?php print $product->model; ?><br />
                            <?php print $product->details; ?>
                        </td>
                    </tr>
                <?php endforeach; ?>
            </table>

        </td>
    </tr>
</table>
<p>
    <?php print t('Order comments:'); ?><br />
    <?php print $order_comments; ?>
</p>
