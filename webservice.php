<?php
print("namit");
 $request_url = 'http://192.168.0.162/site2/nodeapi/node';
  // User data
  $user_data = array(
    'username' => 'kellton',
    'password' => 'password123',
  );
  $user_data = http_build_query($user_data);
  // cURL
  $curl = curl_init($request_url);
  curl_setopt($curl, CURLOPT_HTTPHEADER, array('Accept: application/json')); // Accept JSON response
  curl_setopt($curl, CURLOPT_POST, 1); // Do a regular HTTP POST
  curl_setopt($curl, CURLOPT_POSTFIELDS, $user_data); // Set POST data
  curl_setopt($curl, CURLOPT_HEADER, FALSE);  // Ask to not return Header
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($curl, CURLOPT_FAILONERROR, TRUE);

  $response = curl_exec($curl);
  $http_code = curl_getinfo($curl, CURLINFO_HTTP_CODE);
  // Check if login was successful
  if ($http_code == 200) {
    // Convert json response as array
    $logged_user = json_decode($response);
  }
  else {
    // Get error msg
    $http_message = curl_error($curl);
    die($http_message);
  }
print("<pre>");
  print_r(json_decode($response));
  
?>
