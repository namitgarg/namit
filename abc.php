<?php

class abc {
  var $name;
  var $age ;
  public function detail($x,$y)
  {
    $this->name=$x;
    $this->age =$y;
}
}

$obj= new abc();
$obj->detail("namit",12);
print_r($obj);
print("nami");
?>