<?php

/**
 * Implements hook block info
 * Defines custom blocks
 */
function dd_tools_block_info() {
  $blocks['slideshow'] = array(
    'info' => t('DD tools: Slideshow'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );
  $blocks['news'] = array(
    'info' => t('DD tools: News'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );
  $blocks['categories'] = array(
    'info' => t('DD tools: Categories'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );
  $blocks['flickr'] = array(
    'info' => t('DD tools: Flickr'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );
  $blocks['contact'] = array(
    'info' => t('DD tools: Contact'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );
  return $blocks;
}

/**
 * Defines title and content of custom blocks
 * Defines which function is called for block. Functions can be found in
 * carcan_awar_blocks.inc
 */
function dd_tools_block_view($delta = '') {
  $blocks = array();
  switch ($delta) {
    case 'slideshow':
      $blocks['content'] = dd_tools_slideshow();
      break;
    case 'news':
      $blocks['subject'] = t('News');
      $blocks['content'] = dd_tools_news();
      break;
    case 'categories':
      $blocks['subject'] = t('Categories');
      $blocks['content'] = dd_tools_categories();
      break;
    case 'flickr':
      $blocks['subject'] = t('Photo\'s on Flickr');
      $blocks['content'] = array(
        '#markup' => '<div id="flickr_images"> </div>',
        '#attached' => array(
          'js' => array(
            'data' => drupal_get_path('module', 'dd_tools') . '/js/flickr.js',
            array(
              'data' => array(
                'dd_tools' => array(
                  'block_items' => variable_get('flickr_items', 13),
                ),
              ),
              'type' => 'setting',
            ),
          ),
        ),
      );
      break;
    case 'contact':
      $blocks['content'] = dd_tools_contact();
      break;
  }
  return $blocks;
}

/**
 * Creates the object slideshow
 */
function dd_tools_slideshow() {
  $items = variable_get('slideshow_items', 5);
  $order = variable_get('slideshow_order', 'ASC');
  $order_prop = variable_get('slideshow_order_prop', 'created');
  $query = db_select('node', 'n');
  $query->condition('n.promote', 1);
  $query->range(0, $items);
  $query->orderBy('n.' . $order_prop, $order);
  $query->condition('n.status', 1);
  $query->condition('n.type', 'object');
  $query->fields('n', array('nid', 'title'));
  $results = $query->execute();
  foreach ($results as $result) {
    $nids[] = $result->nid;
  }
  $nodes = node_load_multiple($nids);
  $items = array();
  foreach ($nodes as $node) {
//    dsm(format_date($node->created, 'medium'));
//    dsm(format_date($node->changed, 'medium'));
    $node_view = node_view($node, 'hero_teaser');
    $items[] = array('data' => drupal_render($node_view), 'class' => array('slide'));
  }
  $lib_path = libraries_get_path('responsiveslides');
  $rs_js = 'jQuery(function() {jQuery(".rslides").responsiveSlides({auto: true, timeout: 3000, speed: 500, pager: true, pauseControls: true, navContainer: ""});});';
  $build = array(
    '#markup' => theme('item_list', array('items' => $items, 'title' => NULL, 'type' => 'ul', 'attributes' => array('class' => array('rslides')))),
    '#attached' => array(
      'js' => array(
        array(
          'data' => $lib_path . '/responsiveslides.min.js',
          'type' => 'file',
        ),
        array(
          'data' => $rs_js,
          'type' => 'inline',
        ),
      ),
    ),
  );
  return $build;
}

/**
 * Implements hook_block_configure().
 */
function dd_tools_block_configure($delta = '') {
  $form = array();
  switch ($delta) {
    case 'slideshow' :
      $form['slideshow_items'] = array(
        '#type' => 'select',
        '#title' => t('Number of items'),
        '#options' => array(3 => 3, 5 => 5, 7 => 7, 9 => 9, 11 => 11, 13 => 13, 15 => 15, 17 => 17),
        '#description' => t('This number of items will be shown in the slideshow block'),
        '#default_value' => variable_get('slideshow_items', 5),
      );
      $form['slideshow_order'] = array(
        '#type' => 'select',
        '#title' => t('Order'),
        '#options' => array('ASC ' => t('Ascending'), 'DESC' => t('Descending')),
        '#description' => t('In what order the items will be shown in the slideshow block'),
        '#default_value' => variable_get('slideshow_order', 'DESC'),
      );
      $form['slideshow_order_prop'] = array(
        '#type' => 'select',
        '#title' => t('Order by'),
        '#options' => array('created ' => t('Creation date'), 'changed' => t('Date of last change')),
        '#description' => t('By which date the items will be ordered in the slideshow block'),
        '#default_value' => variable_get('slideshow_order_prop', 'DESC'),
      );
      break;
    case 'news' :
      $form['news_items'] = array(
        '#type' => 'select',
        '#title' => t('Number of items'),
        '#options' => array(2 => 2, 5 => 5, 10 => 10),
        '#description' => t('This number of items will be shown in the news block'),
        '#default_value' => variable_get('news_items', 5),
      );
      break;
    case 'flickr' :
      $form['flickr_items'] = array(
        '#type' => 'select',
        '#title' => t('Number of items'),
        '#options' => array(10 => 10, 12 => 12, 15 => 15, 16 => 16, 18 => 18, 20 => 20),
        '#description' => t('This number of items will be shown in the Flickr block'),
        '#default_value' => variable_get('flickr_items', 5),
      );
      break;
  }
  return $form;
}

/**
 * Implements hook_block_save().
 */
function dd_tools_block_save($delta = '', $edit = array()) {
  switch ($delta) {
    case 'slideshow':
      variable_set('slideshow_items', $edit['slideshow_items']);
      variable_set('slideshow_order', $edit['slideshow_order']);
      variable_set('slideshow_order_prop', $edit['slideshow_order_prop']);
      break;
    case 'news':
      variable_set('news_items', $edit['news_items']);
      break;
    case 'flickr':
      variable_set('flickr_items', $edit['flickr_items']);
      break;
  }
}

function dd_tools_news() {
  $limit = variable_get('news_items', 5);
  $query = db_select('node', 'n')
      ->fields('n')
      ->condition('n.status', 1)
      ->range(0, $limit)
      ->orderBy('n.created', 'DESC')
      ->condition('n.type', 'story');
  $results = $query->execute();
  $items = array();
  foreach ($results as $result) {
    $items[] = array('data' => format_date($result->changed, 'medium') . ' ' . l($result->title, drupal_get_path_alias('node/' . $result->nid)));
  }
  $result = $query->execute();
  $build['news_list'] = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#attrinutes' => array('class' => array('news-list')),
  );
  $build['more'] = array('#markup' => l(t('More'), 'nieuws'));
  return $build;
}

function dd_tools_categories() {
  $vocabulary = taxonomy_vocabulary_machine_name_load('vocabulary_7');
  $terms = taxonomy_get_tree($vocabulary->vid);
  $items = array();
  foreach ($terms as $term) {
    $items[] = array('data' => l($term->name, drupal_get_path_alias('taxonomy/term/' . $term->tid)));
  }
  $build['category_list'] = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#attributes' => array('class' => array('category-list')),
  );
//  $build['more'] = array('#markup' => l(t('More'),'nieuws'));
  return $build;
}

function dd_tools_contact() {


  /* <div><a href=""><img alt="Faceboork" src="/sites/doesdesign.nl/files/facebook-logo.png" style="border-style:solid; border-width:0px; height:32px; width:32px" title="Facebook" /></a> <a href="http://www.linkedin.com/profile/edit?trk=hb_tab_pro_top"><img alt="Linkedin" src="/sites/doesdesign.nl/files/linkedin-logo.png" style="border-style:solid; border-width:0px; height:32px; width:32px" title="Linkedin" /></a> <a href="http://www.youtube.com/user/metalartcreations?feature=mhee"><img alt="Youtube" src="/sites/doesdesign.nl/files/youtube-logo.png" style="border-style:solid; border-width:0px; height:32px; width:32px" title="Youtube" /></a> <a href="http://twitter.com/#!/Doesdesign_nl"><img alt="Twitter" src="/sites/doesdesign.nl/files/twitter-logo.png" style="border-style:solid; border-width:0px; height:32px; width:32px" title="Twitter" /></a></div>
   */

  $socials = array(
    array(
      'name' => 'Facebook',
      'img' => 'facebook-logo.png',
      'cta' => t('Visit Doesdesign at Facebook'),
      'url' => 'https://www.facebook.com/Doesdesign.nl',
      'class' => 'facebook',
    ),
    array(
      'name' => 'Linkedin',
      'img' => 'linkedin-logo.png',
      'cta' => t('Visit Birigit at Linkedin'),
      'url' => 'http://nl.linkedin.com/in/birgitdoesborg',
      'class' => 'linkedin',
    ),
    array(
      'name' => 'Twitter',
      'img' => 'twitter-logo.png',
      'cta' => t('Tweet Birigit'),
      'url' => 'http://twitter.com/#!/Doesdesign_nl',
      'class' => 'twitter',
    ),
    array(
      'name' => 'YouTube',
      'cta' => t('Visit YouTube page'),
      'img' => 'youtube-logo.png',
      'url' => 'http://www.youtube.com/user/metalartcreations',
      'class' => 'youtube',
    ),
  );
  $img_path = drupal_get_path('module', 'dd_tools') . '/images/';
  $items = array();
  foreach ($socials as $social) {

    $img = theme('image', array(
      'path' => $img_path . $social['img'], 'attributes' => array(
        'title' => $social['cta'],
        'alt' => $social['name'],
      )
    ));
    $items[] = array(
      'data' => l($img, $social['url'], array('html' => TRUE, 'attributes' => array('class' => array('social', $social['class']), 'alt' => $social['cta']))),
    );
  }
  $build['doespic'] = array(
    '#theme' => 'image',
    '#path' => $img_path . 'Doesklein.jpg',
    '#width' => '75',
    '#height' => '100',
    '#attributes' => array(
      'class' => array(
        'doespic'
      ),
      'title' => 'Birgit Doesborg',
      'alt' => 'Foto Birgit Doesborg',
    ),
  );
  $build['about']['#markup'] = '<div class="about"><strong>' . l('Birgit Doesborg', 'about') . '</strong>, Goud- en zilversmid.</div>';
  $build['contact_link']['#markup'] = '<div class="contact"><strong>' . l('Contact', 'contact') . '</strong></div>';
  $build['social'] = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#attributes' => array('class' => array('socialist')),
  );
  return $build;
}

/*    height: 80px;
 * 
 * 
 * <div><a href="/about"><img alt="" src="/sites/doesdesign.nl/files/Doesklein.jpg" style="float:left; height:100px; margin-left:0px; margin-right:10px; width:75px" /></a><strong><a href="/about">Birgit Doesborg</a>, </strong>Goud- en zilversmid<strong> </strong></div>

<div><strong><a href="/contact">Contact</a></strong></div>


*/