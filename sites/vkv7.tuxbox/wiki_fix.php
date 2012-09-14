<?php
/**
 * PHP script to convert wiki formatting to html
 * This script must be run on D7 database (after the update from D6 to D7).
 */


$server = "localhost";
$login = "boris";
$password = "themancomesaround";
$database = "vkv7";
$prefix = '';
$really_update = FALSE; # Set this to TRUE to actually run this Drupal 6-to-7 conversion
//$really_update = TRUE; # Set this to TRUE to actually run this Drupal 6-to-7 conversion

///////////////////////////////////////////////////////////////////////////////////////////////////

$link = mysql_connect($server, $login, $password) or die("Connect error : " . mysql_error());
echo "Connect OK\n";

$db_selected = mysql_select_db($database, $link);
if (!$db_selected)
   die ('Select DB error : ' . mysql_error());

$query = "SELECT * FROM ${prefix}field_data_body WHERE body_format = 4";
$result = mysql_query($query);
if (!$result) {
    $message  = 'Query error : ' . mysql_error() . "\n";
    $message .= 'Query : ' . $query;
    die($message);
}

$count=0;
while ($row = mysql_fetch_assoc($result)) 
{
    $count++;
    // echo $tmp;
    // echo "\n###############################################################################\n";

//    $pattern = "/\[img_assist(?:\\\\|\\\]|[^\]])*\]/"; # See http://rubular.com/r/gQs5HjGLok
//    preg_match($pattern, $tmp, $matches, PREG_OFFSET_CAPTURE); # NB: The PREG_OFFSET_CAPTURE gives us the offset_in_tmp variable.
    
    $body = $row['body_value'];
    $id = $row['entity_id'];
    $body = preg_replace('/\%\%\%/', '<hr />',$body);
    $body = preg_replace('/__(.*?)__/', '<strong>${1}</strong>',$body);
    $body = preg_replace('/\*(.*?)\\r/', '<li>$1</li>',$body); 
    $body = preg_replace('/\[[^img_](.*)\|(.*)\]/', '<a href="${2}">${1}</a>',$body);
    $body = preg_replace('/\!\!\!(.*?)\\r/', '<h3>${1}</h3>',$body);
    $body = preg_replace('/\!\!(.*?)\\r/', '<h2>${1}</h2>',$body);
    $body = preg_replace('/\!(.*?)\\r/', '<h1>${1}</h1>',$body);
    echo "\n$count #######################################################################\n";
    echo "Entity ID: ${row['entity_id']}\n";
//        echo "match: "; print_r($match); echo "######### \n";
    echo "Body: $body \n";

    if ($really_update) {
      $update_query = "UPDATE ${prefix}field_data_body SET body_value = '${body}' WHERE entity_id = " . $id;
     echo $update_query;
      mysql_query($update_query);
    }

/*    if ($really_update) {
        $update_query = "UPDATE ${prefix}field_data_body SET body_value = " . $body . "WHERE entity_id = " . $id;
        $res = mysql_query($update_query);
    
        if (!$res) {
            $message  = 'Query error : ' . mysql_error() . "\n";
            $message .= 'Query : ' . $update_query;
            die($message);
        }
    }
*/
//    foreach ($matches as $match) {
//        list($img, $offset_in_tmp) = $match;
        //        $tmp = $match;
        
/*        // Strip off the first and last character - they are [ and ].
        $img_pieces = preg_replace("/^\[(.*)\]$/", '${1}', $img);
        echo "Img w/o brackets: $img_pieces \n";

        // The dollar-underscore variable is a junk collector
        // Here, the first item is the img_assist piece
        list($_, $nid, $title, $desc, $link_img, $align, $width, $height) = explode("|", $img_pieces);
        
        list($_, $nid) = explode('=', $nid, 2);
        list($_, $title) = explode('=', $title, 2);
        list($_, $desc) = explode('=', $desc, 2);
        list($_, $link_img) = explode('=', $link_img, 2);
        list($_, $align) = explode('=', $align, 2);
        list($_, $width) = explode('=', $width, 2);
        list($_, $height) = explode('=', $height, 2);
        
        echo "NID: $nid \n";
        
        $query_image = "SELECT * FROM ${prefix}image WHERE nid=".$nid;
        $result_image = mysql_query($query_image);
        
        $row_image = mysql_fetch_assoc($result_image);
        $fid = $row_image['fid'];
        
        echo "FID: $fid \n";
        
        $query_file = "SELECT * FROM ${prefix}files WHERE fid=".$fid;
        $result_file = mysql_query($query_file);
        
        $row_file = mysql_fetch_assoc($result_file);
        $img_path = $row_file['filepath'];
        
        if ($img_path[0] != '/')  
            $img_path = '/' . $img_path;
        
        echo "Src: $img_path \n";
        
        $image_tag = "<img alt=\"$desc\" src=\"$img_path\" style=\"width: ".$width."px; height: ".$height."px;\">";

        $tmp = str_replace($img, $image_tag, $tmp);
        
        mysql_free_result($result_image);
    }
*/    
    // break; // Test
}// End : while ($row = mysql_fetch_assoc($result)) 
  mysql_free_result($result);

  mysql_close($link);

echo "\nEnd ($count entities modified)\n\n";
