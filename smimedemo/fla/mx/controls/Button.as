class mx.controls.Button extends mx.controls.SimpleButton
{
    var initializing, labelPath, initIcon, getState, enabled, phase, idNames, __width, __height, setState, invalidate, __get__labelPlacement, iconName, __get__label, refresh, createLabel, _iconLinkageName, removeIcons, __get__icon, hitArea_mc, createEmptyObject, __set__icon, __set__label, __set__labelPlacement;
    function Button()
    {
        super();
    } // End of the function
    function init(Void)
    {
        super.init();
    } // End of the function
    function draw()
    {
        if (initializing)
        {
            labelPath.visible = true;
        } // end if
        super.draw();
        if (initIcon != undefined)
        {
            this._setIcon(initIcon);
        } // end if
        delete this.initIcon;
    } // End of the function
    function onRelease(Void)
    {
        super.onRelease();
    } // End of the function
    function createChildren(Void)
    {
        super.createChildren();
    } // End of the function
    function setSkin(tag, linkageName, initobj)
    {
        return (super.setSkin(tag, linkageName, initobj));
    } // End of the function
    function viewSkin(varName)
    {
        var _loc3 = this.getState() ? ("true") : ("false");
        _loc3 = _loc3 + (enabled ? (phase) : ("disabled"));
        super.viewSkin(varName, {styleName: this, borderStyle: _loc3});
    } // End of the function
    function invalidateStyle(c)
    {
        labelPath.invalidateStyle(c);
        super.invalidateStyle(c);
    } // End of the function
    function setColor(c)
    {
        for (var _loc2 = 0; _loc2 < 8; ++_loc2)
        {
            this[idNames[_loc2]].redraw(true);
        } // end of for
    } // End of the function
    function setEnabled(enable)
    {
        labelPath.enabled = enable;
        super.setEnabled(enable);
    } // End of the function
    function calcSize(tag, ref)
    {
        if (__width == undefined || __height == undefined)
        {
            return;
        } // end if
        if (tag < 7)
        {
            ref.setSize(__width, __height, true);
        } // end if
    } // End of the function
    function size(Void)
    {
        this.setState(this.getState());
        this.setHitArea(__width, __height);
        for (var _loc3 = 0; _loc3 < 8; ++_loc3)
        {
            var _loc4 = idNames[_loc3];
            if (typeof(this[_loc4]) == "movieclip")
            {
                this[_loc4].setSize(__width, __height, true);
            } // end if
        } // end of for
        super.size();
    } // End of the function
    function set labelPlacement(val)
    {
        __labelPlacement = val;
        this.invalidate();
        //return (this.labelPlacement());
        null;
    } // End of the function
    function get labelPlacement()
    {
        return (__labelPlacement);
    } // End of the function
    function getLabelPlacement(Void)
    {
        return (__labelPlacement);
    } // End of the function
    function setLabelPlacement(val)
    {
        __labelPlacement = val;
        this.invalidate();
    } // End of the function
    function getBtnOffset(Void)
    {
        if (this.getState())
        {
            var _loc2 = btnOffset;
        }
        else if (phase == "down")
        {
            _loc2 = btnOffset;
        }
        else
        {
            _loc2 = 0;
        } // end else if
        return (_loc2);
    } // End of the function
    function setView(offset)
    {
        var _loc16 = offset ? (btnOffset) : (0);
        var _loc12 = this.getLabelPlacement();
        var _loc7 = 0;
        var _loc6 = 0;
        var _loc9 = 0;
        var _loc8 = 0;
        var _loc5 = 0;
        var _loc4 = 0;
        var _loc3 = labelPath;
        var _loc2 = iconName;
        var _loc15 = _loc3.textWidth;
        var _loc14 = _loc3.textHeight;
        var _loc10 = __width - borderW - borderW;
        var _loc11 = __height - borderW - borderW;
        if (_loc2 != undefined)
        {
            _loc7 = _loc2._width;
            _loc6 = _loc2._height;
        } // end if
        if (_loc12 == "left" || _loc12 == "right")
        {
            if (_loc3 != undefined)
            {
                _loc9 = Math.min(_loc10 - _loc7, _loc15 + 5);
                _loc3._width = Math.min(_loc10 - _loc7, _loc15 + 5);
                _loc8 = Math.min(_loc11, _loc14 + 5);
                _loc3._height = Math.min(_loc11, _loc14 + 5);
            } // end if
            if (_loc12 == "right")
            {
                _loc5 = _loc7;
                if (centerContent)
                {
                    _loc5 = _loc5 + (_loc10 - _loc9 - _loc7) / 2;
                } // end if
                _loc2._x = _loc5 - _loc7;
            }
            else
            {
                _loc5 = _loc10 - _loc9 - _loc7;
                if (centerContent)
                {
                    _loc5 = _loc5 / 2;
                } // end if
                _loc2._x = _loc5 + _loc9;
            } // end else if
            _loc4 = 0;
            _loc2._y = 0;
            if (centerContent)
            {
                _loc2._y = (_loc11 - _loc6) / 2;
                _loc4 = (_loc11 - _loc8) / 2;
            } // end if
            if (!centerContent)
            {
                _loc2._y = _loc2._y + Math.max(0, (_loc8 - _loc6) / 2);
            } // end if
        }
        else
        {
            if (_loc3 != undefined)
            {
                _loc9 = Math.min(_loc10, _loc15 + 5);
                _loc3._width = Math.min(_loc10, _loc15 + 5);
                _loc8 = Math.min(_loc11 - _loc6, _loc14 + 5);
                _loc3._height = Math.min(_loc11 - _loc6, _loc14 + 5);
            } // end if
            _loc5 = (_loc10 - _loc9) / 2;
            _loc2._x = (_loc10 - _loc7) / 2;
            if (_loc12 == "top")
            {
                _loc4 = _loc11 - _loc8 - _loc6;
                if (centerContent)
                {
                    _loc4 = _loc4 / 2;
                } // end if
                _loc2._y = _loc4 + _loc8;
            }
            else
            {
                _loc4 = _loc6;
                if (centerContent)
                {
                    _loc4 = _loc4 + (_loc11 - _loc8 - _loc6) / 2;
                } // end if
                _loc2._y = _loc4 - _loc6;
            } // end else if
        } // end else if
        var _loc13 = borderW + _loc16;
        _loc3._x = _loc5 + _loc13;
        _loc3._y = _loc4 + _loc13;
        _loc2._x = _loc2._x + _loc13;
        _loc2._y = _loc2._y + _loc13;
    } // End of the function
    function set label(lbl)
    {
        this.setLabel(lbl);
        //return (this.label());
        null;
    } // End of the function
    function setLabel(label)
    {
        if (label == "")
        {
            labelPath.removeTextField();
            this.refresh();
            return;
        } // end if
        if (labelPath == undefined)
        {
            var _loc2 = this.createLabel("labelPath", 200, label);
            _loc2._width = _loc2.textWidth + 5;
            _loc2._height = _loc2.textHeight + 5;
            if (initializing)
            {
                _loc2.visible = false;
            } // end if
        }
        else
        {
            delete labelPath.__text;
            labelPath.text = label;
            this.refresh();
        } // end else if
    } // End of the function
    function getLabel(Void)
    {
        return (labelPath.__text != undefined ? (labelPath.__text) : (labelPath.text));
    } // End of the function
    function get label()
    {
        return (this.getLabel());
    } // End of the function
    function _getIcon(Void)
    {
        return (_iconLinkageName);
    } // End of the function
    function get icon()
    {
        if (initializing)
        {
            return (initIcon);
        } // end if
        return (_iconLinkageName);
    } // End of the function
    function _setIcon(linkage)
    {
        if (initializing)
        {
            if (linkage == "")
            {
                return;
            } // end if
            initIcon = linkage;
        }
        else
        {
            if (linkage == "")
            {
                this.removeIcons();
                return;
            } // end if
            super.changeIcon(0, linkage);
            super.changeIcon(1, linkage);
            super.changeIcon(3, linkage);
            super.changeIcon(4, linkage);
            super.changeIcon(5, linkage);
            _iconLinkageName = linkage;
            this.refresh();
        } // end else if
    } // End of the function
    function set icon(linkage)
    {
        this._setIcon(linkage);
        //return (this.icon());
        null;
    } // End of the function
    function setHitArea(w, h)
    {
        if (hitArea_mc == undefined)
        {
            this.createEmptyObject("hitArea_mc", 100);
        } // end if
        var _loc2 = hitArea_mc;
        _loc2.clear();
        _loc2.beginFill(16711680);
        _loc2.drawRect(0, 0, w, h);
        _loc2.endFill();
        _loc2.setVisible(false);
    } // End of the function
    static var symbolName = "Button";
    static var symbolOwner = mx.controls.Button;
    var className = "Button";
    static var version = "2.0.2.126";
    var btnOffset = 0;
    var _color = "buttonColor";
    var __label = "default value";
    var __labelPlacement = "right";
    var falseUpSkin = "ButtonSkin";
    var falseDownSkin = "ButtonSkin";
    var falseOverSkin = "ButtonSkin";
    var falseDisabledSkin = "ButtonSkin";
    var trueUpSkin = "ButtonSkin";
    var trueDownSkin = "ButtonSkin";
    var trueOverSkin = "ButtonSkin";
    var trueDisabledSkin = "ButtonSkin";
    var falseUpIcon = "";
    var falseDownIcon = "";
    var falseOverIcon = "";
    var falseDisabledIcon = "";
    var trueUpIcon = "";
    var trueDownIcon = "";
    var trueOverIcon = "";
    var trueDisabledIcon = "";
    var clipParameters = {labelPlacement: 1, icon: 1, toggle: 1, selected: 1, label: 1};
    static var mergedClipParameters = mx.core.UIObject.mergeClipParameters(mx.controls.Button.prototype.clipParameters, mx.controls.SimpleButton.prototype.clipParameters);
    var centerContent = true;
    var borderW = 1;
} // End of Class
