<?php
//kpr(get_defined_vars());
$classes = $classes ? ' class="' . $classes . ' "' : '';
$id_node = isset($id_node) ? ' id="' . $id_node . '"' : '';
?>

<!-- node.tpl.php -->
<div <?php print $classes . $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php print render($content['field_image'][0]); ?>
  <?php print render($title_suffix); ?>
</div>
