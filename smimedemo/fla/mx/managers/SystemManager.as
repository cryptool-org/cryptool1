class mx.managers.SystemManager
{
    static var addEventListener, _xAddEventListener, __addEventListener, removeEventListener, _xRemoveEventListener, __removeEventListener, form, __screen, dispatchEvent, __get__screen;
    function SystemManager()
    {
    } // End of the function
    static function init(Void)
    {
        if (mx.managers.SystemManager._initialized == false)
        {
            _initialized = true;
            mx.events.EventDispatcher.initialize(mx.managers.SystemManager);
            Mouse.addListener(mx.managers.SystemManager);
            Stage.addListener(mx.managers.SystemManager);
            _xAddEventListener = mx.managers.SystemManager.addEventListener;
            addEventListener = mx.managers.SystemManager.__addEventListener;
            _xRemoveEventListener = mx.managers.SystemManager.removeEventListener;
            removeEventListener = mx.managers.SystemManager.__removeEventListener;
        } // end if
    } // End of the function
    static function addFocusManager(f)
    {
        form = f;
        f.focusManager.activate();
    } // End of the function
    static function removeFocusManager(f)
    {
    } // End of the function
    static function onMouseDown(Void)
    {
        var _loc1 = mx.managers.SystemManager.form;
        _loc1.focusManager._onMouseDown();
    } // End of the function
    static function onResize(Void)
    {
        var _loc7 = Stage.width;
        var _loc6 = Stage.height;
        var _loc9 = _global.origWidth;
        var _loc8 = _global.origHeight;
        var _loc3 = Stage.align;
        var _loc5 = (_loc9 - _loc7) / 2;
        var _loc4 = (_loc8 - _loc6) / 2;
        if (_loc3 == "T")
        {
            _loc4 = 0;
        }
        else if (_loc3 == "B")
        {
            _loc4 = _loc8 - _loc6;
        }
        else if (_loc3 == "L")
        {
            _loc5 = 0;
        }
        else if (_loc3 == "R")
        {
            _loc5 = _loc9 - _loc7;
        }
        else if (_loc3 == "LT")
        {
            _loc4 = 0;
            _loc5 = 0;
        }
        else if (_loc3 == "TR")
        {
            _loc4 = 0;
            _loc5 = _loc9 - _loc7;
        }
        else if (_loc3 == "LB")
        {
            _loc4 = _loc8 - _loc6;
            _loc5 = 0;
        }
        else if (_loc3 == "RB")
        {
            _loc4 = _loc8 - _loc6;
            _loc5 = _loc9 - _loc7;
        } // end else if
        if (mx.managers.SystemManager.__screen == undefined)
        {
            __screen = new Object();
        } // end if
        mx.managers.SystemManager.__screen.x = _loc5;
        mx.managers.SystemManager.__screen.y = _loc4;
        mx.managers.SystemManager.__screen.width = _loc7;
        mx.managers.SystemManager.__screen.height = _loc6;
        _root.focusManager.relocate();
        mx.managers.SystemManager.dispatchEvent({type: "resize"});
    } // End of the function
    static function get screen()
    {
        mx.managers.SystemManager.init();
        if (mx.managers.SystemManager.__screen == undefined)
        {
            mx.managers.SystemManager.onResize();
        } // end if
        return (mx.managers.SystemManager.__screen);
    } // End of the function
    static var _initialized = false;
    static var idleFrames = 0;
    static var isMouseDown = false;
    static var forms = new Array();
} // End of Class
