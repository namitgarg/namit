<?php
/*
 * Object interfaces allow you to create code which specifies which methods a class must implement,
 * Without having to define how these methods are handled. 
 * To implement an interface, the implements operator is used. 
 * All methods in the interface must be implemented within a class; failure to do so will result in a fatal error.
 * Classes may implement more than one interface if desired by separating each interface with a comma. 
 */
interface Physics
{

public function quantumn();
  
}
interface Chemistry
{

public function quantumn();
public function periodic();
  
}

class Intermediate implements Physics,Chemistry
{
  
  public function quantumn()
  {
    print("hiiii");
  }
  public function periodic()
  {
    print("byee");
  }
  
  function __Construct()
  {
    print("constructor");
  }
  
}

$obj = new Intermediate;
$obj->quantumn();
$obj->periodic();
?>