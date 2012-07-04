<div id="page" class="container <?php print $classes; ?>"<?php print $attributes; ?>>
   <div id="header" class="twelve columns clearfix">
    <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/>
      </a>
    <?php endif; ?>

    <?php if ($site_name || $site_slogan): ?>
      <div id="name-and-slogan" class="six columns alpha">

        <?php if ($site_name): ?>
          <?php if ($title): ?>
            <div id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
            </div>
          <?php else: /* Use h1 when the content title is empty */ ?>
            <h1 id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
            </h1>
          <?php endif; ?>
        <?php endif; ?>

        <?php if ($site_slogan): ?>
          <div id="site-slogan"><?php print $site_slogan; ?></div>
        <?php endif; ?>

      </div>
    <?php endif; ?>

    <?php if ($page['header1']): ?>
      <div id="header-region-1" class="three columns">
        <?php print render($page['header1']); ?>
      </div>
    <?php endif; ?>

    <?php if ($page['header2']): ?>
      <div id="header-region-2" class="three columns omega">
        <?php print render($page['header2']); ?>
      </div>
    <?php endif; ?>

  </div> <!-- /header -->

  <div id="content_top"  class="twelve columns clearfix">

    <?php if ($page['content_top1']): ?>
      <div id="content-top-1" class="eight columns alpha">
        <?php print render($page['content_top1']); ?>
      </div>
    <?php endif; ?>

    <?php if ($page['content_top2']): ?>
      <div id="content_top2" class="four columns omega">
        <?php print render($page['content_top2']); ?>
      </div>
    <?php endif; ?>

  </div>



  <!-- ______________________ MAIN _______________________ -->

  <div id="main" class="clearfix twelve columns">

    <div id="content" class="eight columns alpha">

        <?php if ($breadcrumb || $title|| $messages || $tabs || $action_links): ?>
          <div id="content-header">

            <?php // print $breadcrumb; ?>

            <?php if ($page['highlight']): ?>
              <div id="highlight"><?php print render($page['highlight']) ?></div>
            <?php endif; ?>

            <?php if ($title && !$is_front): ?>
              <h1 class="title"><?php print $title; ?></h1>
            <?php endif; ?>

            <?php print render($title_suffix); ?>
            <?php print $messages; ?>
            <?php print render($page['help']); ?>

            <?php if ($tabs): ?>
              <div class="tabs"><?php print render($tabs); ?></div>
            <?php endif; ?>

            <?php if ($action_links): ?>
              <ul class="action-links"><?php print render($action_links); ?></ul>
            <?php endif; ?>
            
          </div> <!-- /#content-header -->
        <?php endif; ?>

        <div id="content-area">
          <?php print render($page['content']) ?>
        </div>

        <?php print $feed_icons; ?>

      </div>

    <?php if ($page['sidebar']): ?>
      <div id="sidebar" class="column sidebar four columns omega">
          <?php print render($page['sidebar']); ?>
      </div>
    <?php endif; ?> <!-- /sidebar-first -->

</div> <!-- /main -->
  
  <!-- bunch of pseudeo regions for the homepage. prevent using panels n shite -->
  

    <div id="content_bot_row_1_2"  class="twelve columns clearfix">
    <?php if ($page['content_bot_row_1_1']): ?>
      <div id="content-bot_row_1_1" class="eight columns alpha">
        <?php print render($page['content_bot_row_1_1']); ?>
      </div>
    <?php endif; ?>
    <?php if ($page['content_bot_row_1_2']): ?>
      <div id="content_bot_row_1_2" class="four columns omega">
        <?php print render($page['content_bot_row_1_2']); ?>
      </div>
    <?php endif; ?>
  </div>


    <div id="content_bot_row_2"  class="twelve columns clearfix">
    <?php if ($page['content_bot_row_2_1']): ?>
      <div id="content-bot_row_2_1" class="four columns alpha">
        <?php print render($page['content_bot_row_2_1']); ?>
      </div>
    <?php endif; ?>
    <?php if ($page['content_bot_row_2_2']): ?>
      <div id="content_bot_row_2_2" class="four columns">
        <?php print render($page['content_bot_row_2_2']); ?>
      </div>
    <?php endif; ?>
    <?php if ($page['content_bot_row_2_3']): ?>
      <div id="content_bot_row_2_3" class="four columns omega">
        <?php print render($page['content_bot_row_2_3']); ?>
      </div>
    <?php endif; ?>
    </div>
  

  <!-- ______________________ FOOTER _______________________ -->

  <?php if ($page['footer']): ?>
    <div id="footer">
      <?php print render($page['footer']); ?>
    </div> <!-- /footer -->
  <?php endif; ?>

</div> <!-- /page -->
