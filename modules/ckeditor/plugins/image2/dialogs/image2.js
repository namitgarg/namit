/**
 * @license Copyright (c) 2003-2015, CKSource - Frederico Knabben. All rights reserved.
 * For licensing, see LICENSE.md or http://ckeditor.com/license
 */

/**
 * @fileOverview Image plugin based on Widgets API
 */

////'use strict';

CKEDITOR.dialog.add('image2', function(editor) {

    // RegExp: 123, 123px, empty string ""
    var regexGetSizeOrEmpty = /(^\s*(\d+)(px)?\s*$)|^$/i,
            lockButtonId = CKEDITOR.tools.getNextId(),
            resetButtonId = CKEDITOR.tools.getNextId(),
            lang = editor.lang.image2,
            commonLang = editor.lang.common,
            lockResetStyle = 'margin-top:18px;width:40px;height:20px;',
            lockResetHtml = new CKEDITOR.template(
                    '<div>' +
                    '<a href="javascript:void(0)" tabindex="-1" title="' + lang.lockRatio + '" class="cke_btn_locked" id="{lockButtonId}" role="checkbox">' +
                    '<span class="cke_icon"></span>' +
                    '<span class="cke_label">' + lang.lockRatio + '</span>' +
                    '</a>' +
                    '<a href="javascript:void(0)" tabindex="-1" title="' + lang.resetSize + '" class="cke_btn_reset" id="{resetButtonId}" role="button">' +
                    '<span class="cke_label">' + lang.resetSize + '</span>' +
                    '</a>' +
                    '</div>').output({
        lockButtonId: lockButtonId,
        resetButtonId: resetButtonId
    }),
    helpers = CKEDITOR.plugins.image2,
            // Editor instance configuration.
            config = editor.config,
            // Content restrictions defined by the widget which
            // impact on dialog structure and presence of fields.
            features = editor.widgets.registered.image.features,
            // Functions inherited from image2 plugin.
            getNatural = helpers.getNatural,
            // Global variables referring to the dialog's context.
            doc, widget, image,
            // Global variable referring to this dialog's image pre-loader.
            preLoader,
            // Global variables holding the original size of the image.
            domWidth, domHeight,
            // Global variables related to image pre-loading.
            preLoadedWidth, preLoadedHeight, srcChanged,
            // Global variables related to size locking.
            lockRatio, userDefinedLock,
            // Global variables referring to dialog fields and elements.
            lockButton, resetButton, widthField, heightField,
            natural;

    // Validates dimension. Allowed values are:
    // "123px", "123", "" (empty string)
    function validateDimension() {
        var match = this.getValue().match(regexGetSizeOrEmpty),
                isValid = !!(match && parseInt(match[1], 10) !== 0);

        if (!isValid)
            alert(commonLang['invalid' + CKEDITOR.tools.capitalize(this.id)]); // jshint ignore:line

        return isValid;
    }

    // Creates a function that pre-loads images. The callback function passes
    // [image, width, height] or null if loading failed.
    //
    // @returns {Function}
    function createPreLoader() {
        var image = doc.createElement('img'),
                listeners = [];

        function addListener(event, callback) {
            listeners.push(image.once(event, function(evt) {
                removeListeners();
                callback(evt);
            }));
        }

        function removeListeners() {
            var l;

            while ((l = listeners.pop()))
                l.removeListener();
        }

        // @param {String} src.
        // @param {Function} callback.
        return function(src, callback, scope) {
            addListener('load', function() {
                // Don't use image.$.(width|height) since it's buggy in IE9-10 (#11159)
                var dimensions = getNatural(image);

                callback.call(scope, image, dimensions.width, dimensions.height);
            });

            addListener('error', function() {
                callback(null);
            });

            addListener('abort', function() {
                callback(null);
            });

            image.setAttribute('src', (config.baseHref || '') + src + '?' + Math.random().toString(16).substring(2));
        };
    }

    // This function updates width and height fields once the
    // "src" field is altered. Along with dimensions, also the
    // dimensions lock is adjusted.
    function onChangeSrc() {
        var value = this.getValue();

        toggleDimensions(false);

        // Remember that src is different than default.
        if (value !== widget.data.src) {
            // Update dimensions of the image once it's preloaded.
            preLoader(value, function(image, width, height) {
                // Re-enable width and height fields.
                toggleDimensions(true);

                // There was problem loading the image. Unlock ratio.
                if (!image)
                    return toggleLockRatio(false);

                // Fill width field with the width of the new image.
                widthField.setValue(width);

                // Fill height field with the height of the new image.
                heightField.setValue(height);

                // Cache the new width.
                preLoadedWidth = width;

                // Cache the new height.
                preLoadedHeight = height;

                // Check for new lock value if image exist.
                toggleLockRatio(helpers.checkHasNaturalRatio(image));
            });

            srcChanged = true;
        }

        // Value is the same as in widget data but is was
        // modified back in time. Roll back dimensions when restoring
        // default src.
        else if (srcChanged) {
            // Re-enable width and height fields.
            toggleDimensions(true);

            // Restore width field with cached width.
            widthField.setValue(domWidth);

            // Restore height field with cached height.
            heightField.setValue(domHeight);

            // Src equals default one back again.
            srcChanged = false;
        }

        // Value is the same as in widget data and it hadn't
        // been modified.
        else {
            // Re-enable width and height fields.
            toggleDimensions(true);
        }
    }

    function onChangeDimension() {
        // If ratio is un-locked, then we don't care what's next.
        if (!lockRatio)
            return;

        var value = this.getValue();

        // No reason to auto-scale or unlock if the field is empty.
        if (!value)
            return;

        // If the value of the field is invalid (e.g. with %), unlock ratio.
        if (!value.match(regexGetSizeOrEmpty))
            toggleLockRatio(false);

        // No automatic re-scale when dimension is '0'.
        if (value === '0')
            return;

        var isWidth = this.id == 'width',
                // If dialog opened for the new image, domWidth and domHeight
                // will be empty. Use dimensions from pre-loader in such case instead.
                width = domWidth || preLoadedWidth,
                height = domHeight || preLoadedHeight;

        // If changing width, then auto-scale height.
        if (isWidth)
            value = Math.round(height * (value / width));

        // If changing height, then auto-scale width.
        else
            value = Math.round(width * (value / height));

        // If the value is a number, apply it to the other field.
        if (!isNaN(value))
            (isWidth ? heightField : widthField).setValue(value);
    }

    // Set-up function for lock and reset buttons:
    // 	* Adds lock and reset buttons to focusables. Check if button exist first
    // 	  because it may be disabled e.g. due to ACF restrictions.
    // 	* Register mouseover and mouseout event listeners for UI manipulations.
    // 	* Register click event listeners for buttons.
    function onLoadLockReset() {
        var dialog = this.getDialog();

        function setupMouseClasses(el) {
            el.on('mouseover', function() {
                this.addClass('cke_btn_over');
            }, el);

            el.on('mouseout', function() {
                this.removeClass('cke_btn_over');
            }, el);
        }

        // Create references to lock and reset buttons for this dialog instance.
        lockButton = doc.getById(lockButtonId);
        resetButton = doc.getById(resetButtonId);

        // Activate (Un)LockRatio button
        if (lockButton) {
            // Consider that there's an additional focusable field
            // in the dialog when the "browse" button is visible.
            dialog.addFocusable(lockButton, 4 + hasFileBrowser);

            lockButton.on('click', function(evt) {
                toggleLockRatio();
                evt.data && evt.data.preventDefault();
            }, this.getDialog());

            setupMouseClasses(lockButton);
        }

        // Activate the reset size button.
        if (resetButton) {
            // Consider that there's an additional focusable field
            // in the dialog when the "browse" button is visible.
            dialog.addFocusable(resetButton, 5 + hasFileBrowser);

            // Fills width and height fields with the original dimensions of the
            // image (stored in widget#data since widget#init).
            resetButton.on('click', function(evt) {
                // If there's a new image loaded, reset button should revert
                // cached dimensions of pre-loaded DOM element.
                if (srcChanged) {
                    widthField.setValue(preLoadedWidth);
                    heightField.setValue(preLoadedHeight);
                }

                // If the old image remains, reset button should revert
                // dimensions as loaded when the dialog was first shown.
                else {
                    widthField.setValue(domWidth);
                    heightField.setValue(domHeight);
                }

                evt.data && evt.data.preventDefault();
            }, this);

            setupMouseClasses(resetButton);
        }
    }

    function toggleLockRatio(enable) {
        // No locking if there's no radio (i.e. due to ACF).
        if (!lockButton)
            return;

        if (typeof enable == 'boolean') {
            // If user explicitly wants to decide whether
            // to lock or not, don't do anything.
            if (userDefinedLock)
                return;

            lockRatio = enable;
        }

        // Undefined. User changed lock value.
        else {
            var width = widthField.getValue(),
                    height;

            userDefinedLock = true;
            lockRatio = !lockRatio;

            // Automatically adjust height to width to match
            // the original ratio (based on dom- dimensions).
            if (lockRatio && width) {
                height = domHeight / domWidth * width;

                if (!isNaN(height))
                    heightField.setValue(Math.round(height));
            }
        }

        lockButton[lockRatio ? 'removeClass' : 'addClass']('cke_btn_unlocked');
        lockButton.setAttribute('aria-checked', lockRatio);

        // Ratio button hc presentation - WHITE SQUARE / BLACK SQUARE
        if (CKEDITOR.env.hc) {
            var icon = lockButton.getChild(0);
            icon.setHtml(lockRatio ? CKEDITOR.env.ie ? '\u25A0' : '\u25A3' : CKEDITOR.env.ie ? '\u25A1' : '\u25A2');
        }
    }

    function toggleDimensions(enable) {
        var method = enable ? 'enable' : 'disable';

        widthField[method]();
        heightField[method]();
    }

    var hasFileBrowser = !!(config.filebrowserImageBrowseUrl || config.filebrowserBrowseUrl),
            srcBoxChildren = [{
                    id: 'src',
                    type: 'text',
                    label: commonLang.url,
                    onKeyup: onChangeSrc,
                    onChange: onChangeSrc,
                    setup: function(widget) {
                        this.setValue(widget.data.src);
                    },
                    commit: function(widget) {
                        widget.setData('src', this.getValue());
                    },
                    validate: CKEDITOR.dialog.validate.notEmpty(lang.urlMissing)
                }];

    // Render the "Browse" button on demand to avoid an "empty" (hidden child)
    // space in dialog layout that distorts the UI.
    if (hasFileBrowser) {
        srcBoxChildren.push({
            type: 'button',
            id: 'browse',
            // v-align with the 'txtUrl' field.
            // TODO: We need something better than a fixed size here.
            style: 'display:inline-block;margin-top:14px;',
            align: 'center',
            label: editor.lang.common.browseServer,
            hidden: true,
            filebrowser: 'info:src'
        });
    }

    return {
        title: lang.title,
        minWidth: 250,
        minHeight: 100,
        onLoad: function() {
            // Create a "global" reference to the document for this dialog instance.
            doc = this._.element.getDocument();

            // Create a pre-loader used for determining dimensions of new images.
            preLoader = createPreLoader();
        },
        onShow: function() {
            // Create a "global" reference to edited widget.
            widget = this.widget;

            // Create a "global" reference to widget's image.
            image = widget.parts.image;

            // Reset global variables.
            srcChanged = userDefinedLock = lockRatio = false;

            // Natural dimensions of the image.
            natural = getNatural(image);

            // Get the natural width of the image.
            preLoadedWidth = domWidth = natural.width;

            // Get the natural height of the image.
            preLoadedHeight = domHeight = natural.height;
        },
        contents: [{
                id: 'info',
                label: lang.infoTab,
                elements: [{
                        type: 'vbox',
                        padding: 0,
                        children: [{
                                type: 'hbox',
                                widths: ['100%'],
                                children: srcBoxChildren
                            }]
                    }, {
                        id: 'alt',
                        type: 'text',
                        label: lang.alt,
                        setup: function(widget) {
                            this.setValue(widget.data.alt);
                        },
                        commit: function(widget) {
                            widget.setData('alt', this.getValue());
                        }
                    }, {
                        type: 'hbox',
                        widths: ['25%', '25%', '50%'],
                        requiredContent: features.dimension.requiredContent,
                        children: [{
                                type: 'text',
                                width: '45px',
                                id: 'width',
                                label: commonLang.width,
                                validate: validateDimension,
                                onKeyUp: onChangeDimension,
                                onLoad: function() {
                                    widthField = this;
                                },
                                setup: function(widget) {
                                    this.setValue(widget.data.width);
                                },
                                commit: function(widget) {
                                    widget.setData('width', this.getValue());
                                }
                            }, {
                                type: 'text',
                                id: 'height',
                                width: '45px',
                                label: commonLang.height,
                                validate: validateDimension,
                                onKeyUp: onChangeDimension,
                                onLoad: function() {
                                    heightField = this;
                                },
                                setup: function(widget) {
                                    this.setValue(widget.data.height);
                                },
                                commit: function(widget) {
                                    widget.setData('height', this.getValue());
                                }
                            }, {
                                id: 'lock',
                                type: 'html',
                                style: lockResetStyle,
                                onLoad: onLoadLockReset,
                                setup: function(widget) {
                                    toggleLockRatio(widget.data.lock);
                                },
                                commit: function(widget) {
                                    widget.setData('lock', lockRatio);
                                },
                                html: lockResetHtml
                            }]
                    },
                    // Code commented by ISHWAR    
//                    {
//                        type: 'hbox',
//                        id: 'alignment',
//                        requiredContent: features.align.requiredContent,
//                        children: [{
//                                id: 'align',
//                                type: 'radio',
//                                items: [
//                                    [commonLang.alignNone, 'none'],
//                                    [commonLang.alignLeft, 'left'],
//                                    [commonLang.alignCenter, 'center'],
//                                    [commonLang.alignRight, 'right']
//                                ],
//                                label: commonLang.align,
//                                setup: function(widget) {
//                                    this.setValue(widget.data.align);
//                                },
//                                commit: function(widget) {
//                                    widget.setData('align', this.getValue());
//                                }
//                            }]
//                    }, 
                    // End code commented by ISWHAR  



                    // Code added by ISHWAR for custom class 


                    {
                        type: 'hbox',
                        id: 'customclassaddon',
                        children: [{
                                id: 'customclassaddonfield',
                                type: 'select',
                                items: [
                                    ['None', 'defaultimage'],
                                    ['Left Image', 'leftimage'],
                                    ['Center Image', 'centerimage'],
                                    ['Right Image', 'rightimage']
                                ],
                                label: 'Add Class',
                                setup: function(e) {

                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                   // Below line I have written for setting the default value 
                                    e.data.customclassaddonfield = 'defaultimage';  // If no any value selected
   
   
                                    if (i(e.element.$.attributes.class, "value")) {
                                        var styleClass = e.element.$.attributes.class.value;
                                        var styleClassArray = styleClass.trim().split(' ');
                                        for (var chunkofStyleClassArray in styleClassArray) {
                                            var selectedStyle = styleClassArray[chunkofStyleClassArray].trim();
                                            if (selectedStyle == 'image') {
                                                // No action                                                    
                                            }
                                            else if (selectedStyle == 'cke_widget_element') {
                                                // No action
                                            } else {
                                              e.data.customclassaddonfield = selectedStyle;
                                            }
                                        }
                                    }

                                    this.setValue(e.data.customclassaddonfield);

                                },
                                commit: function(t) {
                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                    // This condition is added for when user have not selected any class from Dropdown
                                    if (!this.getValue()) {
                                        t.setData("customclassaddonfield", 'defaultimage')
                                        t.element.addClass('defaultimage');
                                    }

                                    if (this.getValue() || this.isChanged()) {
                                        //console.log(t);
                                        if (i(t.element.$.attributes.class, "value")) {
                                            var styleClass = t.element.$.attributes.class.value;
                                            var styleClassArray = styleClass.trim().split(' ');
                                            for (var chunkofStyleClassArray in styleClassArray) {
                                                var selectedStyle = styleClassArray[chunkofStyleClassArray].trim();
                                                if (selectedStyle == 'image') {
                                                    // No action if caption is ON
                                                    if (!t.data.hasCaption) {
                                                        t.element.removeClass(selectedStyle);
                                                    }
                                                }
                                                else if (selectedStyle == 'cke_widget_element') {
                                                    // No action
                                                } else {
                                                   t.element.removeClass(selectedStyle);
                                                }
                                            }
                                        }
                                    }
                                    (this.getValue() || this.isChanged()) && t.setData("customclassaddonfield", this.getValue(), t.element.addClass(this.getValue()))
                                }
                            }]
                    },
                    // End code added  by ISHWAR for custom class



                    {
                        id: 'hasCaption',
                        type: 'checkbox',
                        label: lang.captioned,
                        requiredContent: features.caption.requiredContent,
                        setup: function(widget) {
                            this.setValue(widget.data.hasCaption);
                        },
                        commit: function(widget) {
                            widget.setData('hasCaption', this.getValue());
                        }
                    },
                    // Code start for three custom field by Ishwar

                    // Code added for the padding custom field for padding top, right, bottom, left

                    {
                        type: 'hbox',
                        title: 'Padding',
                        widths: ['25%', '25%', '25%', '25%'],
                        children: [
                            {
                                type: "text",
                                label: "Padding Top",
                                "default": "0",
                                id: "paddingtop",
                                validate: CKEDITOR.dialog.validate.integer('Padding top for Image field must have integer value.'),
                                setup: function(e) {
                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                    if (i(e.element.$.attributes.style, "value")) {
                                        var a = e.element.$.attributes.style.value,
                                                n = a.split(";");
                                        for (var t in n) {   // Started traversing the value of the array
                                            var l = n[t].trim().split(":");
                                            if ("padding" == l[0]) {
                                                var o = l[1].trim().split(" ");
                                                switch (o.length) {  // Getting the length of an array and switch for multiple cases
                                                    case 4:
                                                        e.data.paddingtop = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    case 3:
                                                        e.data.paddingtop = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    case 2:
                                                        e.data.paddingtop = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    case 1:
                                                        e.data.paddingtop = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    default:
                                                        // No action taken if any other value is comming instead of padding
                                                        break;

                                                }
                                            }
                                            // If individually padding-top is comming then below mentioned line will handle 
                                            if ("padding-top" == l[0]) {
                                                var o = l[1].trim().replace("px", "");
                                                e.data.paddingtop = o
                                            }
                                        }  // End the traversing the array for processing DOM element
                                    }

                                    this.setValue(e.data.paddingtop)
                                },
                                commit: function(t) {
                                    (this.getValue() || this.isChanged()) && t.setData("paddingtop", this.getValue(), t.element.setStyle("padding-top", this.getValue() + "px"))
                                    if (!this.getValue()) {
                                        t.element.removeStyle("padding-top");
                                    }

                                }
                            },
                            {
                                type: "text",
                                label: "Padding Right",
                                "default": "0",
                                id: "paddingright",
                                validate: CKEDITOR.dialog.validate.integer('Padding right for Image field must have integer value.'),
                                setup: function(e) {

                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                    if (i(e.element.$.attributes.style, "value")) {
                                        var a = e.element.$.attributes.style.value,
                                                n = a.split(";");
                                        for (var t in n) {   // Started traversing the value of the array
                                            var l = n[t].trim().split(":");
                                            if ("padding" == l[0]) {
                                                var o = l[1].trim().split(" ");
                                                switch (o.length) {  // Getting the length of an array and switch for multiple cases
                                                    case 4:
                                                        e.data.paddingright = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 3:
                                                        e.data.paddingright = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 2:
                                                        e.data.paddingright = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 1:
                                                        e.data.paddingright = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    default:
                                                        // No action taken if any other value is comming instead of padding
                                                        break;
                                                }
                                            }

                                            // If individually padding-right is comming then below mentioned line will handle 

                                            if ("padding-right" == l[0]) {
                                                var o = l[1].trim().replace("px", "");
                                                e.data.paddingright = o
                                            }
                                        }  // End the traversing the array for processing DOM element
                                    }

                                    this.setValue(e.data.paddingright)
                                },
                                commit: function(t) {
                                    (this.getValue() || this.isChanged()) && t.setData("paddingright", this.getValue(), t.element.setStyle("padding-right", this.getValue() + "px"))
                                    if (!this.getValue()) {
                                        t.element.removeStyle("padding-right");
                                    }

                                }
                            },
                            {
                                type: "text",
                                label: "Padding Bottom",
                                "default": "0",
                                id: "paddingbottom",
                                validate: CKEDITOR.dialog.validate.integer('Padding bottom for Image field must have integer value.'),
                                setup: function(e) {

                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                    if (i(e.element.$.attributes.style, "value")) {
                                        var a = e.element.$.attributes.style.value,
                                                n = a.split(";");
                                        for (var t in n) {   // Started traversing the value of the array
                                            var l = n[t].trim().split(":");
                                            if ("padding" == l[0]) {
                                                var o = l[1].trim().split(" ");
                                                switch (o.length) {  // Getting the length of an array and switch for multiple cases
                                                    case 4:
                                                        e.data.paddingbottom = i(o, "2") ? o[2].trim().replace("px", "") : o[2].trim().replace("px", "")
                                                        break;
                                                    case 3:
                                                        e.data.paddingbottom = i(o, "2") ? o[2].trim().replace("px", "") : o[2].trim().replace("px", "")
                                                        break;
                                                    case 2:
                                                        e.data.paddingbottom = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    case 1:
                                                        e.data.paddingbottom = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    default:
                                                        // No action taken if any other value is comming instead of padding
                                                        break;
                                                }
                                            }
                                            // If individually padding-bottom is comming then below mentioned line will handle 

                                            if ("padding-bottom" == l[0]) {
                                                var o = l[1].trim().replace("px", "");
                                                e.data.paddingbottom = o
                                            }
                                        }  // End the traversing the array for processing DOM element
                                    }

                                    this.setValue(e.data.paddingbottom)
                                },
                                commit: function(t) {
                                    (this.getValue() || this.isChanged()) && t.setData("paddingbottom", this.getValue(), t.element.setStyle("padding-bottom", this.getValue() + "px"))
                                    if (!this.getValue()) {
                                        t.element.removeStyle("padding-bottom");
                                    }

                                }
                            },
                            {
                                type: "text",
                                label: "Padding Left",
                                "default": "0",
                                id: "paddingleft",
                                validate: CKEDITOR.dialog.validate.integer('Padding left for Image field must have integer value.'),
                                setup: function(e) {

                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                    if (i(e.element.$.attributes.style, "value")) {
                                        var a = e.element.$.attributes.style.value,
                                                n = a.split(";");
                                        for (var t in n) {   // Started traversing the value of the array
                                            var l = n[t].trim().split(":");
                                            if ("padding" == l[0]) {
                                                var o = l[1].trim().split(" ");
                                                switch (o.length) {  // Getting the length of an array and switch for multiple cases
                                                    case 4:
                                                        e.data.paddingleft = i(o, "3") ? o[3].trim().replace("px", "") : o[3].trim().replace("px", "")
                                                        break;
                                                    case 3:
                                                        e.data.paddingleft = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 2:
                                                        e.data.paddingleft = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 1:
                                                        e.data.paddingleft = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    default:
                                                        // No action taken if any other value is comming instead of padding
                                                        break;
                                                }
                                            }
                                            // If individually padding-left is comming then below mentioned line will handle 

                                            if ("padding-left" == l[0]) {
                                                var o = l[1].trim().replace("px", "");
                                                e.data.paddingleft = o
                                            }
                                        }  // End the traversing the array for processing DOM element
                                    }

                                    this.setValue(e.data.paddingleft)
                                },
                                commit: function(t) {
                                    (this.getValue() || this.isChanged()) && t.setData("paddingleft", this.getValue(), t.element.setStyle("padding-left", this.getValue() + "px"))
                                    if (!this.getValue()) {
                                        t.element.removeStyle("padding-left");
                                    }

                                }
                            },
                        ]
                    },
                    // Code added for the  custom field for margin top, right, bottom, left

                    {
                        type: 'hbox',
                        title: 'Margin',
                        widths: ['25%', '25%', '25%', '25%'],
                        children: [
                            {
                                type: "text",
                                label: "Margin Top",
                                "default": "0",
                                id: "margintop",
                                validate: CKEDITOR.dialog.validate.integer('Margin top for Image field must have integer value.'),
                                setup: function(e) {
                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                    if (i(e.element.$.attributes.style, "value")) {
                                        var a = e.element.$.attributes.style.value,
                                                n = a.split(";");
                                        for (var t in n) {   // Started traversing the value of the array
                                            var l = n[t].trim().split(":");
                                            if ("margin" == l[0]) {
                                                var o = l[1].trim().split(" ");
                                                switch (o.length) {  // Getting the length of an array and switch for multiple cases
                                                    case 4:
                                                        e.data.margintop = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    case 3:
                                                        e.data.margintop = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    case 2:
                                                        e.data.margintop = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    case 1:
                                                        e.data.margintop = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    default:
                                                        // No action taken if any other value is comming instead of padding
                                                        break;

                                                }
                                            }
                                            // If individually margin-top is comming then below mentioned line will handle 
                                            if ("margin-top" == l[0]) {
                                                var o = l[1].trim().replace("px", "");
                                                e.data.margintop = o
                                            }
                                        }  // End the traversing the array for processing DOM element
                                    }

                                    this.setValue(e.data.margintop)
                                },
                                commit: function(t) {
                                    (this.getValue() || this.isChanged()) && t.setData("margintop", this.getValue(), t.element.setStyle("margin-top", this.getValue() + "px"))
                                    if (!this.getValue()) {
                                        t.element.removeStyle("margin-top");
                                    }

                                }
                            },
                            {
                                type: "text",
                                label: "Margin Right",
                                "default": "0",
                                id: "marginright",
                                validate: CKEDITOR.dialog.validate.integer('Margin right for Image field must have integer value.'),
                                setup: function(e) {

                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                    if (i(e.element.$.attributes.style, "value")) {
                                        var a = e.element.$.attributes.style.value,
                                                n = a.split(";");
                                        for (var t in n) {   // Started traversing the value of the array
                                            var l = n[t].trim().split(":");
                                            if ("margin" == l[0]) {
                                                var o = l[1].trim().split(" ");
                                                switch (o.length) {  // Getting the length of an array and switch for multiple cases
                                                    case 4:
                                                        e.data.marginright = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 3:
                                                        e.data.marginright = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 2:
                                                        e.data.marginright = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 1:
                                                        e.data.marginright = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    default:
                                                        // No action taken if any other value is comming instead of padding
                                                        break;
                                                }
                                            }

                                            // If individually margin-right is comming then below mentioned line will handle 

                                            if ("margin-right" == l[0]) {
                                                var o = l[1].trim().replace("px", "");
                                                e.data.marginright = o
                                            }
                                        }  // End the traversing the array for processing DOM element
                                    }

                                    this.setValue(e.data.marginright)
                                },
                                commit: function(t) {
                                    (this.getValue() || this.isChanged()) && t.setData("marginright", this.getValue(), t.element.setStyle("margin-right", this.getValue() + "px"))
                                    if (!this.getValue()) {
                                        t.element.removeStyle("margin-right");
                                    }

                                }
                            },
                            {
                                type: "text",
                                label: "Margin Bottom",
                                "default": "0",
                                id: "marginbottom",
                                validate: CKEDITOR.dialog.validate.integer('Margin bottom for Image field must have integer value.'),
                                setup: function(e) {

                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                    if (i(e.element.$.attributes.style, "value")) {
                                        var a = e.element.$.attributes.style.value,
                                                n = a.split(";");
                                        for (var t in n) {   // Started traversing the value of the array
                                            var l = n[t].trim().split(":");
                                            if ("margin" == l[0]) {
                                                var o = l[1].trim().split(" ");
                                                switch (o.length) {  // Getting the length of an array and switch for multiple cases
                                                    case 4:
                                                        e.data.marginbottom = i(o, "2") ? o[2].trim().replace("px", "") : o[2].trim().replace("px", "")
                                                        break;
                                                    case 3:
                                                        e.data.marginbottom = i(o, "2") ? o[2].trim().replace("px", "") : o[2].trim().replace("px", "")
                                                        break;
                                                    case 2:
                                                        e.data.marginbottom = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    case 1:
                                                        e.data.marginbottom = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    default:
                                                        // No action taken if any other value is comming instead of padding
                                                        break;
                                                }
                                            }
                                            // If individually margin-bottom is comming then below mentioned line will handle 

                                            if ("margin-bottom" == l[0]) {
                                                var o = l[1].trim().replace("px", "");
                                                e.data.marginbottom = o
                                            }
                                        }  // End the traversing the array for processing DOM element
                                    }

                                    this.setValue(e.data.marginbottom)
                                },
                                commit: function(t) {
                                    (this.getValue() || this.isChanged()) && t.setData("marginbottom", this.getValue(), t.element.setStyle("margin-bottom", this.getValue() + "px"))
                                    if (!this.getValue()) {
                                        t.element.removeStyle("margin-bottom");
                                    }

                                }
                            },
                            {
                                type: "text",
                                label: "Margin Left",
                                "default": "0",
                                id: "marginleft",
                                validate: CKEDITOR.dialog.validate.integer('Margin left for Image field must have integer value.'),
                                setup: function(e) {

                                    function i(t, e) {
                                        if ("object" != typeof t || null == t)
                                            return !1;
                                        for (var i = e.split("."); i.length; ) {
                                            var a = i.shift();
                                            if (!(a in t))
                                                return !1;
                                            t = t[a]
                                        }
                                        return !0
                                    }

                                    if (i(e.element.$.attributes.style, "value")) {
                                        var a = e.element.$.attributes.style.value,
                                                n = a.split(";");
                                        for (var t in n) {   // Started traversing the value of the array
                                            var l = n[t].trim().split(":");
                                            if ("margin" == l[0]) {
                                                var o = l[1].trim().split(" ");
                                                switch (o.length) {  // Getting the length of an array and switch for multiple cases
                                                    case 4:
                                                        e.data.marginleft = i(o, "3") ? o[3].trim().replace("px", "") : o[3].trim().replace("px", "")
                                                        break;
                                                    case 3:
                                                        e.data.marginleft = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 2:
                                                        e.data.marginleft = i(o, "1") ? o[1].trim().replace("px", "") : o[1].trim().replace("px", "")
                                                        break;
                                                    case 1:
                                                        e.data.marginleft = i(o, "0") ? o[0].trim().replace("px", "") : o[0].trim().replace("px", "")
                                                        break;
                                                    default:
                                                        // No action taken if any other value is comming instead of padding
                                                        break;
                                                }
                                            }
                                            // If individually margin-left is comming then below mentioned line will handle 

                                            if ("margin-left" == l[0]) {
                                                var o = l[1].trim().replace("px", "");
                                                e.data.marginleft = o
                                            }
                                        }  // End the traversing the array for processing DOM element
                                    }

                                    this.setValue(e.data.marginleft)
                                },
                                commit: function(t) {
                                    (this.getValue() || this.isChanged()) && t.setData("marginleft", this.getValue(), t.element.setStyle("margin-left", this.getValue() + "px"))
                                    if (!this.getValue()) {
                                        t.element.removeStyle("margin-left");
                                    }

                                }
                            },
                        ]
                    }




                    // Code end for three custom field by Ishwar


                ]
            }, {
                id: 'Upload',
                hidden: true,
                filebrowser: 'uploadButton',
                label: lang.uploadTab,
                elements: [{
                        type: 'file',
                        id: 'upload',
                        label: lang.btnUpload,
                        style: 'height:40px'
                    }, {
                        type: 'fileButton',
                        id: 'uploadButton',
                        filebrowser: 'info:src',
                        label: lang.btnUpload,
                        'for': ['Upload', 'upload']
                    }]
            }]
    };
});


CKEDITOR.on('dialogDefinition', function(ev) {
    // Take the dialog name and its definition from the event data.
    var dialogName = ev.data.name;
    var dialogDefinition = ev.data.definition;


    // **************************************
    // IMAGE DIALOG
    // **************************************
    if (dialogName == 'image') {

        // **************************************
        // IMAGE INFO TAB
        // **************************************
        var imageInfoTab = dialogDefinition.getContents('info');

        // remove the hspace and vspace fields
        /////  imageInfoTab.remove('txtHSpace');
        //////   imageInfoTab.remove('txtVSpace');

        // setup constants and other vars (recreating some functionality)
        var IMAGE = 1,
                LINK = 2,
                PREVIEW = 4,
                CLEANUP = 8,
                regexGetSize = /^\s*(\d+)((px)|\%)?\s*$/i,
                regexGetSizeOrEmpty = /(^\s*(\d+)((px)|\%)?\s*$)|^$/i,
                pxLengthRegex = /^\d+px$/;

        // function to update preview
        var updatePreview = function(dialog) {
            //Don't load before onShow.
            if (!dialog.originalElement || !dialog.preview)
                return 1;

            // Read attributes and update imagePreview;
            dialog.commitContent(PREVIEW, dialog.preview);
            return 0;
        };

        // function to commit changes internally

        // Avoid recursions.
        var incommit;

        // Synchronous field values to other impacted fields is required, e.g. border
        // size change should alter inline-style text as well.
        function commitInternally(targetFields) {
            if (incommit)
                return;

            incommit = 1;

            var dialog = this.getDialog(),
                    element = dialog.imageElement;
            if (element) {
                // Commit this field and broadcast to target fields.
                this.commit(IMAGE, element);

                targetFields = [].concat(targetFields);
                var length = targetFields.length,
                        field;
                for (var i = 0; i < length; i++) {
                    field = dialog.getContentElement.apply(dialog, targetFields[i].split(':'));
                    // May cause recursion.
                    field && field.setup(IMAGE, element);
                }
            }

            incommit = 0;
        }

        // new margin fields
        imageInfoTab.add({
            type: 'fieldset',
            label: 'Margins',
            children: [{
                    type: 'vbox',
                    padding: 1,
                    width: '100px',
                    label: 'Margins',
                    align: 'center',
                    children: [
                        // margin-top
                        {
                            type: 'text',
                            id: 'txtMarginTop',
                            width: '40px',
                            labelLayout: 'horizontal',
                            label: 'Top',
                            'default': '',
                            onKeyUp: function() {
                                updatePreview(this.getDialog());
                            },
                            onChange: function() {
                                commitInternally.call(this, 'advanced:txtdlgGenStyle');
                            },
                            validate: CKEDITOR.dialog.validate.integer(ev.editor.lang.image.validateVSpace),
                            setup: function(type, element) {
                                if (type == IMAGE) {
                                    var value,
                                            marginTopPx,
                                            marginTopStyle = element.getStyle('margin-top');

                                    marginTopStyle = marginTopStyle && marginTopStyle.match(pxLengthRegex);
                                    marginTopPx = parseInt(marginTopStyle, 10);
                                    value = marginTopPx;
                                    isNaN(parseInt(value, 10)) && (value = element.getAttribute('vspace'));

                                    this.setValue(value);
                                }
                            },
                            commit: function(type, element, internalCommit) {
                                var value = parseInt(this.getValue(), 10);
                                if (type == IMAGE || type == PREVIEW) {
                                    if (!isNaN(value)) {
                                        element.setStyle('margin-top', CKEDITOR.tools.cssLength(value));
                                    } else if (!value && this.isChanged()) {
                                        element.removeStyle('margin-top');
                                    }

                                    if (!internalCommit && type == IMAGE)
                                        element.removeAttribute('vspace');
                                } else if (type == CLEANUP) {
                                    element.removeAttribute('vspace');
                                    element.removeStyle('margin-top');
                                }
                            }
                        }, // end margin-top

                        // margin-right
                        {
                            type: 'text',
                            id: 'txtMarginRight',
                            width: '40px',
                            labelLayout: 'horizontal',
                            label: 'Right',
                            'default': '',
                            onKeyUp: function() {
                                updatePreview(this.getDialog());
                            },
                            onChange: function() {
                                commitInternally.call(this, 'advanced:txtdlgGenStyle');
                            },
                            validate: CKEDITOR.dialog.validate.integer(ev.editor.lang.image.validateHSpace),
                            setup: function(type, element) {
                                if (type == IMAGE) {
                                    var value,
                                            marginRightPx,
                                            marginRightStyle = element.getStyle('margin-right');

                                    marginRightStyle = marginRightStyle && marginRightStyle.match(pxLengthRegex);
                                    marginRightPx = parseInt(marginRightStyle, 10);
                                    value = marginRightPx;
                                    isNaN(parseInt(value, 10)) && (value = element.getAttribute('hspace'));

                                    this.setValue(value);
                                }
                            },
                            commit: function(type, element, internalCommit) {
                                var value = parseInt(this.getValue(), 10);
                                if (type == IMAGE || type == PREVIEW) {
                                    if (!isNaN(value)) {
                                        element.setStyle('margin-right', CKEDITOR.tools.cssLength(value));
                                    } else if (!value && this.isChanged()) {
                                        element.removeStyle('margin-right');
                                    }

                                    if (!internalCommit && type == IMAGE)
                                        element.removeAttribute('hspace');
                                } else if (type == CLEANUP) {
                                    element.removeAttribute('hspace');
                                    element.removeStyle('margin-right');
                                }
                            }
                        }, // end margin-right

                        // margin-bottom
                        {
                            type: 'text',
                            id: 'txtMarginBottom',
                            width: '40px',
                            labelLayout: 'horizontal',
                            label: 'Bottom',
                            'default': '',
                            onKeyUp: function() {
                                updatePreview(this.getDialog());
                            },
                            onChange: function() {
                                commitInternally.call(this, 'advanced:txtdlgGenStyle');
                            },
                            validate: CKEDITOR.dialog.validate.integer(ev.editor.lang.image.validateVSpace),
                            setup: function(type, element) {
                                if (type == IMAGE) {
                                    var value,
                                            marginBottomPx,
                                            marginBottomStyle = element.getStyle('margin-bottom');

                                    marginBottomStyle = marginBottomStyle && marginBottomStyle.match(pxLengthRegex);
                                    marginBottomPx = parseInt(marginBottomStyle, 10);
                                    value = marginBottomPx;
                                    isNaN(parseInt(value, 10)) && (value = element.getAttribute('vspace'));

                                    this.setValue(value);
                                }
                            },
                            commit: function(type, element, internalCommit) {
                                var value = parseInt(this.getValue(), 10);
                                if (type == IMAGE || type == PREVIEW) {
                                    if (!isNaN(value)) {
                                        element.setStyle('margin-bottom', CKEDITOR.tools.cssLength(value));
                                    } else if (!value && this.isChanged()) {
                                        element.removeStyle('margin-bottom');
                                    }

                                    if (!internalCommit && type == IMAGE)
                                        element.removeAttribute('vspace');
                                } else if (type == CLEANUP) {
                                    element.removeAttribute('vspace');
                                    element.removeStyle('margin-bottom');
                                }
                            }
                        }, // end margin-bottom

                        // margin-left
                        {
                            type: 'text',
                            id: 'txtMarginLeft',
                            width: '40px',
                            labelLayout: 'horizontal',
                            label: 'Left',
                            'default': '',
                            onKeyUp: function() {
                                updatePreview(this.getDialog());
                            },
                            onChange: function() {
                                commitInternally.call(this, 'advanced:txtdlgGenStyle');
                            },
                            validate: CKEDITOR.dialog.validate.integer(ev.editor.lang.image.validateHSpace),
                            setup: function(type, element) {
                                if (type == IMAGE) {
                                    var value,
                                            marginLeftPx,
                                            marginLeftStyle = element.getStyle('margin-left');

                                    marginLeftStyle = marginLeftStyle && marginLeftStyle.match(pxLengthRegex);
                                    marginLeftPx = parseInt(marginLeftStyle, 10);
                                    value = marginLeftPx;
                                    isNaN(parseInt(value, 10)) && (value = element.getAttribute('hspace'));

                                    this.setValue(value);
                                }
                            },
                            commit: function(type, element, internalCommit) {
                                var value = parseInt(this.getValue(), 10);
                                if (type == IMAGE || type == PREVIEW) {
                                    if (!isNaN(value)) {
                                        element.setStyle('margin-left', CKEDITOR.tools.cssLength(value));
                                    } else if (!value && this.isChanged()) {
                                        element.removeStyle('margin-left');
                                    }

                                    if (!internalCommit && type == IMAGE)
                                        element.removeAttribute('hspace');
                                } else if (type == CLEANUP) {
                                    element.removeAttribute('hspace');
                                    element.removeStyle('margin-left');
                                }
                            }
                        } // end margin-left
                    ]
                }

            ]

        }, 'txtBorder');

        // this syntax chokes in Safari and others (I think "default" is reserved)
        //imageInfoTab.get('txtBorder').default = '0';

        // this syntax works...
        // set default border to zero
        var imageTxtBorder = imageInfoTab.get('txtBorder');
        imageTxtBorder['default'] = '0';

    }

});