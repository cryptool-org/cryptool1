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

public class GrafikFr extends Canvas implements MouseListener, MouseMotionListener
{	
	private static final long serialVersionUID = 5809793260799259274L;
	GrafikFr grafikFr;
	Panel bPanelFr;
	ECCFrame eccframe;
	DecimalFormat df;
    /** Creates a new instance of GrafikFr */
    public GrafikFr(int size, ECCFrame eccframe) 
    {
       this.setSize(size,size);
       addMouseListener(this);
       addMouseMotionListener(this);
       grafikFr=(this);
       this.eccframe=eccframe;	
       
       if(eccframe.nks==10)
			df=new DecimalFormat("0.0");
		if(eccframe.nks==100)
			df=new DecimalFormat("0.00");
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
    
    private void zeichneKoordinatensystem(Graphics g)
    {

        int width = eccframe.canvasGroesse;
        int height = eccframe.canvasGroesse;
        int ppz=eccframe.pixelProZelle;
        int maxwert=eccframe.maxwert;
        //Raster
        Color ganzhellgrau=new Color(230,230,230);
        g.setColor(ganzhellgrau);
        //horizontale linien
        for (int yPixel=0;yPixel<=height;yPixel=yPixel+ppz)
            g.drawLine(0,yPixel,width,yPixel);
        //vertikale linien    
        for (int xPixel=0;xPixel<=width;xPixel=xPixel+ppz)
            g.drawLine(xPixel,0,xPixel,height);      
               
        g.setColor(Color.black);
        //y-Achse
        g.drawLine((width-1)/2, 0, (width-1)/2, height);
        //x-Achse
        g.drawLine(0,(height-1)/2,width,(height-1)/2);
   
		//striche auf den achsen, abstand von 1
        for(int x=-maxwert+1;x<=maxwert;x++)
        	{
        		if(x%5==0)
        		{
        			if(x!=0&&x!=maxwert&&maxwert<50)
        			{	
        				if(x<=-10)
        					g.drawString(""+x,xWertToXPixel(x)-10,(height-1)/2+20);
        				
        				if(x==-5)
        					g.drawString(""+x,xWertToXPixel(x)-7,(height-1)/2+20);
        				if(x==5)
        					g.drawString(""+x,xWertToXPixel(x)-3,(height-1)/2+20);
        				
        				if(x>=10)
        					g.drawString(""+x,xWertToXPixel(x)-7,(height-1)/2+20);
        			
        			}
        			
        			if(x!=0&&x!=maxwert&&maxwert>50)
        			{	
        				if((x<=-10)&&(x%10==0))
        					g.drawString(""+x,xWertToXPixel(x)-10,(height-1)/2+20);
        				
        				
        				if((x>=10)&&(x%10==0))
        					g.drawString(""+x,xWertToXPixel(x)-7,(height-1)/2+20);
        			
        			}        			
        			
        			if(x!=maxwert)
        				g.drawLine(xWertToXPixel(x),(height-1)/2-6,xWertToXPixel(x),(height-1)/2+6);
        		
        		
        		}
        	
        		if(x==maxwert)
        		{
        			g.drawLine(xWertToXPixel(x)-ppz/2-1,xWertToXPixel(0)-8,width-1,(height-1)/2);
        			g.drawLine(xWertToXPixel(x)-ppz/2-1,xWertToXPixel(0)+8,width-1,(height-1)/2);
        		}
        		else
        			g.drawLine(xWertToXPixel(x),(height-1)/2-3,xWertToXPixel(x),(height-1)/2+3);
        	}
       
       
        for(int y=-maxwert+1;y<=maxwert;y++)
        	{
        		if(y%5==0)
        		{
        			if(y!=0&&y!=maxwert&&maxwert<50)
        			{
        				if(y<=-10)
        					g.drawString(""+y,(width-1)/2-25,yWertToYPixel(y)+5);
        				if(y==-5)
        					g.drawString(""+y,(width-1)/2-18,yWertToYPixel(y)+5);
        				if(y==5)
        					g.drawString(""+y,(width-1)/2-14,yWertToYPixel(y)+5);
        				if(y>=10)
        					g.drawString(""+y,(width-1)/2-21,yWertToYPixel(y)+5);
        			
        			}	
        			
  
          			if(y!=0&&y!=maxwert&&maxwert>50)
        			{
        				if((y<=-10)&&(y%10==0))
        					g.drawString(""+y,(width-1)/2-25,yWertToYPixel(y)+5);

        				if((y>=10)&&(y%10==0))
        					g.drawString(""+y,(width-1)/2-21,yWertToYPixel(y)+5);
        			
        			}
  
  
        			
        			if(y!=maxwert)
        				g.drawLine((width-1)/2-6,yWertToYPixel(y),(width-1)/2+6,yWertToYPixel(y));
        			/*	
        			g.drawLine((width-1)/2-6,yWertToYPixel(y),(width-1)/2+6,yWertToYPixel(y));
        			if(y!=0)
        				g.drawString(""+y,(width-1)/2-25,yWertToYPixel(y)+5);
        				*/
        		}	
        		
        		
        		if(y==maxwert)
        		{
        			g.drawLine(xWertToXPixel(0)-8,yWertToYPixel(y)+ppz/2+1,(width-1)/2,0);
        			g.drawLine(xWertToXPixel(0)+8,yWertToYPixel(y)+ppz/2+1,(width-1)/2,0);
        		}
        		else
        			g.drawLine((width-1)/2-3,yWertToYPixel(y),(width-1)/2+3,yWertToYPixel(y));
        
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
        
        int x = 10;
        int y = eccframe.grafikFr.getHeight()-10;
       
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
        
    }
    
    private void zeichneElliptischeKurve(Graphics g)
    {
        g.setColor(Color.blue);
        int width=eccframe.canvasGroesse;
        int height = eccframe.canvasGroesse;
        int yPixel, nextYPixel;
        double xWert, nextXWert, yWert,nextYWert;
        
        xWert=xPixelToXWert(0);
        yWert=xWertToYWert(xWert);
        yPixel=yWertToYPixel(yWert);
            
        for (int xPixel=0;xPixel<(width-1);xPixel++)
        {
            nextXWert=xPixelToXWert(xPixel+1);
            nextYWert=xWertToYWert(nextXWert);
            nextYPixel=yWertToYPixel(nextYWert);
            
            yPixel=yWertToYPixel(xWertToYWert(xPixelToXWert(xPixel)));
            nextYPixel=yWertToYPixel(xWertToYWert(xPixelToXWert(xPixel+1)));
            
            //dieser und der nächste Pixel liegen auf der x-Achse =>nichts zeichnen
            if(yWert==0&&nextYWert==0)/*nichts machen*/;
            
            else
            {
                g.drawLine(xPixel,yPixel,xPixel+1,nextYPixel);
                g.drawLine(xPixel,height-2-yPixel,xPixel+1,height-2-nextYPixel);
            }
            
            //Werte schon berechnet: Kopieren statt Denken!
            xWert=nextXWert;
            yWert=nextYWert;
            yPixel=nextYPixel; 
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
	    	
	   	int height = eccframe.canvasGroesse;
	   	boolean pgleichq=false;
	   	pgleichq=((eccframe.pset)&& (eccframe.qset)&&(eccframe.px==eccframe.qx) && (eccframe.py==eccframe.qy));
	   	
	   	//P+Q
	    if (eccframe.rset && eccframe.qset) 
	    {
		    g.setStroke(roundStroke2);
		    Color lila=new Color(148,3,148);
			g.setColor(lila);
			
			// Q in der Mitte
			if ((eccframe.rx<eccframe.qx && eccframe.qx<eccframe.px)||(eccframe.rx>eccframe.qx && eccframe.qx>eccframe.px))
			//	g.drawLine(eccframe.px,eccframe.py,eccframe.rx,height-eccframe.ry);
				zeichneLinie(eccframe.dpx,eccframe.dpy,eccframe.drx,-eccframe.dry,lila,g);
			
			//P in der Mitte
			if ((eccframe.rx<eccframe.px && eccframe.px<=eccframe.qx)||(eccframe.rx>eccframe.px && eccframe.px>=eccframe.qx))
			//	g.drawLine(eccframe.qx,eccframe.qy,eccframe.rx,height-eccframe.ry);
		   		zeichneLinie(eccframe.dqx,eccframe.dqy,eccframe.drx,-eccframe.dry,lila,g);
		   
		    // Wenn -R zwischen P und Q liegt, dann reicht Linie PQ
		    //R in der Mitte
		    if ((eccframe.rx<=eccframe.px && eccframe.rx>=eccframe.qx)||(eccframe.rx>=eccframe.px && eccframe.rx<=eccframe.qx))
		   	//	g.drawLine(eccframe.px,eccframe.py,eccframe.qx,eccframe.qy);
		   		zeichneLinie(eccframe.dpx,eccframe.dpy,eccframe.dqx,eccframe.dqy,lila,g);
		   	g.setColor(new Color(255,0,255));
		   	
			if(eccframe.np>1)
                if(eccframe.dry<0)
                    g.drawString("R = "+eccframe.np+"P", eccframe.rx + 8, eccframe.ry-4);
                else
                    g.drawString("R = "+eccframe.np+"P", eccframe.rx + 8, eccframe.ry+13);
		    else	
                if(eccframe.dry<0)
                    g.drawString("R", eccframe.rx + 8, eccframe.ry-4);
                else
                    g.drawString("R", eccframe.rx + 8, eccframe.ry+13);
			//g.drawLine(eccframe.rx,height-eccframe.ry,eccframe.rx,eccframe.ry);
			zeichneLinie(eccframe.drx,-eccframe.dry,eccframe.drx,eccframe.dry,new Color(255,0,255),g);
		   	
		   	
		    g.setColor(Color.black);
	    	g.fillArc(eccframe.rx - 3,height-eccframe.ry - 3, 6, 6, 0, 360);	
		   	g.setColor(lila);
		    g.fillArc(eccframe.rx - 2,height-eccframe.ry - 2, 4, 4, 0, 360);
            if(eccframe.dry>0)
                g.drawString("-R", eccframe.rx +8, height-eccframe.ry-4); 
            else
                g.drawString("-R", eccframe.rx +8, height-eccframe.ry+13);
		    g.setColor(Color.black);
	    	g.fillArc(eccframe.rx - 3,eccframe.ry - 3, 6, 6, 0, 360);	
		   	g.setColor(new Color(255,0,255));
			g.fillArc(eccframe.rx - 2,eccframe.ry - 2, 4, 4, 0, 360);
			
		   	g.setStroke(roundStroke);
	    }
	    
	    //2P
	    if (eccframe.rset && !eccframe.qset) 
	    {
		    g.setStroke(roundStroke2);
		    Color lila=new Color(148,3,148);		    			
			g.setColor(lila);
			
			//g.drawLine(eccframe.px,eccframe.py,eccframe.rx,height-eccframe.ry);
		    zeichneLinie(eccframe.dpx,eccframe.dpy,eccframe.drx,-eccframe.dry,lila,g);		   	
		
		//	g.drawLine(eccframe.rx,height-eccframe.ry,eccframe.rx,eccframe.ry);
		    zeichneLinie(eccframe.drx,-eccframe.dry,eccframe.drx,eccframe.dry,new Color(255,0,255),g);
		   	
		   	g.setColor(Color.black);
	    	g.fillArc(eccframe.rx - 3,height-eccframe.ry - 3, 6, 6, 0, 360);	
		   	g.setColor(lila);
		    g.fillArc(eccframe.rx - 2,height-eccframe.ry - 2, 4, 4, 0, 360);
            if(eccframe.dry>0)
                g.drawString("-R", eccframe.rx +8, height-eccframe.ry+8); 
            else
                g.drawString("-R", eccframe.rx +8, height-eccframe.ry+8); 
		   	g.setColor(Color.black);
	    	g.fillArc(eccframe.rx - 3,eccframe.ry - 3, 6, 6, 0, 360);
		   	g.setColor(new Color(255,0,255));	
			g.fillArc(eccframe.rx - 2,eccframe.ry - 2, 4, 4, 0, 360);
            if(eccframe.dry<0)
                g.drawString("R = 2P", eccframe.rx + 8, eccframe.ry-4); 
            else
                g.drawString("R = 2P", eccframe.rx + 8, eccframe.ry+13);
		   	g.setStroke(roundStroke);
	    }
	    
	    //R unendlich
	    if (eccframe.rNaN)
     	{
     		g.setStroke(roundStroke2);
			Color lila=new Color(148,3,148);	
		   	g.setColor(lila);
		
			g.drawLine(eccframe.px,height,eccframe.px,0);
			//zeichneLinie(eccframe.dpx,yPixelToYWert(eccframe.canvasGroesse),eccframe.dpx,0,new Color(148,3,148),g);
		   	g.setStroke(roundStroke);
		}
	   	
        //keine Punkte markiert, nur Mausbewegung
	   	if(!(eccframe.pset&&eccframe.qset)&&!eccframe.rset&&!eccframe.rNaN)
	   	{    			
    		//liegt x-koordinate der Maus auf dem Graph?
    		if (punktAufKurve(eccframe.ax,eccframe.ay))
    		{
    			g.setColor(Color.black);
	    		g.fillArc(eccframe.ax - 3,eccframe.ay - 3, 6, 6, 0, 360);
	    		g.setColor(Color.red);
	    		g.fillArc(eccframe.ax - 2,eccframe.ay - 2, 4, 4, 0, 360);
	    		DecimalFormat df=new DecimalFormat("0.00");
        		String ax=df.format(eccframe.dax);
       			String ay=df.format(eccframe.day);	
       			if(eccframe.day<0)
	    			g.drawString("("+ax+"/"+ay+")",eccframe.ax+10,eccframe.ay-4);
	    		else
	    			g.drawString("("+ax+"/"+ay+")",eccframe.ax+10,eccframe.ay+13);
    		}
        	  		
	   	}
	   	
        //Punkt P
	    if ((!pgleichq)&&(eccframe.pset)) 
	    {
	    	g.setColor(Color.black);
	    	g.fillArc(eccframe.px - 3,eccframe.py - 3, 6, 6, 0, 360);
		    //g.setColor(new Color(26,8,143));
		    g.setColor(Color.red);
		    g.fillArc(eccframe.px - 2,eccframe.py - 2, 4, 4, 0, 360);
            if(eccframe.dpy<0)
                g.drawString("P", eccframe.px + 8, eccframe.py-4);
            else
                g.drawString("P", eccframe.px + 8, eccframe.py+13);
	    }
	    
        //Punkt Q
	    if ((!pgleichq)&&(eccframe.qset)) 
	    {
	    	g.setColor(Color.black);
	    	g.fillArc(eccframe.qx - 3,eccframe.qy - 3, 6, 6, 0, 360);
		   	g.setColor(Color.red);
		    g.fillArc(eccframe.qx - 2,eccframe.qy - 2, 4, 4, 0, 360);
		    if(eccframe.np>1)
                if(eccframe.day<0)
                    g.drawString(""+(eccframe.np-1)+"P", eccframe.qx + 8, eccframe.qy-4);
                else
                    g.drawString(""+(eccframe.np-1)+"P", eccframe.qx + 8, eccframe.qy+13);
		    else
                if(eccframe.dqy<0)
                    g.drawString("Q", eccframe.qx + 8, eccframe.qy-4);
                else
                    g.drawString("Q", eccframe.qx + 8, eccframe.qy+13);
	    }
	    
	    if (pgleichq&&eccframe.np==1) 
	    {
	    	g.setColor(Color.black);
	    	g.fillArc(eccframe.qx - 3,eccframe.qy - 3, 6, 6, 0, 360);
		   	g.setColor(Color.red);
		    g.fillArc(eccframe.qx - 2,eccframe.qy - 2, 4, 4, 0, 360);
            if(eccframe.dqy<0)
                g.drawString("P = Q", eccframe.qx + 8, eccframe.qy-4); 
            else
                g.drawString("P = Q", eccframe.qx + 8, eccframe.qy+13);
	    }  
	    
	     if (pgleichq&&eccframe.np>1) 
	    {
	    	g.setColor(Color.black);
	    	g.fillArc(eccframe.qx - 3,eccframe.qy - 3, 6, 6, 0, 360);
		   	g.setColor(Color.red);
		    g.fillArc(eccframe.qx - 2,eccframe.qy - 2, 4, 4, 0, 360);
            if(eccframe.dqy<0)
                g.drawString("P = "+eccframe.np+"P", eccframe.qx + 8, eccframe.qy-4); 
            else
                g.drawString("P = "+eccframe.np+"P", eccframe.qx + 8, eccframe.qy+13);
	
	    } 
	    
	    
    }
    
    public void zeichneLinie(double dax, double day, double dbx, double dby, Color color, Graphics g)
    {
    	double steigung, alpha, dcx, dcy;
    	int ax,ay,bx,by,cx,cy;

    	double verlaengerung=3; // gibt cm an, um die die Gerade über 2 Punkte A und B verlängert wird
		
		if (dax==dbx) steigung=Double.NaN; 
		
		else steigung = (day-dby)/(dax-dbx);
		
		alpha=Math.atan(Math.abs(day-dby)/Math.abs(dax-dbx))*180/Math.PI; // Winkel alpha
		
		dcy=verlaengerung*Math.sin(alpha*Math.PI/180); //Gegenkathete
	
		dcx=verlaengerung*Math.cos(alpha*Math.PI/180);// Ankathete

		if (steigung==0) {dcy=0;dcx=verlaengerung;}
		if (Double.isNaN(steigung)) {dcy=verlaengerung;dcx=0;}
	   	
	   	int ppz=eccframe.pixelProZelle;
    	
       	cx=(int)(dcx*ppz);  // Von Koordinatenpunkt 0,0 ausgehend
       	cy=(int)(dcy*ppz);	// Von Koordinatenpunkt 0,0 ausgehend

		ax=xWertToXPixel(dax);
		ay=yWertToYPixel(day);
		bx=xWertToXPixel(dbx);
		by=yWertToYPixel(dby);

    	g.setColor(color);    	
    	
    	if(ax<bx)
    	{
    		if(steigung >=0)
				g.drawLine(ax-cx,ay+cy,bx+cx,by-cy);
			if(steigung <0)
				g.drawLine(ax-cx,ay-cy,bx+cx,by+cy);
			if (Double.isNaN(steigung)) g.drawLine(ax-cx,ay-cy,bx+cx,by+cy);
		}
		
		if(ax==bx)
    	{
    		if(ay>=by)
				g.drawLine(ax,ay+cy,bx,by-cy);
			else
				g.drawLine(ax,ay-cy,bx,by+cy);
		}
			
		if(ax>bx)
		{
			if(steigung >=0)
				g.drawLine(bx-cx,by+cy,ax+cx,ay-cy);
			else			
				g.drawLine(bx-cx,by-cy,ax+cx,ay+cy);
		}
		
    	
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
			eccframe.ax=0;
			eccframe.ay=0;
			eccframe.aset=false;
			
			DecimalFormat df=new DecimalFormat("0.00");
	        String sx=df.format(eccframe.dpx);
	        String sy=df.format(eccframe.dpy);
	        eccframe.tPanel.LabelP.setText("P= ("+sx+"/"+sy+")");
	        eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelP.getText();
	        if(ECCFrame.log != null) ECCFrame.log.setText(eccframe.LogText);
	        
	        eccframe.tPanel.pGewaehlt();
	    	eccframe.bPanelFr.ButtonP.setEnabled(true);
	    	eccframe.bPanelFr.ButtonDelete.setEnabled(true);
	       	grafikFr.repaint();
		}
		else if(eccframe.pset&&!eccframe.rset&&!eccframe.qset&&eccframe.ax!=0&&!eccframe.rNaN)//&&punktAufKurve(xmouse, ymouse))
		{
			eccframe.qx=eccframe.ax;
			eccframe.qy=eccframe.ay;
			eccframe.dqx=eccframe.dax;
			eccframe.dqy=eccframe.day;
			eccframe.qset=true;
			
			DecimalFormat df=new DecimalFormat("0.00");
	        String sx=df.format(eccframe.dqx);
	        String sy=df.format(eccframe.dqy);
	        eccframe.tPanel.LabelQ.setText("Q= ("+sx+"/"+sy+")");
	        eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelQ.getText();
	        if(ECCFrame.log != null) ECCFrame.log.setText(eccframe.LogText);
	       	eccframe.tPanel.qGewaehlt();
	       	eccframe.bPanelFr.ButtonP.setEnabled(false);
	       	eccframe.bPanelFr.ButtonPQ.setEnabled(true);
	    	eccframe.bPanelFr.ButtonDelete.setEnabled(true);
	       	grafikFr.repaint();
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
    	int height=eccframe.canvasGroesse;
        int xmouse = event.getX();
        int ymouse = event.getY();
//	    int yPixel=yWertToYPixel(xWertToYWert(xPixelToXWert(xmouse)));
//		int y2= height-yPixel;
		boolean unten=false;
	
		if (!eccframe.rset&&!eccframe.rNaN&&punktAufKurve(xmouse, ymouse))
		{
			if(!(eccframe.pset&&eccframe.qset)&&!eccframe.rset)
			{
				if (ymouse<=(height-1)/2) 
					unten=false;
				
				else
					unten=true;

				if(eccframe.day<0)
					grafikFr.repaint(eccframe.ax-3, eccframe.ay-23, 110, 26);
				else
					grafikFr.repaint(eccframe.ax-3, eccframe.ay-3, 100, 20);
		       	
		       	eccframe.ax=xmouse;
				eccframe.dax=xPixelToXWert(xmouse);
				eccframe.day=xWertToYWert(eccframe.dax);
				if(unten)eccframe.day=-eccframe.day;
				eccframe.ay=yWertToYPixel(eccframe.day);
				
				if(eccframe.day<0)
					grafikFr.repaint(eccframe.ax-3, eccframe.ay-23, 110, 26);
				else
					grafikFr.repaint(eccframe.ax-3, eccframe.ay-3, 100, 20);
        		

	      	}
      	}
  		
  	}
  
     
    
//Rechenfunktionen

    //liegt die pixel-koordinate auf dem graph??
    boolean punktAufKurve(int xPixel, int yPixel)
    {
    	double xWert,yWert, yMinus, yPlus;
    	int korrektesYPixel, diffOben,diffUnten;
    	int height=eccframe.canvasGroesse;
    	
		xWert=xPixelToXWert(xPixel);
		yWert=xWertToYWert(xWert);
		
		yMinus=Math.sqrt(Math.pow(xPixelToXWert(xPixel-1),3)+eccframe.a*xPixelToXWert(xPixel-1)+eccframe.b);
		yPlus=Math.sqrt(Math.pow(xPixelToXWert(xPixel+1),3)+eccframe.a*xPixelToXWert(xPixel+1)+eccframe.b);
		
		//die Funktion xWertToYWert macht aus NaN eine 0
		if(yWert==0)
			//ist false, wenn sowohl der Punkt rechts 
			//als auch links vom betrachteten Punkt NaN sind
			if(java.lang.Double.isNaN(yMinus)&&java.lang.Double.isNaN(yPlus))
				return false;

			
			
		korrektesYPixel=yWertToYPixel(yWert);
		
		diffOben=Math.abs(korrektesYPixel-yPixel);
		diffUnten=Math.abs((height-1-korrektesYPixel)-yPixel);
		
		if((diffOben<=3)||(diffUnten<=3))
			return true;
		else
			return false;
    }
    
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   	//Rechenweg IMMER xPixel=>xWert=>yWert=>yPixel
	//alles andere führt zu Rundungsfehlern!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    //konvertiert x-Pixel auf dem Canvas in X-Werte im Koord.System
    double xPixelToXWert(int xPixel)
	{
		int width=eccframe.canvasGroesse;
		int ppz=eccframe.pixelProZelle;
		double x;
		x=((double)xPixel-(width-1)/2)/ppz;
		return x;
	}
	
    //konvertiert y-Pixel auf dem Canvas in Y-Werte im Koord.System
    double yPixelToYWert(int YPixel)
    {
        int height = eccframe.canvasGroesse;
        int ppz=eccframe.pixelProZelle;
    	double y;
    	y=(double)(((height-1)/2)-(double)YPixel)/ppz;
     	return y; 	
    }

    //berechnet die Canvas-x-Pixelkoordinate eines x-Wertes des Graphen
    int xWertToXPixel(double wert)
    {
    	int width=eccframe.canvasGroesse;
    	int ppz=eccframe.pixelProZelle;
    	int xPixel;
    	xPixel=(int)(wert*ppz+(width-1)/2);
    	
    	return xPixel; 	
    }
	
	//berechnet die Canvas-y-Pixelkoordinate eines y-Wertes des Graphen
    int yWertToYPixel(double wert)
    {
    	int height=eccframe.canvasGroesse;
    	int ppz=eccframe.pixelProZelle;
    	int yPixel;
    	yPixel=(int)(height-1-(wert*ppz+(height-1)/2));
    	
    	return yPixel; 	
    }
	
	//berechnet HOCHGENAU genau das, was der Name beschreibt
	double xWertToYWert(double x)
	{
		//berechnen von F(x), nur positiver Wert
    	double y=Math.sqrt(Math.pow(x,3)+eccframe.a*x+eccframe.b);
    	
    	if (java.lang.Double.isNaN(y))
    		return 0;
    	
    	else
    		return y;
    }

}
