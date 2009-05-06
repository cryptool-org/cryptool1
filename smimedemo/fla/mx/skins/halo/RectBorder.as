class mx.skins.halo.RectBorder extends mx.skins.RectBorder
{
    var offset, borderStyleName, getStyle, __borderMetrics, className, borderColorName, backgroundColorName, shadowColorName, highlightColorName, buttonColorName, __get__width, __get__height, clear, _color, drawRoundRect, beginFill, drawRect, endFill;
    function RectBorder()
    {
        super();
    } // End of the function
    function init(Void)
    {
        borderWidths["default"] = 3;
        super.init();
    } // End of the function
    function getBorderMetrics(Void)
    {
        if (offset == undefined)
        {
            var _loc3 = this.getStyle(borderStyleName);
            offset = borderWidths[_loc3];
        } // end if
        if (this.getStyle(borderStyleName) == "default" || this.getStyle(borderStyleName) == "alert")
        {
            __borderMetrics = {left: 3, top: 1, right: 3, bottom: 3};
            return (__borderMetrics);
        } // end if
        return (super.getBorderMetrics());
    } // End of the function
    function drawBorder(Void)
    {
        var _loc6 = _global.styles[className];
        if (_loc6 == undefined)
        {
            _loc6 = _global.styles.RectBorder;
        } // end if
        var _loc5 = this.getStyle(borderStyleName);
        var _loc7 = this.getStyle(borderColorName);
        if (_loc7 == undefined)
        {
            _loc7 = _loc6[borderColorName];
        } // end if
        var _loc8 = this.getStyle(backgroundColorName);
        if (_loc8 == undefined)
        {
            _loc8 = _loc6[backgroundColorName];
        } // end if
        var _loc16 = this.getStyle("backgroundImage");
        if (_loc5 != "none")
        {
            var _loc14 = this.getStyle(shadowColorName);
            if (_loc14 == undefined)
            {
                _loc14 = _loc6[shadowColorName];
            } // end if
            var _loc13 = this.getStyle(highlightColorName);
            if (_loc13 == undefined)
            {
                _loc13 = _loc6[highlightColorName];
            } // end if
            var _loc12 = this.getStyle(buttonColorName);
            if (_loc12 == undefined)
            {
                _loc12 = _loc6[buttonColorName];
            } // end if
            var _loc11 = this.getStyle(borderCapColorName);
            if (_loc11 == undefined)
            {
                _loc11 = _loc6[borderCapColorName];
            } // end if
            var _loc10 = this.getStyle(shadowCapColorName);
            if (_loc10 == undefined)
            {
                _loc10 = _loc6[shadowCapColorName];
            } // end if
        } // end if
        offset = borderWidths[_loc5];
        var _loc9 = offset;
        var _loc3 = this.__get__width();
        var _loc4 = this.__get__height();
        this.clear();
        _color = undefined;
        if (_loc5 == "none")
        {
        }
        else if (_loc5 == "inset")
        {
            _color = colorList;
            this.draw3dBorder(_loc11, _loc12, _loc7, _loc13, _loc14, _loc10);
        }
        else if (_loc5 == "outset")
        {
            _color = colorList;
            this.draw3dBorder(_loc11, _loc7, _loc12, _loc14, _loc13, _loc10);
        }
        else if (_loc5 == "alert")
        {
            var _loc15 = this.getStyle("themeColor");
            this.drawRoundRect(0, 5, _loc3, _loc4 - 5, 5, 6184542, 10);
            this.drawRoundRect(1, 4, _loc3 - 2, _loc4 - 5, 4, [6184542, 6184542], 10, 0, "radial");
            this.drawRoundRect(2, 0, _loc3 - 4, _loc4 - 2, 3, [0, 14342874], 100, 0, "radial");
            this.drawRoundRect(2, 0, _loc3 - 4, _loc4 - 2, 3, _loc15, 50);
            this.drawRoundRect(3, 1, _loc3 - 6, _loc4 - 4, 2, 16777215, 100);
        }
        else if (_loc5 == "default")
        {
            this.drawRoundRect(0, 5, _loc3, _loc4 - 5, {tl: 5, tr: 5, br: 0, bl: 0}, 6184542, 10);
            this.drawRoundRect(1, 4, _loc3 - 2, _loc4 - 5, {tl: 4, tr: 4, br: 0, bl: 0}, [6184542, 6184542], 10, 0, "radial");
            this.drawRoundRect(2, 0, _loc3 - 4, _loc4 - 2, {tl: 3, tr: 3, br: 0, bl: 0}, [12897484, 11844796], 100, 0, "radial");
            this.drawRoundRect(3, 1, _loc3 - 6, _loc4 - 4, {tl: 2, tr: 2, br: 0, bl: 0}, 16777215, 100);
        }
        else if (_loc5 == "dropDown")
        {
            this.drawRoundRect(0, 0, _loc3 + 1, _loc4, {tl: 4, tr: 0, br: 0, bl: 4}, [13290186, 7895160], 100, -10, "linear");
            this.drawRoundRect(1, 1, _loc3 - 1, _loc4 - 2, {tl: 3, tr: 0, br: 0, bl: 3}, 16777215, 100);
        }
        else if (_loc5 == "menuBorder")
        {
            _loc15 = this.getStyle("themeColor");
            this.drawRoundRect(4, 4, _loc3 - 2, _loc4 - 3, 0, [6184542, 6184542], 10, 0, "radial");
            this.drawRoundRect(4, 4, _loc3 - 1, _loc4 - 2, 0, 6184542, 10);
            this.drawRoundRect(0, 0, _loc3 + 1, _loc4, 0, [0, 14342874], 100, 250, "linear");
            this.drawRoundRect(0, 0, _loc3 + 1, _loc4, 0, _loc15, 50);
            this.drawRoundRect(2, 2, _loc3 - 3, _loc4 - 4, 0, 16777215, 100);
        }
        else if (_loc5 == "comboNonEdit")
        {
        }
        else
        {
            this.beginFill(_loc7);
            this.drawRect(0, 0, _loc3, _loc4);
            this.drawRect(1, 1, _loc3 - 1, _loc4 - 1);
            this.endFill();
            _color = borderColorName;
        } // end else if
        if (_loc8 != undefined)
        {
            this.beginFill(_loc8);
            this.drawRect(_loc9, _loc9, this.__get__width() - _loc9, this.__get__height() - _loc9);
            this.endFill();
        } // end if
    } // End of the function
    function draw3dBorder(c1, c2, c3, c4, c5, c6)
    {
        var _loc3 = this.__get__width();
        var _loc2 = this.__get__height();
        this.beginFill(c1);
        this.drawRect(0, 0, _loc3, _loc2);
        this.drawRect(1, 0, _loc3 - 1, _loc2);
        this.endFill();
        this.beginFill(c2);
        this.drawRect(1, 0, _loc3 - 1, 1);
        this.endFill();
        this.beginFill(c3);
        this.drawRect(1, _loc2 - 1, _loc3 - 1, _loc2);
        this.endFill();
        this.beginFill(c4);
        this.drawRect(1, 1, _loc3 - 1, 2);
        this.endFill();
        this.beginFill(c5);
        this.drawRect(1, _loc2 - 2, _loc3 - 1, _loc2 - 1);
        this.endFill();
        this.beginFill(c6);
        this.drawRect(1, 2, _loc3 - 1, _loc2 - 2);
        this.drawRect(2, 2, _loc3 - 2, _loc2 - 2);
        this.endFill();
    } // End of the function
    static function classConstruct()
    {
        mx.core.ext.UIObjectExtensions.Extensions();
        _global.styles.rectBorderClass = mx.skins.halo.RectBorder;
        _global.skinRegistry.RectBorder = true;
        return (true);
    } // End of the function
    static var symbolName = "RectBorder";
    static var symbolOwner = mx.skins.halo.RectBorder;
    static var version = "2.0.2.126";
    var borderCapColorName = "borderCapColor";
    var shadowCapColorName = "shadowCapColor";
    var colorList = {highlightColor: 0, borderColor: 0, buttonColor: 0, shadowColor: 0, borderCapColor: 0, shadowCapColor: 0};
    var borderWidths = {none: 0, solid: 1, inset: 2, outset: 2, alert: 3, dropDown: 2, menuBorder: 2, comboNonEdit: 2};
    static var classConstructed = mx.skins.halo.RectBorder.classConstruct();
    static var UIObjectExtensionsDependency = mx.core.ext.UIObjectExtensions;
} // End of Class
