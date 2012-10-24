<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>" itemscope itemtype="http://schema.org/Product">
  <span class="hidden" <?php print $title_attributes; ?> itemprop="name">
    <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
  </span>
  <?php print render($content['field_image']); ?>
  <div itemprop="description">
    <?php print $body['0']['safe_value']; ?>
  </div>
  <?php print render($content['taxonomy_vocabulary_6']); ?>
  <div class="field field-name-field-prijs" itemprop="offers" itemscope itemtype="http://schema.org/Offer">
    <div class="field-label">Prijs:</div>
    <div class="" itemprop="price">    <?php print render($field_prijs['0']['value']); ?></div>
    <link itemprop="availability" href="http://schema.org/PreOrder" />
  </div>
  <?php print render($content['field_gewicht']); ?>
  <?php print render($content['taxonomy_vocabulary_7']); ?>
</div> <!-- /node--object.tpl.php-->