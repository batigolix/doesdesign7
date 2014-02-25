<div id="page" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <header id="header" role="banner">
     <div id="logo">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/></a>
     </div>
       <div id="site-name-and-slogan">
        <div id="site-name"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a></div>
        <div id="site-slogan"><?php print $site_slogan; ?></div>
      </div>
      <div id="header-block">
        <?php if ($page['header1']): ?>
            <?php print render($page['header1']); ?>
        <?php endif; ?>
      </div>
    </header><!-- end .header -->
    
   <div id="content-wrapper">
    <div id="content-top">
    <?php if ($page['content_top']): ?>
      <nav id="content-top-1" role="navigation">
        <?php print render($page['content_top']); ?>
      </nav>
    <?php endif; ?>
    </div><!-- end content top row -->
    <div id="content">
          <div id="content-area" role="main">
        <?php if ($breadcrumb || $title|| $messages || $tabs || $action_links): ?>
            <?php if ($title && !$is_front): ?><h1 class="title"><?php print $title; ?></h1><?php endif; ?>
            <?php print render($title_suffix); ?>
            <?php print $messages; ?>
            <?php print render($page['help']); ?>
            <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
            <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php endif; ?>
          <?php print render($page['content']) ?>

        </div><!-- end content-area -->
    <?php if ($page['sidebar']): ?>
      <aside id="sidebar" role="complementary">
        <?php print render($page['sidebar']); ?>
      </aside>
    <?php endif; ?> <!-- /sidebar-first -->
        <div id="content-end"></div>
    </div><!-- end content -->



  <?php if ($page['footer']): ?>
    <footer id="footer" role="contentinfo">
      <?php print render($page['footer']); ?>
    </footer> <!-- /footer -->
  <?php endif; ?>

</div> <!-- /content-wrapper -->
</div> <!-- /page -->

