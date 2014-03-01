<?php
//kpr(get_defined_vars());
//kpr($content);
$classes = $classes ? ' class="' . $classes . ' "' : '';
$id_node = isset($id_node) ? ' id="' . $id_node . '"' : '';
?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>" >
  <?php print render($title_prefix); ?>
  <div class="object-image"><?php print render($content['field_image'][0]); ?></div>
  <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <div class="object-description">  <?php print render($content['body']); ?></div>
  <?php print render($title_suffix); ?>
</article>




