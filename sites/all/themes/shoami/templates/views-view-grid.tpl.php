<?php
/**
 * @file views-view-grid.tpl.php
 * Default simple view template to display a rows in a grid.
 *
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 *
 * @ingroup views_templates
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<table class="<?php print $class; ?>"<?php print $attributes; ?>>
  <tbody>
    <?php foreach ($rows as $row_number => $columns): ?>
      <tr class="<?php print $row_classes[$row_number]; ?>">
        <?php foreach ($columns as $column_number => $item): ?>
          <td class="<?php print $column_classes[$row_number][$column_number]; ?>">
            <?php print $item; ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>


 */
?>



<?php
reset($rows);
$gridsize = count($rows[0]);
?>
<?php if (!empty($title)) : ?>
  <h3 class='grid-title'><?php print $title; ?></h3>
<?php endif; ?>
<div class="views-view-grid grid-<?php print $gridsize ?>">

    <?php foreach ($rows as $row_number => $columns): ?>
      <?php
        $row_class = 'row-' . ($row_number + 1);
        if ($row_number == 0 && count($rows) > 1) {
          $row_class .= ' row-first';
        }
        elseif (count($rows) == ($row_number + 1)) {
          $row_class .= ' row-last';
        }
      ?>
      <div class="<?php print $row_class; ?> clearfix">
        <?php foreach ($columns as $column_number => $item): ?>
          <div class="gridCol <?php print 'col-'. ($column_number + 1); ?>">
<?php if ($item): ?>
            <?php print $item; ?>
<?php endif; ?>           
          </div>
        <?php endforeach; ?>
      </div>
    <?php endforeach; ?>
</div>