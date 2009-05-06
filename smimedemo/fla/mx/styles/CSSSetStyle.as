class mx.styles.CSSSetStyle
{
    var styleProp, styleName, stylecache, _color, setColor, invalidateStyle;
    function CSSSetStyle()
    {
    } // End of the function
    function _setStyle(styleProp, newValue)
    {
        this[styleProp] = newValue;
        if (mx.styles.StyleManager.TextStyleMap[styleProp] != undefined)
        {
            if (styleProp == "color")
            {
                if (isNaN(newValue))
                {
                    newValue = mx.styles.StyleManager.getColorName(newValue);
                    this[styleProp] = newValue;
                    if (newValue == undefined)
                    {
                        return;
                    } // end if
                } // end if
            } // end if
            _level0.changeTextStyleInChildren(styleProp);
            return;
        } // end if
        if (mx.styles.StyleManager.isColorStyle(styleProp))
        {
            if (isNaN(newValue))
            {
                newValue = mx.styles.StyleManager.getColorName(newValue);
                this[styleProp] = newValue;
                if (newValue == undefined)
                {
                    return;
                } // end if
            } // end if
            if (styleProp == "themeColor")
            {
                var _loc7 = mx.styles.StyleManager.colorNames.haloBlue;
                var _loc6 = mx.styles.StyleManager.colorNames.haloGreen;
                var _loc8 = mx.styles.StyleManager.colorNames.haloOrange;
                var _loc4 = {};
                _loc4[_loc7] = 12188666;
                _loc4[_loc6] = 13500353;
                _loc4[_loc8] = 16766319;
                var _loc5 = {};
                _loc5[_loc7] = 13958653;
                _loc5[_loc6] = 14942166;
                _loc5[_loc8] = 16772787;
                var _loc9 = _loc4[newValue];
                var _loc10 = _loc5[newValue];
                if (_loc9 == undefined)
                {
                    _loc9 = newValue;
                } // end if
                if (_loc10 == undefined)
                {
                    _loc10 = newValue;
                } // end if
                this.setStyle("selectionColor", _loc9);
                this.setStyle("rollOverColor", _loc10);
            } // end if
            _level0.changeColorStyleInChildren(styleName, styleProp, newValue);
        }
        else
        {
            if (styleProp == "backgroundColor" && isNaN(newValue))
            {
                newValue = mx.styles.StyleManager.getColorName(newValue);
                this[styleProp] = newValue;
                if (newValue == undefined)
                {
                    return;
                } // end if
            } // end if
            _level0.notifyStyleChangeInChildren(styleName, styleProp, newValue);
        } // end else if
    } // End of the function
    function changeTextStyleInChildren(styleProp)
    {
        var _loc4 = getTimer();
        var _loc5;
        for (var _loc5 in this)
        {
            var _loc2 = this[_loc5];
            if (_loc2._parent == this)
            {
                if (_loc2.searchKey != _loc4)
                {
                    if (_loc2.stylecache != undefined)
                    {
                        delete _loc2.stylecache.tf;
                        delete _loc2.stylecache[styleProp];
                    } // end if
                    _loc2.invalidateStyle(styleProp);
                    _loc2.changeTextStyleInChildren(styleProp);
                    _loc2.searchKey = _loc4;
                } // end if
            } // end if
        } // end of for...in
    } // End of the function
    function changeColorStyleInChildren(sheetName, colorStyle, newValue)
    {
        var _loc6 = getTimer();
        var _loc7;
        for (var _loc7 in this)
        {
            var _loc2 = this[_loc7];
            if (_loc2._parent == this)
            {
                if (_loc2.searchKey != _loc6)
                {
                    if (_loc2.getStyleName() == sheetName || sheetName == undefined || sheetName == "_global")
                    {
                        if (_loc2.stylecache != undefined)
                        {
                            delete _loc2.stylecache[colorStyle];
                        } // end if
                        if (typeof(_loc2._color) == "string")
                        {
                            if (_loc2._color == colorStyle)
                            {
                                var _loc4 = _loc2.getStyle(colorStyle);
                                if (colorStyle == "color")
                                {
                                    if (stylecache.tf.color != undefined)
                                    {
                                        stylecache.tf.color = _loc4;
                                    } // end if
                                } // end if
                                _loc2.setColor(_loc4);
                            } // end if
                        }
                        else if (_loc2._color[colorStyle] != undefined)
                        {
                            if (typeof(_loc2) != "movieclip")
                            {
                                _loc2._parent.invalidateStyle();
                            }
                            else
                            {
                                _loc2.invalidateStyle(colorStyle);
                            } // end if
                        } // end else if
                    } // end else if
                    _loc2.changeColorStyleInChildren(sheetName, colorStyle, newValue);
                    _loc2.searchKey = _loc6;
                } // end if
            } // end if
        } // end of for...in
    } // End of the function
    function notifyStyleChangeInChildren(sheetName, styleProp, newValue)
    {
        var _loc5 = getTimer();
        var _loc6;
        for (var _loc6 in this)
        {
            var _loc2 = this[_loc6];
            if (_loc2._parent == this)
            {
                if (_loc2.searchKey != _loc5)
                {
                    if (_loc2.styleName == sheetName || _loc2.styleName != undefined && typeof(_loc2.styleName) == "movieclip" || sheetName == undefined)
                    {
                        if (_loc2.stylecache != undefined)
                        {
                            delete _loc2.stylecache[styleProp];
                            delete _loc2.stylecache.tf;
                        } // end if
                        delete _loc2.enabledColor;
                        _loc2.invalidateStyle(styleProp);
                    } // end if
                    _loc2.notifyStyleChangeInChildren(sheetName, styleProp, newValue);
                    _loc2.searchKey = _loc5;
                } // end if
            } // end if
        } // end of for...in
    } // End of the function
    function setStyle(styleProp, newValue)
    {
        if (stylecache != undefined)
        {
            delete stylecache[styleProp];
            delete stylecache.tf;
        } // end if
        this[styleProp] = newValue;
        if (mx.styles.StyleManager.isColorStyle(styleProp))
        {
            if (isNaN(newValue))
            {
                newValue = mx.styles.StyleManager.getColorName(newValue);
                this[styleProp] = newValue;
                if (newValue == undefined)
                {
                    return;
                } // end if
            } // end if
            if (styleProp == "themeColor")
            {
                var _loc10 = mx.styles.StyleManager.colorNames.haloBlue;
                var _loc9 = mx.styles.StyleManager.colorNames.haloGreen;
                var _loc11 = mx.styles.StyleManager.colorNames.haloOrange;
                var _loc6 = {};
                _loc6[_loc10] = 12188666;
                _loc6[_loc9] = 13500353;
                _loc6[_loc11] = 16766319;
                var _loc7 = {};
                _loc7[_loc10] = 13958653;
                _loc7[_loc9] = 14942166;
                _loc7[_loc11] = 16772787;
                var _loc12 = _loc6[newValue];
                var _loc13 = _loc7[newValue];
                if (_loc12 == undefined)
                {
                    _loc12 = newValue;
                } // end if
                if (_loc13 == undefined)
                {
                    _loc13 = newValue;
                } // end if
                this.setStyle("selectionColor", _loc12);
                this.setStyle("rollOverColor", _loc13);
            } // end if
            if (typeof(_color) == "string")
            {
                if (_color == styleProp)
                {
                    if (styleProp == "color")
                    {
                        if (stylecache.tf.color != undefined)
                        {
                            stylecache.tf.color = newValue;
                        } // end if
                    } // end if
                    this.setColor(newValue);
                } // end if
            }
            else if (_color[styleProp] != undefined)
            {
                this.invalidateStyle(styleProp);
            } // end else if
            this.changeColorStyleInChildren(undefined, styleProp, newValue);
        }
        else
        {
            if (styleProp == "backgroundColor" && isNaN(newValue))
            {
                newValue = mx.styles.StyleManager.getColorName(newValue);
                this[styleProp] = newValue;
                if (newValue == undefined)
                {
                    return;
                } // end if
            } // end if
            this.invalidateStyle(styleProp);
        } // end else if
        if (mx.styles.StyleManager.isInheritingStyle(styleProp) || styleProp == "styleName")
        {
            var _loc8;
            var _loc5 = newValue;
            if (styleProp == "styleName")
            {
                _loc8 = typeof(newValue) == "string" ? (_global.styles[newValue]) : (_loc5);
                _loc5 = _loc8.themeColor;
                if (_loc5 != undefined)
                {
                    _loc8.rollOverColor = _loc8.selectionColor = _loc5;
                } // end if
            } // end if
            this.notifyStyleChangeInChildren(undefined, styleProp, newValue);
        } // end if
    } // End of the function
    static function enableRunTimeCSS()
    {
    } // End of the function
    static function classConstruct()
    {
        var _loc2 = MovieClip.prototype;
        var _loc3 = mx.styles.CSSSetStyle.prototype;
        mx.styles.CSSStyleDeclaration.prototype.setStyle = _loc3._setStyle;
        _loc2.changeTextStyleInChildren = _loc3.changeTextStyleInChildren;
        _loc2.changeColorStyleInChildren = _loc3.changeColorStyleInChildren;
        _loc2.notifyStyleChangeInChildren = _loc3.notifyStyleChangeInChildren;
        _loc2.setStyle = _loc3.setStyle;
        _global.ASSetPropFlags(_loc2, "changeTextStyleInChildren", 1);
        _global.ASSetPropFlags(_loc2, "changeColorStyleInChildren", 1);
        _global.ASSetPropFlags(_loc2, "notifyStyleChangeInChildren", 1);
        _global.ASSetPropFlags(_loc2, "setStyle", 1);
        var _loc4 = TextField.prototype;
        _loc4.setStyle = _loc2.setStyle;
        _loc4.changeTextStyleInChildren = _loc3.changeTextStyleInChildren;
        return (true);
    } // End of the function
    static var classConstructed = mx.styles.CSSSetStyle.classConstruct();
    static var CSSStyleDeclarationDependency = mx.styles.CSSStyleDeclaration;
} // End of Class
