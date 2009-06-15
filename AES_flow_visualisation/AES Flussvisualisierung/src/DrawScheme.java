import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;


public class DrawScheme 
{
    public DrawScheme() {
    }


    private void fillPolygon( Graphics g, double x[], double y[], int count, boolean border )
    {
        int i;
        int tx[] = new int[count];
        int ty[] = new int[count];
        for( i=0; i<count; i++ ) {
            tx[i] = (int) transX( x[i] );
            ty[i] = (int) transY( y[i] );
        }
        g.fillPolygon( tx, ty, count );
        if( border ) {
            g.setColor( Color.black );
            g.drawPolygon( tx, ty, count );
        }
    }

    final static int beforeKeyHeight = 10;
    
    final static int inputBoxWidth = 10;
    final static int inputBoxHeight = 10;
    final static int inputBoxSpace = 5;
    final static int inputBoxDelta = inputBoxWidth + inputBoxSpace;

    final static int inputSpace = 60;
    final static int inputDelta = 4*inputBoxDelta + inputSpace;


    final static int lineToSBoxLength = 10;
    final static int sboxHeight = 10;
    
    final static int lineAfterSBoxHeight = 5;
    final static int lineAfterSBoxDelta = 20;
    final static int shiftDiagonalHeight = 20;
    final static int lineAfterShiftHeight = 40;

    final static int linewidth = 3;
    

    // mix column
    final static int aroundMixBox = 5;
    final static int mixBoxHeight = 10;
    final static int mixBoxWidth = 10;
    final static int mixDiagonalDelta = 2*aroundMixBox + mixBoxHeight + 5;
    final static int diagonalLength = 5+4*mixDiagonalDelta;
    final static int lineMixHeight = 5;
    final static int circleSize = 4;

    final static int keyHeight = 5;
    final static int keyWidth = 8;

    final static int afterKeyHeight = 10;

    
    private void drawVLine( Graphics g, double x, double y1, double y2 ) {
        int tx = (int) (transX(x-linewidth/2.0));
        int ty1 = (int) transY(y1);
        int ty2 = (int) transY(y2);
        g.fillRect( tx, ty1, transX(x+linewidth/2.0)-tx+1, ty2-ty1+1 );
        g.setColor( Color.black );
        g.drawLine( tx, ty1, tx, ty2 );
        g.drawLine( transX(x+linewidth/2.0), ty1, transX(x+linewidth/2.0), ty2 );
    }

    private void drawLine( Graphics g, double x1, double y1, double x2, double y2 ) {
        double alpha = Math.atan((y2-y1)/(x2-x1));
        double d = linewidth/Math.sin(alpha);
        int ty1a = (int) transY((double) (y1+ (d-linewidth)*(y2-y1)/(x2-x1)));
        int ty2a = (int) transY((double) (y2- (d-linewidth)*(y2-y1)/(x2-x1)));

        double y1a = (y1+ (d-linewidth)*(y2-y1)/(x2-x1));
        double y2a = (y2- (d-linewidth)*(y2-y1)/(x2-x1));
        
        int tx1 = (int) transX(x1-(double)linewidth/2);
        int tx2 = (int) transX(x2-(double)linewidth/2);
        int ty1 = transY(y1);
        int ty2 = transY(y2);
        if( x1<x2 ) {
            double xp[] = new double[6];
            double yp[] = new double[6];
            xp[0] = x1-linewidth/2.0; yp[0] = y1;
            xp[1] = x1+ linewidth/2.0; yp[1] = y1;
            xp[2] = x2+ linewidth/2.0; yp[2] = y2a;
            xp[3] = x2+ linewidth/2.0; yp[3] = y2;
            xp[4] = x2-linewidth/2.0; yp[4] = y2;
            xp[5] = xp[0]; yp[5] = y1a;
            fillPolygon( g, xp, yp, 6, false );
            g.setColor( Color.black );
            
            g.drawLine( tx1, ty1a, tx2, ty2 );
            g.drawLine( transX(x1+linewidth/2.0), ty1, transX(x2+linewidth/2.0), ty2a );
            g.drawLine( tx1, ty1, tx1, ty1a );
            g.drawLine( transX(x2+linewidth/2.0), ty2a, transX(x2+linewidth/2.0), ty2 );
        } else {
            int xp[] = new int[6];
            int yp[] = new int[6];
            xp[0] = tx1; yp[0] = ty1;
            xp[1] = tx1+ (int) (linewidth*scaleX); yp[1] = ty1;
            xp[2] = tx1+ (int) (linewidth*scaleX); yp[2] = ty1a;
            xp[3] = tx2+ (int) (linewidth*scaleX); yp[3] = ty2;
            xp[4] = tx2; yp[4] = ty2;
            xp[5] = tx2; yp[5] = ty2a;
            g.fillPolygon( xp, yp, 6 );

            g.setColor( Color.black );
            g.drawLine( tx1, ty1, tx2, ty2a );
            g.drawLine( tx1+(int) (linewidth*scaleX), ty1a, tx2+(int) (linewidth*scaleX), ty2 );
            g.drawLine( tx1+(int) (linewidth*scaleX), ty1, tx1+(int) (linewidth*scaleX), ty1a );
            g.drawLine( tx2, ty2a, tx2, ty2 );
        }
    }

    private void drawMixXOR( Graphics g, double x, double y ) {
        g.setColor( Color.white );
        int s = (int) scaleX*circleSize;
        if( scaleY>scaleX )
            s = (int) scaleY*circleSize;
        g.fillOval( transX(x)-s/2, transY(y)-s/2, s, s );
        g.setColor( Color.black );
        g.drawOval( transX(x)-s/2, transY(y)-s/2, s,s );
    }
    

    private boolean showValues = true;

    public void setShowValues( boolean b ) {
        showValues = b;
    }

    static Color valueToColor( int x ) 
    {
        return new Color( (x % 8)*32+1, ((x/8) % 8)*32, ((x/64) % 3) *64  );
    }
    

    private void setColor( Graphics g, int x ) 
    {
        if( !showValues )
            g.setColor( Color.white );
        else
            g.setColor( valueToColor(x) );
    }

    static int colorToValue( Color c ) 
    {
        System.out.println( c );
        if( c.equals(Color.white) || c.equals(Color.black) )
            return -1;
        return c.getRed()/32 + (c.getGreen()/32)*8 + (c.getGreen()/64)*64;
    }

    static String intToHex( int i ) 
    {
        String s = Integer.toHexString( i ).toUpperCase();
        if( s.length()<2 )
            return "0" + s;
        return s;
    }
    
    
    public void draw( Graphics g, State state, Dimension size, boolean first, boolean last ) {
        scaleX = ((double) size.width)/WIDTH;
        scaleY = ((double) size.height)/HEIGHT;

        int i,j;
        int y=0;
        
        if( first ) 
            y = keyHeight+ inputBoxHeight + lineToSBoxLength;
        double fx[] = new double[10];
        double fy[] = new double[10];
        double startX, startY;
        String s;


        g.setFont( new Font( "SansSerif", Font.PLAIN, (int) (6*scaleY) ) );
        FontMetrics fm = g.getFontMetrics();

        for( i=0; i<4; i++ )
            for( j=0; j<4; j++ ) {
                if( first ) {
                    // draw input
                    setColor( g, state.startValues[i*4+j] );
                    g.fillRect( transX(j*inputBoxDelta+inputDelta*i), transY(0), (int) (inputBoxWidth*scaleX), (int) (inputBoxHeight*scaleY) );
                    drawVLine( g, j*inputBoxDelta+inputDelta*i + (double) inputBoxWidth/2, inputBoxHeight, inputBoxHeight + lineToSBoxLength +keyHeight );
                    g.drawRect( transX(j*inputBoxDelta+inputDelta*i), transY(0), (int) (inputBoxWidth*scaleX), (int) (inputBoxHeight*scaleY) );
                    // round keys
                    fx[0] = j*inputBoxDelta+inputDelta*i + (double) inputBoxWidth/2 - linewidth/2.0 - keyWidth;
                    fy[0] = y - keyHeight;
                    fx[1] = j*inputBoxDelta+inputDelta*i + (double) inputBoxWidth/2 + linewidth/2.0 - keyWidth;
                    fy[1] = fy[0];
                    fx[2] = fx[1];
                    fy[2] = y - linewidth/2.0;
                    fx[3] = fx[0] + keyWidth + linewidth/2.0;
                    fy[3] = fy[2];
                    fx[4] = fx[3];
                    fy[4] = fy[3] + linewidth;
                    fx[5] = fx[0];
                    fy[5] = fy[4];
                    setColor( g, state.roundKeyValues[4*i+j] );
                    fillPolygon( g, fx, fy, 6, true);
                    s = intToHex( state.roundKeyValues[4*i+j] );
                    g.drawString( s, transX(fx[0]+linewidth/2.0)-fm.stringWidth(s)/2, transY(fy[0])-2);
                    // after round keys
                    fx[0] = j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 - linewidth/2.0;
                    fy[0] = y;
                    fx[1] = j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + linewidth/2.0;
                    fy[1] = fy[0];
                    fx[2] = fx[1];
                    fy[2] = y + afterKeyHeight;
                    fx[3] = fx[0];
                    fy[3] = fy[2];
                    setColor( g, state.afterFirstKeyValues[4*i+j] );
                    drawVLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, y, fy[2] + afterKeyHeight);
                    drawMixXOR( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, y );
                } else {
//                    setColor( g, state.startValues[i*4+j] );
                    g.setColor( valueToColor(state.startValues[i*4+j]) );
                    drawVLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, 0, afterKeyHeight );
                }
                
                
                setColor( g, state.afterFirstKeyValues[i*4+j] );
                g.fillRect( transX(j*inputBoxDelta+inputDelta*i), transY( y + afterKeyHeight ), (int) (inputBoxWidth*scaleX), (int) (sboxHeight*scaleY/2.0)+1 );
                setColor( g, state.afterSBoxValues[i*4+j] );
                g.fillRect( transX(j*inputBoxDelta+inputDelta*i), transY( y + afterKeyHeight )+(int) (sboxHeight*scaleY/2.0)+1, (int) (inputBoxWidth*scaleX), (int) (sboxHeight*scaleY/2.0) );
                g.setColor( Color.black );
                g.drawRect( transX(j*inputBoxDelta+inputDelta*i), transY( y + afterKeyHeight ), (int) (inputBoxWidth*scaleX), (int) (sboxHeight*scaleY) );
            }
        y +=  afterKeyHeight + sboxHeight;
        

        for( i=0; i<4; i++ ) {
            setColor( g, state.afterSBoxValues[i*4] );
            if( !last )
                drawVLine( g, inputDelta*i + inputBoxWidth/2.0, 
                           y,
                           y+lineAfterSBoxHeight+3*lineAfterSBoxDelta + shiftDiagonalHeight + lineAfterShiftHeight );
            else
                drawVLine( g, inputDelta*i + inputBoxWidth/2.0, 
                           y,
                           y+lineAfterSBoxHeight+lineAfterSBoxDelta + shiftDiagonalHeight + lineAfterShiftHeight );
            for( j=1; j<4; j++ ) {
                setColor( g, state.afterSBoxValues[i*4+j] );
                drawVLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, 
                           y, y+lineAfterSBoxHeight+(3-j)*lineAfterSBoxDelta );
                setColor( g, state.afterSBoxValues[((i+j)%4)*4+j] );
                if( !last )
                    drawVLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, 
                               y+lineAfterSBoxHeight+(3-j)*lineAfterSBoxDelta + shiftDiagonalHeight,
                               y+lineAfterSBoxHeight+(3-j)*lineAfterSBoxDelta + shiftDiagonalHeight + lineAfterShiftHeight );
                else
                    drawVLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, 
                               y+lineAfterSBoxHeight+(3-j)*lineAfterSBoxDelta + shiftDiagonalHeight,
                               y+lineAfterSBoxHeight+lineAfterSBoxDelta + shiftDiagonalHeight + lineAfterShiftHeight );
            }
        }
        
        setColor( g, state.afterSBoxValues[0*4+1] );
        drawLine( g, 1*inputBoxDelta+inputDelta*0 + inputBoxWidth/2.0, 
                  y+lineAfterSBoxHeight+2*lineAfterSBoxDelta,
                  1*inputBoxDelta+inputDelta*3 + inputBoxWidth/2.0,
                  y+lineAfterSBoxHeight+2*lineAfterSBoxDelta+shiftDiagonalHeight );
        setColor( g, state.afterSBoxValues[1*4+1] );
        drawLine( g, 1*inputBoxDelta+inputDelta*1 + inputBoxWidth/2.0, 
                  y+lineAfterSBoxHeight+2*lineAfterSBoxDelta,
                  1*inputBoxDelta+inputDelta*0 + inputBoxWidth/2.0,
                  y+lineAfterSBoxHeight+2*lineAfterSBoxDelta+shiftDiagonalHeight );
        setColor( g, state.afterSBoxValues[2*4+1] );
        drawLine( g, 1*inputBoxDelta+inputDelta*2 + inputBoxWidth/2.0, 
                  y+lineAfterSBoxHeight+2*lineAfterSBoxDelta,
                  1*inputBoxDelta+inputDelta*1 + inputBoxWidth/2.0,
                  y+lineAfterSBoxHeight+2*lineAfterSBoxDelta+shiftDiagonalHeight );
        setColor( g, state.afterSBoxValues[3*4+1] );
        drawLine( g, 1*inputBoxDelta+inputDelta*3 + inputBoxWidth/2.0, 
                  y+lineAfterSBoxHeight+2*lineAfterSBoxDelta,
                  1*inputBoxDelta+inputDelta*2 + inputBoxWidth/2.0,
                  y+lineAfterSBoxHeight+2*lineAfterSBoxDelta+shiftDiagonalHeight );
        // third diagonal line of each block
        for( i=0; i<4; i++ ) {
            j=2;            
            setColor( g, state.afterSBoxValues[i*4+2] );
            drawVLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, 
                       y, y+lineAfterSBoxHeight+(3-j)*lineAfterSBoxDelta );
            setColor( g, state.afterSBoxValues[((i+2)%4)*4+j] );
            drawVLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, 
                       y+lineAfterSBoxHeight+(3-j)*lineAfterSBoxDelta + shiftDiagonalHeight,
                       y+lineAfterSBoxHeight+(3-j)*lineAfterSBoxDelta + shiftDiagonalHeight + lineAfterShiftHeight );
        }
        setColor( g, state.afterSBoxValues[0*4+2] );
        drawLine( g, 2*inputBoxDelta+inputDelta*0 + inputBoxWidth/2.0, 
                  y+lineAfterSBoxHeight+lineAfterSBoxDelta,
                  2*inputBoxDelta+inputDelta*2 + inputBoxWidth/2.0,
                  y+lineAfterSBoxHeight+lineAfterSBoxDelta+shiftDiagonalHeight );
        setColor( g, state.afterSBoxValues[1*4+2] );
        drawLine( g, 2*inputBoxDelta+inputDelta*1 + inputBoxWidth/2.0, 
                  y+lineAfterSBoxHeight+lineAfterSBoxDelta,
                  2*inputBoxDelta+inputDelta*3 + inputBoxWidth/2.0,
                  y+lineAfterSBoxHeight+lineAfterSBoxDelta+shiftDiagonalHeight );
        setColor( g, state.afterSBoxValues[2*4+2] );
        drawLine( g, 2*inputBoxDelta+inputDelta*2 + inputBoxWidth/2.0, 
                  y+lineAfterSBoxHeight+lineAfterSBoxDelta,
                  2*inputBoxDelta+inputDelta*0 + inputBoxWidth/2.0,
                  y+lineAfterSBoxHeight+lineAfterSBoxDelta+shiftDiagonalHeight );
        setColor( g, state.afterSBoxValues[3*4+2] );
        drawLine( g, 2*inputBoxDelta+inputDelta*3 + inputBoxWidth/2.0, 
                      y+lineAfterSBoxHeight+lineAfterSBoxDelta,
                      2*inputBoxDelta+inputDelta*1 + inputBoxWidth/2.0,
                      y+lineAfterSBoxHeight+lineAfterSBoxDelta+shiftDiagonalHeight );
        // last diagonal line of each block
        for( i=0; i<3; i++ ) {
            setColor( g, state.afterSBoxValues[i*4+3] );
            drawLine( g, 3*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, 
                      y+lineAfterSBoxHeight,
                      3*inputBoxDelta+inputDelta*(i+1) + inputBoxWidth/2.0,
                      y+lineAfterSBoxHeight+ shiftDiagonalHeight );
        }
        setColor( g, state.afterSBoxValues[3*4+3] );
        drawLine( g, 3*inputBoxDelta+inputDelta*3 + inputBoxWidth/2.0, 
                  y+lineAfterSBoxHeight,
                  3*inputBoxDelta + inputBoxWidth/2.0,
                  y+lineAfterSBoxHeight+ shiftDiagonalHeight );
        
        
        y += lineAfterSBoxHeight;

        y += shiftDiagonalHeight;
        y += lineAfterShiftHeight;


        if( !last ) {
            // Mix Column

            double l = diagonalLength/Math.sqrt(2);
            double t = Math.sqrt( shiftDiagonalHeight*shiftDiagonalHeight + inputBoxDelta*inputBoxDelta );
            double alpha = Math.atan( (double) shiftDiagonalHeight / inputBoxDelta );
            double l2 = (t*Math.cos(3.14/4 - alpha))/Math.sqrt(2);
            double l3 = mixDiagonalDelta/Math.sqrt(2);
            int m;
        
            for( i=0; i<4; i++ ) 
                for( j=0; j<4; j++ ) {
                    for( m=0; m<4; m++ ) {
                        setColor( g, state.afterShiftValues[i*4+j] );
                    
                        startX = 3*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + l - (3-j)*l2 - m*l3;
                        startY = y +l  +(3-j)*l2 - m*l3;
                        setColor( g, state.afterShiftValues[i*4+j] );
                        fx[0] = startX - linewidth/2.0/Math.sqrt(2);
                        fy[0] = startY - linewidth/2.0/Math.sqrt(2);
                        fx[1] = startX + linewidth/2.0/Math.sqrt(2);
                        fy[1] = startY + linewidth/2.0/Math.sqrt(2);
                        fx[2] = startX - l2/2.0 + linewidth*Math.sqrt(2)/2.0;
                        fy[2] = startY + l2/2.0;
                        fx[3] = startX - l2/2.0 + (aroundMixBox/Math.sqrt(2)) + linewidth/2.0/Math.sqrt(2);
                        fy[3] = startY + l2/2.0 + (aroundMixBox/Math.sqrt(2)) - linewidth/2.0/Math.sqrt(2);

                        fx[4] = fx[3] + (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                        fy[4] = fy[3] - (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                        
                        fx[5] = fx[4] + mixBoxHeight/Math.sqrt(2)/2.0;
                        fy[5] = fy[4] + mixBoxHeight/Math.sqrt(2)/2.0;

                        fx[9] = startX - l2/2.0 - linewidth*Math.sqrt(2)/2.0;
                        fy[9] = startY + l2/2.0;
                        fx[8] = startX - l2/2.0 + (aroundMixBox/Math.sqrt(2)) - linewidth/2.0/Math.sqrt(2);
                        fy[8] = startY + l2/2.0 + (aroundMixBox/Math.sqrt(2)) + linewidth/2.0/Math.sqrt(2);
                        fx[7] = fx[8] - (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                        fy[7] = fy[8] + (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                    
                        fx[6] = fx[7] + mixBoxHeight/Math.sqrt(2)/2.0;
                        fy[6] = fy[7] + mixBoxHeight/Math.sqrt(2)/2.0;
                        fillPolygon( g, fx, fy, 10, true);
                    }
                    setColor( g, state.afterShiftValues[i*4+j] );
                    drawLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, 
                              y + (3-j)*shiftDiagonalHeight,
                              3*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + l - (3-j)*l2,
                              y  +l  +(3-j)*l2 );
                
                }

            
            for( i=0; i<4; i++ ) {
                for( j=0; j<3; j++ ) 
                    for( m=0; m<4; m++ ) { 
                        // from output of Mix-Box to xor
                        startX = 3*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + l - (3-j)*l2 - m*l3 - l2/2.0;
                        startY = y +l  +(3-j)*l2 - m*l3 + l2/2.0;
                        
                        setColor( g, state.inMixColumn[24*i+12+3-m-4*j] );
                        fx[6] = startX + (mixBoxHeight+aroundMixBox)/Math.sqrt(2) - linewidth/2.0/Math.sqrt(2);
                        fy[6] = startY + (mixBoxHeight+aroundMixBox)/Math.sqrt(2) + linewidth/2.0/Math.sqrt(2);
                        fx[3] = startX + (mixBoxHeight+aroundMixBox)/Math.sqrt(2) + linewidth/2.0/Math.sqrt(2);
                        fy[3] = startY + (mixBoxHeight+aroundMixBox)/Math.sqrt(2) - linewidth/2.0/Math.sqrt(2);
                        fx[4] = fx[3] + aroundMixBox/Math.sqrt(2);
                        fy[4] = fy[3] + aroundMixBox/Math.sqrt(2);
                        fx[5] = fx[6] + aroundMixBox/Math.sqrt(2);
                        fy[5] = fy[6] + aroundMixBox/Math.sqrt(2);
                        fx[2] = fx[3] + (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                        fy[2] = fy[3] - (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                        fx[1] = fx[2] - mixBoxHeight/Math.sqrt(2)/2.0;
                        fy[1] = fy[2] - mixBoxHeight/Math.sqrt(2)/2.0;
                        fx[7] = fx[6] - (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                        fy[7] = fy[6] + (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                        fx[0] = fx[7] - mixBoxHeight/Math.sqrt(2)/2.0;
                        fy[0] = fy[7] - mixBoxHeight/Math.sqrt(2)/2.0;
                        fillPolygon( g, fx, fy, 8, true);
                        s = Integer.toString(State.mixColumnMatrix[12-4*j+3-m]);
                        g.drawString(s, (int) transX((fx[0]+fx[1])/2.0)-fm.stringWidth(s)/2, (int) transY((fy[0]+fy[1])/2.0)+4);
                    }
                for( m=0; m<4; m++ ) {
                    // output of third column of mix
                    startX = 3*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + l - m*l3 - l2/2;
                    startY = y +l  - m*l3 + l2/2.0;
                    
                    setColor( g, state.inMixColumn[24*i+(3-m)] );
                    fx[8] = startX + (mixBoxHeight+aroundMixBox)/Math.sqrt(2) - linewidth/2.0/Math.sqrt(2);
                    fy[8] = startY + (mixBoxHeight+aroundMixBox)/Math.sqrt(2) + linewidth/2.0/Math.sqrt(2);
                    fx[3] = startX + (mixBoxHeight+aroundMixBox)/Math.sqrt(2) + linewidth/2.0/Math.sqrt(2);
                    fy[3] = startY + (mixBoxHeight+aroundMixBox)/Math.sqrt(2) - linewidth/2.0/Math.sqrt(2);
                    fx[4] = fx[3] + (aroundMixBox+linewidth/2.0)/Math.sqrt(2);
                    fy[4] = fy[3] + (aroundMixBox+linewidth/2.0)/Math.sqrt(2);
                    fx[5] = fx[4] - l2 - (aroundMixBox-linewidth)/Math.sqrt(2);
                    fy[5] = fy[4] + l2 + (aroundMixBox-linewidth)/Math.sqrt(2);
                    fx[7] = fx[8] + (aroundMixBox-linewidth/2.0)/Math.sqrt(2);
                    fy[7] = fy[8] + (aroundMixBox-linewidth/2.0)/Math.sqrt(2);
                    fx[6] = fx[7] - l2;
                    fy[6] = fy[7] + l2;
                    fx[2] = fx[3] + (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                    fy[2] = fy[3] - (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                    fx[1] = fx[2] - mixBoxHeight/Math.sqrt(2)/2.0;
                    fy[1] = fy[2] - mixBoxHeight/Math.sqrt(2)/2.0;
                    fx[9] = fx[8] - (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                    fy[9] = fy[8] + (mixBoxWidth-linewidth)/2.0/Math.sqrt(2);
                    fx[0] = fx[9] - mixBoxHeight/Math.sqrt(2)/2.0;
                    fy[0] = fy[9] - mixBoxHeight/Math.sqrt(2)/2.0;
                    fillPolygon( g, fx, fy, 10, true);
                    s = Integer.toString(State.mixColumnMatrix[3-m]);
                    g.drawString(s, (int) transX((fx[0]+fx[1])/2.0)-fm.stringWidth(s)/2, (int) transY((fy[0]+fy[1])/2.0)+4);
                }
            }
            
            for( i=0; i<4; i++ )
                for( j=1; j<3; j++ )
                    for( m=0; m<4; m++ ) {
                        // lines between xor
                        startX = 3*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + l - (3-j)*l2 - (3-m)*l3 - l2/2.0 + (mixBoxHeight+2*aroundMixBox)/Math.sqrt(2);
                        startY = y +l  +(3-j)*l2 - (3-m)*l3 + l2/2.0 + (mixBoxHeight+2*aroundMixBox)/Math.sqrt(2);
                        setColor( g, state.inMixColumn[24*i+24-4*j+m] );
                        fx[0] = startX - linewidth/2.0/Math.sqrt(2);
                        fy[0] = startY - linewidth/2.0/Math.sqrt(2);
                        fx[1] = startX + linewidth/2.0/Math.sqrt(2);
                        fy[1] = startY + linewidth/2.0/Math.sqrt(2);
                        fx[2] = fx[1] - l2;
                        fy[2] = fy[1] + l2;
                        fx[3] = fx[0] - l2;
                        fy[3] = fy[0] + l2;
                        fillPolygon( g, fx, fy, 4, true);
                    }
        
            y += l  + (3-0)*l2 + l2/2.0 + (mixBoxHeight+2*aroundMixBox)/Math.sqrt(2);

            // mix column to round keys
            for( i=0; i<4; i++ )
                for( j=0; j<4; j++ ) {
                    startX = 3*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + l - (3-0)*l2 - (3-j)*l3 - l2/2 + (mixBoxHeight+2*aroundMixBox)/Math.sqrt(2);
                    startY = y - (3-j)*l3 ;
                    fx[0] = startX - linewidth/2.0/Math.sqrt(2);
                    fy[0] = startY - linewidth/2.0/Math.sqrt(2);
                    fx[1] = startX + linewidth/2.0/Math.sqrt(2);
                    fy[1] = startY + linewidth/2.0/Math.sqrt(2);
                    fx[2] = j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + linewidth/2.0;
                    fy[2] = fy[1] + fx[1]-fx[2];
                    fx[5] = j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 - linewidth/2.0;
                    fy[5] = fy[0] + fx[0]-fx[5];

                    fx[3] = fx[2];
                    fy[3] = y + lineMixHeight + (l - 3*l2 - l2/2.0 + (mixBoxHeight+2*aroundMixBox)/Math.sqrt(2) -  linewidth/2.0/Math.sqrt(2) + linewidth/2.0);
  
                    fx[4] = fx[5];
                    fy[4] = fy[3];

                    setColor( g, state.afterMixValues[4*i+j] );
                    fillPolygon( g, fx, fy, 6, true);
                }

            // xor circles
            for( i=0; i<4; i++ )
                for( j=0; j<3; j++ )
                    for( m=0; m<4; m++ ) {
                        startX = 3*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + l - (3-j)*l2 - (3-m)*l3 - l2/2.0 + (mixBoxHeight+2*aroundMixBox)/Math.sqrt(2);
                        startY = y -j*l2 - (3-m)*l3 ;
                        drawMixXOR( g, startX, startY );
                    }
        
            y += lineMixHeight + l - 3*l2 - l2/2.0 + (mixBoxHeight+2*aroundMixBox)/Math.sqrt(2) -  linewidth/2/Math.sqrt(2);
        } else {
            y += lineAfterSBoxDelta;
        }
        
        // round keys
        for( i=0; i<4; i++ ) 
            for( j=0; j<4; j++ ) {
                fx[0] = j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 - linewidth/2.0 - keyWidth;
                fy[0] = y - keyHeight;
                fx[1] = j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0 + linewidth/2.0 - keyWidth;
                fy[1] = fy[0];
                fx[2] = fx[1];
                fy[2] = y - linewidth/2.0;
                fx[3] = fx[0] + keyWidth + linewidth/2.0;
                fy[3] = fy[2];
                fx[4] = fx[3];
                fy[4] = fy[3] + linewidth;
                fx[5] = fx[0];
                fy[5] = fy[4];
                setColor( g, state.secondKeyValues[4*i+j] );
                fillPolygon( g, fx, fy, 6, true);
                s = intToHex( state.secondKeyValues[4*i+j] );
                g.drawString( s, transX(fx[0]+linewidth/2.0)-fm.stringWidth(s)/2, transY(fy[0])-2);
                
            }
        
        // after round keys
        for( i=0; i<4; i++ ) 
            for( j=0; j<4; j++ ) {
                setColor( g, state.resultValues[4*i+j] );
                if( !last )
                    drawVLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, y, (double) size.height/scaleY );
                else
                    drawVLine( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, y, y + afterKeyHeight );
                
                drawMixXOR( g, j*inputBoxDelta+inputDelta*i + inputBoxWidth/2.0, y );
            }
        y += afterKeyHeight;
        if( last ) {
            for( i=0; i<4; i++) 
                for( j=0; j<4; j++) {
                    setColor( g, state.resultValues[i*4+j] );
                    g.fillRect( transX(j*inputBoxDelta+inputDelta*i), transY(y), (int) (inputBoxWidth*scaleX), (int) (inputBoxHeight*scaleY) );
                    g.setColor( Color.black );
                    g.drawRect( transX(j*inputBoxDelta+inputDelta*i), transY(y), (int) (inputBoxWidth*scaleX), (int) (inputBoxHeight*scaleY) );
                }
        }
    }

    int transX( double x ) {
        return (int) (5*scaleY) + keyWidth + (int) Math.round(x*scaleX);
    }
    int transY( double y ) {
        return 0 + 0*keyWidth + (int) Math.round(y*scaleY);
    }

    int transX( int x ) {
        return (int) (5*scaleY) + keyWidth + (int) Math.round(x*scaleX);
    }
    int transY( int y ) {
        return 0 + 0*keyWidth + (int) Math.round(y*scaleY);
    }
    
    double scaleX, scaleY;
    public final static int WIDTH = inputDelta*4 + inputBoxSpace+ 20;
    public final static int HEIGHT = 300;

}

