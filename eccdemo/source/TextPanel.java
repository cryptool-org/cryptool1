package eccdemo;

import java.awt.*;
import java.awt.event.*;


class TextPanel extends Panel implements ItemListener, ActionListener
{
	private static final long serialVersionUID = 1962013459858047635L;
	protected ECCFrame eccframe;
	protected Label LabelRaum;
	protected CheckboxGroup zahlenraum =new CheckboxGroup();
	protected Checkbox fr;
	protected Checkbox fp;
	protected Label LabelTitle;
	protected Label Line;
	protected Label LabelB;
	protected Label LabelP;
	protected Label LabelQ;	
	protected Label LabelR;
	protected Label Text1;
	protected Label Text2;
	protected Label Text3;
	protected Label Text4;
	protected Label Text5;
	protected Label Text6;
	protected Label Text7;
	protected Label Text8;
	protected Label Text9;
	protected Label Text10;
	protected Label Text11;
	protected Label Text12;
	protected Label Text13;
	protected Label Text14;
	protected Label Text15;
	protected Label Text16;
	
	Font fontgross = new Font("Times New Roman",1,12);
	Font fontfett = new Font("Times New Roman",Font.BOLD,12);

	Color rLila=new Color(255,0,255);
	Color pBlau= new Color(26,8,143);
	
	protected GridBagLayout gl;
	protected GridBagConstraints gc;
	
	public TextPanel(ECCFrame eccframe)
	{
		this.eccframe=eccframe;	
		// Layout wird eingerichtet
        gl=new GridBagLayout();
        setLayout(gl);
        gc = new GridBagConstraints();
        gc.gridheight=30;
        gc.gridwidth=4;
        gc.fill=GridBagConstraints.HORIZONTAL;
        gc.insets=new Insets(0,0,0,150);
              
        gc.insets=new Insets(0,0,0,0);
        
        LabelRaum=new Label(eccframe.text.labelSpace);
        LabelRaum.setFont(fontgross);
        gc.gridx=0;
        gc.gridy=1;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(LabelRaum,gc);
        add(LabelRaum);
        
        
        if(ECCFrame.raum==0)
        	fr=new Checkbox (eccframe.text.buttonFr,zahlenraum,true);
        else
        	fr=new Checkbox (eccframe.text.buttonFr,zahlenraum,false);
        fr.addItemListener(this);
        gc.gridx=0;
        gc.gridy=2;
        gc.gridheight=1;
        gc.gridwidth=2;	        
        gc.weightx=0.5;
        gl.setConstraints(fr,gc);
        add(fr);
        
        if(ECCFrame.raum==1)
        	fp=new Checkbox (eccframe.text.buttonFp,zahlenraum,true);
        else
        	fp=new Checkbox (eccframe.text.buttonFp,zahlenraum,false);
        fp.addItemListener(this);
        gc.gridx=0;
        gc.gridy=3;
        gc.gridheight=1;
        gc.gridwidth=2;	        
        gl.setConstraints(fp,gc);
        add(fp);
        
        LabelTitle=new Label(eccframe.text.titel);
        LabelTitle.setFont(fontfett);
        LabelTitle.setForeground(Color.black);
        gc.gridx=0;
        gc.gridy=4;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(LabelTitle,gc);
        add(LabelTitle);
        
        //##################################
        Text1 = new Label(eccframe.text.text1);
        Text1.setForeground(Color.black);
        gc.gridx=0;
        gc.gridy=5;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text1,gc);
        add(Text1);
        
        Text2 = new Label(eccframe.text.text2);
        gc.gridx=0;
        gc.gridy=6;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text2,gc);
        add(Text2);
        
        Text3 = new Label(eccframe.text.text3);
        gc.gridx=0;
        gc.gridy=7;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text3,gc);
        add(Text3);
        
        Text4 = new Label(eccframe.text.text4);
        gc.gridx=0;
        gc.gridy=8;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text4,gc);
        add(Text4);
        
        Text5 = new Label(eccframe.text.text5);
        gc.gridx=0;
        gc.gridy=9;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text5,gc);
        add(Text5);
        
        Text6 = new Label(eccframe.text.text6);
        gc.gridx=0;
        gc.gridy=10;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text6,gc);
        add(Text6);
        
        Text7 = new Label(eccframe.text.text7);
        //Text7.setForeground(Color.blue);
        gc.gridx=0;
        gc.gridy=11;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text7,gc);
        add(Text7);
        
        Text8 = new Label(eccframe.text.text8);
        //Text8.setForeground(Color.blue);
        gc.gridx=0;
        gc.gridy=12;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text8,gc);
        add(Text8);
        
        Text9 = new Label("_______________________________________");
        Text9.setForeground(Color.black);
        Text9.setFont(fontfett);
        gc.gridx=0;
        gc.gridy=13;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text9,gc);
        add(Text9);
        
        Text10 = new Label(eccframe.text.text10);
        Text10.setForeground(Color.blue);
        gc.gridx=0;
        gc.gridy=14;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text10,gc);
        add(Text10);
        
        Text11 = new Label(eccframe.text.text11);
        Text11.setForeground(Color.blue);
        gc.gridx=0;
        gc.gridy=15;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text11,gc);
        add(Text11);
        
        Text12 = new Label(eccframe.text.text12);
        Text12.setForeground(Color.blue);
        gc.gridx=0;
        gc.gridy=16;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text12,gc);
        add(Text12);
        
        Text13 = new Label(eccframe.text.text13);
        Text13.setForeground(Color.blue);
        gc.gridx=0;
        gc.gridy=17;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text13,gc);
        add(Text13);
        
        Text14 = new Label(eccframe.text.text14);
        Text14.setForeground(Color.blue);
        gc.gridx=0;
        gc.gridy=18;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text14,gc);
        add(Text14);
        
        Text15 = new Label(eccframe.text.text15);
        Text15.setForeground(Color.blue);
        gc.gridx=0;
        gc.gridy=19;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text15,gc);
        add(Text15);
        
        Text16 = new Label(eccframe.text.text16);
        Text16.setForeground(Color.blue);
        gc.gridx=0;
        gc.gridy=20;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(Text16,gc);
        add(Text16);
        
        //#######################################
        
        Line = new Label("_______________________________________");
        Line.setForeground(Color.black);
        Line.setFont(fontfett);
        gc.gridx=0;
        gc.gridy=21;
        gc.gridheight=1;
        gc.gridwidth=4;	     
        gl.setConstraints(Line,gc);
        add(Line);
        
        LabelP = new Label();
        LabelP.setForeground(Color.red);
        LabelP.setFont(fontfett);
        gc.gridx=0;
        gc.gridy=22;
        gc.gridheight=1;
        gc.gridwidth=4;	     
        gl.setConstraints(LabelP,gc);
        add(LabelP);
        
        LabelQ = new Label();
        LabelQ.setForeground(Color.red);
        LabelQ.setFont(fontfett);
        gc.gridx=0;
        gc.gridy=23;
        gc.gridheight=1;
        gc.gridwidth=4;       
        gl.setConstraints(LabelQ,gc);
        add(LabelQ);
        
        LabelR = new Label();
        LabelR.setForeground(rLila);
        LabelR.setFont(fontfett);
        gc.gridx=0;
        gc.gridy=24;
        gc.gridheight=1;
        gc.gridwidth=4;	        
        gl.setConstraints(LabelR,gc);
        add(LabelR);

	}
	
	protected void resetPanel()
	{
		Text10.setText(eccframe.text.text10);
		Text11.setText(eccframe.text.text11);
		Text12.setText(eccframe.text.text12);
		Text13.setText(eccframe.text.text13);
		Text14.setText(eccframe.text.text14);
		Text15.setText(eccframe.text.text15);
		Text16.setText(eccframe.text.text16);

		LabelP.setText("");
		LabelQ.setText("");
		LabelR.setText("");
	}
	
	protected void pGewaehlt()
	{
		Text10.setText(eccframe.text.p1);
		Text11.setText(eccframe.text.p2);
		Text12.setText(eccframe.text.p3);
		Text13.setText(eccframe.text.p4);		
		Text14.setText("");
		Text15.setText("");
		Text16.setText("");
	}
	
	protected void qGewaehlt()
	{
		Text10.setText(eccframe.text.q1);
		Text11.setText(eccframe.text.q2);
		Text12.setText(eccframe.text.q3);
		Text13.setText("");
		Text14.setText("");
		Text15.setText("");
		Text16.setText("");
	}
	
	protected void rAus2P()
	{
		Text10.setText(eccframe.text.rp1);
		Text11.setText(eccframe.text.rp2);
		Text12.setText(eccframe.text.rp3);
		Text13.setText(eccframe.text.rp4);
		Text14.setText(eccframe.text.rp5);
		Text15.setText(eccframe.text.rp6);
		Text16.setText("");

	}
	
	protected void rAusPplusQ()
	{
		Text10.setText(eccframe.text.rpq1);
		Text11.setText(eccframe.text.rpq2);
		Text12.setText(eccframe.text.rpq3);
		Text13.setText(eccframe.text.rpq4);
		Text14.setText("");
		Text15.setText("");
		Text16.setText("");

	}
	
	protected void rAus2PNaN()
	{
		Text10.setText(eccframe.text.rAus2PNaN1);
		Text11.setText(eccframe.text.rAus2PNaN2);
		Text12.setText(eccframe.text.rAus2PNaN3);
		Text13.setText("");
		Text14.setText("");
		Text15.setText("");
		Text16.setText("");

	}
	
	protected void rAusPQNaN()
	{
		Text10.setText(eccframe.text.rAusPQNaN1);
		Text11.setText(eccframe.text.rAusPQNaN2);
		Text12.setText(eccframe.text.rAusPQNaN3);
		Text13.setText("");
		Text14.setText("");
		Text15.setText("");
		Text16.setText("");

	}
	
	//Fp
	protected void frAus2P()
	{
		Text10.setText(eccframe.text.frp1);
		Text11.setText(eccframe.text.frp2);
		Text12.setText(eccframe.text.frp3);
		Text13.setText(eccframe.text.frp4);
		Text14.setText("");
		Text15.setText(eccframe.text.frp5);
		Text16.setText(eccframe.text.frp6);
	}
	
	protected void frAusPplusQ()
	{
		Text10.setText(eccframe.text.frpq1);
		Text11.setText(eccframe.text.frpq2);
		Text12.setText("");
		Text13.setText(eccframe.text.frpq3);
		Text14.setText(eccframe.text.frpq4);
		Text15.setText("");
		Text16.setText("");

	}
	
	protected void frAus2PNaN()
	{
		Text10.setText(eccframe.text.frAus2PNaN1);
		Text11.setText(eccframe.text.frAus2PNaN2);
		Text12.setText(eccframe.text.frAus2PNaN3);
		Text13.setText("");
		Text14.setText("");
		Text15.setText("");
		Text16.setText("");

	}
	
	protected void frAusPQNaN()
	{
		Text10.setText(eccframe.text.frAusPQNaN1);
		Text11.setText(eccframe.text.frAusPQNaN2);
		Text12.setText(eccframe.text.frAusPQNaN3);
		Text13.setText("");
		Text14.setText("");
		Text15.setText("");
		Text16.setText("");

	}
	
	public void itemStateChanged(ItemEvent ie)
  	{
    	Object source = ie.getSource();

    	eccframe.reset();
    	
        if(source==fr&&ECCFrame.raum==1) 
        {
        	ECCFrame.raum=0;
        	resetPanel();
        	eccframe.reset();
        	eccframe.makeFr(true);
        }
        
        if(source==fp&&ECCFrame.raum==0)
        {
        	ECCFrame.raum=1;
        	resetPanel();
        	eccframe.reset();
        	eccframe.makeFp(true);
        }
    }
    
    public void actionPerformed(ActionEvent actionevent)
    {
        /*Object obj = actionevent.getSource();
        if (obj == ButtonHelp)
        	ButtonHelpClicked();*/
    }
    
    public void ButtonHelpClicked()
    {
   		/*try 
   		{
       		Process p = Runtime.getRuntime().exec("cmd.exe");
       	}
     	catch (Exception e) 
     	{
       		e.printStackTrace();
       	}*/
    }
        
}