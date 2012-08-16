<?php
/**
 * @file
 * doesdesign.features.inc
 */

/**
 * Implements hook_views_api().
 */
function doesdesign_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function doesdesign_image_default_styles() {
  $styles = array();

  // Exported image style: micro.
  $styles['micro'] = array(
    'name' => 'micro',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '64',
          'height' => '64',
        ),
        'weight' => '1',
      ),
      3 => array(
        'label' => 'Desaturate',
        'help' => 'Desaturate converts an image to grayscale.',
        'effect callback' => 'image_desaturate_effect',
        'dimensions passthrough' => TRUE,
        'module' => 'image',
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: square-thumb.
  $styles['square-thumb'] = array(
    'name' => 'square-thumb',
    'effects' => array(
      5 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '130',
          'height' => '130',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: square-thumb-medium.
  $styles['square-thumb-medium'] = array(
    'name' => 'square-thumb-medium',
    'effects' => array(
      6 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '220',
          'height' => '220',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: x-medium.
  $styles['x-medium'] = array(
    'name' => 'x-medium',
    'effects' => array(
      2 => array(
        'label' => 'Schalen en bijsnijden',
        'help' => 'Bij het schalen blijft de breedte-hoogte verhouding van de oorspronkelijke afbeelding behouden. Bij het bijsnijden wordt de langste zijde ingekort. Hiermee kunt u bijvoorbeeld vierkante miniaturen maken.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '599',
          'height' => '310',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function doesdesign_node_info() {
  $items = array(
    'object' => array(
      'name' => t('Object'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Naam'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => t('If you want to add a static page, like a contact page or an about page, use a page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
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
