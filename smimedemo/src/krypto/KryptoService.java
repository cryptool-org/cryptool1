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
 * 22.02.2008
 */
package krypto;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.math.BigInteger;
import java.nio.charset.Charset;
import java.security.InvalidKeyException;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.PrivateKey;
import java.security.SecureRandom;
import java.security.cert.CertificateEncodingException;
import java.security.cert.X509Certificate;
import java.util.Date;
import java.util.Properties;

import javax.crypto.SecretKey;
import javax.mail.Address;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.security.auth.x500.X500Principal;

import mail.Mail;
import mail.MailService;
import mail.SignedMultiPart;
import main.Config;

import org.bouncycastle.asn1.x509.BasicConstraints;
import org.bouncycastle.asn1.x509.ExtendedKeyUsage;
import org.bouncycastle.asn1.x509.GeneralName;
import org.bouncycastle.asn1.x509.GeneralNames;
import org.bouncycastle.asn1.x509.KeyPurposeId;
import org.bouncycastle.asn1.x509.KeyUsage;
import org.bouncycastle.asn1.x509.X509Extensions;
import org.bouncycastle.asn1.x509.X509Name;
import org.bouncycastle.mail.smime.SMIMEEnvelopedGenerator;
import org.bouncycastle.mail.smime.SMIMEException;
import org.bouncycastle.x509.X509V3CertificateGenerator;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.swt.widgets.Shell;

import texte.ITexte;
import utils.Utils;

/**
 * Bietet einige kryptographische Services an.
 */
public class KryptoService {


	/**
	 * Signiert eine E-Mail unter Berücksichtigung der angegebenen Konfiguration.
	 * @param mail
	 * @param config
	 * @param key
	 * @return
	 */
	public static String signMail(Mail mail, Config config, PrivateKey key, String pword) throws Exception{
		SignedMultiPart signed = new SignedMultiPart();
		if (key != null){
			return MailService.removeMessageId(signed.createSignedMail(
					KeyStoreUtils.createKeyStore(new FileInputStream(config.getFilenamePSE()), pword), 
					pword, key, mail, config));
		} else {
			return MailService.removeMessageId(signed.createSignedMail(null, null, key, mail, config));
		}
	}


	/**
	 * Verschlüsselt eine E-Mail unter Berücksichtigung der angegebenen Konfiguration. 
	 * @param mail
	 * @param config
	 * @param cert
	 * @return
	 */
	public static String encryptMail(Mail mail, Config config, X509Certificate cert, String pword){
		try{
			SMIMEEnvelopedGenerator gen = new SMIMEEnvelopedGenerator();
			gen.addKeyTransRecipient(cert);
			Properties props = new Properties(); 
		    props.put("mail.smtp.host", "mail.java-tutor.com"); 
		    Session session = Session.getDefaultInstance(props); 
		    MimeMessage body = new MimeMessage(session);
			
			// set Text
			MimeBodyPart msg = new MimeBodyPart();
			msg.setText(Utils.toString(mail.getText()));

			// set from
			Address fromUser = new InternetAddress(mail.getAbsender());
			body.setFrom(fromUser);
			
			// set to
			Address toUser = new InternetAddress(mail.getEmpfaenger());
			body.setRecipient(Message.RecipientType.TO, toUser);
			
			// set subject
			body.setSubject(mail.getBetreff());
			
			// set send date
			body.setSentDate(mail.getAbsendeDatum());
			
			// select algorithm
			String algorithm = SMIMEEnvelopedGenerator.AES256_CBC;
			if(config.getEncrAlg()==1)
				algorithm = SMIMEEnvelopedGenerator.DES_EDE3_CBC;
			
			// apply smime
			MimeBodyPart mp = gen.generate(msg, algorithm, "BC");
			body.setContent(mp.getContent(), mp.getContentType());
			
			body.saveChanges();
			
			ByteArrayOutputStream out = new ByteArrayOutputStream();
			body.writeTo(out);
			return MailService.removeMessageId(out.toString(Charset.defaultCharset().name()));
		}
		catch (MessagingException e) {
			MessageBox box = new MessageBox(new Shell(), SWT.OK | SWT.ICON_ERROR);
			box.setText(ITexte.ERR_ENCRYPT.getText(config.getSprache()));
			box.setMessage(ITexte.ERR_ENCRYPT_MAIL.getText(config.getSprache()));
			box.open();
		} catch (NoSuchAlgorithmException e) {
			MessageBox box = new MessageBox(new Shell(), SWT.OK | SWT.ICON_ERROR);
			box.setText(ITexte.ERR_ENCRYPT.getText(config.getSprache()));
			box.setMessage(ITexte.ERR_ENCRYPT_ALGORITHM.getText(config.getSprache()));
			box.open();
		} catch (NoSuchProviderException e) {
			MessageBox box = new MessageBox(new Shell(), SWT.OK | SWT.ICON_ERROR);
			box.setText(ITexte.ERR_ENCRYPT.getText(config.getSprache()));
			box.setMessage(ITexte.ERR_ENCRYPT_PROVIDER.getText(config.getSprache()));
			box.open();
		} catch (SMIMEException e) {
			MessageBox box = new MessageBox(new Shell(), SWT.OK | SWT.ICON_ERROR);
			box.setText(ITexte.ERR_ENCRYPT.getText(config.getSprache()));
			box.setMessage(ITexte.ERR_ENCRYPT_SMIME.getText(config.getSprache()));
			box.open();
		} catch (Exception e) {
			MessageBox box = new MessageBox(new Shell(), SWT.OK | SWT.ICON_ERROR);
			box.setText(ITexte.ERR_ENCRYPT.getText(config.getSprache()));
			box.setMessage(ITexte.ERR_ENCRYPT_JCE.getText(config.getSprache()));
			box.open();
		} 
		return null;
	}


	/**
	 * Holt den privaten Schlüssel aus einer PSE.
	 * @param fileName
	 * @param pword
	 * @return the Privatekey
	 * @throws Exception
	 */
	public static PrivateKey getSecretKeyFromPSE(String alias, String fileName, char[] pword) throws Exception{
		KeyStore store = KeyStore.getInstance("PKCS12", "BC");
		store.load(new FileInputStream(fileName), pword);
//		Enumeration<String> obj = store.aliases();
//		 for (; obj.hasMoreElements(); ) {
//	            String a = (String)obj.nextElement();
//	            if(store.isKeyEntry(a))
//	            	System.out.println(a);
//	            if(store.isCertificateEntry(a))
//	            	System.out.println(a);
//			
//		}
		PrivateKey key = (PrivateKey)store.getKey(alias, pword);

		return key;
	}
	
	/**
	 * Holt das Zertifikat aus einer PSE.
	 * @param fileName
	 * @param pword
	 * @return the certificate
	 * @throws KeyStoreException 
	 * @throws Exception
	 */
	public static X509Certificate getCertificateFromPSE(String alias, String fileName, char[] pword) throws Exception {
		KeyStore store = KeyStore.getInstance("PKCS12", "BC");
		store.load(new FileInputStream(fileName), pword);
		return (X509Certificate) store.getCertificate(alias);
	}

	/**
	 * Generiert eine PSE.
	 * @param fileName
	 * @param pword
	 * @return
	 * @throws Exception
	 */
	public static SecretKey generatePSE(Config config) throws Exception{
		PrivateKey key = Utils.createCredentials(config);
		if (key instanceof SecretKey){
			return (SecretKey)key;
		} else {
			return null;
		}
	}


	/**
	 * Erzeugt ein x509 v3-Zertifikat, das 1 Tag lang gültig ist.
	 * @return
	 * @throws Exception
	 */
	public static X509Certificate generateCertificate(String algorithm){
		X509V3CertificateGenerator certGen = new X509V3CertificateGenerator();
		KeyPair pair = null;

		try {
			pair = generateKeyPair(algorithm, 1024);
		} catch (Exception e){
			try {
				pair = generateKeyPair(algorithm, 512);
			} catch (Exception e2){
				System.out.println(e2.getMessage());
			}
		}

		long day = 24 * 60 * 60 * 1000;  // 1 Tag gültig

		certGen.setSerialNumber(BigInteger.valueOf(System.currentTimeMillis()));
		certGen.setIssuerDN(new X509Name(new X500Principal("CN=Test Certificate").getName()));
		certGen.setNotBefore(new Date(System.currentTimeMillis() - 500000));
		certGen.setNotAfter(new Date(System.currentTimeMillis() + day));
		certGen.setSubjectDN(new X509Name(new X500Principal("CN=Test Certificate").getName()));
		certGen.setPublicKey(pair.getPublic());
		certGen.setSignatureAlgorithm("SHA256WithRSAEncryption");

		certGen.addExtension(X509Extensions.BasicConstraints, true, new BasicConstraints(false));

		certGen.addExtension(X509Extensions.KeyUsage, true, new KeyUsage(KeyUsage.digitalSignature | KeyUsage.keyEncipherment));

		certGen.addExtension(X509Extensions.ExtendedKeyUsage, true, new ExtendedKeyUsage(KeyPurposeId.id_kp_serverAuth));

		certGen.addExtension(X509Extensions.SubjectAlternativeName, false, new GeneralNames(new GeneralName(GeneralName.rfc822Name, "test@test.test")));

		X509Certificate cert= null;
		try{
			cert = certGen.generate(pair.getPrivate(), "BC");
		} catch (CertificateEncodingException e){
			System.out.println("CertificateEncodingException");
		} catch (InvalidKeyException e2){
			System.out.println("InvalidKeyException: " + e2.getMessage());
		} catch (Exception e3){
			// do nothing
		}

		return cert;

	}

	/**
	 * Create a random 1024 bit RSA key pair
	 */
	protected static KeyPair generateKeyPair(String algorithm, int keysize)throws Exception{
		KeyPairGenerator kpGen = null;
		try{
			kpGen = KeyPairGenerator.getInstance(algorithm, "BC");
		} catch (NoSuchAlgorithmException e){
			try{
				kpGen = KeyPairGenerator.getInstance("RSA", "BC");
			} catch (Exception e2){

			}
		} catch (NoSuchProviderException e){
			// BC-Fehler
		}

		kpGen.initialize(keysize, new SecureRandom());

		return kpGen.generateKeyPair();
	}
}
