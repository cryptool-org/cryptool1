class mx.managers.DepthManager
{
    var _childCounter, createClassObject, createObject, _parent, swapDepths, _topmost, getDepth;
    function DepthManager()
    {
        MovieClip.prototype.createClassChildAtDepth = createClassChildAtDepth;
        MovieClip.prototype.createChildAtDepth = createChildAtDepth;
        MovieClip.prototype.setDepthTo = setDepthTo;
        MovieClip.prototype.setDepthAbove = setDepthAbove;
        MovieClip.prototype.setDepthBelow = setDepthBelow;
        MovieClip.prototype.findNextAvailableDepth = findNextAvailableDepth;
        MovieClip.prototype.shuffleDepths = shuffleDepths;
        MovieClip.prototype.getDepthByFlag = getDepthByFlag;
        MovieClip.prototype.buildDepthTable = buildDepthTable;
        _global.ASSetPropFlags(MovieClip.prototype, "createClassChildAtDepth", 1);
        _global.ASSetPropFlags(MovieClip.prototype, "createChildAtDepth", 1);
        _global.ASSetPropFlags(MovieClip.prototype, "setDepthTo", 1);
        _global.ASSetPropFlags(MovieClip.prototype, "setDepthAbove", 1);
        _global.ASSetPropFlags(MovieClip.prototype, "setDepthBelow", 1);
        _global.ASSetPropFlags(MovieClip.prototype, "findNextAvailableDepth", 1);
        _global.ASSetPropFlags(MovieClip.prototype, "shuffleDepths", 1);
        _global.ASSetPropFlags(MovieClip.prototype, "getDepthByFlag", 1);
        _global.ASSetPropFlags(MovieClip.prototype, "buildDepthTable", 1);
    } // End of the function
    static function sortFunction(a, b)
    {
        if (a.getDepth() > b.getDepth())
        {
            return (1);
        } // end if
        return (-1);
    } // End of the function
    static function test(depth)
    {
        if (depth == mx.managers.DepthManager.reservedDepth)
        {
            return (false);
        }
        else
        {
            return (true);
        } // end else if
    } // End of the function
    static function createClassObjectAtDepth(className, depthSpace, initObj)
    {
        var _loc1;
        switch (depthSpace)
        {
            case mx.managers.DepthManager.kCursor:
            {
                _loc1 = mx.managers.DepthManager.holder.createClassChildAtDepth(className, mx.managers.DepthManager.kTopmost, initObj);
                break;
            } 
            case mx.managers.DepthManager.kTooltip:
            {
                _loc1 = mx.managers.DepthManager.holder.createClassChildAtDepth(className, mx.managers.DepthManager.kTop, initObj);
                break;
            } 
            default:
            {
                break;
            } 
        } // End of switch
        return (_loc1);
    } // End of the function
    static function createObjectAtDepth(linkageName, depthSpace, initObj)
    {
        var _loc1;
        switch (depthSpace)
        {
            case mx.managers.DepthManager.kCursor:
            {
                _loc1 = mx.managers.DepthManager.holder.createChildAtDepth(linkageName, mx.managers.DepthManager.kTopmost, initObj);
                break;
            } 
            case mx.managers.DepthManager.kTooltip:
            {
                _loc1 = mx.managers.DepthManager.holder.createChildAtDepth(linkageName, mx.managers.DepthManager.kTop, initObj);
                break;
            } 
            default:
            {
                break;
            } 
        } // End of switch
        return (_loc1);
    } // End of the function
    function createClassChildAtDepth(className, depthFlag, initObj)
    {
        if (_childCounter == undefined)
        {
            _childCounter = 0;
        } // end if
        var _loc3 = this.buildDepthTable();
        var _loc2 = this.getDepthByFlag(depthFlag, _loc3);
        var _loc6 = "down";
        if (depthFlag == mx.managers.DepthManager.kBottom)
        {
            _loc6 = "up";
        } // end if
        var _loc5;
        if (_loc3[_loc2] != undefined)
        {
            _loc5 = _loc2;
            _loc2 = this.findNextAvailableDepth(_loc2, _loc3, _loc6);
        } // end if
        var _loc4 = this.createClassObject(className, "depthChild" + _childCounter++, _loc2, initObj);
        if (_loc5 != undefined)
        {
            _loc3[_loc2] = _loc4;
            this.shuffleDepths(_loc4, _loc5, _loc3, _loc6);
        } // end if
        if (depthFlag == mx.managers.DepthManager.kTopmost)
        {
            _loc4._topmost = true;
        } // end if
        return (_loc4);
    } // End of the function
    function createChildAtDepth(linkageName, depthFlag, initObj)
    {
        if (_childCounter == undefined)
        {
            _childCounter = 0;
        } // end if
        var _loc3 = this.buildDepthTable();
        var _loc2 = this.getDepthByFlag(depthFlag, _loc3);
        var _loc6 = "down";
        if (depthFlag == mx.managers.DepthManager.kBottom)
        {
            _loc6 = "up";
        } // end if
        var _loc5;
        if (_loc3[_loc2] != undefined)
        {
            _loc5 = _loc2;
            _loc2 = this.findNextAvailableDepth(_loc2, _loc3, _loc6);
        } // end if
        var _loc4 = this.createObject(linkageName, "depthChild" + _childCounter++, _loc2, initObj);
        if (_loc5 != undefined)
        {
            _loc3[_loc2] = _loc4;
            this.shuffleDepths(_loc4, _loc5, _loc3, _loc6);
        } // end if
        if (depthFlag == mx.managers.DepthManager.kTopmost)
        {
            _loc4._topmost = true;
        } // end if
        return (_loc4);
    } // End of the function
    function setDepthTo(depthFlag)
    {
        var _loc2 = _parent.buildDepthTable();
        var _loc3 = _parent.getDepthByFlag(depthFlag, _loc2);
        if (_loc2[_loc3] != undefined)
        {
            this.shuffleDepths(this, _loc3, _loc2, undefined);
        }
        else
        {
            this.swapDepths(_loc3);
        } // end else if
        if (depthFlag == mx.managers.DepthManager.kTopmost)
        {
            _topmost = true;
        }
        else
        {
            delete this._topmost;
        } // end else if
    } // End of the function
    function setDepthAbove(targetInstance)
    {
        if (targetInstance._parent != _parent)
        {
            return;
        } // end if
        var _loc2 = targetInstance.getDepth() + 1;
        var _loc3 = _parent.buildDepthTable();
        if (_loc3[_loc2] != undefined && this.getDepth() < _loc2)
        {
            _loc2 = _loc2 - 1;
        } // end if
        if (_loc2 > mx.managers.DepthManager.highestDepth)
        {
            _loc2 = mx.managers.DepthManager.highestDepth;
        } // end if
        if (_loc2 == mx.managers.DepthManager.highestDepth)
        {
            _parent.shuffleDepths(this, _loc2, _loc3, "down");
        }
        else if (_loc3[_loc2] != undefined)
        {
            _parent.shuffleDepths(this, _loc2, _loc3, undefined);
        }
        else
        {
            this.swapDepths(_loc2);
        } // end else if
    } // End of the function
    function setDepthBelow(targetInstance)
    {
        if (targetInstance._parent != _parent)
        {
            return;
        } // end if
        var _loc6 = targetInstance.getDepth() - 1;
        var _loc3 = _parent.buildDepthTable();
        if (_loc3[_loc6] != undefined && this.getDepth() > _loc6)
        {
            _loc6 = _loc6 + 1;
        } // end if
        var _loc4 = mx.managers.DepthManager.lowestDepth + mx.managers.DepthManager.numberOfAuthortimeLayers;
        var _loc5;
        for (var _loc5 in _loc3)
        {
            var _loc2 = _loc3[_loc5];
            if (_loc2._parent != undefined)
            {
                _loc4 = Math.min(_loc4, _loc2.getDepth());
            } // end if
        } // end of for...in
        if (_loc6 < _loc4)
        {
            _loc6 = _loc4;
        } // end if
        if (_loc6 == _loc4)
        {
            _parent.shuffleDepths(this, _loc6, _loc3, "up");
        }
        else if (_loc3[_loc6] != undefined)
        {
            _parent.shuffleDepths(this, _loc6, _loc3, undefined);
        }
        else
        {
            this.swapDepths(_loc6);
        } // end else if
    } // End of the function
    function findNextAvailableDepth(targetDepth, depthTable, direction)
    {
        var _loc5 = mx.managers.DepthManager.lowestDepth + mx.managers.DepthManager.numberOfAuthortimeLayers;
        if (targetDepth < _loc5)
        {
            targetDepth = _loc5;
        } // end if
        if (depthTable[targetDepth] == undefined)
        {
            return (targetDepth);
        } // end if
        var _loc2 = targetDepth;
        var _loc1 = targetDepth;
        if (direction == "down")
        {
            while (depthTable[_loc1] != undefined)
            {
                --_loc1;
            } // end while
            return (_loc1);
        } // end if
        while (depthTable[_loc2] != undefined)
        {
            ++_loc2;
        } // end while
        return (_loc2);
    } // End of the function
    function shuffleDepths(subject, targetDepth, depthTable, direction)
    {
        var _loc9 = mx.managers.DepthManager.lowestDepth + mx.managers.DepthManager.numberOfAuthortimeLayers;
        var _loc8 = _loc9;
        var _loc5;
        for (var _loc5 in depthTable)
        {
            var _loc7 = depthTable[_loc5];
            if (_loc7._parent != undefined)
            {
                _loc9 = Math.min(_loc9, _loc7.getDepth());
            } // end if
        } // end of for...in
        if (direction == undefined)
        {
            if (subject.getDepth() > targetDepth)
            {
                direction = "up";
            }
            else
            {
                direction = "down";
            } // end if
        } // end else if
        var _loc1 = new Array();
        for (var _loc5 in depthTable)
        {
            _loc7 = depthTable[_loc5];
            if (_loc7._parent != undefined)
            {
                _loc1.push(_loc7);
            } // end if
        } // end of for...in
        _loc1.sort(mx.managers.DepthManager.sortFunction);
        if (direction == "up")
        {
            var _loc3;
            var _loc11;
            while (_loc1.length > 0)
            {
                _loc3 = _loc1.pop();
                if (_loc3 == subject)
                {
                    break;
                } // end if
            } // end while
            while (_loc1.length > 0)
            {
                _loc11 = subject.getDepth();
                _loc3 = _loc1.pop();
                var _loc4 = _loc3.getDepth();
                if (_loc11 > _loc4 + 1)
                {
                    if (_loc4 >= 0)
                    {
                        subject.swapDepths(_loc4 + 1);
                    }
                    else if (_loc11 > _loc8 && _loc4 < _loc8)
                    {
                        subject.swapDepths(_loc8);
                    } // end if
                } // end else if
                subject.swapDepths(_loc3);
                if (_loc4 == targetDepth)
                {
                    break;
                } // end if
            } // end while
        }
        else if (direction == "down")
        {
            _loc3 = undefined;
            while (_loc1.length > 0)
            {
                _loc3 = _loc1.shift();
                if (_loc3 == subject)
                {
                    break;
                } // end if
            } // end while
            while (_loc1.length > 0)
            {
                _loc11 = _loc3.getDepth();
                _loc3 = _loc1.shift();
                _loc4 = _loc3.getDepth();
                if (_loc11 < _loc4 - 1 && _loc4 > 0)
                {
                    subject.swapDepths(_loc4 - 1);
                } // end if
                subject.swapDepths(_loc3);
                if (_loc4 == targetDepth)
                {
                    break;
                } // end if
            } // end while
        } // end else if
    } // End of the function
    function getDepthByFlag(depthFlag, depthTable)
    {
        var _loc2 = 0;
        if (depthFlag == mx.managers.DepthManager.kTop || depthFlag == mx.managers.DepthManager.kNotopmost)
        {
            var _loc5 = 0;
            var _loc7 = false;
            var _loc8;
            for (var _loc8 in depthTable)
            {
                var _loc9 = depthTable[_loc8];
                var _loc3 = typeof(_loc9);
                if (_loc3 == "movieclip" || _loc3 == "object" && _loc9.__getTextFormat != undefined)
                {
                    if (_loc9.getDepth() <= mx.managers.DepthManager.highestDepth)
                    {
                        if (!_loc9._topmost)
                        {
                            _loc2 = Math.max(_loc2, _loc9.getDepth());
                            continue;
                        } // end if
                        if (!_loc7)
                        {
                            _loc5 = _loc9.getDepth();
                            _loc7 = true;
                            continue;
                        } // end if
                        _loc5 = Math.min(_loc5, _loc9.getDepth());
                    } // end if
                } // end if
            } // end of for...in
            _loc2 = _loc2 + 20;
            if (_loc7)
            {
                if (_loc2 >= _loc5)
                {
                    _loc2 = _loc5 - 1;
                } // end if
            } // end if
        }
        else if (depthFlag == mx.managers.DepthManager.kBottom)
        {
            for (var _loc8 in depthTable)
            {
                _loc9 = depthTable[_loc8];
                _loc3 = typeof(_loc9);
                if (_loc3 == "movieclip" || _loc3 == "object" && _loc9.__getTextFormat != undefined)
                {
                    if (_loc9.getDepth() <= mx.managers.DepthManager.highestDepth)
                    {
                        _loc2 = Math.min(_loc2, _loc9.getDepth());
                    } // end if
                } // end if
            } // end of for...in
            _loc2 = _loc2 - 20;
        }
        else if (depthFlag == mx.managers.DepthManager.kTopmost)
        {
            for (var _loc8 in depthTable)
            {
                _loc9 = depthTable[_loc8];
                _loc3 = typeof(_loc9);
                if (_loc3 == "movieclip" || _loc3 == "object" && _loc9.__getTextFormat != undefined)
                {
                    if (_loc9.getDepth() <= mx.managers.DepthManager.highestDepth)
                    {
                        _loc2 = Math.max(_loc2, _loc9.getDepth());
                    } // end if
                } // end if
            } // end of for...in
            _loc2 = _loc2 + 100;
        } // end else if
        if (_loc2 >= mx.managers.DepthManager.highestDepth)
        {
            _loc2 = mx.managers.DepthManager.highestDepth;
        } // end if
        var _loc6 = mx.managers.DepthManager.lowestDepth + mx.managers.DepthManager.numberOfAuthortimeLayers;
        for (var _loc9 in depthTable)
        {
            var _loc4 = depthTable[_loc9];
            if (_loc4._parent != undefined)
            {
                _loc6 = Math.min(_loc6, _loc4.getDepth());
            } // end if
        } // end of for...in
        if (_loc2 <= _loc6)
        {
            _loc2 = _loc6;
        } // end if
        return (_loc2);
    } // End of the function
    function buildDepthTable(Void)
    {
        var _loc5 = new Array();
        var _loc4;
        for (var _loc4 in this)
        {
            var _loc2 = this[_loc4];
            var _loc3 = typeof(_loc2);
            if (_loc3 == "movieclip" || _loc3 == "object" && _loc2.__getTextFormat != undefined)
            {
                if (_loc2._parent == this)
                {
                    _loc5[_loc2.getDepth()] = _loc2;
                } // end if
            } // end if
        } // end of for...in
        return (_loc5);
    } // End of the function
    static var reservedDepth = 1048575;
    static var highestDepth = 1048574;
    static var lowestDepth = -16383;
    static var numberOfAuthortimeLayers = 383;
    static var kCursor = 101;
    static var kTooltip = 102;
    static var kTop = 201;
    static var kBottom = 202;
    static var kTopmost = 203;
    static var kNotopmost = 204;
    static var holder = _root.createEmptyMovieClip("reserved", mx.managers.DepthManager.reservedDepth);
    static var __depthManager = new mx.managers.DepthManager();
} // End of Class
