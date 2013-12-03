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
function veldeke_tools_contact_page() {
  $output = '';

  // get contact details
  $cont_vars = _contact_data();
  $cont_vars['mode'] = 'large';
  $cont_vars['info_label'] = t('Information documentation');

  // get contact webform
  $alias = "contact_form";
  $path = drupal_lookup_path("source", $alias);
  $node = menu_get_object("node", 1, $path);
  $webform = 'webform_client_form_' . $node->nid;
  $submission = (object) array();
  $enabled = TRUE;
  $preview = FALSE;
  $contact_form = drupal_get_form($webform, $node, $submission, $enabled, $preview);

  // prepare data for theme functions
  $vars['contact_form'] = drupal_render($contact_form);
  $vars['contact_details'] = theme('contact_details', $cont_vars);

  // print & return page using theme_contact_page
  $output = theme('contact_page', $vars);
  return $output;
}

/**
 * Returns HTML for the expositions table
 * Soratble, pageable, filterable drupal table without db query
 * http://drupal.stackexchange.com/questions/14889/can-tablesort-be-used-without-a-query
 */
function veldeke_tools_properties_page() {
  include_once 'veldeke_tools.forms.inc';
  $vars['building_nav'] = veldeke_tools_building_nav();

  // fetch data
  // csv structure #;Code;Code2;Type;Surf prop;Surf terr/balc;Surf gard;Bedrooms;Floor;Orientation;Cellar;Garage;price;Building;Status
  $table_data = array();
  $properties = _get_properties();
  unset($properties[0]); // remove header
  foreach ($properties as $property) {
    $table_data[] = array(
        'propid' => $property[0],
        'code' => $property[1],
        // 'code2' => $property[1],
        'type' => $property[2],
        'surface_property' => $property[3],
        'surface_terrace' => $property[4],
        // 'surface_garden' => $property[1],
        'bedrooms' => $property[5],
        'floor' => $property[6],
        'orientation' => $property[7],
        'cellar' => $property[8],
        'garage' => $property[9],
        // 'price' => $property[12],
        // 'building' => $property[12],
        'status' => $property[10],
            // 'type' => $property[14],
    );
  }

  // if filter already set, filter the array
  if (isset($_SESSION['form_values']['bedrooms']) && $_SESSION['form_values']['bedrooms'] < 998) {
    $table_data = _filter_table_array($table_data, 'bedrooms', $_SESSION['form_values']['bedrooms'], '==');
  }
  if (isset($_SESSION['form_values']['surface']) && $_SESSION['form_values']['surface'] > 0) {
    $table_data = _filter_table_array($table_data, 'surface_property', $_SESSION['form_values']['surface'], '>=');
  }
//  if (isset($_SESSION['form_values']['price']) && $_SESSION['form_values']['price'] != 0) {
//    $table_data = _filter_table_array($table_data, 'price', $_SESSION['form_values']['price'], '<=');
//  }
  // headers array, sorting by default on country
  $headers = array(
      array('data' => t('Ref.')),
      array('data' => t('Floor')),
      array('data' => t('Bedroom(s)')),
      array('data' => t('Property (m2)')),
      array('data' => t('Terrace (m2)')),
          //array('data' => t('Price(eur)')),
  );

  // getting the current sort and order parameters from the url
  // $order = tablesort_get_order($headers);
  // $sort = tablesort_get_sort($headers);
  // sort the table data
  // $table_data = _sort_table_array($table_data, $order['sql'], $sort);
  // create the array with rows for theme table
  $rows = array();
  foreach ($table_data as $entry) {
    //$price = ($entry['status'] == 'Sold' ? t('Sold') : number_format($entry['price'], 0, ',', '.'));
    $rowclass = ($entry['status'] == 'Sold' ? 'sold' : 'not-sold');
    $ref = ($entry['status'] == 'Sold' ? $entry['code'] : l($entry['code'], 'property/' . $entry['propid']));

    $rows[] = array(
        'data' => array(
            array('data' => $ref),
            array('data' => $entry['floor']),
            array('data' => $entry['bedrooms']),
            array('data' => $entry['surface_property']),
            array('data' => $entry['surface_terrace']),
        //array('data' => $price),
        ),
        'class' => array($rowclass),
    );
  }
  /*  */

  // add any attributes and send everything to theme table
  $attributes = array('class' => array('property'));

  // generate filter form
  $filter = drupal_get_form('veldeke_tools_properties_filter_form');
  $vars['filter'] = drupal_render($filter);

  // generate table
  $table = array('header' => $headers, 'attributes' => $attributes, 'rows' => $rows, 'sticky' => FALSE);
  $vars['table'] = theme('table', $table);

  // generate & return page
  $output = theme('properties_page', $vars);
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
  $output = '';
    $type = 'ul';
  $attributes = array(
      'class' => 'symbols',
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