<?php

class Books {
public $subject;
private $teacher;
protected  $course;

public function get_subject($sub_name)
{
  $this->subject=$sub_name;
}
public function show_subject()
{
  print($this->subject);
}

private function get_teacher($teacher_name)
{
  $this->teacher=$teacher_name;
}
private function show_teacher()
{
  print($this->teacher);
}

protected function get_course($course_name)
{
  $this->course=$course_name;
}
protected function show_course()
{
  print($this->course);
}

}

$book_obj= new Books;
$book_obj->get_subject("english");
$book_obj->show_subject();
$book_obj->get_course("pronoun");
$book_obj->show_course();
//$bank_obj->get_teacher("ansh");
//$bank_obj->show_teacher();

class Homework extends Books {
  
}
   
?>