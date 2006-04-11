/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/pkcs_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*-----------------------------------------------------------------------*/
/*  FILE  pkcs_p.h          VERSION 1.0   01.01.1995 BY Liu     */
/*-----------------------------------------------------------------------*/

#if !defined(SECUDE_PKCS_INCLUDE) || !SECUDE_PKCS_INCLUDE
#error do not include this file, include <secude/pkcs.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


int  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV oid_cmp SEC_PROTOTYPE_2(
        ObjId	 *	, oid1,
	ObjId	 *	, oid2
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free_CertificationRequestInfo SEC_PROTOTYPE_1(
	CertificationRequestInfo ** , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_CertificationRequestInfo SEC_PROTOTYPE_1(
	CertificationRequestInfo * , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free_CertificationRequest SEC_PROTOTYPE_1(
	CertificationRequest ** , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_CertificationRequest SEC_PROTOTYPE_1(
	CertificationRequest * , str
);

/***************************************************************
 *
 * Headers from file pkcs/pkcs_ed.c
 *
 ***************************************************************/ 

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_RecipientInfos SEC_PROTOTYPE_1(
        RecipientInfos	 *  , infostruct
);

RecipientInfos SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_RecipientInfos SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SET_OF_AlgId SEC_PROTOTYPE_1(
        SET_OF_AlgId	 *  , infostruct
);

SET_OF_AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SET_OF_AlgId SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_ExtendedCertificatesAndCertificates SEC_PROTOTYPE_1(
        ExtendedCertificatesAndCertificates	 *  , infostruct
);

ExtendedCertificatesAndCertificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_ExtendedCertificatesAndCertificates SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SET_OF_CRL SEC_PROTOTYPE_1(
        SET_OF_CRL	 *  , infostruct
);

SET_OF_CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SET_OF_CRL SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SignerInfos SEC_PROTOTYPE_1(
        SignerInfos	 *  , infostruct
);

SignerInfos SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SignerInfos SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_ContentInfo SEC_PROTOTYPE_1(
        ContentInfo	 *  , infostruct
);

ContentInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_ContentInfo SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_Data SEC_PROTOTYPE_1(
        OctetString	 *  , infostruct
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_Data SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SignedData SEC_PROTOTYPE_1(
        SignedData	 *  , infostruct
);

SignedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SignedData SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_EnvelopedData SEC_PROTOTYPE_1(
        EnvelopedData	 *  , infostruct
);

EnvelopedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_EnvelopedData SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SignedAndEnvelopedData SEC_PROTOTYPE_1(
        SignedAndEnvelopedData	 *  , infostruct
);

SignedAndEnvelopedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SignedAndEnvelopedData SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_DigestedData SEC_PROTOTYPE_1(
        DigestedData	 *  , infostruct
);

DigestedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_DigestedData SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_EncryptedData SEC_PROTOTYPE_1(
        EncryptedData	 *  , infostruct
);

EncryptedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_EncryptedData SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

#define e_SETOFAttribute e_SET_OF_Attr
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SET_OF_Attr SEC_PROTOTYPE_1(
        SET_OF_Attr	 *  , infostruct
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SET_OF_Attr_BER SEC_PROTOTYPE_1(
        SET_OF_Attr	 *  , infostruct
);

#define d_SETOFAttribute d_SET_OF_Attr
SET_OF_Attr SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SET_OF_Attr SEC_PROTOTYPE_1(
        OctetString	 *  , asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_encode_ContentField SEC_PROTOTYPE_2(
        ContentInfo     *  , in_continfo, 
	ASN1EncodingRule   , rule
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_CertificationRequest SEC_PROTOTYPE_1(
	CertificationRequest	*	, infostruct
);

CertificationRequest SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_CertificationRequest SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_CertificationRequestInfo SEC_PROTOTYPE_1(
	CertificationRequestInfo	*	, infostruct
);

CertificationRequestInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_CertificationRequestInfo SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);


/***************************************************************
 *
 * Headers from file pkcs/pkcs_cpy.c
 *
 ***************************************************************/ 

SignedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_SignedData SEC_PROTOTYPE_1(
        SignedData	 *  , sigdata
);

ContentInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_ContentInfo SEC_PROTOTYPE_1(
        ContentInfo	*  , contentInfo
);

EnvelopedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_EnvelopedData SEC_PROTOTYPE_1(
        EnvelopedData	 *  , data
);

SignedAndEnvelopedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_SignedAndEnvelopedData SEC_PROTOTYPE_1(
        SignedAndEnvelopedData	 *  , data
);

DigestedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_DigestedData SEC_PROTOTYPE_1(
        DigestedData	 *  , data
);

EncryptedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_EncryptedData SEC_PROTOTYPE_1(
        EncryptedData	 *  , data
);

#define aux_cpy_ExtCertsAndCerts aux_cpy_ExtendedCertificatesAndCertificates
ExtendedCertificatesAndCertificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_ExtendedCertificatesAndCertificates SEC_PROTOTYPE_1(
        ExtendedCertificatesAndCertificates	 *  , certs
);

#define aux_cpy_ExtCertOrCert aux_cpy_ExtendedCertificateOrCertificate
ExtendedCertificateOrCertificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_ExtendedCertificateOrCertificate SEC_PROTOTYPE_1(
        ExtendedCertificateOrCertificate	 *  , cert
);

#define aux_cpy_ExtCertificate aux_cpy_ExtendedCertificate
ExtendedCertificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_ExtendedCertificate SEC_PROTOTYPE_1(
        ExtendedCertificate	 *  , extcert
);

#define aux_cpy_ExtCertificateInfo aux_cpy_ExtendedCertificateInfo
ExtendedCertificateInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_ExtendedCertificateInfo SEC_PROTOTYPE_1(
        ExtendedCertificateInfo	 *  , extcertinfo
);

#define aux_cpy_SETOFSignerInfo aux_cpy_SignerInfos
SignerInfos SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_SignerInfos SEC_PROTOTYPE_1(
        SignerInfos	 *  , siginfos
);

SignerInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_SignerInfo SEC_PROTOTYPE_1(
        SignerInfo	 *  , info
);

#define aux_cpy_SETOFRecipientInfo aux_cpy_RecipientInfos
RecipientInfos SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_RecipientInfos SEC_PROTOTYPE_1(
        RecipientInfos	 *  , siginfos
);

RecipientInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_RecipientInfo SEC_PROTOTYPE_1(
        RecipientInfo	 *  , info
);

EncryptedContentInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_EncryptedContentInfo SEC_PROTOTYPE_1(
        EncryptedContentInfo	 *  , info
);

IssuerAndSerialNumber SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_IssuerAndSerialN SEC_PROTOTYPE_1(
        IssuerAndSerialNumber	 *  , isserian
);

#define aux_cpy_SETOFAttr aux_cpy_SET_OF_Attr
SET_OF_Attr SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_SET_OF_Attr SEC_PROTOTYPE_1(
        SET_OF_Attr	 *  , attrs
);

CCSBag SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_CCSBag SEC_PROTOTYPE_1(
	CCSBag	 *	, bag
);
PrivateKeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_PrivateKeyInfo SEC_PROTOTYPE_1(
	PrivateKeyInfo	 *	, pki
);



/***************************************************************
 *
 * Headers from file pkcs/pkcs_free.c
 *
 ***************************************************************/ 


#define aux_free2_ExtCertInfo aux_free2_ExtendedCertificateInfo
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ExtendedCertificateInfo SEC_PROTOTYPE_1(
        ExtendedCertificateInfo	*  , p
);
#define aux_free_ExtCertInfo aux_free_ExtendedCertificateInfo
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ExtendedCertificateInfo SEC_PROTOTYPE_1(
        ExtendedCertificateInfo	**  , p
);

#define aux_free2_ExtCertificate aux_free2_ExtendedCertificate
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ExtendedCertificate SEC_PROTOTYPE_1(
        ExtendedCertificate	*  , p
);

#define aux_free_ExtCertificate aux_free_ExtendedCertificate
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ExtendedCertificate SEC_PROTOTYPE_1(
        ExtendedCertificate	**  , p
);

#define aux_free2_ExtCertOrCert aux_free2_ExtendedCertificateOrCertificate
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ExtendedCertificateOrCertificate SEC_PROTOTYPE_1(
        ExtendedCertificateOrCertificate	*  , p
);

#define aux_free_ExtCertOrCert aux_free_ExtendedCertificateOrCertificate
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ExtendedCertificateOrCertificate SEC_PROTOTYPE_1(
        ExtendedCertificateOrCertificate	**  , p
);

#define aux_free_ExtCertsAndCerts aux_free_ExtendedCertificatesAndCertificates
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ExtendedCertificatesAndCertificates SEC_PROTOTYPE_1(
        ExtendedCertificatesAndCertificates	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ExtendedCertificatesAndCertificates SEC_PROTOTYPE_1(
	ExtendedCertificatesAndCertificates	*	, p
);

#define aux_free2_IssuerAndSerialN aux_free2_IssuerAndSerialNumber
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_IssuerAndSerialNumber SEC_PROTOTYPE_1(
        IssuerAndSerialNumber	*  , p
);

#define aux_free_IssuerAndSerialN aux_free_IssuerAndSerialNumber
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_IssuerAndSerialNumber SEC_PROTOTYPE_1(
        IssuerAndSerialNumber	**  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SignerInfo SEC_PROTOTYPE_1(
        SignerInfo	*  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SignerInfo SEC_PROTOTYPE_1(
        SignerInfo	**  , p
);

#define aux_free_SETOFSignerInfo aux_free_SignerInfos
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SignerInfos SEC_PROTOTYPE_1(
        SignerInfos	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SignerInfos SEC_PROTOTYPE_1(
	SignerInfos	*	, p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_RecipientInfo SEC_PROTOTYPE_1(
        RecipientInfo	*  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_RecipientInfo SEC_PROTOTYPE_1(
        RecipientInfo	**  , p
);
#define aux_free_SETOFRecipientInfo aux_free_RecipientInfos
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_RecipientInfos SEC_PROTOTYPE_1(
        RecipientInfos	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_RecipientInfos SEC_PROTOTYPE_1(
	RecipientInfos	*	, p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ContentInfo SEC_PROTOTYPE_1(
        ContentInfo	*  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ContentInfo SEC_PROTOTYPE_1(
        ContentInfo	**  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_DigestedData SEC_PROTOTYPE_1(
        DigestedData	*  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_DigestedData SEC_PROTOTYPE_1(
        DigestedData	**  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SignedData SEC_PROTOTYPE_1(
        SignedData	*  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SignedData SEC_PROTOTYPE_1(
        SignedData	**  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EncryptedContentInfo SEC_PROTOTYPE_1(
        EncryptedContentInfo	*  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EncryptedContentInfo SEC_PROTOTYPE_1(
        EncryptedContentInfo	**  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EncryptedData SEC_PROTOTYPE_1(
        EncryptedData	*  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EncryptedData SEC_PROTOTYPE_1(
        EncryptedData	**  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EnvelopedData SEC_PROTOTYPE_1(
        EnvelopedData	*  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EnvelopedData SEC_PROTOTYPE_1(
        EnvelopedData	**  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SignedAndEnvelopedData SEC_PROTOTYPE_1(
        SignedAndEnvelopedData	*  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SignedAndEnvelopedData SEC_PROTOTYPE_1(
        SignedAndEnvelopedData	**  , p
);

/* PKCS#8 / PKCS#12 */
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ECPrivateKey SEC_PROTOTYPE_1(
	ECPrivateKey	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PrivateKeyInfo SEC_PROTOTYPE_1(
	PrivateKeyInfo	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EncryptedPrivateKeyInfo SEC_PROTOTYPE_1(
	EncryptedPrivateKeyInfo	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_MacData SEC_PROTOTYPE_1(
	MacData	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PFX SEC_PROTOTYPE_1(
	PFX	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AuthenticatedSafes SEC_PROTOTYPE_1(
	AuthenticatedSafes	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SafeBag SEC_PROTOTYPE_1(
	SafeBag	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SafeContents SEC_PROTOTYPE_1(
	SafeContents	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CCSBag SEC_PROTOTYPE_1(
	CCSBag	*	, p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ECPrivateKey SEC_PROTOTYPE_1(
	ECPrivateKey	**	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PrivateKeyInfo SEC_PROTOTYPE_1(
	PrivateKeyInfo	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EncryptedPrivateKeyInfo SEC_PROTOTYPE_1(
	EncryptedPrivateKeyInfo 	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_MacData SEC_PROTOTYPE_1(
	MacData	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PFX SEC_PROTOTYPE_1(
	PFX	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AuthenticatedSafes SEC_PROTOTYPE_1(
	AuthenticatedSafes	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SafeBag SEC_PROTOTYPE_1(
	SafeBag	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SafeContents SEC_PROTOTYPE_1(
	SafeContents	**  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CCSBag SEC_PROTOTYPE_1(
	CCSBag	**  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_P12_Bag SEC_PROTOTYPE_1(
	P12_Bag	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_P12_Bags SEC_PROTOTYPE_1(
	P12_Bag	**	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_P12_Safe SEC_PROTOTYPE_1(
	P12_Safe	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_P12_Safe SEC_PROTOTYPE_1(
	P12_Safe	**	, p
);




/***************************************************************
 *
 * Headers from file pkcs/pkcs_print.c
 *
 ***************************************************************/ 

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_ContentInfo SEC_PROTOTYPE_2(
        char         *  , string,
        ContentInfo *  , contentInfo
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_ContentInfo SEC_PROTOTYPE_2(
        FILE         *  , ff,
        ContentInfo *  , contentInfo
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_ContentInfo SEC_PROTOTYPE_1(
        ContentInfo *  , contentInfo
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_CertificationRequest SEC_PROTOTYPE_2(
        char         *  , string,
        CertificationRequest *  , certification_request
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CertificationRequest SEC_PROTOTYPE_2(
        FILE         *  , ff,
        CertificationRequest *  , certification_request
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CertificationRequest SEC_PROTOTYPE_1(
        CertificationRequest *  , certification_request
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_DigestedData SEC_PROTOTYPE_2(
        char *  , string,
        DigestedData *  , digestdata
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_DigestedData SEC_PROTOTYPE_2(
        FILE	*  , ff,
        DigestedData *  , digestdata
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_DigestedData SEC_PROTOTYPE_1(
        DigestedData *  , digestdata
);



char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_EncryptedData SEC_PROTOTYPE_2(
        char *  , string,
        EncryptedData *  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_EncryptedContentInfo SEC_PROTOTYPE_2(
        char *  , string,
        EncryptedContentInfo *  , p_data
);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_EncryptedData SEC_PROTOTYPE_2(
        FILE *  , ff,
        EncryptedData *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_EncryptedContentInfo SEC_PROTOTYPE_2(
        FILE	*  , ff,
        EncryptedContentInfo *  , p_data
);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_EncryptedData SEC_PROTOTYPE_1(
        EncryptedData *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_EncryptedContentInfo SEC_PROTOTYPE_1(
        EncryptedContentInfo *  , p_data
);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_EnvelopedData SEC_PROTOTYPE_2(
        char *  , string,
        EnvelopedData *  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_RecipientInfos SEC_PROTOTYPE_2(
        char *  , string,
        RecipientInfos *  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_RecipientInfo SEC_PROTOTYPE_2(
        char *  , string,
        RecipientInfo *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_EnvelopedData SEC_PROTOTYPE_2(
        FILE *  , ff,
        EnvelopedData *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_RecipientInfos SEC_PROTOTYPE_2(
        FILE *  , ff,
        RecipientInfos *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_RecipientInfo SEC_PROTOTYPE_2(
        FILE *  , ff,
        RecipientInfo *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_EnvelopedData SEC_PROTOTYPE_1(
        EnvelopedData	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_RecipientInfos SEC_PROTOTYPE_1(
        RecipientInfos	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_RecipientInfo SEC_PROTOTYPE_1(
        RecipientInfo	*  , p_data
);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_IssuerAndSerialNumber SEC_PROTOTYPE_2(
        char *  , string,
        IssuerAndSerialNumber *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_IssuerAndSerialNumber SEC_PROTOTYPE_2(
        FILE *  , ff, 
        IssuerAndSerialNumber *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_IssuerAndSerialNumber SEC_PROTOTYPE_1(
        IssuerAndSerialNumber *  , p_data
);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_SignedData SEC_PROTOTYPE_2(
        char *  , string,
        SignedData *  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_SignerInfos SEC_PROTOTYPE_2(
        char *  , string,
        SignerInfos	*  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_SignerInfo SEC_PROTOTYPE_2(
        char *  , string,
        SignerInfo *  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_SET_OF_AlgId SEC_PROTOTYPE_2(
        char *  , string,
        SET_OF_AlgId *  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_SET_OF_CRL SEC_PROTOTYPE_2(
        char *  , string,
        SET_OF_CRL *  , p_data
);

#define print_ExtCertsAndCerts print_ExtendedCertificatesAndCertificates
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_ExtendedCertificatesAndCertificates SEC_PROTOTYPE_2(
        char *  , string,
        ExtendedCertificatesAndCertificates *  , p_data
);

#define print_ExtCertOrCert print_ExtendedCertificateOrCertificate
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_ExtendedCertificateOrCertificate SEC_PROTOTYPE_2(
        char *  , string,
        ExtendedCertificateOrCertificate	*  , p_data
);

#define print_ExtCertificate print_ExtendedCertificate
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_ExtendedCertificate SEC_PROTOTYPE_2(
        char *  , string,
        ExtendedCertificate *  , cert
);

#define print_ExtCertificateInfo print_ExtendedCertificateInfo
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_ExtendedCertificateInfo SEC_PROTOTYPE_2(
        char *  , string,
        ExtendedCertificateInfo	*  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_SET_OF_Attr SEC_PROTOTYPE_2(
        char *  , string,
        SET_OF_Attr	*  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_Attr SEC_PROTOTYPE_2(
        char *  , string,
        Attr *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SignedData SEC_PROTOTYPE_2(
        FILE *  , ff,
        SignedData *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SignerInfos SEC_PROTOTYPE_2(
        FILE *  , ff,
        SignerInfos	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SignerInfo SEC_PROTOTYPE_2(
        FILE *  , ff,
        SignerInfo *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SET_OF_AlgId SEC_PROTOTYPE_2(
        FILE *  , ff,
        SET_OF_AlgId *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SET_OF_CRL SEC_PROTOTYPE_2(
        FILE *  , ff,
        SET_OF_CRL *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_ExtendedCertificatesAndCertificates SEC_PROTOTYPE_2(
        FILE *  , ff, 
        ExtendedCertificatesAndCertificates *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_ExtendedCertificateOrCertificate SEC_PROTOTYPE_2(
        FILE *  , ff,
        ExtendedCertificateOrCertificate	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_ExtendedCertificate SEC_PROTOTYPE_2(
        FILE *  , ff,
        ExtendedCertificate *  , cert
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_ExtendedCertificateInfo SEC_PROTOTYPE_2(
        FILE *  , ff,
        ExtendedCertificateInfo	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SET_OF_Attr SEC_PROTOTYPE_2(
        FILE *  , ff,
        SET_OF_Attr	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_Attr SEC_PROTOTYPE_2(
        FILE *  , ff,
        Attr *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SignedData SEC_PROTOTYPE_1(
        SignedData *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SignerInfos SEC_PROTOTYPE_1(
        SignerInfos	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SignerInfo SEC_PROTOTYPE_1(
        SignerInfo *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SET_OF_AlgId SEC_PROTOTYPE_1(
        SET_OF_AlgId *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SET_OF_CRL SEC_PROTOTYPE_1(
        SET_OF_CRL *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_ExtendedCertificatesAndCertificates SEC_PROTOTYPE_1(
        ExtendedCertificatesAndCertificates *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_ExtendedCertificateOrCertificate SEC_PROTOTYPE_1(
        ExtendedCertificateOrCertificate	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_ExtendedCertificate SEC_PROTOTYPE_1(
        ExtendedCertificate *  , cert
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_ExtendedCertificateInfo SEC_PROTOTYPE_1(
        ExtendedCertificateInfo	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SET_OF_Attr SEC_PROTOTYPE_1(
        SET_OF_Attr	*  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_Attr SEC_PROTOTYPE_1(
        Attr *  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sxprint_OctetString SEC_PROTOTYPE_2(
        char *  , string, 
        OctetString *  , p_data
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_ContentType SEC_PROTOTYPE_2(
        char *  , string, 
        ObjId *  , p_data
);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_X509Certificate SEC_PROTOTYPE_2(
        char *  , string, 
        Certificate *  , cert
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_CertificateToBeSigned SEC_PROTOTYPE_2(
        char *  , string, 
        ToBeSigned *  , tbs
);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_SignedAndEnvelopedData SEC_PROTOTYPE_2(
        char *  , string, 
        SignedAndEnvelopedData *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SignedAndEnvelopedData SEC_PROTOTYPE_2(
        FILE *  , ff, 
        SignedAndEnvelopedData *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SignedAndEnvelopedData SEC_PROTOTYPE_1(
        SignedAndEnvelopedData *  , p_data
);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_ContentType SEC_PROTOTYPE_2(
        FILE *  , ff, 
        ObjId *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_ContentType SEC_PROTOTYPE_1(
        ObjId *  , p_data
);



/***************************************************************
 *
 * Headers from file pkcs/pkcs_aux.c
 *
 ***************************************************************/

ContentTypeId SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2ContentType SEC_PROTOTYPE_1(
        ObjId	 *  , given_objid
);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_ContentType2ObjId SEC_PROTOTYPE_1(
        ContentTypeId	  , given_type
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_ObjId2ContentTypeName SEC_PROTOTYPE_1(
        ObjId	 *  , given_objid
);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_ContentTypeName2ObjId SEC_PROTOTYPE_1(
        char	 *  , ct_name
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_BString2OString SEC_PROTOTYPE_1(
        BitString	*  , bstr
);

BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_OString2BString SEC_PROTOTYPE_1(
        OctetString	*  , ostr
);

AttributeTypeTable SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_ObjId2AttrT SEC_PROTOTYPE_1(
        ObjId	 *  , given_objid
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_SET_OF_AlgId SEC_PROTOTYPE_2(
        SET_OF_AlgId *  , tosetof,
        AlgId *  , from
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_SignerInfos SEC_PROTOTYPE_2(
        SignerInfos *  , tosetof,
        SignerInfo *  , from
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_RecipientInfos SEC_PROTOTYPE_2(
        RecipientInfos	*  , tosetof,
        RecipientInfo	*  , from
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_ExtCertsAndCerts SEC_PROTOTYPE_2(
        ExtendedCertificatesAndCertificates *  , tosetof,
        ExtendedCertificateOrCertificate *  , from
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_SET_OF_CRL SEC_PROTOTYPE_2(
        SET_OF_CRL *  , tosetof,
        CRL	*  , from
);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_ExtCertOrCert2Certificate SEC_PROTOTYPE_1(
        ExtCertOrCert *   , extcert_cert
);

ExtCertOrCert SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_lookup_ExtCertsAndCerts4issuer SEC_PROTOTYPE_2(
        ExtCertsAndCerts *   , certs,
        IssuerAndSerialNumber *   , issuerandserial
);
ExtCertOrCert SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_lookup_ExtCertsAndCerts4KeyID SEC_PROTOTYPE_2(
        ExtCertsAndCerts *   , certs,
        SubjectKeyId *   , keyid
);

ExtCertOrCert SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_lookup_ExtCertsAndCerts4subject SEC_PROTOTYPE_2(
        ExtCertsAndCerts *   , certs,
        DName *   , subject
);

ExtCertsAndCerts SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_Certificates2ExtCertsAndCerts SEC_PROTOTYPE_1(
        Certificates *  , from
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_Certificates2ExtCertsAndCerts SEC_PROTOTYPE_2(
	ExtCertsAndCerts * , result,
        Certificates *  , from
);

Certificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_ExtCertsAndCerts2Certificates SEC_PROTOTYPE_2(
        ExtCertsAndCerts *  , from,
        IssuerAndSerialNumber	*  , user_cert_issn
);
Certificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_ExtCertsAndCerts2Certificates_KeyID SEC_PROTOTYPE_2(
        ExtCertsAndCerts *  , from,
        SubjectKeyId	*  , keyid
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_get_hashinput SEC_PROTOTYPE_3(
        PSESel *  , pse_sel,
        HashInput *  , hashinput,
        char *  , keyname
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_padding SEC_PROTOTYPE_2(
        OctetString	*  , ostr_input,
        unsigned int  ,  blocksize
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_remove_padding SEC_PROTOTYPE_1(
        OctetString *  , ostr_input
);

PKCS12_BagType SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2PKCS12_BagType SEC_PROTOTYPE_1(
	ObjId	 *	, given_objid
);

PKCS12_CCSType SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2PKCS12_CCSType SEC_PROTOTYPE_1(
	ObjId	 *	, given_objid
);



/***************************************************************
 *
 * Headers from file pkcs/pkcs_attr.c
 *
 ***************************************************************/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV pkcs_get_attr SEC_PROTOTYPE_4(
	SET_OF_Attr * , attrlist,
	ObjId * , objid,
	void ** , value,
	int, no
);

RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV pkcs_add_attr SEC_PROTOTYPE_4(
	SET_OF_Attr ** , attrlist,
	ObjId * , objid,
	void ** , value,
	int, no
);
Attr SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_Attr_new SEC_PROTOTYPE_2(
        ObjId *  , attrType,
        caddr_t   , attrValues
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_SAttr SEC_PROTOTYPE_2(
        SET_OF_Attr *  , setofattr,
        Attr *  , attr
);

SET_OF_Attr SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_merge_SAttr SEC_PROTOTYPE_2(
        SET_OF_Attr	*  , a,
        SET_OF_Attr	*  , b
);

AttrValues SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_Avls_merge SEC_PROTOTYPE_2(
        AttrValues	*  , a,
        AttrValues	*  , b
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_Avl_cmp SEC_PROTOTYPE_2(
        OctetString *  , a,
        OctetString *  , b
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV AUX_cmp_OctetString SEC_PROTOTYPE_2(
        OctetString	*  , p,
        OctetString	*  , q
);

SET_OF_Attr SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_search_SAttr SEC_PROTOTYPE_2(
        ObjId		*  , attr_type,
        SET_OF_Attr	*  , setof_attr
);



/***************************************************************
 *
 * Headers from file pkcs/pkcs_util.c
 *
 ***************************************************************/
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_create_CertificationRequest SEC_PROTOTYPE_2(
	PSE		    , pse_handle,
	SET_OF_Attr	*   , attributes
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_create_CertificationRequest_for_key SEC_PROTOTYPE_3(
	PSE		    , pse_handle,
	SET_OF_Attr	*   , attributes,
	KeyType	, keytype
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_create_CertificationRequest_for_key_with_ext SEC_PROTOTYPE_4(
	PSE		    , pse_handle,
	SET_OF_Attr	*   , attributes,
	KeyType	, keytype,
    Boolean , encode_cmmf_extensions
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_create_CertificationRequest_for_key_with_ext_and_DName SEC_PROTOTYPE_5(
	PSE		    , pse_handle,
	SET_OF_Attr	*   , attributes,
	KeyType	, keytype,
    Boolean , encode_cmmf_extensions,
	DName * , requested_name
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs_CertificationRequest2ProtoCertificate SEC_PROTOTYPE_3(
	PSE		    , pse_handle,
	CertificationRequest	*	    , req,
	Certificate  ** , cert
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_ContentInfo2TBx SEC_PROTOTYPE_2(
        ContentInfo *  , continfo,
        ASN1EncodingRule   , rule
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_DER2TBx SEC_PROTOTYPE_1(
	DERcode	 *	, der
);

ContentInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_TBx2ContentInfo SEC_PROTOTYPE_2(
        ObjId *  , contentType,
        OctetString *  , tbX_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_get_MessageDigest SEC_PROTOTYPE_4(
        ContentInfo	*   , in_continfo,
        AlgId		*   , digestAI,
        HashInput	*   , hashinput,
        SET_OF_Attr	*  , authAttrs
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_get_encryptedDigest SEC_PROTOTYPE_3(
        OctetString *  , digest,
        AlgId *  , digestAlgId,
        Key *  , private_key
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs_verify_encryptedDigest SEC_PROTOTYPE_4(
        OctetString	*   , digest,
        AlgId	*  , digestAI,
        OctetString	*   , encryptedDigest,
        Key		*   , public_key
);

EncryptedContentInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_get_EncryptedContentInfo SEC_PROTOTYPE_2(
        ContentInfo		*   , in_continfo,
        Key			*   , content_encryption_key
);

ContentInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_decrypt_EncryptedContentInfo SEC_PROTOTYPE_2(
        EncryptedContentInfo	*   , encryptedContinfo,
        Key			*   , content_decryption_key
);

ContentInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_construct_ContentInfo SEC_PROTOTYPE_2(
        caddr_t   , content,
        ContentTypeId   , type_choice
);

DigestedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_digest_ContentInfo SEC_PROTOTYPE_3(
        ContentInfo *   , in_continfo,
        AlgId *  , digestAI,
        HashInput *   , hashinput
);

EncryptedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_encrypt_ContentInfo SEC_PROTOTYPE_2(
        ContentInfo *   , in_continfo,
        Key *   , content_encryption_key
);

ContentInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_decrypt_ContentInfo SEC_PROTOTYPE_2(
        ContentInfo *   , in_continfo,
        Key *   , content_decryption_key
);

EnvelopedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_envelope_ContentInfo SEC_PROTOTYPE_3(
        ContentInfo *   , in_continfo,
        AlgId *  , contentencAI,
        SET_OF_Certificate *   , recipients_certs
);

ContentInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_develope_ContentInfo SEC_PROTOTYPE_3(
        ContentInfo *   , in_continfo,
        IssuerAndSerialNumber *   , recipient,
        Key *   , recipient_private_key
);

SignerInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_sign_ContentInfo SEC_PROTOTYPE_7(
	ContentInfo	*   , in_continfo,
	IssuerAndSerialNumber *  , signer,
	AlgId		*   , digestAI,
	Key		*   , digestencKey,
	SET_OF_Attr	*   , authAttrs,
	SET_OF_Attr	*   , unauthAttrs,	
	HashInput	*   , hash_input
);

SignedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_create_SignedData SEC_PROTOTYPE_5(
	ContentInfo	*   , in_continfo,
	SignerInfo	*   , signerInfo,
	AlgId		*   , digestAI,
	ExtCertsAndCerts *   , certs,
	SET_OF_CRL 	*   , crls
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs_update_SignedData SEC_PROTOTYPE_5(
	SignedData	*   , sd,
	SignerInfo	*   , signerInfo,
	AlgId		*   , digestAI,
	ExtCertsAndCerts *   , certs,
	SET_OF_CRL 	*   , crls
);

SignerInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_get_countersignature SEC_PROTOTYPE_7(
	OctetString	*   , encryptedDigest,
	IssuerAndSerialNumber *  , signer,
	AlgId		*   , digestAI,
	Key		*   , digestencKey,
	SET_OF_Attr	*   , authAttrs,
	SET_OF_Attr	*   , unauthAttrs,	
	HashInput	*   , hash_input
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs_verify_countersignature SEC_PROTOTYPE_5(
	PSE		    , pse_handle, 
	OctetString	*   , encryptedDigest,
	SignerInfo 	*   , countersignature,
	Certificate	*   , cert,
	HashInput	*   , hash_input
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs_verify_ContentInfo SEC_PROTOTYPE_5( 
	PSE		    , pse_handle, 
	ContentInfo	*   , in_continfo,
	SignerInfo 	*   , signerInfo,
	Certificate	*   , cert,
	HashInput	*   , hash_input
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs_verify_ContentInfoExt SEC_PROTOTYPE_6( 
	PSE		             , pse_handle, 
	ContentInfo	   *     , in_continfo,
	SignerInfo 	   *     , signerInfo,
	Certificate	   *     , cert,
	HashInput	   *     , hash_input,
    P7VerifyResult *     , p_verify_result
);

RecipientInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_get_encryptedKey SEC_PROTOTYPE_2(
	Key		*   , contentencKey,
	Certificate	*   , recipient_cert
);

KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_decrypt_encryptedKey SEC_PROTOTYPE_3(
	RecipientInfo	*   , recipientinfo,
	AlgId		*   , subjectkeyAI,
	Key		*   , keydecKey
);

SignedAndEnvelopedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_envelop_SignedData SEC_PROTOTYPE_3(
	SignedData		*   , signedData,
	Key			*   , contentencKey,
	SET_OF_Certificate 	*   , recipients_certs
);

SignedData SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs_develop_SignedAndEnvelopedData SEC_PROTOTYPE_3(
	SignedAndEnvelopedData	*   , signedAndEnvelopedData,
	IssuerAndSerialNumber	*   , recipient,
	Key			*   , keydecKey
);

/*
PemMessageLocal *pkcs_SignedData2PemMessageLocal(
	SignedData	* signedData,
	PEM_Proc_Types	proc_type
);
SignedData *pkcs_PemMessageLocal2SignedData(
	PemMessageLocal	* local
);
PemMessageLocal *pkcs_SignedAndEnvelopedData2PemMessageLocal(
	SignedAndEnvelopedData	*se_data
);
SignedAndEnvelopedData *pkcs_PemMessageLocal2SignedAndEnvelopedData(
	PemMessageLocal	* local
);
*/


/* from pkcsed.c: */

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_SignerInfo SEC_PROTOTYPE_1(
	SignerInfo	*	, infostruct
);
SignerInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_SignerInfo SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_ECPrivateKey SEC_PROTOTYPE_1(
	ECPrivateKey	 *	, infos
);
ECPrivateKey SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_ECPrivateKey SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_PrivateKeyInfo SEC_PROTOTYPE_1(
	PrivateKeyInfo	 *	, infos
);
PrivateKeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_PrivateKeyInfo SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_EncryptedPrivateKeyInfo SEC_PROTOTYPE_1(
	EncryptedPrivateKeyInfo	 *	, infos
);
EncryptedPrivateKeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_EncryptedPrivateKeyInfo SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_PFX SEC_PROTOTYPE_1(
	PFX	 *	, infos
);
PFX SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_PFX SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_AuthenticatedSafes SEC_PROTOTYPE_1(
	AuthenticatedSafes	 *	, infos
);
AuthenticatedSafes SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_AuthenticatedSafes SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SafeContents SEC_PROTOTYPE_1(
	SafeContents	 *	, infos
);
SafeContents SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SafeContents SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);



/* from pkcsasn1.c : */

ASN1_en_de_PROTO(ExtendedCertificateInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ExtendedCertificateInfo;

#define encode_ExtendedCertificate(i, g, f) \
    ASN1encode_SIGNED(i, g, (ASN1signed *)f)
#define decode_ExtendedCertificate(i, f, e, r) \
    (ExtendedCertificate *)ASN1decode_SIGNED(i, f, e, (ASN1signed *)r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ExtendedCertificate;

ASN1_en_de_PROTO(ExtendedCertificateOrCertificate)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ExtendedCertificateOrCertificate;

#define encode_ExtendedCertificatesAndCertificates(i, g, f) \
    ASN1e_gen_List(i, g, f)
#define decode_ExtendedCertificatesAndCertificates(i, f, e, r) \
    ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ExtendedCertificatesAndCertificates;

ASN1_en_de_PROTO(ContentInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ContentInfo;

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV encode_CHOICEinContentInfo SEC_PROTOTYPE_3(
        ASN1info_type           *    , info,
        ASN1global              *    , glob ,
        ContentInfo             *    , from
);
ContentInfo 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  decode_CHOICEinContentInfo SEC_PROTOTYPE_4(
        ASN1info_type           *    , info,
        char                    **   , from,
	char                    *    , endptr,
	ContentInfo             *    , ret
);
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CHOICEinContentInfo;

ASN1_en_de_PROTO(SignedData)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SignedData;

ASN1_en_de_PROTO(SignerInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SignerInfo;

#define encode_SignerInfos(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_SignerInfos(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SignerInfos;

ASN1_en_de_PROTO(IssuerAndSerialNumber)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_IssuerAndSerialNumber;

ASN1_en_de_PROTO(RecipientInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_RecipientInfo;

#define encode_RecipientInfos(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_RecipientInfos(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_RecipientInfos;

ASN1_en_de_PROTO(EncryptedContentInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EncryptedContentInfo;

ASN1_en_de_PROTO(EnvelopedData)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EnvelopedData;

ASN1_en_de_PROTO(SignedAndEnvelopedData)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SignedAndEnvelopedData;

ASN1_en_de_PROTO(DigestedData)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_DigestedData;

ASN1_en_de_PROTO(EncryptedData)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EncryptedData;

ASN1_en_de_PROTO(CertificationRequestInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CertificationRequestInfo;

#define encode_CertificationRequest(i, g, f) ASN1encode_SIGNED(i, g, f)
#define decode_CertificationRequest(i, f, e, r) ASN1decode_SIGNED(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CertificationRequest;

ASN1_en_de_PROTO(ECPrivateKey)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ECPrivateKey;

ASN1_en_de_PROTO(PrivateKeyInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PrivateKeyInfo;

ASN1_en_de_PROTO(EncryptedPrivateKeyInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EncryptedPrivateKeyInfo;

ASN1_en_de_PROTO(PFX)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PFX;

ASN1_en_de_PROTO(MacData)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_MacData;

#define encode_AuthenticatedSafes(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_AuthenticatedSafes(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AuthenticatedSafes;

ASN1_en_de_PROTO(SafeBag)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SafeBag;

#define encode_SafeContents(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_SafeContents(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SafeContents;

ASN1_en_de_PROTO(CCSBag)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CCSBag;
#ifdef STRUCTS_FOR_TIMESTAMPING
ASN1_en_de_PROTO(MessageImprint)
ASN1_en_de_PROTO(TimeStampReq_1)
ASN1_en_de_PROTO(TSTTime)
ASN1_en_de_PROTO(PKIStatusInfo)
ASN1_en_de_PROTO(TimeStampReq_0)
ASN1_en_de_PROTO(TimeStampToken_0)
ASN1_en_de_PROTO(TimeStampReq)
ASN1_en_de_PROTO(TSTInfo)
ASN1_en_de_PROTO(TimeStampToken)
ASN1_en_de_PROTO(TimeStampToken_1)
#endif /* STRUCTS_FOR_TIMESTAMPING */
/* Global variables defined in pkcs_init.c  */

	/* Object Identifiers for PKCS */

extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DataType_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SignedDataType_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX EnvelopedDataType_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SignedAndEnvelopedDataType_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DigestedDataType_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX EncryptedDataType_OID;

extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX OCSPLogAttribute_OID;

extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX EmailAddress_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX UnstructuredName_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX ContentType_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX MessageDigest_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SigningTime_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX Countersignature_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX UnstructuredAddress_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX ChallengePassword_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX ExtendedCertificateAttributes_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX ExtensionRequest_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX P12_FriendlyName_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX P12_LocalKeyID_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX KeyBag_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX PKCS8ShroudedKeyBag_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CertBag_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CRLBag_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SecretBag_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SafeContentsBag_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CCS_X509Certificate_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CCS_SDSICertificate_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CCS_X509Crl_OID;

extern ContentTypeList	SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  	ct_list[];
extern AttributeTypeTable	SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  at_table[];

extern PKCS12_BagTypeList SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX bagTypeList[];
extern PKCS12_CCSTypeList SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ccsTypeList[];

extern int SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  pkcs_verbose;

extern unsigned int SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  print_ContentInfo_flag;

/* 
 * PKCS#5 / PKCS#12
 */
AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs5_pbeAlg2encAlg_static SEC_PROTOTYPE_1(
	AlgId		 *	, pbe_alg
);
AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs5_pbeAlg2encAlg SEC_PROTOTYPE_1(
	AlgId		 *	, pbe_alg
);
AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs5_pbeAlg2hashAlg_static SEC_PROTOTYPE_1(
	AlgId		 *	, pbe_alg
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs5_pbeAlg2keylength SEC_PROTOTYPE_1(
	AlgId		 *	, pbe_alg
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs5_derive_salt SEC_PROTOTYPE_4(
	OctetString	 *	, password,
	OctetString	 *	, message,
	AlgId		 *	, pbe_alg,
	Boolean			, message_is_guessable
);
Key SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs5_generate_key SEC_PROTOTYPE_2(
	OctetString	 *	, password,
	AlgId		 *	, pbe_alg
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_set_des_parity_bits SEC_PROTOTYPE_2(
	char	 *	, ptr,
	int		, len
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV hmac_hash_init SEC_PROTOTYPE_3(
	void		**	, context,
	AlgId		 *	, hashalg,
	OctetString	 * 	, key
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV hmac_hash_more SEC_PROTOTYPE_2(
	void		**	, context,
	OctetString	 *	, in_octets
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV hmac_hash_end SEC_PROTOTYPE_2(
	void		**	, context,
	OctetString	 *	, hash_result
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV hmac_hash_all SEC_PROTOTYPE_4(
	OctetString	 *	, in_octets,
	OctetString	 *	, hash_result,
	AlgId		 *	, hashalg,
	OctetString	 * 	, key
);
Key SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs12_generate_key SEC_PROTOTYPE_2(
	OctetString	 *	, password,
	AlgId		 *	, pbe_alg
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_output_length_of_hash SEC_PROTOTYPE_1(
	AlgId	*	, hash_alg
);
BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs12_generate_pseudo_random SEC_PROTOTYPE_6(
	OctetString	 *	, password,
	OctetString	 *	, salt,
	int			, iterationCount,
	AlgId		 *	, hash_alg,
	sec_byte		, ID,
	int			, bits_required
);

/* "high-level" PKCS#12 functions */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs12_decode SEC_PROTOTYPE_4(
	OctetString	 *	, asn1_str,
	OctetString	 *	, password,
	P12_Safe	 *	, safe,
	Boolean		 *	, verified
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs12_encode SEC_PROTOTYPE_3(
	P12_Safe	 *	, safe,
	OctetString	 *	, password,
	OctetString	 *	, asn1_out
);
PrivateKeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_create_PrivateKeyInfo SEC_PROTOTYPE_3(
	KeyInfo		 *	, key,
	Certificate	 *	, cert,
	SET_OF_Attr	 *	, attributes
);
KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_PrivateKeyInfo2KeyInfo SEC_PROTOTYPE_1(
	PrivateKeyInfo		 *	, pki
);

#ifdef STRUCTS_FOR_TIMESTAMPING
/* *********************************************************************** */
/* VERSION 1                                                               */
/* *********************************************************************** */


TimeStampReq_1 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_TimeStampReq_1 SEC_PROTOTYPE_1(
	
	OctetString	 *  	, asn1_string 

);



OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_TimeStampReq_1 SEC_PROTOTYPE_1(
	
	TimeStampReq_1	 *	, namestruct
	
);


 
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_TSTInfo_1 SEC_PROTOTYPE_1(
	
	TSTInfo_1 *	, namestruct

);


TSTInfo_1 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_TSTInfo_1 SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_TimeStampToken_1 SEC_PROTOTYPE_1(
	
	TimeStampToken_1  *	, namestruct

);

TimeStampToken_1 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_TimeStampToken_1 SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);




/* *********************************************************************** */
/* VERSION 0                                                               */
/* *********************************************************************** */


TimeStampReq_0 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_TimeStampReq_0 SEC_PROTOTYPE_1(
	
	OctetString	 *  	, asn1_string 

);



OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_TimeStampReq_0 SEC_PROTOTYPE_1(
	
	TimeStampReq_0	 *	, namestruct
	
);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_TimeStampToken_0 SEC_PROTOTYPE_1(
	
	TimeStampToken_0  *	, namestruct

);
 
TimeStampToken_0 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_TimeStampToken_0 SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);



/* *********************************************************************** */
/* VERSION X                                                              */
/* *********************************************************************** */

TimeStampReq SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_TimeStampReq SEC_PROTOTYPE_1(
	
	OctetString	 *  	, asn1_string 

);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_TimeStampReq SEC_PROTOTYPE_1(
	
	TimeStampReq	 *	, namestruct
	
);


 
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_TSTInfo SEC_PROTOTYPE_1(
	
	TSTInfo	 *	, namestruct

);


TSTInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_TSTInfo SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_TimeStampToken SEC_PROTOTYPE_1(
	
	TimeStampToken	 *	, namestruct

);

TimeStampToken SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_TimeStampToken SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);





int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV encode_TSTInfo_1 SEC_PROTOTYPE_3(
        ASN1info_type   *    , info,
        ASN1global      *    , glob ,
        TSTInfo_1         *  , from
);

TSTInfo_1 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV decode_TSTInfo_1 SEC_PROTOTYPE_4(
        ASN1info_type      *    , info,
        char               **   , from,
	char               *    , endptr,
	TSTInfo_1            *    , ret
);


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV encode_TSTInfo_0 SEC_PROTOTYPE_3(
        ASN1info_type   *    , info,
        ASN1global      *    , glob ,
        TSTInfo_0         *  , from
);


TSTInfo_0 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV decode_TSTInfo_0 SEC_PROTOTYPE_4(
        ASN1info_type      *    , info,
        char               **   , from,
	char               *    , endptr,
	TSTInfo_0            *    , ret
);


MessageImprint SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_MessageImprint SEC_PROTOTYPE_1(
	
	MessageImprint	 *	, org

);
TSTTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_TSTTime SEC_PROTOTYPE_1(
	
	TSTTime	 *	, org

);
PKIStatusInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_PKIStatusInfo SEC_PROTOTYPE_1(
	
	PKIStatusInfo	 *	, org

);
TSTInfo_0 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_TSTInfo_0 SEC_PROTOTYPE_1(
	
	TSTInfo_0	 *	, org

);
TSTInfo_1 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_TSTInfo_1 SEC_PROTOTYPE_1(
	
	TSTInfo_1	 *	, org

);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_PKIStatusInfo SEC_PROTOTYPE_2(
	
	char		*	, string,
	
	PKIStatusInfo	*	, p_data

);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_TSTTime SEC_PROTOTYPE_2(
	
	char		*	, string,
	
	TSTTime  	*	, p_data

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_TSTInfo_0 SEC_PROTOTYPE_2(
	
	char		*	, string,
	
	TSTInfo_0	*	, tstInfo

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_TSTInfo_1 SEC_PROTOTYPE_2(
	
	char		*	, string,
	
	TSTInfo_1	*	, tstInfo

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_TSTInfo_1 SEC_PROTOTYPE_2(
	
	FILE		*	, ff,
	
	TSTInfo_1	*	, tstInfo

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_TSTInfo_1 SEC_PROTOTYPE_1(
	
	TSTInfo_1	*	, tstInfo

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_MessageImprint SEC_PROTOTYPE_2(
	
	char		*	, string,
	
	MessageImprint	*	, p_data

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_MessageImprint SEC_PROTOTYPE_1(
	
	MessageImprint	**	, p

);




void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TimeStampReq_0 SEC_PROTOTYPE_1(
	
	TimeStampReq_0	**	, p

);




void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TimeStampReq_1 SEC_PROTOTYPE_1(
	
	TimeStampReq_1	**	, p

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TSTTime SEC_PROTOTYPE_1(
	
	TSTTime	**	, p

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TSTInfo_0 SEC_PROTOTYPE_1(
	
	TSTInfo_0	**	, p

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PKIStatusInfo SEC_PROTOTYPE_1(
	
	PKIStatusInfo	**	, p

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TSTInfo_1 SEC_PROTOTYPE_1(
	
	TSTInfo_1	**	, p

);



void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TimeStampToken_1 SEC_PROTOTYPE_1(
	
	TimeStampToken_1	**	, p

);



extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_MessageImprint;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TimeStampReq_1;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TSTTime;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PKIStatusInfo;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TSTInfo_1;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TimeStampReq_0;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TSTInfo_0;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TimeStampToken_0;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TimeStampReq;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TSTInfo;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TimeStampToken;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TimeStampToken_1;

#endif /* STRUCTS_FOR_TIMESTAMPING */



extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_MT_CertRep;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_MT_PKCSReq;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_MT_GetCert;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_MT_GetCRL;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_MT_DualReq;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_MT_DualRep;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_MT_RevReq;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_MT_RevRep;

extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_ST_SUCCESS;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_ST_PENDING;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_ST_FAILURE;

extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_FI_BADALG;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_FI_BADMESSAGECHECK;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_FI_BADREQUEST;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_FI_BADTIME;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_FI_BADCERTID;
extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX CRS_FI_UNSUPPORTEDEXT;

extern sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX crs_protocol_version;

extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX crs_message_type_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX crs_status_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX crs_failinfo_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX crs_sendernonce_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX crs_recipientnonce_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX crs_transactionid_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX crs_extensionreq_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX crs_version_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX crs_dualstatus_OID;


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_unauthenticated_attribute SEC_PROTOTYPE_4(
	SignerInfo   * 	, siginfo,
	ObjId        * 	, attrtype,
	OctetString  * 	, attrvalue,
    Boolean         , merge
);
SET_OF_OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_unauthenticated_attribute SEC_PROTOTYPE_2(
	SignerInfo   * 	, siginfo,
	ObjId        * 	, attrtype
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_update_pkcs7WithOCSP SEC_PROTOTYPE_2(
    OctetString     * , pkcs7message,
    SEQUENCE_OF_OctetString  * , ocsplog
);


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


