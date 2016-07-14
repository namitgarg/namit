<?php

/*
 * Declaring class members or methods as static ma kes them accessible without needing an instantiation of the class.
 *  A member declared as static can not be accessed with an instantiated class object (though a static method can).
 * 
 * Static properties of class is a property which is directly accessible from class with the help of ::(scope resolution operator). 
 *   You can declare static  property using static keyword.
 *  In other word you can make any property static by using static keyword. following is the basic example of static variable in php class:
 */

class Foo {

  public static $my_static = 'foo';

  public function staticValue() {
    return self::$my_static;
  }

}

print Foo::$my_static . "\n";
$foo = new Foo();

print $foo->staticValue() . "\n";



/* Static Methods or functions
  As in general class various process are same for methods and properties,
 *  same is with Static Methods and Properties in PHP. 
 * You can create your function or method static using static keyword.
 *  You can access all visible static methods for you using :: like in static variables.
 * */

class test {

  static function abc($param1, $param2) {
    echo "$param1 , $param2";
  }

}

test::abc("ankur", "techflirt");
?>