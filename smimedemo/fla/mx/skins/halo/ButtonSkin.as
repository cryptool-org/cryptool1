class mx.skins.halo.ButtonSkin extends mx.skins.RectBorder
{
    var __get__height, __get__width, getStyle, _parent, clear, __get__y, __get__x, drawRoundRect;
    function ButtonSkin()
    {
        super();
    } // End of the function
    function init()
    {
        super.init();
    } // End of the function
    function size()
    {
        this.drawHaloRect(this.__get__width(), this.__get__height());
    } // End of the function
    function drawHaloRect(w, h)
    {
        var _loc6 = this.getStyle("borderStyle");
        var _loc4 = this.getStyle("themeColor");
        var _loc5 = _parent.emphasized;
        this.clear();
        switch (_loc6)
        {
            case "falseup":
            {
                if (_loc5)
                {
                    this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, 9542041, 100);
                    this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, _loc4, 75);
                    this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, [3355443, 16777215], 85, 0, "radial");
                    this.drawRoundRect(this.__get__x() + 2, this.__get__y() + 2, w - 4, h - 4, 3, [0, 14342874], 100, 0, "radial");
                    this.drawRoundRect(this.__get__x() + 2, this.__get__y() + 2, w - 4, h - 4, 3, _loc4, 75);
                    this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 3, w - 6, h - 6, 2, 16777215, 100);
                    this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 4, w - 6, h - 7, 2, 16316664, 100);
                }
                else
                {
                    this.drawRoundRect(0, 0, w, h, 5, 9542041, 100);
                    this.drawRoundRect(1, 1, w - 2, h - 2, 4, [13291985, 16250871], 100, 0, "radial");
                    this.drawRoundRect(2, 2, w - 4, h - 4, 3, [9542041, 13818586], 100, 0, "radial");
                    this.drawRoundRect(3, 3, w - 6, h - 6, 2, 16777215, 100);
                    this.drawRoundRect(3, 4, w - 6, h - 7, 2, 16316664, 100);
                } // end else if
                break;
            } 
            case "falsedown":
            {
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, 9542041, 100);
                this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, [3355443, 16579836], 100, 0, "radial");
                this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, _loc4, 50);
                this.drawRoundRect(this.__get__x() + 2, this.__get__y() + 2, w - 4, h - 4, 3, [0, 14342874], 100, 0, "radial");
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, _loc4, 40);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 3, w - 6, h - 6, 2, 16777215, 100);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 4, w - 6, h - 7, 2, _loc4, 20);
                break;
            } 
            case "falserollover":
            {
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, 9542041, 100);
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, _loc4, 50);
                this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, [3355443, 16777215], 100, 0, "radial");
                this.drawRoundRect(this.__get__x() + 2, this.__get__y() + 2, w - 4, h - 4, 3, [0, 14342874], 100, 0, "radial");
                this.drawRoundRect(this.__get__x() + 2, this.__get__y() + 2, w - 4, h - 4, 3, _loc4, 50);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 3, w - 6, h - 6, 2, 16777215, 100);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 4, w - 6, h - 7, 2, 16316664, 100);
                break;
            } 
            case "falsedisabled":
            {
                this.drawRoundRect(0, 0, w, h, 5, 13159628, 100);
                this.drawRoundRect(1, 1, w - 2, h - 2, 4, 15921906, 100);
                this.drawRoundRect(2, 2, w - 4, h - 4, 3, 13949401, 100);
                this.drawRoundRect(3, 3, w - 6, h - 6, 2, 15921906, 100);
                break;
            } 
            case "trueup":
            {
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, 10066329, 100);
                this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, [3355443, 16579836], 100, 0, "radial");
                this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, _loc4, 50);
                this.drawRoundRect(this.__get__x() + 2, this.__get__y() + 2, w - 4, h - 4, 3, [0, 14342874], 100, 0, "radial");
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, _loc4, 40);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 3, w - 6, h - 6, 2, 16777215, 100);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 4, w - 6, h - 7, 2, 16250871, 100);
                break;
            } 
            case "truedown":
            {
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, 10066329, 100);
                this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, [3355443, 16579836], 100, 0, "radial");
                this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, _loc4, 50);
                this.drawRoundRect(this.__get__x() + 2, this.__get__y() + 2, w - 4, h - 4, 3, [0, 14342874], 100, 0, "radial");
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, _loc4, 40);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 3, w - 6, h - 6, 2, 16777215, 100);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 4, w - 6, h - 7, 2, _loc4, 20);
                break;
            } 
            case "truerollover":
            {
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, 9542041, 100);
                this.drawRoundRect(this.__get__x(), this.__get__y(), w, h, 5, _loc4, 50);
                this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, [3355443, 16777215], 100, 0, "radial");
                this.drawRoundRect(this.__get__x() + 1, this.__get__y() + 1, w - 2, h - 2, 4, _loc4, 40);
                this.drawRoundRect(this.__get__x() + 2, this.__get__y() + 2, w - 4, h - 4, 3, [0, 14342874], 100, 0, "radial");
                this.drawRoundRect(this.__get__x() + 2, this.__get__y() + 2, w - 4, h - 4, 3, _loc4, 40);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 3, w - 6, h - 6, 2, 16777215, 100);
                this.drawRoundRect(this.__get__x() + 3, this.__get__y() + 4, w - 6, h - 7, 2, 16316664, 100);
                break;
            } 
            case "truedisabled":
            {
                this.drawRoundRect(0, 0, w, h, 5, 13159628, 100);
                this.drawRoundRect(1, 1, w - 2, h - 2, 4, 15921906, 100);
                this.drawRoundRect(2, 2, w - 4, h - 4, 3, 13949401, 100);
                this.drawRoundRect(3, 3, w - 6, h - 6, 2, 15921906, 100);
            } 
        } // End of switch
    } // End of the function
    static function classConstruct()
    {
        mx.core.ext.UIObjectExtensions.Extensions();
        _global.skinRegistry.ButtonSkin = true;
        return (true);
    } // End of the function
    static var symbolName = "ButtonSkin";
    static var symbolOwner = mx.skins.halo.ButtonSkin;
    var className = "ButtonSkin";
    var backgroundColorName = "buttonColor";
    static var classConstructed = mx.skins.halo.ButtonSkin.classConstruct();
    static var UIObjectExtensionsDependency = mx.core.ext.UIObjectExtensions;
} // End of Class
