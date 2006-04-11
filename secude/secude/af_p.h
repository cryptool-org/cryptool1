/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/af_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#if !defined(SECUDE_AF_INCLUDE) || !SECUDE_AF_INCLUDE
#error do not include this file, include <secude/af.h>
#endif

#include <secude/asn1.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#define CERT_FIRST = 1;
#define CERT_LAST = -1;
Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_Certificate_n_from_Certificates SEC_PROTOTYPE_2(Certificates *,certs, int ,n);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_tbs_DERcode_of_Certificate SEC_PROTOTYPE_1(Certificate * ,cert);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_serialnumber_of_Certificate SEC_PROTOTYPE_1(Certificate *, cert);
DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_subject_of_Certificate SEC_PROTOTYPE_1(Certificate *, cert);
DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_issuer_of_Certificate SEC_PROTOTYPE_1(Certificate     * ,cert);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_notafter_of_Certificate SEC_PROTOTYPE_1(Certificate     * ,cert);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_notbefore_of_Certificate SEC_PROTOTYPE_1(Certificate     * ,cert);


RC SEC_API_CALLING_CONV af_int_set_crl_options(PSE pse, char *config_node);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sap_secin SEC_PROTOTYPE_2(
	int , cnt,
	char ** , p
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sap_seclogin SEC_PROTOTYPE_2(
	int , cnt,
	char ** , p
);

FILE SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_stdin SEC_PROTOTYPE_0();
FILE SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_stdout SEC_PROTOTYPE_0();
FILE SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_stderr SEC_PROTOTYPE_0();

FILE SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_fopen SEC_PROTOTYPE_2(

        const char      *       , filename,

        const char       *      , mode

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fclose SEC_PROTOTYPE_1(

        FILE    *       , stream

);

Boolean SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV af_check_KeyUsage SEC_PROTOTYPE_2(
		ToBeSigned * ,tbs,
		KeyType , type
);
#ifdef X509v3
Boolean SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV af_check_ExtKeyUsage SEC_PROTOTYPE_3(
	ToBeSigned * 	, tbs,
	KeyPurposeId * 	, kpIdentifier,
	Boolean		, critical
);
#endif
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV af_complete_PSE SEC_PROTOTYPE_1(
        PSE ,  pse
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV af_pse_get_keysize SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	int	 *	, sig,
	int	 *	, enc,
	AlgEnc 	 *	, sig_type

);

#ifdef ASN1_NETSCAPE_STUFF
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_PublicKeyAndChallenge SEC_PROTOTYPE_1(
	PublicKeyAndChallenge * , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free_PublicKeyAndChallenge SEC_PROTOTYPE_1(
	PublicKeyAndChallenge ** , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_SignedPublicKeyAndChallenge SEC_PROTOTYPE_1(
	SignedPublicKeyAndChallenge * , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free_SignedPublicKeyAndChallenge SEC_PROTOTYPE_1(
	SignedPublicKeyAndChallenge ** , str
);
#endif /*ASN1_NETSCAPE_STUFF*/


#define aux_free_SETOFCRL aux_free_SET_OF_CRL
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_CRL SEC_PROTOTYPE_1(
        SET_OF_CRL      **  , p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SET_OF_CRL SEC_PROTOTYPE_1(
        SET_OF_CRL      *      , p
);

extern AF_options SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX af_def_options;

extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX cred_owner;

Creds SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_credentials_file SEC_PROTOTYPE_0();
Creds SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_credentials_file_from_shared_mem SEC_PROTOTYPE_0();
Creds SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_credentials_file_from_file SEC_PROTOTYPE_0();

Cred SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_nth_credentials SEC_PROTOTYPE_2(
	Creds * , cred_list,
	unsigned int    , no
);
Cred SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_credentials_by_pse SEC_PROTOTYPE_4(
	char *	, pse,
	char *	, ca,
	Boolean , with_pin,
	char *	, app
);
Cred SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_credentials_by_name SEC_PROTOTYPE_3(
	char *	, user_name,
	Boolean , with_pin,
	char *	, app
);
Cred SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_Cred SEC_PROTOTYPE_1(
	Cred *	, cred
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_put_credentials_in_shared_mem SEC_PROTOTYPE_1(
	Creds * , cred_list
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_put_credentials_file SEC_PROTOTYPE_1(
	Creds * , cred_list
);

Cred SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_credentials SEC_PROTOTYPE_5(
	Creds * , cred_list,
	Name *	, name,
	char *	, pse,
	char *	, ca,
	char *	, app
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Cred SEC_PROTOTYPE_1(
	Cred 	**, cred
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Cred SEC_PROTOTYPE_1(
	Cred 	*, cred
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Creds SEC_PROTOTYPE_1(
	Creds 	**, creds
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Creds SEC_PROTOTYPE_1(
	Creds 	*, creds
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_credentials SEC_PROTOTYPE_4(
	Creds ** , cred_list,
	Cred *	, creds,
	Boolean , def,
	char * , owner
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_delete_credentials SEC_PROTOTYPE_6(
	Creds ** , cred_list,
	Name *	, name,
	char *	, pse,
	char *	, ca,
	char *	, app,
	unsigned int    , no
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_SEQ_OF_Name SEC_PROTOTYPE_1(
	
	SET_OF_Name	 *	, namestruct

);

SET_OF_Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_SEQ_OF_Name SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_Creds SEC_PROTOTYPE_1(
	
	Creds	 *	, namestruct

);

Creds SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_Creds SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

sec_uint4 SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_get_pse_lifetime SEC_PROTOTYPE_1(
	PSE , pse);

#if defined(X500) && defined(X500_USE_LDAP)
/*#ifdef LDAP_WITH_DL_OPEN
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_ldap_library_name SEC_PROTOTYPE_0();

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV load_ldap_library SEC_PROTOTYPE_1(
	PSE, pse_handle
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV unload_ldap_library SEC_PROTOTYPE_1(
	PSE, pse_handle
);
#endif*/
RC  SEC_API_CALLING_CONV sec_ldap_insert_entry_in_url (                 
    char *  url,   DName *  entry, char **newurl
    );
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ldap_get_url SEC_PROTOTYPE_4(
    PSE   , pse_handle,
    char *,  name,
    DName *,  entry,
    SET_OF_CRL **,   obj
    );


#endif

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AttrValueAssertion SEC_PROTOTYPE_1(
	AttrValueAssertion	 *	, ava
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AttrValueAssertion SEC_PROTOTYPE_1(
	AttrValueAssertion	 **	, ava
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_RDName SEC_PROTOTYPE_1(
	
	RDName	 *	, rdn

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_RDName SEC_PROTOTYPE_1(
	
	RDName	**	, rdn

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_DName SEC_PROTOTYPE_1(
	
	DName	 *	, dn

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_Name SEC_PROTOTYPE_1(
	
	SET_OF_Name	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SET_OF_Name SEC_PROTOTYPE_1(
	SET_OF_Name	*	, obj
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_DName SEC_PROTOTYPE_1(
	
	DName	**	, dn

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ToBeSigned SEC_PROTOTYPE_1(
	
	ToBeSigned	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ToBeSigned SEC_PROTOTYPE_1(
	
	ToBeSigned	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Certificate SEC_PROTOTYPE_1(
	
	Certificate	 *	, cert

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Certificate SEC_PROTOTYPE_1(
	
	Certificate	**	, cert

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CertificateSet SEC_PROTOTYPE_1(
	
	SET_OF_Certificate	**	, certset

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_Certificate SEC_PROTOTYPE_1(
	
	SET_OF_Certificate	**	, certset

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SET_OF_Certificate SEC_PROTOTYPE_1(
    SET_OF_Certificate      *     , certset
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CertificatePair SEC_PROTOTYPE_1(
	
	CertificatePair	 *	, cpair

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CertificatePair SEC_PROTOTYPE_1(
	
	CertificatePair	**	, cpair

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CertificatePairSet SEC_PROTOTYPE_1(
	
	SET_OF_CertificatePair	**	, cpairset

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CertificatePairSet SEC_PROTOTYPE_1(
	SET_OF_CertificatePair	*	, cpairset
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CrossCertificates SEC_PROTOTYPE_1(
	
	CrossCertificates	**	, ccerts

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CrossCertificates SEC_PROTOTYPE_1(
	
	CrossCertificates	 *	, ccerts

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_FCPath SEC_PROTOTYPE_1(
	
	FCPath	**	, path

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_FCPath SEC_PROTOTYPE_1(
	FCPath	*	, path
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Certificates SEC_PROTOTYPE_1(
	
	Certificates	**	, certs

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Certificates SEC_PROTOTYPE_1(
	Certificates	*	, certs
);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CRLWithCertificates SEC_PROTOTYPE_1(
	
	CRLWithCertificates	**	, crlwithcerts

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CRLWithCertificates SEC_PROTOTYPE_1(
	CRLWithCertificates	*	, crlwithcerts
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_CRLWithCertificates SEC_PROTOTYPE_1(
	
	SET_OF_CRLWithCertificates	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CertificationPath SEC_PROTOTYPE_1(
	
	CertificationPath	**	, certpath

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CertificationPath SEC_PROTOTYPE_1(
	CertificationPath	*	, certpath
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CertificatePairs SEC_PROTOTYPE_1(
	
	CertificatePairs	**	, pairs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SEQUENCE_OF_CertificatePair SEC_PROTOTYPE_1(
	
	SEQUENCE_OF_CertificatePair	**	, seq

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PKRoot SEC_PROTOTYPE_1(
	
	PKRoot	**	, pkroot

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PKRoot SEC_PROTOTYPE_1(
	PKRoot	*	, pkroot
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_RootInfo SEC_PROTOTYPE_1(
	
	Serial	 *	, rootinfo

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_RootInfo SEC_PROTOTYPE_1(
	
	Serial	**	, rootinfo

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PKList SEC_PROTOTYPE_1(
	
	PKList	**	, pklist

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PKList SEC_PROTOTYPE_1(
	PKList	*	, pklist
);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Crl SEC_PROTOTYPE_1(
	
	Crl	 *	, crlpse

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Crl SEC_PROTOTYPE_1(
	
	Crl	**	, crlpse

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CrlSet SEC_PROTOTYPE_1(
	
	CrlSet	**	, crlset

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CrlSet SEC_PROTOTYPE_1(
	CrlSet	*	, crlset
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CRLEntry SEC_PROTOTYPE_1(
	
	CRLEntry	 *	, crlentry

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CRLEntry SEC_PROTOTYPE_1(
	
	CRLEntry	**	, crlentry

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SEQUENCE_OF_CRLEntry SEC_PROTOTYPE_1(
	
	SEQUENCE_OF_CRLEntry	**	, seq

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SEQUENCE_OF_CRLEntry SEC_PROTOTYPE_1(
	SEQUENCE_OF_CRLEntry	*	, seq
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CRLTBS SEC_PROTOTYPE_1(
	
	CRLTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CRLTBS SEC_PROTOTYPE_1(
	
	CRLTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CRL SEC_PROTOTYPE_1(
	
	CRL	 *	, crl

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CRL SEC_PROTOTYPE_1(
	
	CRL	**	, crl

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_IssuedCertificate SEC_PROTOTYPE_1(
	
	IssuedCertificate	 *	, isscert

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_IssuedCertificate SEC_PROTOTYPE_1(
	
	IssuedCertificate	**	, isscert

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_IssuedCertificate SEC_PROTOTYPE_1(
	
	SET_OF_IssuedCertificate	**	, isscertset

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SET_OF_IssuedCertificate SEC_PROTOTYPE_1(
	SET_OF_IssuedCertificate	*	, isscertset
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_VerificationStep SEC_PROTOTYPE_1(
	
	VerificationStep	**	, verstep

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_VerificationResult SEC_PROTOTYPE_1(
	
	VerificationResult	 *	, verres

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_VerificationResult SEC_PROTOTYPE_1(
	
	VerificationResult	**	, verres

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_OcspResults SEC_PROTOTYPE_1(
	OcspCheckResults	*	, p_results
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_OcspHdl SEC_PROTOTYPE_1(
	H_OCSP_CHECK*	, p_h_rev_check
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_OcspHdl SEC_PROTOTYPE_1(
	H_OCSP_CHECK	, h_rev_check
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Validity SEC_PROTOTYPE_1(
	
	Validity	 *	, valid

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Validity SEC_PROTOTYPE_1(
	
	Validity	**	, valid

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_DName SEC_PROTOTYPE_1(
	
	SET_OF_DName	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_NAME SEC_PROTOTYPE_1(
	
	NAME	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_NAME SEC_PROTOTYPE_1(
	
	SET_OF_NAME	**	, obj

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AliasList SEC_PROTOTYPE_1(
	
	AliasList	**	, alist

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AliasList SEC_PROTOTYPE_1(
	AliasList	*	, alist
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Aliases SEC_PROTOTYPE_1(
	Aliases	*	, aliases
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_AlgId SEC_PROTOTYPE_1(
	
	SET_OF_AlgId	**	, p

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SET_OF_AlgId SEC_PROTOTYPE_1(
	SET_OF_AlgId	*	, p
);



/*  from  aux_cpy.c : */

SET_OF_CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_SET_OF_CRL SEC_PROTOTYPE_1(
        SET_OF_CRL       *  , crlset
);


Validity SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Validity SEC_PROTOTYPE_1(
	
	Validity	 *	, valid

);

Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Name SEC_PROTOTYPE_1(
	
	char	 *	, namefrom

);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_ReducedString SEC_PROTOTYPE_1(
	
	char	 *	, a

);

RDName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_RDName SEC_PROTOTYPE_1(
	
	RDName	 *	, rdn

);

DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_DName SEC_PROTOTYPE_1(
	
	DName	 *	, dn

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_DName SEC_PROTOTYPE_2(
	
	DName	 *	, dup_dname,
	
	DName	 *	, dname

);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Certificate SEC_PROTOTYPE_1(
	
	Certificate	 *	, cert

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_Certificate SEC_PROTOTYPE_2(
	
	Certificate	 *	, dup_cert,
	
	Certificate	 *	, cert

);

PKList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PKList SEC_PROTOTYPE_1(
	
	PKList	 *	, list

);

Certificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Certificates SEC_PROTOTYPE_1(
	
	Certificates	 *	, certs

);

CertificatePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CertificatePair SEC_PROTOTYPE_1(
	
	CertificatePair	 *	, certs

);

SET_OF_Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SET_OF_Certificate SEC_PROTOTYPE_1(
	
	SET_OF_Certificate	 *	, certs

);

SET_OF_Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SET_OF_Name SEC_PROTOTYPE_1(
	
	SET_OF_Name	 *	, nameset

);

SET_OF_CertificatePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SET_OF_CertificatePair SEC_PROTOTYPE_1(
	
	SET_OF_CertificatePair	 *	, certs

);

FCPath SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_FCPath SEC_PROTOTYPE_1(
	
	FCPath	 *	, fcpath

);

ToBeSigned SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_ToBeSigned SEC_PROTOTYPE_1(
	
	ToBeSigned	 *	, tbs

);

PKRoot SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PKRoot SEC_PROTOTYPE_1(
	
	PKRoot	 *	, pkr

);

IssuedCertificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_IssuedCertificate SEC_PROTOTYPE_1(
	
	IssuedCertificate	 *	, isscert

);

SET_OF_IssuedCertificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SET_OF_IssuedCertificate SEC_PROTOTYPE_1(
	
	SET_OF_IssuedCertificate	 *	, isscertset

);

Crl SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Crl SEC_PROTOTYPE_1(
	
	Crl	 *	, crlpse

);

CrlSet SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CrlSet SEC_PROTOTYPE_1(
	
	CrlSet	 *	, crlset

);

struct Serial SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Serial SEC_PROTOTYPE_1(
	
	struct Serial	 *	, serial

);

Aliases SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Aliases SEC_PROTOTYPE_1(
	
	Aliases	 *	, aliases

);

AliasList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_AliasList SEC_PROTOTYPE_1(
	
	AliasList	 *	, aliaslist

);

CRLEntry SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CRLEntry SEC_PROTOTYPE_1(
	
	CRLEntry	 *	, crlentry

);

SEQUENCE_OF_CRLEntry SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SEQUENCE_OF_CRLEntry SEC_PROTOTYPE_1(
	
	SEQUENCE_OF_CRLEntry	 *	, seq

);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CRL SEC_PROTOTYPE_1(
	
	CRL	 *	, crl

);

CRLTBS SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CRLTBS SEC_PROTOTYPE_1(
	
	CRLTBS	 *	, tbs

);

SET_OF_DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SET_OF_DName SEC_PROTOTYPE_1(
	
	SET_OF_DName	 *	, old

);

VerificationStep SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_VerificationStep SEC_PROTOTYPE_1(
	
	VerificationStep	 *	, old

);

VerificationResult SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_VerificationResult SEC_PROTOTYPE_1(
	
	VerificationResult	 *	, old

);


SET_OF_CRLWithCertificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SET_OF_CRLWithCertificates SEC_PROTOTYPE_1(
	
	SET_OF_CRLWithCertificates	 *	, old

);

CRLWithCertificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CRLWithCertificates SEC_PROTOTYPE_1(
	
	CRLWithCertificates	 *	, old

);

/* from afed.c */

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_DName SEC_PROTOTYPE_1(
	
	DName	 *	, namestruct

);

DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_DName SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);
#ifdef STRONG
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_Attribute SEC_PROTOTYPE_1(
	
	Attr	 *	, attr

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_AttributeType SEC_PROTOTYPE_1(
	
	AttrType	 *	, attrtype

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_AttributeValueAssertion SEC_PROTOTYPE_1(
	
	AttrValueAssertion	 *	, ava

);
PE SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV certificate_enc SEC_PROTOTYPE_1(
	
	Certificate	 *	, parm

);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  certificate_dec SEC_PROTOTYPE_1(
	
	PE	  	, pe

);

PE SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV AlgId_enc SEC_PROTOTYPE_1(
	
	AlgId	 *	, parm

);

AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  AlgId_dec SEC_PROTOTYPE_1(
	
	PE	  	, pe

);

PE SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crl_enc SEC_PROTOTYPE_1(
	
	CRL	 *	, parm

);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  crl_dec SEC_PROTOTYPE_1(
	
	PE	  	, pe

);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  str2crl SEC_PROTOTYPE_1(
	
	char	 *	, str

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV printcrl SEC_PROTOTYPE_3(
	
	PS	  	, ps,
	
	CRL	 *	, parm,
	
	int	  	, format

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_crl_cmp SEC_PROTOTYPE_2(
	
	CRL	 *	, a,
	
	CRL	 *	, b

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crl_syntax SEC_PROTOTYPE_0();

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_sntx_dummy SEC_PROTOTYPE_0();

#endif
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CertExtensions SEC_PROTOTYPE_1(
	
	CertExtensions	 *	, certextensions

);

CertExtensions SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CertExtensions SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_Certificates SEC_PROTOTYPE_1(
	
	Certificates	 *	, certificates

);

Certificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_Certificates SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_Certificate SEC_PROTOTYPE_1(
	
	Certificate	 *	, certificate

);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_Certificate SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CertificateSet SEC_PROTOTYPE_1(
	
	SET_OF_Certificate	 *	, certset

);

SET_OF_Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CertificateSet SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CertificatePairSet SEC_PROTOTYPE_1(
	
	SET_OF_CertificatePair	 *	, cpairset

);

SET_OF_CertificatePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CertificatePairSet SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ToBeSigned SEC_PROTOTYPE_1(
	
	ToBeSigned	 *	, tobesigned

);

ToBeSigned SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_ToBeSigned SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_FCPath SEC_PROTOTYPE_1(
	
	FCPath	 *	, fcpath

);

FCPath SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_FCPath SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PKRoot SEC_PROTOTYPE_1(
	
	PKRoot	 *	, pkroot

);

PKRoot SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PKRoot SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PKList SEC_PROTOTYPE_1(
	
	PKList	 *	, pklist

);

PKList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PKList SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CRL SEC_PROTOTYPE_1(
	
	CRL	 *	, crl

);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CRL SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CRLEntry SEC_PROTOTYPE_1(
	
	CRLEntry	 *	, crlentry

);

CRLEntry SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CRLEntry SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CRLEntrySequence SEC_PROTOTYPE_1(
	
	SEQUENCE_OF_CRLEntry	 *	, seq

);

SEQUENCE_OF_CRLEntry SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CRLEntrySequence SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CrlSet SEC_PROTOTYPE_1(
	
	CrlSet	 *	, crlset

);

CrlSet SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CrlSet SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CRLTBS SEC_PROTOTYPE_1(
	
	CRLTBS	 *	, tbs

);

CRLTBS SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CRLTBS SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CRLWithCertificates SEC_PROTOTYPE_1(
	
	CRLWithCertificates	 *	, arg

);

CRLWithCertificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CRLWithCertificates SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_AliasList SEC_PROTOTYPE_1(
	
	AliasList	 *	, alist

);

AliasList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_AliasList SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_SerialNumber SEC_PROTOTYPE_1(
	
	SerialNumber	 *	, serial

);

SerialNumber SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_SerialNumber SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_SET_OF_IssuedCertificate SEC_PROTOTYPE_1(
	
	SET_OF_IssuedCertificate	 *	, isscertset

);

SET_OF_IssuedCertificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_SET_OF_IssuedCertificate SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GRAPHICString SEC_PROTOTYPE_1(
	
	char	 *	, string

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GRAPHICString SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

#ifdef ASN1_NETSCAPE_STUFF
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PublicKeyAndChallenge SEC_PROTOTYPE_1(
	
	PublicKeyAndChallenge	 *	, value

);

PublicKeyAndChallenge SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PublicKeyAndChallenge SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_SignedPublicKeyAndChallenge SEC_PROTOTYPE_1(
	
	SignedPublicKeyAndChallenge	 *	, value

);

SignedPublicKeyAndChallenge SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_SignedPublicKeyAndChallenge SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);
#endif /*ASN1_NETSCAPE_STUFF*/


#if defined(X500) && defined(STRONG)
/*  from  encode/str_ed.c : */
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_TokenTBS SEC_PROTOTYPE_1(
	
	TokenTBS	 *	, token_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_AddArgumentTBS SEC_PROTOTYPE_1(
	
	AddArgumentTBS	 *	, addarg_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CompareArgumentTBS SEC_PROTOTYPE_1(
	
	CompareArgumentTBS	 *	, cmparg_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CompareResultTBS SEC_PROTOTYPE_1(
	
	CompareResultTBS	 *	, cmpres_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ListArgumentTBS SEC_PROTOTYPE_1(
	
	ListArgumentTBS	 *	, listarg_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ListResultTBS SEC_PROTOTYPE_1(
	
	ListResultTBS	 *	, listres_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ListResult SEC_PROTOTYPE_1(
	
	ListResult	 *	, listres

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ModifyEntryArgumentTBS SEC_PROTOTYPE_1(
	
	ModifyEntryArgumentTBS	 *	, modarg_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ModifyRDNArgumentTBS SEC_PROTOTYPE_1(
	
	ModifyRDNArgumentTBS	 *	, modrdnarg_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ReadArgumentTBS SEC_PROTOTYPE_1(
	
	ReadArgumentTBS	 *	, readarg_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ReadResultTBS SEC_PROTOTYPE_1(
	
	ReadResultTBS	 *	, readres_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_RemoveArgumentTBS SEC_PROTOTYPE_1(
	
	RemoveArgumentTBS	 *	, remarg_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_SearchArgumentTBS SEC_PROTOTYPE_1(
	
	SearchArgumentTBS	 *	, searcharg_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_SearchResultTBS SEC_PROTOTYPE_1(
	
	SearchResultTBS	 *	, searchres_tbs

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_SearchResult SEC_PROTOTYPE_1(
	
	SearchResult	 *	, searchres

);

typeDSE_PSAPaddr SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  PSAPaddr_dec SEC_PROTOTYPE_1(
	
	PE	  	, pe

);

#endif  /* X500 & STRONG */


#if defined(USE_STDARG)
int SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV   log_print(PSE pse_handle,char *format, ...);
#else
int SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV   log_print();
#endif

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV cadb_init SEC_PROTOTYPE_1(
	PSE, pse_handle
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_cadb_add_user SEC_PROTOTYPE_2(
	PSE, pse_handle,
	Name	 *	, name
);

SET_OF_IssuedCertificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_cadb_get_user SEC_PROTOTYPE_2(
	PSE, pse_handle,
	Name	 *	, name
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_cadb_add_Certificate SEC_PROTOTYPE_3(
	PSE, pse_handle,
	KeyType		  	, keytype,
	Certificate	 *	, newcert
);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_cadb_get_Certificate SEC_PROTOTYPE_2(
	PSE, pse_handle,
	
	OctetString *	, serial

);

SET_OF_Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_cadb_list_user SEC_PROTOTYPE_1(
	PSE, pse_handle

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  logtime SEC_PROTOTYPE_0();

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_cadb_add_CRLWithCertificates SEC_PROTOTYPE_2(
	PSE, pse_handle,
	
	CRLWithCertificates	 *	, crlwithcerts

);

SET_OF_CRLWithCertificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_cadb_list_CRLWithCertificates SEC_PROTOTYPE_1(
	PSE, pse_handle

);

CRLWithCertificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_cadb_get_CRLWithCertificates SEC_PROTOTYPE_2(
	PSE, pse_handle,
	
	Name	 *	, name

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_encrypt_init SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	void 		**	, context,
	 
	Key		 *	, key,
	
	DName		 *	, dname

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_encrypt_more SEC_PROTOTYPE_3(
	void 		**	, context,
	 
	OctetString	 *	, inoctets,
	
	BitString	 *	, outbits

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_encrypt_end SEC_PROTOTYPE_2(
	void 		**	, context,
	 
	BitString	 *	, outbits

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_encrypt_all SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	OctetString *	, inoctets,
	 BitString *	, outbits,
	 Key *	, key,
	 DName *	, dname
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_decrypt_init SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	void 		**	, context,
	 
	Key		 *	, key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_decrypt_more SEC_PROTOTYPE_3(
	void 		**	, context,
	 
	BitString	 *	, inbits,
	
	OctetString	 *	, outoctets

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_decrypt_end SEC_PROTOTYPE_2(
	void 		**	, context,
	 
	OctetString	 *	, outoctets

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_decrypt_all SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	BitString *	, inbits,
	 OctetString *	, outoctets,
	 Key *	, key
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_sign_init SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	void		**	, context,
	
	Signature	 *	, signature

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_sign_init_with_encryption_key SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	void		**	, context,
	
	Signature	 *	, signature

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_sign_more SEC_PROTOTYPE_2(
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_sign_end SEC_PROTOTYPE_1(
	void		**	, context

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_sign_all SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	OctetString	 *	, in_octets,
	
	Signature	 *	, signature

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_sign_all_with_encryption_key SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	OctetString	 *	, in_octets,
	
	Signature	 *	, signature

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_verify_init SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	void		**	, context,
	
	Signature	 *	, sign,
	
	Certificates	 *	, or_cert,
	
	UTCTime		 *	, time,
	
	PKRoot		 *	, pkroot

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_verify_more SEC_PROTOTYPE_2(
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_verify_end SEC_PROTOTYPE_1(
	void		**	, context

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_verify_all SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	OctetString	 *	, in_octets,
	
	Signature	 *	, sign,
	
	Certificates	 *	, or_cert,
	
	UTCTime		 *	, time,
	
	PKRoot		 *	, pkroot

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_verify_Certificates SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	Certificates	 *	, or_cert,
	
	UTCTime		 *	, time,
	
	PKRoot		 *	, pkroot
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_verify_Certificates_with_CLRs SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	Certificates	 *	, or_cert,
	
	UTCTime		 *	, time,
	
	PKRoot		 *	, pkroot,

        SET_OF_CRL       *      , CRLset,
        
        Boolean		  	, call_af_verify
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_verify_Certificates_with_CRLs SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	Certificates	 *	, or_cert,
	
	UTCTime		 *	, time,
	
	PKRoot		 *	, pkroot,

        SET_OF_CRL       *      , CRLset,
        
        Boolean		  	, call_af_verify
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_set_RevocationCheckOptions SEC_PROTOTYPE_18(
    H_OCSP_CHECK, h_rev_check,
    KeyInfo          *,  pCAKeyInfo,
    SET_OF_CRL*, p_CRLs,
    eRevocationCheckType, RevocationCheckType,
    e_ocsp_auth_scheme, ocsp_auth_scheme,
    Boolean           ,  b_ocsp_query_acceptCRLSign,
    Boolean           ,  b_ocsp_query_requireCertHash,
    Boolean           ,  b_ocsp_query_requireNonce,
    Boolean           ,  b_ocsp_query_sendCertHash,
    Boolean           ,  b_ocsp_query_signRequest,
    char             *,  szResponderUri,
    Boolean           ,  b_retrieveResponse,
    unsigned int      ,  nTimeoutFullMilliSecds,
    char *            ,  szProxyUrl,
    char *            ,  szProxyUser,
    char *            ,  szProxyPassword,
    OctetString      *,  pSavedResponse,
    UTCTime          *,  pTime
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_ocsp_set_PCAListCB SEC_PROTOTYPE_2(
H_OCSP_CHECK    , h_ocsp_check,
PCAList_IF *   ,  p_if
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_set_OCSP_Trace_Function SEC_PROTOTYPE_3(
    H_OCSP_CHECK       ,  h_rev_check,
    OCSPTraceFunc    *,  fpOCSPTraceFunction,
    void             *,  OCSPTraceContext
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_set_OCSPResponse_Base64 SEC_PROTOTYPE_2(
    H_OCSP_CHECK       ,  h_rev_check,
    const char *       ,  szResponse
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_set_OCSP_Trace_Level SEC_PROTOTYPE_2(
    H_OCSP_CHECK       ,  h_rev_check,
    OCSPTraceLevel    ,  OCSPTraceLevel
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_verify_set_OCSP_options SEC_PROTOTYPE_2(
    void *        , verify_ctx,
    H_OCSP_CHECK , h_rev_check
);

/* creates bare Ocsp handle without reading settings from anywhere */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_create_OcspHdl SEC_PROTOTYPE_1(
    H_OCSP_CHECK*  , p_h_rev_check
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_verify_Certificates_with_OCSP SEC_PROTOTYPE_6(
    PSE ,  pse_handle,
    Certificates	 *	 , or_cert,
    UTCTime		 *	     , p_time,
    PKRoot		 *	     , pkroot,
    Boolean              , call_af_verify,
    H_OCSP_CHECK , h_rev_check
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_check_OCSP SEC_PROTOTYPE_4(
 PSE, pse
, Certificates *, or_cert
, UTCTime      *, p_time
, H_OCSP_CHECK, h_rev_check
);

/************************************************************************/
/* Accessors to H_OCSP_CHECK                                                                     */
/************************************************************************/
eRevocationCheckType
SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV GetRevocationCheckType SEC_PROTOTYPE_1(
 H_OCSP_CHECK, h
);

const OcspCheckResults 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV GetOcspResults SEC_PROTOTYPE_1(
 H_OCSP_CHECK, h
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_get_SingleOcspQuery SEC_PROTOTYPE_2(
 H_OCSP_CHECK, h,
 const SingleOCSPQuery **, pp
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_OCSPRespIsFresh SEC_PROTOTYPE_2(
 H_OCSP_CHECK, h,
 Boolean*, p_bRes
);

typedef const char * const_char_p;

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  af_get_OCSPResponseDumpPath SEC_PROTOTYPE_2(
 H_OCSP_CHECK, h
 , const_char_p *, szPath
);

/*
 Search if the certificate is on the CRL.
 If found, entry is set to the appropriate entry (NO COPY OF THE MEMORY, DONT FREE IT) and
 the reason code is returned (see enum CRLReason, 0 = unspecified or unknown).
 If not found, -1 is returned
 */
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_search_CRLEntry SEC_PROTOTYPE_3(
	CRL			*	, crl,
	Certificate	*	, cert,
	CRLEntry	**	, entry
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_check_validity_of_Certificate SEC_PROTOTYPE_2(
	
	UTCTime		 *	, time,
	
	Certificate	 *	, cert

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_check_validity_of_PKRoot SEC_PROTOTYPE_2(
	
	UTCTime	 *	, time,
	
	PKRoot	 *	, pkroot

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_check_validity_of_ToBeSigned SEC_PROTOTYPE_2(
	
	UTCTime		 *	, time,
	
	ToBeSigned	 *	, tbs

);

FCPath SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  reduce_FCPath_to_HierarchyPath SEC_PROTOTYPE_2(
	
	FCPath	 *	, fpath,
	DName    *      , root_name

);

FCPath SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV reduce_FCPath_to_HierarchyPath_by_Issuer SEC_PROTOTYPE_3(
	
	FCPath	 *  , fpath,
	DName    *  , root_name,
    DName    *  , issuer_name
);

Certificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  transform_reducedFCPath_into_Certificates SEC_PROTOTYPE_1(
	
	FCPath	 *	, fpath

);

Crl SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  CRL2Crl SEC_PROTOTYPE_1(
	
	CRL	 *	, crl

);

#ifdef X509v3
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_add_extensions SEC_PROTOTYPE_2(

	char		      * , string,

	CertExtensions	      ** , extensions
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_add_extensions_with_feedback SEC_PROTOTYPE_3(

	char              * , string,

	CertExtensions	 ** , extensions,

    AddExt_Feedback   * , feedback
);


RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV set_standard_extensions SEC_PROTOTYPE_5(
        PSE                     , pse,

        Certificate     *       , cert,

        char            *       , ext_file,

        char            *       , ext_labels,

        int                     , is_ca_cert
);

RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV set_standard_crl_extensions SEC_PROTOTYPE_4(
	PSE	            , pse,
	CRL     	*	, crl,
	char		*	, ext_file,
	char		*	, ext_labels
);

RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV set_standard_crlentry_extensions SEC_PROTOTYPE_5(
	PSE	            , pse,
	CRLEntry    *	, crlentry,
	char		*	, ext_file,
	char		*	, ext_labels,
    char        *   , parm_invalidityDate
);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV check_keyUsageBit SEC_PROTOTYPE_3(

        PSE ,  pse_handle,

        KeyType         , type,
 
        KeyUsageTypes    , usage
 
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV check_critical SEC_PROTOTYPE_1(
	Ext_void	* 	, ext

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV check_all_extensions SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	Certificate	 *	, cert,

	int	 	, index

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV check_basicConstraints SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	Certificate	 *	, cert,

	int	 	, index

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV check_keyUsage SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	Certificate	 *	, cert,

	int	 	, index,

	Boolean	 	, CA

);
Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV check_Policies SEC_PROTOTYPE_2(
	CertificatePolicies  * , tosearch,
	CertExtensions  * , extensions
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV check_certificatePolicies SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	Certificate	 *	, cert,

	int	 	, index

);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV check_cRLDistributionPoints SEC_PROTOTYPE_4(
    PSE 			,  pse_handle,
    Certificate      *      , cert,
    int             	, index,
    SET_OF_CRL	**	, CRLset
);
#endif

Certificate  SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_certify SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	Certificate	*	, tbc_cert,
	
	Validity	*	, validity,
	
	AlgId		*	, sig_alg,
	
	DName		*	, name
	
);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_certify_with_serial SEC_PROTOTYPE_6(
    PSE             , pse_handle,
    Certificate	*	, tbc_cert,
    Validity	*	, validity,
    AlgId		*	, sig_alg,
    DName		*	, name,
    OctetString *   , serial
);


Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_certifyPK SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	KeyInfo		*	, pkey,
	
	Validity	*	, validity,
	
	AlgId		*	, sig_alg,
	
	DName		 *	, name,

        Boolean                 , is_ca_cert

);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_certifyPK_with_serial SEC_PROTOTYPE_7(
    PSE             , pse_handle,
    KeyInfo		*	, pkey,
    Validity	*	, validity,
    AlgId		*	, sig_alg,
    DName		*	, name,
    Boolean			, is_ca_cert,
    OctetString *   , serial
);


#ifdef X500
/*  prototypes from  af/af_dir.c : */

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_dir_enter_Certificate SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	Certificate	 *	, cert,
	
	CertificateType	  	, type

);

SET_OF_Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_dir_retrieve_Certificate SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	DName		 *	, dname,
	
	CertificateType	  	, type

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_dir_delete_Certificate SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	OctetString	 *	, serial,
	
	DName		 *	, issuer,
	
	CertificateType	  	, type

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_dir_enter_CRL SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	CRL	 *	, crl

);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_dir_retrieve_CRL SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	DName	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_dir_enter_ARL SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	CRL	 *	, crl

);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_dir_retrieve_ARL SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	DName	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_dir_enter_CertificatePair SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	CertificatePair	 *	, cpair

);

SET_OF_CertificatePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_dir_retrieve_CertificatePair SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	DName	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_dir_delete_CertificatePair SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	CertificatePair	 *	, cpair

);

#if 0
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_dir_delete_Certificate_from_targetObject SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	DName		 *	, target,
	
	DName		 *	, issuer,
	
	CertificateType	  	, type

);
#endif

#endif /* X500 */



#ifdef AFDBFILE
SET_OF_Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_afdb_retrieve_Certificate SEC_PROTOTYPE_2(
	
	DName	 *	, dname,
	
	KeyType	  	, ktype

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_afdb_enter_Certificate SEC_PROTOTYPE_2(
	Certificate	 *	, cert,
	
	KeyType		  	, ktype

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_afdb_delete_Certificate SEC_PROTOTYPE_4(
        DName * ,  directory_user_dname,
	
	OctetString *	, serial,
	
	DName	    *	, issuer,
	
	KeyType	     	, ktype

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_afdb_enter_CRL_ARL SEC_PROTOTYPE_3(
	
	CRL	 *	, crl,
	char *  , type,
	DName * , issuer

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_afdb_enter_CRL SEC_PROTOTYPE_1(
	
	CRL	 *	, crl

);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_afdb_retrieve_CRL SEC_PROTOTYPE_1(
	
	DName	 *	, dname

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_afdb_enter_ARL SEC_PROTOTYPE_1(
	
	CRL	 *	, crl

);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_afdb_retrieve_ARL SEC_PROTOTYPE_1(
	
	DName	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_afdb_enter_CertificatePair SEC_PROTOTYPE_2(
        DName * ,  directory_user_dname,
	
	CertificatePair	 *	, cpair

);

SET_OF_CertificatePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_afdb_retrieve_CertificatePair SEC_PROTOTYPE_1(
	
	DName	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_afdb_delete_CertificatePair SEC_PROTOTYPE_2(
        DName * ,  directory_user_dname,
	
	CertificatePair	 *	, cpair

);


#endif  /* AFDBFILE */

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_x500_check SEC_PROTOTYPE_0();


CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_create_CRL SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	UTCTime	 *	, lastUpdate,
	
	UTCTime	 *	, nextUpdate,

	AlgId	 *	, sig_alg,

	int	 	, version

);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_create_CRL_NoExts SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	UTCTime	 *	, lastUpdate,
	
	UTCTime	 *	, nextUpdate,

	AlgId	 *	, sig_alg

);

CRLEntry SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_create_CRLEntry SEC_PROTOTYPE_1(
	
	OctetString * 	, serial

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_search_CRLEntry SEC_PROTOTYPE_2(
	
	CRL		 *	, crl,
	
	CRLEntry	 *	, crlentry

);

PSESel SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_open SEC_PROTOTYPE_2(

        ObjId    *      , af_object,

        Boolean         , create

);

PSESel SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_create SEC_PROTOTYPE_1(

        char     *      , objname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_delete SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	char	 *	, objname

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_rename SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, oldname,
	
        char     *	, newname

);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, objname,
	
	ObjId	 *	, objtype

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	char	 *	, objname,
	
	void	 *	, opaque,
	
	ObjId	 *	, opaque_type

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_encode SEC_PROTOTYPE_3(
	
	char	 *	, objname,
	
	void	 *	, opaque,
	
	ObjId	 *	, opaque_type

);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_decode SEC_PROTOTYPE_3(
	
	char	 	*	, objname,
	
	OctetString	*	, ostr,
	
	ObjId	 	*	, opaque_type

);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_cpy_opaque SEC_PROTOTYPE_3(
	
	char		*	, objname,
	
	void	 	*	, opaque,
	
	ObjId	 	*	, opaque_type

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_free SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	void	 **	, opaque,
	
	ObjId	 *	, opaque_type

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_print SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	char	 *	, objname,
	
	void	 *	, opaque,
	
	ObjId	 *	, opaque_oid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_fprint SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	FILE	 *	, ff,
	
	char	 *	, objname,
	
	void	 *	, opaque,
	
	ObjId	 *	, opaque_oid

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_sprint SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	char	 *	, string,
	
	char	 *	, objname,
	
	void	 *	, opaque,
	
	ObjId	 *	, opaque_oid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_reset SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	char	 *	, objname

);

DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_Name SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

#ifdef X509v3
PolicyList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_policies SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);
PolicyList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_policies_static SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);
#endif

AliasList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_AliasList SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

QuipuPWD SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_get_QuipuPWD SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_DHparam SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_DSAcommon SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

SerialNumber SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_SerialNumber SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

#ifdef X509v3
SerialNumber SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_CRLNumber SEC_PROTOTYPE_1(
    PSE ,  pse_handle
);
#endif

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_Certificate SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	KeyType	     	, type,
	
	DName	    *	, issuer,
	
	OctetString *	, serial

);

SET_OF_Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_CertificateSet SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	KeyType	  	, type

);

SET_OF_CertificatePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_CertificatePairSet SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

FCPath SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_FCPath SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	DName	 *	, name

);
FCPath SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_pse_get_FCPath_by_Issuer SEC_PROTOTYPE_3(
    PSE         , pse_handle,
    DName	 *	, name,
    DName    *  , issuer_name
);

FCPath SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_FCPath_static SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	DName	 *	, name

);

Certificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_Certificates SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	KeyType	  	, type,
	
	DName	 *	, name

);

PKRoot SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_PKRoot SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

PKRoot SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_PKRoot_static SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

PKList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_PKList SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	KeyType	  	, type

);

PKList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_PKList_static SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	KeyType	  	, type

);


PKList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_pse_get_PCAList SEC_PROTOTYPE_1(
        PSE ,  pse_handle
);

PKList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_pse_get_PCAList_static SEC_PROTOTYPE_1(
        PSE ,  pse_handle
);


CrlSet SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_CrlSet SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

CrlSet SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_CrlSet_static SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_Certificate SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	KeyType		  	, type,
	
	Certificate	 *	, cert,
	
	Boolean		  	, hierarchy

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_FCPath SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	FCPath	 *	, fcpath

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_CertificatePairSet SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	SET_OF_CertificatePair	 *	, cpairset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_AliasList SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	AliasList	 *	, alist

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_QuipuPWD SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	QuipuPWD	 	, pwd

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_SerialNumber SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	SerialNumber	 *	, serial

);

#ifdef X509v3
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_CRLNumber SEC_PROTOTYPE_2(
    PSE ,  pse_handle,
    CRLNumber	 *	, serial
);
#endif

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_PKRoot SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	PKRoot	 *	, pkroot

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_PKList SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	KeyType	  	, type,
	
	PKList	 *	, list

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_PCAList SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	PKList	 *	, list

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_CrlSet SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	CrlSet	 *	, crlset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_DHparam SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	AlgId	 *	, dhparam

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_DSAcommon SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	AlgId	 *	, dsacommon

);

#ifdef X509v3
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_policies SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	PolicyList	 *	, policies

);
#endif

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_add_PK SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	KeyType		  	, type,
	
	ToBeSigned	 *	, tbs

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_add_PCA SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	ToBeSigned	 *	, tbs

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_delete_PK SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	KeyType	     	, type,
	
	DName	    *	, name,
	
	DName	    *	, issuer,
	
	OctetString *	, serial

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_delete_PCA SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	DName	    *	, name

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_add_CertificatePairSet SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	SET_OF_CertificatePair	 *	, cpairset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_add_CRL SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Crl	 *	, crlpse

);

#ifdef X509v3
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_add_globalpolicies SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Certificate	*	, cert
	
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_add_policies SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	Certificate	*	, cert,
	
	FCPath	*	, forwardpath,
	
	DName	*	, pkroot

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_add_policy SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	ObjId	 *	, policy,

	DName	 *	, issuer,

	GeneralNames	 *	, alt_issuer

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_delete_policy SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	DName	 *	, issuer,

	ObjId	 *	, policyIdentifier

);
#endif

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_delete_CRL SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	DName	 *	, issuer

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_exchange_PK SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	KeyType		  	, type,
	
	ToBeSigned	 *	, tbs

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_exchange_PCAPK SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	ToBeSigned	 *	, tbs

);

DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_owner SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	KeyType	  	, type,
	
	KeyInfo	 *	, pk

);

KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_PK SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	KeyType	     	, type,
	
	DName	    *	, subject,
	
	DName	    *	, issuer,
	
	OctetString *	, serial

);

ToBeSigned SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_TBS SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	KeyType	     	, type,
	
	DName	    *	, subject,
	
	DName	    *	, issuer,
	
	OctetString *	, serial

);

KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_PCAPK SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	DName	    *	, subject,
	
	DName	    *	, issuer,
	
	OctetString *	, serial

);

ToBeSigned SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_PCATBS SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	DName	    *	, subject,
	
	DName	    *	, issuer,
	
	OctetString *	, serial

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_gen_key SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	Key	 *	, key,
	
	KeyType	  	, ktype,
	
	Boolean	  	, replace

);

AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_signAI SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);



OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_incr_serial SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

#ifdef X509v3
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_incr_CRLNumber SEC_PROTOTYPE_1(
    PSE ,  pse_handle
);
#endif

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_update_pse SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	Certificate 	**	, parm_cert,
	
	FCPath		**	, parm_fcpath,
	
	PKRoot		**	, parm_pkroot,
	
	char		**	, parm_finger_print

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_encrypt_key SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	EncryptedKey	 *	, encrypted_key,
	
	Key		 *	, plain_key,
	
	Key		 *	, encryption_key,
	
	DName		 *	, name,
	
	AlgId		 *	, encryption_key_algid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_decrypt_key SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	EncryptedKey	 *	, encrypted_key,
	
	Key		 *	, plain_key,
	
	AlgId		 *	, decryption_key_algid

);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_create_Certificate SEC_PROTOTYPE_10(
        PSE ,  pse_handle,
	
	KeyInfo	    *	, keyinfo,
	
	AlgId	    *	, sig_alg,
	
	char	    *	, obj_name,
	
	DName	    *	, subject,
	
	OctetString *	, serial,

	GeneralNames * 	, subject_names,
 
        KeyIdentifier * , subjKeyId,

        Boolean         , CA,

	KeyUsage    *	, key_usage

);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_get_objoid SEC_PROTOTYPE_1(
	
	char	 *	, objname

);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_get_objoid_static SEC_PROTOTYPE_1(
	
	char	 *	, objname

);

AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_get_signature_alg SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	AlgId	 *	, sig_alg,
	
	AlgId	 *	, key_alg

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_get_oidname SEC_PROTOTYPE_1(
	
	ObjId	 *	, objtype

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_search_Certificate SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	KeyType	  	, type,
	
	DName	 *	, dname,
	
	Boolean		, verify_cert,
	
	Certificate **	, cert
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_search_Certificate_IS SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	KeyType	  	, type,
	
	DName	 *	, issuer,
	SerialNumber	 *	, serial,
	
	Boolean		, verify_cert,
	
	Certificate **	, cert

);
#ifdef X509v3
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_search_Certificate_KeyID SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	KeyType	  	, type,
	
    SubjectKeyId *   , keyid,
	
	Boolean		, verify_cert,
	
	Certificate **	, cert

);
#endif
Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_PKRoot2Protocert SEC_PROTOTYPE_1(
	
	PKRoot	 *	, pkroot

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_OctetString2SignedFile SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	char		 *	, file,
	
	OctetString	 *	, ostr,
	
	Boolean		  	, withcerts,
	
	AlgId		 *	, signai

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_SignedFile2OctetString SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	char	 *	, file

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Attr SEC_PROTOTYPE_1(
	
	Attr	 *	, attr

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Attr SEC_PROTOTYPE_1(
	
	Attr	**	, attr

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AttrValues SEC_PROTOTYPE_1(
	AttrValues	*	, set
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AttrValues SEC_PROTOTYPE_1(
	
	AttrValues	**	, set

);
#define aux_free_SETOFAttr aux_free_SET_OF_Attr

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_Attr SEC_PROTOTYPE_1(
	
	SET_OF_Attr	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SET_OF_Attr SEC_PROTOTYPE_1(
	SET_OF_Attr	*	, p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_OctetString SEC_PROTOTYPE_1(
	
	SET_OF_OctetString	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SET_OF_OctetString SEC_PROTOTYPE_1(
	SET_OF_OctetString	*	, set
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SEQUENCE_OF_ObjId SEC_PROTOTYPE_1(
	SEQUENCE_OF_ObjId	**	, set
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SEQUENCE_OF_ObjId SEC_PROTOTYPE_1(
	SEQUENCE_OF_ObjId	*	, set
);

#if defined(X500) && defined(STRONG)
/*  prototypes from  af/str_free.c : */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AttrAttrTypeCHOICE SEC_PROTOTYPE_1(
	
	AttrAttrTypeCHOICE	 *	, choice

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AttrAttrTypeCHOICE SEC_PROTOTYPE_1(
	
	AttrAttrTypeCHOICE	**	, choice

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_AttrAttrTypeCHOICE SEC_PROTOTYPE_1(
	
	SET_OF_AttrAttrTypeCHOICE	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Ava SEC_PROTOTYPE_1(
	
	AttrValueAssertion	 *	, ava

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Ava SEC_PROTOTYPE_1(
	
	AttrValueAssertion	**	, ava

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EntryINFO SEC_PROTOTYPE_1(
	
	EntryINFO	 *	, ent

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EntryINFO SEC_PROTOTYPE_1(
	
	EntryINFO	**	, ent

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_EntryINFO SEC_PROTOTYPE_1(
	
	SET_OF_EntryINFO	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_ObjId SEC_PROTOTYPE_1(
	
	SET_OF_ObjId	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EntryInfoSEL SEC_PROTOTYPE_1(
	
	EntryInfoSEL	 *	, eis

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EntryInfoSEL SEC_PROTOTYPE_1(
	
	EntryInfoSEL	**	, eis

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SecurityParameters SEC_PROTOTYPE_1(
	
	SecurityParameters	 *	, sp

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SecurityParameters SEC_PROTOTYPE_1(
	
	SecurityParameters	**	, sp

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ServiceControls SEC_PROTOTYPE_1(
	
	ServiceControls	 *	, sc

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ServiceControls SEC_PROTOTYPE_1(
	
	ServiceControls	**	, sc

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CommonArguments SEC_PROTOTYPE_1(
	
	CommonArguments	 *	, ca

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CommonArguments SEC_PROTOTYPE_1(
	
	CommonArguments	**	, ca

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CommonRes SEC_PROTOTYPE_1(
	
	CommonRes	 *	, cr

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CommonRes SEC_PROTOTYPE_1(
	
	CommonRes	**	, cr

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SECExtension SEC_PROTOTYPE_1(
	
	SECExtension	 *	, secext

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SECExtension SEC_PROTOTYPE_1(
	
	SECExtension	**	, secext

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_SECExtension SEC_PROTOTYPE_1(
	
	SET_OF_SECExtension	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_TokenTBS SEC_PROTOTYPE_1(
	
	TokenTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TokenTBS SEC_PROTOTYPE_1(
	
	TokenTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AddArgumentTBS SEC_PROTOTYPE_1(
	
	AddArgumentTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AddArgumentTBS SEC_PROTOTYPE_1(
	
	AddArgumentTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CompareArgumentTBS SEC_PROTOTYPE_1(
	
	CompareArgumentTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CompareArgumentTBS SEC_PROTOTYPE_1(
	
	CompareArgumentTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CompareResultTBS SEC_PROTOTYPE_1(
	
	CompareResultTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CompareResultTBS SEC_PROTOTYPE_1(
	
	CompareResultTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ListArgumentTBS SEC_PROTOTYPE_1(
	
	ListArgumentTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ListArgumentTBS SEC_PROTOTYPE_1(
	
	ListArgumentTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SubordEntry SEC_PROTOTYPE_1(
	
	SubordEntry	 *	, sub

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SubordEntry SEC_PROTOTYPE_1(
	
	SubordEntry	**	, sub

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_SubordEntry SEC_PROTOTYPE_1(
	
	SET_OF_SubordEntry	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ListInfo SEC_PROTOTYPE_1(
	
	ListInfo	 *	, info

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ListInfo SEC_PROTOTYPE_1(
	
	ListInfo	**	, info

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ListResultTBS SEC_PROTOTYPE_1(
	
	ListResultTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ListResultTBS SEC_PROTOTYPE_1(
	
	ListResultTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EntryModification SEC_PROTOTYPE_1(
	
	EntryModification	 *	, em

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EntryModification SEC_PROTOTYPE_1(
	
	EntryModification	**	, em

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SEQUENCE_OF_EntryModification SEC_PROTOTYPE_1(
	
	SEQUENCE_OF_EntryModification	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ModifyEntryArgumentTBS SEC_PROTOTYPE_1(
	
	ModifyEntryArgumentTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ModifyEntryArgumentTBS SEC_PROTOTYPE_1(
	
	ModifyEntryArgumentTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ModifyRDNArgumentTBS SEC_PROTOTYPE_1(
	
	ModifyRDNArgumentTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ModifyRDNArgumentTBS SEC_PROTOTYPE_1(
	
	ModifyRDNArgumentTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ReadArgumentTBS SEC_PROTOTYPE_1(
	
	ReadArgumentTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ReadArgumentTBS SEC_PROTOTYPE_1(
	
	ReadArgumentTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ReadResultTBS SEC_PROTOTYPE_1(
	
	ReadResultTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ReadResultTBS SEC_PROTOTYPE_1(
	
	ReadResultTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_RemoveArgumentTBS SEC_PROTOTYPE_1(
	
	RemoveArgumentTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_RemoveArgumentTBS SEC_PROTOTYPE_1(
	
	RemoveArgumentTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_PE SEC_PROTOTYPE_1(
	
	SET_OF_PE	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_OperationProgress SEC_PROTOTYPE_1(
	
	OperationProgress	**	, op

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PSAPaddr SEC_PROTOTYPE_1(
	
	typeDSE_PSAPaddr	 *	, psap

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PSAPaddr SEC_PROTOTYPE_1(
	
	typeDSE_PSAPaddr	**	, psap

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AccessPoint SEC_PROTOTYPE_1(
	
	AccessPoint	 *	, accpoint

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AccessPoint SEC_PROTOTYPE_1(
	
	AccessPoint	**	, accpoint

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_AccessPoint SEC_PROTOTYPE_1(
	
	SET_OF_AccessPoint	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ContReference SEC_PROTOTYPE_1(
	
	ContReference	 *	, cref

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ContReference SEC_PROTOTYPE_1(
	
	ContReference	**	, cref

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_ContReference SEC_PROTOTYPE_1(
	
	SET_OF_ContReference	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PartialOutQual SEC_PROTOTYPE_1(
	
	PartialOutQual	 *	, poq

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PartialOutQual SEC_PROTOTYPE_1(
	
	PartialOutQual	**	, poq

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SearchInfo SEC_PROTOTYPE_1(
	
	SearchInfo	 *	, info

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SearchInfo SEC_PROTOTYPE_1(
	
	SearchInfo	**	, info

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SFilterSubstrings SEC_PROTOTYPE_1(
	
	SFilterSubstrings	 *	, substrgs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SFilterSubstrings SEC_PROTOTYPE_1(
	
	SFilterSubstrings	**	, substrgs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SFilterItem SEC_PROTOTYPE_1(
	
	SFilterItem	 *	, fi

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SFilterItem SEC_PROTOTYPE_1(
	
	SFilterItem	**	, fi

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SFilter SEC_PROTOTYPE_1(
	
	SFilter	 *	, flt

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SFilter SEC_PROTOTYPE_1(
	
	SFilter	**	, flt

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_SFilter SEC_PROTOTYPE_1(
	
	SET_OF_SFilter	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_StringsCHOICE SEC_PROTOTYPE_1(
	
	StringsCHOICE	 *	, choice

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_StringsCHOICE SEC_PROTOTYPE_1(
	
	StringsCHOICE	**	, choice

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SEQUENCE_OF_StringsCHOICE SEC_PROTOTYPE_1(
	
	SEQUENCE_OF_StringsCHOICE	**	, seq

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SearchArgumentTBS SEC_PROTOTYPE_1(
	
	SearchArgumentTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SearchArgumentTBS SEC_PROTOTYPE_1(
	
	SearchArgumentTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SearchResultTBS SEC_PROTOTYPE_1(
	
	SearchResultTBS	 *	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SearchResultTBS SEC_PROTOTYPE_1(
	
	SearchResultTBS	**	, tbs

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Token SEC_PROTOTYPE_1(
	
	Token	 *	, tok

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Token SEC_PROTOTYPE_1(
	
	Token	**	, tok

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AddArgument SEC_PROTOTYPE_1(
	
	AddArgument	 *	, addarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AddArgument SEC_PROTOTYPE_1(
	
	AddArgument	**	, addarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CompareArgument SEC_PROTOTYPE_1(
	
	CompareArgument	 *	, comparearg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CompareArgument SEC_PROTOTYPE_1(
	
	CompareArgument	**	, comparearg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CompareResult SEC_PROTOTYPE_1(
	
	CompareResult	 *	, compareres

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CompareResult SEC_PROTOTYPE_1(
	
	CompareResult	**	, compareres

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ListArgument SEC_PROTOTYPE_1(
	
	ListArgument	 *	, listarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ListArgument SEC_PROTOTYPE_1(
	
	ListArgument	**	, listarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ListResult SEC_PROTOTYPE_1(
	
	ListResult	 *	, listres

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ListResult SEC_PROTOTYPE_1(
	
	ListResult	**	, listres

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_ListResult SEC_PROTOTYPE_1(
	
	SET_OF_ListResult	**	, set

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ModifyEntryArgument SEC_PROTOTYPE_1(
	
	ModifyEntryArgument	 *	, modifyentryarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ModifyEntryArgument SEC_PROTOTYPE_1(
	
	ModifyEntryArgument	**	, modifyentryarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ModifyRDNArgument SEC_PROTOTYPE_1(
	
	ModifyRDNArgument	 *	, modifyrdnarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ModifyRDNArgument SEC_PROTOTYPE_1(
	
	ModifyRDNArgument	**	, modifyrdnarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ReadArgument SEC_PROTOTYPE_1(
	
	ReadArgument	 *	, readarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ReadArgument SEC_PROTOTYPE_1(
	
	ReadArgument	**	, readarg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ReadResult SEC_PROTOTYPE_1(
	
	ReadResult	 *	, readres

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ReadResult SEC_PROTOTYPE_1(
	
	ReadResult	**	, readres

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_RemoveArgument SEC_PROTOTYPE_1(
	
	RemoveArgument	 *	, removearg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_RemoveArgument SEC_PROTOTYPE_1(
	
	RemoveArgument	**	, removearg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SearchArgument SEC_PROTOTYPE_1(
	
	SearchArgument	 *	, searcharg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SearchArgument SEC_PROTOTYPE_1(
	
	SearchArgument	**	, searcharg

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SearchResult SEC_PROTOTYPE_1(
	
	SearchResult	 *	, searchres

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SearchResult SEC_PROTOTYPE_1(
	
	SearchResult	**	, searchres

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_SearchResult SEC_PROTOTYPE_1(
	
	SET_OF_SearchResult	**	, set

);


/*  prototypes from  af/str_int.c :  */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_random SEC_PROTOTYPE_1(
	
	struct random_number	 **	, random

);

struct SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV SecurityServices *use_serv_secude SEC_PROTOTYPE_0();

struct SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV signature *secudesigned SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	caddr_t	  	, arg,
	
	int	  	, type,
	
	AlgId    *	, algorithm

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secudeverify SEC_PROTOTYPE_0();

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_ckpath SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	caddr_t			  	, arg,
	
	struct certificate_list	 *	, quipu_cpath,
	
	struct signature	 *	, quipu_sig,
	
	DN			 *	, nameptr,
	
	int			  	, type

);

struct SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV certificate_list *secude_mkpath SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

struct SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV encrypted *secudeencrypted SEC_PROTOTYPE_0();

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secudedecrypted SEC_PROTOTYPE_0();

struct SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV Nonce *secudemknonce SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	AlgId *	, algorithm

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secudecknonce SEC_PROTOTYPE_1(
	
	struct Nonce	 *	, nonce

);


/*  prototypes from  af/str_print.c :  */

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_TokenTBS SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	TokenTBS	 *	, tok_tbs

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_Token SEC_PROTOTYPE_2(
	
	FILE	 *	, ff,
	
	Token	 *	, tok

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_AddArgument SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	AddArgument	 *	, addarg

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_CompareArgument SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	CompareArgument	 *	, comparearg

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_CompareResult SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	CompareResult	 *	, compareres

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_ListArgument SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	ListArgument	 *	, listarg

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_ListResult SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	ListResult	 *	, listres

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_ModifyEntryArgument SEC_PROTOTYPE_2(
	
	FILE			 *	, ff,
	
	ModifyEntryArgument	 *	, modifyentryarg

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_ModifyRDNArgument SEC_PROTOTYPE_2(
	
	FILE			 *	, ff,
	
	ModifyRDNArgument	 *	, modifyrdnarg

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_ReadArgument SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	ReadArgument	 *	, readarg

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_ReadResult SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	ReadResult	 *	, readres

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_RemoveArgument SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	RemoveArgument	 *	, removearg

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_SearchArgument SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	SearchArgument	 *	, searcharg

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_SearchResult SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	SearchResult	 *	, searchres

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_CommonArguments SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	CommonArguments	 *	, ca

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_CommonRes SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	CommonRes	 *	, cr

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strong_fprint_SecurityParameters SEC_PROTOTYPE_2(
	
	FILE			 *	, ff,
	
	SecurityParameters	 *	, sec_parm

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CertificationPath SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE			 *	, ff,
	
	CertificationPath	 *	, certpath

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CertificatePairs SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE			 *	, ff,
	
	CertificatePairs	 *	, certpairs

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CertificatePair SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE		 *	, ff,
	
	CertificatePair	 *	, cpair

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_random SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	BitString	 *	, random

);

#endif /* if defined(X500) && defined(STRONG) */



/* 
 *	src/aux
 */
 
AliasFile SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_alias SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	char	 *	, alias

);

DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alias2DName SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Name	 *	, alias

);

Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alias2Name SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Name	 *	, alias

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cat_groupORalias SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	Name	 *	, alias,
	
	SET_OF_NAME **	, list

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_DName2alias SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	DName		 *	, dname,
	
	AliasType	  	, type

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_DName2NameOrAlias SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	DName		 *	, dname

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_Name2NameOrAlias SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Name		 *	, name

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_Name2alias SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	Name		 *	, name,
	
	AliasType	  	, type

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_DName2aliasf SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	DName		 *	, dname,
	
	AliasType	  	, type,
	
	AliasFile	  	, afile

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_Name2aliasf SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	char		 *	, name,
	
	AliasType	  	, type,
	
	AliasFile	  	, afile

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_alias_name SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	char		 *	, alias,
	
	Name		 *	, name,
	
	AliasFile	  	, aliasf,
	
	Boolean		  	, prior,
	
	Boolean		  	, writef

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_alias SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	char		 *	, alias,
	
	DName		 *	, dn,
	
	AliasFile	  	, aliasf,
	
	Boolean		  	, prior,
	
	Boolean		  	, writef

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_group_alias SEC_PROTOTYPE_6(
        PSE ,  pse_handle,
	
	char		 *	, alias,
	
	DName		 *	, dn,
	
	AliasFile	  	, aliasf,
	
	Boolean		  	, prior,
	
	Boolean		  	, writef

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_delete_alias SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	char		 *	, alias,
	
	AliasFile	  	, aliasf,
	
	Boolean		  	, writef

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_delete_group_alias SEC_PROTOTYPE_5(
        PSE ,  pse_handle,
	
	char		 *	, alias,
	
	DName		 *	, dname,
	
	AliasFile	  	, aliasf,
	
	Boolean		  	, writef

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_alias2dnames SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	 *	, ff,
	
	char	 *	, alias

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_alias2dname SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	 *	, ff,
	
	char	 *	, alias

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_dname2alias SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	 *	, ff,
	
	char	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_alias2dnames SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
		
	char	 *	, alias

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_alias2dname SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	char	 *	, alias

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_dname2alias SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	char	 *	, dname

);

Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_search_AliasList SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	Name	 *	, name,
	
	char	 *	, pattern

);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_alias_chkfile SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	Name		 *	, name,
	
	AliasFile	  	, aliasf

);

Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_next_AliasList SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Name	 *	, name

);

Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alias_nxtname SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Boolean	  	, reset

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alias_getallf SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 	*	, name,
	
	AliasFile		, aliasf

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alias_getall SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, name,
	
	AliasType,	type

);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_get_AliasList SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_reset_AliasList SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_put_AliasList SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	AliasFile	  	, aliasf

);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_check_AliasList SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	FILE	 *	, ff

);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_alias_writeprotection SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

AliasList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_select_AliasList SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	AliasFile	  	, aliasf

);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_filter_AliasList SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	Boolean	  	, user_aliases,
	
	Boolean	  	, system_aliases

);

AliasFile SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_alias_filter SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_Name2DName SEC_PROTOTYPE_1(
	
	char	 *	, name

);

DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_Name2DName_T61 SEC_PROTOTYPE_1(
	char	 *	, name
);
DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_Name2DName_UTF8 SEC_PROTOTYPE_1(
	char	 *	, name
);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_DName2Name SEC_PROTOTYPE_1(
	
	DName	 *	, name_ae

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_DName2Attr SEC_PROTOTYPE_2(
	
	DName	 *	, name_ae,
	
	char	 *	, attr_key

);

/* added for PKCS#11 */
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_ObjId2Attr SEC_PROTOTYPE_2(
	DName	 *	, name_ae,

	ObjId	 *	, attr_oid
);


DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_ORName2DName SEC_PROTOTYPE_1(
	
	char	 *	, name

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_DName2CAPITALName SEC_PROTOTYPE_1(
	
	DName	 *	, name_ae

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_DName2CAPITALString SEC_PROTOTYPE_2(
	
	DName	 *	, name_ae,
	
	char     *	, separator

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_DName2afdbname SEC_PROTOTYPE_2(
	
	DName	 *	, dname,
	
	Boolean	  	, create

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_AliasList SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	AliasList	 *	, aliaslist

);

#ifdef ASN1_NETSCAPE_STUFF
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_SignedPublicKeyAndChallenge SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	SignedPublicKeyAndChallenge	 *	, spkac

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PublicKeyAndChallenge SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	PublicKeyAndChallenge	 *	, pkac

);
#endif /*ASN1_NETSCAPE_STUFF*/

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_DNameOrAlias SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, string,
	
	DName	 *	, dname

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_DName SEC_PROTOTYPE_2(
	
	char	 *	, string,
	
	DName	 *	, dname

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_NameOrAlias SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, string,
	
	Name	 *	, name

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_GRAPHICString SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	char		 *	, graphic

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PSESel SEC_PROTOTYPE_2(
	
	char	 *	, string,
	
	PSESel	 *	, pse

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_Version SEC_PROTOTYPE_1(
	
	char	 *	, string

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_version SEC_PROTOTYPE_1(
	
	char	 *	, string

);

#ifdef X509v3

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_GeneralNames SEC_PROTOTYPE_3(
	
	char	 *	, string,

        char     *      , type,

        GeneralNames *  , generalNames

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_AuthorityKeyId SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_AuthorityKeyId *    , authorityKeyId

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_KeyUsage SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_KeyUsage *          , keyUsage
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_ExtKeyUsage SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_ExtKeyUsage *          , extKeyUsage
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PrivateKeyUsagePeriod SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_PrivateKeyUsagePeriod  * , period
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PolicyQualifierInfo SEC_PROTOTYPE_2(
	
	char	 *	, string,

        PolicyQualifierInfo *   , qualifier
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_DisplayText SEC_PROTOTYPE_2(
	char	 *	, string,
	DisplayText *     , policy
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_UserNotice SEC_PROTOTYPE_2(
	char	 *	, string,
	UserNotice *     , policy
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PolicyInformation SEC_PROTOTYPE_2(
	
	char	 *	, string,

        PolicyInformation *     , policy
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_CertificatePolicies SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_CertificatePolicies *       , policies
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_MappingElement SEC_PROTOTYPE_2(
	
	char	 *	, string,

        MappingElement *        , policy
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PolicyMappings SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_PolicyMappings *    , policyMap
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_DirectoryAttributes SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Attr     *      , attr
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_SubjectDirectoryAttr SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_DirectoryAttributes *  , dirAttr
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_BasicConstraints SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_BasicConstraints *  , constraints
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_GeneralSubtrees SEC_PROTOTYPE_2(
	
	char	 *	, string,

        GeneralSubtrees  *      , subtree
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_NameConstraints SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_NameConstraints *  , constraints
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PolicyConstraints SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_PolicyConstraints *  , constraints
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_AuthInfoAccess SEC_PROTOTYPE_1(
	
	Ext_AuthInfoAccess *  , authInfoAccess

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_AuthInfoAccess SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_AuthInfoAccess *  , authInfoAccess


);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_AuthInfoAccess SEC_PROTOTYPE_2(
	
	char	 *		, string,

	Ext_AuthInfoAccess *  , authInfoAccess

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_DistributionPoint SEC_PROTOTYPE_2(
	
	char	 *	, string,

        DistributionPoint  *    , distrPoint
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_CRLDistributionPoints SEC_PROTOTYPE_2(
	
	char	 *	, string,

        Ext_CRLDistPoints *  , distrPoints
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_IssuingDistPoint SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	IssuingDistPoint	 *	, idp

);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_CRLReason SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	CRLReason	  	, reason

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_nonSupported SEC_PROTOTYPE_2(
	
	char	 *	, string,

        SEQUENCE_OF_Extension *  , nonSupported
);

#endif

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PSEToc SEC_PROTOTYPE_3(
	
	char	 *	, string,
	
	PSEToc	 *	, toc1,
	
	PSEToc	 *	, toc2

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_Certificate SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char		 *	, string,
	
	Certificate	 *	, cert

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_Serialnumber SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	OctetString	 *	, serial

);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_SerialNumberX SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	OctetString	 *	, serialnumber

);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_ToBeSigned SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char		 *	, string,
	
	ToBeSigned	 *	, tbs

);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_FCPath SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, string,
	
	FCPath	 *	, fcpath

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_Certificates SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char		 *	, string,
	
	Certificates	 *	, certs

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_Validity SEC_PROTOTYPE_2(
	
	char	 *	, string,
	
	Validity *	, valid

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_RootInfo SEC_PROTOTYPE_3(
	
	char	 *	, string,
	
	Serial	 *	, rootinfo,
	
	Boolean	  	, new_

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PKRoot SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, string,
	
	PKRoot	 *	, pkroot

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PKList SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, string,
	
	PKList	 *	, pklist

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_CRLEntry SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	CRLEntry	 *	, crlentry

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_CRL SEC_PROTOTYPE_2(
	
	char	 *	, string,
	
	CRL	 *	, crl

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_CRLTBS SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	CRLTBS	 *	, tbs

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_CertificateSet SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char			 *	, string,
	
	SET_OF_Certificate	 *	, certset

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_CertificatePairSet SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char			 *	, string,
	
	SET_OF_CertificatePair	 *	, cpair

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_Crl SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, string,
	
	Crl	 *	, crlpse

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_CrlSet SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, string,
	
	CrlSet	 *	, crlset

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_policies SEC_PROTOTYPE_2(
	
	char			 *	, string,
	
	PolicyList	 *	, policies

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_IssuedCertificate SEC_PROTOTYPE_2(
	
	char			 *	, string,
	
	IssuedCertificate	 *	, isscert

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_SET_OF_IssuedCertificate SEC_PROTOTYPE_2(
	
	char				 *	, string,
	
	SET_OF_IssuedCertificate	 *	, isscertset

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_SET_OF_Name SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	SET_OF_Name	 *	, nameset

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_CRLWithCertificates SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char		 *	, string,
	
	CRLWithCertificates	 *	, arg

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_SET_OF_CRLWithCertificates SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char			 *	, string,
	
	SET_OF_CRLWithCertificates	 *	, set

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_VerificationResult SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char			 *	, string,
	
	VerificationResult	 *	, verres

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_TrustPath SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char			 *	, string,
	
	VerificationResult	 *	, verres

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_error SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char	 *	, string,
	
	int	  	, verbose

);

/*
AZ 20041105120500Z: There is no such aux_free_GeneralTime. However, it is mentioned in the documentation
of d_GeneralTime.
*/
#define aux_free_GeneralTime(arg) aux_free_UTCTime(arg)

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_UTCTime SEC_PROTOTYPE_1(
        UTCTime	**  , p
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_UTCTime SEC_PROTOTYPE_2(
        char *  , string,
        UTCTime *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_UTCTime SEC_PROTOTYPE_2(
        FILE *  , ff,
        UTCTime *  , p_data
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_UTCTime SEC_PROTOTYPE_1(
        UTCTime *  , p_data
);








#ifdef X509v3

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  aux_fprint_GeneralNames SEC_PROTOTYPE_3(
	
	FILE	 *	, ff,

        char     *      , type,

        GeneralNames *  , generalNames

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_AuthorityKeyId SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_AuthorityKeyId	 *	, authorityKeyId

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_KeyUsage SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_KeyUsage	 *	, keyUsage

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_ExtKeyUsage SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_ExtKeyUsage	 *	, extKeyUsage

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PrivateKeyUsagePeriod SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_PrivateKeyUsagePeriod	 *	, period

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PolicyQualifierInfo SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	PolicyQualifierInfo	 *	, qualifier

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  aux_fprint_DisplayText SEC_PROTOTYPE_2(
	FILE		 *	, ff,
	DisplayText *     , policy
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  aux_fprint_UserNotice SEC_PROTOTYPE_2(
	FILE		 *	, ff,
	UserNotice *     , policy
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PolicyInformation SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	PolicyInformation	 *	, policy

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CertificatePolicies SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_CertificatePolicies	 *	, policies

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_MappingElement SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	MappingElement	 *	, policy

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PolicyMappings SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_PolicyMappings	 *	, policyMap

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_DirectoryAttributes SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Attr	 *	, attr

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SubjectDirectoryAttr SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_DirectoryAttributes	 *	, dirAttr

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_BasicConstraints SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_BasicConstraints	 *	, constraints

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_GeneralSubtrees SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	GeneralSubtrees	 *	, subtree

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_NameConstraints SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_NameConstraints	 *	, constraints

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PolicyConstraints SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_PolicyConstraints	 *	, constraints

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_DistributionPoint SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	DistributionPoint	 *	, distrPoint

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CRLDistributionPoints SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	Ext_CRLDistPoints	 *	, distrPoints

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_nonSupported SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	SEQUENCE_OF_Extension	 *	, nonSupported

);
#endif

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_AliasList SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	AliasList	 *	, aliaslist

);

#ifdef ASN1_NETSCAPE_STUFF
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SignedPublicKeyAndChallenge SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	SignedPublicKeyAndChallenge	 *	, spkac

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PublicKeyAndChallenge SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	PublicKeyAndChallenge	 *	, pkac

);
#endif /*ASN1_NETSCAPE_STUFF*/

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_DNameOrAlias SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	DName	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_DName SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	DName	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_NameOrAlias SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	Name	 *	, name

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_GRAPHICString SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	char	*	, graphic

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PSESel SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	PSESel	 *	, pse

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_Version SEC_PROTOTYPE_1(
	
	FILE	*	, ff

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_version SEC_PROTOTYPE_1(
	
	FILE	*	, ff

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PSEToc SEC_PROTOTYPE_3(
	
	FILE	*	, ff,
	
	PSEToc	 *	, toc1,
	
	PSEToc	 *	, toc2

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_Certificate SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	Certificate	 *	, cert

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_Serialnumber SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	OctetString	 *	, serial

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_ToBeSigned SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	ToBeSigned	 *	, tbs

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_FCPath SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	FCPath	 *	, fcpath

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_Certificates SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	Certificates	 *	, certs

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_Validity SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	Validity *	, valid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_RootInfo SEC_PROTOTYPE_3(
	
	FILE	*	, ff,
	
	Serial	 *	, rootinfo,
	
	Boolean	  	, new_

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PKRoot SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	PKRoot	 *	, pkroot

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PKList SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	PKList	 *	, pklist

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CRLEntry SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	CRLEntry	 *	, crlentry

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CRL SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	CRL	 *	, crl

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CRLTBS SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	CRLTBS	 *	, tbs

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CertificateSet SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	SET_OF_Certificate	 *	, certset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CertificatePairSet SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	SET_OF_CertificatePair	 *	, cpair

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_Crl SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	Crl	 *	, crlpse

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CrlSet SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	CrlSet	 *	, crlset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_policies SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	PolicyList	 *	, policies

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_IssuedCertificate SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	IssuedCertificate	 *	, isscert

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SET_OF_IssuedCertificate SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	SET_OF_IssuedCertificate	 *	, isscertset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SET_OF_Name SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	SET_OF_Name	 *	, nameset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_CRLWithCertificates SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	CRLWithCertificates	 *	, arg

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SET_OF_CRLWithCertificates SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	SET_OF_CRLWithCertificates	 *	, set

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_VerificationResult SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	VerificationResult	 *	, verres

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_TrustPath SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	VerificationResult	 *	, verres

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_error SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE	*	, ff,
	
	int	  	, verbose

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_validity_timeframe SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	Validity  *	, valid

);

#ifdef X509v3

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  aux_print_GeneralNames SEC_PROTOTYPE_2(
	
        char     *      , type,

        GeneralNames *  , generalNames

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_AuthorityKeyId SEC_PROTOTYPE_1(
	
	Ext_AuthorityKeyId	 *	, authorityKeyId

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_KeyUsage SEC_PROTOTYPE_1(
	
	Ext_KeyUsage	 *	, keyUsage

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_ExtKeyUsage SEC_PROTOTYPE_1(
	
	Ext_ExtKeyUsage	 *	, extKeyUsage

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PrivateKeyUsagePeriod SEC_PROTOTYPE_1(
	
	Ext_PrivateKeyUsagePeriod	 *	, period

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PolicyQualifierInfo SEC_PROTOTYPE_1(
	
	PolicyQualifierInfo	 *	, qualifier

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_DisplayText SEC_PROTOTYPE_1(
	DisplayText *     , policy
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_UserNotice SEC_PROTOTYPE_1(
	UserNotice *     , policy
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PolicyInformation SEC_PROTOTYPE_1(
	
	PolicyInformation	 *	, policy

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CertificatePolicies SEC_PROTOTYPE_1(
	
	Ext_CertificatePolicies	 *	, policies

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_MappingElement SEC_PROTOTYPE_1(
	
	MappingElement	 *	, policy

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PolicyMappings SEC_PROTOTYPE_1(
	
	Ext_PolicyMappings	 *	, policyMap

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_DirectoryAttributes SEC_PROTOTYPE_1(
	
	Attr	 *	, attr

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SubjectDirectoryAttr SEC_PROTOTYPE_1(
	
	Ext_DirectoryAttributes	 *	, dirAttr

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_BasicConstraints SEC_PROTOTYPE_1(
	
	Ext_BasicConstraints	 *	, constraints

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_GeneralSubtrees SEC_PROTOTYPE_1(
	
	GeneralSubtrees	 *	, subtree

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_NameConstraints SEC_PROTOTYPE_1(
	
	Ext_NameConstraints	 *	, constraints

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PolicyConstraints SEC_PROTOTYPE_1(
	
	Ext_PolicyConstraints	 *	, constraints

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_DistributionPoint SEC_PROTOTYPE_1(
	
	DistributionPoint	 *	, distrPoint

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CRLDistributionPoints SEC_PROTOTYPE_1(
	
	Ext_CRLDistPoints	 *	, distrPoints

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_nonSupported SEC_PROTOTYPE_1(
	
	SEQUENCE_OF_Extension	 *	, nonSupported

);

#endif

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_AliasList SEC_PROTOTYPE_1(
	
	AliasList	 *	, aliaslist

);

#ifdef ASN1_NETSCAPE_STUFF
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SignedPublicKeyAndChallenge SEC_PROTOTYPE_1(
	
	SignedPublicKeyAndChallenge	 *	, spkac

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PublicKeyAndChallenge SEC_PROTOTYPE_1(
	
	PublicKeyAndChallenge	 *	, pkac

);
#endif /*ASN1_NETSCAPE_STUFF*/

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_DNameOrAlias SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	DName	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_DName SEC_PROTOTYPE_1(
	
	DName	 *	, dname

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_NameOrAlias SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Name	 *	, name

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_GRAPHICString SEC_PROTOTYPE_1(
	
	char	 *	, graphic

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PSESel SEC_PROTOTYPE_1(
	
	PSESel	 *	, pse

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_Version SEC_PROTOTYPE_0();

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_version SEC_PROTOTYPE_0();

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PSEToc SEC_PROTOTYPE_2(
	
	PSEToc	 *	, toc1,
	
	PSEToc	 *	, toc2

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_Certificate SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Certificate	 *	, cert

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_Serialnumber SEC_PROTOTYPE_1(
	
	OctetString	 *	, serial

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_ToBeSigned SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	ToBeSigned	 *	, tbs

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_FCPath SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	FCPath	 *	, fcpath

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_Certificates SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Certificates	 *	, certs

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_Validity SEC_PROTOTYPE_1(
	
	Validity *	, valid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_RootInfo SEC_PROTOTYPE_2(
	
	Serial	 *	, rootinfo,
	
	Boolean	  	, new_

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PKRoot SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	PKRoot	 *	, pkroot

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PKList SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	PKList	 *	, pklist

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CRLEntry SEC_PROTOTYPE_1(
	
	CRLEntry	 *	, crlentry

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CRL SEC_PROTOTYPE_1(
	
	CRL	 *	, crl

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CRLTBS SEC_PROTOTYPE_1(
	
	CRLTBS	 *	, tbs

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CertificateSet SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	SET_OF_Certificate	 *	, certset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CertificatePairSet SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	SET_OF_CertificatePair	 *	, cpair

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_Crl SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	Crl	 *	, crlpse

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CrlSet SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	CrlSet	 *	, crlset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_policies SEC_PROTOTYPE_1(
	
	PolicyList	 *	, policies

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_IssuedCertificate SEC_PROTOTYPE_1(
	
	IssuedCertificate	 *	, isscert

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SET_OF_IssuedCertificate SEC_PROTOTYPE_1(
	
	SET_OF_IssuedCertificate	 *	, isscertset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SET_OF_Name SEC_PROTOTYPE_1(
	
	SET_OF_Name	 *	, nameset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_CRLWithCertificates SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	CRLWithCertificates	 *	, arg

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SET_OF_CRLWithCertificates SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	SET_OF_CRLWithCertificates	 *	, set

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_VerificationResult SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	VerificationResult	 *	, verres

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_TrustPath SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	VerificationResult	 *	, verres

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_error SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	int	  	, verbose

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_validity_timeframe SEC_PROTOTYPE_1(
	
	Validity  *	, valid

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_usage SEC_PROTOTYPE_2(
	
	ProgramUsage	*	, Usage,
	
	int			, Level

);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_cert_fingerprint SEC_PROTOTYPE_1(
	
	Certificate  *	, cert
	
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_cert_fingerprint_MSIE SEC_PROTOTYPE_1(
	
	Certificate  *	, cert
	
);





int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV catstr SEC_PROTOTYPE_3(
	
	char	**	, ptr_str,
	
	int	 *	, ptr_len,
	
	char	 *	, new_

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  str_low SEC_PROTOTYPE_1(
	
	char	 *	, str

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  str_up SEC_PROTOTYPE_1(
	
	char	 *	, str

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV Trim SEC_PROTOTYPE_1(
	
	char	 *	, str

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV Skip_blanks SEC_PROTOTYPE_2(
	
	char	 *	, str,
	
	int	 *	, ptr_idx

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ScanOp SEC_PROTOTYPE_3(
	
	char	 *	, str,
	
	int	 *	, ptr_idx,
	
	char	 *	, oper

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  Scanv SEC_PROTOTYPE_3(
	
	char	 *	, str,
	
	int	 *	, ptr_idx,
	
	char	 *	, delim

);



/*   from ? : */
ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_oid2syntaxoid SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_error SEC_PROTOTYPE_0();

int	 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_set_extension SEC_PROTOTYPE_2(
	
	char	 *	, name,
	
	char	 *	, extension

);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_is_SC SEC_PROTOTYPE_1(
	
	PSE , pse_handle

);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_fgets SEC_PROTOTYPE_5(
	
	char 		 *	, prompt,
	
	char 		 *	, answ,
	
	int		  	, answ_len,
	
	FILE		 *	, out,
	
	FILE		 *	, in

);


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_fgets_stdin SEC_PROTOTYPE_3(
	
	char 		 *	, prompt,
	
	char 		 *	, inp,

	int				, inp_len
	
);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_error SEC_PROTOTYPE_5(
	
	int		  	, number,
	
	char		 *	, text,
	
	char		 *	, addr,
	
	Struct_No	  	, addrtype,
	
	char		 *	, proc

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_add_warning SEC_PROTOTYPE_5(
	
	int		  	, number,
	
	char		 *	, text,
	
	char		 *	, addr,
	
	Struct_No	  	, addrtype,
	
	char		 *	, proc

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_last_error SEC_PROTOTYPE_0();

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_KeyInfo SEC_PROTOTYPE_2(
	
	KeyInfo	 *	, keyinfo1,
	
	KeyInfo	 *	, keyinfo2

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_Signature SEC_PROTOTYPE_2(
	
	Signature	 *	, sig1,
	
	Signature	 *	, sig2

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_ObjId2PSEObjectName SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_PSEObjectName2ObjId SEC_PROTOTYPE_1(
	
	char	 *	, name

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_pstrcmp SEC_PROTOTYPE_2(
	
	OctetString	 *	, a,
	
	OctetString	 *	, b

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_lexequ SEC_PROTOTYPE_2(
	
	OctetString	 *	, str1,
	
	OctetString	 *	, str2

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_Name SEC_PROTOTYPE_2(
	
	char	 *	, name1,
	
	char	 *	, name2

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_RDName SEC_PROTOTYPE_2(
	
	RDName	 *	, a,
	
	RDName	 *	, b

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_DName SEC_PROTOTYPE_2(
	
	DName	 *	, a,
	
	DName	 *	, b

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_checkPemDNameSubordination SEC_PROTOTYPE_2(
	
	DName	 *	, sup,
	
	DName	 *	, sub

);

Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_PemDNameSubordination SEC_PROTOTYPE_2(
	
	DName	 *	, sup,
	
	DName	 *	, sub

);

Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_PCA SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	VerificationResult	 *	, vr

);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_keyword2oid SEC_PROTOTYPE_1(
	
	char	 *	, keyword

);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_keyword2syntaxoid SEC_PROTOTYPE_1(
	
	char	 *	, keyword

);

SEC_attr_encoding SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_keyword2attr_encoding SEC_PROTOTYPE_1(
	
	char	 *	, keyword

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_oid2keyword SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_determine_Signer SEC_PROTOTYPE_2(
	
	VerificationResult	 * 	, verres,
	
	Boolean			 * 	, authentication

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_check_3166 SEC_PROTOTYPE_1(
	
	char	 *	, a

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_check_print_string SEC_PROTOTYPE_1(
	
	char	 *	, str

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_check_IA5_string SEC_PROTOTYPE_1(
	char	 *	, str
);

Certificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_create_Certificates SEC_PROTOTYPE_2(
	
	Certificate	 *	, cert,
	
	FCPath		 *	, fcpath

);

FCPath SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_create_FCPath SEC_PROTOTYPE_1(
	
	Certificate	 *	, cert

);

PKRoot SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_create_PKRoot SEC_PROTOTYPE_2(
	
	Certificate	 *	, cert1,
	
	Certificate	 *	, cert2

);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_create_Certificate SEC_PROTOTYPE_1(
	
	ToBeSigned	 *	, tbs

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_tbs SEC_PROTOTYPE_2(
	
	ToBeSigned	 *	, a,
	
	ToBeSigned	 *	, b

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_Certificate SEC_PROTOTYPE_2(
	
	Certificate	 *	, a,
	
	Certificate	 *	, b

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_CertificatePair SEC_PROTOTYPE_2(
	
	CertificatePair	 *	, a,
	
	CertificatePair	 *	, b

);

CertificatePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_CertificatePair SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_CertificatePair SEC_PROTOTYPE_1(
	CertificatePair	 *	, certpair
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_abs_path SEC_PROTOTYPE_2(
	
	char	 *	, path,
	
	char	 *	, file

);

#if defined(USE_STDARG)
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_sappend_char(OctetString *string, char *format, ...);
#else
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_sappend_char();
#endif /* USE_STDARG */


UTCTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_nextUpdate SEC_PROTOTYPE_1(
	
	UTCTime	 *	, lastUpdate

);

UTCTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  get_date_of_expiry SEC_PROTOTYPE_0();


/* from af/af_ed.c */

E_PROTOTYPE(SEC,RSAPrivateKey)
D_PROTOTYPE(SEC,RSAPrivateKey)



/********* EXTERNALS ***********/
/* ObjId addresses (from af.h) */

extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX countryName;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX orgName;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX orgUnitName;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX commonName;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX surName;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX localityName;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX streetAddress;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX title;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX serialNumber;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX businessCategory;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX description;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX stateOrProvinceName;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CountryString;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CaseIgnoreString;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX PrintableString;

extern AttrList SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX attrlist[];

/*
 * External initialization of attrlist[]:
 *
 
AttrList attrlist[] = {
 
"C",     "COUNTRY",             &countryName_oid,         &CountryString_oid,
"O",     "ORGANIZATION",        &orgName_oid,             &CaseIgnoreString_oid,
"OU",    "ORGANIZATIONAL UNIT", &orgUnitName_oid,         &CaseIgnoreString_oid,
"CN",    "COMMON NAME",         &commonName_oid,          &CaseIgnoreString_oid,
"S",     "SURNAME",             &surName_oid,             &CaseIgnoreString_oid,
"L",     "LOCALITY",            &localityName_oid,        &CaseIgnoreString_oid,
"ST",    "STREET ADDRESS",      &streetAddress_oid,       &CaseIgnoreString_oid,
"T",     "TITLE",               &title_oid,               &CaseIgnoreString_oid,
"SN",    "SERIAL NUMBER",       &serialNumber_oid,        &PrintableString_oid,
"BC,     "BUSINESS CATEGORY",   &businessCategory_oid,    &CaseIgnoreString_oid,
"D",     "DESCRIPTION",         &description_oid,         &CaseIgnoreString_oid,
"SP",    "STATE OR PROVINCE",   &stateOrProvinceName_oid, &CaseIgnoreString_oid,
0 };
 
*/
 

 /*********************************************** 
 * Here is the new reentrant stuff
 ***********************************************/

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_get_SC_DATA SEC_PROTOTYPE_3(
	char	 *	, psename,
	SC_DATA  **	, sc_data,
	int		, sct_id
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_onekeypaironly SEC_PROTOTYPE_1(
	PSE	, pse_handle
);
 
PSE SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_create SEC_PROTOTYPE_5(
	char	 *	, psename,
	char	 *	, cadir,
	char	 *	, pin,
	SC_DATA  *	, sc_data,
	Boolean 	, onekeypaironly
);
AlgEnc SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_signature_key_AlgEnc SEC_PROTOTYPE_1(
	PSE , pse_hdl
);
PSE SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_open SEC_PROTOTYPE_4(
	char	 *	, psename,
	char	 *	, cadir,
	char	 *	, pin,
	SC_DATA  *	, sc_data
);	
PSE SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_create_handle SEC_PROTOTYPE_0();	
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_close SEC_PROTOTYPE_1(
	PSE , pse_handle
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_set_options SEC_PROTOTYPE_2(
	PSE , pse_handle,
	AF_options * , options
);
AF_options SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_create_AF_options SEC_PROTOTYPE_0();

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AF_options SEC_PROTOTYPE_1(
	AF_options ** , options
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AF_options SEC_PROTOTYPE_1(
AF_options* , af_options);

AF_options SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_AF_options SEC_PROTOTYPE_1(
	AF_options * , options
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_AF_options SEC_PROTOTYPE_2(
	AF_options * , dup_options,
	AF_options * , options
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_get_options SEC_PROTOTYPE_2(
	PSE , pse,
	AF_options * , options
);
PSESel SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_get_PSESel SEC_PROTOTYPE_2(
	PSE , pse_hdl,
	ObjId	 *	, af_object
);

VerificationResult SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_get_VerificationResult SEC_PROTOTYPE_1(
	PSE , pse_hdl
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_get_ca_dir SEC_PROTOTYPE_1(
	PSE , pse_hdl
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_get_app_name SEC_PROTOTYPE_1(
	PSE , pse_hdl
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_get_pse_locator SEC_PROTOTYPE_1(
	PSE , pse_hdl
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_single_login SEC_PROTOTYPE_6(
	char	 *	, psename,
	char	 *	, cadir,
	char	 **	, abs_psename,
	char	 **	, abs_cadir,
	char	 **	, pin,
	Boolean	 *	, pin_from_env	
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_abs_pse_paths SEC_PROTOTYPE_4(
	char	 *	, psename,
	char	 *	, cadir,
	char	 **	, abs_psename,
	char	 **	, abs_cadir	
);
PSE SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_open_by_keyboard SEC_PROTOTYPE_5(
	char	 *	, psename,
	char	 *	, cadir,
	AF_options *	, af_options,
	int		, sct_id,
	Boolean		, single_login
);
Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_Certificate_static SEC_PROTOTYPE_4(
        PSE ,  pse_handle,
	
	KeyType	     	, type,
	
	DName	    *	, issuer,
	
	OctetString *	, serial

);


DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  af_pse_get_Name_static SEC_PROTOTYPE_1(
        PSE ,  pse_handle

);

extern   AFPSEObjects SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX af_pse_objects[];


/* from afdname: */

unsigned char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_iso8859convert SEC_PROTOTYPE_1(
	char	* 	, sstr
);


Attr SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_Attr SEC_PROTOTYPE_1(
        Attr	 *  , attr
);

AttrValues SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_AttrValues SEC_PROTOTYPE_1(
        AttrValues	 *  , avls
);

#ifdef X509v3

/* from afaxutil.c: */

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_Extension2ObjId SEC_PROTOTYPE_1(
	Extension_number , num
);
Extension_number SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2Extension SEC_PROTOTYPE_1(
	ObjId * ,id
);

/* from afed.c: */
GeneralName_number SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV GNtype SEC_PROTOTYPE_1(
        OctetString            *  , name
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_KeyUsage SEC_PROTOTYPE_1(
	KeyUsage	 *	, keyUsage
);

KeyUsage SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_KeyUsage SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ExtKeyUsage SEC_PROTOTYPE_1(
	ExtKeyUsage	 *	, extKeyUsage
);

ExtKeyUsage SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_ExtKeyUsage SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GNrfc822Name SEC_PROTOTYPE_1(
	char	 *	, name
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GNrfc822Name SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GNdNSName SEC_PROTOTYPE_1(
	char	 *	, name
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GNdNSName SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GNuRI SEC_PROTOTYPE_1(
	char	 *	, name
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GNuRI SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GNdirectoryName SEC_PROTOTYPE_1(
	DName	 *	, name
);

DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GNdirectoryName SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GNiPAddress SEC_PROTOTYPE_1(
	OctetString	 *	, name
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GNiPAddress SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GNregisteredID SEC_PROTOTYPE_1(
	ObjId	 *	, name
);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GNregisteredID SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PolicyList SEC_PROTOTYPE_1(
	PolicyList	 *	, policies
);

PolicyList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PolicyList SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_AuthorityKeyId SEC_PROTOTYPE_1(
	AuthorityKeyId	 *	, keyId
);

AuthorityKeyId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_AuthorityKeyId SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PrivateKeyUsagePeriod SEC_PROTOTYPE_1(
	PrivateKeyUsagePeriod	 *	, period
);

PrivateKeyUsagePeriod
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PrivateKeyUsagePeriod SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CertificatePolicies SEC_PROTOTYPE_1(
	CertificatePolicies	 *	, policies
);

CertificatePolicies 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CertificatePolicies SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PolicyMappings SEC_PROTOTYPE_1(
	PolicyMappings	 *	, mappings
);

PolicyMappings SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PolicyMappings SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GeneralNames SEC_PROTOTYPE_1(
	GeneralNames	 *	, names
);

GeneralNames SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GeneralNames SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_DirectoryAttributes SEC_PROTOTYPE_1(
		DirectoryAttributes *	, attributes
);

DirectoryAttributes 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_DirectoryAttributes SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_BasicConstraints SEC_PROTOTYPE_1(
	BasicConstraints	 *	, constr
);

BasicConstraints SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_BasicConstraints SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_NameConstraints SEC_PROTOTYPE_1(
	NameConstraints	 *	, constr
);

NameConstraints SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_NameConstraints SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PolicyConstraints SEC_PROTOTYPE_1(
	PolicyConstraints	 *	, constr
);

PolicyConstraints SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PolicyConstraints SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_AuthInfoAccess SEC_PROTOTYPE_1(
	AuthInfoAccess	 *	, access
);

AuthInfoAccess SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_AuthInfoAccess SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CRLReason SEC_PROTOTYPE_1(
	CRLReason	 *	, reason
);

CRLReason SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CRLReason SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CRLDistPoints SEC_PROTOTYPE_1(
	CRLDistPoints	 *	, point
);

CRLDistPoints SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CRLDistPoints SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_IssuingDistPoint SEC_PROTOTYPE_1(
	IssuingDistPoint	 *	, point
);

IssuingDistPoint SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_IssuingDistPoint SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_CRLNumber SEC_PROTOTYPE_1(
	CRLNumber	 *	, number
);

CRLNumber SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_CRLNumber SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GeneralTime SEC_PROTOTYPE_1(
	char	 *	, time
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GeneralTime SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);


/* from afcpy.c: */

CertExtensions SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CertExtensions SEC_PROTOTYPE_1(
	CertExtensions	 *	, old
);

CRLExtensions SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CRLExtensions SEC_PROTOTYPE_1(
	CRLExtensions	 *	, old
);

CRLEntryExtensions SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CRLEntryExtensions SEC_PROTOTYPE_1(
	CRLEntryExtensions	 *	, old
);

SEQUENCE_OF_Extension SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SEQUENCE_OF_Extension SEC_PROTOTYPE_1(
	SEQUENCE_OF_Extension	 *	, old
);

v3Extension SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Extension SEC_PROTOTYPE_1(
	v3Extension	 *	, old
);

KeyUsage SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_KeyUsage SEC_PROTOTYPE_1(
	KeyUsage	 *	, old
);

ExtKeyUsage SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_ExtKeyUsage SEC_PROTOTYPE_1(
	ExtKeyUsage	 *	, old
);

GeneralNames SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_GeneralNames SEC_PROTOTYPE_1(
	GeneralNames	 *	, old
);

AuthorityKeyId 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_AuthorityKeyId SEC_PROTOTYPE_1(
	AuthorityKeyId	 *	, old
);

PrivateKeyUsagePeriod 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PrivateKeyUsagePeriod SEC_PROTOTYPE_1(
	PrivateKeyUsagePeriod	 *	, old
);

PolicyQualifierInfo 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PolicyQualifierInfo SEC_PROTOTYPE_1(
	PolicyQualifierInfo	 *	, old
);

PolicyQualifierInfos 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PolicyQualifierInfos SEC_PROTOTYPE_1(
	PolicyQualifierInfos	 *	, old
);

DisplayText 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_DisplayText SEC_PROTOTYPE_1(
	DisplayText	 *	, old
);

UserNotice 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_UserNotice SEC_PROTOTYPE_1(
	UserNotice	 *	, old
);

PolicyInformation 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PolicyInformation SEC_PROTOTYPE_1(
	PolicyInformation	 *	, old
);

CertificatePolicies 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CertificatePolicies SEC_PROTOTYPE_1(
	CertificatePolicies	 *	, old
);

MappingElement 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_MappingElement SEC_PROTOTYPE_1(
	MappingElement	 *	, old
);

PolicyMappings 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PolicyMappings SEC_PROTOTYPE_1(
	PolicyMappings	 *	, old
);

DirectoryAttributes 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_DirectoryAttributes SEC_PROTOTYPE_1(
	DirectoryAttributes	 *	, old
);

BasicConstraints 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_BasicConstraints SEC_PROTOTYPE_1(
	BasicConstraints	 *	, old
);

GeneralSubtree 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_GeneralSubtree SEC_PROTOTYPE_1(
	GeneralSubtree	 *	, old
);

GeneralSubtrees 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_GeneralSubtrees SEC_PROTOTYPE_1(
	GeneralSubtrees	 *	, old
);

NameConstraints 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_NameConstraints SEC_PROTOTYPE_1(
	NameConstraints	 *	, old
);

PolicyConstraints 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PolicyConstraints SEC_PROTOTYPE_1(
	PolicyConstraints	 *	, old
);

AccessDescription
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_AccessDescription SEC_PROTOTYPE_1(
	AccessDescription	 *	, old
);

AuthInfoAccess 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_AuthInfoAccess SEC_PROTOTYPE_1(
	AuthInfoAccess	 *	, old
);

DistributionPointName 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_DistributionPointName SEC_PROTOTYPE_1(
	DistributionPointName	 *	, old
);

ReasonFlags SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_ReasonFlags SEC_PROTOTYPE_1(
	ReasonFlags	 *	, old
);

DistributionPoint 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_DistributionPoint SEC_PROTOTYPE_1(
	DistributionPoint	 *	, old
);

CRLDistPoints 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CRLDistPoints SEC_PROTOTYPE_1(
	CRLDistPoints	 *	, old
);

IssuingDistPoint 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_IssuingDistPoint SEC_PROTOTYPE_1(
	IssuingDistPoint	 *	, old
);

CRLReason SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_CRLReason SEC_PROTOTYPE_1(
	CRLReason	 *	, old
);

policy2name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_policy2name SEC_PROTOTYPE_1(
	policy2name	 *	, old
);

PolicyList SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PolicyList SEC_PROTOTYPE_1(
	PolicyList	 *	, old
);

/* from affree.c: */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_policies SEC_PROTOTYPE_1(
        PolicyList       **      , policies
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_policy2name SEC_PROTOTYPE_1(
	policy2name	*	, p2n
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_policies SEC_PROTOTYPE_1(
	PolicyList	*	, policies
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Extension SEC_PROTOTYPE_1(
	v3Extension	**	, ext
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Extension SEC_PROTOTYPE_1(
	v3Extension	*	, ext
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CertExtensions SEC_PROTOTYPE_1(
	CertExtensions	**	, exts
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CertExtensions SEC_PROTOTYPE_1(
	CertExtensions	*	, exts
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SEQUENCE_OF_Extension SEC_PROTOTYPE_1(
	SEQUENCE_OF_Extension	**	, ext
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SEQUENCE_OF_Extension SEC_PROTOTYPE_1(
	SEQUENCE_OF_Extension	*	, seq
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CRLExtensions SEC_PROTOTYPE_1(
	CRLExtensions	**	, exts
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CRLExtensions SEC_PROTOTYPE_1(
	CRLExtensions	*	, exts
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CRLEntryExtensions SEC_PROTOTYPE_1(
	CRLEntryExtensions	**	, exts
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CRLEntryExtensions SEC_PROTOTYPE_1(
	CRLEntryExtensions	*	, exts
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_GeneralNames SEC_PROTOTYPE_1(
	GeneralNames	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_GeneralNames SEC_PROTOTYPE_1(
	GeneralNames	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AuthorityKeyId SEC_PROTOTYPE_1(
	AuthorityKeyId	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AuthorityKeyId SEC_PROTOTYPE_1(
	AuthorityKeyId	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_KeyUsage SEC_PROTOTYPE_1(
	KeyUsage	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ExtKeyUsage SEC_PROTOTYPE_1(
	ExtKeyUsage	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ExtKeyUsage SEC_PROTOTYPE_1(
	ExtKeyUsage	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PrivateKeyUsagePeriod SEC_PROTOTYPE_1(
	PrivateKeyUsagePeriod	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PrivateKeyUsagePeriod SEC_PROTOTYPE_1(
	PrivateKeyUsagePeriod	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PolicyQualifierInfo SEC_PROTOTYPE_1(
	PolicyQualifierInfo	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PolicyQualifierInfo SEC_PROTOTYPE_1(
	PolicyQualifierInfo	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PolicyQualifierInfos SEC_PROTOTYPE_1(
	PolicyQualifierInfos	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PolicyQualifierInfos SEC_PROTOTYPE_1(
	PolicyQualifierInfos	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_DisplayText SEC_PROTOTYPE_1(
	DisplayText	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_DisplayText SEC_PROTOTYPE_1(
	DisplayText	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_UserNotice SEC_PROTOTYPE_1(
	UserNotice	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_UserNotice SEC_PROTOTYPE_1(
	UserNotice	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_NoticeReference SEC_PROTOTYPE_1(
	NoticeReference	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SEQUENCE_OF_Integer SEC_PROTOTYPE_1(
	SEQUENCE_OF_Integer	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PolicyInformation SEC_PROTOTYPE_1(
	PolicyInformation	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PolicyInformation SEC_PROTOTYPE_1(
	PolicyInformation	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CertificatePolicies SEC_PROTOTYPE_1(
	CertificatePolicies	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CertificatePolicies SEC_PROTOTYPE_1(
	CertificatePolicies	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_MappingElement SEC_PROTOTYPE_1(
	MappingElement	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_MappingElement SEC_PROTOTYPE_1(
	MappingElement	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PolicyMappings SEC_PROTOTYPE_1(
	PolicyMappings	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PolicyMappings SEC_PROTOTYPE_1(
	PolicyMappings	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_DirectoryAttributes SEC_PROTOTYPE_1(
	DirectoryAttributes	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_BasicConstraints SEC_PROTOTYPE_1(
	BasicConstraints	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_GeneralSubtree SEC_PROTOTYPE_1(
	GeneralSubtree	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_GeneralSubtree SEC_PROTOTYPE_1(
	GeneralSubtree	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_GeneralSubtrees SEC_PROTOTYPE_1(
	GeneralSubtrees	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_GeneralSubtrees SEC_PROTOTYPE_1(
	GeneralSubtrees	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_NameConstraints SEC_PROTOTYPE_1(
	NameConstraints	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_NameConstraints SEC_PROTOTYPE_1(
	NameConstraints	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PolicyConstraints SEC_PROTOTYPE_1(
	PolicyConstraints	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PolicyConstraints SEC_PROTOTYPE_1(
	PolicyConstraints	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CRLReason SEC_PROTOTYPE_1(
	CRLReason	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_DistributionPointName SEC_PROTOTYPE_1(
	DistributionPointName	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_DistributionPointName SEC_PROTOTYPE_1(
	DistributionPointName	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ReasonFlags SEC_PROTOTYPE_1(
	ReasonFlags	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_DistributionPoint SEC_PROTOTYPE_1(
	DistributionPoint	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_DistributionPoint SEC_PROTOTYPE_1(
	DistributionPoint	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CRLDistPoints SEC_PROTOTYPE_1(
	CRLDistPoints	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CRLDistPoints SEC_PROTOTYPE_1(
	CRLDistPoints	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_IssuingDistPoint SEC_PROTOTYPE_1(
	IssuingDistPoint	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_IssuingDistPoint SEC_PROTOTYPE_1(
	IssuingDistPoint	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AccessDescription SEC_PROTOTYPE_1(
	AccessDescription	**	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AccessDescription SEC_PROTOTYPE_1(
	AccessDescription	*	, ptr
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AuthInfoAccess SEC_PROTOTYPE_1(
	AuthInfoAccess	**	, ptr
); 

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AuthInfoAccess SEC_PROTOTYPE_1(
	AuthInfoAccess	*	, ptr
);

/* from afasn1.c: */

Ext_void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_new_EXT SEC_PROTOTYPE_1(
        Boolean        , crit
);

#endif

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1encode_SIGNED SEC_PROTOTYPE_3(
        ASN1info_type   *    , info,
        ASN1global      *    , glob ,
        ASN1signed      *    , from
);
ASN1signed
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1decode_SIGNED SEC_PROTOTYPE_4(
        ASN1info_type       *    , info,
        char                **   , from,
	char                *    , endptr,
	ASN1signed          *    , ret
);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_parse_ObjId SEC_PROTOTYPE_1(
	char 	* , str
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_parse_IPAddress SEC_PROTOTYPE_1(
	char 	* , str
);

ASN1_en_de_PROTO(rc2CBC_Parm)
ASN1_en_de_PROTO(PBEParameter)
ASN1_en_de_PROTO(CertificatePair)
ASN1_en_de_PROTO(Crl)
ASN1_en_de_PROTO(Serial)
ASN1_en_de_PROTO(Aliases)
#ifdef ASN1_NETSCAPE_STUFF
ASN1_en_de_PROTO(PublicKeyAndChallenge)
#endif
#ifdef X509v3
ASN1_en_de_PROTO(policy2name)
#endif
ASN1_en_de_PROTO(EncrCred)

#ifdef USE_NEW_ARITHMETIC

ASN1_en_de_PROTO(EC_Parameters)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EC_Parameters;
ASN1_en_de_PROTO(EC_FieldID)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EC_FieldID;
ASN1_en_de_PROTO(EC_curve)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EC_curve;
ASN1_en_de_PROTO(EC_char2field)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EC_char2field;
ASN1_en_de_PROTO(EC_pentanomial)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EC_pentanomial;
ASN1_en_de_PROTO(EC_KeyParameter)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EC_KeyParameter;

#else /* USE_NEW_ARITHMETIC */

ASN1_en_de_PROTO(FieldID)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_FieldID;
ASN1_en_de_PROTO(Curve)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Curve;
ASN1_en_de_PROTO(char2field)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_char2field;
ASN1_en_de_PROTO(pentanomial)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_pentanomial;
ASN1_en_de_PROTO(ECParameters)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ECParameters;
ASN1_en_de_PROTO(ECKeyParameter)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ECKeyParameter;

#endif /* USE_NEW_ARITHMETIC */

ASN1_en_de_PROTO(Validity)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Validity;
ASN1_en_de_PROTO(CRLEntry)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CRLEntry;
ASN1_en_de_PROTO(ToBeSigned)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ToBeSigned;
ASN1_en_de_PROTO(AlgId)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AlgId;
ASN1_en_de_PROTO(KeyInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_KeyInfo;
ASN1_en_de_PROTO(KeyBits)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_KeyBits;
ASN1_en_de_PROTO(AttrValueAssertion)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AttrValueAssertion;
ASN1_en_de_PROTO(Attr)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Attr;
ASN1_en_de_PROTO(Certificates)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Certificates;
ASN1_en_de_PROTO(PKRoot)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PKRoot;

ASN1_en_de_PROTO(CRLTBS)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CRLTBS;
ASN1_en_de_PROTO(CRLWithCertificates)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CRLWithCertificates;
ASN1_en_de_PROTO(AliasList)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AliasList;

ASN1_en_de_PROTO(PKCS1_OAEP_Parameter)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PKCS1_OAEP_Parameter;
ASN1_en_de_PROTO(PKCS1_PSS_Parameter)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PKCS1_PSS_Parameter;
ASN1_en_de_PROTO(PKCS1_SaltedHash_Parameter)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PKCS1_SaltedHash_Parameter;


#define decode_Certificate(i, f, e, r) \
    (Certificate *)ASN1decode_SIGNED(i, f, e, (ASN1signed *)r)
#define encode_Certificate(i, g, f) ASN1encode_SIGNED(i, g, (ASN1signed *)f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Certificate;

#define decode_CRL(i, f, e, r) \
    (CRL *)ASN1decode_SIGNED(i, f, e, (ASN1signed *)r)
#define encode_CRL(i, g, f) ASN1encode_SIGNED(i, g, (ASN1signed *)f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CRL;

#define decode_PKList(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_PKList(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PKList;

#define decode_SEQUENCE_OF_CRLEntry(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SEQUENCE_OF_CRLEntry(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQUENCE_OF_CRLEntry;

#define decode_DName(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_DName(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_DName;

#define decode_RDName(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_RDName(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_RDName;

#define decode_AttrValues(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_AttrValues(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AttrValues;

#define decode_SET_OF_Attr(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SET_OF_Attr(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SET_OF_Attr;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SET_OF_Attr_BER;

#define decode_SET_OF_Certificate(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SET_OF_Certificate(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SET_OF_Certificate;

#define decode_FCPath(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_FCPath(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_FCPath;

#define decode_SET_OF_CertificatePair(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SET_OF_CertificatePair(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SET_OF_CertificatePair;

#define decode_SET_OF_CRL(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SET_OF_CRL(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SET_OF_CRL;

#define decode_CrlSet(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_CrlSet(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CrlSet;

#define decode_SET_OF_AlgId(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SET_OF_AlgId(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SET_OF_AlgId;

#define decode_SEQ_OF_AlgId(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SEQ_OF_AlgId(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQ_OF_AlgId;

#ifdef X509v3
ASN1_en_de_PROTO(v3Extension)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_v3Extension;

#define encode_SEQUENCE_OF_Extension(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_SEQUENCE_OF_Extension(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQUENCE_OF_Extension;

ASN1_en_de_PROTO(CertExtensions)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CertExtensions;

ASN1_en_de_PROTO(CRLExtensions)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CRLExtensions;

ASN1_en_de_PROTO(CRLEntryExtensions)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CRLEntryExtensions;

ASN1_en_de_PROTO(KeyUsage)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_KeyUsage;

ASN1_en_de_PROTO(ExtKeyUsage)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ExtKeyUsage;

ASN1_en_de_PROTO(TYPE_IDENTIFIER)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GNotherName;

/* IA5String */
#define decode_GNrfc822Name(i, f, e, r) decode_xyzString(i, f, e, r)
#define encode_GNrfc822Name(i, g, f) encode_xyzString(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GNrfc822Name;

/* IA5String */
#define decode_GNdNSName(i, f, e, r) decode_xyzString(i, f, e, r)
#define encode_GNdNSName(i, g, f) encode_xyzString(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GNdNSName;

/* IA5String */
#define decode_GNuRI(i, f, e, r) decode_xyzString(i, f, e, r)
#define encode_GNuRI(i, g, f) encode_xyzString(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GNuRI;

/* DName */
#define decode_GNdirectoryName(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_GNdirectoryName(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GNdirectoryName;

#define decode_GNiPAddress(i, f, e, r) decode_OctetString(i, f, e, r)
#define encode_GNiPAddress(i, g, f) encode_OctetString(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GNiPAddress;

#define decode_GNregisteredID(i, f, e, r) decode_ObjId(i, f, e, r)
#define encode_GNregisteredID(i, g, f) encode_ObjId(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GNregisteredID;

#define decode_GeneralName(i, f, e, r) decode_DERcode(i, f, e, r)
#define encode_GeneralName(i, g, f) encode_DERcode(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GeneralName;

#define decode_GeneralNames(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_GeneralNames(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GeneralNames;

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_GN_number_of SEC_PROTOTYPE_2(
       GeneralNames	     *	, names,
       GeneralName_number       , type
);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_GN_get_by_index SEC_PROTOTYPE_3(
       GeneralNames	     *	, names,
       GeneralName_number       , type,
       int                      , index
);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_GN_get_any_by_index SEC_PROTOTYPE_3(
       GeneralNames	     *	, names,
       int                      , index,
       GeneralName_number     *  , is_type
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_GN_add_name SEC_PROTOTYPE_3(
       GeneralNames	    **	, namesp,
       GeneralName_number       , type,
       char                 *   , new_name
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_GN_add_name_internal SEC_PROTOTYPE_3(
       GeneralNames	    **	, namesp,
       GeneralName_number       , type,
       void                 *   , new_name
);
GeneralName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_string2GeneralName SEC_PROTOTYPE_2(
       GeneralName_number       , type,
       char                 *   , new_name
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_ANYQueryFunc SEC_PROTOTYPE_4(
    OctetString **, out,
    char **, status,
    const char *, responderurl,
    void *, context)
;
#if defined(X509v3) && defined(WWW)

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV www_get_crl SEC_PROTOTYPE_3(
        PSE   , pse_handle,

        char *  ,  address,

        SET_OF_CRL ** ,  CRLset

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV www_get_certificate SEC_PROTOTYPE_3(
        PSE   , pse_handle,

        char *  ,  address,

        SET_OF_Certificate ** ,  CertSet

);

#endif /* X509v3 & WWW */


#ifdef PEM_INSTALLED

SET_OF_CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pemCRLwithCertificates2CRLSet SEC_PROTOTYPE_2(
        PSE   ,  pse_handle,

        OctetStream  * ,  input_stream
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pem_stream2LocalForm SEC_PROTOTYPE_4(
        PSE   ,  pse_handle,

        OctetStream  * ,  input_stream,

        SET_OF_Certificate **, CertSet,

        SET_OF_CRL **, CRLset
);
#endif

#ifdef PKCS_INSTALLED

SET_OF_CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pkcs7CRL2CRLSet SEC_PROTOTYPE_2(
        PSE   ,  pse_handle,

        OctetStream  * ,  input_stream
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkcs7_stream2LocalForm SEC_PROTOTYPE_4(
        PSE   ,  pse_handle,

        OctetStream  * ,  input_stream,
 
        SET_OF_Certificate **, CertSet,
 
        SET_OF_CRL **, CRLset
);

#endif

ASN1_en_de_PROTO(AuthorityKeyId)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AuthorityKeyId;

ASN1_en_de_PROTO(PrivateKeyUsagePeriod)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PrivateKeyUsagePeriod;

ASN1_en_de_PROTO(PolicyQualifierInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PolicyQualifierInfo;

#define encode_PolicyQualifierInfos(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_PolicyQualifierInfos(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PolicyQualifierInfos;

ASN1_en_de_PROTO(PolicyInformation)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PolicyInformation;

#define encode_CertificatePolicies(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_CertificatePolicies(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CertificatePolicies;

ASN1_en_de_PROTO(MappingElement)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_MappingElement;

#define encode_PolicyMappings(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_PolicyMappings(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PolicyMappings;

#define encode_DirectoryAttributes(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_DirectoryAttributes(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_DirectoryAttributes;

ASN1_en_de_PROTO(BasicConstraints)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_BasicConstraints;

ASN1_en_de_PROTO(GeneralSubtree)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GeneralSubtree;

#define encode_GeneralSubtrees(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_GeneralSubtrees(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GeneralSubtrees;

ASN1_en_de_PROTO(NameConstraints)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_NameConstraints;

#define encode_PolicyConstraints(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_(PolicyConstraintsi, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PolicyConstraints;

ASN1_en_de_PROTO(ReasonFlags)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ReasonFlags;

ASN1_en_de_PROTO(DistributionPointName)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_DistributionPointName;

ASN1_en_de_PROTO(DistributionPoint)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_DistributionPoint;

ASN1_en_de_PROTO(AccessDescription)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AccessDescription;

/*ASN1_en_de_PROTO(AuthInfoAccess)*/
#define encode_AuthInfoAccess(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_AuthInfoAccess(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AuthInfoAccess;

#define encode_CRLDistPoints(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_CRLDistPoints(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CRLDistPoints;

ASN1_en_de_PROTO(IssuingDistPoint)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_IssuingDistPoint;

extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CRLReason;

/*
ASN1_en_de_PROTO()
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_;

#define encode_(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_(i, f, e, r) ASN1d_gen_List(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_;
*/


#endif

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SEQ_OF_Name SEC_PROTOTYPE_1(
	SET_OF_Name	 *	, p
);
SET_OF_Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SEQ_OF_Name SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQ_OF_Name;
#define encode_SEQ_OF_Name(i, g, f) ASN1e_gen_List(i, g, f)
#define decode_SEQ_OF_Name(i, f, e, r) ASN1d_gen_List(i, f, e, r)

ASN1_en_de_PROTO(Cred)
ASN1_en_de_PROTO(Creds)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Creds;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EncrCred;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Cred;

extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CertificatePair;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Crl;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Serial;

#ifdef ASN1_NETSCAPE_STUFF
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PublicKeyAndChallenge;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SignedPublicKeyAndChallenge;

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_PublicKeyAndChallenge SEC_PROTOTYPE_1(
	PublicKeyAndChallenge	 *	, pkac
);
PublicKeyAndChallenge SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_PublicKeyAndChallenge SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_get_SignedPublicKeyAndChallenge SEC_PROTOTYPE_3(
        PSE 			, pse_handle,
	char		*	, challenge,
	KeyType			, key_type
);
#endif

#ifdef ASN1_NEW_DNAME_HANDLING
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_OSstr_Impl_PrintableString;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_OSstr_Impl_T61String;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_OSstr_Impl_IA5String;

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_ANYString2String SEC_PROTOTYPE_1(
	OctetString	*	, ostr
);
#endif


#if defined(PEM_INSTALLED) || defined(PKCS_INSTALLED)
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pem_pse_store_crlset SEC_PROTOTYPE_2(

        PSE                                     , pse_handle,

        SET_OF_CRLWithCertificates       *      , set_of_pemcrlwithcerts

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pem_cadb_store_crlset SEC_PROTOTYPE_2(

        PSE                                     , pse_handle,

        SET_OF_CRLWithCertificates       *      , set_of_pemcrlwithcerts

);
#endif

/* PIN Policy */

PINPolicy SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_pse_get_PPolicy SEC_PROTOTYPE_1(
	PSE			, pse
);

PINState SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_pse_get_PState SEC_PROTOTYPE_1(
	PSE			, pse
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_PPolicy SEC_PROTOTYPE_2(
	PSE			, pse,
	PINPolicy	*	, pol
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_PState SEC_PROTOTYPE_2(
	PSE			, pse,
	PINState	*	, pst
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pin_checkexpired SEC_PROTOTYPE_5(
	PSE			, pse,
	PINPolicy	*	, pol,
	PINState	*	, pst0,
	Boolean		*	, expired,
	int		*	, graceleft
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pin_setlogin SEC_PROTOTYPE_3(
	PSE			, pse,
	PINPolicy	*	, pol,
	PINState	*	, pst0
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pin_setnew SEC_PROTOTYPE_4(
	PSE			, pse,
	PINPolicy	*	, pol,
	PINState	*	, pst0,
	char		*	, pin
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pin_checksyntax SEC_PROTOTYPE_4(
	char 		*	, rules,
	Boolean		*	, ok,
	int		*	, line,
	char		**	, msg
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pin_checknew SEC_PROTOTYPE_8(
	PSE			, pse,
	PINPolicy	*	, pol,
	PINState	*	, pst0,
	PINContext	*	, ctx,
	char		*	, pin,
	char		*	, oldpin,
	Boolean		*	, ok,
	char		**	, msg
);


PINPolicy SEC_GLOBAL_FUNC_PREFIX *SEC_API_CALLING_CONV d_PINPolicy SEC_PROTOTYPE_1(
	OctetString	 *	, os
);

PINState SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_PINState SEC_PROTOTYPE_1(
	OctetString	 *	, os
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_PINPolicy SEC_PROTOTYPE_1(
	PINPolicy	 *	, pol
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_PINState SEC_PROTOTYPE_1(
	PINState	 *	, pst
);
#ifdef X509v3
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TYPE_IDENTIFIER SEC_PROTOTYPE_1(
        TYPE_IDENTIFIER **      , tid
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_TYPE_IDENTIFIER SEC_PROTOTYPE_1(
	TYPE_IDENTIFIER	*	, tid
);
#endif
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PINPolicy SEC_PROTOTYPE_1(
	PINPolicy	 **	, pol
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PINState SEC_PROTOTYPE_1(
	PINState	 **	, pst
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PINContext SEC_PROTOTYPE_1(
	PINContext	 **	, pctx
);

SET_OF_RDNalias SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SET_OF_RDNalias SEC_PROTOTYPE_1(
	OctetString *  , asn1
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SET_OF_RDNalias SEC_PROTOTYPE_1(
	SET_OF_RDNalias *  , aliases
);

DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_DName2RDNalias SEC_PROTOTYPE_2(
	PSE  , pse,
	DName *, name
);
DName SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_RDNalias2DName SEC_PROTOTYPE_2(
	PSE  , pse,
	DName *, name
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_add_RDNalias SEC_PROTOTYPE_4(
	SET_OF_RDNalias **  , aliases,
	ObjId *, type,
	char *, find,
	char *, repl
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_delete_RDNalias SEC_PROTOTYPE_4(
	SET_OF_RDNalias **  , aliases,
	ObjId *, type,
	char *, find,
	char *, repl
);
SET_OF_RDNalias SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV af_pse_get_SET_OF_RDNalias SEC_PROTOTYPE_1(
	PSE  , pse
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_pse_update_SET_OF_RDNalias SEC_PROTOTYPE_2(
	PSE  , pse,
	SET_OF_RDNalias *  , aliases
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SET_OF_RDNalias SEC_PROTOTYPE_1(
	
	SET_OF_RDNalias	 *	, rdnalias

);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_SET_OF_RDNalias SEC_PROTOTYPE_2(
	char	 *	, string,
    SET_OF_RDNalias *          , rdnalias
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SET_OF_RDNalias SEC_PROTOTYPE_2(
	FILE		 *	, ff,
	SET_OF_RDNalias	 *	, rdnalias
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_RDNalias SEC_PROTOTYPE_1(
        SET_OF_RDNalias      **  , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_RDNalias SEC_PROTOTYPE_1(
        RDNalias      *      , p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SET_OF_RDNalias SEC_PROTOTYPE_1(
        SET_OF_RDNalias      *      , p
);


ASN1_en_de_PROTO(RDNalias)
ASN1_en_de_PROTO(SET_OF_RDNalias)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_RDNalias;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SET_OF_RDNalias;


#define decode_SEQUENCE_OF_Integer(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SEQUENCE_OF_Integer(i, g, f) ASN1e_gen_List(i, g, f)

#ifdef X509v3

extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PolicyList;

extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQUENCE_OF_Integer;
ASN1_en_de_PROTO(DisplayText)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_DisplayText;
ASN1_en_de_PROTO(NoticeReference)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_NoticeReference;
ASN1_en_de_PROTO(UserNotice)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_UserNotice;

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_UserNotice SEC_PROTOTYPE_1(
	UserNotice	 *	, p
);
UserNotice SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_UserNotice SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
#endif
#define decode_SET_OF_OctetString(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SET_OF_OctetString(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SET_OF_OctetString;

#define decode_SEQUENCE_OF_OctetString(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SEQUENCE_OF_OctetString(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQUENCE_OF_OctetString;

#define decode_SEQUENCE_OF_ObjId(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SEQUENCE_OF_ObjId(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQUENCE_OF_ObjId;

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SET_OF_OctetString SEC_PROTOTYPE_1(
	SET_OF_OctetString	 *	, p
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SEQUENCE_OF_OctetString SEC_PROTOTYPE_1(
	SEQUENCE_OF_OctetString	 *	, p
);
SET_OF_OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SET_OF_OctetString SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
SEQUENCE_OF_OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SEQUENCE_OF_OctetString SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

#define decode_QCStatements(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_QCStatements(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_QCStatements;
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_QCStatements SEC_PROTOTYPE_1(
    QCStatements	 *	, p
    );
QCStatements SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_QCStatements SEC_PROTOTYPE_1(
    OctetString	 *	, asn1_string
    );
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_QSStatement;
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_QSStatement SEC_PROTOTYPE_1(
    QSStatement	 *	, p
    );
QSStatement SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_QSStatement SEC_PROTOTYPE_1(
    OctetString	 *	, asn1_string
    );
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_QSStatement SEC_PROTOTYPE_1(
    QSStatement	*	, str
    );
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_QSStatement SEC_PROTOTYPE_1(
    QSStatement **	, str
    );

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_QCStatements SEC_PROTOTYPE_1(
    QCStatements	*	, set
    );
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_QCStatements SEC_PROTOTYPE_1(
    QCStatements **	, str
    );

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Iso4217CurrencyCode SEC_PROTOTYPE_1(
    Iso4217CurrencyCode	*	, set
    );
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Iso4217CurrencyCode SEC_PROTOTYPE_1(
    Iso4217CurrencyCode **	, str
    );
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Iso4217CurrencyCode;
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_Iso4217CurrencyCode SEC_PROTOTYPE_1(
    Iso4217CurrencyCode	 *	, p
    );
Iso4217CurrencyCode SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_Iso4217CurrencyCode SEC_PROTOTYPE_1(
    OctetString	 *	, asn1_string
    );

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_MonetaryValue SEC_PROTOTYPE_1(
    MonetaryValue	*	, set
    );
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_MonetaryValue SEC_PROTOTYPE_1(
    MonetaryValue **	, str
    );
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_MonetaryValue;
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_MonetaryValue SEC_PROTOTYPE_1(
    MonetaryValue	 *	, p
    );
MonetaryValue SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_MonetaryValue SEC_PROTOTYPE_1(
    OctetString	 *	, asn1_string
    );

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SemanticsInformation SEC_PROTOTYPE_1(
    SemanticsInformation	*	, set
    );
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SemanticsInformation SEC_PROTOTYPE_1(
    SemanticsInformation **	, str
    );
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SemanticsInformation;
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SemanticsInformation SEC_PROTOTYPE_1(
    SemanticsInformation	 *	, p
    );
SemanticsInformation SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SemanticsInformation SEC_PROTOTYPE_1(
    OctetString	 *	, asn1_string
    );

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_oid_and_value SEC_PROTOTYPE_4(
    char     *              , string,
    ObjId *  , oid,
    OctetString *  , value,
    Boolean * , critical
    );

KeyBits SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_convert_RSAPrivateKey_to_KeyBits SEC_PROTOTYPE_2(
	RSAPrivateKey	*	, rsapvk,
	int					, inherit_memory_from_pvk
);

enum { BC_UNKNOWNCONT, BC_NEEDPW, BC_NOUSERCERT, BC_NOCACERT, BC_FOUNDROOT, BC_BADP12};
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_build_certificates SEC_PROTOTYPE_9(
	OctetString * , new_data,
	OctetString * , password,
	int           , keyid,
    Certificates ** ,  certs,
	Certificate	 **	, root_key,
	KeyInfo *     , public_key,
	KeyInfo **    , private_key,
	SET_OF_Certificate ** , unused,
	DName **      , cert_needed
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_set_Authentication_mode SEC_PROTOTYPE_2(
	PSE  , pse,
	Boolean, use_authentication_cert
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_use_EncCert_for_Signature SEC_PROTOTYPE_2(
	PSE  , pse,
	Boolean, use_enc_cert_for_signature
);
#ifdef USETMPPSEFORGSS
/* create a PSE with one RSA key pair of the same key size where the certificate is signed by orig_pse */
/* the certification path of this PSE is accepted by GSS Server even if orig_pse is not a CA */
/* the certificate is X509v1 */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_create_tmp_pse_for_gss SEC_PROTOTYPE_5(
    PSE , orig_pse,
    char ** , path, /* the path is build by the function and returned here */
    char ** , pin,  /* the pin is created by the function and returned here */
    char ** , notbefore, /* the validity could be given by application or is created */
    char ** , notafter /* by the function and returned (Current - 1 hour until current + 23 hours)*/
);
#endif
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_encode_sse_PSE SEC_PROTOTYPE_2(
    PSE , pse,
    char ** , enc
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_extract_Certificates SEC_PROTOTYPE_3( OctetString * , cont, SET_OF_Certificate **, certs, OctetString **,dec);

/* creates Ocsp handle and fills it with options read from input profile handles */
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV af_create_H_OCSP_CHECK SEC_PROTOTYPE_4(
    H_OCSP_CHECK*, p_h,
    Certificate *, p_cert,
    char *, szApplicationNode,
    char *, szLogModuleName
);

/* Helper function for testing if a certificate belongs to certain (sub-) CA. */
extern RC testnames SEC_PROTOTYPE_2(
	Certificate *, p_cert,
	char ***, pcertnames);
extern RC testname SEC_PROTOTYPE_2(
	const char *, name,
	const char *, teststr_c);

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



