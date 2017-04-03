*********************************************************
-----------------------MetaTag Import Export-------------
*********************************************************

Introduction

------------
MetaTag Import Export can be used to import metatags form a CSV file or Export
metatags to a CSV file for node pages.Module supports 4 fields which are
provided by Metatag module.


Description
-----------

* This module has two separate forms for import and export.
   * Export - you can select the content type and a CSV file will be downloaded
              to Your System.

   * Import - Upload the CSV file in the format given in Sample file and 
              metatags will imported with success and error messages.

    * Csv file has 6 fields
	    * Node Title - The node title of the node(optional leave the column
                            empty if you don't have title).
	    * path - The node/nid or the URL Alias for the node.
            * title - The meta title from the Meta tag module.
            * description - The meta description from the Meta tag module.
	    * abstract - The Meta Abstract from the Meta tag module.
	    * keywords - The Meta keywords from the Meta tag module.
	
   * Leave a cell empty if you don't want to change the value of that field.
   
   * Type "_blank" if you want to set a value of any field empty.


Requirements
------------

This module requires the following modules:

 * Metatag (https://www.drupal.org/project/metatag)
 * Chaos tool suite (ctools) (https://www.drupal.org/project/ctools)
 * Token (https://www.drupal.org/project/token)
 * Path (Core)
 * System (Core

Installation & Use
-------------------
* Install as you would normally install a contributed Drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.

Configuration
-------------

* Configure user permissions in Administration >> People >> Permissions:
  * Metatag Import - Select the roles you want to give permission to import 
                     Metatags using the module.
  * Metatag Export - Select the roles you want to give permission to export
                     Metatags using the module.

* Form Page
 * Metatag-import - The form for metatag import can be accessed by 
                    going to /admin/config/search/metatags/import
 * Metatag-export - The form for metatag export can be accessed by 
                    going to /admin/config/search/metatags/export

Drush
------
The module has support for drush command
 * Metatag Export - drush metatag-export <type>
         (file is created on the directory private:://metatag_import_export_csv)
 
* Metatag Import - drush metatag-import < path to your CSV file>
