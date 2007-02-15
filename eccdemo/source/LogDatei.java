package eccdemo;

import java.awt.*;
import java.awt.event.*;

public class LogDatei extends Dialog implements ActionListener
{
	
	protected Button ButtonOK;
	protected TextArea myTextArea;
	protected boolean exit;
	
	public LogDatei(ECCFrame eccframe, String myLogText) // Konstruktor 
	{
		super(eccframe, eccframe.text.logTitle, true);
	 			
		addWindowListener(new WindowAdapter() 
	    {
	    public void windowClosing(WindowEvent event) 
	    {exit=true;setVisible(false);dispose();}
	    });
	
		exit=false;
		BorderLayout myBorderLayout = new BorderLayout();
		setLayout(myBorderLayout);
		
		myTextArea = new TextArea();
		myTextArea.setEditable(false);
		myTextArea.setText(myLogText);
	    add("Center",myTextArea);
	   	
	   	ButtonOK = new Button (" OK ");
	   	ButtonOK.setEnabled(true);
		ButtonOK.addActionListener(this);
	    ButtonOK.setPreferredSize(new Dimension(40,20));
	    add("South",ButtonOK);
		//myTextArea.setFocusable(false);
		ButtonOK.setFocusable(true);
		setLocation(250,150);
	   	setSize (500,250);
		setResizable(false);

		setVisible(true);

		pack();
	}
 
    public void actionPerformed(ActionEvent actionevent)
    {
	    Object obj = actionevent.getSource();
	    if(obj == ButtonOK) exit=true;
	    setVisible(false);
	    dispose();
    }
 }  