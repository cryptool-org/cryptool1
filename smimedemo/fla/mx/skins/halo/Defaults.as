class mx.skins.halo.Defaults
{
    var beginGradientFill, beginFill, moveTo, lineTo, curveTo, endFill;
    function Defaults()
    {
    } // End of the function
    static function setThemeDefaults()
    {
        var _loc2 = _global.style;
        _loc2.themeColor = 8453965;
        _loc2.disabledColor = 8684164;
        _loc2.modalTransparency = 0;
        _loc2.filled = true;
        _loc2.stroked = true;
        _loc2.strokeWidth = 1;
        _loc2.strokeColor = 0;
        _loc2.fillColor = 16777215;
        _loc2.repeatInterval = 35;
        _loc2.repeatDelay = 500;
        _loc2.fontFamily = "_sans";
        _loc2.fontSize = 12;
        _loc2.selectionColor = 13500353;
        _loc2.rollOverColor = 14942166;
        _loc2.useRollOver = true;
        _loc2.backgroundDisabledColor = 14540253;
        _loc2.selectionDisabledColor = 14540253;
        _loc2.selectionDuration = 200;
        _loc2.openDuration = 250;
        _loc2.borderStyle = "inset";
        _loc2.color = 734012;
        _loc2.textSelectedColor = 24371;
        _loc2.textRollOverColor = 2831164;
        _loc2.textDisabledColor = 16777215;
        _loc2.vGridLines = true;
        _loc2.hGridLines = false;
        _loc2.vGridLineColor = 6710886;
        _loc2.hGridLineColor = 6710886;
        _loc2.headerColor = 15395562;
        _loc2.indentation = 17;
        _loc2.folderOpenIcon = "TreeFolderOpen";
        _loc2.folderClosedIcon = "TreeFolderClosed";
        _loc2.defaultLeafIcon = "TreeNodeIcon";
        _loc2.disclosureOpenIcon = "TreeDisclosureOpen";
        _loc2.disclosureClosedIcon = "TreeDisclosureClosed";
        _loc2.popupDuration = 150;
        _loc2.todayColor = 6710886;
        _loc2 = _global.styles.ScrollSelectList = new mx.styles.CSSStyleDeclaration();
        _loc2.backgroundColor = 16777215;
        _loc2.borderColor = 13290186;
        _loc2.borderStyle = "inset";
        _loc2 = _global.styles.ComboBox = new mx.styles.CSSStyleDeclaration();
        _loc2.borderStyle = "inset";
        _loc2 = _global.styles.NumericStepper = new mx.styles.CSSStyleDeclaration();
        _loc2.textAlign = "center";
        _loc2 = _global.styles.RectBorder = new mx.styles.CSSStyleDeclaration();
        _loc2.borderColor = 14015965;
        _loc2.buttonColor = 7305079;
        _loc2.shadowColor = 15658734;
        _loc2.highlightColor = 12897484;
        _loc2.shadowCapColor = 14015965;
        _loc2.borderCapColor = 9542041;
        var _loc4 = new Object();
        _loc4.borderColor = 16711680;
        _loc4.buttonColor = 16711680;
        _loc4.shadowColor = 16711680;
        _loc4.highlightColor = 16711680;
        _loc4.shadowCapColor = 16711680;
        _loc4.borderCapColor = 16711680;
        mx.core.UIComponent.prototype.origBorderStyles = _loc4;
        var _loc3;
        _loc3 = _global.styles.TextInput = new mx.styles.CSSStyleDeclaration();
        _loc3.backgroundColor = 16777215;
        _loc3.borderStyle = "inset";
        _global.styles.TextArea = _global.styles.TextInput;
        _loc3 = _global.styles.Window = new mx.styles.CSSStyleDeclaration();
        _loc3.borderStyle = "default";
        _loc3 = _global.styles.windowStyles = new mx.styles.CSSStyleDeclaration();
        _loc3.fontWeight = "bold";
        _loc3 = _global.styles.dataGridStyles = new mx.styles.CSSStyleDeclaration();
        _loc3.fontWeight = "bold";
        _loc3 = _global.styles.Alert = new mx.styles.CSSStyleDeclaration();
        _loc3.borderStyle = "alert";
        _loc3 = _global.styles.ScrollView = new mx.styles.CSSStyleDeclaration();
        _loc3.borderStyle = "inset";
        _loc3 = _global.styles.View = new mx.styles.CSSStyleDeclaration();
        _loc3.borderStyle = "none";
        _loc3 = _global.styles.ProgressBar = new mx.styles.CSSStyleDeclaration();
        _loc3.color = 11187123;
        _loc3.fontWeight = "bold";
        _loc3 = _global.styles.AccordionHeader = new mx.styles.CSSStyleDeclaration();
        _loc3.fontWeight = "bold";
        _loc3.fontSize = "11";
        _loc3 = _global.styles.Accordion = new mx.styles.CSSStyleDeclaration();
        _loc3.borderStyle = "solid";
        _loc3.backgroundColor = 16777215;
        _loc3.borderColor = 9081738;
        _loc3.headerHeight = 22;
        _loc3.marginLeft = _loc3.marginRight = _loc3.marginTop = _loc3.marginBottom = -1;
        _loc3.verticalGap = -1;
        _loc3 = _global.styles.DateChooser = new mx.styles.CSSStyleDeclaration();
        _loc3.borderColor = 9542041;
        _loc3.headerColor = 16777215;
        _loc3 = _global.styles.CalendarLayout = new mx.styles.CSSStyleDeclaration();
        _loc3.fontSize = 10;
        _loc3.textAlign = "right";
        _loc3.color = 2831164;
        _loc3 = _global.styles.WeekDayStyle = new mx.styles.CSSStyleDeclaration();
        _loc3.fontWeight = "bold";
        _loc3.fontSize = 11;
        _loc3.textAlign = "center";
        _loc3.color = 2831164;
        _loc3 = _global.styles.TodayStyle = new mx.styles.CSSStyleDeclaration();
        _loc3.color = 16777215;
        _loc3 = _global.styles.HeaderDateText = new mx.styles.CSSStyleDeclaration();
        _loc3.fontSize = 12;
        _loc3.fontWeight = "bold";
        _loc3.textAlign = "center";
    } // End of the function
    function drawRoundRect(x, y, w, h, r, c, alpha, rot, gradient, ratios)
    {
        if (typeof(r) == "object")
        {
            var _loc18 = r.br;
            var _loc16 = r.bl;
            var _loc15 = r.tl;
            var _loc10 = r.tr;
        }
        else
        {
            _loc10 = r;
            _loc15 = r;
            _loc16 = r;
            _loc18 = r;
        } // end else if
        if (typeof(c) == "object")
        {
            if (typeof(alpha) != "object")
            {
                var _loc9 = [alpha, alpha];
            }
            else
            {
                _loc9 = alpha;
            } // end else if
            if (ratios == undefined)
            {
                ratios = [0, 255];
            } // end if
            var _loc14 = h * 7.000000E-001;
            if (typeof(rot) != "object")
            {
                var _loc11 = {matrixType: "box", x: -_loc14, y: _loc14, w: w * 2, h: h * 4, r: rot * 1.745329E-002};
            }
            else
            {
                _loc11 = rot;
            } // end else if
            if (gradient == "radial")
            {
                this.beginGradientFill("radial", c, _loc9, ratios, _loc11);
            }
            else
            {
                this.beginGradientFill("linear", c, _loc9, ratios, _loc11);
            } // end else if
        }
        else if (c != undefined)
        {
            this.beginFill(c, alpha);
        } // end else if
        r = _loc18;
        var _loc13 = r - r * 7.071068E-001;
        var _loc12 = r - r * 4.142136E-001;
        this.moveTo(x + w, y + h - r);
        this.lineTo(x + w, y + h - r);
        this.curveTo(x + w, y + h - _loc12, x + w - _loc13, y + h - _loc13);
        this.curveTo(x + w - _loc12, y + h, x + w - r, y + h);
        r = _loc16;
        _loc13 = r - r * 7.071068E-001;
        _loc12 = r - r * 4.142136E-001;
        this.lineTo(x + r, y + h);
        this.curveTo(x + _loc12, y + h, x + _loc13, y + h - _loc13);
        this.curveTo(x, y + h - _loc12, x, y + h - r);
        r = _loc15;
        _loc13 = r - r * 7.071068E-001;
        _loc12 = r - r * 4.142136E-001;
        this.lineTo(x, y + r);
        this.curveTo(x, y + _loc12, x + _loc13, y + _loc13);
        this.curveTo(x + _loc12, y, x + r, y);
        r = _loc10;
        _loc13 = r - r * 7.071068E-001;
        _loc12 = r - r * 4.142136E-001;
        this.lineTo(x + w - r, y);
        this.curveTo(x + w - _loc12, y, x + w - _loc13, y + _loc13);
        this.curveTo(x + w, y + _loc12, x + w, y + r);
        this.lineTo(x + w, y + h - r);
        if (c != undefined)
        {
            this.endFill();
        } // end if
    } // End of the function
    static function classConstruct()
    {
        mx.core.ext.UIObjectExtensions.Extensions();
        mx.skins.halo.Defaults.setThemeDefaults();
        mx.core.UIObject.prototype.drawRoundRect = mx.skins.halo.Defaults.prototype.drawRoundRect;
        return (true);
    } // End of the function
    static var classConstructed = mx.skins.halo.Defaults.classConstruct();
    static var CSSStyleDeclarationDependency = mx.styles.CSSStyleDeclaration;
    static var UIObjectExtensionsDependency = mx.core.ext.UIObjectExtensions;
    static var UIObjectDependency = mx.core.UIObject;
} // End of Class
