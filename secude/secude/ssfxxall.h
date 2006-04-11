/* @(#) $Id$ SAP*/
/**********************************************************************/
/**********************************************************************/
/*                                                                    */
/*  (C) Copyright SAP AG, Walldorf  1996 - 1999                       */
/*                                                                    */
/*                                                                    */
/*  ssfxxall.h                                                        */
/*  ==========                                                        */
/*                                                                    */
/* This header file contains all type definitions for the SSF API,    */
/* i.e., macros, constants and ypes                                   */
/* The function declarations can be found in ssfxxapi.h				  */
/*                                                                    */
/* The SSF ("Secure Store & Forward") API provides services to        */
/* protect SAP R/3 data and documents while such data is being stored */
/* on insecure media or is in transit over insecure communication     */
/* channels.                                                          */
/*                                                                    */
/* SSF provides data integrity, authentication and non-repudiation    */
/* services using digital signatures, as well as confidentiality      */
/* through the use of digital envelopes and encryption. Through the   */
/* SSF API security toolkits from external vendors are integrated     */
/* with SAP R/3.                                                      */
/*                                                                    */
/*                                                                    */
/* Documentation:                                                     */
/*   - "Secure Store & Forward (SSF) - Spezifikation"                 */ 
/*                                                                    */
/*                                                                    */
/*  Author:    Michael Friedrich                                      */
/*  Reviewer:                                                         */
/*  Version:   1.50                                                   */
/*                                                                    */
/*  Description:                                                      */
/*    This file is to be included in all "C" source files that        */
/*    implement or make use of SSF services.                          */
/*                                                                    */
/*  Prerequisites:                                                    */
/*    - headers which should be included before: saptype.h            */
/*      (not required, but if used must be included *before* this)    */
/*    - standard conformance: platform-independent "C" code           */
/*    - others:                                                       */
/*                                                                    */
/*                                                                    */
/**********************************************************************/

#ifndef SSFXXALL_H
#define SSFXXALL_H  1

#ifdef __cplusplus
extern "C" {
#endif


#define SSF_VERSION2	/*	some extensions that are only required
							and implemented in SAP's libssfso		*/

/**********************************************************************/
/*                                                                    */
/*  constants                                                         */
/*                                                                    */
/**********************************************************************/

/* SSF Function Return Codes --------------------------------------*/

#define SSF_API_OK                    0  /*operation ok            */
#define SSF_API_NOSECTK               1  /*no security toolk. found*/
#define SSF_API_INVALID_FORMAT        2  /*unknown wrapper format  */   
#define SSF_API_NODATA                3  /*input data length zero  */
#define SSF_API_NOMEMORY              4  /*insuff. main memory     */  
#define SSF_API_SIGNER_ERRORS         5  /*there are signer errors */               
#define SSF_API_NORESULTLISTMEMORY    6  /*no memory f. result list*/              
#define SSF_API_UNKNOWN_PAB           7  /*Priv.Addr.Book not found*/              
#define SSF_API_INVALID_PAB_PASSWORD  8  /*invalid PAB password    */              
#define SSF_API_RECIPIENT_ERRORS      9  /*there are recip. errors */              
#define SSF_API_INVALID_MDALG         10 /*unknown MD algorithm    */
#define SSF_API_ENCODE_FAILED         11 /*could not encode output */  
#define SSF_API_DECODE_FAILED         12 /*could not decode input  */  
#define SSF_API_UNKNOWN_SECTK_ERROR   13 /*unknown sec.toolk. error*/

/* 14 ist bereits im ABAP vergeben und in Nachrichtenklasse 1S dokumentiert */

#define SSF_API_SECTK_NO_LICENSE      15 /* SecTK license (ticket) */
					 /* is missing or invalid  */
#define SSF_API_SECTK_NO_ENVELOPE     16 /* this is a SAPCRYPTOLIB */
					 /* without SSF Envelope() */
					 /* and SSF Develope()     */
#define SSF_API_CANT_WRITE_FILE       81 /* File could not be opened for writing 
                                            e.g.logfile for SsfVerify
                                          */
#define SSF_API_KEYUSAGE_SIGN         82 /* Could not use PAB for signing
                                            as key usage was not properly set.
                                          */

/* SSF Aux Function Return Codes -------------------------------------*/

#define SSF_AUX_OK                    0 /* function ended successfully*/ 
#define SSF_AUX_NOMEMORY             51 /* no more memory output data */
#define SSF_AUX_NOSIGRCPID           52 /* signer/recip. id is empty  */
#define SSF_AUX_NOSIGRCPINFO         53 /* signer/recipient info empty*/
#define SSF_AUX_NOSIGRCPINFOLIST     54 /* sig./recip. info list empty*/


/* Signer and Recipient result codes ------------------------------*/
/*                     - used in uResult component of a signer or  */
/*                       recipient security information structure  */

#define SSF_API_SIGNER_OK          0 /* operation ok for signer    */
#define SSF_API_RECIPIENT_OK       0 /* operation ok for recipient */
#define SSF_API_PROFILE_LOCKED    21 /* security profile is locked */
#define SSF_API_UNKNOWN_SIGNER    22 /* unknown signer             */              
#define SSF_API_UNKNOWN_RECIPIENT 22 /* unknown recipient          */
#define SSF_API_UNKNOWN_PROFILE   23 /* security profile not found */               
#define SSF_API_INVALID_PROFILE   24 /* security profile not usable*/               
#define SSF_API_INVALID_PASSWORD  25 /* invalid password for signer*/              
#define SSF_API_NOCERTIFICATE     26 /* certificate not found      */  
#define SSF_API_SIGNER_NOT_OK     27 /* signature invalid          */
#define SSF_API_RECIPIENT_NOT_OK  27 /* operation not ok f. recip. */  
#define SSF_API_UNDEFINED_RESULT  28 /* initial value on input     */

#define SSF_API_REVOCATION_CERTIFICATE_REVOKED       31 /* OCSPSingleResponse::status == revoked */
#define SSF_API_REVOCATION_OCSP_RESPONSE_MISSING     32 /* There is no OCSP response, as the responder was unreachable.
                                                           This may happen as a result of network problems, a shutdown proxy,
                                                           a busy responder that replied with status TryAgainLater or InternalError, a mispelled
                                                           responder URI etc.
                                                        */
#define SSF_API_REVOCATION_OCSP_REQUEST_REJECTED     33 /* OCSP request failed.
                                                           The responder was present but did not produce a valid BasicResponse.
                                                           This status may result from client
                                                           or server errors as
                                                           well as an invalid
                                                           response signature.
                                                         */
#define SSF_API_REVOCATION_CERTIFICATE_UNKNOWN       34 /* OCSPSingleResponse::status == revoked */


/**********************************************************************/
/*                                                                    */
/*  typedefs                                                          */
/*                                                                    */
/**********************************************************************/

#ifndef SAP_UINT_MAX /* need some common SAP types */
	/* SSF type for function return codes: SAPRETURN */
	typedef int      SAPRETURN;

	/* SSF type for Integer: SAP_INT */
	typedef int      SAP_INT;
	typedef unsigned int SAP_UINT;
	typedef char	SAP_B7;
	typedef char	SAP_RAW;

	typedef unsigned char SAP_BOOL;
	#ifndef FALSE
		#define FALSE  0
	#endif
	#ifndef TRUE
		#define TRUE  1
	#endif

#endif /* SAP_UINT_MAX */


/* NOTE UC: these two are 'char *' even for UNICODE systems !!! */
/* SSF type for Characterstring names */
typedef SAP_B7 *	SsfCharstring;
typedef SAP_INT		SsfCharlen;

/* SSF type for Octetstring data */
typedef SAP_RAW *	SsfOctetstring;
typedef SAP_INT		SsfOctetlen;


/*--------------------------------------------------------------------*/
/* Signer/Recipient Security Information types -----------------------*/
/*--------------------------------------------------------------------*/

/* Security info of one signer/recipient */
typedef struct /* SigRcpSsfInformation */
{
	SsfCharstring  strSigRcpId;				/* name of signer/recipient */
	SAP_INT        strSigRcpIdL;			/* length of above          */
	SsfCharstring  strSigRcpReserved;		/* reserved for future use  */
	SAP_INT        strSigRcpReservedL;		/* length of above          */
	SsfCharstring  strSigRcpProfile;		/* signer/recip sec profile */
	SAP_INT        strSigRcpProfileL;		/* length of above          */
	SsfCharstring  strSigRcpPassword;		/* password signer/recipient*/
	SAP_INT        strSigRcpPasswordL;		/* length of above          */
	SAP_UINT       uResult;					/* result of SSF operation  */
}   SigRcpSsfInformation;

/* these two names are obsolete - kept here for backwards compatibility  */
#define strSigRcpIdNamespace strSigRcpReserved
#define strSigRcpIdNamespaceL strSigRcpReservedL

/* Pointer to security info of one signer/recipient */
typedef SigRcpSsfInformation *      PtrSigRcpSsfInformation;
    
/* List of signer security info */
typedef struct SigRcpSsfInformationListStruct *   
    SigRcpSsfInformationList;

/* List element of signer security info */
typedef struct SigRcpSsfInformationListStruct 
{
	SigRcpSsfInformationList   ptrNextSigRcp;   /*next element*/
	PtrSigRcpSsfInformation    ptrSigRcp;       /*this element*/
}   SigRcpSsfInformationListElement;


#ifdef SSF_VERSION2

#ifndef SSF_IMPLEMENTATION	
	/* for the implementation part, there should be better typedefs ... */
	typedef struct s_SsfProfile {int dummy;} * SsfProfileHandle;
	typedef struct s_SsfCert {int dummy;} * SsfCertHandle;
	typedef struct s_SsfCertList {int dummy;} * SsfCertListHandle;
#endif

/* this selects a certificate: either provide Subject or (Issuer, SerialNo) */
/*	NOTE: The strings for Subject and Issuer are currently expected 
	to be 0-terminated. This limitation might be removed in the future.
	Please provide the correct length as well!! */
typedef struct {
	SsfCharstring  Subject;		/* must be \0-terminated (currently)! */
	SAP_INT        SubjectL;	/* length of above */
	SsfCharstring  Issuer;		/* must be \0-terminated (currently)! */
	SAP_INT        IssuerL;		/* length of above */
	SsfOctetstring SerialNo;	/* in binary representation: the first octet is the most significant one. */
	SAP_INT        SerialNoL;	/* length of above */
}  SsfCertIdent;

#endif /* SSF_VERSION2 */


#ifdef __cplusplus
}
#endif

#endif  /* SSFXXALL_H */


