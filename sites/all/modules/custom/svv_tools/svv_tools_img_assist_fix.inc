<?php

/**
 * PHP script to convert Image Assist Tag into HTML tags.
 * 
 * Drupal 6-to-7 conversion
 *
 * This script must be run on D7 database (after the update from D6 to D7).
 * http://drupal.org/node/841568
 */
function svv_tools_img_assist_fix() {

$really_update = TRUE; # Set this to TRUE to actually run this Drupal 6-to-7 conversion
//  $really_update = FALSE; # Set this to TRUE to actually run this Drupal 6-to-7 conversion

  $query = db_select('field_data_body', 'bod');
  $query->addField('bod', 'body_value', 'body_value');
  $query->addField('bod', 'entity_id', 'entity_id');
  $query->condition('body_value', '%[img_assist%', 'LIKE');
//  $query->condition('n.status', '1');
//  $query->condition('field_date_reservation_value', $start, '>=');
//  $joinCond = 'n.nid = dare.entity_id';
//  $query->join('field_data_field_date_reservation', 'dare', $joinCond);
//  $query->addField('noac', 'field_noderef_activity_nid', 'activity');
  $results = $query->execute();
  drupal_set_message($debug_mode = TRUE ? $query->__toString() : 'f');

  $data = array();
  foreach ($results as $result) {
    $key = $result->entity_id;
    $values = array();
    $values['entity_id'] = $result->entity_id;
    $values['body_value'] = $result->body_value;
    $data[$key] = $values;
  }

  //dpm($data);
  $count = 0;

  foreach ($data as $row) {
    //dpm($row);
    $body = $row['body_value'];
    $count++;
    dsm("\n$count ###### {$row['entity_id']} ################## ###############################################\n");
    //dsm("Entity ID: ${row['entity_id']}\n");
    $pattern = "/\[img_assist(?:\\\\|\\\]|[^\]])*\]/"; # See http://rubular.com/r/gQs5HjGLok
    preg_match($pattern, $body, $matches, PREG_OFFSET_CAPTURE); # NB: The PREG_OFFSET_CAPTURE gives us the offset_in_tmp variable.
    foreach ($matches as $image_marker) {
      list($img, $offset_in_tmp) = $image_marker;
      //dsm("Img: $img \n");
      // Strip off the first and last character - they are [ and ].
      $img_pieces = preg_replace("/^\[(.*)\]$/", '${1}', $img);
      //dsm("Img w/o brackets: $img_pieces \n");
      dpm($img_pieces);
      // The dollar-underscore variable is a junk collector
      // Here, the first item is the img_assist piece
      $pieces = explode("|", $img_pieces);
      //dpm($pieces);
      $image = array();
      foreach ($pieces as $piece) {
        $piece2 = explode("=", $piece);
        //dpm($piece2);
        $image[$piece2[0]] = (!empty($piece2[1]) ? $piece2[1] : '');
      }
      //dpm($image);

      $query = db_select('image', 'img');
      $query->addField('img', 'fid', 'fid');
      $query->addField('fil', 'filepath', 'filepath');
      $query->condition('img.nid', $image['nid']);
      $query->condition('filename', '_original');
//      $query->condition('filepath', '%preview%', 'NOT LIKE');
//      $query->condition('filepath', '%img_assist_properties%', 'NOT LIKE');
      $joinCond = 'img.fid = fil.fid';
      $query->join('files', 'fil', $joinCond);
      $results = $query->execute();
      //drupal_set_message($debug_mode = TRUE ? $query->__toString() : 'f');
      foreach ($results as $result) {
        //dpm($result);

        $img_path = $result->filepath;
        
        $image2 = image_get_info($result->filepath);
        //dpm($image2); 
        
        if (!empty($image['align'])) {
          $align2 = "float: {$image['align']};";
        }
        if (!isset($image['title'])) {
          $image['title'] = ' ';
        }
        if (!empty($image['desc'])) {
          $desc = $image['title'];
        }
        $image['title'] = str_replace('"', "", $image['title']);
        $image['title'] = str_replace("'", "", $image['title']);
        $image_tag = "<img alt=\"{$image['desc']}\" title=\"{$image['title']}\" src=\"/{$result->filepath}\" style=\"width:{$image2['width']}px; height:{$image2['height']}px;\">";
        dsm($image_tag);
        print($image_tag);
        $body = str_replace($img, $image_tag, $body);
      }
    }
    if ($really_update) {
      $orig = node_load($row['entity_id']); // load original'
      $node = $orig;
      dsm($body);
      $node->body[$node->language][0]['value'] = $body; // Do some changes
      dpm($node);
      node_save($node); // save your changes
    }
  }
  $output = "\nEnd ($count entities modified)\n\n";
  return $output;
}