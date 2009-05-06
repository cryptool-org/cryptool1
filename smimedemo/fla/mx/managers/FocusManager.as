class mx.managers.FocusManager extends mx.core.UIComponent
{
    var __defaultPushButton, defPushButton, __get__defaultPushButton, form, move, tabEnabled, _height, _width, _y, _x, _alpha, _parent, tabCapture, watch, lastMouse, _visible, lastFocus, doLater, lastSelFocus, cancelAllDoLaters, _searchKey, _lastTarget, _firstNode, _nextIsNext, _nextNode, _lastx, _prevNode, _needPrev, _foundList, _prevObj, _nextObj, _firstObj, _lastObj, _lastNode, lastTabFocus, findFocusFromObject, __set__defaultPushButton, __get__nextTabIndex;
    function FocusManager()
    {
        super();
    } // End of the function
    function get defaultPushButton()
    {
        return (__defaultPushButton);
    } // End of the function
    function set defaultPushButton(x)
    {
        if (x != __defaultPushButton)
        {
            __defaultPushButton.__set__emphasized(false);
            __defaultPushButton = x;
            defPushButton = x;
            x.__set__emphasized(true);
        } // end if
        //return (this.defaultPushButton());
        null;
    } // End of the function
    function getMaxTabIndex(o)
    {
        var _loc3 = 0;
        var _loc6;
        for (var _loc6 in o)
        {
            var _loc2 = o[_loc6];
            if (_loc2._parent == o)
            {
                if (_loc2.tabIndex != undefined)
                {
                    if (_loc2.tabIndex > _loc3)
                    {
                        _loc3 = _loc2.tabIndex;
                    } // end if
                } // end if
                if (_loc2.tabChildren == true)
                {
                    var _loc4 = this.getMaxTabIndex(_loc2);
                    if (_loc4 > _loc3)
                    {
                        _loc3 = _loc4;
                    } // end if
                } // end if
            } // end if
        } // end of for...in
        return (_loc3);
    } // End of the function
    function getNextTabIndex(Void)
    {
        return (this.getMaxTabIndex(form) + 1);
    } // End of the function
    function get nextTabIndex()
    {
        return (this.getNextTabIndex());
    } // End of the function
    function relocate(Void)
    {
        var _loc2 = mx.managers.SystemManager.__get__screen();
        this.move(_loc2.x - 1, _loc2.y - 1);
    } // End of the function
    function init(Void)
    {
        super.init();
        tabEnabled = false;
        _width = _height = 1;
        _x = _y = -1;
        _alpha = 0;
        _parent.focusManager = this;
        _parent.tabChildren = true;
        _parent.tabEnabled = false;
        form = _parent;
        _parent.addEventListener("hide", this);
        _parent.addEventListener("reveal", this);
        mx.managers.SystemManager.init();
        mx.managers.SystemManager.addFocusManager(form);
        tabCapture.tabIndex = 0;
        this.watch("enabled", enabledChanged);
        Selection.addListener(this);
        lastMouse = new Object();
        _global.ASSetPropFlags(_parent, "focusManager", 1);
        _global.ASSetPropFlags(_parent, "tabChildren", 1);
        _global.ASSetPropFlags(_parent, "tabEnabled", 1);
    } // End of the function
    function enabledChanged(id, oldValue, newValue)
    {
        _visible = newValue;
        return (newValue);
    } // End of the function
    function activate(Void)
    {
        Key.addListener(this);
        activated = _visible = true;
        if (lastFocus != undefined)
        {
            bNeedFocus = true;
            if (!mx.managers.SystemManager.isMouseDown)
            {
                this.doLater(this, "restoreFocus");
            } // end if
        } // end if
    } // End of the function
    function deactivate(Void)
    {
        Key.removeListener(this);
        activated = _visible = false;
        var _loc2 = this.getSelectionFocus();
        var _loc3 = this.getActualFocus(_loc2);
        if (this.isOurFocus(_loc3))
        {
            lastSelFocus = _loc2;
            lastFocus = _loc3;
        } // end if
        this.cancelAllDoLaters();
    } // End of the function
    function isOurFocus(o)
    {
        if (o.focusManager == this)
        {
            return (true);
        } // end if
        while (o != undefined)
        {
            if (o.focusManager != undefined)
            {
                return (false);
            } // end if
            if (o._parent == _parent)
            {
                return (true);
            } // end if
            o = o._parent;
        } // end while
        return (false);
    } // End of the function
    function onSetFocus(o, n)
    {
        if (n == null)
        {
            if (activated)
            {
                bNeedFocus = true;
            } // end if
        }
        else
        {
            var _loc2 = this.getFocus();
            if (this.isOurFocus(_loc2))
            {
                bNeedFocus = false;
                lastFocus = _loc2;
                lastSelFocus = n;
            } // end if
        } // end else if
    } // End of the function
    function restoreFocus(Void)
    {
        var _loc2 = lastSelFocus.hscroll;
        if (_loc2 != undefined)
        {
            var _loc5 = lastSelFocus.scroll;
            var _loc4 = lastSelFocus.background;
        } // end if
        lastFocus.setFocus();
        var _loc3 = Selection;
        Selection.setSelection(_loc3.lastBeginIndex, _loc3.lastEndIndex);
        if (_loc2 != undefined)
        {
            lastSelFocus.scroll = _loc5;
            lastSelFocus.hscroll = _loc2;
            lastSelFocus.background = _loc4;
        } // end if
    } // End of the function
    function onUnload(Void)
    {
        mx.managers.SystemManager.removeFocusManager(form);
    } // End of the function
    function setFocus(o)
    {
        if (o == null)
        {
            Selection.setFocus(null);
        }
        else if (o.setFocus == undefined)
        {
            Selection.setFocus(o);
        }
        else
        {
            o.setFocus();
        } // end else if
    } // End of the function
    function getActualFocus(o)
    {
        for (var _loc1 = o._parent; _loc1 != undefined; _loc1 = o._parent)
        {
            if (_loc1.focusTextField != undefined)
            {
                while (_loc1.focusTextField != undefined)
                {
                    o = _loc1;
                    _loc1 = _loc1._parent;
                    if (_loc1 == undefined)
                    {
                        return;
                    } // end if
                    if (_loc1.focusTextField == undefined)
                    {
                        return (o);
                    } // end if
                } // end while
            } // end if
            if (_loc1.tabEnabled != true)
            {
                return (o);
            } // end if
            o = _loc1;
        } // end of for
        return;
    } // End of the function
    function getSelectionFocus()
    {
        var m = Selection.getFocus();
        var o = eval(m);
        return (o);
    } // End of the function
    function getFocus(Void)
    {
        var _loc2 = this.getSelectionFocus();
        return (this.getActualFocus(_loc2));
    } // End of the function
    function walkTree(p, index, groupName, dir, lookup, firstChild)
    {
        var _loc5 = true;
        var _loc11;
        for (var _loc11 in p)
        {
            var _loc2 = p[_loc11];
            if (_loc2._parent == p && _loc2.enabled != false && _loc2._visible != false && (_loc2.tabEnabled == true || _loc2.tabEnabled != false && (_loc2.onPress != undefined || _loc2.onRelease != undefined || _loc2.onReleaseOutside != undefined || _loc2.onDragOut != undefined || _loc2.onDragOver != undefined || _loc2.onRollOver != undefined || _loc2.onRollOut != undefined || _loc2 instanceof TextField)))
            {
                if (_loc2._searchKey == _searchKey)
                {
                    continue;
                } // end if
                _loc2._searchKey = _searchKey;
                if (_loc2 != _lastTarget)
                {
                    if ((_loc2.groupName != undefined || groupName != undefined) && _loc2.groupName == groupName)
                    {
                        continue;
                    } // end if
                    if (_loc2 instanceof TextField && _loc2.selectable == false)
                    {
                        continue;
                    } // end if
                    if (_loc5 || _loc2.groupName != undefined && _loc2.groupName == _firstNode.groupName && _loc2.selected == true)
                    {
                        if (firstChild)
                        {
                            _firstNode = _loc2;
                            firstChild = false;
                        } // end if
                    } // end if
                    if (_nextIsNext == true)
                    {
                        if (_loc2.groupName != undefined && _loc2.groupName == _nextNode.groupName && _loc2.selected == true || _nextNode == undefined && (_loc2.groupName == undefined || _loc2.groupName != undefined && _loc2.groupName != groupName))
                        {
                            _nextNode = _loc2;
                        } // end if
                    } // end if
                    if (_loc2.groupName == undefined || groupName != _loc2.groupName)
                    {
                        if (_lastx.groupName != undefined && _loc2.groupName == _lastx.groupName && _lastx.selected == true)
                        {
                        }
                        else
                        {
                            _lastx = _loc2;
                        } // end if
                    } // end else if
                }
                else
                {
                    _prevNode = _lastx;
                    _needPrev = false;
                    _nextIsNext = true;
                } // end else if
                if (_loc2.tabIndex != undefined)
                {
                    if (_loc2.tabIndex == index)
                    {
                        if (_foundList[_loc2._name] == undefined)
                        {
                            if (_needPrev)
                            {
                                _prevObj = _loc2;
                                _needPrev = false;
                            } // end if
                            _nextObj = _loc2;
                        } // end if
                    } // end if
                    if (dir && _loc2.tabIndex > index)
                    {
                        if (_nextObj == undefined || _nextObj.tabIndex > _loc2.tabIndex && (_loc2.groupName == undefined || _nextObj.groupName == undefined || _loc2.groupName != _nextObj.groupName) || _nextObj.groupName != undefined && _nextObj.groupName == _loc2.groupName && _nextObj.selected != true && (_loc2.selected == true || _nextObj.tabIndex > _loc2.tabIndex))
                        {
                            _nextObj = _loc2;
                        } // end if
                    }
                    else if (!dir && _loc2.tabIndex < index)
                    {
                        if (_prevObj == undefined || _prevObj.tabIndex < _loc2.tabIndex && (_loc2.groupName == undefined || _prevObj.groupName == undefined || _loc2.groupName != _prevObj.groupName) || _prevObj.groupName != undefined && _prevObj.groupName == _loc2.groupName && _prevObj.selected != true && (_loc2.selected == true || _prevObj.tabIndex < _loc2.tabIndex))
                        {
                            _prevObj = _loc2;
                        } // end if
                    } // end else if
                    if (_firstObj == undefined || _loc2.tabIndex < _firstObj.tabIndex && (_loc2.groupName == undefined || _firstObj.groupName == undefined || _loc2.groupName != _firstObj.groupName) || _firstObj.groupName != undefined && _firstObj.groupName == _loc2.groupName && _firstObj.selected != true && (_loc2.selected == true || _loc2.tabIndex < _firstObj.tabIndex))
                    {
                        _firstObj = _loc2;
                    } // end if
                    if (_lastObj == undefined || _loc2.tabIndex > _lastObj.tabIndex && (_loc2.groupName == undefined || _lastObj.groupName == undefined || _loc2.groupName != _lastObj.groupName) || _lastObj.groupName != undefined && _lastObj.groupName == _loc2.groupName && _lastObj.selected != true && (_loc2.selected == true || _loc2.tabIndex > _lastObj.tabIndex))
                    {
                        _lastObj = _loc2;
                    } // end if
                } // end if
                if (_loc2.tabChildren)
                {
                    this.getTabCandidateFromChildren(_loc2, index, groupName, dir, _loc5 && firstChild);
                } // end if
                _loc5 = false;
                continue;
            } // end if
            if (_loc2._parent == p && _loc2.tabChildren == true && _loc2._visible != false)
            {
                if (_loc2 == _lastTarget)
                {
                    if (_loc2._searchKey == _searchKey)
                    {
                        continue;
                    } // end if
                    _loc2._searchKey = _searchKey;
                    if (_prevNode == undefined)
                    {
                        var _loc3 = _lastx;
                        var _loc7 = false;
                        while (_loc3 != undefined)
                        {
                            if (_loc3 == _loc2)
                            {
                                _loc7 = true;
                                break;
                            } // end if
                            _loc3 = _loc3._parent;
                        } // end while
                        if (_loc7 == false)
                        {
                            _prevNode = _lastx;
                        } // end if
                    } // end if
                    _needPrev = false;
                    if (_nextNode == undefined)
                    {
                        _nextIsNext = true;
                    } // end if
                }
                else if (!(_loc2.focusManager != undefined && _loc2.focusManager._parent == _loc2))
                {
                    if (_loc2._searchKey == _searchKey)
                    {
                        continue;
                    } // end if
                    _loc2._searchKey = _searchKey;
                    this.getTabCandidateFromChildren(_loc2, index, groupName, dir, _loc5 && firstChild);
                } // end else if
                _loc5 = false;
            } // end if
        } // end of for...in
        _lastNode = _lastx;
        if (lookup)
        {
            if (p._parent != undefined)
            {
                if (p != _parent)
                {
                    if (_prevNode == undefined && dir)
                    {
                        _needPrev = true;
                    }
                    else if (_nextNode == undefined && !dir)
                    {
                        _nextIsNext = false;
                    } // end else if
                    _lastTarget = _lastTarget._parent;
                    this.getTabCandidate(p._parent, index, groupName, dir, true);
                } // end if
            } // end if
        } // end if
    } // End of the function
    function getTabCandidate(o, index, groupName, dir, firstChild)
    {
        var _loc2;
        var _loc3 = true;
        if (o == _parent)
        {
            _loc2 = o;
            _loc3 = false;
        }
        else
        {
            _loc2 = o._parent;
            if (_loc2 == undefined)
            {
                _loc2 = o;
                _loc3 = false;
            } // end if
        } // end else if
        this.walkTree(_loc2, index, groupName, dir, _loc3, firstChild);
    } // End of the function
    function getTabCandidateFromChildren(o, index, groupName, dir, firstChild)
    {
        this.walkTree(o, index, groupName, dir, false, firstChild);
    } // End of the function
    function getFocusManagerFromObject(o)
    {
        while (o != undefined)
        {
            if (o.focusManager != undefined)
            {
                return (o.focusManager);
            } // end if
            o = o._parent;
        } // end while
        return;
    } // End of the function
    function tabHandler(Void)
    {
        bDrawFocus = true;
        var _loc5 = this.getSelectionFocus();
        var _loc4 = this.getActualFocus(_loc5);
        if (_loc4 != _loc5)
        {
            _loc5 = _loc4;
        } // end if
        if (this.getFocusManagerFromObject(_loc5) != this)
        {
            _loc5 == undefined;
        } // end if
        if (_loc5 == undefined)
        {
            _loc5 = form;
        }
        else if (_loc5.tabIndex != undefined)
        {
            if (_foundList != undefined || _foundList.tabIndex != _loc5.tabIndex)
            {
                _foundList = new Object();
                _foundList.tabIndex = _loc5.tabIndex;
            } // end if
            _foundList[_loc5._name] = _loc5;
        } // end else if
        var _loc3 = Key.isDown(16) != true;
        _searchKey = getTimer();
        _needPrev = true;
        _nextIsNext = false;
        _lastx = undefined;
        _firstNode = undefined;
        _lastNode = undefined;
        _nextNode = undefined;
        _prevNode = undefined;
        _firstObj = undefined;
        _lastObj = undefined;
        _nextObj = undefined;
        _prevObj = undefined;
        _lastTarget = _loc5;
        var _loc6 = _loc5;
        this.getTabCandidate(_loc6, _loc5.tabIndex == undefined ? (0) : (_loc5.tabIndex), _loc5.groupName, _loc3, true);
        var _loc2;
        if (_loc3)
        {
            if (_nextObj != undefined)
            {
                _loc2 = _nextObj;
            }
            else
            {
                _loc2 = _firstObj;
            } // end else if
        }
        else if (_prevObj != undefined)
        {
            _loc2 = _prevObj;
        }
        else
        {
            _loc2 = _lastObj;
        } // end else if
        if (_loc2.tabIndex != _loc5.tabIndex)
        {
            _foundList = new Object();
            _foundList.tabIndex = _loc2.tabIndex;
            _foundList[_loc2._name] = _loc2;
        }
        else
        {
            if (_foundList == undefined)
            {
                _foundList = new Object();
                _foundList.tabIndex = _loc2.tabIndex;
            } // end if
            _foundList[_loc2._name] = _loc2;
        } // end else if
        if (_loc2 == undefined)
        {
            if (_loc3 == false)
            {
                if (_nextNode != undefined)
                {
                    _loc2 = _nextNode;
                }
                else
                {
                    _loc2 = _firstNode;
                } // end else if
            }
            else if (_prevNode == undefined || _loc5 == form)
            {
                _loc2 = _lastNode;
            }
            else
            {
                _loc2 = _prevNode;
            } // end else if
        } // end else if
        if (_loc2 == undefined)
        {
            return;
        } // end if
        lastTabFocus = _loc2;
        this.setFocus(_loc2);
        if (_loc2.emphasized != undefined)
        {
            if (defPushButton != undefined)
            {
                _loc5 = defPushButton;
                defPushButton = _loc2;
                _loc5.emphasized = false;
                _loc2.emphasized = true;
            } // end if
        }
        else if (defPushButton != undefined && defPushButton != __defaultPushButton)
        {
            _loc5 = defPushButton;
            defPushButton = __defaultPushButton;
            _loc5.emphasized = false;
            __defaultPushButton.__set__emphasized(true);
        } // end else if
    } // End of the function
    function onKeyDown(Void)
    {
        mx.managers.SystemManager.idleFrames = 0;
        if (defaultPushButtonEnabled)
        {
            if (Key.getCode() == 13)
            {
                if (this.__get__defaultPushButton() != undefined)
                {
                    this.doLater(this, "sendDefaultPushButtonEvent");
                } // end if
            } // end if
        } // end if
    } // End of the function
    function sendDefaultPushButtonEvent(Void)
    {
        defPushButton.dispatchEvent({type: "click"});
    } // End of the function
    function getMousedComponentFromChildren(x, y, o)
    {
        for (var _loc7 in o)
        {
            var _loc2 = o[_loc7];
            if (_loc2._visible && _loc2.enabled && _loc2._parent == o && _loc2._searchKey != _searchKey)
            {
                _loc2._searchKey = _searchKey;
                if (_loc2.hitTest(x, y, true))
                {
                    if (_loc2.onPress != undefined || _loc2.onRelease != undefined)
                    {
                        return (_loc2);
                    } // end if
                    var _loc3 = this.getMousedComponentFromChildren(x, y, _loc2);
                    if (_loc3 != undefined)
                    {
                        return (_loc3);
                    } // end if
                    return (_loc2);
                } // end if
            } // end if
        } // end of for...in
        return;
    } // End of the function
    function mouseActivate(Void)
    {
        if (!bNeedFocus)
        {
            return;
        } // end if
        _searchKey = getTimer();
        var _loc2 = this.getMousedComponentFromChildren(lastMouse.x, lastMouse.y, form);
        if (_loc2 instanceof mx.core.UIComponent)
        {
            return;
        } // end if
        _loc2 = this.findFocusFromObject(_loc2);
        if (_loc2 == lastFocus)
        {
            return;
        } // end if
        if (_loc2 == undefined)
        {
            this.doLater(this, "restoreFocus");
            return;
        } // end if
        var _loc3 = _loc2.hscroll;
        if (_loc3 != undefined)
        {
            var _loc6 = _loc2.scroll;
            var _loc5 = _loc2.background;
        } // end if
        this.setFocus(_loc2);
        var _loc4 = Selection;
        Selection.setSelection(_loc4.lastBeginIndex, _loc4.lastEndIndex);
        if (_loc3 != undefined)
        {
            _loc2.scroll = _loc6;
            _loc2.hscroll = _loc3;
            _loc2.background = _loc5;
        } // end if
    } // End of the function
    function _onMouseDown(Void)
    {
        bDrawFocus = false;
        if (lastFocus != undefined)
        {
            lastFocus.drawFocus(false);
        } // end if
        mx.managers.SystemManager.idleFrames = 0;
        var _loc3 = Selection;
        _loc3.lastBeginIndex = Selection.getBeginIndex();
        _loc3.lastEndIndex = Selection.getEndIndex();
        lastMouse.x = _root._xmouse;
        lastMouse.y = _root._ymouse;
        _root.localToGlobal(lastMouse);
    } // End of the function
    function onMouseUp(Void)
    {
        if (_visible)
        {
            this.doLater(this, "mouseActivate");
        } // end if
    } // End of the function
    function handleEvent(e)
    {
        if (e.type == "reveal")
        {
            mx.managers.SystemManager.activate(form);
        }
        else
        {
            mx.managers.SystemManager.deactivate(form);
        } // end else if
    } // End of the function
    static function enableFocusManagement()
    {
        if (!mx.managers.FocusManager.initialized)
        {
            initialized = true;
            Object.registerClass("FocusManager", mx.managers.FocusManager);
            if (_root.focusManager == undefined)
            {
                _root.createClassObject(mx.managers.FocusManager, "focusManager", mx.managers.DepthManager.highestDepth--);
            } // end if
        } // end if
    } // End of the function
    static var symbolName = "FocusManager";
    static var symbolOwner = mx.managers.FocusManager;
    static var version = "2.0.2.126";
    var className = "FocusManager";
    var bNeedFocus = false;
    var bDrawFocus = false;
    var defaultPushButtonEnabled = true;
    var activated = true;
    static var initialized = false;
    static var UIObjectExtensionsDependency = mx.core.ext.UIObjectExtensions;
} // End of Class
