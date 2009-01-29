package eccdemo;

import java.awt.*;
import java.awt.event.*;

public class ECCFrame extends Frame //implements KeyListener
{
 	
 	/*****  DEFINITIONEN   *****/
 	 
 	//0=deutsch, 1=englisch
    static protected int sprache=1;
    
    //0=Fr, 1=Fp
    static protected int raum=0;
    
 	//Startwerte der Kurvenparameter
	static protected double a;
    static protected double b;
    //Scrollrad-Schieber
    static protected int a_scroll;
    static protected int b_scroll;
    //nachkommastellen: 10=1, 100=2 etc.
    static protected int nks;
    
    
    protected int [] c={6,8,11,12,22,24,33,44,66,88}; 
    static protected int amin;	// Werte für Panel a
    static protected int amax;
    static protected int bmin;	// Werte für Panel b
    static protected int bmax;
   
    static protected int px;			// x-Pixelkoordinate Punkt P
	static protected int py;			// y-Pixelkoordinate Punkt P
	static protected double dpx;		// double-Wert von px
	static protected double dpy;		// double-Wert von py
	static protected boolean pset;// Wurde ein Punkt P gewählt?false=nein;
  
    static protected int qx;			// x-Pixelkoordinate Punkt Q
	static protected int qy;			// y-Pixelkoordinate Punkt Q
	static protected double dqx;		// double-Wert von qx
	static protected double dqy;		// double-Wert von qy
	static protected boolean qset; 	// Wurde ein Punkt Q gewählt?false=nein;
	
	static protected int rx;			// x-Pixelkoordinate Punkt R
	static protected int ry;			// y-Pixelkoordinate Punkt R
	static protected double drx;		// double-Wert von rx
	static protected double dry;		// double-Wert von ry
	static protected boolean rset; 	// Wurde ein Punkt R berechnet?false=nein;
	static protected boolean rNaN; 	// Ist R unendlich?false=nein;
    static protected int np;				// bei welchem vielfachen von P befindet sich das Programm? 
    
    static protected int ax;			// x-Pixelkoordinate AuswahlPunkt A
	static protected int ay;			// y-Pixelkoordinate AuswahlPunkt A
	static protected double dax;		// double-Wert von ax
	static protected double day;		// double-Wert von ay
	static protected boolean aset; 	// Wurde ein AuswahlPunkt gewählt, aber noch nicht mit
    										// Maus geklickt
    static protected int maxwert;    //standardwerte= maxwert=15, pixelPro=15
   
   	static protected int abstand;
    static protected int zeichenfenster; /// Pixel des Zeichenfensters
    static protected int pixelProZelle;
    
    static protected int canvasGroesse;//grösse +1, damit immer genau eine mitte existiert; immer quadratisch
    

    static protected int frameBreite;
    static protected int frameHoehe;
    
    static protected String LogText=""; // Leere LogDatei
    
    protected GrafikFp grafikFp;
    protected GrafikFr grafikFr;
    protected BedienungsPanelFp bPanelFp;
    protected BedienungsPanelFr bPanelFr;
    protected TextPanel tPanel;
    protected GridBagLayout gl;
    protected GridBagConstraints gc;
    protected Texte text;
    static protected ECCFrame eccframe;
    
    protected int[][] punkt;
    static protected int zaehlerpunkte=0;
    
    protected int [] p={3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};  

   static protected int pIndex=7;
   static protected int cIndex=1; 
    
    private void exitForm(java.awt.event.WindowEvent evt) {                          
        System.exit(0);
        }
        
    /** Konstruktor von ECCFrame */

    public ECCFrame(int sprache, int raum)
    {
        //	super ("Punktaddition auf Elliptischen Kurven");
        reset();
        
        //Nachkommsstellen
        this.nks=100;
        this.raum=raum;
        this.sprache=sprache;
        text=new Texte(sprache);
        
    	// Layout wird eingerichtet
        gl=new GridBagLayout();
        setLayout(gl);
        gc = new GridBagConstraints();
        gc.gridheight=gc.gridwidth=12;
        gc.fill=GridBagConstraints.NONE;
        
        //addKeyListener(this);
        
		//Fr
    	if(raum==0)
     		makeFr(this, false);
     		
     	if(raum==1)
     		makeFp(this, false);
		
		// Window beenden
        addWindowListener(new WindowAdapter() 
        {
            public void windowClosing(WindowEvent event) 
            {
            exitForm(event);
            }
        });

    }
    
    // Start
    //public static void main (String args [])
    public static void main (String args [])
    {
    	eccframe=new ECCFrame(sprache,raum);
    	
    	if (sprache==0)
    		eccframe.setTitle("ECC-Demo, v1.0: Punktaddition auf Elliptischen Kurven über den reellen Zahlenraum R");
    	else
    		eccframe.setTitle("ECC Demonstration, v1.0: Point addition on elliptic curves over the real number space R");
    	eccframe.setLocation(50,50);
    }

	protected void reset()
	{
		 px=0;			// x-Pixelkoordinate Punkt P
		 py=0;			// y-Pixelkoordinate Punkt P
		 dpx=0;		// double-Wert von px
		 dpy=0;		// double-Wert von py
		 pset=false;// Wurde ein Punkt P gewählt?false=nein;
	  
	     qx=0;			// x-Pixelkoordinate Punkt Q
		 qy=0;			// y-Pixelkoordinate Punkt Q
		 dqx=0;		// double-Wert von qx
		 dqy=0;		// double-Wert von qy
		 qset=false; 	// Wurde ein Punkt Q gewählt?false=nein;
		
		 rx=0;			// x-Pixelkoordinate Punkt R
		 ry=0;			// y-Pixelkoordinate Punkt R
		 drx=0;		// double-Wert von rx
		 dry=0;		// double-Wert von ry
		 rset=false; 	// Wurde ein Punkt R berechnet?false=nein;
		 rNaN=false; 	// Ist R unendlich?false=nein;
	     np=1;				// bei welchem vielfachen von P befindet sich das Programm? 
	    
	     ax=0;			// x-Pixelkoordinate AuswahlPunkt A
		 ay=0;			// y-Pixelkoordinate AuswahlPunkt A
		 dax=0;		// double-Wert von ax
		 day=0;		// double-Wert von ay
		 aset=false; 	// Wurde ein AuswahlPunkt gewählt, aber noch nicht mit
	    										// Maus geklickt
	   
	   	 abstand=25;
	     zeichenfenster=529; /// Pixel des Zeichenfensters
	}
	
	protected void makeFr(ECCFrame eccframe, boolean checkbox)
	{
			eccframe.setTitle(text.frameTitleFr);
     		a=-10;
     		b=15;
     		a_scroll=(int)a*eccframe.nks;
     		b_scroll=(int)b*eccframe.nks;
     		cIndex=3; 
     		amin=-50;
     		amax=50;
     		bmin=-50;
     		bmax=50;
	        maxwert=c[cIndex];    //standardwerte= maxwert=15, pixelPro=15
	        pixelProZelle=264/eccframe.maxwert;//anzahl sollte gerade sein, damit das raster genau auf den achsen liegt
	        canvasGroesse=(11*2*24)+1;//grösse +1, damit immer genau eine mitte existiert; immer quadratisch
			frameBreite=900;//canvasGroesse+300;
	        frameHoehe=650;//canvasGroesse+100;
	        // Grafikbereich wird erzeugt
	        grafikFr= new GrafikFr(canvasGroesse,eccframe);
	        // Bedieungspanel wird erzeugt 
	        bPanelFr = new BedienungsPanelFr(eccframe); 
	        
	        gc.gridx=0;
	        gc.gridy=0;
	        gc.gridheight=5;
	        gc.gridwidth=5;
	        gc.weightx=0.5;	 
	               
        	gl.setConstraints(grafikFr,gc);
        	if(checkbox)
				remove(grafikFp);
        	add(grafikFr);
        	
        	
        	// Textpanel wird erzeugt
        	if(checkbox)
				remove(tPanel);	
		    tPanel = new TextPanel(eccframe);            
		    
		    gc.gridx=6;
		    gc.gridy=0;
		    gc.gridheight=5;//10
		    gc.gridwidth=5;
		    gl.setConstraints(tPanel,gc);
		    
		    add(tPanel);
        
			gc.gridx=0;
	        gc.gridy=5;
	        gc.gridheight=1;
	        gc.gridwidth=12;//5;
	        gc.weightx=0.5;
	        
	       	gl.setConstraints(bPanelFr,gc);
	       	if(checkbox)remove(bPanelFp);
	       	add(bPanelFr);   
	       	
	       	
	       	setSize (frameBreite, frameHoehe);
        	setResizable(false);
        	setVisible(true);
	    }
	    
	protected void makeFp(ECCFrame eccframe, boolean checkbox)
	{
			eccframe.setTitle(text.frameTitleFp);
	    	a=11;
	    	b=20;
	    	a_scroll=(int)a;
     		b_scroll=(int)b;
	    	amin=-99;
     		amax=99;
     		bmin=-99;
     		bmax=99;
	    	maxwert=23; 
	        canvasGroesse=zeichenfenster;//2*abstand+zeichenfenster;
	        frameBreite=900;//canvasGroesse+300;
	     	frameHoehe=650;//canvasGroesse+100;
	        // Grafikbereich wird erzeugt
	        grafikFp= new GrafikFp(canvasGroesse,eccframe);
	        // Bedieungspanel wird erzeugt 
	        bPanelFp = new BedienungsPanelFp(eccframe); 
	        
	        gc.gridx=0;
	        gc.gridy=0;
	        gc.gridheight=5;
	        gc.gridwidth=5;
	        gc.weightx=0.5;	        
	        
    		gl.setConstraints(grafikFp,gc);
    		if(checkbox)
    			remove(grafikFr);
        	add(grafikFp);
        		
        	if(checkbox)
				remove(tPanel);
        	// Textpanel wird erzeugt
		    tPanel = new TextPanel(eccframe);            
		    
		    gc.gridx=6;
		    gc.gridy=0;
		    gc.gridheight=5;//10
		    gc.gridwidth=5;
		    gl.setConstraints(tPanel,gc);
		    
		    add(tPanel);
        	
        	gc.gridx=0;
	        gc.gridy=5;
	        gc.gridheight=1;
	        gc.gridwidth=12;//5;
	        gc.weightx=0.5;
	        
	        gl.setConstraints(bPanelFp,gc);
	        if(checkbox)remove(bPanelFr);
	        add(bPanelFp);	
	        
	        setSize (frameBreite, frameHoehe);
        	setResizable(false);
        	setVisible(true);			
	        
    }
	
}
