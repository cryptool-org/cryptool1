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

public class LogDatei extends Dialog implements ActionListener
{
	
	private static final long serialVersionUID = -3737366206000100569L;
	protected Button ButtonOK;
	protected TextArea myTextArea;
	protected boolean exit;
	
	public LogDatei(ECCFrame eccframe, String myLogText) // Konstruktor 
	{
		super(eccframe, eccframe.text.logTitle, false);
	 			
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
		myTextArea.setSelectionStart(myTextArea.getText().length());
		myTextArea.setSelectionEnd(myTextArea.getText().length());
	    add("Center",myTextArea);
	   	
	   	ButtonOK = new Button (" OK ");
	   	ButtonOK.setEnabled(true);
		ButtonOK.addActionListener(this);
	    ButtonOK.setSize(new Dimension(40,20));
	    add("South",ButtonOK);
		//myTextArea.setFocusable(false);
		ButtonOK.setFocusable(true);
		setLocation(250,150);
	   	setSize (500,250);
		setResizable(false);

		setVisible(true);

		pack();
	}
 
	public void setText(String myLogText){
		myTextArea.setText(myLogText);
		myTextArea.setSelectionStart(myTextArea.getText().length());
		myTextArea.setSelectionEnd(myTextArea.getText().length());
	}
	
    public void actionPerformed(ActionEvent actionevent)
    {
	    Object obj = actionevent.getSource();
	    if(obj == ButtonOK) exit=true;
	    setVisible(false);
	    dispose();
    }
 }  