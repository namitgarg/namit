<?php
$options  = array (
  'http' => 
  array (
    'ignore_errors' => true,
    'header' => 
    array (
      0 => 'authorization: Bearer YOUR_API_TOKEN',
    ),
  ),
);
 
$context  = stream_context_create( $options );
$response = file_get_contents(
    'https://public-api.wordpress.com/rest/v1/sites/82974409/users',
    false,
    $context
);
$response = json_decode( $response );
print_r($response);
?>