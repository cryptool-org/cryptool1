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
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.security.KeyStore;
import java.security.PrivateKey;
import java.security.cert.CertStore;
import java.security.cert.Certificate;
import java.security.cert.CollectionCertStoreParameters;
import java.security.cert.X509Certificate;
import java.util.Arrays;

import javax.mail.Session;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

import main.Config;

import org.bouncycastle.cms.CMSSignedDataGenerator;
import org.bouncycastle.mail.smime.SMIMESignedGenerator;

import sun.misc.BASE64Decoder;
import utils.Utils;


public class SignedMultiPart extends SignedDataProcessor{
	
	
	private MimeMessage body;

	private boolean valid;
	
	
	/**
	 * Konstruktor
	 */
	public SignedMultiPart(){
		
	}

	/**
	 * @return the Message
	 */
	public MimeMessage getMessage(){
		return body;
	}
	
	/**
	 * @return isValid
	 */
	public boolean isValid(){
		return valid;
	}
	
	/**
	 * Erzeugt eine signierte MIME-Nachricht
	 * @param mail
	 * @param config
	 * @return
	 * @throws Exception
	 */
	public String createSignedMail(KeyStore store, String pword, PrivateKey key, 
			Mail mail, Config config) throws Exception {
		
		KeyStore        credentials;
	    Certificate[]   chain;
	    CertStore       certsAndCRLs; 
	    X509Certificate cert; 
		if (store == null){
			credentials = Utils.createCredentialsAsKeyStore(config);
		    key = (PrivateKey)credentials.getKey(Utils.END_ENTITY_ALIAS, Utils.KEY_PASSWD);
		    chain = credentials.getCertificateChain(Utils.END_ENTITY_ALIAS);
		    certsAndCRLs = CertStore.getInstance("Collection",
		                            new CollectionCertStoreParameters(Arrays.asList(chain)), "BC");
		    cert = (X509Certificate)chain[0];
		} else{
			credentials = store;
			if (pword == null){
				pword = "";
			}
//			    key = (PrivateKey)credentials.getKey(Utils.END_ENTITY_ALIAS, pword.toCharArray());
		    chain = credentials.getCertificateChain(config.getAliasPSE());
		    certsAndCRLs = CertStore.getInstance("Collection",
		                            new CollectionCertStoreParameters(Arrays.asList(chain)), "BC");
		    cert = (X509Certificate)chain[0];
		}
		
		ByteArrayOutputStream bOut = new ByteArrayOutputStream();
		
		// Behandlung Multipart/signed
		if (config.getMimeTyp() == 0){
		    // create the message we want signed
		    MimeBodyPart    bodyPart = new MimeBodyPart();
            bodyPart.setText(Utils.toString(mail.getText()));

	        // create the signed message
	        MimeMultipart multiPart = Utils.createMultipartWithSignature(
	        		key, cert, certsAndCRLs, bodyPart, config.getHashDescription());

	        // create the mail message
	        body = Utils.createMimeMessage(mail.getBetreff(), multiPart, mail.getAbsender(), 
	        		mail.getEmpfaenger(), multiPart.getContentType());
	        
	        body.writeTo(bOut);
		} else {

//				boolean implicit = true;
//				SignedContent sc = new SignedContent(implicit);
			
//	        CMSSignedDataGenerator gen = new CMSSignedDataGenerator();
	        SMIMESignedGenerator smimeGen = new SMIMESignedGenerator();

	        if (config.getHash() == 0){
	        	smimeGen.addSigner(key, cert, CMSSignedDataGenerator.DIGEST_SHA1);
//	        	gen.addSigner(key, cert, CMSSignedDataGenerator.DIGEST_SHA1);
	        } else{
	        	smimeGen.addSigner(key, cert, CMSSignedDataGenerator.DIGEST_MD5);
//	        	gen.addSigner(key, cert, CMSSignedDataGenerator.DIGEST_MD5);
	        }

	        smimeGen.addCertificatesAndCRLs(certsAndCRLs);
	        smimeGen.setContentTransferEncoding(config.getTranscodeDescription());
	        
	        // workaround to get the english date format
	        MimeMessage message = new MimeMessage(Session.getDefaultInstance(System.getProperties()));
	        message.setSentDate(mail.getAbsendeDatum());
	        message.setText("");
	        message.writeTo(bOut);
	        String date = MailService.removeMessageId(bOut.toString());
	        date = date.substring(date.indexOf("Date:"), date.indexOf('\n')-1).substring(date.indexOf(' ')+1);
	      
	        // create the message
	        BASE64Decoder base64dec = new BASE64Decoder();
	        message = new MimeMessage(Session.getDefaultInstance(System.getProperties()));
	        message.setText(Charset.defaultCharset().decode(ByteBuffer.wrap(base64dec.decodeBuffer(Utils.toString(mail.getText())))).toString());
	        message.setHeader("Content-Transfer-Encoding", "base64");
	        
	        // sign the message
	        MimeBodyPart signed = smimeGen.generateEncapsulated(message, "BC");
	        signed.setHeader("From", mail.getAbsender());
	        signed.setHeader("To", mail.getEmpfaenger());
	        signed.setHeader("Subject", mail.getBetreff());
	        signed.setHeader("Date", date);
	        signed.setHeader("MIME-Version", "1.0");
	        signed.setHeader("Message-ID", "12345");

	        bOut.reset();
	        signed.writeTo(bOut);
		}
		
        return bOut.toString(Charset.defaultCharset().name()).replaceAll("Content-Transfer-Encoding: 7bit", 
	    		"Content-Transfer-Encoding: " + config.getTranscodeDescription());
        
    }
	

}
