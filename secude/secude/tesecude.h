/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/tesecude.h
 *###
 *### global functions:
 *###
 *###*****************************************/



#ifndef _TESECUDE_
#define _TESECUDE_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Calling convention for TS KAPI functions */

/* cdecl should be appropriate, if it is a "normal" docrypt library */
#define TS_KAPI_CALLING_CONV SEC_CDECL

#include <secude/af.h>


/*-----------------------------------------------------------------------*/
/*    Definitions                                                        */
/*-----------------------------------------------------------------------*/

#define TS_CERT_FID	"C1"		/* File-ID of the smartcard-file */
					/* which contains the Telesec	 */
					/* certificate ('C1')		 */	
#define TS_CLASS_BYTE	(sec_byte)0xB0		/* Class byte for a TCOS-command */
#define TS_INS_SELECTF	(sec_byte)0xA4		/* Instruction byte for TCOS-    */
						/* command 'select file'	 */
#define TS_INS_READB	(sec_byte)0xB0		/* Instruction byte for TCOS-    */
						/* command 'read binary'	 */
#define TS_INS_READR	(sec_byte)0xB2		/* Instruction byte for TCOS-    */
						/* command 'read record'	 */
#define TS_MODULUS	(sec_byte)0x4E		/* First byte of the file-id for */
						/* an RSA modulus file		 */
#define TS_EXPONENT	(sec_byte)0x45		/* First byte of the file-id for */
						/* an RSA public exponent file	 */
#define TTC_key_id	   2		/* Identifier of the TTC 	 */
					/* public key			 */


#define MAX_SC_RESP	 255		/* Max. length of the SC response*/
#define MAX_SC_CMD	 256		/* Max. length of the SC command */
#define MAX_TS_CERT	1024		/* Max. length of the Telesec    */
					/* certificate			 */
#define MAX_MOD_LEN	  64		/* Max. modulus-length (keysize	 */
					/* 512)				 */




/*-----------------------------------------------------------------------*/
/*    Error codes for the crypto API                                     */
/*-----------------------------------------------------------------------*/

#define DC_NO_PB 		 0
#define DC_NOT_AVAILABLE	 1
#define DC_BAD_ALGO		 2

#define DC_CS_INCONCLUSIVE       3
#define DC_CS_PB                 4
#define DC_CC_PB                 5
#define DC_SIG_PB                6
#define DC_BAD_ENC_ALGO          7
#define DC_ENC_PB                8
#define DC_BAD_KEY_ENC_ALGO      9
#define DC_DECR_PB               10



/* typedefs etc. for SME-IF */

typedef enum ts_sme_type { ts_ft_error = -3,
	       ts_ft_ill_decrypt = -2,
	       ts_ft_multiple = -1, 
	       ts_ft_no_sme = 0, 
	       ts_ft_any, ts_ft_signed, ts_ft_decrypt, ts_ft_encrypt,
	       ts_ft_enc_sign
} ts_sme_type;

typedef enum ts_cert_type { ts_ct_unknown = 0,
	       ts_ct_telesec,
	       ts_ct_X509,
	       ts_ct_teletrust
} ts_cert_type;

typedef struct TSCertTemplate {
    ts_cert_type type;
    OctetString *cert_DERcode;
} TSCertTemplate;

typedef SET_OF(TSCertTemplate) SET_OF_TSCertTemplate;

typedef enum ts_cert_state {
    ts_cs_ok = 0,
    ts_cs_revoked,
    ts_cs_inconclusive,
    ts_cs_expired,
    ts_cs_integrity,
    ts_cs_other
} ts_cert_state;

typedef enum ts_sig_state {
    ts_ss_ok = 0,
    ts_ss_not_ok,
    ts_ss_other
} ts_sig_state;

typedef enum ts_check_res {
    ts_ok = 0,
    ts_revoked,
    ts_expired,
    ts_not_ok_server,
    ts_fault_client
} ts_check_res;

typedef struct TSSigVerRes {
    ts_cert_state cert_state;
    ts_sig_state sig_state;
    TSCertTemplate *cert;
    struct TSSigVerRes *next;
} TSSigVerRes;

typedef struct TSVerRes {
    int num_sig;
    int	first_invalid;
    TSSigVerRes *sigs;
} TSVerRes;

typedef struct TSFileOri {
    char *orig;
    char *date;
    char *info;
} TSFileOri;

typedef struct TSEncPar {
    char not_recipient;
    TSCertTemplate *originator;
    SET_OF_TSCertTemplate *recipients;
} TSEncPar;

typedef struct TelesecCertTBS {
    int		 version;		/* DEFAULT 1 */
    char	*certNumber;		/* PrintableString */
    DName	*namingAuthority;
    AlgId	*signatureAlg;
    DName	*issuer;
    UTCTime	*timeOfIssue;
    Validity	*validity;
    DName	*subject;
    KeyInfo	*subjectPK1;
    KeyInfo	*subjectPK2;		/* OPTIONAL */
} TelesecCertTBS;

typedef struct TelesecCert {
    TelesecCertTBS	*tbs;
    OctetString		*sigString;
} TelesecCert;


/*-----------------------------------------------------------------------*/
/*    Definitions  for communication with Telesec Trust Center                                                      */
/*-----------------------------------------------------------------------*/

/*
 *  if Borland C++ not used: word/dword handling 
 */
/* some types are already there in Borland C++ */
typedef    sec_uint4           dword;  /* unsigned 32-bit integer */ 
typedef    sec_uint2           word;   /* unsigned 16-bit integer */ 
typedef    sec_uint2           WORD;   /* unsigned 16-bit integer */
 
#if !defined(SEC_BCC) && !defined(SEC_MSC)
typedef    sec_uint4           DWORD;  /* unsigned 32-bit integer */ 
typedef    char		       byte;
typedef    char		       BYTE;
#endif

#define CHAR_TO_DWORD(strptr)                    \
            (((dword) *((strptr)+3) << 24) | \
             ((dword) *((strptr)+2) << 16) | \
             ((dword) *((strptr)+1) <<  8) | \
             ((dword) *(strptr)))


#define DEFAULT_TTC_CALLNUMBER		"002712390360"
#define DEFAULT_TTC_IPADR		"164.25.197.169"
#define DEFAULT_TTC_PORT		1024
#define DEFAULT_TTC_TIMEOUT		900000		/* msec */

#define PKS_SIGNED_SME_name		"signedSME"	/* filename */
#define PKS_DUMMY_name			"dummy"		/* filename */
#define PKS_TTP_MSG_name		"ttp_msg"	/* filename */
#define PKS_TTP_REC_name		"rec_ttp_msg"	/* filename */
#define PKS_PKDP_name			"pkdp"		/* filename */
#define PKS_RLP_name			"rlp"		/* filename */
#define PKS_CHRES_name			"chinfo"	/* filename */
#define PKS_SECUDE_REQUEST_STRING 	"SECUDE request" 
#define PKS_ERR_MSG_ID			0
#define PKS_REQ_PKDP_ID			2
#define PKS_REQ_RLP_ID			4
#define PKS_CHECK_CERT_ID		13
#define PKS_SEND_CI_ID			101
#define PKS_REQ_BREAK_ID		201
#define MAXESTRING			100	/* Max. length of returned errorstring */
#define MAXTCPBLOCK			1024	/* Max. length of transmitted Data Block */						   



typedef struct pks_FILTER {
    char	*certNumber;
    char	*surName;
    char	*givenName;
    char	*postalCode;
    char	*localityName;
    char	*organisationName;
    char	*organisationUnitName;
    unsigned char	*timeofIssue;
    word	userGroupR;
} pks_FILTER;





#define SECUDE_TS_INCLUDE 1
#include <secude/ts_p.h>
#undef SECUDE_TS_INCLUDE

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* _TESECUDE_ */

