<?php

/**
 * @file
 * TODO Auto generated file, add description.
 */

/**
 * Returns project page
 * @return string
 */
function veldeke_tools_test() {
  $output = 'test';
  return $output;
}

/**
 * Returns body strings from selected nodes.
 * @return string
 */
function veldeke_tools_export() {

  $output = '';

  $query = db_select('node', 'n');
  $query->condition('n.status', 1);
  $query->condition('n.type', 'book');
  $query->condition('n.title', '%Waord met%', 'LIKE');
  $query->addField('n', 'title');
  $query->join('field_data_body', 'fdb', 'n.nid = fdb.entity_id');
  $query->condition('fdb.bundle', 'book');
  $query->addField('fdb', 'body_value', 'body');
  $query->orderBy('n.title', 'ASC');
  $results = $query->execute();
  $num_rows = $query->countQuery()->execute()->fetchField();
  drupal_set_message($num_rows);
//
  foreach ($results as $result) {
    $output .= $result->body;
  }
  $output = preg_replace('/^\s+|\n|\r|\s+$/m', '', $output);
  $output = preg_replace('/<h3>(.*?)<\/h3>/i', '', $output);
  $output = preg_replace('/<h2>(.*?)<\/h2>/i', '', $output);
  $output = preg_replace('/<dt>(.*?)<\/dt>(.*?)<dd>(.*?)<\/dd>/i', '$1;$3 <br/>', $output);

  return $output;
}

/**
 * Returns HTML for the terms pages
 */
function veldeke_tools_terms($lang = 'nl', $letter = 'a') {
  $output = '';
  $output .= veldeke_tools_lang_nav($letter);
  $output .= veldeke_tools_az_browse($lang);
  $terms = veldeke_tools_fetch_terms($lang, $letter);
  $alfa = array_shift(array_values($terms));
  $omega = end($terms);
  $count = count($terms);
  drupal_set_title(t('Dictionary') . ': ' . t('From !alfa to !omega', array('!alfa' => $alfa['term'], '!omega' => $omega['term'])));
  $build['dictionary_page'] = array(// print table
      '#theme' => 'definition_list',
      '#items' => $terms,
  );
  return $build;
}
