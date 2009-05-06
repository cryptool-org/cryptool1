class mx.core.UIObject extends MovieClip
{
    var _width, _height, _x, _y, _parent, __get__width, __get__height, _minHeight, __get__minHeight, _minWidth, __get__minWidth, _visible, dispatchEvent, __get__visible, _xscale, __get__scaleX, _yscale, __get__scaleY, methodTable, onEnterFrame, tfList, __width, __height, moveTo, lineTo, createTextField, attachMovie, buildDepthTable, findNextAvailableDepth, idNames, childrenCreated, _name, createAccessibilityImplementation, _endInit, validateNow, hasOwnProperty, _loc2, initProperties, stylecache, className, ignoreClassStyleDeclaration, _tf, fontFamily, fontSize, color, marginLeft, marginRight, fontStyle, fontWeight, textAlign, textIndent, textDecoration, embedFonts, styleName, enabled, __get__bottom, __get__left, __set__minHeight, __set__minWidth, __get__right, __set__scaleX, __set__scaleY, __get__top, __set__visible, __get__x, __get__y;
    function UIObject()
    {
        super();
        this.constructObject();
    } // End of the function
    function get width()
    {
        return (_width);
    } // End of the function
    function get height()
    {
        return (_height);
    } // End of the function
    function get left()
    {
        return (_x);
    } // End of the function
    function get x()
    {
        return (_x);
    } // End of the function
    function get top()
    {
        return (_y);
    } // End of the function
    function get y()
    {
        return (_y);
    } // End of the function
    function get right()
    {
        //return (_parent.width - (_x + this.width()));
    } // End of the function
    function get bottom()
    {
        //return (_parent.height - (_y + this.height()));
    } // End of the function
    function getMinHeight(Void)
    {
        return (_minHeight);
    } // End of the function
    function setMinHeight(h)
    {
        _minHeight = h;
    } // End of the function
    function get minHeight()
    {
        return (this.getMinHeight());
    } // End of the function
    function set minHeight(h)
    {
        this.setMinHeight(h);
        //return (this.minHeight());
        null;
    } // End of the function
    function getMinWidth(Void)
    {
        return (_minWidth);
    } // End of the function
    function setMinWidth(w)
    {
        _minWidth = w;
    } // End of the function
    function get minWidth()
    {
        return (this.getMinWidth());
    } // End of the function
    function set minWidth(w)
    {
        this.setMinWidth(w);
        //return (this.minWidth());
        null;
    } // End of the function
    function setVisible(x, noEvent)
    {
        if (x != _visible)
        {
            _visible = x;
            if (noEvent != true)
            {
                this.dispatchEvent({type: x ? ("reveal") : ("hide")});
            } // end if
        } // end if
    } // End of the function
    function get visible()
    {
        return (_visible);
    } // End of the function
    function set visible(x)
    {
        this.setVisible(x, false);
        //return (this.visible());
        null;
    } // End of the function
    function get scaleX()
    {
        return (_xscale);
    } // End of the function
    function set scaleX(x)
    {
        _xscale = x;
        //return (this.scaleX());
        null;
    } // End of the function
    function get scaleY()
    {
        return (_yscale);
    } // End of the function
    function set scaleY(y)
    {
        _yscale = y;
        //return (this.scaleY());
        null;
    } // End of the function
    function doLater(obj, fn)
    {
        if (methodTable == undefined)
        {
            methodTable = new Array();
        } // end if
        methodTable.push({obj: obj, fn: fn});
        onEnterFrame = doLaterDispatcher;
    } // End of the function
    function doLaterDispatcher(Void)
    {
        delete this.onEnterFrame;
        if (invalidateFlag)
        {
            this.redraw();
        } // end if
        var _loc3 = methodTable;
        methodTable = new Array();
        if (_loc3.length > 0)
        {
            var _loc2;
            while (_loc2 = _loc3.shift(), _loc3.shift() != undefined)
            {
                _loc2.obj[_loc2.fn]();
            } // end while
        } // end if
    } // End of the function
    function cancelAllDoLaters(Void)
    {
        delete this.onEnterFrame;
        methodTable = new Array();
    } // End of the function
    function invalidate(Void)
    {
        invalidateFlag = true;
        onEnterFrame = doLaterDispatcher;
    } // End of the function
    function invalidateStyle(Void)
    {
        this.invalidate();
    } // End of the function
    function redraw(bAlways)
    {
        if (invalidateFlag || bAlways)
        {
            invalidateFlag = false;
            var _loc2;
            for (var _loc2 in tfList)
            {
                tfList[_loc2].draw();
            } // end of for...in
            this.draw();
            this.dispatchEvent({type: "draw"});
        } // end if
    } // End of the function
    function draw(Void)
    {
    } // End of the function
    function move(x, y, noEvent)
    {
        var _loc3 = _x;
        var _loc2 = _y;
        _x = x;
        _y = y;
        if (noEvent != true)
        {
            this.dispatchEvent({type: "move", oldX: _loc3, oldY: _loc2});
        } // end if
    } // End of the function
    function setSize(w, h, noEvent)
    {
        var _loc2 = __width;
        var _loc3 = __height;
        __width = w;
        __height = h;
        this.size();
        if (noEvent != true)
        {
            this.dispatchEvent({type: "resize", oldWidth: _loc2, oldHeight: _loc3});
        } // end if
    } // End of the function
    function size(Void)
    {
        _width = __width;
        _height = __height;
    } // End of the function
    function drawRect(x1, y1, x2, y2)
    {
        this.moveTo(x1, y1);
        this.lineTo(x2, y1);
        this.lineTo(x2, y2);
        this.lineTo(x1, y2);
        this.lineTo(x1, y1);
    } // End of the function
    function createLabel(name, depth, text)
    {
        this.createTextField(name, depth, 0, 0, 0, 0);
        var _loc2 = this[name];
        _loc2._color = mx.core.UIObject.textColorList;
        _loc2._visible = false;
        _loc2.__text = text;
        if (tfList == undefined)
        {
            tfList = new Object();
        } // end if
        tfList[name] = _loc2;
        _loc2.invalidateStyle();
        this.invalidate();
        _loc2.styleName = this;
        return (_loc2);
    } // End of the function
    function createObject(linkageName, id, depth, initobj)
    {
        return (this.attachMovie(linkageName, id, depth, initobj));
    } // End of the function
    function createClassObject(className, id, depth, initobj)
    {
        var _loc3 = className.symbolName == undefined;
        if (_loc3)
        {
            Object.registerClass(className.symbolOwner.symbolName, className);
        } // end if
        var _loc4 = this.createObject(className.symbolOwner.symbolName, id, depth, initobj);
        if (_loc3)
        {
            Object.registerClass(className.symbolOwner.symbolName, className.symbolOwner);
        } // end if
        return (_loc4);
    } // End of the function
    function createEmptyObject(id, depth)
    {
        return (this.createClassObject(mx.core.UIObject, id, depth));
    } // End of the function
    function destroyObject(id)
    {
        var _loc2 = this[id];
        if (_loc2.getDepth() < 0)
        {
            var _loc4 = this.buildDepthTable();
            var _loc5 = this.findNextAvailableDepth(0, _loc4, "up");
            var _loc3 = _loc5;
            _loc2.swapDepths(_loc3);
        } // end if
        _loc2.removeMovieClip();
        delete this[id];
    } // End of the function
    function getSkinIDName(tag)
    {
        return (idNames[tag]);
    } // End of the function
    function setSkin(tag, linkageName, initObj)
    {
        if (_global.skinRegistry[linkageName] == undefined)
        {
            mx.skins.SkinElement.registerElement(linkageName, mx.skins.SkinElement);
        } // end if
        return (this.createObject(linkageName, this.getSkinIDName(tag), tag, initObj));
    } // End of the function
    function createSkin(tag)
    {
        var _loc2 = this.getSkinIDName(tag);
        this.createEmptyObject(_loc2, tag);
        return (this[_loc2]);
    } // End of the function
    function createChildren(Void)
    {
    } // End of the function
    function _createChildren(Void)
    {
        this.createChildren();
        childrenCreated = true;
    } // End of the function
    function constructObject(Void)
    {
        if (_name == undefined)
        {
            return;
        } // end if
        this.init();
        this._createChildren();
        this.createAccessibilityImplementation();
        this._endInit();
        if (validateNow)
        {
            this.redraw(true);
        }
        else
        {
            this.invalidate();
        } // end else if
    } // End of the function
    function initFromClipParameters(Void)
    {
        var _loc4 = false;
        var _loc2;
        for (var _loc2 in clipParameters)
        {
            if (this.hasOwnProperty(_loc2))
            {
                _loc4 = true;
                set("def_" + _loc2, this[_loc2]);
                delete this[_loc2];
            } // end if
        } // end of for...in
        if (_loc4)
        {
            for (var _loc2 in clipParameters)
            {
                var _loc3 = this["def_" + _loc2];
                if (_loc3 != undefined)
                {
                    this[_loc2] = _loc3;
                } // end if
            } // end of for...in
        } // end if
    } // End of the function
    function init(Void)
    {
        __width = _width;
        __height = _height;
        if (initProperties == undefined)
        {
            this.initFromClipParameters();
        }
        else
        {
            this.initProperties();
        } // end else if
        if (_global.cascadingStyles == true)
        {
            stylecache = new Object();
        } // end if
    } // End of the function
    function getClassStyleDeclaration(Void)
    {
        var _loc4 = this;
        for (var _loc3 = className; _loc3 != undefined; _loc3 = _loc4.className)
        {
            if (ignoreClassStyleDeclaration[_loc3] == undefined)
            {
                if (_global.styles[_loc3] != undefined)
                {
                    return (_global.styles[_loc3]);
                } // end if
            } // end if
            _loc4 = _loc4.__proto__;
        } // end of for
    } // End of the function
    function setColor(color)
    {
    } // End of the function
    function __getTextFormat(tf, bAll)
    {
        var _loc8 = stylecache.tf;
        if (_loc8 != undefined)
        {
            var _loc3;
            for (var _loc3 in mx.styles.StyleManager.TextFormatStyleProps)
            {
                if (bAll || mx.styles.StyleManager.TextFormatStyleProps[_loc3])
                {
                    if (tf[_loc3] == undefined)
                    {
                        tf[_loc3] = _loc8[_loc3];
                    } // end if
                } // end if
            } // end of for...in
            return (false);
        } // end if
        var _loc6 = false;
        for (var _loc3 in mx.styles.StyleManager.TextFormatStyleProps)
        {
            if (bAll || mx.styles.StyleManager.TextFormatStyleProps[_loc3])
            {
                if (tf[_loc3] == undefined)
                {
                    var _loc5 = _tf[_loc3];
                    if (_loc5 != undefined)
                    {
                        tf[_loc3] = _loc5;
                        continue;
                    } // end if
                    if (_loc3 == "font" && fontFamily != undefined)
                    {
                        tf[_loc3] = fontFamily;
                        continue;
                    } // end if
                    if (_loc3 == "size" && fontSize != undefined)
                    {
                        tf[_loc3] = fontSize;
                        continue;
                    } // end if
                    if (_loc3 == "color" && color != undefined)
                    {
                        tf[_loc3] = color;
                        continue;
                    } // end if
                    if (_loc3 == "leftMargin" && marginLeft != undefined)
                    {
                        tf[_loc3] = marginLeft;
                        continue;
                    } // end if
                    if (_loc3 == "rightMargin" && marginRight != undefined)
                    {
                        tf[_loc3] = marginRight;
                        continue;
                    } // end if
                    if (_loc3 == "italic" && fontStyle != undefined)
                    {
                        tf[_loc3] = fontStyle == _loc3;
                        continue;
                    } // end if
                    if (_loc3 == "bold" && fontWeight != undefined)
                    {
                        tf[_loc3] = fontWeight == _loc3;
                        continue;
                    } // end if
                    if (_loc3 == "align" && textAlign != undefined)
                    {
                        tf[_loc3] = textAlign;
                        continue;
                    } // end if
                    if (_loc3 == "indent" && textIndent != undefined)
                    {
                        tf[_loc3] = textIndent;
                        continue;
                    } // end if
                    if (_loc3 == "underline" && textDecoration != undefined)
                    {
                        tf[_loc3] = textDecoration == _loc3;
                        continue;
                    } // end if
                    if (_loc3 == "embedFonts" && embedFonts != undefined)
                    {
                        tf[_loc3] = embedFonts;
                        continue;
                    } // end if
                    _loc6 = true;
                } // end if
            } // end if
        } // end of for...in
        if (_loc6)
        {
            var _loc9 = styleName;
            if (_loc9 != undefined)
            {
                if (typeof(_loc9) != "string")
                {
                    _loc6 = _loc9.__getTextFormat(tf, true, this);
                }
                else if (_global.styles[_loc9] != undefined)
                {
                    _loc6 = _global.styles[_loc9].__getTextFormat(tf, true, this);
                } // end if
            } // end if
        } // end else if
        if (_loc6)
        {
            var _loc10 = this.getClassStyleDeclaration();
            if (_loc10 != undefined)
            {
                _loc6 = _loc10.__getTextFormat(tf, true, this);
            } // end if
        } // end if
        if (_loc6)
        {
            if (_global.cascadingStyles)
            {
                if (_parent != undefined)
                {
                    _loc6 = _parent.__getTextFormat(tf, false);
                } // end if
            } // end if
        } // end if
        if (_loc6)
        {
            _loc6 = _global.style.__getTextFormat(tf, true, this);
        } // end if
        return (_loc6);
    } // End of the function
    function _getTextFormat(Void)
    {
        var _loc2 = stylecache.tf;
        if (_loc2 != undefined)
        {
            return (_loc2);
        } // end if
        _loc2 = new TextFormat();
        this.__getTextFormat(_loc2, true);
        stylecache.tf = _loc2;
        if (enabled == false)
        {
            var _loc3 = this.getStyle("disabledColor");
            _loc2.color = _loc3;
        } // end if
        return (_loc2);
    } // End of the function
    function getStyleName(Void)
    {
        var _loc2 = styleName;
        if (_loc2 != undefined)
        {
            if (typeof(_loc2) != "string")
            {
                return (_loc2.getStyleName());
            }
            else
            {
                return (_loc2);
            } // end if
        } // end else if
        if (_parent != undefined)
        {
            return (_parent.getStyleName());
        }
        else
        {
            return;
        } // end else if
    } // End of the function
    function getStyle(styleProp)
    {
        var _loc3;
        ++_global.getStyleCounter;
        if (this[styleProp] != undefined)
        {
            return (this[styleProp]);
        } // end if
        var _loc6 = styleName;
        if (_loc6 != undefined)
        {
            if (typeof(_loc6) != "string")
            {
                _loc3 = _loc6.getStyle(styleProp);
            }
            else
            {
                var _loc7 = _global.styles[_loc6];
                _loc3 = _loc7.getStyle(styleProp);
            } // end if
        } // end else if
        if (_loc3 != undefined)
        {
            return (_loc3);
        } // end if
        _loc7 = this.getClassStyleDeclaration();
        if (_loc7 != undefined)
        {
            _loc3 = _loc7[styleProp];
        } // end if
        if (_loc3 != undefined)
        {
            return (_loc3);
        } // end if
        if (_global.cascadingStyles)
        {
            if (mx.styles.StyleManager.isInheritingStyle(styleProp) || mx.styles.StyleManager.isColorStyle(styleProp))
            {
                var _loc5 = stylecache;
                if (_loc5 != undefined)
                {
                    if (_loc5[styleProp] != undefined)
                    {
                        return (_loc5[styleProp]);
                    } // end if
                } // end if
                if (_parent != undefined)
                {
                    _loc3 = _parent.getStyle(styleProp);
                }
                else
                {
                    _loc3 = _global.style[styleProp];
                } // end else if
                if (_loc5 != undefined)
                {
                    _loc5[styleProp] = _loc3;
                } // end if
                return (_loc3);
            } // end if
        } // end if
        if (_loc3 == undefined)
        {
            _loc3 = _global.style[styleProp];
        } // end if
        return (_loc3);
    } // End of the function
    static function mergeClipParameters(o, p)
    {
        for (var _loc3 in p)
        {
            o[_loc3] = p[_loc3];
        } // end of for...in
        return (true);
    } // End of the function
    static var symbolName = "UIObject";
    static var symbolOwner = mx.core.UIObject;
    static var version = "2.0.2.126";
    static var textColorList = {color: 1, disabledColor: 1};
    var invalidateFlag = false;
    var lineWidth = 1;
    var lineColor = 0;
    var tabEnabled = false;
    var clipParameters = {visible: 1, minHeight: 1, minWidth: 1, maxHeight: 1, maxWidth: 1, preferredHeight: 1, preferredWidth: 1};
} // End of Class
