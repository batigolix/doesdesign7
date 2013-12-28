<?php

/**
 * @file
 * TODO Auto generated file, add description.
 */

/**
 * Returns project page
 * @return string
 */
function veldeke_tools_composition($page_type) {
  $output = '';
  $stubs = array();
  $v = taxonomy_vocabulary_machine_name_load('page_type');
  if ($v) {
    if ($page_type == 'Project') {
      $term = veldeke_tools_get_term('Project', 'page_type'); // get term object for page type project
      $view_mode = 'full';
    } elseif ($page_type == 'Maison veldeke') {
      $term = veldeke_tools_get_term('Maison veldeke', 'page_type'); // get term object for page type project
      $view_mode = 'jumbo_teaser';
    }
    $nodes = _fetch_nodes_by_field(array('field' => 'field_page_type', 'column' => 'tid', 'value' => $term->tid, 'bundle' => 'page'));
    $i = 1;
    if (isset($nodes)) {
      foreach ($nodes as $node) {
        $node->class[] = veldeke_tools_ordinal($i);
        $node->class[] = $i % 2 ? 'odd' : 'even';
        if ($i == 1) {
          $node->class[] = 'first';
        }
        if ($i == count($nodes)) {
          $node->class[] = 'last';
        }
        $node->class[] = veldeke_tools_slugify($node->title);
        $node_view = node_view($node, $view_mode);
        $stubs[] = array(
            'html' => drupal_render($node_view),
        );
        $i++;
      }
      $variables = array(
          'stubs' => $stubs,
          'name' => $page_type,
      );
      $output .= theme('composition_page', $variables);
    } else {
      drupal_set_message('No content of the page type "@type" found', 'error', array('@type' => $page_type));
    }
  } else {
    drupal_set_message('The taxonomy Page type does not exist', 'error');
  }
  return $output;
}

/**
 * Returns project page
 * @return string
 */
function veldeke_tools_test() {


  $num_deleted = db_delete('veldeke_dictionary')
          ->execute();

  dsm($num_deleted . ' terms deleted');

  //https://docs.google.com/spreadsheet/pub?key=0AgLDdff6gGPwdHJBOXJoU3FEMERzUDZ4Wk96WU1OOEE&single=true&gid=0&output=csv
  $csv_file = 'https://docs.google.com/spreadsheet/pub?key=0AgLDdff6gGPwdHJBOXJoU3FEMERzUDZ4Wk96WU1OOEE&single=true&gid=0&output=csv';
  $terms = veldeke_tools_fetch_data($csv_file);
  unset($terms[0]); // header csv
  dpm($terms);

  foreach ($terms as $term) {
    dpm($term);
    try {
      $id = db_insert('veldeke_dictionary')
              ->fields(array(
                  'updated' => $term[1],
                  'dtid' => $term[0],
                  'nl_term' => $term[2],
                  'li_term' => $term[3],
                  'misc' => $term[4],
//    'created' => REQUEST_TIME,
              ))
              ->execute();
      dsm($id);
    } catch (Exception $e) {
      dsm($e);
    }
  }

  $query = db_insert('veldeke_dictionary')->fields(array('dtid', 'nl_term', 'li_term', 'misc'));
  foreach ($terms as $record) {
    $query->values($record);
  }
  $query->execute();

//  foreach($terms as $term) {
//        $now = time();
//        dsm($now);
//        $update = strtotime($term[1]); // end date of event as unix timestamp
//
//        dsm($update);
//
//                  try {
//                    
//                    $id = db_insert('veldeke_dictionary')
//  ->fields(array(
//    'title' => 'Example',
//    'uid' => 1,
//    'created' => REQUEST_TIME,
//  ))
//  ->execute();
//                    
//            // store data in database
//            db_merge('veldeke_dictionary')
//                    ->key(array('dtid' => $fap->Id))
//                    ->fields(array(
//                        'ft_rxid' => $ft_rxid,
//                        'fa_rxid' => $fa_rxid,
//                        'fp_rxid' => $fp_rxid,
//                        'sa_eid' => $sa_eid,
//                        'ac_eid' => $ac_eid,
//                        'maximum' => $fap->Maximum,
//                        'capacity_check' => $fap->CapacityCheck,
//                        'capacity_type' => $fap->CapacityType,
//                        'start' => $fap->From,
//                        'end' => $fap->Until,
//                        'available' => $fap->Available,
//                        'maximum_per_group' => $fa->FileActivity->MaxPeoplePerGroup,
//                        'message' => 'Updated: ' . date("Y-m-d H:i:s"), // 2001-03-10 17:16:18 // TO DO; Dont do this, it is awful
//                    ))
//                    ->execute();
//            (variable_get('debug_mode') == 1 ? drupal_set_message("Slot {$fap->Id} created") : '');
//            $i++;
//          } catch (Exception $e) {
//            $problem = TRUE;
//          }
//
//        
//        
//  }
//            // get current date to exclude slots that have passed
//        $now = time();
//        $end_date = strtotime($fap->Until); // end date of event as unix timestamp
//        (variable_get('debug_mode') == 1 ? dsm($now) : '');
//        (variable_get('debug_mode') == 1 ? dsm($end_date) : '');
//        if ($end_date > $now) { // exclude past slots
//          try {
//            // store data in database
//            db_merge('slots')
//                    ->key(array('rxid' => $fap->Id))
//                    ->fields(array(
//                        'ft_rxid' => $ft_rxid,
//                        'fa_rxid' => $fa_rxid,
//                        'fp_rxid' => $fp_rxid,
//                        'sa_eid' => $sa_eid,
//                        'ac_eid' => $ac_eid,
//                        'maximum' => $fap->Maximum,
//                        'capacity_check' => $fap->CapacityCheck,
//                        'capacity_type' => $fap->CapacityType,
//                        'start' => $fap->From,
//                        'end' => $fap->Until,
//                        'available' => $fap->Available,
//                        'maximum_per_group' => $fa->FileActivity->MaxPeoplePerGroup,
//                        'message' => 'Updated: ' . date("Y-m-d H:i:s"), // 2001-03-10 17:16:18 // TO DO; Dont do this, it is awful
//                    ))
//                    ->execute();
//            (variable_get('debug_mode') == 1 ? drupal_set_message("Slot {$fap->Id} created") : '');
//            $i++;
//          } catch (Exception $e) {
//            $problem = TRUE;
//          }


  $output = 'test';
  return $output;
}

/**
 * Returns contact page
 * @return string
 */
function veldeke_tools_export() {
  
$output = '';

  $query = db_select('node', 'n');
  $query->condition('n.status', 1);
  $query->condition('n.type', 'book');
  $query->condition('n.title', 'Waord met%', 'LIKE');
  $query->addField('n', 'title');
  $query->join('field_data_body', 'fdb', 'n.nid = fdb.entity_id');
  $query->condition('fdb.bundle', 'book');
  $query->addField('fdb', 'body_value', 'body');
//  $query->range(0, 3);
//    
  $results = $query->execute();
  $num_rows = $query->countQuery()->execute()->fetchField();
  drupal_set_message($num_rows);
//
  foreach($results as $result) {
//    dpm($result);
    $output .= $result->body;
    
  }
//
  
  $output = preg_replace('/<h3>(.*?)<\/h3>/i', '', $output);
  $output = preg_replace('/<h2>(.*?)<\/h2>/i', '', $output);
  $output = preg_replace('/<dt>(.*?)<\/dt>(.*?)<dd>(.*?)<\/dd>/i', '$1;$3 <br/>', $output);
  
return $output;
}

/**
 * Prepare data for the property detail page
 * @param type $propid
 * @return type
 */
function veldeke_tools_property_detail_page($propid) {

  $vars['building_nav'] = veldeke_tools_building_nav();

  $imgpath = drupal_get_path('module', 'veldeke_tools') . '/images/';

  // fetch single property details from csv
  $properties = _get_properties();
  foreach ($properties as $key => $property) {
    if ($property[0] == $propid) {
      $result_property = $property;
    }
  }

  // slugify data
  $floor = veldeke_tools_slugify($result_property[6]);
  $code = veldeke_tools_slugify($result_property[1]);

  // set title
  $title = $result_property[1] . ' - ' . $result_property[2] . ' - ' . $result_property[6];
  drupal_set_title($title);

  // define images
  $property_img_path = $imgpath . 'property/' . $result_property[1] . '.png';
  if (file_exists($property_img_path)) {
    $vars['property_img'] = theme_image(array(
        'path' => $property_img_path,
        'alt' => t('Property'),
        'attributes' => array('class' => 'property'),
            )
    );
  } else {
    $vars['property_img'] = '<p>' . t('No property image available') . '</p>';
  }

  $floor_img_path = $imgpath . 'floor/' . $code . '.png';
  if (file_exists($floor_img_path)) {
    $vars['floor_img'] = theme_image(array(
        'path' => $floor_img_path,
        'alt' => t('Floor'),
        'attributes' => array('class' => 'floor'),
            )
    );
  } else {
    $vars['floor_img'] = '<p>' . t('No floor image available') . '</p>';
  }

  $building_img_path = $imgpath . 'building/picture.jpg';
  if (file_exists($building_img_path)) {
    $vars['building_img'] = theme_image(array(
        'path' => $building_img_path,
        'alt' => t('Building'),
        'attributes' => array('class' => 'building'),
            ));
  } else {
    $vars['building_img'] = '<p>' . t('No building image available') . '</p>';
  }

  // define symbols block
  $vars['symbols'] = veldeke_tools_symbols(); // symbols html (= legend for property layout)
  // define details 'block'. display field values in an item list
  $details = array();
  $details[] = array('label' => t('Type'), 'value' => $result_property[2]);
  $details[] = array('label' => t('Floor'), 'value' => $result_property[6]);
  $details[] = array('label' => t('Bedrooms'), 'value' => $result_property[5]);
  $details[] = array('label' => t('Surface appartment'), 'value' => number_format($result_property[3], 2, ',', '.') . ' m²');
  //$details[] = array('label' => t('Surface garden'), 'value' => number_format($result_property[6], 2, ',', '.') . ' m²',);
  $details[] = array('label' => t('Surface terrace'), 'value' => number_format($result_property[4], 2, ',', '.') . ' m²',);
  $details[] = array('label' => t('Orientation'), 'value' => $result_property[7]);
  $details[] = array('label' => t('Cellar'), 'value' => $result_property[8]);
  $details[] = array('label' => t('Parking'), 'value' => $result_property[9]);
  //$details[] = array('label' => t('Price'), 'value' => number_format($result_property[12], 0, ',', '.') . ' € * ' . t('Cellar included'));
  $items = array();
  foreach ($details as $detail) {
    $items[] = array(
        'data' => "<strong>{$detail['label']}</strong>{$detail['value']}",
    );
  }
  $vars['details'] = theme('item_list', array('items' => $items, 'type' => 'ul'));

  // define contact us button
  $vars['contact_us_link'] = l(t('Contact us'), 'contact', array('query' => array('subject' => $title), 'attributes' => array('class' => 'button big')));

  // define link to file & labeling
  $path = drupal_get_path('module', 'veldeke_tools') . '/files/property-details/';
  $file = $path . $result_property[1] . '.pdf';
  $file_location = file_create_url($file);
  //      $file = $abs_file = realpath($file);
  //      $vars['file_size'] = format_size(filesize($file));
  $vars['download_link'] = l('<i class="icon-pdf"></i>' . t('Download floorplan'), $file_location, array('html' => true, 'attributes' => array('class' => array('download-pdf'))));

  $vars['code'] = $result_property[1];
  $output = theme('property_detail_page', $vars);
  return $output;
}

/**
 * 
 */
function veldeke_tools_building() {
  return theme('building_page', $vars);
}

/**
 * 
 */
function veldeke_tools_terms($lang='nl',$letter='a') {
  $path = drupal_get_path('module','veldeke_tools');
  drupal_add_css($path.'/css/veldeke_tools.css');
  $output = '';
  $output .= veldeke_tools_lang_nav($letter);
  $type = 'ul';
  $attributes = array(
      'class' => 'az-browser',
  );
  $items = array();
  foreach (range('A', 'Z') as $char) {
  $items[] = array('data' => l($char, 'terms/'.$lang.'/'.$char));
  }
  $output .= theme('item_list', array('items' => $items, 'title' => 'Browse', 'type' => $type, 'attributes' => $attributes));

  $terms = veldeke_tools_fetch_terms($lang,$letter);
  $alfa = array_shift(array_values($terms));
  $omega = end($terms);
  $count = count($terms);
  $title = t('From !alfa to !omega', array('!alfa' => $alfa['term'], '!omega' => $omega['term']));
  $output .= theme('definition_list', array('title' => $title, 'items' => $terms));
  return $output;
}