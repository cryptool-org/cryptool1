class mx.controls.UIScrollBar extends mx.controls.scrollClasses.ScrollBar
{
    var textField, wasHorizontal, __set__horizontal, __get__horizontal, __height, __width, hscroll, hPosition, scroll, vPosition, __get___targetInstanceName, _parent, synchScroll, setScrollProperties, __set__scrollPosition, initializing, _rotation, _xscale, hScroller, vScroller, isScrolling, scrollPosition, dispatchEvent, __set___targetInstanceName, __get__height, __get__width;
    function UIScrollBar()
    {
        super();
    } // End of the function
    function init(Void)
    {
        super.init();
        textField.owner = this;
        this.__set__horizontal(wasHorizontal);
        if (this.__get__horizontal())
        {
            textField != undefined ? (super.setSize(textField._width, 16)) : (super.setSize(__width, __height));
        }
        else
        {
            textField != undefined ? (super.setSize(16, textField._height)) : (super.setSize(__width, __height));
        } // end else if
        if (this.__get__horizontal())
        {
            var _loc3 = __width;
            __height = __width;
            width = _loc3;
            __width = 16;
        } // end if
        textField.onScroller = function ()
        {
            hPosition = hscroll;
            vPosition = scroll - 1;
        };
        if (this.__get___targetInstanceName() != undefined)
        {
            this.setScrollTarget(this.__get___targetInstanceName());
            this.__get___targetInstanceName().addListener(this);
        } // end if
    } // End of the function
    function get _targetInstanceName()
    {
        return (textField);
    } // End of the function
    function get height()
    {
        if (wasHorizontal)
        {
            return (__width);
        }
        else
        {
            return (__height);
        } // end else if
    } // End of the function
    function get width()
    {
        if (wasHorizontal)
        {
            return (__height);
        }
        else
        {
            return (__width);
        } // end else if
    } // End of the function
    function size(Void)
    {
        super.size();
        this.onTextChanged();
    } // End of the function
    function draw()
    {
        super.draw();
    } // End of the function
    function set _targetInstanceName(t)
    {
        if (t == undefined)
        {
            textField.removeListener(this);
            delete textField[this.__get__horizontal() ? ("hScroller") : ("vScroller")];
            if (textField.hScroller != undefined && textField.vScroller != undefined)
            {
                textField.unwatch("text");
                textField.unwatch("htmltext");
            } // end if
        } // end if
        var _loc3 = _parent[t];
        textField = _parent[t];
        this.onTextChanged();
        //return (this._targetInstanceName());
        null;
    } // End of the function
    function setSize(w, h)
    {
        if (this.__get__horizontal())
        {
            super.setSize(h, w);
        }
        else
        {
            super.setSize(w, h);
        } // end else if
    } // End of the function
    function onTextChanged(Void)
    {
        if (textField == undefined)
        {
            return;
        } // end if
        clearInterval(synchScroll);
        if (this.__get__horizontal())
        {
            var _loc2 = textField.hscroll;
            this.setScrollProperties(textField._width, 0, textField.maxhscroll);
            this.__set__scrollPosition(Math.min(_loc2, textField.maxhscroll));
        }
        else
        {
            _loc2 = textField.scroll;
            var _loc3 = textField.bottomScroll - textField.scroll;
            this.setScrollProperties(_loc3, 1, textField.maxscroll);
            this.__set__scrollPosition(Math.min(_loc2, textField.maxscroll));
        } // end else if
    } // End of the function
    function get horizontal()
    {
        return (wasHorizontal);
    } // End of the function
    function set horizontal(v)
    {
        wasHorizontal = v;
        if (v && initializing)
        {
            if (_rotation == 90)
            {
                return;
            } // end if
            _xscale = -100;
            _rotation = -90;
        } // end if
        if (!initializing)
        {
            if (v)
            {
                if (_rotation == 0)
                {
                    _rotation = -90;
                    _xscale = -100;
                } // end if
            }
            else if (_rotation == -90)
            {
                _rotation = 0;
                _xscale = 100;
            } // end if
        } // end else if
        //return (this.horizontal());
        null;
    } // End of the function
    function callback(prop, oldval, newval)
    {
        clearInterval(hScroller.synchScroll);
        clearInterval(vScroller.synchScroll);
        hScroller.synchScroll = setInterval(hScroller, "onTextChanged", 50);
        vScroller.synchScroll = setInterval(vScroller, "onTextChanged", 50);
        return (newval);
    } // End of the function
    function setScrollTarget(tF)
    {
        if (tF == undefined)
        {
            textField.removeListener(this);
            delete textField[this.__get__horizontal() ? ("hScroller") : ("vScroller")];
            if (textField.hScroller != undefined && textField.vScroller != undefined)
            {
                textField.unwatch("text");
                textField.unwatch("htmltext");
            } // end if
        } // end if
        textField = undefined;
        if (!(tF instanceof TextField))
        {
            return;
        } // end if
        textField = tF;
        if (this.__get__horizontal())
        {
            textField.hScroller = this;
            textField.hScroller.lineScrollSize = 5;
        }
        else
        {
            textField.vScroller = this;
            textField.vScroller.lineScrollSize = 1;
        } // end else if
        this.onTextChanged();
        function onChanged(Void)
        {
            this.onTextChanged();
        } // End of the function
        function onScroller(Void)
        {
            if (!isScrolling)
            {
                if (!horizontal)
                {
                    scrollPosition = textField.scroll;
                }
                else
                {
                    scrollPosition = textField.hscroll;
                } // end if
            } // end else if
        } // End of the function
        textField.addListener(this);
        textField.watch("text", callback);
        textField.watch("htmlText", callback);
    } // End of the function
    function scrollHandler(Void)
    {
        if (this.__get__horizontal())
        {
            var _loc2 = textField.background;
            textField.hscroll = scrollPosition;
            textField.background = _loc2;
        }
        else
        {
            textField.scroll = scrollPosition;
        } // end else if
    } // End of the function
    function setEnabled(enable)
    {
        super.setEnabled(enable);
        if (enable)
        {
            textField.addListener(this);
        }
        else
        {
            textField.removeListener();
        } // end else if
    } // End of the function
    function dispatchScrollEvent(detail)
    {
        this.dispatchEvent({type: "scroll"});
    } // End of the function
    static var symbolName = "UIScrollBar";
    static var symbolOwner = mx.controls.UIScrollBar;
    var className = "UIScrollBar";
    var clipParameters = {_targetInstanceName: 1, horizontal: 1};
    static var mergedClipParameters = mx.core.UIObject.mergeClipParameters(mx.controls.UIScrollBar.prototype.clipParameters);
    static var version = "2.0.2.126";
} // End of Class
