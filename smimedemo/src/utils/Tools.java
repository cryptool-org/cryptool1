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

package utils;


import java.io.IOException;
import java.io.Reader;
import java.math.BigInteger;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.KeyStore;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.cert.Certificate;
import java.security.cert.X509Certificate;
import java.util.Date;
import java.util.Properties;

import javax.mail.Address;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import javax.security.auth.x500.X500Principal;
import javax.security.auth.x500.X500PrivateCredential;

import main.Config;

import org.bouncycastle.asn1.x509.BasicConstraints;
import org.bouncycastle.asn1.x509.KeyUsage;
import org.bouncycastle.asn1.x509.X509Extensions;
import org.bouncycastle.asn1.x509.X509Name;
import org.bouncycastle.x509.X509V1CertificateGenerator;
import org.bouncycastle.x509.X509V3CertificateGenerator;
import org.bouncycastle.x509.extension.AuthorityKeyIdentifierStructure;
import org.bouncycastle.x509.extension.SubjectKeyIdentifierStructure;


public class Tools {

	
	protected static final int BLKSIZE = 8196;
	private static final int VALIDITY_PERIOD = 7 * 24 * 60 * 60 * 1000; // one week
	public static char[] KEY_PASSWD = "keyPassword".toCharArray();

	
    /**
     * Create a MIME message from using the passed in content.
     * @author David Hook
     */
    public static MimeMessage createMimeMessage(
        String subject, Object content, String contentType) throws MessagingException {
        
    	Properties props = System.getProperties();
        Session session = Session.getDefaultInstance(props, null);

        Address fromUser = new InternetAddress("\"Eric H. Echidna\"<eric@bouncycastle.org>");
        Address toUser = new InternetAddress("example@bouncycastle.org");

        MimeMessage message = new MimeMessage(session);
        
        message.setFrom(fromUser);
        message.setRecipient(Message.RecipientType.TO, toUser);
        message.setSubject(subject);
        message.setContent(content, contentType);
        message.saveChanges();
        
        return message;
    }
   
    
    /**
     * Read text from a txt-file. 
     * @param reader is
     * @return String. Content of the file 
     * @author David Hook
     */
    public static String readerToString(Reader is) throws IOException{
    	StringBuffer sb = new StringBuffer();
    	char[] b = new char[BLKSIZE];
    	int n;
    	while ((n = is.read(b))>0){
    		sb.append(b,0,n);
    	}
    	    	
    	return sb.toString();
    	
    }
    
    /**
     * Convert a byte array of 8 bit characters into a String.
     * 
     * @param bytes the array containing the characters
     * @param length the number of bytes to process
     * @return a String representation of bytes
     */
    public static String toString(
        byte[] bytes,
        int    length){
        char[]	chars = new char[length];
        
        for (int i = 0; i != chars.length; i++){
            chars[i] = (char)(bytes[i] & 0xff);
        }
        
        return new String(chars);
    }

    /**
     * Create a random 1024 bit RSA key pair
     * @return KeyPair
     */
    public static KeyPair generateRSAKeyPair()
        throws Exception{
        KeyPairGenerator  kpGen = KeyPairGenerator.getInstance("RSA", "BC");
    
        kpGen.initialize(1024, new SecureRandom());
    
        return kpGen.generateKeyPair();
	}

    /**
     * Generate a sample V1 certificate to use as a CA root certificate
     * @author David Hook
     */
    public static X509Certificate generateRootCert(KeyPair pair)
        throws Exception
	{
	    X509V1CertificateGenerator  certGen = new X509V1CertificateGenerator();
	
	    certGen.setSerialNumber(BigInteger.valueOf(1));
	    certGen.setIssuerDN(new X509Name("CN=Test CA Certificate"));
	    certGen.setNotBefore(new Date(System.currentTimeMillis()));
	    certGen.setNotAfter(new Date(System.currentTimeMillis() + VALIDITY_PERIOD));
	    certGen.setSubjectDN(new X509Name("CN=Test CA Certificate"));
	    certGen.setPublicKey(pair.getPublic());
	    certGen.setSignatureAlgorithm("SHA1WithRSAEncryption");
	
	    return certGen.generate(pair.getPrivate(), "BC");
	}
    
    /**
     * Generate a sample V3 certificate to use as an intermediate CA certificate
     * @author David Hook
     */
    public static X509Certificate generateIntermediateCert(PublicKey intKey, PrivateKey caKey, X509Certificate caCert)
        throws Exception
    {
        X509V3CertificateGenerator  certGen = new X509V3CertificateGenerator();

        certGen.setSerialNumber(BigInteger.valueOf(1));
        certGen.setIssuerDN(new X509Name(caCert.getSubjectX500Principal().getName()));
        certGen.setNotBefore(new Date(System.currentTimeMillis()));
        certGen.setNotAfter(new Date(System.currentTimeMillis() + VALIDITY_PERIOD));
        certGen.setSubjectDN(new X509Name(new X500Principal("CN=Test Intermediate Certificate").getName()));
        certGen.setPublicKey(intKey);
        certGen.setSignatureAlgorithm("SHA1WithRSAEncryption");
    
        certGen.addExtension(X509Extensions.AuthorityKeyIdentifier, false, new AuthorityKeyIdentifierStructure(caCert));
        certGen.addExtension(X509Extensions.SubjectKeyIdentifier, false, new SubjectKeyIdentifierStructure(intKey));
        certGen.addExtension(X509Extensions.BasicConstraints, true, new BasicConstraints(0));
        certGen.addExtension(X509Extensions.KeyUsage, true, new KeyUsage(KeyUsage.digitalSignature | KeyUsage.keyCertSign | KeyUsage.cRLSign));

        return certGen.generate(caKey, "BC");
    }
    
    /**
     * Generate a sample V3 certificate to use as an end entity certificate
     * @author David Hook
     */
    public static X509Certificate generateEndEntityCert(PublicKey entityKey, PrivateKey caKey, X509Certificate caCert)
	    throws Exception
	{
        X509V3CertificateGenerator  certGen = new X509V3CertificateGenerator();

        certGen.setSerialNumber(BigInteger.valueOf(1));
        certGen.setIssuerDN(new X509Name(caCert.getSubjectX500Principal().getName()));
        certGen.setNotBefore(new Date(System.currentTimeMillis()));
        certGen.setNotAfter(new Date(System.currentTimeMillis() + VALIDITY_PERIOD));
        certGen.setSubjectDN(new X509Name(new X500Principal("CN=Test End Certificate").getName()));
        certGen.setPublicKey(entityKey);
        certGen.setSignatureAlgorithm("SHA1WithRSAEncryption");
        
        certGen.addExtension(X509Extensions.AuthorityKeyIdentifier, false, new AuthorityKeyIdentifierStructure(caCert));
        certGen.addExtension(X509Extensions.SubjectKeyIdentifier, false, new SubjectKeyIdentifierStructure(entityKey));
        certGen.addExtension(X509Extensions.BasicConstraints, true, new BasicConstraints(false));
        certGen.addExtension(X509Extensions.KeyUsage, true, new KeyUsage(KeyUsage.digitalSignature | KeyUsage.keyEncipherment));

        return certGen.generate(caKey, "BC");
	}
    
    public static KeyStore createCredentials(Config config) throws Exception {
    KeyStore store = KeyStore.getInstance("JKS");

    store.load(null, null);
    
    X500PrivateCredential    rootCredential = Utils.createRootCredential(null);
    X500PrivateCredential    interCredential = Utils.createIntermediateCredential(rootCredential.getPrivateKey(), rootCredential.getCertificate());
    X500PrivateCredential    endCredential = Utils.createEndEntityCredential(interCredential.getPrivateKey(), interCredential.getCertificate(), config);
    
    store.setCertificateEntry(rootCredential.getAlias(), rootCredential.getCertificate());
    store.setKeyEntry(endCredential.getAlias(), endCredential.getPrivateKey(), KEY_PASSWD, 
            new Certificate[] { endCredential.getCertificate(), interCredential.getCertificate(), rootCredential.getCertificate() });

    return store;
    }
    
}
