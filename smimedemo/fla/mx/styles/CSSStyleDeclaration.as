class mx.styles.CSSStyleDeclaration
{
    var _tf;
    function CSSStyleDeclaration()
    {
    } // End of the function
    function __getTextFormat(tf, bAll)
    {
        var _loc5 = false;
        if (_tf != undefined)
        {
            var _loc2;
            for (var _loc2 in mx.styles.StyleManager.TextFormatStyleProps)
            {
                if (bAll || mx.styles.StyleManager.TextFormatStyleProps[_loc2])
                {
                    if (tf[_loc2] == undefined)
                    {
                        var _loc3 = _tf[_loc2];
                        if (_loc3 != undefined)
                        {
                            tf[_loc2] = _loc3;
                            continue;
                        } // end if
                        _loc5 = true;
                    } // end if
                } // end if
            } // end of for...in
        }
        else
        {
            _loc5 = true;
        } // end else if
        return (_loc5);
    } // End of the function
    function getStyle(styleProp)
    {
        var _loc2 = this[styleProp];
        var _loc3 = mx.styles.StyleManager.getColorName(_loc2);
        return (_loc3 == undefined ? (_loc2) : (_loc3));
    } // End of the function
    static function classConstruct()
    {
        mx.styles.CSSTextStyles.addTextStyles(mx.styles.CSSStyleDeclaration.prototype, true);
        return (true);
    } // End of the function
    static var classConstructed = mx.styles.CSSStyleDeclaration.classConstruct();
    static var CSSTextStylesDependency = mx.styles.CSSTextStyles;
} // End of Class
