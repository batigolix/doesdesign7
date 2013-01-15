<?php
function svv_tools_wiki_fix() {
//  $really_update=FALSE;
  $really_update=TRUE;
  $query = db_select('field_data_body', 'bod');
  $query->addField('bod', 'body_value', 'body_value');
  $query->addField('bod', 'entity_id', 'entity_id');
//  $query->condition('body_value', '%!!%', 'LIKE');
//  $query->range(0, 10);
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
  $count=0;
  foreach($data as $row) { 
    dpm($row);
    $count++;
    $body = $row['body_value'];
	dsm($body);
    $id = $row['entity_id'];
    $body = preg_replace('/__(.*?)__/', '<strong>${1}</strong>',$body);
    $body = preg_replace('/\[(.*?)\|(.*?)\]/', '<a href="${2}">${1}</a>',$body);
    $body = preg_replace('/\%\%\%/', '<hr />',$body);
    $body = preg_replace('/---(.*)---\\r/', '<hr />',$body);
    $body = preg_replace('/\*(.*)\\r/', '<li>$1</li>',$body); 
    $body = preg_replace('/\!\!\!(.*)\\r/', '<h1>${1}</h1>',$body);
    $body = preg_replace('/\!\!(.*)\\r/', '<h2>${1}</h2>',$body);
    $body = preg_replace('/\!([A-Z])(.*)\\r/', '<h3>${1}${2}</h3>',$body);
    $body = preg_replace('/\!(\<a)(.*)\\r/', '<h3>${1}${2}</h3>',$body);
    $body = preg_replace('/\!(\<str)(.*)\\r/', '<h3>${1}${2}</h3>',$body);
    $body = preg_replace('/\{\{\{\\r\\n\}\}\}/', '<br />',$body);
    echo "\n$count #######################################################################\n";
    echo "Entity ID: ${row['entity_id']}\n";
    //$body = addslashes($body);
    dsm($body);
    if ($really_update) {
  	  dsm('lets go');
 	  $orig = node_load($row['entity_id']); // load original'
	  $node=$orig;	
	  //dsm($body);
//      $node->body[$node->language][0]['value'] = $body; // Do some changes
      $node->body['und'][0]['value'] = $body; // Do some changes
      dpm($node);
      node_save($node); // save your changes
	}
  }
  echo "\nEnd ($count entities modified)\n\n";
  return 'doh';
}