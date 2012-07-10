<div id="page" class="container <?php print $classes; ?>"<?php print $attributes; ?>>
  <div id="header" class="row">
     <div class="columns two" id="logo">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/></a>
     </div>
       <div class="columns four">
        <div id="site-name"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a></div>
        <div id="site-slogan"><?php print $site_slogan; ?></div>
      </div>
      <div class="columns three">
        <?php if ($page['header1']): ?>
            <?php print render($page['header1']); ?>
        <?php endif; ?>
      </div>
      <div class="columns three">
        <?php if ($page['header2']): ?>
            <?php print render($page['header2']); ?>
        <?php endif; ?>
      </div>
    </div><!-- end .header -->
  <div id="content_top" class="row">
    <?php if ($page['content_top1']): ?>
      <nav id="content-top-1" class="eight columns">
        <?php print render($page['content_top1']); ?>
      </nav>
    <?php endif; ?>
    <?php if ($page['content_top2']): ?>
      <div id="content_top2" class="columns four">
        <?php print render($page['content_top2']); ?>
      </div>
    <?php endif; ?>
  </div><!-- end content top row -->
  <div id="main" class="row">
    <div id="content" class="eight columns">
        <?php if ($breadcrumb || $title|| $messages || $tabs || $action_links): ?>
          <div id="content-header">
            <?php // print $breadcrumb; ?>
            <?php if ($page['highlight']): ?><div id="highlight"><?php print render($page['highlight']) ?></div><?php endif; ?>
            <?php if ($title && !$is_front): ?><h1 class="title"><?php print $title; ?></h1><?php endif; ?>
            <?php print render($title_suffix); ?>
            <?php print $messages; ?>
            <?php print render($page['help']); ?>
            <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
            <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
          </div> <!-- /#content-header -->
        <?php endif; ?>
        <div id="content-area">
          <?php print render($page['content']) ?>
        </div><!-- end content-area -->
        <?php // print $feed_icons; ?>


  <!-- bunch of pseudeo regions for the homepage. prevent using panels n shite -->

<div id="content_bot_row_2"  class="row">
    <?php if ($page['content_bot_row_2_1']): ?>
      <div id="content-bot_row_2_1" class="four columns">
        <?php print render($page['content_bot_row_2_1']); ?>
      </div>
    <?php endif; ?>
    <?php if ($page['content_bot_row_2_2']): ?>
      <div id="content_bot_row_2_2" class="four columns">
        <?php print render($page['content_bot_row_2_2']); ?>
      </div>
    <?php endif; ?>
</div><!-- end content bot row 2 -->

</div><!-- end content -->
    <?php if ($page['sidebar']): ?>
      <div id="sidebar" class="four columns">
        <?php print render($page['sidebar']); ?>
      </div>
    <?php endif; ?> <!-- /sidebar-first -->
  </div> <!-- /main -->

  <?php if ($page['footer']): ?>
    <div id="footer" class="row">
    <div class="columns twelve">
      <?php print render($page['footer']); ?>
    </div> <!-- /footer -->
    </div> <!-- /footer -->
  <?php endif; ?>

</div> <!-- /page -->

