<?php


/**
 * @file
 * Contains all block related code
 */

/**
 * Implements hook_block_info().
 */
function veldeke_dictionary_block_info() {
  $blocks['search_terms'] = array(
    'info' => t('Veldeke dictionary: search terms'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );

  $blocks['lang_nav'] = array(
    'info' => t('Veldeke dictionary: Language navigation'),
    'cache' => DRUPAL_NO_CACHE,
  );

  $blocks['az_browse'] = array(
    'info' => t('Veldeke dictionary: A-Z nav'),
    'cache' => DRUPAL_NO_CACHE,
  );

  $blocks['toc'] = array(
    'info' => t('Veldeke dictionary: dictionary TOC'),
    'cache' => DRUPAL_NO_CACHE,
  );

  $blocks['instruct'] = array(
    'info' => t('Veldeke dictionary: dictionary instructions'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );

  $blocks['download_csv'] = array(
    'info' => t('Veldeke dictionary: download csv'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function veldeke_dictionary_block_view($delta = '') {
  $blocks = array();
  switch ($delta) {
    case 'search_terms':
      $blocks['content'] = drupal_get_form('search_terms');
      break;

    case 'lang_nav':
      $arg_letter = arg(2);
      $az_letter = isset($arg_letter) ? $arg_letter : 'a';
      $blocks['subject'] = t('Dictionary');
      $blocks['content'] = veldeke_dictionary_lang_nav($az_letter);
      break;

    case 'az_browse':
      $arg_lang = arg(1);
      $az_lang = $arg_lang == 'li' ? 'li' : 'nl';
      $blocks['subject'] = NULL;
      $blocks['content'] = veldeke_dictionary_az_browse($az_lang);
      break;

    case 'toc':
      $blocks['subject'] = t('Dictionary table of contents');
      $blocks['content'] = veldeke_dictionary_toc();
      break;

    case 'instruct':
      $blocks['subject'] = t('Dictionary instructions');
      $blocks['content'] = array('#markup' => variable_get('dicinstruct_text', 'test'));
      break;

    case 'download_csv':
      $blocks['subject'] = t('Download csv');
      $blocks['content'] = user_access('administer veldeke dictionary') ? drupal_get_form('download_csv') : NULL;
      break;
  }
  return $blocks;
}

/**
 * Configures the dictionary block.
 */
function veldeke_dictionary_block_configure($delta = '') {
  $form = array();
  if ($delta == 'dictionary_instruct') {
    $form['dicinstruct_text'] = array(
      '#type' => 'textarea',
      '#title' => t('Block contents'),
      '#rows' => 5,
      '#cols' => 20,
      '#description' => t('This text will appear in the example block.'),
      '#default_value' => variable_get('dicinstruct_text', '<strong>Tilde</strong>: Um aan te gaeve det \'n waord \'ne lange klank haet gebroeke weej de tilde ( ~ ) Beej \'t schrieve laote weej de tilde weg.'),
    );
  }
  return $form;
}

/**
 * Implements hook_block_save().
 */
function veldeke_dictionary_block_save($delta = '', $edit = array()) {
  if ($delta == 'dictionary_instruct') {
    variable_set('dicinstruct_text', $edit['dicinstruct_text']);
  }
}

/**
 * Constructs the TOC block.
 */
function veldeke_dictionary_toc() {
  $type = 'ul';
  $attributes = array(
    'class' => 'dictionary_toc',
  );
  $items = array();
  foreach (range('A', 'Z') as $char) {
    $items[] = array('data' => l(t('Words with an @char', array('@char' => $char)), 'terms/nl/' . $char));
  }
  return theme('item_list', array(
      'items' => $items,
      'title' => NULL,
      'type' => $type,
      'attributes' => $attributes,
    ));
}


/**
 * Returns render array for a A-Z browser.
 */
function veldeke_dictionary_az_browse($lang = 'nl') {
  $type = 'ul';
  $attributes = array(
    'class' => 'az-browser',
  );
  $items = array();
  foreach (range('A', 'Z') as $char) {
    $items[] = array('data' => l($char, 'terms/' . $lang . '/' . strtolower($char)));
  }
  return array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#title' => t('Browse'),
    '#type' => $type,
    '#attributes' => $attributes,
  );
}

/**
 * Returns render array for a TOC.
 */
function veldeke_dictionary_dictionary_toc() {
  $type = 'ul';
  $attributes = array(
    'class' => 'dictionary_toc',
  );
  $items = array();
  foreach (range('A', 'Z') as $char) {
    $items[] = array('data' => l(t('Words with an @char', array('@char' => $char)), 'terms/nl/' . $char));
  }
  return array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#title' => NULL,
    '#type' => $type,
    '#attributes' => $attributes,
  );
}

/**
 * Returns html for lang navigation.
 */
function veldeke_dictionary_lang_nav($letter = 'a') {

  $items = array();
  $items[] = array('data' => l(t('Nederlands'), 'terms/nl/' . $letter));
  $items[] = array('data' => l(t('Venloos'), 'terms/li/' . $letter));
  $build = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#title' => t('Switch language'),
    '#type' => 'ul',
    '#attributes' => array(
      'class' => 'lang-nav',
    ),
  );
  return $build;
}
