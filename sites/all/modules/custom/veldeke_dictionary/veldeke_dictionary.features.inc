<?php

/**
 * @file
 * veldeke_dictionary.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function veldeke_dictionary_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_node_info().
 */
function veldeke_dictionary_node_info() {
  $items = array(
    'dictionary_entry' => array(
      'name' => t('Dictionary entry'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  return $items;
}
