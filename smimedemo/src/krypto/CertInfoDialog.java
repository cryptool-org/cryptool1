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

package krypto;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.security.NoSuchProviderException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.util.Date;



public class CertInfoDialog {
	
//	private static Dialog dialog;
	
	
	/**
	 * Konstuktor 
	 */
	public CertInfoDialog(){
		
	}
	
	public void creatDialog(String certFileName){
		//dialog = new Dialog(shell,SWT.None);
		try{
			CertificateFactory fact = CertificateFactory.getInstance("X.509","BC");
			X509Certificate    x509Cert = (X509Certificate)fact.generateCertificate(new FileInputStream(certFileName));
			//.setText("Infos zum Zertifikat");
			//shell.setMessage("Zertifikatstyp: \t" + x509Cert.getType()+"\nVersion: \t\t" + x509Cert.getVersion()+ "\nAussteller: \t" + x509Cert.getIssuerX500Principal()+"\nSignaturalgorithmus:" + x509Cert.getSigAlgName()+"\nGültig bis: \t" + x509Cert.getNotAfter());
			//dialog.open();
			
	        System.out.println("Infos zum Zertifikat: ");
	        System.out.println("===================== ");
	        System.out.println("Zertifikatstyp: " + x509Cert.getType());
	        System.out.println("Version: " + x509Cert.getVersion());
	        System.out.println("Aussteller/issuer: " + x509Cert.getIssuerX500Principal());
	        System.out.println("Seriennummer: " + x509Cert.getSerialNumber());
	        System.out.println("Signaturalgorithmus: " + x509Cert.getSigAlgName() + " (" + x509Cert.getSigAlgOID() + ")");
	        System.out.println("Hashcode: " + x509Cert.hashCode());
	        try{
	        	x509Cert.checkValidity(new Date());
	        }
	        catch (Exception e){
	        /*	MessageBox errCert = new MessageBox(shell, SWT.ICON_ERROR |
						SWT.OK);
				errCert.setText("Zertifikatsfehler");    
				errCert.setMessage("Zertifikat nicht gültig!");
				int r = errCert.open(); */
	        }
	        System.out.println("Gültig von: " + x509Cert.getNotBefore());
	        System.out.println("Gültig bis: " + x509Cert.getNotAfter());
	        System.out.println("BasicConstraints: " + x509Cert.getBasicConstraints());
	        
			}
			catch (CertificateException e){
				/*MessageBox errCert = new MessageBox(shell, SWT.ICON_ERROR |
						SWT.OK);
				errCert.setText("Zertifikatsfehler");    
				errCert.setMessage("Kein x.509 Zertifikat gefunden!");
				    int r = errCert.open(); */
			}
			catch (NoSuchProviderException e){
				System.out.println("Provider nicht gefunden!");
			}
			catch (FileNotFoundException e){
			/*	MessageBox errFile = new MessageBox(shell, SWT.ICON_ERROR |
						SWT.OK);
					errFile.setText("Dateifehler");
					errFile.setMessage("Datei nicht gefunden!");
				    int r2 = errFile.open(); */
	        
	        }
			
			
/*			while(!shell.isDisposed()){
				if(!display.readAndDispatch())
					display.sleep();
				}
			    
			System.out.println("und wech");
			display.dispose(); */
			
	}
	
//	public static void main (String[] args){
//		new CertInfoDialog();
//	}
}
