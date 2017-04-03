<?php 
               $find = array("(", ")", "-", " ");
             $replace = "";
           $phone = str_replace($find, $replace, $output);
				$phone_dial=l($output,'tel:+1'.$phone);
        
        print($phone_dial);
?>
