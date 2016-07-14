<?php
// Defining a class by using class Class Name
class Books {
  
  /* Member variables are the variables that are defined inside a class and can be used only be a memeber function of the class
   * Here public is the acces specifier
   *  */
  public $price;
// var $price;
  /* above method can also be used to declare a member variable or data memeber
   */
  
  
  /*
   * constructor for the class 
   * You can also declare a constructor by using a class name but this is depreciated in PHP 7
   */
  function __construct() {

    print("namit");
  }

  /* Member functions */

  function setPrice($par) {
    $this->price = $par;
  }

  function getPrice() {
    echo $this->price . "<br/>";
  }

}


/*
 * Inheritance class inherits the memeber function and data member of the parent class
 */
class Homework extends Books {

  public $subject;

  function __construct() {
    print("garg");
    print($this->price);
  }
function set_subject($val1)
{
  $this->subject=$val1;
  
}
function get_subject()
{
  echo $this->subject;
}
}
//intialization of an object the constructor will be call automatically
$physics = new Books;
// calll a meber function of a class
   $physics->setPrice(30);
   $physics->getPrice();
$home = new Homework;
// this is how to call a memeber function of a parent class
$home->setPrice(40);
   
?>