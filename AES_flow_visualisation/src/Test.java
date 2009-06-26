import java.awt.BorderLayout;
import java.awt.Frame;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

class CloseListener implements WindowListener {
    public CloseListener( ) {
    }
 
    public void windowOpened( WindowEvent e) {
    }
    public void windowClosing( WindowEvent e) {
        e.getWindow().dispose();
        System.exit(0);
    }
    public void windowActivated( WindowEvent e) {
    }
    public void windowDeactivated( WindowEvent e) {
    }
    public void windowIconified( WindowEvent e) {
    }
    public void windowDeiconified( WindowEvent e) {
    }
    public void windowClosed( WindowEvent e) {
    }
}


public class Test {
	public static String language = "EN";
	
    @SuppressWarnings("deprecation")
	public static void main( String arg[] ) {
    	if(arg.length == 1){
    		language = arg[0];
    	}
    	
    	Frame frame = new Frame( language.equalsIgnoreCase("DE") ? "AES-Flussvisualisierung" : "AES Flow Visualisation");
    	frame.setLayout( new BorderLayout() ); 
        frame.add( new MainView(), "Center" );  
        frame.setSize( 800, (int) (((float)800)*DrawScheme.HEIGHT/DrawScheme.WIDTH) );
        frame.addWindowListener( new CloseListener() );
        frame.show();
    }
};
