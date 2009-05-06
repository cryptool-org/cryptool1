class mx.controls.scrollClasses.ScrollThumb extends mx.skins.CustomBorder
{
    var useHandCursor, ymin, ymax, datamin, datamax, _ymouse, lastY, scrollMove, _y, _parent, onMouseMove, grip_mc, gripSkin, setSkin, __get__height, __get__width;
    function ScrollThumb()
    {
        super();
    } // End of the function
    function createChildren(Void)
    {
        super.createChildren();
        useHandCursor = false;
    } // End of the function
    function setRange(_ymin, _ymax, _datamin, _datamax)
    {
        ymin = _ymin;
        ymax = _ymax;
        datamin = _datamin;
        datamax = _datamax;
    } // End of the function
    function dragThumb(Void)
    {
        scrollMove = _ymouse - lastY;
        scrollMove = scrollMove + _y;
        if (scrollMove < ymin)
        {
            scrollMove = ymin;
        }
        else if (scrollMove > ymax)
        {
            scrollMove = ymax;
        } // end else if
        _parent.isScrolling = true;
        _y = scrollMove;
        var _loc2 = Math.round((datamax - datamin) * (_y - ymin) / (ymax - ymin)) + datamin;
        _parent.scrollPosition = _loc2;
        _parent.dispatchScrollEvent("ThumbTrack");
        updateAfterEvent();
    } // End of the function
    function stopDragThumb(Void)
    {
        _parent.isScrolling = false;
        _parent.dispatchScrollEvent("ThumbPosition");
        _parent.dispatchScrollChangedEvent();
        delete this.onMouseMove;
    } // End of the function
    function onPress(Void)
    {
        _parent.pressFocus();
        lastY = _ymouse;
        onMouseMove = dragThumb;
        super.onPress();
    } // End of the function
    function onRelease(Void)
    {
        _parent.releaseFocus();
        this.stopDragThumb();
        super.onRelease();
    } // End of the function
    function onReleaseOutside(Void)
    {
        _parent.releaseFocus();
        this.stopDragThumb();
        super.onReleaseOutside();
    } // End of the function
    function draw()
    {
        super.draw();
        if (grip_mc == undefined)
        {
            this.setSkin(3, gripSkin);
        } // end if
    } // End of the function
    function size()
    {
        super.size();
        grip_mc.move((this.__get__width() - grip_mc.width) / 2, (this.__get__height() - grip_mc.height) / 2);
    } // End of the function
    static var symbolOwner = mx.skins.CustomBorder.symbolOwner;
    var className = "ScrollThumb";
    var btnOffset = 0;
    var horizontal = false;
    var idNames = new Array("l_mc", "m_mc", "r_mc", "grip_mc");
} // End of Class
