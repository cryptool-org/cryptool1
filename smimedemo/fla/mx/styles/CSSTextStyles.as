class mx.styles.CSSTextStyles
{
    var _tf;
    function CSSTextStyles()
    {
    } // End of the function
    static function addTextStyles(o, bColor)
    {
        o.addProperty("textAlign", function ()
        {
            return (_tf.align);
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.align = x;
        });
        o.addProperty("fontWeight", function ()
        {
            return (_tf.bold != undefined ? (_tf.bold ? ("bold") : ("none")) : (undefined));
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.bold = x == "bold";
        });
        if (bColor)
        {
            o.addProperty("color", function ()
            {
                return (_tf.color);
            }, function (x)
            {
                if (_tf == undefined)
                {
                    _tf = new TextFormat();
                } // end if
                _tf.color = x;
            });
        } // end if
        o.addProperty("fontFamily", function ()
        {
            return (_tf.font);
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.font = x;
        });
        o.addProperty("textIndent", function ()
        {
            return (_tf.indent);
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.indent = x;
        });
        o.addProperty("fontStyle", function ()
        {
            return (_tf.italic != undefined ? (_tf.italic ? ("italic") : ("none")) : (undefined));
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.italic = x == "italic";
        });
        o.addProperty("marginLeft", function ()
        {
            return (_tf.leftMargin);
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.leftMargin = x;
        });
        o.addProperty("marginRight", function ()
        {
            return (_tf.rightMargin);
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.rightMargin = x;
        });
        o.addProperty("fontSize", function ()
        {
            return (_tf.size);
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.size = x;
        });
        o.addProperty("textDecoration", function ()
        {
            return (_tf.underline != undefined ? (_tf.underline ? ("underline") : ("none")) : (undefined));
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.underline = x == "underline";
        });
        o.addProperty("embedFonts", function ()
        {
            return (_tf.embedFonts);
        }, function (x)
        {
            if (_tf == undefined)
            {
                _tf = new TextFormat();
            } // end if
            _tf.embedFonts = x;
        });
    } // End of the function
} // End of Class
