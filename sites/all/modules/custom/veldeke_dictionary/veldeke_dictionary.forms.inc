<?php

/**
 * @file
 * TODO Auto generated file, add description.
 */

/**
 * Defines the form to downlaod th csv from google.
 */
function download_csv($form, &$form_state) {
  $form['intro']['#markup'] = t('Download the google csv spreadsheet with dictionary entries');
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Download'),
  );
  return $form;
}

/**
 * Submits the download csv form.
 */
function download_csv_submit(&$form, &$form_state) {
  $result = download_external_file('https://docs.google.com/spreadsheet/pub?key=0AgLDdff6gGPwdHVzM2pmQkZjSXVDUUwybkpQWGROVkE&single=true&gid=0&output=csv', 'public://veldeke-dictionary.csv');
}

/**
 * Defines the search terms form.
 */
function search_terms($form, &$form_state) {
  $form['entry'] = array(
    '#type' => 'textfield',
    '#size' => 12,
    '#title' => t('Search in the dictionary'),
    '#autocomplete_path' => 'veldeke_dictionary/search_terms_autocomplete_callback',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Search',
  );
  return $form;
}

/**
 * Submits search terms form.
 *
 * Redirects the visitor to the result.
 */
function search_terms_submit($form, &$form_state) {
  $form_state['redirect'] = 'node/' . $form_state['values']['node'];
}

/**
 * Validates search terms form.
 *
 * Verifies & extracts node id from input texts and provides the node ID.
 */
function search_terms_validate($form, &$form_state) {
  $entry = $form_state['values']['entry'];
  $matches = array();
  $nid = 0;

  // Matches a pattern like [33334] and if found extracts the numeric portion.
  $result = preg_match('/\[([0-9]+)\]$/', $entry, $matches);
  if ($result > 0) {

    $nid = $matches[$result];
    $node = node_load($nid);
    if (empty($node)) {
      form_error($form['node'], t('Sorry, no node with nid %nid can be found', array('%nid' => $nid)));
      return;
    }
  }

  // Do an alternative search in case JavaScript is disabled.
  else {
    $nid = db_select('node')
      ->fields('node', array('nid'))
      ->condition('title', db_like($entry) . '%', 'LIKE')
      ->range(0, 1)
      ->execute()
      ->fetchField();
  }

  if (!empty($nid)) {
    $form_state['values']['node'] = $nid;
  }
  else {
    form_error($form['node'], t('Sorry, no node starting with %title can be found', array('%title' => $entry)));
  }
}
