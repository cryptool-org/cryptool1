package userinterface;



import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import texte.ITexte;


public class PasswordDialog extends Dialog {
	private Label lblQuestion;
	private Text txtResponse;
	private Button btnOkay;
	private Button btnCancel;
	private MyInputDialogData data;
	private String language;

	
	PasswordDialog (Shell x, String language){
		super(x);
		this.language = language;
	} 
	
	
	public MyInputDialogData open () {
	
		data = new MyInputDialogData();
		final Shell shell = new Shell(getParent(), SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		shell.setText(getText());
		shell.setSize(260,130);
		
		lblQuestion = new org.eclipse.swt.widgets.Label(shell, SWT.NONE);
		lblQuestion.setLocation(25,10);
		lblQuestion.setSize(250,20);
		lblQuestion.setText(ITexte.EINGABE_PASSWORT.getText(language));
		
		txtResponse = new org.eclipse.swt.widgets.Text(shell, SWT.BORDER);
		txtResponse.setLocation(25,30);
		txtResponse.setSize(200,20);
		txtResponse.setVisible(true);
		txtResponse.setEchoChar('*');
		
		btnOkay = new Button (shell, SWT.PUSH);
		btnOkay.setText ("OK");
		btnOkay.setLocation(25,60);
		btnOkay.setSize(75,25);
		
		btnCancel = new Button (shell, SWT.PUSH);
		btnCancel.setText (ITexte.ABBRECHEN.getText(language));
		btnCancel.setLocation(160,60);
		btnCancel.setSize(75,25);
		
		Listener listener = new Listener () {
			public void handleEvent (Event event) {
				data.setButtonResponse(event.widget == btnOkay);
				data.setTextResponse(txtResponse.getText());
				shell.close ();
			}
		};
		btnOkay.addListener(SWT.Selection, listener);
		btnCancel.addListener(SWT.Selection, listener);
		shell.open();
		Display display = getParent().getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) 
				display.sleep();
			}
		return data;
	}
}