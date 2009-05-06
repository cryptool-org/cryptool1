class mx.styles.StyleManager
{
    function StyleManager()
    {
    } // End of the function
    static function registerInheritingStyle(styleName)
    {
        mx.styles.StyleManager.inheritingStyles[styleName] = true;
    } // End of the function
    static function isInheritingStyle(styleName)
    {
        return (mx.styles.StyleManager.inheritingStyles[styleName] == true);
    } // End of the function
    static function registerColorStyle(styleName)
    {
        mx.styles.StyleManager.colorStyles[styleName] = true;
    } // End of the function
    static function isColorStyle(styleName)
    {
        return (mx.styles.StyleManager.colorStyles[styleName] == true);
    } // End of the function
    static function registerColorName(colorName, colorValue)
    {
        mx.styles.StyleManager.colorNames[colorName] = colorValue;
    } // End of the function
    static function isColorName(colorName)
    {
        return (mx.styles.StyleManager.colorNames[colorName] != undefined);
    } // End of the function
    static function getColorName(colorName)
    {
        return (mx.styles.StyleManager.colorNames[colorName]);
    } // End of the function
    static var inheritingStyles = {color: true, direction: true, fontFamily: true, fontSize: true, fontStyle: true, fontWeight: true, textAlign: true, textIndent: true};
    static var colorStyles = {barColor: true, trackColor: true, borderColor: true, buttonColor: true, color: true, dateHeaderColor: true, dateRollOverColor: true, disabledColor: true, fillColor: true, highlightColor: true, scrollTrackColor: true, selectedDateColor: true, shadowColor: true, strokeColor: true, symbolBackgroundColor: true, symbolBackgroundDisabledColor: true, symbolBackgroundPressedColor: true, symbolColor: true, symbolDisabledColor: true, themeColor: true, todayIndicatorColor: true, shadowCapColor: true, borderCapColor: true, focusColor: true};
    static var colorNames = {black: 0, white: 16777215, red: 16711680, green: 65280, blue: 255, magenta: 16711935, yellow: 16776960, cyan: 65535, haloGreen: 8453965, haloBlue: 2881013, haloOrange: 16761344};
    static var TextFormatStyleProps = {font: true, size: true, color: true, leftMargin: false, rightMargin: false, italic: true, bold: true, align: true, indent: true, underline: false, embedFonts: false};
    static var TextStyleMap = {textAlign: true, fontWeight: true, color: true, fontFamily: true, textIndent: true, fontStyle: true, lineHeight: true, marginLeft: true, marginRight: true, fontSize: true, textDecoration: true, embedFonts: true};
} // End of Class
