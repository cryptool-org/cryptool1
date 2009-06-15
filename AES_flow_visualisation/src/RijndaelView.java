import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Panel;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Date;


public class RijndaelView extends Panel implements Runnable, MouseListener
{
    private static final long serialVersionUID = -1353326338989995747L;
	public RijndaelView( FinishListener f, ClickListener c) 
    {
        finishListener = f;
        clickListener = c;
        draw = new DrawScheme();
        setBackground( Color.white );
        round = 0;
//        if( clickListener!=null )
//            addMouseListener( this );
        actRound = new State();
    }

    public void setStartValues( int[] v, int[] k ) 
    {
        actRound.setStartValues( v, k );
        offDimension = null;
        createOffscreen();
        repaint();
    }

    public void reset() 
    {
        round = 0;
        splitY=0;
        scroll=0;
        isScrolling = false;
        offDimension = null;
        createOffscreen();
        repaint();
    }

    public int getStartValue( int index ) 
    {
        return actRound.getStartValue( index );
    }
    
    public void clearKey() 
    {
        isScrolling = false;
        splitY = 0;
        scroll = 0;
        round = 0;
        actRound.clearKey();
        nextRound = null;
        offDimension = null;
        createOffscreen();
        repaint();
    }
    

    public int getResultValue( int index ) 
    {
        return actRound.getResultValue( index );
    }
    
    public boolean isDoubleBuffered( ) 
    {
        return true;
    }

    public void paint( Graphics g ) 
    {
        update( g );
    }
    
    public void update( Graphics g ) 
    {
        Dimension d = getSize();
        if( d.width>0 ) {
            if ( (offDimension == null)
                 || (d.width != offDimension.width)
                 || (d.height != offDimension.height) )
            {
                createOffscreen();
            }
            if( scroll>0 ) {
                g.drawImage( fullImage, 0,0,d.width-1, d.height-1-(int) (scroll*d.height),
                             0, (int) (scroll*d.height), d.width-1, d.height-1, this ); 
                g.drawImage( nextImage, 0,d.height-(int) (scroll*d.height)-1, d.width-1, d.height-1,
                             0, 0, d.width-1, (int) (scroll*d.height), this ); 
            } else {
                g.drawImage( fullImage, 0,0,d.width-1, (int) (splitY*d.height), 0, 0, d.width-1, (int) (splitY*d.height), this ); 
                g.drawImage( whiteImage, 0,(int) (splitY*d.height),d.width-1, d.height-1, 0, (int) (splitY*d.height), d.width-1, d.height-1, this ); 
            }
        }
    }

    public void run() {
        Dimension d = getSize();
        if ( (offDimension == null)
             || (d.width != offDimension.width)
             || (d.height != offDimension.height) )
        {
            createOffscreen();
        }
        
        Graphics g = getGraphics();
        
        long startTime = new Date().getTime();
        while( (!isScrolling && splitY< 1.0) || (isScrolling && scroll<1.0)  ) {
            long time = new Date().getTime() - startTime;
            if( isScrolling ) {
                scroll = (double) time/scrollSpeed;
                if( scroll>1.0)
                    scroll = 1.0;
                
                g.drawImage( fullImage, 0,0,d.width-1, d.height-1-(int) (scroll*d.height),
                             0, (int) (scroll*d.height), d.width-1, d.height-1, this ); 
                g.drawImage( nextImage, 0,d.height-(int) (scroll*d.height), d.width-1, d.height-1,
                             0, 0, d.width-1, (int) (scroll*d.height)-1, this ); 
            } else {
                int last_s = (int) (splitY * d.height);
                splitY = (double) time/animSpeed;
                if( splitY>1.0)
                    splitY = 1.0;
                int s = (int) (splitY * d.height);
                g.drawImage( fullImage, 0,last_s,d.width-1, 
                               s, 0, last_s,
                             d.width-1, s, this ); 
            }
            
            if( isScrolling )
                try {
                    Thread.sleep( 10 );
                } catch( InterruptedException e ) {
                    System.err.println( "interrupt" );
                }
      
        }
        animThread = null;
        if( isScrolling ) {
            actRound = nextRound;
            round = (round + 1) % noRounds;
            finishListener.scrollFinished();
        } else
            finishListener.animFinished();
    }
    

    public void startAnim() {
        isScrolling = false;
        splitY = 0;
        scroll = 0;
//        repaint();
        if( animThread == null ) {
            animThread = new Thread(this);
            animThread.start();
        }
    }

    public void nextRound() {
        if( round == noRounds-1 ) {
            nextRound = new State();
        } else
            nextRound = actRound.nextRound();

        offDimension = null;
        createOffscreen();
        startScroll();
    }

    public void startScroll() {
        scroll = 0;
        isScrolling = true;
        if( animThread == null ) {
            animThread = new Thread(this);
            animThread.start();
        }
    }

    private void createOffscreen() 
    {
        Dimension d = getSize();
        
        if ( d!=null && d.height>0 && d.width>0 
             &&( (offDimension == null) || (d.width != offDimension.width)
             || (d.height != offDimension.height)) )
        {
            offDimension = d;
            whiteImage = createImage(d.width, d.height);
            draw.setShowValues( false );
            draw.draw( whiteImage.getGraphics(), actRound, d, round==0, round==noRounds-1 );
            try {
                fullImage = createImage(d.width, d.height);
            } catch( Exception e ) {
                System.out.println( e );
                System.out.println( d );
                
            }
            
            draw.setShowValues( true );
            draw.draw( fullImage.getGraphics(), actRound, d, round==0, round==noRounds-1 );
            if( nextRound !=null ) {
                nextImage = createImage(d.width, d.height);
                draw.setShowValues( false );
                draw.draw( nextImage.getGraphics(), nextRound, d, round==noRounds-1, round==noRounds-2 );
            }
            
        }
    }

    public int getValue( Point p ) 
    {
/*        createOffscreen();
        int[] pixels = new int[1];
        System.out.println( secondImage.getSource() );
        
        PixelGrabber pg = new PixelGrabber(secondImage.getSource(), p.x, p.y, 1, 1, pixels, 0, 1);
        try {
            System.out.println("grab");
            pg.grabPixels();
            System.out.println("grab done "+ pixels[0] );
            
            return draw.colorToValue( new Color((pixels[0] >> 16)&  0xff,(pixels[0] >> 8) &  0xff, pixels[0] &  0xff) );
        } catch (InterruptedException e) {
            return -1;
            }*/
        return -1;
        
    }

    public void mouseClicked( MouseEvent e ) 
    {
        if( e.getSource()==this && clickListener!=null ) {
            int v = getValue( e.getPoint() );
            if( v>=0 )
                clickListener.clicked( v );
        }
    }
    
    public void mouseEntered( MouseEvent e ) 
    {
    }
 
    public void mouseExited( MouseEvent e ) 
    {
    }
    public void mousePressed( MouseEvent e ) 
    {
    }
    public void mouseReleased( MouseEvent e ) 
    {
    }

    public int getRound() 
    {
        return round;
    }

    DrawScheme draw;
    Dimension offDimension = null;
    Image whiteImage = null;
    Image fullImage = null;
    Image nextImage = null;
    double splitY=0, scroll=0;
    boolean isScrolling = false;
    
    Thread animThread = null;
    
    FinishListener finishListener;
    ClickListener clickListener;
    
    final static int animSpeed = 8000;
    final static int scrollSpeed = 3000;
    final static int noRounds = 10;

    State actRound=null, nextRound=null;
    int round;
};

