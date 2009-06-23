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

import java.math.BigInteger;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.KeyStore;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.cert.CertPathBuilder;
import java.security.cert.CertStore;
import java.security.cert.Certificate;
import java.security.cert.PKIXBuilderParameters;
import java.security.cert.PKIXCertPathBuilderResult;
import java.security.cert.TrustAnchor;
import java.security.cert.X509CertSelector;
import java.security.cert.X509Certificate;
import java.util.Collections;
import java.util.Date;
import java.util.Properties;

import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.mail.Address;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.security.auth.x500.X500Principal;
import javax.security.auth.x500.X500PrivateCredential;

import krypto.KeyStoreUtils;
import main.Config;

import org.bouncycastle.asn1.ASN1EncodableVector;
import org.bouncycastle.asn1.cms.AttributeTable;
import org.bouncycastle.asn1.smime.SMIMECapabilitiesAttribute;
import org.bouncycastle.asn1.smime.SMIMECapability;
import org.bouncycastle.asn1.smime.SMIMECapabilityVector;
import org.bouncycastle.asn1.smime.SMIMEEncryptionKeyPreferenceAttribute;
import org.bouncycastle.asn1.x509.BasicConstraints;
import org.bouncycastle.asn1.x509.KeyUsage;
import org.bouncycastle.asn1.x509.X509Extensions;
import org.bouncycastle.asn1.x509.X509Name;
import org.bouncycastle.mail.smime.SMIMESignedGenerator;
import org.bouncycastle.mail.smime.SMIMEUtil;
import org.bouncycastle.x509.X509V3CertificateGenerator;
import org.bouncycastle.x509.extension.AuthorityKeyIdentifierStructure;
import org.bouncycastle.x509.extension.SubjectKeyIdentifierStructure;



public class Utils {

	private static String	digits = "0123456789abcdef";
    private static final int VALIDITY_PERIOD = 7 * 24 * 60 * 60 * 1000; // one week
    public static String ROOT_ALIAS = "root";
    public static String INTERMEDIATE_ALIAS = "intermediate";
    public static String END_ENTITY_ALIAS = "end";
    public static char[] KEY_PASSWD = "keyPassword".toCharArray();
//    private static final long SerialVersionUID = 0;
    
    /**
     * Create a KeyStore containing the a private credential with
     * certificate chain and a trust anchor.
     */
    public static PrivateKey createCredentials(Config config) throws Exception {
        KeyStore store = KeyStoreUtils.createKeyStore();

        store.load(null, null);
        
        X500PrivateCredential    rootCredential = Utils.createRootCredential(config);
        X500PrivateCredential    interCredential = Utils.createIntermediateCredential(rootCredential.getPrivateKey(), rootCredential.getCertificate());
        X500PrivateCredential    endCredential = Utils.createEndEntityCredential(interCredential.getPrivateKey(), interCredential.getCertificate(), config);
        
        store.setCertificateEntry(rootCredential.getAlias(), rootCredential.getCertificate());
        store.setKeyEntry(endCredential.getAlias(), endCredential.getPrivateKey(), KEY_PASSWD, 
                new Certificate[] { endCredential.getCertificate(), interCredential.getCertificate(), rootCredential.getCertificate() });

        return endCredential.getPrivateKey();
    }
    
    /**
     * Create a KeyStore containing the a private credential with
     * certificate chain and a trust anchor.
     */
    public static KeyStore createCredentialsAsKeyStore(Config config) throws Exception {
        
    	KeyStore store = KeyStoreUtils.createKeyStore();

        store.load(null, null);
        
        X500PrivateCredential    rootCredential = Utils.createRootCredential(config);
        X500PrivateCredential    interCredential = Utils.createIntermediateCredential(rootCredential.getPrivateKey(), rootCredential.getCertificate());
        X500PrivateCredential    endCredential = Utils.createEndEntityCredential(interCredential.getPrivateKey(), interCredential.getCertificate(), config);
        
        store.setCertificateEntry(rootCredential.getAlias(), rootCredential.getCertificate());
        store.setKeyEntry(endCredential.getAlias(), endCredential.getPrivateKey(), KEY_PASSWD, 
                new Certificate[] { endCredential.getCertificate(), interCredential.getCertificate(), rootCredential.getCertificate() });

        return store;
    }
    /**
     * Build a path using the given root as the trust anchor, and the passed
     * in end constraints and certificate store.
     * <p>
     * Note: the path is built with revocation checking turned off.
     */
    public static PKIXCertPathBuilderResult buildPath(
        X509Certificate  rootCert,
        X509CertSelector endConstraints,
        CertStore        certsAndCRLs) throws Exception {
        
    	CertPathBuilder       builder = CertPathBuilder.getInstance("PKIX", "BC");
        PKIXBuilderParameters buildParams = new PKIXBuilderParameters(Collections.singleton(new TrustAnchor(rootCert, null)), endConstraints);
        
        buildParams.addCertStore(certsAndCRLs);
        buildParams.setRevocationEnabled(false);
        
        return (PKIXCertPathBuilderResult)builder.build(buildParams);
    }
    
    /**
     * Create a MIME message from using the passed in content.
     */
    public static MimeMessage createMimeMessage(
        String subject, Object content, String sender, String recepient,  
        String contentType) throws MessagingException {
    	
        Properties props = System.getProperties();
        Session session = Session.getDefaultInstance(props, null);

        javax.mail.Address fromUser = new InternetAddress(sender);
        Address toUser = new InternetAddress(recepient);

        MimeMessage message = new MimeMessage(session);
        
        message.setFrom(fromUser);
        message.setRecipient(Message.RecipientType.TO, toUser);
        message.setSubject(subject);
        message.setContent(content, contentType);
        message.saveChanges();
        
        return message;
    }

    /**
     * Return length many bytes of the passed in byte array as a hex string.
     * 
     * @param data the bytes to be converted.
     * @param length the number of bytes in the data block to be converted.
     * @return a hex representation of length bytes of data.
     */
    public static String toHex(byte[] data, int length){
        StringBuffer	buf = new StringBuffer();
        
        for (int i = 0; i != length; i++) {
            int	v = data[i] & 0xff;
            
            buf.append(digits.charAt(v >> 4));
            buf.append(digits.charAt(v & 0xf));
        }
        
        return buf.toString();
    }
    
    /**
     * Return the passed in byte array as a hex string.
     * 
     * @param data the bytes to be converted.
     * @return a hex representation of data.
     */
    public static String toHex(byte[] data){
        return toHex(data, data.length);
    }

	/**
     * Return a string of length len made up of blanks.
     * 
     * @param len the length of the output String.
     * @return the string of blanks.
     */
    public static String makeBlankString(int	len)    {
        char[]   buf = new char[len];
        
        for (int i = 0; i != buf.length; i++) {
            buf[i] = ' ';
        }
        
        return new String(buf);
    }

    /**
     * Create a key for use with AES.
     * 
     * @param bitLength
     * @param random
     * @return a SecretKey of requested bitLength
     * @throws NoSuchAlgorithmException
     * @throws NoSuchProviderException
     */
    public static SecretKey createKeyForAES(
        int          bitLength,
        SecureRandom random) 
    	throws NoSuchAlgorithmException, NoSuchProviderException {
        
    	KeyGenerator generator = KeyGenerator.getInstance("AES", "BC");
        generator.init(256, random);
        return generator.generateKey();
    }
    
    /**
     * Create an IV suitable for using with AES in CTR mode.
     * <p>
     * The IV will be composed of 4 bytes of message number,
     * 4 bytes of random data, and a counter of 8 bytes.
     * 
     * @param messageNumber the number of the message.
     * @param random a source of randomness
     * @return an initialised IvParameterSpec
     */
    public static IvParameterSpec createCtrIvForAES(int messageNumber, SecureRandom random) {
        byte[]          ivBytes = new byte[16];
        
        // initially randomize
        
        random.nextBytes(ivBytes);
        
        // set the message number bytes
        
        ivBytes[0] = (byte)(messageNumber >> 24);
        ivBytes[1] = (byte)(messageNumber >> 16);
        ivBytes[2] = (byte)(messageNumber >> 8);
        ivBytes[3] = (byte)(messageNumber >> 0);
        
        // set the counter bytes to 1
        
        for (int i = 0; i != 7; i++){
            ivBytes[8 + i] = 0;
        }
        
        ivBytes[15] = 1;
        
        return new IvParameterSpec(ivBytes);
    }
    
    /**
     * Convert a byte array of 8 bit characters into a String.
     * 
     * @param bytes the array containing the characters
     * @param length the number of bytes to process
     * @return a String representation of bytes
     */
    public static String toString(byte[] bytes, int    length) {
        char[]	chars = new char[length];
        
        for (int i = 0; i != chars.length; i++){
            chars[i] = (char)(bytes[i] & 0xff);
        }
        
        return new String(chars);
    }
    
    /**
     * Convert a byte array of 8 bit characters into a String.
     * 
     * @param bytes the array containing the characters
     * @return a String representation of bytes
     */
    public static String toString(byte[] bytes) {
        return toString(bytes, bytes.length);
    }
    
    /**
     * Convert the passed in String to a byte array by
     * taking the bottom 8 bits of each character it contains.
     * 
     * @param string the string to be converted
     * @return a byte array representation
     */
    public static byte[] toByteArray(String string) {
        byte[]	bytes = new byte[string.length()];
        char[]  chars = string.toCharArray();
        
        for (int i = 0; i != chars.length; i++) {
            bytes[i] = (byte)chars[i];
        }
        
        return bytes;
    }

    private static class FixedRand extends SecureRandom {
    	static final long serialVersionUID = 7834646578436578463L;
    	MessageDigest	sha;
        byte[]			state;
        
        FixedRand(){
            try
            {
                this.sha = MessageDigest.getInstance("SHA-1");
                this.state = sha.digest();
            }
            catch (NoSuchAlgorithmException e)
            {
                throw new RuntimeException("can't find SHA-1!");
            }
        }
	
	    public void nextBytes(
	       byte[] bytes)
	    {
	        int	off = 0;
	        
	        sha.update(state);
	        
	        while (off < bytes.length)
	        {	            
	            state = sha.digest();
	            
	            if (bytes.length - off > state.length)
	            {
	                System.arraycopy(state, 0, bytes, off, state.length);
	            }
	            else
	            {
	                System.arraycopy(state, 0, bytes, off, bytes.length - off);
	            }
	            
	            off += state.length;
	            
	            sha.update(state);
	        }
	    }
    }
    
    /**
     * Return a SecureRandom which produces the same value.
     * <b>This is for testing only!</b>
     * @return a fixed random
     */
    public static SecureRandom createFixedRandom(){
        return new FixedRand();
    }

    /**
     * Create a random 1024 bit RSA key pair
     */
    public static KeyPair generateRSAKeyPair() throws Exception{
        KeyPairGenerator  kpGen = KeyPairGenerator.getInstance("RSA", "BC");
    
        kpGen.initialize(1024, new SecureRandom());
//        System.out.println("RSA-Schlüsselpaar generiert.");
        return kpGen.generateKeyPair();
	}
    
    /**
     * Create a random 1024 bit RSA key pair
     */
    public static KeyPair generateDSAKeyPair() throws Exception{
        KeyPairGenerator  kpGen = KeyPairGenerator.getInstance("DSA", "BC");
    
        kpGen.initialize(1024, new SecureRandom());
//        System.out.println("DSA-Schlüsselpaar generiert.");
        return kpGen.generateKeyPair();
	}
    
    /**
     * Generate a sample V1 certificate to use as a CA root certificate
     */
    public static X509Certificate generateRootCert(KeyPair pair, Config config) throws Exception {
	    X509V3CertificateGenerator  certGen = new X509V3CertificateGenerator();
	
	    certGen.setSerialNumber(BigInteger.valueOf(1));
	    certGen.setIssuerDN(new X509Name("CN=Test CA Certificate"));
	    certGen.setNotBefore(new Date(System.currentTimeMillis()));
	    certGen.setNotAfter(new Date(System.currentTimeMillis() + VALIDITY_PERIOD));
	    certGen.setSubjectDN(new X509Name("CN=Test CA Certificate"));
	    certGen.setPublicKey(pair.getPublic());
	    
	    
	    if (config == null){
	    	certGen.setSignatureAlgorithm("SHA1WithRSAEncryption");
	    } else{
	    	String name = "SHA1WithRSAEncryption";
	    	certGen.setSignatureAlgorithm(name);
	    }
	
	    return certGen.generate(pair.getPrivate(), "BC");
	}
    
    /**
     * Generate a sample V3 certificate to use as an intermediate CA certificate
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
        certGen.addExtension(X509Extensions.KeyUsage, true, new org.bouncycastle.asn1.x509.KeyUsage(org.bouncycastle.asn1.x509.KeyUsage.digitalSignature | org.bouncycastle.asn1.x509.KeyUsage.keyCertSign | KeyUsage.cRLSign));

        return certGen.generate(caKey, "BC");
    }
    
    /**
     * Generate a sample V3 certificate to use as an end entity certificate
     */
    public static X509Certificate generateEndEntityCert(PublicKey entityKey, PrivateKey caKey, X509Certificate caCert, Config config)
	    throws Exception
	{
        X509V3CertificateGenerator  certGen = new X509V3CertificateGenerator();

        certGen.setSerialNumber(BigInteger.valueOf(1));
        certGen.setIssuerDN(new X509Name(caCert.getSubjectX500Principal().getName()));
        certGen.setNotBefore(new Date(System.currentTimeMillis()));
        certGen.setNotAfter(new Date(System.currentTimeMillis() + VALIDITY_PERIOD));
        certGen.setSubjectDN(new X509Name(new X500Principal("CN=Test End Certificate").getName()));
        certGen.setPublicKey(entityKey);
        if(config.getHash() == 0)
        	certGen.setSignatureAlgorithm("SHA1WithRSAEncryption");
        else
        	certGen.setSignatureAlgorithm("MD5WithRSAEncryption");
        
        certGen.addExtension(X509Extensions.AuthorityKeyIdentifier, false, new AuthorityKeyIdentifierStructure(caCert));
        certGen.addExtension(X509Extensions.SubjectKeyIdentifier, false, new SubjectKeyIdentifierStructure(entityKey));
        certGen.addExtension(X509Extensions.BasicConstraints, true, new BasicConstraints(false));
        certGen.addExtension(X509Extensions.KeyUsage, true, new org.bouncycastle.asn1.x509.KeyUsage(org.bouncycastle.asn1.x509.KeyUsage.digitalSignature | org.bouncycastle.asn1.x509.KeyUsage.keyEncipherment));

        return certGen.generate(caKey, "BC");
	}

    /**
     * Generate a X500PrivateCredential for the root entity.
     */
    public static X500PrivateCredential createRootCredential(Config config)
        throws Exception {
    	KeyPair rootPair = null;
    	if (config != null){
//	    	if (config.getSigAlgDescription().equals(Config.DSA)){
//	    		rootPair = generateDSAKeyPair();
//	    	} else{
//	    		rootPair = generateRSAKeyPair();
//	    	}
//    	} else{
    		rootPair = generateRSAKeyPair();
    	}
        X509Certificate rootCert = generateRootCert(rootPair, config);
        
        return new X500PrivateCredential(rootCert, rootPair.getPrivate(), ROOT_ALIAS);
    }
    
    /**
     * Generate a X500PrivateCredential for the intermediate entity.
     */
    public static X500PrivateCredential createIntermediateCredential(
        PrivateKey      caKey, X509Certificate caCert) throws Exception {
        
    	KeyPair         interPair = generateRSAKeyPair();
        X509Certificate interCert = generateIntermediateCert(interPair.getPublic(), caKey, caCert);
        
        return new X500PrivateCredential(interCert, interPair.getPrivate(), INTERMEDIATE_ALIAS);
    }
    
    /**
     * Generate a X500PrivateCredential for the end entity.
     */
    public static X500PrivateCredential createEndEntityCredential(
        PrivateKey      caKey, X509Certificate caCert, Config config) throws Exception{
    	KeyPair endPair = null;
    	
    	if(config.getSigAlg() == 0)
    		endPair = generateRSAKeyPair();
    	else
    		endPair = generateDSAKeyPair();
    	
        X509Certificate endCert = generateEndEntityCert(endPair.getPublic(), caKey, caCert, config);
        
        return new X500PrivateCredential(endCert, endPair.getPrivate(), END_ENTITY_ALIAS);
    }
    
    public static MimeMultipart createMultipartWithSignature(
            PrivateKey      key, X509Certificate cert, CertStore       certsAndCRLs,
            MimeBodyPart    dataPart)  throws Exception {
            
    	// create some smime capabilities in case someone wants to respond
        ASN1EncodableVector         signedAttrs = new ASN1EncodableVector();
        SMIMECapabilityVector       caps = new SMIMECapabilityVector();

        caps.addCapability(SMIMECapability.aES256_CBC);
        caps.addCapability(SMIMECapability.dES_EDE3_CBC);
        caps.addCapability(SMIMECapability.rC2_CBC, 128);

        signedAttrs.add(new SMIMECapabilitiesAttribute(caps));
        signedAttrs.add(new SMIMEEncryptionKeyPreferenceAttribute(SMIMEUtil.createIssuerAndSerialNumberFor(cert)));

        // set up the generator
        SMIMESignedGenerator gen = new SMIMESignedGenerator();

        gen.addSigner(key, cert, SMIMESignedGenerator.DIGEST_SHA256, new AttributeTable(signedAttrs), null);

        gen.addCertificatesAndCRLs(certsAndCRLs);

        // create the signed message
//        return new MimeMultipart();
    	return gen.generate(dataPart, "BC");
    }
    
    public static MimeMultipart createMultipartWithSignature(PrivateKey key, X509Certificate cert, 
    		CertStore certsAndCRLs, MimeBodyPart dataPart, String algorithm) 
    		throws Exception {
            
    	// create some smime capabilities in case someone wants to respond
        ASN1EncodableVector         signedAttrs = new ASN1EncodableVector();
        SMIMECapabilityVector       caps = new SMIMECapabilityVector();

        caps.addCapability(SMIMECapability.aES256_CBC);
        caps.addCapability(SMIMECapability.dES_EDE3_CBC);
        caps.addCapability(SMIMECapability.rC2_CBC, 128);

        signedAttrs.add(new SMIMECapabilitiesAttribute(caps));
        signedAttrs.add(new SMIMEEncryptionKeyPreferenceAttribute(SMIMEUtil.createIssuerAndSerialNumberFor(cert)));

        // set up the generator
        SMIMESignedGenerator gen = new SMIMESignedGenerator();

        if (algorithm.equals("SHA-1")){
        	gen.addSigner(key, cert, SMIMESignedGenerator.DIGEST_SHA1, new AttributeTable(signedAttrs), null);
        } else if (algorithm.equals("MD5")){
        	gen.addSigner(key, cert, SMIMESignedGenerator.DIGEST_MD5, new AttributeTable(signedAttrs), null);
        } else {
        	gen.addSigner(key, cert, SMIMESignedGenerator.DIGEST_SHA256, new AttributeTable(signedAttrs), null);
        }

        gen.addCertificatesAndCRLs(certsAndCRLs);

    	return gen.generate(dataPart, "BC");
    }

}
