class mx.skins.halo.FocusRect extends mx.skins.SkinElement
{
    var boundingBox_mc, _yscale, _xscale, clear, beginFill, drawRoundRect, endFill, _visible, _parent, removeEventListener, getDepth, addEventListener, getStyle, height, width, y, x;
    function FocusRect()
    {
        super();
        boundingBox_mc._visible = false;
        boundingBox_mc._width = boundingBox_mc._height = 0;
    } // End of the function
    function draw(o)
    {
        o.adjustFocusRect();
    } // End of the function
    function setSize(w, h, r, a, rectCol)
    {
        _xscale = _yscale = 100;
        this.clear();
        if (typeof(r) == "object")
        {
            r.br = r.br > 2 ? (r.br - 2) : (0);
            r.bl = r.bl > 2 ? (r.bl - 2) : (0);
            r.tr = r.tr > 2 ? (r.tr - 2) : (0);
            r.tl = r.tl > 2 ? (r.tl - 2) : (0);
            this.beginFill(rectCol, a * 3.000000E-001);
            this.drawRoundRect(0, 0, w, h, r);
            this.drawRoundRect(2, 2, w - 4, h - 4, r);
            this.endFill();
            r.br = r.br > 1 ? (r.br + 1) : (0);
            r.bl = r.bl > 1 ? (r.bl + 1) : (0);
            r.tr = r.tr > 1 ? (r.tr + 1) : (0);
            r.tl = r.tl > 1 ? (r.tl + 1) : (0);
            this.beginFill(rectCol, a * 3.000000E-001);
            this.drawRoundRect(1, 1, w - 2, h - 2, r);
            r.br = r.br > 1 ? (r.br - 1) : (0);
            r.bl = r.bl > 1 ? (r.bl - 1) : (0);
            r.tr = r.tr > 1 ? (r.tr - 1) : (0);
            r.tl = r.tl > 1 ? (r.tl - 1) : (0);
            this.drawRoundRect(2, 2, w - 4, h - 4, r);
            this.endFill();
        }
        else
        {
            var _loc5;
            if (r != 0)
            {
                _loc5 = r - 2;
            }
            else
            {
                _loc5 = 0;
            } // end else if
            this.beginFill(rectCol, a * 3.000000E-001);
            this.drawRoundRect(0, 0, w, h, r);
            this.drawRoundRect(2, 2, w - 4, h - 4, _loc5);
            this.endFill();
            this.beginFill(rectCol, a * 3.000000E-001);
            if (r != 0)
            {
                _loc5 = r - 2;
                r = r - 1;
            }
            else
            {
                _loc5 = 0;
                r = 0;
            } // end else if
            this.drawRoundRect(1, 1, w - 2, h - 2, r);
            this.drawRoundRect(2, 2, w - 4, h - 4, _loc5);
            this.endFill();
        } // end else if
    } // End of the function
    function handleEvent(e)
    {
        if (e.type == "unload")
        {
            _visible = true;
        }
        else if (e.type == "resize")
        {
            e.target.adjustFocusRect();
        }
        else if (e.type == "move")
        {
            e.target.adjustFocusRect();
        } // end else if
    } // End of the function
    static function classConstruct()
    {
        mx.core.UIComponent.prototype.drawFocus = function (focused)
        {
            var _loc2 = _parent.focus_mc;
            if (!focused)
            {
                _loc2._visible = false;
                this.removeEventListener("unload", _loc2);
                this.removeEventListener("move", _loc2);
                this.removeEventListener("resize", _loc2);
            }
            else
            {
                if (_loc2 == undefined)
                {
                    _loc2 = _parent.createChildAtDepth("FocusRect", mx.managers.DepthManager.kTop);
                    _loc2.tabEnabled = false;
                    _parent.focus_mc = _loc2;
                }
                else
                {
                    _loc2._visible = true;
                } // end else if
                _loc2.draw(this);
                if (_loc2.getDepth() < this.getDepth())
                {
                    _loc2.setDepthAbove(this);
                } // end if
                this.addEventListener("unload", _loc2);
                this.addEventListener("move", _loc2);
                this.addEventListener("resize", _loc2);
            } // end else if
        };
        mx.core.UIComponent.prototype.adjustFocusRect = function ()
        {
            var _loc2 = this.getStyle("themeColor");
            if (_loc2 == undefined)
            {
                _loc2 = 8453965;
            } // end if
            var _loc3 = _parent.focus_mc;
            _loc3.setSize(width + 4, height + 4, 0, 100, _loc2);
            _loc3.move(x - 2, y - 2);
        };
        TextField.prototype.drawFocus = mx.core.UIComponent.prototype.drawFocus;
        TextField.prototype.adjustFocusRect = mx.core.UIComponent.prototype.adjustFocusRect;
        mx.skins.halo.FocusRect.prototype.drawRoundRect = mx.skins.halo.Defaults.prototype.drawRoundRect;
        return (true);
    } // End of the function
    static var classConstructed = mx.skins.halo.FocusRect.classConstruct();
    static var DefaultsDependency = mx.skins.halo.Defaults;
    static var UIComponentDependency = mx.core.UIComponent;
} // End of Class
