/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

package eccdemo;

import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class ECCFrame extends Frame //implements KeyListener
{
 	
 	private static final long serialVersionUID = -1076165377082193067L;

	/*****  DEFINITIONEN   *****/
 	 
 	//0=deutsch, 1=englisch
    protected static int sprache=0;
    
    //0=Fr, 1=Fp
    protected static int raum=0;
    
 	//Startwerte der Kurvenparameter
	protected double a;
    protected double b;
    //Scrollrad-Schieber
    protected int a_scroll;
    protected int b_scroll;
    //nachkommastellen: 10=1, 100=2 etc.
    protected int nks;
    
    
    protected int [] c={6,8,11,12,22,24,33,44,66,88}; 
    protected int amin;	// Werte für Panel a
    protected int amax;
    protected int bmin;	// Werte für Panel b
    protected int bmax;
   
    protected int px;			// x-Pixelkoordinate Punkt P
	protected int py;			// y-Pixelkoordinate Punkt P
	protected double dpx;		// double-Wert von px
	protected double dpy;		// double-Wert von py
	protected boolean pset;// Wurde ein Punkt P gewählt?false=nein;
  
    protected int qx;			// x-Pixelkoordinate Punkt Q
	protected int qy;			// y-Pixelkoordinate Punkt Q
	protected double dqx;		// double-Wert von qx
	protected double dqy;		// double-Wert von qy
	protected boolean qset; 	// Wurde ein Punkt Q gewählt?false=nein;
	
	protected int rx;			// x-Pixelkoordinate Punkt R
	protected int ry;			// y-Pixelkoordinate Punkt R
	protected double drx;		// double-Wert von rx
	protected double dry;		// double-Wert von ry
	protected boolean rset; 	// Wurde ein Punkt R berechnet?false=nein;
	protected boolean rNaN; 	// Ist R unendlich?false=nein;
    protected int np;				// bei welchem vielfachen von P befindet sich das Programm? 
    
    protected int ax;			// x-Pixelkoordinate AuswahlPunkt A
	protected int ay;			// y-Pixelkoordinate AuswahlPunkt A
	protected double dax;		// double-Wert von ax
	protected double day;		// double-Wert von ay
	protected boolean aset; 	// Wurde ein AuswahlPunkt gewählt, aber noch nicht mit
    										// Maus geklickt
    protected int maxwert;    //standardwerte= maxwert=15, pixelPro=15
   
   	protected int abstand;
    protected int zeichenfenster; /// Pixel des Zeichenfensters
    protected int pixelProZelle;
    
    protected int canvasGroesse;//grösse +1, damit immer genau eine mitte existiert; immer quadratisch
    

    protected int frameBreite;
    protected int frameHoehe;
    
    protected String LogText=""; // Leere LogDatei
    
    protected GrafikFp grafikFp;
    protected GrafikFr grafikFr;
    protected BedienungsPanelFp bPanelFp;
    protected BedienungsPanelFr bPanelFr;
    protected TextPanel tPanel;
    protected GridBagLayout gl;
    protected GridBagConstraints gc;
    protected Texte text;
    protected static ECCFrame eccframe;

	public static LogDatei log;
    
    protected int[][] punkt;
    protected int zaehlerpunkte=0;
    
    protected int [] p={3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};  

   protected int pIndex=7;
   protected int cIndex=1; 
    
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
        ECCFrame.raum=raum;
        ECCFrame.sprache=sprache;
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
     		makeFr(false);
     		
     	if(raum==1)
     		makeFp(false);
		
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
    //public void main (String args [])
    public static void main (String args [])
    {
    	eccframe=new ECCFrame(sprache,raum);
    	
    	if (sprache==0)
    		eccframe.setTitle("ECC-Demo 1.1: Punktaddition auf Elliptischen Kurven über den reellen Zahlenraum R");
    	else
    		eccframe.setTitle("ECC Demonstration 1.1: Point addition on elliptic curves over the real number space R");
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
	
	protected void makeFr(boolean checkbox)
	{
			this.setTitle(Texte.frameTitleFr);
     		a=-10;
     		b=15;
     		a_scroll=(int)a*this.nks;
     		b_scroll=(int)b*this.nks;
     		cIndex=3; 
     		amin=-50;
     		amax=50;
     		bmin=-50;
     		bmax=50;
	        maxwert=c[cIndex];    //standardwerte= maxwert=15, pixelPro=15
	        pixelProZelle=264/this.maxwert;//anzahl sollte gerade sein, damit das raster genau auf den achsen liegt
	        canvasGroesse=(11*2*24)+1;//grösse +1, damit immer genau eine mitte existiert; immer quadratisch
			frameBreite=900;//canvasGroesse+300;
	        frameHoehe=650;//canvasGroesse+100;
	        // Grafikbereich wird erzeugt
	        grafikFr= new GrafikFr(canvasGroesse,this);
	        // Bedieungspanel wird erzeugt 
	        bPanelFr = new BedienungsPanelFr(this); 
	        
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
		    tPanel = new TextPanel(this);            
		    
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
        	bPanelFr.startLogDatei();
	    }
	    
	protected void makeFp(boolean checkbox)
	{
			this.setTitle(Texte.frameTitleFp);
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
	        grafikFp= new GrafikFp(canvasGroesse,this);
	    	// Bedieungspanel wird erzeugt 
	        bPanelFp = new BedienungsPanelFp(this); 
	        
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
		    tPanel = new TextPanel(this);            
		    
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
        	bPanelFp.startLogDatei();
	        
    }
	
}
