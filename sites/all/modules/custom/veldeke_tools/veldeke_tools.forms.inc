<?php

/**
 * @file
 * TODO Auto generated file, add description.
 */

/**
 * settings form build callback.
 *
 * @param array $form
 *   Drupal form array.
 * @param array $form_state
 *   Drupal form_state array.
 *
 * @return array
 *   Drupal form array.
 */
function veldeke_settings($form, &$form_state) {
  $form = array();
  $form['debug'] = array(
      '#type' => 'fieldset',
      '#title' => t('Debugging'),
  );
  $form['debug']['debug_mode'] = array(
      '#type' => 'radios',
      '#title' => t('Operate in debug mode'),
      '#options' => array(1 => 'True', 0 => 'False'),
      '#default_value' => variable_get('debug_mode', 0),
  );
  $form['debug']['debug_max'] = array(
      '#type' => 'textfield',
      '#title' => t('Max nr of items to process'),
      '#description' => 'To prevent long waiting during testing you can limit the number of items that will be processed',
      '#default_value' => variable_get('debug_max', 999999),
      '#size' => 7,
  );
  $form['lists'] = array(
      '#type' => 'fieldset',
      '#title' => t('Lists'),
  );
  $form['lists']['max_items'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of items shown in lists'),
      '#default_value' => variable_get('max_items', '12'),
      '#size' => 5,
  );
  $form['cron'] = array(
      '#type' => 'fieldset',
      '#title' => t('Cron settings'),
  );
  $form['cron']['cron_interval'] = array(
      '#type' => 'select',
      '#title' => t('Cron interval'),
      '#description' => t('Time after which cron tasks will respond to a processing request.'),
      '#default_value' => variable_get('cron_interval', 60 * 60),
      '#options' => array(
          3600 => t('1 hour'),
          12 * 3600 => t('12 hours'),
          60 * 60 * 24 => t('1 day'),
          7 * 60 * 60 * 24 => t('1 week'),
      ),
  );
  return system_settings_form($form);
}

/**
 * Implements hook form. Second form, shwon together with results. Can be used to filter down results
 */

function veldeke_tools_properties_filter_form($form, &$form_state) {
  $form = array();
  $options_bedrooms = array(
      999 => t('- Any -'),
      0 => 'Studio',
      1 => '1',
      2 => '2',
      3 => '3',
  );
  $options_surface =  array(
      0 => t('- Any -'),
      50 => 'min. 50 m²',
      75 => 'min. 75 m²',
      100 => 'min. 100 m²',
      125 => 'min. 125 m²',
      150 => 'min. 150 m²',
//      150 => '150 >',
  );
//  $options_price =  array(
//      0 => t('- Any -'),
//      '200000.00' => 'max. 200.000 €',
//      '250000.00' => 'max. 250.000 €',
//      '300000.00' => 'max. 300.000 €',
//      '350000.00' => 'max. 350.000 €',
//      '400000.00' => 'max. 400.000 €',
//      '450000.00' => 'max. 450.000 €',
//      '500000.00' => 'max. 500.000 €',
//   );
  $storage = (isset($_SESSION['form_values'])?$_SESSION['form_values']:0);  //dpm($storage);
  $selected_bedrooms = isset($storage['bedrooms']) ? $storage['bedrooms'] : 999;
  $selected_surface = isset($storage['surface']) ? $storage['surface'] : 0;
//  $selected_price = isset($storage['price']) ? $storage['price'] : 0;
  $form['bedrooms'] = array(
      '#type' => 'select',
      '#title' => t('Bedrooms'),
      '#options' => $options_bedrooms,
      '#default_value' => $selected_bedrooms,
  );
  $form['surface'] = array(
      '#type' => 'select',
      '#title' => t('Surface'),
      '#options' => $options_surface,
      '#default_value' => $selected_surface,
  );
//  $form['price'] = array(
//      '#type' => 'select',
//      '#title' => t('Price'),
//      '#options' => $options_price,
//      '#default_value' => $selected_price,
//  );
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Search'),
  );
  $form['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
      '#weight' => 30,
      '#submit' => array('veldeke_tools_reset'),
  );
  return $form;
}

/*
 * Clears set filters
 */

function veldeke_tools_reset() {
  if (isset($_SESSION['form_values'])) {
    unset($_SESSION['form_values']);
  }
  drupal_goto(current_path());
  drupal_set_message('Filters were reset');
}

/**
 * IMplements custom submit
 */

function veldeke_tools_properties_filter_form_submit(&$form, &$form_state) {
  $_SESSION['form_values'] = $form_state['values'];
  $form_state['rebuild'] = TRUE;
}

/*
 * 
 */

function veldeke_tools_import_dictionary_form($form, &$form_state) {
  $form = array();
//  $form['qty'] = array(
//    '#title' => 'Quantity', '#type' => 'textfield', '#required' => TRUE,
//    '#default_value' => 100,
//    '#description' => t('Enter the number of pages you want to create.'),
//  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );
  return $form;
}
function veldeke_tools_import_dictionary_form_validate(&$form, &$form_state){
//  if(!is_numeric($form_state['values']['qty'])){
//    form_set_error('qty','You must enter a numeric value for quantity.');
//  }
}

function veldeke_tools_import_dictionary_form_submit(&$form, &$form_state){
  batch_set(veldeke_tools_import_dictionary());
}

/*
 * Validates CSV file. Checks file type
 */

function veldeke_tools_upload_csv_form_validate($form, &$form_state) {
  $validators = array('file_validate_extensions' => array('txt csv'));
  $file = file_save_upload('file_upload', $validators);
  if (!$file) {
    form_set_error('file_upload', t('Problem uploading file'));
  } else {
    $form_state['values']['file_upload'] = $file;
  }
}

/*
 * Processes uploaded CSV data
 */

function veldeke_tools_upload_csv_form_submit($form, &$form_state) {
  
//  $line_max = variable_get('user_import_line_max', 1000);
//  ini_set('auto_detect_line_endings', true);
//  $filepath = $form_state['values']['file_upload']->uri;
//  veldeke_tools_replace_csv($filepath);
  
//  $data = $form_state['values']['write_contents'];
  $uri = !empty($form_state['values']['file_upload']->uri) ? $form_state['values']['file_upload']->uri : NULL;

  // Managed operations work with a file object.
  $file_object = file_save_data($data, $uri, FILE_EXISTS_RENAME);
  if (!empty($file_object)) {
    $url = file_create_url($file_object->uri);
    $_SESSION['file_example_default_file'] = $file_object->uri;
    drupal_set_message(t('Saved managed file: %file to destination %destination (accessible via !url, actual uri=<span id="uri">@uri</span>)', array('%file' => print_r($file_object, TRUE), '%destination' => $uri, '@uri' => $file_object->uri, '!url' => l(t('this URL'), $url))));
  }
  else {
    drupal_set_message(t('Failed to save the managed file'), 'error');
  }
}

  
  
  


/*
 * Creates terms from csv data
 * TODO. finish when we have real data
 */

function veldeke_tools_replace_csv($file) {
  
  $output = '';

  
//
//  
//  
//  
//  $output = '';
//  $data_path = drupal_get_path('module', 'veldeke_tools') . '/data/';
//  
//  dsm($data_path);
//  dsm($file);
//  
// $info = pathinfo($file);
// $ext = $info['extension']; // get the extension of the file
// $newname = "newname.".$ext; 
// $target = $data_path.$newname;
// dsm(move_uploaded_file($file, $target));
//  
//  
//  
//    if (file_exists($data_path . $file)) {
//      rename($file['current_filename'],$file['new_filename']);
//    }
//  
//  
//  if (($handle = fopen($file, "r")) !== FALSE) {
//    # Set the parent multidimensional array key to 0.
//    $nn = 0;
//    while (($data = fgetcsv($handle, 0, ";", "'")) !== FALSE) {
//      # Count the total keys in the row.
//      $c = count($data);
//      # Populate the multidimensional array.
//      for ($x = 0; $x < $c; $x++) {
//        $rows[$nn][$x] = $data[$x];
//      }
//      $nn++;
//    }
//    # Close the File.
//    fclose($handle);
//  }
//  
  return $output;
}
