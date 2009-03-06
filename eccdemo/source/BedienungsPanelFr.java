package eccdemo;

import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Label;
import java.awt.Panel;
import java.awt.Scrollbar;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.AdjustmentEvent;
import java.awt.event.AdjustmentListener;
import java.text.DecimalFormat;


public class BedienungsPanelFr extends Panel implements AdjustmentListener, ActionListener
{
    

	private static final long serialVersionUID = -4151351382513485560L;
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
	protected DecimalFormat df;
	protected String a_string;
	protected String b_string;
        /** Creates a new instance of BedienungsPanelFr */
    public BedienungsPanelFr(ECCFrame eccframe) 
    {		
    	
        this.eccframe=eccframe;	
        
       
		if(eccframe.nks==10)
			df=new DecimalFormat("0.0");
		if(eccframe.nks==100)
			df=new DecimalFormat("0.00");
        
		ScrollbarA = new Scrollbar(Scrollbar.HORIZONTAL, eccframe.a_scroll, 1,eccframe.amin*eccframe.nks,(eccframe.amax+1)*eccframe.nks);
		ScrollbarB = new Scrollbar(Scrollbar.HORIZONTAL, eccframe.b_scroll, 1, eccframe.bmin*eccframe.nks,(eccframe.bmax+1)*eccframe.nks);
        ScrollbarC = new Scrollbar(Scrollbar.HORIZONTAL, eccframe.cIndex, 1, 0,10); 
        ScrollbarA.addAdjustmentListener(this);
        ScrollbarB.addAdjustmentListener(this);
        ScrollbarC.addAdjustmentListener(this);     
		a_string=df.format(eccframe.a);
		b_string=df.format(eccframe.b);
    	LabelA = new Label("a = "+ a_string);
    	LabelB = new Label("b = "+ b_string);
        LabelC = new Label("Zoom:");
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
        
        //Größe und Ausrichtung anpassen
        LabelA.setAlignment(Label.RIGHT);
        ScrollbarA.setSize(new Dimension(90,20));
        LabelB.setAlignment(Label.RIGHT);
        ScrollbarB.setSize(new Dimension(90,20));
        LabelC.setAlignment(Label.RIGHT);
        ScrollbarC.setSize(new Dimension(90,20));
        ButtonP.setSize(new Dimension(90,20));
        ButtonPQ.setSize(new Dimension(90,20));
        ButtonDelete.setSize(new Dimension(90,20));
        ButtonLog.setSize(new Dimension(90,20));        
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
    
    	startLogDatei();
    }


        public void adjustmentValueChanged(AdjustmentEvent adjustmentevent)
    {
        Object obj = adjustmentevent.getSource();
			
        if(obj == ScrollbarA)
        {
        	eccframe.a_scroll= adjustmentevent.getValue();
            eccframe.a=((double)eccframe.a_scroll)/eccframe.nks;
			
			
        	
        	a_string=eccframe.bPanelFr.df.format(eccframe.a);
			
            LabelA.setText("a = " + a_string);
            ButtonDeleteClicked();
            
            startLogDatei();
 
        } 
        else
        if(obj == ScrollbarB)
        {
        	eccframe.b_scroll= adjustmentevent.getValue();
            eccframe.b=((double)eccframe.b_scroll)/eccframe.nks;
			
			String b_string=eccframe.bPanelFr.df.format(eccframe.b);
			
            LabelB.setText("b = " + b_string);
            ButtonDeleteClicked();

            startLogDatei();
 		
        }
        
        
        else
        if(obj == ScrollbarC)
        {
            eccframe.cIndex= adjustmentevent.getValue();
            LabelC.setText("Zoom :");
            
            double dummydpx=eccframe.dpx;
            double dummydpy=eccframe.dpy;

            double dummydqx=eccframe.dqx;
            double dummydqy=eccframe.dqy;

            double dummydrx=eccframe.drx;
            double dummydry=eccframe.dry;            
                        
            eccframe.maxwert=eccframe.c[eccframe.cIndex];
            eccframe.pixelProZelle=264/eccframe.maxwert;

            eccframe.px=eccframe.grafikFr.xWertToXPixel(dummydpx); 
            eccframe.py=eccframe.grafikFr.yWertToYPixel(dummydpy);  
            eccframe.qx=eccframe.grafikFr.xWertToXPixel(dummydqx); 
            eccframe.qy=eccframe.grafikFr.yWertToYPixel(dummydqy);  
            eccframe.rx=eccframe.grafikFr.xWertToXPixel(dummydrx); 
            eccframe.ry=eccframe.grafikFr.yWertToYPixel(dummydry);  
            eccframe.grafikFr.repaint();  
         }
    }
 
     public void actionPerformed(ActionEvent actionevent)
    {
        Object obj = actionevent.getSource();
        
        if(obj == ButtonDelete) 
        { 
        // Funktion Punkte löschen
        ButtonDeleteClicked();
        }
        else
        if(obj == ButtonP) 
        {
        // Funktion Punkte addieren  	
		ButtonAddierenPPClicked();
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
    
        eccframe.LogText=eccframe.text.logFrNumberSpace;
        eccframe.LogText=eccframe.LogText+eccframe.text.logCurve;
        eccframe.LogText=eccframe.LogText+"y^2 = x^3"; 
        
        if(eccframe.a < 0) eccframe.LogText = eccframe.LogText+" - "+Math.abs(eccframe.a) + "x";
        else if(eccframe.a > 0) eccframe.LogText = eccframe.LogText +" + "+eccframe.a+"x";
       
        if(eccframe.b < 0) eccframe.LogText = eccframe.LogText+" - "+Math.abs(eccframe.b);
        else if(eccframe.b > 0) eccframe.LogText = eccframe.LogText + " + " + eccframe.b;
 
        eccframe.LogText=eccframe.LogText+"\n";		
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
        eccframe.bPanelFr.ButtonP.setLabel(" "+(eccframe.np+1)+" * P ");
       	eccframe.bPanelFr.ButtonP.setEnabled(false);
       	eccframe.bPanelFr.ButtonPQ.setEnabled(false);
    	eccframe.bPanelFr.ButtonDelete.setEnabled(false);
    	eccframe.tPanel.resetPanel();
    	eccframe.LogText="";
    	startLogDatei();
    	eccframe.grafikFr.repaint();
    	    	
    
    }
   public void ButtonAddierenPQClicked() 
   {
		eccframe.bPanelFr.ButtonPQ.setEnabled(false);
        
        double lambda;
       
        if (eccframe.dpx == eccframe.dqx && eccframe.dpy == eccframe.dqy) // P = Q ?
        
        {
        	
				if(eccframe.dpy == 0) 
				{// Punkt im Unendlichen
				eccframe.rset=false;
				eccframe.rNaN=true;
        		eccframe.rx=0;
        		eccframe.ry=0;
        		eccframe.drx=0;
        		eccframe.dry=0;
        		eccframe.tPanel.rAusPQNaN();
        		eccframe.tPanel.LabelR.setText("R = O");
        		eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelR.getText(); 
        		if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
				eccframe.grafikFr.repaint();
				return;}
			
				lambda = (3 * Math.pow(eccframe.dpx, 2) + eccframe.a) / (2 * eccframe.dpy);
				eccframe.drx=Math.pow(lambda,2) - eccframe.dpx - eccframe.dpx;

        }
       	else // P != Q
       	{ 
         		if(eccframe.dpx - eccframe.dqx == 0)
                {// Punkt im Unendlichen
                eccframe.rset=false;
                eccframe.rNaN=true;
        		eccframe.rx=0;
        		eccframe.ry=0;
        		eccframe.tPanel.rAusPQNaN();
        		eccframe.tPanel.LabelR.setText("R = O"); 
        		eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelR.getText();
        		if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
				eccframe.grafikFr.repaint();
				return;}
				
                lambda = (eccframe.dpy - eccframe.dqy) / (eccframe.dpx - eccframe.dqx);
            	eccframe.drx=Math.pow(lambda,2) - eccframe.dpx - eccframe.dqx;
        } 
        
        eccframe.rset=true;

        eccframe.dry=lambda * (eccframe.dpx - eccframe.drx) - eccframe.dpy;
        eccframe.rx=eccframe.grafikFr.xWertToXPixel(eccframe.drx);
        eccframe.ry=eccframe.grafikFr.yWertToYPixel(eccframe.dry);
        DecimalFormat df=new DecimalFormat("0.00");
        String sx=df.format(eccframe.drx);
        String sy=df.format(eccframe.dry);
        if(eccframe.np==1)
        	{
        		eccframe.tPanel.LabelR.setText("R = ("+sx+"/"+sy+")");
        		eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelR.getText();
        		if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
        		eccframe.tPanel.rAusPplusQ();
        	}
        else
        {
        	eccframe.tPanel.LabelR.setText("R = "+(eccframe.np-1)+"P + P = ("+sx+"/"+sy+")");
        	eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelR.getText();
        	if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
        	eccframe.tPanel.rAus2P();
        }
		eccframe.grafikFr.repaint();
	}
	
   public void ButtonAddierenPPClicked() 
   {
   		DecimalFormat df=new DecimalFormat("0.00");
   	  		
   	  	
   		if(eccframe.np>1)
   		{
   			eccframe.qx=eccframe.rx;
   			eccframe.qy=eccframe.ry;
   			eccframe.dqx=eccframe.drx;
   			eccframe.dqy=eccframe.dry;
   			eccframe.qset=true;
   			eccframe.rset=false;
   			eccframe.np++;
   			eccframe.bPanelFr.ButtonP.setLabel(" "+(eccframe.np+1)+" * P ");
   			String sx=df.format(eccframe.dqx);
	        String sy=df.format(eccframe.dqy);
   			eccframe.tPanel.LabelQ.setText(""+(eccframe.np-1)+"P = ("+sx+"/"+sy+")");
   			eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelQ.getText();
   			if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
   			ButtonAddierenPQClicked();
   			
   		}
           
       
		if(eccframe.dpy == 0) 
		{
			// Punkt im Unendlichen
			eccframe.rset=false;
			eccframe.rNaN=true;
	        eccframe.rx=0;
	        eccframe.ry=0;
	        eccframe.drx=0;
	        eccframe.dry=0;
	        eccframe.np=1;
//	        String sx=df.format(eccframe.drx);
//	        String sy=df.format(eccframe.dry);
	        eccframe.tPanel.LabelR.setText("R = O");
	        eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelR.getText();
	        if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
	        eccframe.tPanel.rAus2PNaN();
			eccframe.grafikFr.repaint();
			return;
		}
		
		if(eccframe.np==1)
		{	
			double lambda = (3 * Math.pow(eccframe.dpx, 2) + eccframe.a) / (2 * eccframe.dpy);
			eccframe.drx=Math.pow(lambda,2) - eccframe.dpx - eccframe.dpx;
	        eccframe.dry=lambda * (eccframe.dpx - eccframe.drx) - eccframe.dpy;
	        eccframe.rx=eccframe.grafikFr.xWertToXPixel(eccframe.drx);
	        eccframe.ry=eccframe.grafikFr.yWertToYPixel(eccframe.dry);
	        eccframe.rset=true;
	        eccframe.rNaN=false;
	        eccframe.np++;
	        eccframe.bPanelFr.ButtonP.setLabel(" "+(eccframe.np+1)+" * P ");
	        String sx=df.format(eccframe.drx);
	        String sy=df.format(eccframe.dry);
	        eccframe.tPanel.LabelR.setText("R = 2P = ("+sx+"/"+sy+")");
	        eccframe.LogText=eccframe.LogText+"\n"+eccframe.tPanel.LabelR.getText();
	        if(ECCFrame.log != null)ECCFrame.log.setText(eccframe.LogText);
	        eccframe.tPanel.rAus2P();
			eccframe.grafikFr.repaint();
		}
	}
	
}