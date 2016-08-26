<?php

//make http request
$response = file_get_contents('https://www.googleapis.com/language/translate/v2?key=INSERT-YOUR-KEY&q=hello%20world&source=en&target=de');

//decode json to array
$json = json_decode($response);

//show the json array in a readable format
echo '<pre>';

//show array
print_r($json);

?>