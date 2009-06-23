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

package userinterface;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;
import java.io.Writer;
import java.security.NoSuchProviderException;
import java.security.PrivateKey;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;

import javax.mail.internet.ParseException;

import krypto.KryptoService;
import mail.Mail;
import mail.MailService;
import main.Config;
import main.Resetable;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.StackLayout;
import org.eclipse.swt.events.PaintEvent;
import org.eclipse.swt.events.PaintListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.ImageData;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import texte.ITexte;
import utils.Tools;
import utils.Version;

/**
 * Die GUI des S/MIME Visualization Control Centers.
 */
public class GUI implements Resetable {
	
	// Parameter für die GUI-Dimensionen
	private int windowlength;
	
	private int windowheight;
	
	
	// Parameter für die interne Verwaltung der gewählten Optionen
	
	/** Auswahl zwischen Signieren und Verschlüsseln  <br>
	 *  auswahl = 0: signieren; auswahl = 1: verschlüsseln */
	private int auswahl;                                      
													 		 
	private boolean internalCertificate;                     // true  = Testzertifikat wird benutzt
													 		 // false = Eigenes Zertifikat wird benutzt 
	private boolean start;                                   // Gibt an, welcher Button gedrückt wurde
												     		 // true = Start; false = Abbruch
	private String emailText;                                // Nachrichtentext der E-Mail
	private String emailAdressReceipient;                    // E-Mail-Adresse des Empfängers
	private String certFileName;							 // Pfad der Zertifikats-Datei
	private String language = "";
	//static String intCertFileName;
	
	/** Zertifikat */
	private X509Certificate x509Cert = null;
	
	/** Privater Schlüssel */
	private PrivateKey theKey = null;
	
	/** Passwort zum privaten Schlüssel */
	private String password = null;
	
	/** Aktuelle Konfiguration */
	private Config config = null;
	
	//	 Die Auswahl der ComboBoxen wird hier gespeichert
	private int selectedHash, selectedSigAlg, selectedMimeType, selectedTransCode;  
	private int selectedEncAlg;
	
	// Einzelne Elemente der GUI
	private Combo combo1, combo2, combo3, combo5;							// Comboboxen
	private Combo comboV1;
	private Label label1, label2, label3, label5;					// Labels
	private Label labelV1;
	
	// Buttons
	private Button buttonStart, buttonAbbrechen; 
	private Button buttonLoadCert, buttonInternalCert, buttonOwnCert;		
	private Button buttonSignieren, buttonVerschlüsseln;										// Button Signieren oder Verschlüsseln
	
	// Textfelder
	private Text text0, textMailBody, textReceipient;							

	
	// Groups
	private Group groupSteuerungsParameter;
	private Group groupSignieren;
	private Group groupZertifikatsOptionen;
	private Group groupNachrichtenText;

	/** Testmodus aktiviert? */
	private boolean test = false;

	private Shell shell;

	private Composite sigComp;

	private Composite encComp;

	private StackLayout parameterLayout;

	private Text textSender;

	private Text textSubject;

	private String emailAdressSender;

	private String emailSubject;
	
	/**
	 * Konstruktor: Erzeugt die GUI und legt Parameter fest 
	 * @param keine
	 */
	public GUI(Config config, boolean test){
		auswahl = 0;	 
		start = false;									     // default: Beendet durch Start-Button
		internalCertificate = true;								     // default: Beispielzertifikat wird verwendet
				
		// GUI-Dimensionen festlegen
		windowlength = 800;
		windowheight = 560;
		emailAdressReceipient = "bob@web.de";				// default für E-Mail-Adresse Empfänger
		emailAdressSender = "alice@wunderland.de";
		emailSubject = "Hallo";
		
		certFileName = null;
//		x509Cert = KryptoService.generateCertificate("RSA");
					
		this.config = config;
		selectedHash = config.getHash();  	            //Auswahl Hashfunktion;         0 = SHA-1, 1 = MD5 
		selectedSigAlg = config.getSigAlg();  	        //Auswahl Signatur-Algorithmus; 0 = RSA, 1 = DSA
		selectedMimeType = config.getMimeTyp();  	    //Auswahl MIME-Typ;             0 = Multipart/signed, 1 = CMS signed-data
		selectedTransCode = config.getTransCode();  	//Auswahl Transferkodierung;	0 = Base64, 1 = quoted-printable
		selectedEncAlg = config.getEncrAlg();
		language = config.getSprache();
		internalCertificate = config.isInternesCertificate();
		
		emailText = ITexte.EMAIL_TEXT.getText(language);  			// default E-Mail-Text
		
		this.test = test;
	}
	

	/**
	 * Baut die GUI auf.
	 * @param args
	 */
	public void setUp() {
		
		selectedHash  = config.getHash();  	 
		selectedSigAlg  = config.getSigAlg(); 
		selectedMimeType  = config.getMimeTyp();
		selectedTransCode  = config.getTransCode(); 
		selectedEncAlg = config.getEncrAlg();
		internalCertificate   = config.isInternesCertificate();
		
		final Display display = new Display();
		shell = new Shell(display);
		try {
			shell.setImage(new Image(display, "lock2.gif"));
		} catch (Exception e){}
		
		shell.setText(ITexte.HEADLINE.getText(language) + " " + Version.version);
		shell.setSize(windowlength, windowheight);
		shell.setMinimumSize(windowlength, windowheight);
		shell.setLayout(new GridLayout(2, true));
		
		
		createGroupHeadline();
		createGroupSigantur();
		createGroupCertificate();
		createGroupMessage();
		createGroupParameter();
		
		
		//Start-Button
		buttonStart = new Button(shell,SWT.PUSH);
		buttonStart.setText(ITexte.START_SIGNIEREN.getText(language));
		buttonStart.setToolTipText(ITexte.TT_BUTTON_START.getText(language));
		GridData gridData = new GridData(SWT.LEFT, SWT.FILL, false, false);
		gridData.widthHint= 200;
		gridData.heightHint = 50;
		buttonStart.setLayoutData(gridData);
		buttonStart.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				emailText = textMailBody.getText().substring(0, Math.min(50, textMailBody.getText().length()));
				emailAdressReceipient = textReceipient.getText();
				emailAdressSender = textSender.getText();
				emailSubject = textSubject.getText();
				
				Mail mail = new Mail();
				mail.setAbsender(emailAdressSender);
				mail.setBetreff(emailSubject);
				mail.setEmpfaenger(emailAdressReceipient);
				mail.setText(textMailBody.getText().getBytes());
				mail.setMailTypes(new String[]{"text/plain"});
				start = true;
				
				String mail4 = null;
				try	{
					MailService service = new MailService();
					
					// Konfiguration aktualisieren
					config.setEncrAlg(selectedEncAlg); 
					config.setHash(selectedHash);
					config.setMimeTyp(selectedMimeType);
					config.setSigAlg(selectedSigAlg);
					config.setTransCode(selectedTransCode);
					config.setInternesCertificate(internalCertificate);
					
					String mail1 = service.createMail1(mail, config);
					String mail2 = service.createMail2(mail, config);
					String mail3 = service.createMail3(mail, config);
					
					if (auswahl == 0){
						mail4 = KryptoService.signMail   (mail, config, theKey, password);
					} else {
						mail4 = KryptoService.encryptMail(mail, config, getX509Cert(), password);
					}
					
					// Datei schreiben
					writeXML(mail1, mail2, mail3, mail4);
					
					if(mail4 != null){
						if (config.getSprache().equals("DE")){
							Runtime.getRuntime().exec("SMIME_Animation.exe anim.swf");
						} else{
							Runtime.getRuntime().exec("SMIME_Animation.exe anim.swf");
						}
//						display.dispose();
					}

				} catch (IOException e3) {
					if (test){
						e3.printStackTrace();
					}

					MessageBox err = new MessageBox(shell, SWT.ICON_ERROR |
							SWT.OK);
					err.setText(ITexte.ERR_FILE_ERROR.getText(language));    
					err.setMessage("" + e3.getMessage());
					err.open();
				} catch (ParseException e4) {
					if (test){
						e4.printStackTrace();
					}

					MessageBox err = new MessageBox(shell, SWT.ICON_ERROR |
							SWT.OK);
					err.setText("ParseError");    
					err.setMessage(ITexte.ERR_PARSING.getText(language));
					err.open();
				} catch (NullPointerException e2) {
					if (test){
						e2.printStackTrace();
					}

					MessageBox err = new MessageBox(shell, SWT.ICON_ERROR |
							SWT.OK);
					err.setText(ITexte.ERR_ERROR.getText(language));    
					err.setMessage(ITexte.ERR_UNKNOWN.getText(language));
					err.open();
				} catch (Exception e) {
					if (test){
						e.printStackTrace();
					}
					MessageBox err = new MessageBox(shell, SWT.ICON_ERROR |
							SWT.OK);
					err.setText(ITexte.ERR_ERROR.getText(language));    
					err.setMessage(e.getMessage());
					err.open();
				}
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
			}
		});
		
	
		//Abbrechen-Button
		buttonAbbrechen = new Button(shell,SWT.PUSH);
		buttonAbbrechen.setText(ITexte.ABBRECHEN.getText(language));
		gridData = new GridData(SWT.RIGHT, SWT.FILL, false, false);
		gridData.widthHint= 200;
		gridData.heightHint = 50;
		buttonAbbrechen.setLayoutData(gridData);
		buttonAbbrechen.setToolTipText(ITexte.TT_BUTTON_ABBRECHEN.getText(language));
		buttonAbbrechen.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				start = false;
				display.dispose();
				}
			public void widgetDefaultSelected(SelectionEvent arg0) {
				}
		});
		
		shell.open();
		
		while(!shell.isDisposed()){
			if(!display.readAndDispatch())
				display.sleep();
			}
		display.dispose();

	}
	
	private void createGroupMessage() {
		groupNachrichtenText = new Group(shell,SWT.NULL);
		groupNachrichtenText.setText(ITexte.NACHRICHTENTEXT.getText(language));
		groupNachrichtenText.setLayout(new GridLayout(2, false));
		groupNachrichtenText.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true));
		
		Label label = new Label(groupNachrichtenText,SWT.NONE);
		label.setText(ITexte.EMAIL_ADRESSE_TO.getText(language));
		
		textReceipient = new Text(groupNachrichtenText, SWT.BORDER);
		textReceipient.setText(emailAdressReceipient);
		textReceipient.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
		textReceipient.setToolTipText(ITexte.TT_EMAIL.getText(language));
		
		label = new Label(groupNachrichtenText,SWT.NONE);
		label.setText(ITexte.EMAIL_ADRESSE_FROM.getText(language));
		
		textSender = new Text(groupNachrichtenText, SWT.BORDER);
		textSender.setText(emailAdressSender);
		textSender.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
		textSender.setToolTipText(ITexte.TT_SENDER_EMAIL.getText(language));
		
		label = new Label(groupNachrichtenText,SWT.NONE);
		label.setText(ITexte.EMAIL_ADRESSE_SUBJECT.getText(language));
		
		textSubject = new Text(groupNachrichtenText, SWT.BORDER);
		textSubject.setText(emailSubject);
		textSubject.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
		textSubject.setToolTipText(ITexte.TT_SUBJECT_EMAIL.getText(language));
		
		textMailBody = new Text(groupNachrichtenText, SWT.BORDER | SWT.V_SCROLL | SWT.WRAP);
		textMailBody.setTextLimit(50);
		textMailBody.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 2, 1));
		textMailBody.setToolTipText(ITexte.TT_GRP_NACH_TEXT.getText(language));
		textMailBody.setText(emailText);
		
		label = new Label(groupNachrichtenText, SWT.WRAP);
		label.setText(ITexte.TT_GRP_NACH_TEXT_MAX.getText(language));
		label.setLayoutData(new GridData(SWT.LEFT, SWT.FILL, true, false, 2, 1));
		
		Button buttonLoadMailText = new Button(groupNachrichtenText,SWT.None);
		buttonLoadMailText.setLayoutData(new GridData(SWT.CENTER, SWT.FILL, false, false, 2, 1));
		buttonLoadMailText.setText(ITexte.BUTTON_NACHTEXT_LADEN.getText(language));
		buttonLoadMailText.addSelectionListener(new SelectionAdapter()  {
			public void widgetSelected(SelectionEvent arg0) {
				
				//File-Dialog
				FileDialog dialog = new FileDialog (shell, SWT.OPEN);
				dialog.setText(ITexte.TITEL_FILEDIALOG.getText(language));
				dialog.setFilterNames (new String [] {
						ITexte.TEXT_DATEIEN.getText(language),
						ITexte.ALLE_DATEIEN.getText(language)
						});
				dialog.setFilterExtensions (new String [] {"*.txt","*.*"}); 
				dialog.setFilterPath ("c:\\");
				dialog.setFileName("");
				
				String mailtext = dialog.open();
				
				if (mailtext != null){
					
					try {
						Reader t = new FileReader(mailtext);
						String input = Tools.readerToString(t);
						textMailBody.setText(input.substring(0, Math.min(50, input.length())));
						emailText = input;
						t.close();
					}
						
					catch (FileNotFoundException e){
						if (test){
							e.printStackTrace();
						}

						MessageBox errFile = new MessageBox(shell, SWT.ICON_ERROR |
								SWT.OK);
						errFile.setText(ITexte.ERR_FILE_ERROR.getText(language));    
						errFile.setMessage(ITexte.ERR_FILE_NOT_FOUND.getText(language));
						errFile.open();
				    }
					catch (IOException e){
						if (test){
							e.printStackTrace();
						}

						MessageBox errFile2 = new MessageBox(shell, SWT.ICON_ERROR |
								SWT.OK);
						errFile2.setText(ITexte.ERR_FILE_ERROR.getText(language));    
						errFile2.setMessage(""+e);
						errFile2.open();
					}
				}
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {widgetSelected(arg0);}
		});
	}


	private void createGroupCertificate() {
		groupZertifikatsOptionen = new Group(shell,SWT.NULL);
		groupZertifikatsOptionen.setText(ITexte.GRP_PSE_OPT.getText(language));
		groupZertifikatsOptionen.setToolTipText(ITexte.TT_GRP_PSE_OPT.getText(language));
		groupZertifikatsOptionen.setLayout(new GridLayout(2, false));
		groupZertifikatsOptionen.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
				
		// Interne PSE /Zertifikat
		buttonInternalCert = new Button(groupZertifikatsOptionen,SWT.RADIO);
		buttonInternalCert.setText(ITexte.INTERNE_PSE.getText(language));
		buttonInternalCert.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 2, 1));
		buttonInternalCert.setSelection(true);
		//buttonInternalCert.setToolTipText("Erlaubt die Auswahl zwischen externem (aus Datei) und internem Zertifikat");
		buttonInternalCert.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				
				if (buttonInternalCert.isEnabled()) {	
					internalCertificate = true;
					reset();
					buttonStart.setEnabled(true);
					if (auswahl == 0) {
						buttonOwnCert.setText(ITexte.EIG_PSE.getText(language));
					} else{
						buttonOwnCert.setText(ITexte.EIG_ZERT.getText(language));
					}
					buttonLoadCert.setEnabled(false);
				} 
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
			// do nothing	
			}
		});
		
		// Eigene PSE / Zertifikat
		buttonOwnCert = new Button(groupZertifikatsOptionen,SWT.RADIO);
		buttonOwnCert.setText(ITexte.EIG_PSE.getText(language));
		buttonOwnCert.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				if (buttonOwnCert.isEnabled()) {	
					internalCertificate = false;
				}
				if (theKey == null){
					buttonStart.setEnabled(false);
				} else{
					buttonStart.setEnabled(true);
				}
				
				if (auswahl == 0) {	
					buttonOwnCert.setText(ITexte.EIG_PSE.getText(language));
				} else{
					buttonOwnCert.setText(ITexte.EIG_ZERT.getText(language));
				}
				buttonLoadCert.setEnabled(true);
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
				}
		});
		
		buttonLoadCert = new Button(groupZertifikatsOptionen,SWT.PUSH);
		buttonLoadCert.setEnabled(false);
		if (auswahl == 0){
			buttonLoadCert.setText(ITexte.PSE_LADEN.getText(language));
			buttonLoadCert.setToolTipText(ITexte.TT_BUTTON_FILEDIALOG2.getText(language));
		} else {
			buttonLoadCert.setText(ITexte.ZERTIFIKAT_LADEN.getText(language));
			buttonLoadCert.setToolTipText(ITexte.TT_BUTTON_FILEDIALOG.getText(language));
		}
		buttonLoadCert.addSelectionListener(new SelectionAdapter()  {
			public void widgetSelected(SelectionEvent arg0)  {
				if (auswahl == 0){
					FileDialog dialog = new FileDialog (shell, SWT.OPEN);
					dialog.setText(ITexte.PSE_LADEN_FILE.getText(language));
					dialog.setFilterNames (new String [] {"PSE (*.p12)", "PSE (*.pfx)"});
					dialog.setFilterExtensions (new String [] {"*.p12", "*.pfx"}); //Windows wild cards
					dialog.setFilterPath ("c:\\"); //Windows path
					dialog.setFileName (" ");
					
					String filenamePSE = dialog.open();
										
					if (filenamePSE != null){
						PasswordDialog p_dialog = new PasswordDialog(shell, language);
						p_dialog.setText(ITexte.PSE_PASSWORT.getText(language));
						MyInputDialogData myData = p_dialog.open();
						if (myData.isButtonResponse()){
							try{
								password = myData.getTextResponse();
								
								AliasDialog a_dialog = new AliasDialog(shell, language);
								a_dialog.setText(ITexte.ALIAS.getText(language));
								MyInputDialogData myAlias = a_dialog.open();
								if (myAlias.isButtonResponse()){
									String alias = myAlias.getTextResponse();  
									
									theKey = KryptoService.getSecretKeyFromPSE(
											alias,
											filenamePSE, password.toCharArray());
									x509Cert = KryptoService.getCertificateFromPSE(
											alias,
											filenamePSE, password.toCharArray());
									
									if(theKey == null){
										throw new Exception(ITexte.ERR_PRIVATEKEY.getText(language));
									}
									MessageBox pseSuccessful = new MessageBox(shell, SWT.ICON_INFORMATION |
											SWT.OK);
									pseSuccessful.setText("PSE");    
									pseSuccessful.setMessage(ITexte.PSE_ERF_GELADEN.getText(language));
									pseSuccessful.open();
									buttonOwnCert.setText(ITexte.PSE_GELADEN.getText(language));
									buttonStart.setEnabled(true);
									config.setFilenamePSE(filenamePSE);
									config.setAliasPSE(alias);
									update();
								}
								
							} catch (IOException e1){
								MessageBox errCert = new MessageBox(shell, SWT.ICON_ERROR |
										SWT.OK);
								errCert.setText(ITexte.ERR_ERROR.getText(language));    
								errCert.setMessage(e1.getMessage());
								errCert.open();
								if (test) e1.printStackTrace();
							}catch (Exception e){
								MessageBox errCert = new MessageBox(shell, SWT.ICON_ERROR |
										SWT.OK);
								errCert.setText(ITexte.ERR_ERROR.getText(language));    
								errCert.setMessage(ITexte.ERR_OPEN_PSE.getText(language));
								errCert.open();
								if (test) e.printStackTrace();
							}
						}
					}
				}
				if (auswahl == 1){
					FileDialog dialog = new FileDialog (shell, SWT.OPEN);
					dialog.setText(ITexte.ZERT_LADEN_FILE.getText(language));
					dialog.setFilterNames (new String [] {
							ITexte.ZERTIFIKAT.getText(language) + " (*.cer)",
							ITexte.ZERTIFIKAT.getText(language) + " (*.der)"});
					dialog.setFilterExtensions (new String [] {"*.cer","*.der"}); //Windows wild cards
					dialog.setFilterPath ("c:\\"); //Windows path
					dialog.setFileName (" ");
					
					certFileName = dialog.open();
					
					if (certFileName != null){
						
						try{
							try{
								CertificateFactory fact = CertificateFactory.getInstance("X.509","BC");
								x509Cert = (X509Certificate)fact.generateCertificate(new FileInputStream(certFileName));
								
							} catch (NoSuchProviderException e) {
								System.out.println("BC-Provider not found...");
							}
														
							MessageBox certSuccessful = new MessageBox(shell, SWT.ICON_INFORMATION |
									SWT.OK);
							certSuccessful.setText(ITexte.ZERTIFIKAT.getText(language));    
							certSuccessful.setMessage(ITexte.ZERTIFIKAT_GEL_FUER.getText(language)
									+x509Cert.getSubjectX500Principal());
							certSuccessful.open();
							buttonInternalCert.setSelection(false);
							buttonOwnCert.setSelection(true);
							buttonOwnCert.setText(ITexte.ZERTIFIKAT_GELADEN.getText(language));
							buttonStart.setEnabled(true);
							config.setFilenamePSE(certFileName);
							update();
							
						} catch (CertificateException e){
							MessageBox errCert = new MessageBox(shell, SWT.ICON_ERROR |
									SWT.OK);
							errCert.setText(ITexte.ZERTIFIKAT_FEHLER.getText(language));    
							errCert.setMessage(ITexte.ERR_X509.getText(language));
							errCert.open();
							buttonInternalCert.setSelection(true);
							buttonOwnCert.setSelection(false);
							internalCertificate = true;
						} catch (FileNotFoundException e){
				        
							MessageBox errFile = new MessageBox(shell, SWT.ICON_ERROR |
									SWT.OK);
							errFile.setText(ITexte.ERR_FILE_ERROR.getText(language));
							errFile.setMessage(ITexte.ERR_FILE_NOT_FOUND.getText(language));
							errFile.open();
							buttonInternalCert.setSelection(true);
							buttonOwnCert.setSelection(false);
							internalCertificate = true;
					        
					    }
			
					}
				}
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
			}
		});
	}


	private void createGroupParameter() {
		groupSteuerungsParameter = new Group(shell,SWT.NULL);
		groupSteuerungsParameter.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true));
		parameterLayout = new StackLayout();
		groupSteuerungsParameter.setLayout(parameterLayout);
		groupSteuerungsParameter.setText(ITexte.GRP_STEUERUNGS_PARAM.getText(language));
		
		sigComp = new Composite(groupSteuerungsParameter,SWT.NONE);
		sigComp.setLayout(new GridLayout(2, false));
		encComp = new Composite(groupSteuerungsParameter,SWT.NONE);
		encComp.setLayout(new GridLayout(2, false));
		
		parameterLayout.topControl = sigComp;
		
		// Combobox Signatur-Algorithmus
		label2 = new Label(sigComp,SWT.NONE);
		label2.setText(ITexte.SIG_ALG.getText(language));
		
		combo2 = new Combo(sigComp, SWT.DROP_DOWN|SWT.READ_ONLY);
		combo2.setItems(new String[] {"RSA","DSA"});
		combo2.select(selectedSigAlg);
		combo2.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
		combo2.setToolTipText(ITexte.TT_SIG_ALG.getText(language));
		combo2.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				if (combo2.getSelectionIndex() == 0){
					selectedSigAlg = 0;
					combo1.setEnabled(true);
				}
				if (combo2.getSelectionIndex() == 1){
					selectedSigAlg = 1;
					combo1.select(0);
					combo1.setEnabled(false);
					selectedHash = 0;
				}
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
			}
		});
		
		// Steuerungsparameter Signieren
		// Combobox Hash-Funktion
		label1 = new Label(sigComp,SWT.NONE);
		label1.setText(ITexte.HASH_FUNKT.getText(language));
		
		combo1 = new Combo(sigComp, SWT.DROP_DOWN|SWT.READ_ONLY);
		combo1.setItems(new String[] {"SHA-1","MD5"});
		combo1.select(selectedHash);
		combo1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
		combo1.setToolTipText(ITexte.TT_HASH.getText(language));
		combo1.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				if (combo1.getSelectionIndex() == 0){
					selectedHash = 0;
				}
				if (combo1.getSelectionIndex() == 1){
					selectedHash = 1;
				}
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
			}
		});

	
		// Combobox Transfercodierung
		label5 = new Label(sigComp,SWT.NONE);
		label5.setText(ITexte.TRANS_CODE.getText(language));
		
		combo5 = new Combo(sigComp, SWT.DROP_DOWN|SWT.READ_ONLY);
		combo5.setItems(new String[] {"Base64","quoted-printable"});
		combo5.select(selectedTransCode);
		combo5.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
		combo5.setToolTipText(ITexte.TT_TRANS_CODE.getText(language));
		combo5.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				
				if (combo5.getSelectionIndex() == 0){
					selectedTransCode = 0;
				}
				else if (combo5.getSelectionIndex() == 1){
					selectedTransCode = 1;
				}
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
			}
		});

		
		// Combobox MIME-Typ
		label3 = new Label(sigComp,SWT.NONE);
		label3.setText(ITexte.MIME_TYP.getText(language));
		
		combo3 = new Combo(sigComp, SWT.DROP_DOWN|SWT.READ_ONLY);
		combo3.setItems(new String[] {"multipart/signed","PKCS#7/signed-data"});
		combo3.select(selectedMimeType);
		combo3.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
		combo3.setToolTipText(ITexte.TT_MIME_TYP.getText(language));
		combo3.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				
				if (combo3.getSelectionIndex() == 0){
					selectedMimeType = 0;
					combo5.setEnabled(true);
					combo5.select(1);
				}
				if (combo3.getSelectionIndex() == 1){
					selectedMimeType = 1;
					combo5.select(0);
					selectedTransCode = 0;
					combo5.setEnabled(false);
				}
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
				
			}
		});
		
		// Steuerungsparameter zum Verschlüsseln 
		// Combobox Symmetrisches Verschlüsselungsverfahren
		labelV1 = new Label(encComp,SWT.NONE);
		labelV1.setText(ITexte.VERSCHL_VERFAHREN.getText(language));
		
		comboV1 = new Combo(encComp, SWT.DROP_DOWN|SWT.READ_ONLY);
		comboV1.setItems(new String[] {"AES", "Triple-DES",});
		comboV1.select(0);
		comboV1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
		comboV1.setToolTipText(ITexte.TT_VERSCHL_VERFAHREN.getText(language));
		comboV1.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				if (comboV1.getSelectionIndex() == 0){
					selectedEncAlg = 0;
				}
				if (comboV1.getSelectionIndex() == 1){
					selectedEncAlg = 1;
				}
				
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
			}
		});
		
		Canvas image = new Canvas(encComp, SWT.DOUBLE_BUFFERED);
		GridData gridData = new GridData(SWT.CENTER, SWT.BOTTOM, true, true, 2, 1);
		gridData.widthHint = 135;
		gridData.heightHint = 135;
		image.setLayoutData(gridData);
		image.addPaintListener(new PaintListener(){
			@Override
			public void paintControl(PaintEvent e) {
				Image id = new Image(e.display, "images" + File.separatorChar + "encrypt.png");
				ImageData imD = id.getImageData();
				imD.transparentPixel = 16777215; //white
				Image img = new Image(Display.getCurrent(), imD);
				e.gc.drawImage(img, 0, 0);
			}
		});
		
		image = new Canvas(sigComp, SWT.DOUBLE_BUFFERED);
		image.setLayoutData(gridData);
		image.addPaintListener(new PaintListener(){
			@Override
			public void paintControl(PaintEvent e) {				
				Image id = new Image(e.display, "images" + File.separatorChar + "sign.png");
				ImageData imD = id.getImageData();
				imD.transparentPixel = 16777215; //white
				Image img = new Image(Display.getCurrent(), imD);
				e.gc.drawImage(img, 0, 0);
			}
		});
	}


	private void createGroupSigantur() {
		groupSignieren = new Group(shell,SWT.NULL);
		groupSignieren.setText(ITexte.GRP_SIGNIEREN.getText(language));
		groupSignieren.setToolTipText(ITexte.TT_GRP_SIG_VER.getText(language));
		groupSignieren.setLayout(new GridLayout(1, false));
		groupSignieren.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
		
		buttonSignieren = new Button(groupSignieren,SWT.RADIO);
		buttonSignieren.setText(ITexte.SIGNIEREN.getText(language));
		buttonSignieren.setVisible(true);
		buttonSignieren.setSelection(true);
		buttonSignieren.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				if (buttonSignieren.isEnabled()) {
					auswahl = 0;
					buttonStart.setText(ITexte.START_SIGNIEREN.getText(language));
					buttonLoadCert.setText(ITexte.PSE_LADEN.getText(language));
					groupZertifikatsOptionen.setText(ITexte.GRP_PSE_OPT.getText(language));
					buttonOwnCert.setText(ITexte.EIG_PSE.getText(language));
					buttonInternalCert.setText(ITexte.INTERNE_PSE.getText(language));
					buttonLoadCert.setToolTipText(ITexte.TT_BUTTON_FILEDIALOG2.getText(language));
					parameterLayout.topControl = sigComp;
					update();
				}
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {widgetSelected(arg0);}
		});
		
		
		buttonVerschlüsseln = new Button(groupSignieren,SWT.RADIO);
		buttonVerschlüsseln.setText(ITexte.VERSCHLUESSELN.getText(language));
		buttonVerschlüsseln.setEnabled(true); // nicht anwählbar
		buttonVerschlüsseln.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent arg0) {
				if (buttonVerschlüsseln.isEnabled()) {	
					auswahl = 1;
					buttonStart.setText(ITexte.START_ENCRYPTING.getText(language));
					buttonLoadCert.setText(ITexte.ZERTIFIKAT_LADEN.getText(language));
					buttonLoadCert.setToolTipText(ITexte.TT_BUTTON_FILEDIALOG.getText(language));
					groupZertifikatsOptionen.setText(ITexte.ZERTIFIKAT_AUSWAEHLEN.getText(language));
					buttonOwnCert.setText(ITexte.EIG_ZERT.getText(language));
					buttonInternalCert.setText(ITexte.INTERN_ZERT.getText(language));
					parameterLayout.topControl = encComp;
					update();
				} 
			}
			public void widgetDefaultSelected(SelectionEvent arg0) {
			}
		});
	}


	private void createGroupHeadline() {
		// Label 0 zur kurzen Erklärung des Programms, Position zw. Titelzeile und Reiter
		text0 = new Text(shell,SWT.WRAP | SWT.MULTI);
		text0.setText(ITexte.BESCHREIBUNG.getText(language));
		text0.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 2, 1));
		text0.setEditable(false);
		text0.setToolTipText("Version: " + Version.getVersionInfo());
		
	}

	private void update(){
		shell.layout();
		groupNachrichtenText.layout();
		groupSignieren.layout();
		groupSteuerungsParameter.layout();
		groupZertifikatsOptionen.layout();
	}

	public boolean isReady(){
		return start;
	}
	
	/**
	 * Schreibt die XML-Austauschdatei für die Flash-Animation.
	 * @param mail1 E-Mail 1
	 * @param mail2 E-Mail 2
	 * @param mail3 E-Mail 3
	 * @param mail4 E-Mail 4
	 * @throws IOException
	 */
	private void writeXML(String mail1, String mail2, String mail3, String mail4) throws IOException{
	
		StringBuffer sb = new StringBuffer();
		sb.append(getHeader());
		sb.append("<visualization>");
		sb.append("\n");
		sb.append("<action>" + auswahl + "</action>");
		sb.append("\n");
		sb.append("<language>" + (config.getSprache().equalsIgnoreCase("DE") ? 0 : 1) + "</language>");
		sb.append("\n");
		sb.append(getCertOpt(getX509Cert()));
		sb.append(getSteuerungsParam());
		sb.append(getMail1(mail1));
		sb.append(getMail2(mail2));
		sb.append(getMail3(mail3));
		sb.append(getMail4(mail4));
		sb.append("</visualization>");
		sb.append("\n");
		
		// Daten in Datei schreiben
		write(config.getFilename(), sb.toString());
		
	}

	/**
	 * Schreibt die übergebenen Daten in ein File.
	 * @param filename
	 * @param data
	 * @throws IOException
	 */
	private void write(String filename, String data) throws IOException{
		Writer w = new FileWriter(new File(filename));
		w.write(data);
		w.flush();
		w.close();
	}
	
	/**
	 * Gibt den Header der xml-Datei zurück
	 * @return
	 */
	private String getHeader(){
		StringBuffer sb = new StringBuffer();
		
		// Startzeile
		sb.append("<?xml version=\"1.0\" ");
		sb.append("encoding=\"ISO-8859-1\" ");
		sb.append("standalone=\"no\" ?>");
		sb.append("\n");
		
		// DOCTYPE
		sb.append("<!DOCTYPE visualization [");
		sb.append("\n");
		sb.append("<!ELEMENT visualization (action, language, certOpt, steuerungsParam, ");
		sb.append(" mail1, mail2, mail3, mail4) >");
		sb.append("\n");
		sb.append("<!ELEMENT action            (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT language          (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT certOpt (version, serial, certSigAlg, issuer, ");
		sb.append("\n");
		sb.append("issuerID, validFrom, validTo, owner, ownerID, keyAlg) >");
		sb.append("\n");
		sb.append("<!ELEMENT version           (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT serial            (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT certSigAlg        (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT issuer            (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT issuerID          (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT validFrom         (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT validTo           (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT owner             (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT ownerID           (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT keyAlg            (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT steuerungsParam (hashAlg, sigAlg, MIME-Typ, transCode, receiverAdr) >");
		sb.append("\n");
		sb.append("<!ELEMENT hashAlg           (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT sigAlg            (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT MIME-Typ          (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT transCode         (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT receiverAdr       (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT mail1             (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT mail2             (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT mail3             (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT mail4             (#PCDATA) >");
		sb.append("\n");
		sb.append("<!ELEMENT owner             (#PCDATA) >");
		sb.append("\n");
		sb.append("]>");
		sb.append("\n");
		
		return sb.toString();
	}
	
	private String getCertOpt(X509Certificate x509Cert){
		StringBuffer sb = new StringBuffer();
		sb.append("<certOpt>");
		if (x509Cert != null){
			sb.append("<version>v" + x509Cert.getVersion() + "</version>");
			sb.append("\n");
			sb.append("<serial>" + x509Cert.getSerialNumber() + "</serial>");
			sb.append("\n");
			sb.append("<certSigAlg>" + x509Cert.getSigAlgName() + "</certSigAlg>");
			sb.append("\n");
			if(x509Cert.getSubjectDN().getName().equals("CN=Test Certificate"))
				sb.append("<issuer>" + "CN=Trust Center" + "</issuer>");
			else
				sb.append("<issuer>" + x509Cert.getIssuerDN()+ "</issuer>");
			sb.append("\n");
			sb.append("<issuerID>" + " " + "</issuerID>");
			sb.append("\n");
			sb.append("<validFrom>" + x509Cert.getNotBefore() + "</validFrom>");
			sb.append("\n");
			sb.append("<validTo>" + x509Cert.getNotAfter() + "</validTo>");
			sb.append("\n");
			if(x509Cert.getSubjectDN().getName().equals("CN=Test Certificate"))
				sb.append("<owner>" + (auswahl == 0 ? "CN=Alice" : "CN=Bob") + "</owner>");
			else
				sb.append("<owner>" + x509Cert.getSubjectDN().getName() + "</owner>");
			sb.append("\n");
			sb.append("<ownerID>" + " " + " </ownerID>");
			sb.append("\n");
			if(auswahl == 0)
				sb.append("<keyAlg>" + " " + "</keyAlg>");
			else
				sb.append("<keyAlg>" + (config.getEncrAlg() == 0 ? "AES" : "Triple-DES") + "</keyAlg>");
			sb.append("\n");
		}
		sb.append("</certOpt>");
		sb.append("\n");
		
		return sb.toString();
	}
	
	/**
	 * Schreibt die Steuerungsparameter.
	 * @return
	 */
	private String getSteuerungsParam(){
		StringBuffer sb = new StringBuffer();
	
		sb.append("<steuerungsParam>");
		sb.append("\n");
		sb.append("<hashAlg>" + selectedHash + "</hashAlg>");
		sb.append("\n");
		sb.append("<sigAlg>" + selectedSigAlg + "</sigAlg>");
		sb.append("\n");
		sb.append("<MIME-Typ>" + selectedMimeType + "</MIME-Typ>");
		sb.append("\n");
		sb.append("<transCode>" + selectedTransCode + "</transCode>");
		sb.append("\n");
		sb.append("<receiverAdr>" + emailAdressReceipient + "</receiverAdr>");
		sb.append("\n");
		sb.append("</steuerungsParam>");
		sb.append("\n");
		
		return sb.toString();
	}
	
	private String getMail1(String mail){
		StringBuffer sb = new StringBuffer();
		sb.append("<mail1>");
		sb.append(mail);
		sb.append("</mail1>");
		sb.append("\n");
		return sb.toString();
	}
	
	private String getMail2(String mail){
		StringBuffer sb = new StringBuffer();
		sb.append("<mail2>");
		sb.append(mail);
		sb.append("</mail2>");
		sb.append("\n");
		return sb.toString();
	}
	
	private String getMail3(String mail){
		StringBuffer sb = new StringBuffer();
		sb.append("<mail3>");
		sb.append(mail);
		sb.append("</mail3>");
		sb.append("\n");
		return sb.toString();
	}
	
	private String getMail4(String mail){
		StringBuffer sb = new StringBuffer();
		sb.append("<mail4>");
		sb.append(mail);
		sb.append("</mail4>");
		sb.append("\n");
		return sb.toString();
	}

	
	/**
	 * Setzt die vertraulichen Informationen zurück.
	 */
	public void reset(){
		theKey = null;
		password = null;
		x509Cert = null;
	}


	/**
	 * Gibt das Zertifikat zurück.
	 * @return the x509Cert
	 */
	public X509Certificate getX509Cert() {
		if (x509Cert == null){
			x509Cert = KryptoService.generateCertificate("RSA");
		}
		return x509Cert;
	}


	/**
	 * @param cert the x509Cert to set
	 */
	public void setX509Cert(X509Certificate cert) {
		x509Cert = cert;
	}
	
}
