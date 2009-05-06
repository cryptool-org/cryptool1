class mx.skins.SkinElement extends MovieClip
{
    var _visible, _x, _y, _width, _height;
    function SkinElement()
    {
        super();
    } // End of the function
    static function registerElement(name, className)
    {
        Object.registerClass(name, className == undefined ? (mx.skins.SkinElement) : (className));
        _global.skinRegistry[name] = true;
    } // End of the function
    function set visible(visible)
    {
        _visible = visible;
    } // End of the function
    function move(x, y)
    {
        _x = x;
        _y = y;
    } // End of the function
    function setSize(w, h)
    {
        _width = w;
        _height = h;
    } // End of the function
} // End of Class
