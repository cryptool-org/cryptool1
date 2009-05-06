/**
 * 01.05.2008
 */
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

public class AliasDialog extends Dialog {

	private Label lblQuestion;
	private Text txtResponse;
	private Button btnOkay;
	private Button btnCancel;
	private MyInputDialogData data;
	private String language;
	
	
	/**
	 * @param arg0
	 */
	public AliasDialog(Shell arg0, String language) {
		super(arg0);
		this.language = language;
	}

	/**
	 * @param arg0
	 * @param arg1
	 */
	public AliasDialog(Shell arg0, int arg1, String language) {
		super(arg0, arg1);
		this.language = language;
	}

	
	/**
	 * @return
	 */
	public MyInputDialogData open () {
		
		int start = 25;       // Startpos x
		int startBtn = 60;    // Startpos y Buttons
		
		int laengeGes = 410;  // Länge des Doalogs
		int laengeTxt = 350;  // Länge der Textbox
		
		int laengeBtn = 100;  // Länge der Buttons
		int hoeheBtn = 25;    // Höhe der Buttons
		
		data = new MyInputDialogData();
		final Shell shell = new Shell(getParent(), SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		shell.setText(getText());
		shell.setSize(laengeGes,130);
		
		lblQuestion = new Label(shell, SWT.NONE);
		lblQuestion.setLocation(start,10);
		lblQuestion.setSize(laengeGes-10, 20);
		lblQuestion.setText(ITexte.EINGABE_ALIAS.getText(language));
		
		txtResponse = new Text(shell, SWT.BORDER);
		txtResponse.setLocation(start,30);
		txtResponse.setSize(laengeTxt,20);
		txtResponse.setVisible(true);
		
		btnOkay = new Button (shell, SWT.PUSH);
		btnOkay.setText ("OK");
		btnOkay.setLocation(start, startBtn);
		btnOkay.setSize(laengeBtn, hoeheBtn);
		
		btnCancel = new Button (shell, SWT.PUSH);
		btnCancel.setText (ITexte.ABBRECHEN.getText(language));
		btnCancel.setLocation(laengeTxt + start - laengeBtn, startBtn);
		btnCancel.setSize(laengeBtn, hoeheBtn);
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
