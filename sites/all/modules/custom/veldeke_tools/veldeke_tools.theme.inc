<?php

/**
 * @file
 * TODO Auto generated file, add description.
 */

/**
 * Implements hook_theme().
 *
 */
function veldeke_tools_theme() {
  $theme = array();

  $theme['definition_list'] = array(
      'variables' => array(
          'title' => NULL,
          'items' => NULL,
//          'table' => NULL,
//          'pager' => NULL,
      ),
  );

  $theme['definition'] = array(
      'variables' => array(
          'definition' => NULL,
          'misc' => NULL,
      ),
  );

  return $theme;
}
/**
 * 
 * @param type $vars
 * @return string
 */
function theme_definition(&$vars) {
  $output = "<div class='definition'>";
  $output .= "<span class='definition-key'>{$vars['definition']}</span>";
  if (isset($vars['misc'])) {
    $output .= " | <em class='misc'>{$vars['misc']}</em>";
  }
  $output .= '</div>';
  return $output;
}
/**
 * 
 * @param type $vars
 * @return string
 */
function theme_definition_list(&$vars) {
  $title = $vars['title'];
  $items = $vars['items'];
  $output = '<div class="definition-list">';
  if (isset($title)) {
    $output .= '<h3>' . ($filter ? check_plain($title) : $title) . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<dl>";
    foreach ($items as $item) {
      if (is_string($item['term'])) {
        $output .= '  <dt>' . ($filter ? check_plain($item['term']) : $item['term']) . '</dt>';
      } elseif (is_array($item['term'])) {
        foreach ($item['term'] as $term) {
          $output .= '  <dt>' . ($filter ? check_plain($term) : $term) . "</dt>\n";
        }
      }

      if (is_string($item['definitions'])) {
        $output .= '  <dd>' . ($filter ? filter_xss($item['definitions']) : $item['definitions']) . '</dd>';
      } elseif (is_array($item['definitions'])) {
        foreach ($item['definitions'] as $definition) {
          $output .= '  <dd>' . ($filter ? filter_xss($definition) : $definition) . "</dd>\n";
        }
      }
    }
    $output .= "</dl>";
  }
  $output .= '</div>';
  return $output;
}