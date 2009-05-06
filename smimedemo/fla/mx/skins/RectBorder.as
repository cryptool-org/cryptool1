class mx.skins.RectBorder extends mx.skins.Border
{
    var __width, __height, offset, __borderMetrics, __get__borderMetrics, __get__height, __get__width;
    function RectBorder()
    {
        super();
    } // End of the function
    function get width()
    {
        return (__width);
    } // End of the function
    function get height()
    {
        return (__height);
    } // End of the function
    function init(Void)
    {
        super.init();
    } // End of the function
    function draw(Void)
    {
        this.size();
    } // End of the function
    function getBorderMetrics(Void)
    {
        var _loc2 = offset;
        if (__borderMetrics == undefined)
        {
            __borderMetrics = {left: _loc2, top: _loc2, right: _loc2, bottom: _loc2};
        }
        else
        {
            __borderMetrics.left = _loc2;
            __borderMetrics.top = _loc2;
            __borderMetrics.right = _loc2;
            __borderMetrics.bottom = _loc2;
        } // end else if
        return (__borderMetrics);
    } // End of the function
    function get borderMetrics()
    {
        return (this.getBorderMetrics());
    } // End of the function
    function drawBorder(Void)
    {
    } // End of the function
    function size(Void)
    {
        this.drawBorder();
    } // End of the function
    function setColor(Void)
    {
        this.drawBorder();
    } // End of the function
    static var symbolName = "RectBorder";
    static var symbolOwner = mx.skins.RectBorder;
    static var version = "2.0.2.126";
    var className = "RectBorder";
    var borderStyleName = "borderStyle";
    var borderColorName = "borderColor";
    var shadowColorName = "shadowColor";
    var highlightColorName = "highlightColor";
    var buttonColorName = "buttonColor";
    var backgroundColorName = "backgroundColor";
} // End of Class
