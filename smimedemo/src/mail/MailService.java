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

package mail;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.charset.Charset;
import java.util.Properties;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

import main.Config;

import org.apache.commons.codec.binary.Base64;
import org.apache.commons.codec.net.QuotedPrintableCodec;

import texte.ITexte;
import utils.Utils;

public class MailService {
	
	
	/**
	 * Konstruktor 
	 */
	public MailService() {
	
	}


	/**
	 * Erstellt eine MIME-Mail.
	 * @param email
	 * @throws MessagingException
	 * @throws IOException
	 */
	public String createMail1(Mail email, Config config) throws MessagingException, IOException { 
		
		Properties props = new Properties(); 
	    props.put("mail.smtp.host", "mail.java-tutor.com"); 
	    Session session = Session.getDefaultInstance(props); 
	    
		Message msg = new MimeMessage(session); 
//		msg.setHeader("MIME-Version" , "1.0"); 
//		msg.setHeader("Content-Type" , "text/plain"); 
				
		// Absender
		InternetAddress addressFrom = new InternetAddress(email.getAbsender()); 
	    msg.setFrom(addressFrom); 
	    
	    // Empfänger
	    InternetAddress addressTo = new InternetAddress(email.getEmpfaenger()); 
	    msg.setRecipient(Message.RecipientType.TO, addressTo); 
	    
	    msg.setSubject(email.getBetreff());
	    msg.setSentDate(email.getAbsendeDatum());
	    String txt = Utils.toString(email.getText()); 
	    
	    msg.setText(txt);
	    msg.saveChanges();
	    
	    // Mail in Ausgabestrom schreiben
		ByteArrayOutputStream bOut = new ByteArrayOutputStream();
		try{
			msg.writeTo(bOut);
		} catch (IOException e){
			if (config.isTest()) System.out.println("Fehler beim Schreiben der Mail in Schritt 1");
			throw e;
		}
	    return removeMessageId(bOut.toString(Charset.defaultCharset().name()));
	}    

	public static String removeMessageId(String message) {
		String output = "";
		int pos1 = message.indexOf("Message-ID");
	    int pos2 = message.indexOf("\n")+1;
	    output = message.substring(0, pos1);
	    output += (message.substring(pos2));
		return output;
	}


	/**
	 * Erstellt eine kanonisierte MIME-Mail.
	 * @param email
	 * @throws MessagingException
	 * @throws IOException
	 */
	public String createMail2(Mail email, Config config) throws MessagingException, IOException{ 
		
		byte[] mailAsBytes = email.getText();
		int laenge = mailAsBytes.length + getCRLF().length;
		byte[] bOout = new byte[laenge];
		for (int i = 0; i < mailAsBytes.length; i++){
			bOout[i] = mailAsBytes[i];
		}
		
		byte[] neu = getCRLF();
		int counter = 0;
		for (int i = mailAsBytes.length; i < laenge; i++){
			bOout[i] = neu[counter];
			counter++;
		}
		
		email.setText(bOout);
		
		Properties props = new Properties(); 
	    props.put("mail.smtp.host", "mail.java-tutor.com"); 
	    Session session = Session.getDefaultInstance(props); 

		Message msg = new MimeMessage(session); 
//		msg.setHeader("MIME-Version" , "1.0"); 
//		msg.setHeader("Content-Type" , "text/plain"); 
				
		// Absender
		InternetAddress addressFrom = new InternetAddress(email.getAbsender()); 
	    msg.setFrom(addressFrom); 
	    
	    // Empfänger
	    InternetAddress addressTo = new InternetAddress(email.getEmpfaenger()); 
	    msg.setRecipient(Message.RecipientType.TO, addressTo); 
	    
	    msg.setSubject(email.getBetreff());
	    msg.setSentDate(email.getAbsendeDatum());
	    
	    msg.setText(Utils.toString(email.getText()));
	    msg.saveChanges();
/*	    
	    // Erstellen des Content
	    MimeMultipart content = new MimeMultipart("text"); 
		
    	MimeBodyPart part = new MimeBodyPart(); 
    	part.setText(email.getText()); 
    	part.setHeader("MIME-Version" , "1.0"); 
    	part.setHeader("Content-Type" , part.getContentType()); 
		 
    	content.addBodyPart(part);
    	System.out.println(content.getContentType());
		
		Message msg = new MimeMessage(session); 
		msg.setContent(content); 
		msg.setHeader("MIME-Version" , "1.0"); 
		msg.setHeader("Content-Type" , content.getContentType()); 
				
		InternetAddress addressFrom = new InternetAddress(email.getAbsender()); 
	    msg.setFrom(addressFrom); 
	    
	    InternetAddress addressTo = new InternetAddress(email.getEmpfänger()); 
	    msg.setRecipient(Message.RecipientType.TO, addressTo); 
	    
	    msg.setSubject(email.getBetreff());
	    msg.setSentDate(email.getAbsendeDatum()); */
	    
	    //msg.setContent(email.getText(), "text/plain");
	    
	    // Mail in Ausgabestrom schreiben
		ByteArrayOutputStream bOut = new ByteArrayOutputStream();
		try{
			msg.writeTo(bOut);
		} catch (IOException e){
			System.out.println("Fehler beim Schreiben der Mail in Schritt 2");
			throw e;
		}
//		String out = bOut.toString();
//	    int pos1 = out.indexOf("Message-ID");
//	    int pos2 = out.indexOf("@localhost") + 13;
//	    String output = out.subSequence(0, pos1).toString();
//	    output += (out.substring(pos2));

		
	    return removeMessageId(bOut.toString(Charset.defaultCharset().name()));
	}    

	/**
	 * Erstellt eine MIME-Mail inkl. Transfercodierung.
	 * @param email
	 * @throws MessagingException
	 * @throws IOException
	 */
	public String createMail3(Mail email, Config config) throws MessagingException, IOException { 
		
		byte[] mailAsBytes = email.getText();
		byte[] outputBytes;
		
		// Transfercodierung anwenden
		if (config.getTranscodeDescription().equals(Config.BASE64)){
			outputBytes = encodeBase64(mailAsBytes);
		} else if (config.getTranscodeDescription().equals(Config.QP)){
			outputBytes = encodeQuotedPrintable(mailAsBytes);
		} else{
			outputBytes = mailAsBytes;
		}
		email.setText(outputBytes);
		
		Properties props = new Properties(); 
		props.put("mail.smtp.host", "mail.java-tutor.com"); 
	    Session session = Session.getDefaultInstance(props); 
	    
		MimeMessage msg = new MimeMessage(session); 
//		msg.setHeader("MIME-Version" , "1.0"); 
//		msg.setHeader("Content-Type" , "text/plain"); 
				
		// Absender
		InternetAddress addressFrom = new InternetAddress(email.getAbsender()); 
	    msg.setFrom(addressFrom); 
	    
	    // Empfänger
	    InternetAddress addressTo = new InternetAddress(email.getEmpfaenger()); 
	    msg.setRecipient(Message.RecipientType.TO, addressTo); 
	    
	    msg.setSubject(email.getBetreff());
	    msg.setSentDate(email.getAbsendeDatum());
	    
	    msg.setText(Utils.toString(outputBytes));
	    msg.saveChanges();
	    
	    // Mail in Ausgabestrom schreiben
		ByteArrayOutputStream bOut = new ByteArrayOutputStream();
		try{
			msg.writeTo(bOut);
		} catch (IOException e){
			System.out.println("Fehler beim Schreiben der Mail in Schritt 3");
			throw e;
		}
		
//		String out = bOut.toString();
//	    int pos1 = out.indexOf("Message-ID");
//	    int pos2 = out.indexOf("@localhost") + 13;
//	    String output = out.subSequence(0, pos1).toString();
//	    output += (out.substring(pos2));
		
	    				   
	    return removeMessageId(bOut.toString().replaceAll(ITexte.CONTENT, 
	    		"Content-Transfer-Encoding: " + config.getTranscodeDescription()));
	}    
	
	/**
	 * Gibt Carriage Return und Linefeed als Zeichenfolge zurück.
	 * <CR> <LF>
	 * @return
	 */
	private byte[] getCRLF(){
		return "&lt;CR&gt;&lt;LF&gt;".getBytes();
	}
	
	/**
	 * Konvertiert die übergebene Bytes in das Quoted printable Format.
	 * @param input Die Originalbytes
	 * @return In Quoted Printable konvertierte Bytes.
	 */
	public byte[] encodeQuotedPrintable(byte[] input){
		
		QuotedPrintableCodec qp = new QuotedPrintableCodec();
		
		return qp.encode(input);
	}
	
	/**
	 * Konvertiert die übergebene Bytes in das Base64 Format.
	 * @param input Die Originalbytes
	 * @return In base64 konvertierte Bytes.
	 */
	public byte[] encodeBase64(byte[] input){
		Base64 b64 = new Base64();
		return b64.encode(input);
	}

}
