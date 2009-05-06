class mx.controls.VScrollBar extends mx.controls.scrollClasses.ScrollBar
{
    var scrollIt;
    function VScrollBar()
    {
        super();
    } // End of the function
    function init(Void)
    {
        super.init();
    } // End of the function
    function isScrollBarKey(k)
    {
        if (k == 38)
        {
            this.scrollIt("Line", -1);
            return (true);
        }
        else if (k == 40)
        {
            this.scrollIt("Line", 1);
            return (true);
        }
        else if (k == 33)
        {
            this.scrollIt("Page", -1);
            return (true);
        }
        else if (k == 34)
        {
            this.scrollIt("Page", 1);
            return (true);
        } // end else if
        return (super.isScrollBarKey(k));
    } // End of the function
    static var symbolName = "VScrollBar";
    static var symbolOwner = mx.core.UIComponent;
    static var version = "2.0.2.126";
    var className = "VScrollBar";
    var minusMode = "Up";
    var plusMode = "Down";
    var minMode = "AtTop";
    var maxMode = "AtBottom";
} // End of Class
