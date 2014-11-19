<?php
/**
 * @file
 * veldeke_dictionary.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function veldeke_dictionary_taxonomy_default_vocabularies() {
  return array(
    'dialects' => array(
      'name' => 'Dialecten',
      'machine_name' => 'dialects',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
