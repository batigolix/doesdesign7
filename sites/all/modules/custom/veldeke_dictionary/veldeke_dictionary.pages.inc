<?php

/**
 * @file
 * TODO Auto generated file, add description.
 */

/**
 * Returns test page.
 */
function veldeke_dictionary_test() {
  $output['#markup'] = 'test';
  download_external_file('https://docs.google.com/spreadsheet/pub?key=0AgLDdff6gGPwdHVzM2pmQkZjSXVDUUwybkpQWGROVkE&single=true&gid=0&output=csv', 'public://veldeke-dictionary.csv');
  return $output;
}

/**
 * Returns render array with entries for 1 letter for dictionary pages.
 */
function veldeke_dictionary_entries($lang = 'nl', $letter = 'a') {
  $entries = veldeke_dictionary_fetch_entries($lang, $letter);

  // Populates an item list for the definition list.
  if ($entries) {
    foreach ($entries as $entry) {
      $wrentry = entity_metadata_wrapper('node', $entry);

      // Checks if head word, translation and conjugation are available.
      if (($wrentry->__isset('field_translation')) && ($wrentry->__isset('field_head_word')) && ($wrentry->__isset('field_conjugation'))) {
        $data[] = array(
          'term' => $lang == 'li' ? $wrentry->field_translation->value() : $wrentry->field_head_word->value(),
          'definitions' => $lang == 'li' ? $wrentry->field_head_word->value() : theme('definition', array(
            'definition' => $wrentry->field_translation->value(),
            'misc' => $wrentry->field_conjugation->value(),
          )),
        );
      }
    }
    $build['dictionary_page'] = array(
      '#theme' => 'definition_list',
      '#items' => $data,
    );
    $alfa = array_shift(array_values($data));
    $omega = end($data);
    $count = count($data);
    drupal_set_title(t('Dictionary') . ': ' . t('From !alfa to !omega', array(
          '!alfa' => $alfa['term'],
          '!omega' => $omega['term'],
        )));
  }
  else {
    drupal_set_message('No dictionary entries found. Please try another letter.', 'notice');
    drupal_set_title(t('Dictionary'));
  }

  $build['#attached']['css'] = array(
    drupal_get_path('module', 'veldeke_dictionary') . '/css/veldeke_dictionary.css',
  );

  return $build;
}


/**
 * Inspects wrapped entity fields.
 */
function _wwrapper_debug($w) {
  $values = array();
  foreach ($w->getPropertyInfo() as $key => $val) {
    $values[$key] = $w->$key->value();
  }
  return $values;
}
