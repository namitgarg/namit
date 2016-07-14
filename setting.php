<?php
$file = fopen("sitelist1.txt","r");

while(! feof($file))
  {
  
  $sname[]=fgets($file);
  $sitename=str_replace(array("\r", "\n"), '', $sname);
      
  }
  print("<pre>");
  

fclose($file);
foreach($sitename as $values)
{
//  print($values);
  $namit=htmlspecialchars($values);
  $file1 = "d:\\pageone\\docroot\\sites\\".$values."\\settings.php";
  print($file1);
  print("<br>");
  $current = file_get_contents($file1);
  $new_current=str_replace("# drupal_fast_404();"," drupal_fast_404();",$current,$count);
  if($count==0)
  {
    print("Already modified for $values");
  }
  else
  {
    print("modified settings.php for $values </br>");
  }
  
  file_put_contents($file1, $new_current);
}
//$prefix="git add";
//$output="";
//foreach($sitename as $values)
//{
//  $output=$output." ".$values."/settings.php";
//}
//print($prefix.$output);


?>