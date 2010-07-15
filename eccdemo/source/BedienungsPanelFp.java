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


public class BedienungsPanelFp extends Panel implements AdjustmentListener, ActionListener
{
	private static final long serialVersionUID = 6357778793016876862L;
	protected ECCFrame eccframe;
	protected Scrollbar ScrollbarA;
    protected Scrollbar ScrollbarB;
    protected Scrollbar ScrollbarC;
    protected Label LabelA;
    protected Label LabelB;
    protected Label LabelC;
	protected Button ButtonP;
	protected Button ButtonPQ;
	protected Button ButtonDelete;
	protected Button ButtonLog;
	protected Button ButtonExit;
	protected DecimalFormat df;
	protected String a_string;
	protected String b_string;

        /** Creates a new instance of BedienungsPanelFp */
    public BedienungsPanelFp(ECCFrame eccframe) 
    {		
        this.eccframe=eccframe;	
        df=new DecimalFormat("0");
		ScrollbarA = new Scrollbar(Scrollbar.HORIZONTAL, eccframe.a_scroll, 1,eccframe.amin,eccframe.amax+1);
		ScrollbarB = new Scrollbar(Scrollbar.HORIZONTAL, eccframe.b_scroll, 1, eccframe.bmin,eccframe.bmax+1);
		ScrollbarC = new Scrollbar(Scrollbar.HORIZONTAL, eccframe.pIndex, 1, 0,24);        
        ScrollbarA.addAdjustmentListener(this);
        ScrollbarB.addAdjustmentListener(this);
        ScrollbarC.addAdjustmentListener(this);  
              
		a_string=df.format(eccframe.a);
		b_string=df.format(eccframe.b);
    	LabelA = new Label("a = "+ a_string);
    	LabelB = new Label("b = "+ b_string);
    	LabelC = new Label("p = "+ eccframe.p[eccframe.pIndex]);  
    	
    	Color lila=new Color(148,3,148);
		Font fontgross = new Font("Times New Roman",1,12);
		LabelA.setForeground(Color.red);
		LabelA.setFont(fontgross);
		LabelB.setForeground(lila);
     	LabelB.setFont(fontgross);  
     	LabelC.setFont(fontgross); 

    	     
        ButtonP = new Button(" "+(eccframe.np+1)+" * P ");
        ButtonP.setEnabled(false);
        ButtonP.addActionListener(this);
        ButtonPQ = new Button(" P + Q ");
        ButtonPQ.setEnabled(false);
        ButtonPQ.addActionListener(this);
        ButtonDelete = new Button(eccframe.text.buttonDelete);
        ButtonDelete.setEnabled(false);
        ButtonDelete.addActionListener(this);
        ButtonLog = new Button(eccframe.text.buttonLog);
        ButtonLog.setEnabled(true);
        ButtonLog.addActionListener(this);
        ButtonExit = new Button(eccframe.text.buttonExit);
        ButtonExit.setEnabled(true);
        ButtonExit.addActionListener(this);
        
        //Gr??e und Ausrichtung anpassen
        LabelA.setAlignment(Label.RIGHT);
        ScrollbarA.setPreferredSize(new Dimension(100,15));
        LabelB.setAlignment(Label.RIGHT);
        ScrollbarB.setPreferredSize(new Dimension(100,15));
        LabelC.setAlignment(Label.RIGHT);
        ScrollbarC.setPreferredSize(new Dimension(100,15));
                
        add(LabelA);
        add(ScrollbarA);
    	add(LabelB);
        add(ScrollbarB);
        add(LabelC);
        add(ScrollbarC);
        add(ButtonP);
        add(ButtonPQ);
        add(ButtonDelete);
        add(ButtonLog);
        add(ButtonExit);
        
        startLogDatei();
    }


        public void adjustmentValueChanged(AdjustmentEvent adjustmentevent)
    {
        Object obj = adjustmentevent.getSource();
        if(obj == ScrollbarA)
        {
            eccframe.a= adjustmentevent.getValue();
            
            a_string=df.format(eccframe.a);
            LabelA.setText("a = " + a_string);
            ButtonDeleteClicked();
            startLogDatei();
        } 
        else
        if(obj == ScrollbarB)
        {
            eccframe.b= adjustmentevent.getValue();
            
            b_string=df.format(eccframe.b);
            LabelB.setText("b = " + b_string);
            ButtonDeleteClicked();
            startLogDatei();
        }
  
          else
        if(obj == ScrollbarC)
        {
            eccframe.pIndex= adjustmentevent.getValue();
            LabelC.setText("p = " + eccframe.p[eccframe.pIndex]);
            eccframe.maxwert=eccframe.p[eccframe.pIndex];
            ButtonDeleteClicked();
            startLogDatei();
         }
    }
 
     public void actionPerformed(ActionEvent actionevent)
    {
        Object obj = actionevent.getSource();
        
        if(obj == ButtonDelete) 
        { 
        // Funktion Punkte l?schen
        ButtonDeleteClicked();
        }
        else
        if(obj == ButtonExit){
        System.exit(0);
        }
        else
        if(obj == ButtonP) 
        {
        

        if(eccframe.rNaN)
            {
			eccframe.rset=true;
			eccframe.rNaN=false;
	        eccframe.rx=eccframe.px;
	        eccframe.ry=eccframe.py;
	        eccframe.drx=eccframe.dpx;
	        eccframe.dry=eccframe.dpy;	
	        eccframe.qset=false;

	        
	        
	        
	        eccframe.np++;
   			eccframe.bPanelFp.ButtonP.setLabel(" "+(eccframe.np+1)+" * P ");
   			DecimalFormat df=new DecimalFormat("0");
   			eccframe.tPanel.LabelQ.setText(""+(eccframe.np-1)+"P = O");
//   			eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelQ.getText();
//   			if(log != null)log.setText(eccframe.LogText);
   			String sx=df.format(eccframe.drx);
	        String sy=df.format(eccframe.dry);   			
   			eccframe.tPanel.LabelR.setText("R = "+(eccframe.np-1)+"P + P = O + P = ("+sx+"/"+sy+")");
	       	eccframe.LogText=eccframe.LogText+"\n"+eccframe.np+"P = ("+sx+"/"+sy+")";
	       	if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
	        eccframe.tPanel.frAus2P();
	        eccframe.grafikFp.repaint();
	        }
        // Funktion Punkte addieren  	
	     	else ButtonAddierenPPClicked();
        }
         else
        if(obj == ButtonPQ) 
        {
        // Funktion Punkte addieren  	
		ButtonAddierenPQClicked();
        } 
        
        else
        if(obj == ButtonLog) 
        {
        // Funktion Log-Datei

 		ECCFrame.log = new LogDatei(eccframe, eccframe.LogText);
 		 		// Window beenden
       
        if (ECCFrame.log.exit==true) {ECCFrame.log.setVisible(false);ECCFrame.log.dispose();}
 
        }        
        
        
    }
    
    
        public void startLogDatei() {
    
        eccframe.LogText=eccframe.text.logFpNumberSpace+eccframe.p[eccframe.pIndex]+" -----\n\n";
        eccframe.LogText=eccframe.LogText+eccframe.text.logCurve;
        eccframe.LogText=eccframe.LogText+"y^2 = x^3"; 
        
        if(eccframe.a < 0) eccframe.LogText = eccframe.LogText+" - "+Math.abs(eccframe.a) + "x";
        else if(eccframe.a > 0) eccframe.LogText = eccframe.LogText +" + "+eccframe.a+"x";
       
        if(eccframe.b < 0) eccframe.LogText = eccframe.LogText+" - "+Math.abs(eccframe.b);
        else if(eccframe.b > 0) eccframe.LogText = eccframe.LogText + " + " + eccframe.b;
        
 		eccframe.LogText=eccframe.LogText+"\n";
 		if(eccframe.punkt != null && eccframe.punkt.length != 0){
 			eccframe.LogText += "\n"+ Texte.pointsText + " ";
 			for(int i=0; i<eccframe.zaehlerpunkte; i++){
 				eccframe.LogText += "(" + eccframe.punkt[i][0] + "|" + eccframe.punkt[i][1] + ")";
 				if(i < eccframe.zaehlerpunkte-1)
 					eccframe.LogText += ", ";
 			}
 			eccframe.LogText=eccframe.LogText+"\n";
 		}
 		
 		
 		if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
 		}
    
    
    public void ButtonDeleteClicked() 
    {
    	
    	eccframe.pset=false;
        eccframe.qset=false;
        eccframe.rset=false;
        eccframe.rNaN=false;
        eccframe.ax=0;
        eccframe.ay=0;
        eccframe.np=1;
        eccframe.bPanelFp.ButtonP.setLabel(" "+(eccframe.np+1)+" * P ");
       	eccframe.bPanelFp.ButtonP.setEnabled(false);
       	eccframe.bPanelFp.ButtonPQ.setEnabled(false);
    	eccframe.bPanelFp.ButtonDelete.setEnabled(false);
    	eccframe.tPanel.resetPanel();
    	eccframe.LogText="";
    	startLogDatei();
    	eccframe.grafikFp.repaint();    	
    
    }
   public void ButtonAddierenPQClicked() 
   {
		eccframe.bPanelFp.ButtonPQ.setEnabled(false);
        
        double lambda;
       
        if (eccframe.dpx == eccframe.dqx && eccframe.dpy == berechneModular(-eccframe.dqy)) 
        
        {
        	
		// Punkt im Unendlichen
				eccframe.rset=false;
				eccframe.rNaN=true;
        		eccframe.rx=0;
        		eccframe.ry=0;
        		eccframe.drx=0;
        		eccframe.dry=0;
        		eccframe.tPanel.frAusPQNaN();
        		String bez="";
        		if (eccframe.np-1==0)
        			bez="";
        			else bez=""+(eccframe.np-1);
        		
        		if (eccframe.np>1){
        			eccframe.tPanel.LabelR.setText("R = "+bez+"P + P = O");
        			eccframe.LogText=eccframe.LogText+"\n"+eccframe.np+"P = O";
        			if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
        		}
				else {
					eccframe.tPanel.LabelR.setText("R = P + Q = O");
					eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelR.getText();
					if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
				}
				 
				eccframe.grafikFp.repaint();
				return;}
				
		if(eccframe.dpx == eccframe.dqx && eccframe.dpy == eccframe.dqy)
			lambda = (3 * Math.pow(eccframe.dpx, 2) + eccframe.a) * berechneInverse(2 * eccframe.dpy)%eccframe.p[eccframe.pIndex];
			else lambda = berechneModular(eccframe.dpy - eccframe.dqy) * berechneInverse(berechneModular(eccframe.dpx - eccframe.dqx))%eccframe.p[eccframe.pIndex];
       
        eccframe.drx=berechneModular(Math.pow(lambda,2) - eccframe.dpx - eccframe.dqx)%eccframe.p[eccframe.pIndex];
        eccframe.rset=true;
        eccframe.dry=berechneModular(lambda * berechneModular(eccframe.dpx - eccframe.drx) - eccframe.dpy)%eccframe.p[eccframe.pIndex];
	    eccframe.rx=eccframe.grafikFp.xWertToXPixel(eccframe.drx);
	    eccframe.ry=eccframe.grafikFp.yWertToYPixel(eccframe.dry);
      
        DecimalFormat df=new DecimalFormat("0");
        String sx=df.format(eccframe.drx);
        String sy=df.format(eccframe.dry);
        if(eccframe.np==1)
        	{
        		eccframe.tPanel.LabelR.setText("R = ("+sx+"/"+sy+")"); 
        		eccframe.tPanel.frAusPplusQ();
        		eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelR.getText();
        		if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
        	}
        else
        {
        	eccframe.tPanel.LabelR.setText("R = "+(eccframe.np-1)+"P + P = ("+sx+"/"+sy+")");
        	eccframe.LogText=eccframe.LogText+"\n"+eccframe.np+"P = ("+sx+"/"+sy+")";
        	if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
        	eccframe.tPanel.frAus2P();
        }
		eccframe.grafikFp.repaint();
	}
	
	public int berechneModular(double ii) // in positive Zahl umrechnen
    {									
    	int i=(int)ii;
        
        while(i<0) i = i+ eccframe.p[eccframe.pIndex];	

        return i;
    }
    
	
   public int berechneInverse(double ii) // Erweiterter Euklidischer Algorithmus
    {
    int m=(int)ii;
    int n = eccframe.p[eccframe.pIndex];
	int s = 1;
	int t = 0;
	int u0 = 0;
	int v0 = 1;
	while(n!=0) {
	
	int r = m % n;
	int q = m / n; 
	m=n;n=r;int u1=s - q * u0;int v1=t - q * v0;
	s = u0;t = v0;u0 = u1;v0 = v1;
	}
	return s;

    }	

   public void ButtonAddierenPPClicked() 
   {
   		DecimalFormat df=new DecimalFormat("0");
   	  		
   	  	
   		if(eccframe.np>1)
   		{
   			eccframe.qx=eccframe.rx;
   			eccframe.qy=eccframe.ry;
   			eccframe.dqx=eccframe.drx;
   			eccframe.dqy=eccframe.dry;
   			eccframe.qset=true;
   			eccframe.rset=false;
   			eccframe.np++;
   			eccframe.bPanelFp.ButtonP.setLabel(" "+(eccframe.np+1)+" * P ");
   			String sx=df.format(eccframe.dqx);
	        String sy=df.format(eccframe.dqy);
   			eccframe.tPanel.LabelQ.setText(""+(eccframe.np-1)+"P = ("+sx+"/"+sy+")");
//   	   		eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelQ.getText();
//   			if(log != null)log.setText(eccframe.LogText);
   			ButtonAddierenPQClicked();
   		}
           
       
		if(eccframe.dpy == 0) 
		{
				eccframe.rset=true;
				eccframe.rNaN=true;
        		eccframe.rx=0;
        		eccframe.ry=0;
        		eccframe.drx=0;
        		eccframe.dry=0;
        		eccframe.tPanel.frAus2PNaN();
        		String bez="";
        		if (eccframe.np-1==0)
        			bez="";
        			else bez=""+(eccframe.np-1);
        		
        		eccframe.tPanel.LabelR.setText("R = "+bez+"P + P = O");
        	   	eccframe.LogText=eccframe.LogText+"\n"+eccframe.np+"P = O";
        	   	if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
        		if (eccframe.np==1) eccframe.np++;
        		eccframe.bPanelFp.ButtonP.setLabel(" "+(eccframe.np+1)+" * P "); 
				eccframe.grafikFp.repaint();
				
				return;}
		
		if(eccframe.np==1)
		{	
			
			double lambda = ((3 * Math.pow(eccframe.dpx, 2) + eccframe.a) * berechneInverse(2 * eccframe.dpy))%eccframe.p[eccframe.pIndex];
			eccframe.drx=berechneModular(Math.pow(lambda,2) - eccframe.dpx - eccframe.dpx)%eccframe.p[eccframe.pIndex];
	        eccframe.dry=berechneModular(lambda * berechneModular(eccframe.dpx - eccframe.drx) - eccframe.dpy)%eccframe.p[eccframe.pIndex];
	        eccframe.rx=eccframe.grafikFp.xWertToXPixel(eccframe.drx);
	        eccframe.ry=eccframe.grafikFp.yWertToYPixel(eccframe.dry);
	        eccframe.rset=true;
	        eccframe.rNaN=false;
	        eccframe.np++;
	        eccframe.bPanelFp.ButtonP.setLabel(" "+(eccframe.np+1)+" * P ");
	        String sx=df.format(eccframe.drx);
	        String sy=df.format(eccframe.dry);
	        eccframe.tPanel.LabelR.setText("2P = ("+sx+"/"+sy+")");
	        eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelR.getText();
	        if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
	        eccframe.tPanel.frAus2P();
			eccframe.grafikFp.repaint();
		}
	}
	
}
