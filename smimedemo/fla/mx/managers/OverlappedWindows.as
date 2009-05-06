class mx.managers.OverlappedWindows
{
    function OverlappedWindows()
    {
    } // End of the function
    static function checkIdle(Void)
    {
        if (mx.managers.SystemManager.idleFrames > 10)
        {
            mx.managers.SystemManager.dispatchEvent({type: "idle"});
        }
        else
        {
            ++mx.managers.SystemManager.idleFrames;
        } // end else if
    } // End of the function
    static function __addEventListener(e, o, l)
    {
        if (e == "idle")
        {
            if (mx.managers.SystemManager.interval == undefined)
            {
                mx.managers.SystemManager.interval = setInterval(mx.managers.SystemManager.checkIdle, 100);
            } // end if
        } // end if
        mx.managers.SystemManager._xAddEventListener(e, o, l);
    } // End of the function
    static function __removeEventListener(e, o, l)
    {
        if (e == "idle")
        {
            if (mx.managers.SystemManager._xRemoveEventListener(e, o, l) == 0)
            {
                clearInterval(mx.managers.SystemManager.interval);
            } // end if
        }
        else
        {
            mx.managers.SystemManager._xRemoveEventListener(e, o, l);
        } // end else if
    } // End of the function
    static function onMouseDown(Void)
    {
        mx.managers.SystemManager.idleFrames = 0;
        mx.managers.SystemManager.isMouseDown = true;
        var _loc5 = _root;
        var _loc3;
        var _loc8 = _root._xmouse;
        var _loc7 = _root._ymouse;
        if (mx.managers.SystemManager.form.modalWindow == undefined)
        {
            if (mx.managers.SystemManager.forms.length > 1)
            {
                var _loc6 = mx.managers.SystemManager.forms.length;
                var _loc4;
                for (var _loc4 = 0; _loc4 < _loc6; ++_loc4)
                {
                    var _loc2 = mx.managers.SystemManager.forms[_loc4];
                    if (_loc2._visible)
                    {
                        if (_loc2.hitTest(_loc8, _loc7))
                        {
                            if (_loc3 == undefined)
                            {
                                _loc3 = _loc2.getDepth();
                                _loc5 = _loc2;
                                continue;
                            } // end if
                            if (_loc3 < _loc2.getDepth())
                            {
                                _loc3 = _loc2.getDepth();
                                _loc5 = _loc2;
                            } // end if
                        } // end if
                    } // end if
                } // end of for
                if (_loc5 != mx.managers.SystemManager.form)
                {
                    mx.managers.SystemManager.activate(_loc5);
                } // end if
            } // end if
        } // end if
        var _loc9 = mx.managers.SystemManager.form;
        _loc9.focusManager._onMouseDown();
    } // End of the function
    static function onMouseMove(Void)
    {
        mx.managers.SystemManager.idleFrames = 0;
    } // End of the function
    static function onMouseUp(Void)
    {
        mx.managers.SystemManager.isMouseDown = false;
        mx.managers.SystemManager.idleFrames = 0;
    } // End of the function
    static function activate(f)
    {
        if (mx.managers.SystemManager.form != undefined)
        {
            if (mx.managers.SystemManager.form != f && mx.managers.SystemManager.forms.length > 1)
            {
                var _loc1 = mx.managers.SystemManager.form;
                _loc1.focusManager.deactivate();
            } // end if
        } // end if
        mx.managers.SystemManager.form = f;
        f.focusManager.activate();
    } // End of the function
    static function deactivate(f)
    {
        if (mx.managers.SystemManager.form != undefined)
        {
            if (mx.managers.SystemManager.form == f && mx.managers.SystemManager.forms.length > 1)
            {
                var _loc5 = mx.managers.SystemManager.form;
                _loc5.focusManager.deactivate();
                var _loc3 = mx.managers.SystemManager.forms.length;
                var _loc1;
                var _loc2;
                for (var _loc1 = 0; _loc1 < _loc3; ++_loc1)
                {
                    if (mx.managers.SystemManager.forms[_loc1] == f)
                    {
                        for (var _loc1 = _loc1 + 1; _loc1 < _loc3; ++_loc1)
                        {
                            if (mx.managers.SystemManager.forms[_loc1]._visible == true)
                            {
                                _loc2 = mx.managers.SystemManager.forms[_loc1];
                            } // end if
                        } // end of for
                        mx.managers.SystemManager.form = _loc2;
                        break;
                        continue;
                    } // end if
                    if (mx.managers.SystemManager.forms[_loc1]._visible == true)
                    {
                        _loc2 = mx.managers.SystemManager.forms[_loc1];
                    } // end if
                } // end of for
                _loc5 = mx.managers.SystemManager.form;
                _loc5.focusManager.activate();
            } // end if
        } // end if
    } // End of the function
    static function addFocusManager(f)
    {
        mx.managers.SystemManager.forms.push(f);
        mx.managers.SystemManager.activate(f);
    } // End of the function
    static function removeFocusManager(f)
    {
        var _loc3 = mx.managers.SystemManager.forms.length;
        var _loc1;
        for (var _loc1 = 0; _loc1 < _loc3; ++_loc1)
        {
            if (mx.managers.SystemManager.forms[_loc1] == f)
            {
                if (mx.managers.SystemManager.form == f)
                {
                    mx.managers.SystemManager.deactivate(f);
                } // end if
                mx.managers.SystemManager.forms.splice(_loc1, 1);
                return;
            } // end if
        } // end of for
    } // End of the function
    static function enableOverlappedWindows()
    {
        if (!mx.managers.OverlappedWindows.initialized)
        {
            initialized = true;
            mx.managers.SystemManager.checkIdle = mx.managers.OverlappedWindows.checkIdle;
            mx.managers.SystemManager.__addEventListener = mx.managers.OverlappedWindows.__addEventListener;
            mx.managers.SystemManager.__removeEventListener = mx.managers.OverlappedWindows.__removeEventListener;
            mx.managers.SystemManager.onMouseDown = mx.managers.OverlappedWindows.onMouseDown;
            mx.managers.SystemManager.onMouseMove = mx.managers.OverlappedWindows.onMouseMove;
            mx.managers.SystemManager.onMouseUp = mx.managers.OverlappedWindows.onMouseUp;
            mx.managers.SystemManager.activate = mx.managers.OverlappedWindows.activate;
            mx.managers.SystemManager.deactivate = mx.managers.OverlappedWindows.deactivate;
            mx.managers.SystemManager.addFocusManager = mx.managers.OverlappedWindows.addFocusManager;
            mx.managers.SystemManager.removeFocusManager = mx.managers.OverlappedWindows.removeFocusManager;
        } // end if
    } // End of the function
    static var initialized = false;
    static var SystemManagerDependency = mx.managers.SystemManager;
} // End of Class
