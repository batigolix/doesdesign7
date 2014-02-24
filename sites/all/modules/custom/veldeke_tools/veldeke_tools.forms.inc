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
  return system_settings_form($form);
}

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
  kpr(variable_get('letters'));
  $form = array();
  $letters = array();
  foreach (range('A', 'Z') as $char) {
    $letters[$char] = $char;
  }
  $form['letters'] = array(
      '#type' => 'checkboxes',
      '#options' => $letters,
      '#title'=>'Letters',
      '#default_value'=>  variable_get('letters',$letters),
  );
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Import'),
  );



  return $form;
}

function veldeke_tools_import_dictionary_form_validate(&$form, &$form_state) {
  
}

function veldeke_tools_import_dictionary_form_submit(&$form, &$form_state) {
  $letters = $form_state['values']['letters'];
  variable_set('letters', $letters);
  batch_set(veldeke_tools_import_dictionary($letters));
}
