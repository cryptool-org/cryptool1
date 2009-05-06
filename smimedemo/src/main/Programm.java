package main;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.security.NoSuchProviderException;
import java.security.Security;
import java.security.cert.CertificateException;

import org.bouncycastle.jce.provider.BouncyCastleProvider;

import userinterface.GUI;


/**
 * Hauptprogramm.
 */
public class Programm {
	
	// Schalter ob PreProduction oder nicht
	private static boolean isPreProduction = false;
	
	private static int hash, sigAlg, mimeTyp, transCode;			//Parameter Signatur
	private static int encAlg;										//Parameter Verschlüsselung
//	private static String certfilepath;
	private static Config config = null;
	
	/**
	 * Konstruktor
	 */
	public Programm(){
		hash = 0;
		sigAlg = 0;
		transCode = 1;
		encAlg = 0;
		mimeTyp = 0;
	}

	/**
	 * Hauptprogramm.
	 * @param args
	 * @throws NoSuchProviderException 
	 * @throws CertificateException 
	 * @throws IOException 
	 */
	public static void main(String[] args) throws CertificateException, NoSuchProviderException, IOException {
		
//		BASE64Decoder dec = new BASE64Decoder();
//		byte[] bary = dec.decodeBuffer("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");
//		String s = Charset.defaultCharset().decode(ByteBuffer.wrap(bary)).toString();
//		
//		bary = dec.decodeBuffer("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");
//		s = Charset.defaultCharset().decode(ByteBuffer.wrap(bary)).toString();
		
		
		isPreProduction = false;
		
		// Parameter laden
		File file = new File("smime.ini");
		int[] params = loadParam(file);
		
		// Configuration setzen 
		if (params.length == 4){
			config = new Config(params[0], params[1], params[3], 0, params[2]);
		} else {
			config = new Config(hash, sigAlg, transCode, encAlg, mimeTyp);
		}

		config.setInternesCertificate(true);
		
		// Dateiname des Outputfiles
		config.setFilename("params.xml");
		config.setTest(isPreProduction);
//		config.setFilename("c:/toto.xml");

		// Sprache setzen
		if (args.length == 1){
			if (args[0].toUpperCase().equals("DE") ||
					args[0].toUpperCase().equals("EN"))
			config.setSprache(args[0].toUpperCase());
		} else{
			config.setSprache("DE");
		}
		
		try {
			// Hinzufügen des BC-Providers
			Security.addProvider(new BouncyCastleProvider());
			
			// GUI erzeugen
			GUI gui = new GUI(config, isPreProduction);
			gui.setUp();
			
//			while(gui.isReady()) {
//				try {
//					if (!isPreProduction){
//						if (config.getSprache().equals("DE")){
//							Runtime.getRuntime().exec("SMIME_Animation.exe signing_de.swf");
//						} else{
//							Runtime.getRuntime().exec("SMIME_Animation.exe signing_en.swf");
//						}
//					}
//					
//				} catch (Exception e){
//					if (isPreProduction){
//						System.out.println(ITexte.ERR_FLASH.getText(config.getSprache()));
//					}
//					throw e;
//				}
//				gui.setUp();
//			}
	
//			System.out.println(ITexte.ABBRUCH.getText(config.getSprache()));
		} catch (Exception e){
			System.out.println("Error while running...");
			if (isPreProduction) System.out.println(e.getMessage());
		}

	}

	/**
	 * Lädt die default-Einstellungen aus der angegebenen Datei.
	 * @param f
	 * @return
	 */
	public static int[] loadParam(File f){
		int[] param = {0,0,0,0};
		
		try{
			
			FileReader fr = new FileReader(f);   
			StringBuffer sb = new StringBuffer();
			
			int b = 0;
			while (b != -1){
				b = fr.read();
				sb.append((char)b);
			}
			fr.close();
			
			String s = sb.toString();
			
			// HashAlg
			int anfang, ende = -1;
			anfang = s.indexOf("<hashAlg>")+9;
			ende   = s.indexOf("</hashAlg>");
			if (anfang != -1 && ende != -1){
				param[0] = Integer.parseInt(s.substring(anfang, ende));
			} 
			
			//SigAlg
			anfang = -1; 
			ende = -1;
			anfang = s.indexOf("<sigAlg>")+8;
			ende   = s.indexOf("</sigAlg>");
			if (anfang != -1 && ende != -1){
				param[1] = Integer.parseInt(s.substring(anfang, ende));
			} 
			
			//MIME-Typ
			anfang = -1; 
			ende = -1;
			anfang = s.indexOf("<MIMETyp>")+9;
			ende   = s.indexOf("</MIMETyp>");
			if (anfang != -1 && ende != -1){
				param[2] = Integer.parseInt(s.substring(anfang, ende));
			} 

			//transCode
			anfang = -1; 
			ende = -1;
			anfang = s.indexOf("<transCode>")+11;
			ende   = s.indexOf("</transCode>");
			if (anfang != -1 && ende != -1){
				param[3] = Integer.parseInt(s.substring(anfang, ende));
			}

			return param;
			
		} catch (Exception e){
			System.out.println("Kann die Datei der Startparameter nicht finden oder öffnen!\n=>Default-Einstellungen werden verwendet!");
			return new int[]{0,0,0,1};
		}
		
	}
	
	
	/**
	 * Gibt Infos zum Zertifikat in der Console aus.
	 * @param file
	 * @throws CertificateException
	 * @throws NoSuchProviderException
	 */
//	protected static void info (String file) throws CertificateException, NoSuchProviderException{
//		
//		// create the certificate factory
//        CertificateFactory fact = CertificateFactory.getInstance("X.509","BC");
//        
//        // read the certificate
//        try {
//	        X509Certificate    x509Cert = (X509Certificate)fact.generateCertificate(new FileInputStream(file));
//	        System.out.println("");
//	        System.out.println("Infos zum Zertifikat: ");
//	        System.out.println("===================== ");
//	        System.out.println("Zertifikatstyp: " + x509Cert.getType());
//	        System.out.println("Version: " + x509Cert.getVersion());
//	        System.out.println("Herausgeber/issuer: " + x509Cert.getIssuerX500Principal());
//	        System.out.println("Seriennummer: " + x509Cert.getSerialNumber());
//	        System.out.println("Signaturalgorithmus: " + x509Cert.getSigAlgName() + " (" + x509Cert.getSigAlgOID() + ")");
//	        System.out.println("Hashcode: " + x509Cert.hashCode());
//	        x509Cert.checkValidity(new Date());
//	        System.out.println("Gültig von: " + x509Cert.getNotBefore());
//	        System.out.println("Gültig bis: " + x509Cert.getNotAfter());
//	        System.out.println("----------------------------------------------------");
//        }
//        catch (FileNotFoundException e) {
//        	 System.err.println( "Datei gibt es nicht!" );
//        	 System.exit(0);
//        }
//        catch (CertificateException e){
//        	e.getCause();
//       	 	System.err.println( "Fehler beim Zertifikat: kein korrektes Format!" );
//       	 	System.exit(0);
//       }

//	}
}
