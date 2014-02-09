<!DOCTYPE html>
<!--[if lt IE 7]> <html class="no-js ie6 oldie" lang="en"> <![endif]-->
<!--[if IE 7]>    <html class="no-js ie7 oldie" lang="en"> <![endif]-->
<!--[if IE 8]>    <html class="no-js ie8 oldie" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js" lang="nl" <?php print $rdf_namespaces; ?>> <!--<![endif]-->
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <?php if (!empty($html5shim)) { print $html5shim; } ?>
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <meta content="Doesdesign, birgit, doesborg, mokume, mokume-gane, ringen, trouwringen, sieraden" name="keywords" />
  <meta content="Doesdesign, originele mokume-gane sieraden met organische patronen" name="description" />
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip">
    <a href="#main-menu"><?php print t('Jump to Navigation'); ?></a>
  </div>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>
