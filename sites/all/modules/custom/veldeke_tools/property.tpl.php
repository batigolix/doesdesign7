<?php
if ($classes) {
  $classes = ' class="' . $classes . ' "';
}
?>

<?php print $building_nav; ?>

<article role="article">
    <figure class="property-plan">
      <?php print $property_img; ?>
    </figure>
  <section class="content">
    <?php // print render($content);?>
    <div class="details">
      <h2><?php print t('Details'); ?></h2>
      <?php print $details; ?>
      <h2><?php print t('Symbols'); ?></h2>
      <?php print $symbols; ?>
    </div>
    <?php print $contact_us_link ?>
    <div class="links">
      <?php print $download_link; ?>
    </div>
  </section>
</article>
<section class="flat-location">
<h1><?php print t('Situation'); ?></h1>
<?php print $building_img; ?>
<?php print $floor_img; ?>
</section>