package mail;


import java.security.cert.CertStore;
import java.security.cert.PKIXCertPathBuilderResult;
import java.security.cert.X509CertSelector;
import java.security.cert.X509Certificate;
import java.util.Iterator;

import org.bouncycastle.cms.CMSSignedData;
import org.bouncycastle.cms.SignerInformation;
import org.bouncycastle.cms.SignerInformationStore;


import utils.Utils;

/**
 * Base class for signed examples.
 */
public class SignedDataProcessor
{
    /**
     * Return a boolean array representing keyUsage with digitalSignature set.
     */
    static boolean[] getKeyUsageForSignature()
    {
        boolean[] val = new boolean[9];

        val[0] = true;

        return val;
    }
    
    /**
     * Take a CMS SignedData message and a trust anchor and determine if
     * the message is signed with a valid signature from a end entity
     * entity certificate recognized by the trust anchor rootCert.
     */
    @SuppressWarnings("unchecked")
	public static boolean isValid(
        CMSSignedData   signedData,
        X509Certificate rootCert)
        throws Exception
    {
        CertStore certsAndCRLs = signedData.getCertificatesAndCRLs("Collection", "BC");
        SignerInformationStore  signers = signedData.getSignerInfos();
        Iterator                it = signers.getSigners().iterator();

        if (it.hasNext())
        {
            SignerInformation         signer = (SignerInformation)it.next();
            X509CertSelector          signerConstraints = signer.getSID();
            
            signerConstraints.setKeyUsage(getKeyUsageForSignature());
            
            PKIXCertPathBuilderResult result = Utils.buildPath(rootCert, signer.getSID(), certsAndCRLs);

            return signer.verify(result.getPublicKey(), "BC");
        }
        
        return false;
    }
}
