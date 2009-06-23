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

import java.awt.*;
import java.awt.event.*;
import java.text.DecimalFormat;

public class GrafikFp extends Canvas implements MouseListener, MouseMotionListener
{	
	private static final long serialVersionUID = 6472885893885917160L;
	GrafikFp grafikFp;
	Panel bPanelFp;
	ECCFrame eccframe;
	DecimalFormat df;
    /** Creates a new instance of GrafikFp */
    public GrafikFp(int size, ECCFrame eccframe) 
    {
       this.setSize(size,size);
       addMouseListener(this);
       addMouseMotionListener(this);
       grafikFp=(this);
       this.eccframe=eccframe;	
       
		df=new DecimalFormat("0");
		
		berechnePunkte(eccframe.maxwert);
    }
    
    public void paint (Graphics gold)
    {
	Graphics2D g = (Graphics2D)gold;
	BasicStroke roundStroke = new BasicStroke(1.0f, 1, 1);
 	BasicStroke roundStroke2 = new BasicStroke(1.6f,1,1);
    
    // Zeichnungsstift= normal 
    g.setStroke(roundStroke);
    
	// Kordinatensystem zeichnen
    zeichneKoordinatensystem(g); 
 	
 	// Antialiasing ein
    g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
    
    // Zeichnungsstift= fett 
    g.setStroke(roundStroke2);
    
    // ECC-Kurve zeichnen

    zeichneElliptischeKurve(g);
    	
  	// Antialiasing aus   
    g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_OFF);
    // Zeichnungsstift= normal 
    g.setStroke(roundStroke);
    
    // ECC-Gleichung zeichnen
    zeichneECCGleichung(g);
    
   
    // Antialiasing ein
    g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
    // gegebenenfalls ausgesuchte Punkte zeichnen
    zeichnePunkte(g);
        	
  	// Antialiasing aus   
    g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_OFF);
    }
    

	private void berechnePunkte(int max)
    {
        eccframe.punkt = new int[2*max][2];
        int zaehlerpunkte=0;
       
        for(int x = 0; x < max; x++)
        {
            for(int y = 0; y < max; y++)
            {
                int linkeSeite = (y * y) % max;
                int rechteSeite= ((x*x*x)+(int)eccframe.a*x+(int)eccframe.b) % max;
                if(linkeSeite == rechteSeite)
                {
               
                	eccframe.punkt[zaehlerpunkte][0] = x;
                    eccframe.punkt[zaehlerpunkte][1] = y;
                    zaehlerpunkte++;
                }
            }

        }
         eccframe.zaehlerpunkte=zaehlerpunkte;
    }
	

	private void zeichneKoordinatensystem(Graphics g)
    {

//        int width = eccframe.canvasGroesse;
        int height = eccframe.canvasGroesse;

        int maxwert=eccframe.maxwert;
//       	int abstand=eccframe.abstand;
        
        Color ganzhellgrau=new Color(230,230,230);
        g.setColor(ganzhellgrau);
        
         //vertikale linien  
        for(int i = 0; i < maxwert; i++)
            g.drawLine(xWertToXPixel(i), yWertToYPixel(0), xWertToXPixel(i), yWertToYPixel(maxwert-1));
		
		//horizontale linien
        for(int j = 0; j < maxwert; j++)
            g.drawLine(xWertToXPixel(0), yWertToYPixel(j), xWertToXPixel(maxwert-1), yWertToYPixel(j));
        
        g.setColor(Color.black);
        
        //y-Achse
        g.drawLine(xWertToXPixel(0), yWertToYPixel(0), xWertToXPixel(0), yWertToYPixel(maxwert-1));
       
        //x-Achse
        g.drawLine(xWertToXPixel(0), yWertToYPixel(0), xWertToXPixel(maxwert-1), yWertToYPixel(0));
   
   
		//striche auf den achsen, abstand von 1
        for(int x=1;x<maxwert;x++)
        	{
        		if(x%5==0||x==maxwert)
        		{
        			if(x!=0&&x!=maxwert)
        			{	
        				
        				if(x==5)
        					g.drawString(""+x,xWertToXPixel(x)-3,(height-eccframe.abstand)+20);
        				if(x>=10)
        					g.drawString(""+x,xWertToXPixel(x)-7,(height-eccframe.abstand)+20);
        			
        			}
        		g.drawLine(xWertToXPixel(x),(height-eccframe.abstand)-6,xWertToXPixel(x),(height-eccframe.abstand)+6);
        		
        		
        		}
        	
        
        if ((maxwert<=11)&&(x>=0)&&(x<=10)&&(x%5!=0)) g.drawString(""+x,xWertToXPixel(x)-3,(height-eccframe.abstand)+20);
        g.drawLine(xWertToXPixel(x),(height-eccframe.abstand)-3,xWertToXPixel(x),(height-eccframe.abstand)+3);
        	
        	
        	}
       

       
        for(int y=1;y<maxwert;y++)
        	{
        		if(y%5==0||y==maxwert)
        		{
        			if(y!=0&&y!=maxwert)
        			{
        			
        				if(y==5)
        					g.drawString(""+y,eccframe.abstand-14,yWertToYPixel(y)+5);
        				if(y>=10)
        					g.drawString(""+y,eccframe.abstand-21,yWertToYPixel(y)+5);
        			
        			}	
        			
        				g.drawLine(eccframe.abstand-6,yWertToYPixel(y),eccframe.abstand+6,yWertToYPixel(y));

        		}	
        		
        		
      if ((maxwert<=11)&&(y>=0)&&(y<=10)&&(y%5!=0)) g.drawString(""+y,eccframe.abstand-14,yWertToYPixel(y)+5);
          			g.drawLine(eccframe.abstand-3,yWertToYPixel(y),eccframe.abstand+3,yWertToYPixel(y));
        
        	}
		
     
       
	}
	
    private void zeichneECCGleichung(Graphics g)
    {    	
        Font fontklein = new Font(g.getFont().getName(), 1, 11);
        g.setFont(fontklein);
        FontMetrics fontmetricsklein = g.getFontMetrics();
        
        Font fontgross = new Font(g.getFont().getName(), 1, 14);
        g.setFont(fontgross);
        FontMetrics fontmetricsgross = g.getFontMetrics();
        
        g.setColor(Color.blue);
        int x = 20;
        int y = 15;
        
        String text = "y";
        g.setFont(fontgross);
        g.drawString(text, x,y);
        x += fontmetricsgross.stringWidth(text) + 2;
        
        text = "2";
        g.setFont(fontklein);
        g.drawString(text, x, y - fontmetricsklein.getHeight() / 2);
        x += fontmetricsklein.stringWidth(text);
        
        text = " = x";
        g.setFont(fontgross);
        g.drawString(text, x, y);
        x += fontmetricsgross.stringWidth(text) + 2;
        
        text = "3";
        g.setFont(fontklein);
        g.drawString(text, x, y - fontmetricsklein.getHeight() / 2);
        x+= fontmetricsklein.stringWidth(text);
        
        
text="";
        
        if(eccframe.a < 0)  text =" - ";
        
        else if(eccframe.a > 0) text = " + ";
        	
        if ((eccframe.a < 0) || (eccframe.a > 0)) {
        	
        	if(eccframe.a < 0) g.setColor(Color.RED); 
        	g.setFont(fontgross);
        	g.drawString(text, x, y);
        	x+= fontmetricsgross.stringWidth(text)+2;
        	
        	text=df.format(Math.abs(eccframe.a));
        	g.setColor(Color.RED); 
        	g.setFont(fontgross);
        	g.drawString(text, x, y);
        	x+= fontmetricsgross.stringWidth(text);
        	
        	text="x";
        	g.setColor(Color.BLUE);       
        	g.setFont(fontgross);
        	g.drawString(text, x, y);
        	x+= fontmetricsgross.stringWidth(text)+2;

        	}
        
        text="";g.setColor(Color.blue); //Default =blue
        
        if(eccframe.b < 0)  text =" - ";
        
        else if(eccframe.b > 0) text = " + ";
        	
        if ((eccframe.b < 0) || (eccframe.b > 0)) {
        	
        	Color lila=new Color(148,3,148);
		    if(eccframe.b < 0) g.setColor(lila); 
        	g.setFont(fontgross);
        	g.drawString(text, x, y);
        	x+= fontmetricsgross.stringWidth(text)+2;
        	
        	text=df.format(Math.abs(eccframe.b)); 
        	g.setColor(lila); 
        	g.setFont(fontgross);
        	g.drawString(text, x, y);
        	x+= fontmetricsgross.stringWidth(text);
        	
        	} 

		g.setColor(Color.blue); //Default =blue	
		
		//text = " über ";
		text = eccframe.text.graph1;
		g.setFont(fontgross);
		g.drawString(text, x, y );
		x+=fontmetricsgross.stringWidth(text);
		
		g.setColor(Color.black);
		text = "F";
		g.setFont(fontgross);
		g.drawString(text, x, y );
		x+=fontmetricsgross.stringWidth(text);		
		
		text=""+eccframe.p[eccframe.pIndex];
		g.setFont(fontklein);
		g.drawString(text, x, y + fontmetricsklein.getHeight() / 2);
		x+=fontmetricsklein.stringWidth(text);
		
		g.setColor(Color.blue);
		text=eccframe.text.graph2+((eccframe.zaehlerpunkte)+1)+eccframe.text.graph3;
		g.setFont(fontgross);			
        g.drawString(text, x, y);
        x+=fontmetricsgross.stringWidth(text);
        
        
    }
    
    
    private void zeichneElliptischeKurve(Graphics g)
    {

//        int width=eccframe.canvasGroesse;
//        int height = eccframe.canvasGroesse;
        int xwert=0;
        int ywert=0;
        
		berechnePunkte(eccframe.maxwert);
     	for (int i=0;i<eccframe.zaehlerpunkte;i++) {
			
			xwert=xWertToXPixel(eccframe.punkt[i][0]);
			ywert=yWertToYPixel(eccframe.punkt[i][1]);
				
     	    g.setColor(Color.black);
	    	g.fillArc(xwert - 2,ywert - 2, 5, 5, 0, 360);
		   	g.setColor(Color.CYAN);
		    g.fillArc(xwert - 1,ywert - 1, 3, 3, 0, 360);
		    
		    }

     
        
    }
    
    
    
       
    // Funktion überprüft, ob Punkte existieren und zeichnet diese  
	private void zeichnePunkte (Graphics gold) 
	{
	
	
		Graphics2D g = (Graphics2D)gold;
		BasicStroke roundStroke = new BasicStroke(1.0f, 1, 1);
	 	BasicStroke roundStroke2 = new BasicStroke(1.8f,1,1);
	    
	    // Zeichnungsstift= dick 
	    g.setStroke(roundStroke);
	    	
//	   	int height = eccframe.canvasGroesse;
	   	boolean pgleichq=false;
	   	pgleichq=((eccframe.pset)&& (eccframe.qset)&&(eccframe.px==eccframe.qx) && (eccframe.py==eccframe.qy));
	   	
	   	//P+Q
	    if (eccframe.rset && eccframe.qset) 
	    {
		    g.setStroke(roundStroke2);

		   	g.setColor(new Color(255,0,255));
		   	
			if(eccframe.np>1)
		    	drawString(g,"R = "+eccframe.np+"P", eccframe.rx, eccframe.ry);
		    else	
		    	drawString(g,"R", eccframe.rx, eccframe.ry); 

		    
		    g.setColor(Color.black);
	    	g.fillArc(eccframe.rx - 2,eccframe.ry - 2, 5, 5, 0, 360);	
		   	g.setColor(new Color(255,0,255));
			g.fillArc(eccframe.rx - 1,eccframe.ry - 1, 3, 3, 0, 360);
			
		   	g.setStroke(roundStroke);
	    }
	    
	    //2P
	    if (eccframe.rset && !eccframe.qset&&eccframe.np<=2) 
	    {
		    g.setStroke(roundStroke2);
//		    Color lila=new Color(148,3,148);		    			
			
		   	
		   	g.setColor(Color.black);
	    	g.fillArc(eccframe.rx - 2,eccframe.ry - 2, 5, 5, 0, 360);
		   	g.setColor(new Color(255,0,255));	
			g.fillArc(eccframe.rx - 1,eccframe.ry - 1, 3, 3, 0, 360);
		    drawString(g,"R = 2P", eccframe.rx, eccframe.ry); 
		   	
		   	g.setStroke(roundStroke);
	    }
	    
	     //2P, jedoch np>2 
	    if (eccframe.rset && !eccframe.qset&&eccframe.np>2) 
	    {
		    g.setStroke(roundStroke2);
//		    Color lila=new Color(148,3,148);		    			
			
		   	
		   	g.setColor(Color.black);
	    	g.fillArc(eccframe.rx - 2,eccframe.ry - 2, 5, 5, 0, 360);
		   	g.setColor(Color.red);	
			g.fillArc(eccframe.rx - 1,eccframe.ry - 1, 3, 3, 0, 360);
		    drawString(g,"R = P = "+eccframe.np+"P", eccframe.rx, eccframe.ry); 
		   	
		   	g.setStroke(roundStroke);
	    }
	    
	    
	    
	    
	    //R unendlich
	    if (eccframe.rNaN)
     	{
     		g.setStroke(roundStroke2);
			Color lila=new Color(148,3,148);	
		   	g.setColor(lila);

		   	g.setStroke(roundStroke);
		}
	   	
	    //    keine Punkte markiert, nur Mausbewegung
	   	if(!(eccframe.pset&&eccframe.qset)&&!eccframe.rset&&!eccframe.rNaN)
	   	{    			
    		//liegt x-koordinate der Maus auf dem Graph?
    		if ((punktAufKurve(eccframe.ax,eccframe.ay)!=-1)&&(eccframe.ax!=0)&&(eccframe.ay!=0))
    		{
    			g.setColor(Color.black);
	    		g.fillArc(eccframe.ax - 2,eccframe.ay - 2, 5, 5, 0, 360);
	    		g.setColor(Color.red);
	    		g.fillArc(eccframe.ax - 1,eccframe.ay - 1, 3, 3, 0, 360);
	    		//darstellung der koordinaten im canvas bei mousemoved
	    		DecimalFormat df=new DecimalFormat("0");
        		String ax=df.format(eccframe.dax);
       			String ay=df.format(eccframe.day);	
                
//                if (eccframe.dax<=(eccframe.maxwert/2)) {
//                	
//                   if(eccframe.day>0) drawString(g,"("+ax+"/"+ay+")",eccframe.ax,eccframe.ay);
//           	       else 
//           	    	   drawString(g,"("+ax+"/"+ay+")",eccframe.ax,eccframe.ay);
//                }
                

//                if (eccframe.dax>(eccframe.maxwert/2)) {
//                	
//                   if(eccframe.day>0) drawString(g,"("+ax+"/"+ay+")",eccframe.ax,eccframe.ay);
//           	       else 
                	drawString(g,"("+ax+"/"+ay+")",eccframe.ax,eccframe.ay);
//                }
                
                
	   		}
        	  		
	   	}
	
	    if ((!pgleichq)&&(eccframe.pset)) 
	    {
	    	g.setColor(Color.black);
	    	g.fillArc(eccframe.px - 2,eccframe.py - 2, 5, 5, 0, 360);
		    g.setColor(Color.red);
		    g.fillArc(eccframe.px - 1,eccframe.py - 1, 3, 3, 0, 360);
		    drawString(g,"P", eccframe.px, eccframe.py);
	    }
	    
	    if ((!pgleichq)&&(eccframe.qset)) 
	    {
	    	g.setColor(Color.black);
	    	g.fillArc(eccframe.qx - 2,eccframe.qy - 2, 5, 5, 0, 360);
		   	g.setColor(Color.red);
		    g.fillArc(eccframe.qx - 1,eccframe.qy - 1, 3, 3, 0, 360);
		    if(eccframe.np>1)
		    	drawString(g,""+(eccframe.np-1)+"P", eccframe.qx, eccframe.qy);
		    else	
		    	drawString(g,"Q", eccframe.qx, eccframe.qy); 
	    }
	    
	    if (pgleichq&&eccframe.np==1) 
	    {
	    	g.setColor(Color.black);
	    	g.fillArc(eccframe.qx - 2,eccframe.qy - 2, 5, 5, 0, 360);
		   	g.setColor(Color.red);
		    g.fillArc(eccframe.qx - 1,eccframe.qy - 1, 3, 3, 0, 360);
		    drawString(g,"P = Q", eccframe.qx, eccframe.qy); 
	
	    }  
	    
	     if (pgleichq&&eccframe.np>1) 
	    {
	    	g.setColor(Color.black);
	    	g.fillArc(eccframe.qx - 2,eccframe.qy - 2, 5, 5, 0, 360);
		   	g.setColor(Color.red);
		    g.fillArc(eccframe.qx - 1,eccframe.qy - 1, 3, 3, 0, 360);
		    drawString(g,"P = "+(eccframe.np-1)+"P", eccframe.qx, eccframe.qy); 
	
	    } 
	    
	    
    }
    
	private void drawString(Graphics2D g, String text, int x, int y){
		if(x > eccframe.canvasGroesse / 2){
			x = x - 8;
			for(byte c : text.getBytes()){
				x -= 7;
			}
		}
		else
			x = x + 8; 
		
		if(y > eccframe.canvasGroesse / 2)
			y = y - 8;
		else
			y = y + 14;
		
		g.drawString(text, x, y);
	}
	
//Actionhandler

	// Maus wurde geklickt
	public void mouseClicked(MouseEvent event)
	{
//		int xmouse = event.getX();
//        int ymouse = event.getY();
        
		if(!eccframe.pset&&eccframe.ax!=0)//&&punktAufKurve(xmouse, ymouse))
		{
			eccframe.px=eccframe.ax;
			eccframe.py=eccframe.ay;
			eccframe.dpx=eccframe.dax;
			eccframe.dpy=eccframe.day;
			eccframe.pset=true;
			
			DecimalFormat df=new DecimalFormat("0");
	        String sx=df.format(eccframe.dpx);
	        String sy=df.format(eccframe.dpy);
	        eccframe.tPanel.LabelP.setText("P= ("+sx+"/"+sy+")");
	        eccframe.tPanel.pGewaehlt();
	    	eccframe.bPanelFp.ButtonP.setEnabled(true);
	    	eccframe.bPanelFp.ButtonDelete.setEnabled(true);
	       	eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelP.getText();
	       	if(ECCFrame.log != null) ECCFrame.log.setText(eccframe.LogText);
	       	grafikFp.repaint();
		}
		else if(eccframe.pset&&!eccframe.rset&&!eccframe.qset&&eccframe.ax!=0&&!eccframe.rNaN)//&&punktAufKurve(xmouse, ymouse))
		{
			eccframe.qx=eccframe.ax;
			eccframe.qy=eccframe.ay;
			eccframe.dqx=eccframe.dax;
			eccframe.dqy=eccframe.day;
			eccframe.qset=true;
			
			DecimalFormat df=new DecimalFormat("0");
	        String sx=df.format(eccframe.dqx);
	        String sy=df.format(eccframe.dqy);
	        eccframe.tPanel.LabelQ.setText("Q= ("+sx+"/"+sy+")");
	       	eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelQ.getText();
	       	if(ECCFrame.log != null) ECCFrame.log.setText(eccframe.LogText);
	       	eccframe.tPanel.qGewaehlt();
	       	eccframe.bPanelFp.ButtonP.setEnabled(false);
	       	eccframe.bPanelFp.ButtonPQ.setEnabled(true);
	    	eccframe.bPanelFp.ButtonDelete.setEnabled(true);
	    	
	       	grafikFp.repaint();
		}
	}
		
    
    // Funktionrümpfe notwendig für Implementierung
    public void mouseEntered(MouseEvent mouseevent)
    {}

    public void mouseExited(MouseEvent mouseevent)
    {}

    public void mousePressed(MouseEvent mouseevent)
    {}

    public void mouseReleased(MouseEvent mouseevent)
    {}
    
    public void mouseDragged(MouseEvent mouseevent)
  	{}
  	
    public void mouseMoved(MouseEvent event)
    {
//    	int height=eccframe.canvasGroesse;
        int xmouse = event.getX();
        int ymouse = event.getY();
		
		int treffer=punktAufKurve(xmouse, ymouse);
	
	
		if (!eccframe.rset&&!eccframe.rNaN&&treffer!=-1)
		{
			if(!(eccframe.pset&&eccframe.qset)&&!eccframe.rset)
			{
				if ((eccframe.punkt[treffer][0]!=eccframe.dax)||(eccframe.punkt[treffer][1]!=eccframe.day)) 
				{
				
				grafikFp.repaint(eccframe.ax-100, eccframe.ay-100, 200, 200);
		       	eccframe.ax=xWertToXPixel(eccframe.punkt[treffer][0]);
				eccframe.ay=yWertToYPixel(eccframe.punkt[treffer][1]);
				eccframe.dax=eccframe.punkt[treffer][0];
				eccframe.day=eccframe.punkt[treffer][1];
				grafikFp.repaint(eccframe.ax-100, eccframe.ay-100, 200, 200);
				
				}
			
	      	}
      	}
  		
  	}
  
     
    

//Rechenfunktionen

    //liegt die pixel-koordinate auf dem graph??
    int punktAufKurve(int xPixel, int yPixel)
    {
    	double xWert,yWert;
//    	int height=eccframe.canvasGroesse;
    	
		xWert=xPixelToXWert(xPixel);
		yWert=yPixelToYWert(yPixel);
		
		double diffx=0;
		double diffy=0;
		double dummy=0;
		int indexx=-1;
		int indexy=-1;
		
		if (eccframe.zaehlerpunkte==0) return -1;
        
        // Nächstliegende X-Koordinate finden.
        for(int i = 0; i < eccframe.zaehlerpunkte; i++)
        {
            dummy=Math.abs(eccframe.punkt[i][0]-xWert);
            
            if (indexx==-1) {diffx=dummy;indexx=i;}
            	
            	else if ((indexx!=-1)&&(dummy<diffx)) {diffx=dummy;indexx=i;}
            
        }
        
        int xgefunden=eccframe.punkt[indexx][0];
        
        // Nächstliegende Y-Koordinate finden.
        
        for(int i = 0; i < eccframe.zaehlerpunkte; i++) {
        
            if (eccframe.punkt[i][0]==xgefunden) {
            	
            	dummy=(int)Math.abs(eccframe.punkt[i][1]-yWert);
            	
            	if (indexy==-1) {diffy=dummy;indexy=i;}
            	
            	else if ((indexy!=-1)&&(dummy<diffy)) {diffy=dummy;indexy=i;}

            }
            
        }
	return indexy;

    }
    
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   	//Rechenweg IMMER xPixel=>xWert=>yWert=>yPixel
	//alles andere führt zu Rundungsfehlern!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    // NEU konvertiert x-Pixel auf dem Canvas in X-Werte im Koord.System
    double xPixelToXWert(int xPixel)
	{
		int height=eccframe.canvasGroesse;
		int maxwert=eccframe.maxwert-1;
		
		double Skalierung = ((double)(height - 2 * eccframe.abstand))/maxwert;
		double x;
		x=((double)xPixel-eccframe.abstand)/Skalierung;

		return x;
	}
	
    // NEU konvertiert y-Pixel auf dem Canvas in Y-Werte im Koord.System
    double yPixelToYWert(int YPixel)
    {
        int height = eccframe.canvasGroesse;
        int maxwert=eccframe.maxwert-1;
        
        double Skalierung = ((double)(height - 2 * eccframe.abstand))/maxwert;
        
    	double y;
    	y=maxwert - (double)((YPixel - eccframe.abstand)/Skalierung);
    	
    	return y; 	
    }
   

    // NEU berechnet die Canvas-x-Pixelkoordinate eines x-Wertes des Graphen
    int xWertToXPixel(double wert)
    {
    	int height=eccframe.canvasGroesse;
    	int maxwert=eccframe.maxwert-1;
    	
    	double Skalierung = ((double)(height - 2 * eccframe.abstand))/maxwert;
    	int xPixel;
    	xPixel=(int)(Skalierung*wert+eccframe.abstand);
    	
    	return xPixel; 	
    }
	
	// NEU berechnet die Canvas-y-Pixelkoordinate eines y-Wertes des Graphen
    int yWertToYPixel(double wert)
    {
    	int height=eccframe.canvasGroesse;
    	int maxwert=eccframe.maxwert-1;
    	
    	double Skalierung = ((double)(height - 2 * eccframe.abstand))/maxwert;
    	int yPixel;
    	yPixel=(int)(Skalierung*((double)maxwert - wert) + eccframe.abstand);
    	
    	return yPixel; 	
    }
    	
}
