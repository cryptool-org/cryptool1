class mx.core.UIComponent extends mx.core.UIObject
{
    var __width, __height, invalidate, stylecache, removeEventListener, dispatchEvent, drawFocus, addEventListener, _xscale, _yscale, _focusrect, watch, enabled, __get__height, __get__width;
    function UIComponent()
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
    function setVisible(x, noEvent)
    {
        super.setVisible(x, noEvent);
    } // End of the function
    function enabledChanged(id, oldValue, newValue)
    {
        this.setEnabled(newValue);
        this.invalidate();
        delete stylecache.tf;
        return (newValue);
    } // End of the function
    function setEnabled(enabled)
    {
        this.invalidate();
    } // End of the function
    function getFocus()
    {
        var selFocus = Selection.getFocus();
        return (selFocus === null ? (null) : (eval(selFocus)));
    } // End of the function
    function setFocus()
    {
        Selection.setFocus(this);
    } // End of the function
    function getFocusManager()
    {
        for (var _loc2 = this; _loc2 != undefined; _loc2 = _loc2._parent)
        {
            if (_loc2.focusManager != undefined)
            {
                return (_loc2.focusManager);
            } // end if
        } // end of for
        return;
    } // End of the function
    function onKillFocus(newFocus)
    {
        this.removeEventListener("keyDown", this);
        this.removeEventListener("keyUp", this);
        this.dispatchEvent({type: "focusOut"});
        this.drawFocus(false);
    } // End of the function
    function onSetFocus(oldFocus)
    {
        this.addEventListener("keyDown", this);
        this.addEventListener("keyUp", this);
        this.dispatchEvent({type: "focusIn"});
        if (this.getFocusManager().bDrawFocus != false)
        {
            this.drawFocus(true);
        } // end if
    } // End of the function
    function findFocusInChildren(o)
    {
        if (o.focusTextField != undefined)
        {
            return (o.focusTextField);
        } // end if
        if (o.tabEnabled == true)
        {
            return (o);
        } // end if
        return;
    } // End of the function
    function findFocusFromObject(o)
    {
        if (o.tabEnabled != true)
        {
            if (o._parent == undefined)
            {
                return;
            } // end if
            if (o._parent.tabEnabled == true)
            {
                o = o._parent;
            }
            else if (o._parent.tabChildren)
            {
                o = this.findFocusInChildren(o._parent);
            }
            else
            {
                o = this.findFocusFromObject(o._parent);
            } // end else if
        } // end else if
        return (o);
    } // End of the function
    function pressFocus()
    {
        var _loc3 = this.findFocusFromObject(this);
        var _loc2 = this.getFocus();
        if (_loc3 != _loc2)
        {
            _loc2.drawFocus(false);
            if (this.getFocusManager().bDrawFocus != false)
            {
                _loc3.drawFocus(true);
            } // end if
        } // end if
    } // End of the function
    function releaseFocus()
    {
        var _loc2 = this.findFocusFromObject(this);
        if (_loc2 != this.getFocus())
        {
            _loc2.setFocus();
        } // end if
    } // End of the function
    function isParent(o)
    {
        while (o != undefined)
        {
            if (o == this)
            {
                return (true);
            } // end if
            o = o._parent;
        } // end while
        return (false);
    } // End of the function
    function size()
    {
    } // End of the function
    function init()
    {
        super.init();
        _xscale = 100;
        _yscale = 100;
        _focusrect = _global.useFocusRect == false;
        this.watch("enabled", enabledChanged);
        if (enabled == false)
        {
            this.setEnabled(false);
        } // end if
    } // End of the function
    function dispatchValueChangedEvent(value)
    {
        this.dispatchEvent({type: "valueChanged", value: value});
    } // End of the function
    static var symbolName = "UIComponent";
    static var symbolOwner = mx.core.UIComponent;
    static var version = "2.0.2.126";
    static var kStretch = 5000;
    var focusEnabled = true;
    var tabEnabled = true;
    var origBorderStyles = {themeColor: 16711680};
    var clipParameters = {};
    static var mergedClipParameters = mx.core.UIObject.mergeClipParameters(mx.core.UIComponent.prototype.clipParameters, mx.core.UIObject.prototype.clipParameters);
} // End of Class
