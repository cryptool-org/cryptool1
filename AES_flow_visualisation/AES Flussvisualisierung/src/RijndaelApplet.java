import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
 
public class RijndaelApplet extends Applet implements ActionListener {
	
	private static final long serialVersionUID = 6079662446157328361L;

	public void actionPerformed( ActionEvent e ) {
        Test.main( null );
    }
    
    public void init() {
        setLayout(new java.awt.GridLayout(1,0));
        Button startButton = new Button( "Start" );
        add( startButton );
        startButton.addActionListener( this );
        validate();
        Test.main( null );
    }
};
