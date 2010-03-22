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

/**
 * 
 */
package texte;

/**
 * Enthält alle in der GUI anzuzeigenden Texte in deutsch und englisch.
 */
public interface ITexte {

	
	/** Beschreibung der GUI  */
	public static final TranslationText BESCHREIBUNG = new TranslationText(
			"Hier sehen Sie, wie die dynamisch ausgewählten Daten zu einer sicheren E-Mail verarbeitet werden.\n\n" +
			"Die Visualisierung dieser Abläufe beim Versenden einer E-Mail erfolgt in zwei Schritten (Control-Center & Flash-Animation):\n" +
			"- In diesem Steuerfenster entscheiden Sie, ob Sie eine E-Mail verschlüsseln oder signieren wollen, und hier legen Sie die entsprechenden Steuer-Parameter fest.\n" +
			"- Nach dem Drücken des Startknopfes werden diese Vorgänge in einer Flash-Animation visualisiert.\n" +
			"\nSie können mit dem Steuerfenster auch mehrere parallel laufende Flash-Animationen erzeugen. Diese laufen unabhängig vom Steuerfenster.",
			"In this window you can dynamically configure parameters for secure email messaging.\n\n" +
			"The visualisation is then done in two steps (control center & flash animation):\n" +
			"- At the contol center you choose wether to encrypt or sign an email and the appropriate parameters.\n" +
			"- After clicking the start button the chosen procedure is visualized with a flash animation.\n" +
			"\nYou can open more than one flash animation at once with different parameter from the control center.");
	
	/** Überschrift / Headline  */
	public static final TranslationText HEADLINE = new TranslationText(
			"S/MIME Visualisierungs-Control-Center",
			"S/MIME Visualization Control Center");
	
	/** Titel Filedialog  */
	public static final TranslationText TITEL_FILEDIALOG = new TranslationText(
			"E-Mail-Text aus Datei laden",
			"Load message text from file");
	
	/** Start Signieren  */
	public static final TranslationText START_SIGNIEREN = new TranslationText(
			"Signieren starten",
			"Start signing");
	
	/** Start Verschlüsseln  */
	public static final TranslationText START_ENCRYPTING = new TranslationText(
			"Verschlüsselung starten",
			"Start encrypting");
	
	/** Abbrechen  */
	public static final TranslationText ABBRECHEN = new TranslationText(
			"Beenden",
			"Close");
	
	/** Zertifikat geladen für */
	public static final TranslationText ZERTIFIKAT_GEL_FUER = new TranslationText(
			"Zertifikat geladen für ",
			"Certificate loaded for ");
	
	/** Eigene PSE geladen */
	public static final TranslationText PSE_GELADEN = new TranslationText(
			"Eigene PSE geladen",
			"Internal PSE loaded");
	
	/** PSE erfolgreich geladen! */
	public static final TranslationText PSE_ERF_GELADEN = new TranslationText(
			"PSE erfolgreich geladen!",
			"PSE successfully loaded!");
	
	
	
	
	/** Zertifikat des Empfängers auswählen */
	public static final TranslationText ZERTIFIKAT_AUSWAEHLEN = new TranslationText(
			"Zertifikat des Empfängers auswählen",
			"Choose receiver's certificate");
	
	
	 
	
	/** Vorhandenes Zertifikat laden  */
	public static final TranslationText ZERTIFIKAT_LADEN = new TranslationText(
			"Vorhandenes Zertifikat laden",
			"Load personal certificate");
	
	/** Eigenes Zertifikat */
	public static final TranslationText EIG_ZERT = new TranslationText(
			"Eigenes Zertifikat",
			"Personal certificate");
	
	/** Eigene PSE  */
	public static final TranslationText EIG_PSE = new TranslationText(
			"Eigene PSE",
			"Personal PSE");
	
	
	/** Internes Zertifikat  */
	public static final TranslationText INTERN_ZERT = new TranslationText(
			"Internes Zertifikat",
			"Internal certificate");
	
	/** Vorhandene PSE laden  */
	public static final TranslationText PSE_LADEN = new TranslationText(
			"Vorhandene PSE laden",
			"Load existing PSE");
	
	/** PSE aus Datei laden  */
	public static final TranslationText PSE_LADEN_FILE = new TranslationText(
			"PSE aus Datei laden",
			"Load PSE from file");
	
	/** Passwort für die PSE  */
	public static final TranslationText PSE_PASSWORT = new TranslationText(
			"Passwort für die PSE",
			"Password for PSE");
	
	/** Zertifikat aus Datei laden  */
	public static final TranslationText ZERT_LADEN_FILE = new TranslationText(
			"Zertifikat aus Datei laden",
			"Load certificate from file");
	
	/** Zertifikat */
	public static final TranslationText ZERTIFIKAT = new TranslationText(
			"Zertifikat",
			"Certificate");
	

	/** Eigenes Zertifikat geladen*/
	public static final TranslationText ZERTIFIKAT_GELADEN = new TranslationText(
			"Eigenes Zertifikat geladen",
			"Certificate loaded");

	/** Zertifikatsfehler*/
	public static final TranslationText ZERTIFIKAT_FEHLER = new TranslationText(
			"Zertifikatsfehler",
			"Certificate error");

	/** Interne PSE */
	public static final TranslationText INTERNE_PSE = new TranslationText(
			"Interne PSE",
			"Internal PSE");
	
	/** Hier den Text der E-Mail eingeben... */
	public static final TranslationText EMAIL_TEXT = new TranslationText(
			"Hier den Text der E-Mail eingeben...",
			"Enter the message text here...");
	
	
	
	/** Gruppe Signieren / Verschlüsseln */
	public static final TranslationText GRP_SIGNIEREN = new TranslationText(
			"Signieren oder Verschlüsseln",
			"Signing or encrypting");

	/** Gruppe Steuerungsparameter */
	public static final TranslationText GRP_STEUERUNGS_PARAM = new TranslationText(
			"Steuerungsparameter",
			"Control parameters");

	/** Gruppe PSE-Optionen*/
	public static final TranslationText GRP_PSE_OPT = new TranslationText(
			"PSE des Senders auswählen",
			"Choose sender's PSE");

	/** Gruppe Zertifikats-Optionen*/
	public static final TranslationText GRP_CERT_OPT = new TranslationText(
			"Zertifikat des Empfängers auswählen",
			"Choose receiver's certificate");

	/** Button E-Mailtext laden  */
	public static final TranslationText BUTTON_NACHTEXT_LADEN = new TranslationText(
			"Nachrichtentext aus Datei laden",
			"Load message text from file");

	/** Bitte geben Sie das Passwort der PSE ein  */
	public static final TranslationText EINGABE_PASSWORT = new TranslationText(
			"Bitte geben Sie das Passwort der PSE ein",
			"Please enter the password");
	
	/** Bitte geben Sie den Alias für den privaten Schlüssel ein */
	public static final TranslationText EINGABE_ALIAS = new TranslationText(
			"Bitte geben Sie den Alias an, mit dem der private Schlüssel verknüpft ist:",
			"Please enter the alias which is associated with the private key:");
	
	
	/** Alias eingeben */
	public static final TranslationText ALIAS= new TranslationText(
			"Alias eingeben",
			"Enter alias");

	/** Button Hilfe */
	public static final TranslationText BUTTON_HELP= new TranslationText(
			"Hilfe",
			"Help");
	
	
	/** Nachrichtentext */
	public static final TranslationText NACHRICHTENTEXT = new TranslationText(
			"Text der Nachricht",
			"Text of the message");
	
	
	/** Hash-Funktion  */
	public static final TranslationText HASH_FUNKT = new TranslationText(
			"Hash-Funktion:",
			"Hash function:");

	/** Signatur Algorithmus  */
	public static final TranslationText SIG_ALG = new TranslationText(
			"Signatur-Algorithmus:",
			"Signature algorithm:");
	
	/** MIME-Type  */
	public static final TranslationText MIME_TYP = new TranslationText(
			"MIME-Typ:",
			"MIME type:");
	
	/** Transfer-Codierung */
	public static final TranslationText TRANS_CODE = new TranslationText(
			"Transferkodierung:",
			"transfer encoding:");

	/** E-Mail-Adresse */
	public static final TranslationText EMAIL_ADRESSE_TO = new TranslationText(
			"Empfänger:",
			"Receiver:");

	/** E-Mail-Adresse */
	public static final TranslationText EMAIL_ADRESSE_FROM = new TranslationText(
			"Absender:",
			"Sender:");

	/** E-Mail-Adresse */
	public static final TranslationText EMAIL_ADRESSE_SUBJECT = new TranslationText(
			"Betreff:",
			"Subject:");

	/** Verschlüsselungsverfahren */
	public static final TranslationText VERSCHL_VERFAHREN = new TranslationText(
			"Verschlüsselungsverfahren: ",
			"Encrypting algorithm :");

	
	/** Verschlüsselungsverfahren */
	public static final TranslationText TT_VERSCHL_VERFAHREN = new TranslationText(
			"Verschlüsselungsverfahren wählen",
			"Choose encrypting algorithm");
	
	
	
	/** Signieren */
	public static final TranslationText SIGNIEREN = new TranslationText(
			"Signieren",
			"Signing");
	
	/** Verschlüsseln */
	public static final TranslationText VERSCHLUESSELN = new TranslationText(
			"Verschlüsseln",
			"Encrypting");
	
	/** Alle Dateien */
	public static final TranslationText ALLE_DATEIEN = new TranslationText(
			"Alle Dateien (*.*)",
			"All files (*.*)");
	
	/** Text-Dateien */
	public static final TranslationText TEXT_DATEIEN = new TranslationText(
			"Textdatei (*.txt)",
			"Text file (*.txt)");
	
	
	/** Tooltip Gruppe Signieren */
	public static final TranslationText TT_GRP_SIG_VER = new TranslationText(
			"Hier erfolgt die Auswahl zwischen Signieren und Verschlüsseln",
			"Here you can make a choice between signing or encrypting");

	/** Tooltip Gruppe  */
	public static final TranslationText TT_GRP_CERT_OPT = new TranslationText(
			"Hier kann ausgewählt werden, ob ein Beispielzertifikat oder ein eigenes benutzt werden soll",
			"Here you can make a choice between a personal certificate or an internal certificate");
	
	/** Tooltip Gruppe PSE-Optionen */
	public static final TranslationText TT_GRP_PSE_OPT = new TranslationText(
			"Hier kann ausgewählt werden, ob eine Beispiel-PSE oder eine Eigene benutzt werden soll",
			"Here you can make a choice between a personal PSE or an internal PSE");
	
	/** Tooltip Gruppe  */
	public static final TranslationText TT_GRP_ST_PARAM = new TranslationText(
			"Auswahl der Steuerungsparameter",
			"Choice of control parameters");

	/** Tooltip Gruppe  */
	public static final TranslationText TT_GRP_NACH_TEXT = new TranslationText(
			"Hier den Text der E-Mail eingeben",
			"Here you can enter the message text");
	
	/** Tooltip Gruppe  */
	public static final TranslationText TT_GRP_NACH_TEXT_MAX = new TranslationText(
			"Hinweis: In dieser Demo kann das Nachrichtenfeld maximal 50 Zeichen aufnehmen. Beim Laden aus einer Datei wird nach 50 Zeichen abgeschnitten.",
			"Note: In this demonstration the text field can only handle 50 characters, longer texts will be shortened.");

	/** Tooltip Tab Signieren  */
	public static final TranslationText TT_TAB_SIGNIEREN = new TranslationText(
			"Hier werden alle Einstellungen zum Signieren festgelegt",
			"Here you can modify settings for signing");
	
	/** Tooltip Tab Signieren  */
	public static final TranslationText TT_TAB_ENCRYPT = new TranslationText(
			"Hier werden alle Einstellungen zum Verschlüsseln festgelegt",
			"Here you can modify settings for encrypting");
	
	/** Tooltip Hash-Funktion */
	public static final TranslationText TT_HASH = new TranslationText(
			"Hash-Funktion wählen",
			"Choose a hash function");
	
	/** Tooltip Signaturalgorithmus */
	public static final TranslationText TT_SIG_ALG = new TranslationText(
			"Algorithmus zum Signieren wählen",
			"Choose encryption algorithm");

	/** Tooltip Transfercodierung */
	public static final TranslationText TT_TRANS_CODE = new TranslationText(
			"Transferkodierung wählen",
			"Choose transfer encoding");

	/** Tooltip MIME-Typ */
	public static final TranslationText TT_MIME_TYP = new TranslationText(
			"MIME-Typ der E-Mail wählen (Multipart empfohlen)",
			"Choose MIME type of the message (multipart recommended)");

	/** Tooltip E-Mail-Adresse */
	public static final TranslationText TT_EMAIL = new TranslationText(
			"Hier E-Mail-Adresse des Empfängers eingeben",
			"Here you can enter the receiver's address");
	
	/** Tooltip E-Mail-Adresse */
	public static final TranslationText TT_SENDER_EMAIL = new TranslationText(
			"Hier E-Mail-Adresse des Absenders eingeben",
			"Here you can enter the sender's address");
	
	/** Tooltip E-Mail-Adresse */
	public static final TranslationText TT_SUBJECT_EMAIL = new TranslationText(
			"Hier den Betreff eingeben",
			"Here you can enter the subject");
	
	/** Titel Tabreiter Signieren  */
	public static final TranslationText TAB_SIGNIEREN = new TranslationText(
			"Zum Signieren",
			"For signing");

	/** Tooltip Tabreiter Verschlüsseln  */
	public static final TranslationText TAB_VERSCHLUESSELN = new TranslationText(
			"Zum Verschlüsseln",
			"For encrypting");

	/** Tooltip Button Start  */
	public static final TranslationText TT_BUTTON_START = new TranslationText(
			"Startet die Visualisierung",
			"Start visualization");
	
	/** Tooltip Button Abbrechen  */
	public static final TranslationText TT_BUTTON_ABBRECHEN = new TranslationText(
			"Beendet das Programm",
			"Shutdown application");
	
	/** Tooltip Button Hilfe  */
	public static final TranslationText TT_BUTTON_HELP = new TranslationText(
			"Hilfe",
			"Help");
	
	public static final TranslationText TT_BUTTON_FILEDIALOG = new TranslationText(
			"Öffnet einen Dialog zum Auswählen eines Zertifikats aus einer Datei.\nWird " + 
			"kein Zertifikat aus einer externen Datei geladen, wird ein intern generiertes Zertifikat benutzt.",
			"Opens an dialog for choosing a certificate from a file. If no certificate was chosen,\n"
			+ " an internal certificate will be used.");
	

	public static final TranslationText TT_BUTTON_FILEDIALOG2 = new TranslationText(
			"Öffnet einen Dialog zum Auswählen einer PSE aus einer Datei.\nWird " + 
			"keine PSE aus einer externen Datei geladen, wird eine intern generierte PSE benutzt.",
			"Opens an dialog for choosing a PSE from a file. If no PSE was chosen,\n"
			+ " an internal PSE will be used.");
	
	
	/** Fehler: Datei nicht gefunden  */
	public static final TranslationText ERR_FILE_NOT_FOUND = new TranslationText(
			"Datei nicht gefunden!",
			"File not found!");
	
	/** Fehler: Dateifehler */
	public static final TranslationText ERR_FILE_ERROR = new TranslationText(
			"Dateifehler",
			"File error");
	
	/** Fehler: Allgemeiner Fehler */
	public static final TranslationText ERR_ERROR = new TranslationText(
			"Fehler",
			"Error");

	/** Fehler: Fehler beim öffnen */
	public static final TranslationText ERR_OPEN_PSE = new TranslationText(
			"Fehler beim Öffnen der PSE.",
			"Error while opening PSE.");

	
	/** Fehler: Unbekannter Fehler */
	public static final TranslationText ERR_UNKNOWN = new TranslationText(
			"Unbekannter Fehler",
			"Unknown error");
	
	/** Fehler: Kein X.509-Zertifikat! */
	public static final TranslationText ERR_X509 = new TranslationText(
			"Kein X.509-Zertifikat!",
			"No X.509 certificate!");
	

	/** Abbruch! */
	public static final TranslationText ABBRUCH = new TranslationText(
			"Abbruch!",
			"Abort!");


	/** Fehler beim Laden des Bildes! */
	public static final TranslationText ERR_IMAGE = new TranslationText(
			"Fehler beim Laden des Bildes!",
			"Error while loading image!");

	/** Privater Schlüssel nicht vorhanden! */
	public static final TranslationText ERR_PRIVATEKEY = new TranslationText(
			"Privater Schlüssel nicht vorhanden!",
			"Private key not available!");
	
	
	/** Fehler beim Ausführen der Flash-Animation! */
	public static final TranslationText ERR_FLASH = new TranslationText(
			"Fehler beim Ausführen der Flash-Animation!",
			"Error while running flash animation!");

	/** Fehler beim Parsen */
	public static final TranslationText ERR_PARSING = new TranslationText(
			"Fehler beim Parsen!",
			"Error while parsing!");
	
	/** Fehler beim verschlüsseln */
	public static final TranslationText ERR_ENCRYPT = new TranslationText(
			"Verschlüsselung konnte nicht ausgeführt werden",
			"Encryption could not be performed");
	
	/** Fehler beim laden des Providers */
	public static final TranslationText ERR_ENCRYPT_PROVIDER = new TranslationText(
			"Verschlüsselungsanbieter nicht gefunden!",
			"Encryption provider not found!");
	
	/** Fehler beim generieren von SMIME*/
	public static final TranslationText ERR_ENCRYPT_SMIME = new TranslationText(
			"Fehler beim erstellen des S/MIME Anhangs!",
			"Error generating S/MIME mail extension!");
	
	/** Fehler beim laden des Algorithmus*/
	public static final TranslationText ERR_ENCRYPT_ALGORITHM = new TranslationText(
			"Verschlüsselungsalgorithmus nicht gefunden!",
			"Encryption algorithm not found!");
	
	/** Fehler bei der Erstellung der eMail*/
	public static final TranslationText ERR_ENCRYPT_MAIL = new TranslationText(
			"Fehler beim erstellen der Mail!",
			"Error generating mail!");
	
	/** Fehler beim initialisieren der JCE*/
	public static final TranslationText ERR_ENCRYPT_JCE = new TranslationText(
			"Die \"Java Unlimited Strength Jurisdiction Policy\" ist nicht installiert!\n" +
			"Um starke Verschlüsselungsfunktionen unter Java zu verwenden, muss diese Policy installiert sein.\n" +
			"Die dynamische Visualisierung für sichere E-Mail-Verschlüsselung nutzt diese starken Verschlüsselungsverfahren.\n\n" +
			"Die benötigten Policy-Dateien finden Sie unter \"http://java.sun.com/javase/downloads/index.jsp\".\n" +
			"Details zur Installation erhalten Sie in der CrypTool-Onlinehilfe, indem Sie den Menüpunkt \"Einzelverfahren \\ Protokolle \\ Sichere E-Mail mit S/MIME\" markieren (ohne ihn anzuklicken) und F1 drücken. Dort finden Sie unter \"Bemerkung 1\" eine genaue Beschreibung des nötigen Vorgehens.\n\n" +
			"Die Anwendung muss danach neu gestartet werden.",
			"The \"Java Unlimited Strength Jurisdiction Policy\" is not installed!\n" +
			"This policy is needed in order to apply strong encryption. You have to install the policy files when selecting to encrypt emails.\n" +
			"The visualisation of secure email encryption uses strong encryption methods.\n\n" +
			"The required policy-files can be found at \"http://java.sun.com/javase/downloads/index.jsp\".\n" +
			"Detailled instructions on how to install these files can be found in the CrypTool online help system by highlighting \"Indiv. Procedures \\ Protocols \\ Secure E-Mail with S/MIME\" in CrypTool and pressing F1. Step-by-step instructions are provided in section \"Remark 1\".\n\n" +
			"The application has to be restarted afterwards.");
	
	/**
	 * Content-Transfer-Encoding: 7bit
	 */
	public static final String CONTENT = "Content-Transfer-Encoding: 7bit";
			

	
	
}
