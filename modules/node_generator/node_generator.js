(function($) {
    Drupal.behaviors.node_generator = {
        'attach': function(context) {
            $('#edit-select-content-type', context).change(function(e) {
                var th = $(this); 
                $(th).parents("#-node-generator-input-form").find("#edit-category-field").html("");   
                $(th).parents("#-node-generator-input-form").find("#edit-tag-field").html("");   
                
                $.getJSON(Drupal.settings.basePath+'getfield/'+$(this).val(), function(obj) {
                    var options="<option selected='selected' value=''>Please select</option>";
                    $.each(obj, function(key, value){
                        options+='<option value="' + key + '">' + value + '</option>'; 
                    });
                    $(th).parents("#-node-generator-input-form").find("#edit-category-field").html(options);
                    $(th).parents("#-node-generator-input-form").find("#edit-tag-field").html(options);
                });			
                e.stopImmediatePropagation();
                return false;
            });
        }
    }
})(jQuery);