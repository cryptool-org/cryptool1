class mx.core.ext.UIComponentExtensions
{
    var tabEnabled, getFocusManager, drawFocus;
    function UIComponentExtensions()
    {
    } // End of the function
    static function Extensions()
    {
        if (mx.core.ext.UIComponentExtensions.bExtended == true)
        {
            return (true);
        } // end if
        bExtended = true;
        TextField.prototype.setFocus = function ()
        {
            Selection.setFocus(this);
        };
        TextField.prototype.onSetFocus = function (oldFocus)
        {
            if (tabEnabled != false)
            {
                if (this.getFocusManager().bDrawFocus)
                {
                    this.drawFocus(true);
                } // end if
            } // end if
        };
        TextField.prototype.onKillFocus = function (oldFocus)
        {
            if (tabEnabled != false)
            {
                this.drawFocus(false);
            } // end if
        };
        TextField.prototype.drawFocus = mx.core.UIComponent.prototype.drawFocus;
        TextField.prototype.getFocusManager = mx.core.UIComponent.prototype.getFocusManager;
        mx.managers.OverlappedWindows.enableOverlappedWindows();
        mx.styles.CSSSetStyle.enableRunTimeCSS();
        mx.managers.FocusManager.enableFocusManagement();
    } // End of the function
    static var bExtended = false;
    static var UIComponentExtended = mx.core.ext.UIComponentExtensions.Extensions();
    static var UIComponentDependency = mx.core.UIComponent;
    static var FocusManagerDependency = mx.managers.FocusManager;
    static var OverlappedWindowsDependency = mx.managers.OverlappedWindows;
} // End of Class
