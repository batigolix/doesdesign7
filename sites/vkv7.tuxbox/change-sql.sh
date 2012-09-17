#!/bin/bash
echo "Hello World"

mysqldump --user=boris --password=themancomesaround vkv7 field_data_body > /home/boris/www/drupal7_a2h/sites/vkv7.tuxbox/field_data_body.sql
find field_data_body.sql -type f -exec sed -i 's/\%\%\%/<hr \/>/g' {} \;
find field_data_body.sql -type f -exec sed -i 's/__(.*?)__/<strong>$1<\/strong>/g' {} \;

#    $body = preg_replace('/\%\%\%/', '<hr />',$body);
#    $body = preg_replace('/__(.*?)__/', '<strong>${1}</strong>',$body);
#    $body = preg_replace('/\*(.*?)\\r/', '<li>$1</li>',$body); 
#    $body = preg_replace('/[\[^img_](.*)\|(.*)\]/', '<a href="${2}">${1}</a>',$body);
#    $body = preg_replace('/\!\!\!(.*?)\\r/', '<h1>${1}</h1>',$body);
#    $body = preg_replace('/\!\!(.*?)\\r/', '<h2>${1}</h2>',$body);
#    $body = preg_replace('/\!(.*?)\\r/', '<h3>${1}</h3>',$body);

mysqlimport --user=boris --password=themancomesaround vkv7 < /home/boris/www/drupal7_a2h/sites/vkv7.tuxbox/field_data_body.sql