<?php
/**
 * @file
 * dd_nieuws.features.inc
 */

/**
 * Implements hook_views_api().
 */
function dd_nieuws_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function dd_nieuws_node_info() {
  $items = array(
    'story' => array(
      'name' => t('Story'),
      'base' => 'node_content',
      'description' => t('Stories are articles in their simplest form: they have a title, a teaser and a body, but can be extended by other modules. The teaser is part of the body too. Stories may be used as a personal blog or for news articles.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
