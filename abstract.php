<?php
/*
 * Abstract classes are special because they can never be instantiated. 
 * Instead, you typically inherit a set of base functionality from them in a new class.
 *  For that reason, they are commonly used as the base classes in a larger class hierarchy.
 * only abstract classes can hold abstract functions
 */
abstract class Animal
{
    public $name;
    public $age;
    
    public function Describe()
    {
        return $this->name . ", " . $this->age . " years old";    
    }
    
    abstract public function Greet();
}

class Dog extends Animal
{
    public function Greet()
    {
        return "Woof!";    
    }
    
    public function Describe()
    {
      // calls the function of the parent
        return parent::Describe() . ", and I'm a dog!";    
    }
}
$animal = new Dog();
$animal->name = "Bob";
$animal->age = 7;
echo $animal->Describe();
echo $animal->Greet();

?>