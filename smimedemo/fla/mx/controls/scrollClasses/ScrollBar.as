class mx.controls.scrollClasses.ScrollBar extends mx.core.UIComponent
{
    var isScrolling, scrollTrack_mc, scrollThumb_mc, __get__scrollPosition, __get__pageScrollSize, __get__lineScrollSize, __height, tabEnabled, focusEnabled, boundingBox_mc, setSkin, upArrow_mc, _minHeight, _minWidth, downArrow_mc, createObject, createClassObject, enabled, __get__virtualHeight, __set__scrollPosition, _height, dispatchEvent, minMode, maxMode, plusMode, minusMode, _parent, getStyle, scrolling, _ymouse, __set__lineScrollSize, __set__pageScrollSize;
    function ScrollBar()
    {
        super();
    } // End of the function
    function get scrollPosition()
    {
        return (_scrollPosition);
    } // End of the function
    function set scrollPosition(pos)
    {
        _scrollPosition = pos;
        if (isScrolling != true)
        {
            pos = Math.min(pos, maxPos);
            pos = Math.max(pos, minPos);
            var _loc3 = (pos - minPos) * (scrollTrack_mc.height - scrollThumb_mc._height) / (maxPos - minPos) + scrollTrack_mc.top;
            scrollThumb_mc.move(0, _loc3);
        } // end if
        //return (this.scrollPosition());
        null;
    } // End of the function
    function get pageScrollSize()
    {
        return (largeScroll);
    } // End of the function
    function set pageScrollSize(lScroll)
    {
        largeScroll = lScroll;
        //return (this.pageScrollSize());
        null;
    } // End of the function
    function set lineScrollSize(sScroll)
    {
        smallScroll = sScroll;
        //return (this.lineScrollSize());
        null;
    } // End of the function
    function get lineScrollSize()
    {
        return (smallScroll);
    } // End of the function
    function get virtualHeight()
    {
        return (__height);
    } // End of the function
    function init(Void)
    {
        super.init();
        _scrollPosition = 0;
        tabEnabled = false;
        focusEnabled = false;
        boundingBox_mc._visible = false;
        boundingBox_mc._width = boundingBox_mc._height = 0;
    } // End of the function
    function createChildren(Void)
    {
        if (scrollTrack_mc == undefined)
        {
            this.setSkin(mx.controls.scrollClasses.ScrollBar.skinIDTrack, scrollTrackName);
        } // end if
        scrollTrack_mc.visible = false;
        var _loc3 = new Object();
        _loc3.enabled = false;
        _loc3.preset = mx.controls.SimpleButton.falseDisabled;
        _loc3.initProperties = 0;
        _loc3.autoRepeat = true;
        _loc3.tabEnabled = false;
        var _loc2;
        if (upArrow_mc == undefined)
        {
            _loc2 = this.createButton(upArrowName, "upArrow_mc", mx.controls.scrollClasses.ScrollBar.skinIDUpArrow, _loc3);
        } // end if
        _loc2.buttonDownHandler = onUpArrow;
        _loc2.clickHandler = onScrollChanged;
        _minHeight = _loc2.height;
        _minWidth = _loc2.width;
        if (downArrow_mc == undefined)
        {
            _loc2 = this.createButton(downArrowName, "downArrow_mc", mx.controls.scrollClasses.ScrollBar.skinIDDownArrow, _loc3);
        } // end if
        _loc2.buttonDownHandler = onDownArrow;
        _loc2.clickHandler = onScrollChanged;
        _minHeight = _minHeight + _loc2.height;
    } // End of the function
    function createButton(linkageName, id, skinID, o)
    {
        if (skinID == mx.controls.scrollClasses.ScrollBar.skinIDUpArrow)
        {
            o.falseUpSkin = upArrowUpName;
            o.falseDownSkin = upArrowDownName;
            o.falseOverSkin = upArrowOverName;
        }
        else
        {
            o.falseUpSkin = downArrowUpName;
            o.falseDownSkin = downArrowDownName;
            o.falseOverSkin = downArrowOverName;
        } // end else if
        var _loc3 = this.createObject(linkageName, id, skinID, o);
        this[id].visible = false;
        this[id].useHandCursor = false;
        return (_loc3);
    } // End of the function
    function createThumb(Void)
    {
        var _loc2 = new Object();
        _loc2.validateNow = true;
        _loc2.tabEnabled = false;
        _loc2.leftSkin = thumbTopName;
        _loc2.middleSkin = thumbMiddleName;
        _loc2.rightSkin = thumbBottomName;
        _loc2.gripSkin = thumbGripName;
        this.createClassObject(mx.controls.scrollClasses.ScrollThumb, "scrollThumb_mc", mx.controls.scrollClasses.ScrollBar.skinIDThumb, _loc2);
    } // End of the function
    function setScrollProperties(pSize, mnPos, mxPos, ls)
    {
        var _loc4;
        var _loc2 = scrollTrack_mc;
        pageSize = pSize;
        largeScroll = ls != undefined && ls > 0 ? (ls) : (pSize);
        minPos = Math.max(mnPos, 0);
        maxPos = Math.max(mxPos, 0);
        _scrollPosition = Math.max(minPos, _scrollPosition);
        _scrollPosition = Math.min(maxPos, _scrollPosition);
        if (maxPos - minPos > 0 && enabled)
        {
            var _loc5 = _scrollPosition;
            if (!initializing)
            {
                upArrow_mc.enabled = true;
                downArrow_mc.enabled = true;
            } // end if
            _loc2.onPress = _loc2.onDragOver = startTrackScroller;
            _loc2.onRelease = releaseScrolling;
            _loc2.onDragOut = _loc2.stopScrolling = stopScrolling;
            _loc2.onReleaseOutside = releaseScrolling;
            _loc2.useHandCursor = false;
            if (scrollThumb_mc == undefined)
            {
                this.createThumb();
            } // end if
            var _loc3 = scrollThumb_mc;
            if (scrollTrackOverName.length > 0)
            {
                _loc2.onRollOver = trackOver;
                _loc2.onRollOut = trackOut;
            } // end if
            _loc4 = pageSize / (maxPos - minPos + pageSize) * _loc2.height;
            if (_loc4 < _loc3.minHeight)
            {
                if (_loc2.height < _loc3.minHeight)
                {
                    _loc3.__set__visible(false);
                }
                else
                {
                    _loc4 = _loc3.minHeight;
                    _loc3.__set__visible(true);
                    _loc3.setSize(_minWidth, _loc3.minHeight + 0);
                } // end else if
            }
            else
            {
                _loc3.__set__visible(true);
                _loc3.setSize(_minWidth, _loc4);
            } // end else if
            _loc3.setRange(upArrow_mc.__get__height() + 0, this.__get__virtualHeight() - downArrow_mc.__get__height() - _loc3.__get__height(), minPos, maxPos);
            _loc5 = Math.min(_loc5, maxPos);
            this.__set__scrollPosition(Math.max(_loc5, minPos));
        }
        else
        {
            scrollThumb_mc.__set__visible(false);
            if (!initializing)
            {
                upArrow_mc.enabled = false;
                downArrow_mc.enabled = false;
            } // end if
            delete _loc2.onPress;
            delete _loc2.onDragOver;
            delete _loc2.onRelease;
            delete _loc2.onDragOut;
            delete _loc2.onRollOver;
            delete _loc2.onRollOut;
            delete _loc2.onReleaseOutside;
        } // end else if
        if (initializing)
        {
            scrollThumb_mc.__set__visible(false);
        } // end if
    } // End of the function
    function setEnabled(enabledFlag)
    {
        super.setEnabled(enabledFlag);
        this.setScrollProperties(pageSize, minPos, maxPos, largeScroll);
    } // End of the function
    function draw(Void)
    {
        if (initializing)
        {
            initializing = false;
            scrollTrack_mc.visible = true;
            upArrow_mc.__set__visible(true);
            downArrow_mc.__set__visible(true);
        } // end if
        this.size();
    } // End of the function
    function size(Void)
    {
        if (_height == 1)
        {
            return;
        } // end if
        if (upArrow_mc == undefined)
        {
            return;
        } // end if
        var _loc3 = upArrow_mc.__get__height();
        var _loc2 = downArrow_mc.__get__height();
        upArrow_mc.move(0, 0);
        var _loc4 = scrollTrack_mc;
        _loc4._y = _loc3;
        _loc4._height = this.__get__virtualHeight() - _loc3 - _loc2;
        downArrow_mc.move(0, this.__get__virtualHeight() - _loc2);
        this.setScrollProperties(pageSize, minPos, maxPos, largeScroll);
    } // End of the function
    function dispatchScrollEvent(detail)
    {
        this.dispatchEvent({type: "scroll", detail: detail});
    } // End of the function
    function isScrollBarKey(k)
    {
        if (k == 36)
        {
            if (this.__get__scrollPosition() != 0)
            {
                this.__set__scrollPosition(0);
                this.dispatchScrollEvent(minMode);
            } // end if
            return (true);
        }
        else if (k == 35)
        {
            if (this.__get__scrollPosition() < maxPos)
            {
                this.__set__scrollPosition(maxPos);
                this.dispatchScrollEvent(maxMode);
            } // end if
            return (true);
        } // end else if
        return (false);
    } // End of the function
    function scrollIt(inc, mode)
    {
        var _loc3 = smallScroll;
        if (inc != "Line")
        {
            _loc3 = largeScroll == 0 ? (pageSize) : (largeScroll);
        } // end if
        var _loc2 = _scrollPosition + mode * _loc3;
        if (_loc2 > maxPos)
        {
            _loc2 = maxPos;
        }
        else if (_loc2 < minPos)
        {
            _loc2 = minPos;
        } // end else if
        if (this.__get__scrollPosition() != _loc2)
        {
            this.__set__scrollPosition(_loc2);
            var _loc4 = mode < 0 ? (minusMode) : (plusMode);
            this.dispatchScrollEvent(inc + _loc4);
        } // end if
    } // End of the function
    function startTrackScroller(Void)
    {
        _parent.pressFocus();
        if (_parent.scrollTrackDownName.length > 0)
        {
            if (_parent.scrollTrackDown_mc == undefined)
            {
                _parent.setSkin(mx.controls.scrollClasses.ScrollBar.skinIDTrackDown, scrollTrackDownName);
            }
            else
            {
                _parent.scrollTrackDown_mc.visible = true;
            } // end if
        } // end else if
        _parent.trackScroller();
        _parent.scrolling = setInterval(_parent, "scrollInterval", this.getStyle("repeatDelay"), "Page", -1);
    } // End of the function
    function scrollInterval(inc, mode)
    {
        clearInterval(scrolling);
        if (inc == "Page")
        {
            this.trackScroller();
        }
        else
        {
            this.scrollIt(inc, mode);
        } // end else if
        scrolling = setInterval(this, "scrollInterval", this.getStyle("repeatInterval"), inc, mode);
    } // End of the function
    function trackScroller(Void)
    {
        if (scrollThumb_mc._y + scrollThumb_mc.__get__height() < _ymouse)
        {
            this.scrollIt("Page", 1);
        }
        else if (scrollThumb_mc._y > _ymouse)
        {
            this.scrollIt("Page", -1);
        } // end else if
    } // End of the function
    function dispatchScrollChangedEvent(Void)
    {
        this.dispatchEvent({type: "scrollChanged"});
    } // End of the function
    function stopScrolling(Void)
    {
        clearInterval(_parent.scrolling);
        _parent.scrollTrackDown_mc.visible = false;
    } // End of the function
    function releaseScrolling(Void)
    {
        _parent.releaseFocus();
        this.stopScrolling();
        _parent.dispatchScrollChangedEvent();
    } // End of the function
    function trackOver(Void)
    {
        if (_parent.scrollTrackOverName.length > 0)
        {
            if (_parent.scrollTrackOver_mc == undefined)
            {
                _parent.setSkin(mx.controls.scrollClasses.ScrollBar.skinIDTrackOver, scrollTrackOverName);
            }
            else
            {
                _parent.scrollTrackOver_mc.visible = true;
            } // end if
        } // end else if
    } // End of the function
    function trackOut(Void)
    {
        _parent.scrollTrackOver_mc.visible = false;
    } // End of the function
    function onUpArrow(Void)
    {
        _parent.scrollIt("Line", -1);
    } // End of the function
    function onDownArrow(Void)
    {
        _parent.scrollIt("Line", 1);
    } // End of the function
    function onScrollChanged(Void)
    {
        _parent.dispatchScrollChangedEvent();
    } // End of the function
    static var symbolOwner = mx.core.UIComponent;
    var className = "ScrollBar";
    var minPos = 0;
    var maxPos = 0;
    var pageSize = 0;
    var largeScroll = 0;
    var smallScroll = 1;
    var _scrollPosition = 0;
    var scrollTrackName = "ScrollTrack";
    var scrollTrackOverName = "";
    var scrollTrackDownName = "";
    var upArrowName = "BtnUpArrow";
    var upArrowUpName = "ScrollUpArrowUp";
    var upArrowOverName = "ScrollUpArrowOver";
    var upArrowDownName = "ScrollUpArrowDown";
    var downArrowName = "BtnDownArrow";
    var downArrowUpName = "ScrollDownArrowUp";
    var downArrowOverName = "ScrollDownArrowOver";
    var downArrowDownName = "ScrollDownArrowDown";
    var thumbTopName = "ScrollThumbTopUp";
    var thumbMiddleName = "ScrollThumbMiddleUp";
    var thumbBottomName = "ScrollThumbBottomUp";
    var thumbGripName = "ScrollThumbGripUp";
    static var skinIDTrack = 0;
    static var skinIDTrackOver = 1;
    static var skinIDTrackDown = 2;
    static var skinIDUpArrow = 3;
    static var skinIDDownArrow = 4;
    static var skinIDThumb = 5;
    var idNames = new Array("scrollTrack_mc", "scrollTrackOver_mc", "scrollTrackDown_mc", "upArrow_mc", "downArrow_mc");
    var clipParameters = {minPos: 1, maxPos: 1, pageSize: 1, scrollPosition: 1, lineScrollSize: 1, pageScrollSize: 1, visible: 1, enabled: 1};
    static var mergedClipParameters = mx.core.UIObject.mergeClipParameters(mx.controls.scrollClasses.ScrollBar.prototype.clipParameters, mx.core.UIComponent.prototype.clipParameters);
    var initializing = true;
} // End of Class
