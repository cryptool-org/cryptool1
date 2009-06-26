import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Checkbox;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

public class MainView extends Container implements ActionListener, FinishListener, ClickListener, ItemListener, FocusListener
{
    private static final long serialVersionUID = 7641258745625210687L;
	public MainView() 
    {
        setLayout( new BorderLayout() );
        Panel p = new Panel();
        p.setLayout(new GridLayout(3,1));

        Panel pi = new Panel();
        pi.setLayout( new FlowLayout() );

        Label label = new Label( Test.language.equalsIgnoreCase("DE") ? "Daten:" : "Data:", Label.RIGHT);
        label.setPreferredSize(new Dimension(65, 25));
        pi.add( label );
        input = new TextField[16];
        int i;
        
        int[] v = new int[16];
        
        for( i=0; i<16; i++ ) {
            v[i] = (int) (Math.random()*256);
            String s = Integer.toHexString( v[i] ).toUpperCase();
            if( s.length()<2 )
                s = "0" + s;

            input[i] = new TextField( s, 2);
            pi.add( input[i] );
        }

        Panel keyPanel = new Panel();
        keyPanel.setLayout( new FlowLayout() );
        label = new Label( Test.language.equalsIgnoreCase("DE") ? "Schlüssel:" : "Key:", Label.RIGHT);
        label.setPreferredSize(new Dimension(65, 25));
        keyPanel.add( label );

        key = new TextField[16];
        int[] k = new int[16];
        
        for( i=0; i<16; i++ ) {
            k[i] = (int) (Math.random()*256);
            String s = Integer.toHexString( k[i] ).toUpperCase();
            if( s.length()<2 )
                s = "0" + s;

            key[i] = new TextField( s, 2);
            key[i].addFocusListener( this );
            keyPanel.add( key[i] );
        }

        Panel pb = new Panel();
        pb.setLayout( new FlowLayout() );
        roundLabel = new Label( Test.language.equalsIgnoreCase("DE") ? "1. Runde" : "Round 1");
        pb.add( roundLabel );
        startButton = new Button( Test.language.equalsIgnoreCase("DE") ? "Berechnung" : "Calculation" );
        pb.add( startButton );
//        nextButton = new Button( "neue Runde" );
//        nextButton.setEnabled( false );
//        pb.add( nextButton );
        resetButton = new Button( Test.language.equalsIgnoreCase("DE") ? "Reset" : "Reset" );
        pb.add( resetButton );
        clearInputButton = new Button( Test.language.equalsIgnoreCase("DE") ? "0-Eingabe" : "0-Input" );
        pb.add( clearInputButton );
        randomInputButton = new Button( Test.language.equalsIgnoreCase("DE") ? "Zufällige Eingabe" : "Random Input" );
        pb.add( randomInputButton );
        zeroKeyButton = new Button( Test.language.equalsIgnoreCase("DE") ? "0-Schlüssel" : "0-Key" );
        pb.add( zeroKeyButton );
        randomKeyButton = new Button( Test.language.equalsIgnoreCase("DE") ? "Zufälliger Schlüssel" : "Random Key");
        pb.add( randomKeyButton );
        pauseBox = new Checkbox( Test.language.equalsIgnoreCase("DE") ? "Pausen" : "Stops", null, true );
        pb.add( pauseBox );
        p.add( pi );
        p.add( keyPanel );
        p.add( pb );
        add( p, BorderLayout.NORTH );
        rijn = new RijndaelView( this, this );
        rijn.setStartValues(v,k);
        add( rijn, BorderLayout.CENTER );

        startButton.addActionListener( this );
//        nextButton.addActionListener( this );
        clearInputButton.addActionListener( this );
        randomInputButton.addActionListener( this );
        zeroKeyButton.addActionListener( this );
        randomKeyButton.addActionListener( this );
        resetButton.addActionListener( this );
        pauseBox.addItemListener( this );
    }

    private int[] getKey() 
    {
        int k[] = new int[16];
        int i=0;
        
        try {
            for( i=0; i<16; i++ ) {
                k[i] = Integer.valueOf(key[i].getText(),16).intValue();
                if( k[i]<0 && k[i]>255 )
                    throw new NumberFormatException();
            }
        } catch( NumberFormatException ex ) {
            key[i].requestFocus();
            auto = false;
            return null;
        }
        return k;
    }
    
    private int[] getInput() 
    {
        int v[] = new int[16];
        int i=0;
        
        try {
            for( i=0; i<16; i++ ) {
                v[i] = Integer.valueOf(input[i].getText(),16).intValue();
                if( v[i]<0 && v[i]>255 )
                    throw new NumberFormatException();
            }
        } catch( NumberFormatException ex ) {
            if( i<16 ) {
                input[i].requestFocus();
                auto = false;
            }
            return null;
        }
        return v;
    }



    public void startAnim()
    {
        int i;
        
        int v[] = getInput();
        if( v==null )
            return;
        
        int k[] = null;
        if( rijn.getRound() == 0 ) {
            k = getKey();
            if( k==null )
                return;
            
            for( i=0; i<16; i++ )
                key[i].setEnabled( false );
        }

        running = true;
        startButton.setEnabled( false );
        rijn.setStartValues(v,k);
        rijn.startAnim();
    }

    public void itemStateChanged(ItemEvent e )  
    {
        if( e.getSource() == pauseBox ) {
            auto = !pauseBox.getState();
            if( auto && !running ) {
                if( startButton.isEnabled() )
                    startAnim();
                else {
                    running = true;
//                    nextButton.setEnabled( false );
                    startButton.setEnabled( false );
                    startButton.setLabel( Test.language.equalsIgnoreCase("DE") ? "Berechnung" : "Calculation" );
                    rijn.nextRound();
                }
            }
        }
    }

    public void reset() 
    {
        roundLabel.setText( Test.language.equalsIgnoreCase("DE") ? "1. Runde" : "Round 1");
        rijn.reset();
        auto = false;
        running = false;
//        nextButton.setEnabled( false );
        startButton.setLabel( Test.language.equalsIgnoreCase("DE") ? "Berechnung" : "Calculation" );
        startButton.setEnabled( true );
        pauseBox.setState( true );
        int i;
        for( i=0; i<16; i++ )
            key[i].setEnabled( true );

    }
    

    public void actionPerformed( ActionEvent e ) {
        if( !auto ) {
/*            if( e.getSource() == startButton ) {
                startAnim();
            }
            if( e.getSource() == nextButton ) {
                nextButton.setEnabled( false );
                running = true;
                rijn.nextRound();
                }*/
            if( e.getActionCommand().equals( Test.language.equalsIgnoreCase("DE") ? "Berechnung" : "Calculation" ) )
            {
                startAnim();
            }
            if( e.getActionCommand().equals( Test.language.equalsIgnoreCase("DE") ? "Neue Runde" : "New Round" ) )
            {
                startButton.setEnabled( false );
                running = true;
                rijn.nextRound();
            }
                
            if( e.getSource() == clearInputButton ) {
                int i;
                for( i=0; i<16; i++ )
                    input[i].setText( "00" );
            }
            if( e.getSource() == zeroKeyButton ) {
                reset();
                int i;
                for( i=0; i<16; i++ )
                    key[i].setText( "00" );
                updateDrawValues();
            }
            if( e.getSource() == resetButton ) {
                reset();
            }
        
            if( e.getSource() == randomInputButton ) {
                int i;
                for( i=0; i<16; i++ ) {
                    String s = Integer.toHexString( (int) (Math.random()*256) ).toUpperCase();
                    if( s.length()<2 )
                        s = "0" + s;
                    input[i].setText( s );
                }
            }
            if( e.getSource() == randomKeyButton ) {
                int i;
                for( i=0; i<16; i++ ) {
                    String s = Integer.toHexString( (int) (Math.random()*256) ).toUpperCase();
                    if( s.length()<2 )
                        s = "0" + s;
                    key[i].setText( s );
                }
                updateDrawValues();
            }
        }
        
    }

    public void focusGained(FocusEvent e) 
    {
    }

    public void focusLost(FocusEvent e) 
    {
        if( rijn.getRound()==0 && startButton.isEnabled()
            && startButton.getLabel().equals( Test.language.equalsIgnoreCase("DE") ? "Berechnung" : "Calculation" ) ) 
        {
            updateDrawValues();
        }
    }
    
    private void updateDrawValues() 
    {
        int v[] = getInput();
        if( v==null )
            return;
        
        int k[] = null;
        if( rijn.getRound() == 0 ) {
            k = getKey();
            if( k==null )
                return;
        }
        rijn.setStartValues(v,k);
    }
    

    public void animFinished() 
    {
//        nextButton.setEnabled( true );
        if( auto ) {
//            nextButton.setEnabled( false );
            rijn.nextRound();
        } else {
            startButton.setLabel( Test.language.equalsIgnoreCase("DE") ? "Neue Runde" : "New Round" );
            startButton.getParent().doLayout();
            
            startButton.setEnabled( true );
            running = false;
        }
        
    }
    
    public void scrollFinished()
    {
        int i;
        for( i=0; i<16; i++ ) {
            String s = Integer.toHexString( rijn.getStartValue(i) ).toUpperCase();
            if( s.length()<2 )
                s = "0" + s;
            input[i].setText( s );
        }
        
        if( rijn.getRound() == 0 ) {
            for( i=0; i<16; i++ )
                key[i].setEnabled( true );
        }

//        nextButton.setEnabled( false );
//        startButton.setEnabled( true );
        startButton.setLabel( Test.language.equalsIgnoreCase("DE") ? "Berechnung" : "Calculation" );
        startButton.setEnabled( true );
        roundLabel.setText( Test.language.equalsIgnoreCase("DE") ? Integer.toString(rijn.getRound()+1) + ". Runde" : "Round " + Integer.toString(rijn.getRound()+1));
        if( auto )
            startAnim();
        else
            running = false;
    }

    public void clicked( int value ) 
    {
        System.out.println( value );
    }
    

    private RijndaelView rijn;
    private Label roundLabel;
    private Button startButton, clearInputButton, 
        randomInputButton, zeroKeyButton, randomKeyButton, resetButton;
    private Checkbox pauseBox;
    private TextField input[];
    private TextField key[];
    private boolean auto = false, running = false;
}
