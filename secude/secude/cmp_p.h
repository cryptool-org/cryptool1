/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/cmp_p.h
 *###
 *### global functions:
 *###
 *###*****************************************//* cmp_p.h */
/* external */



/*
 * function headers
 */

#ifndef _CMP_P_H_
#define _CMP_P_H_

#if !defined(SECUDE_CMP_INCLUDE) || !SECUDE_CMP_INCLUDE
#error do not include this file, include <secude/cmp.h>
#endif

 /* ------------------ outside interface functions ------------------------- */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
  * @defgroup CMP The Certificate Management Protocol API in the SECUDE SDK
  * @{
  */


/** 
  * this function encodes a complete CMP message
  * @param pkimess a complete filled c-structure
  * @return a SECUDE OctetString within the asn.1 coded CMP message if succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_PKIMessage SEC_PROTOTYPE_1(
	struct CMP_PKIMessage *	, pkimess
);

/** 
  * this function decodes a complete CMP message
  * @param asn1_string a correct asn.1 coded CMP message
  * @return a pointer to a CMP_PKIMessage c-structure if succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIMessage SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_PKIMessage SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

/** 
  * this function verify the signature of a CMP message. The first certificate in the extracerts structure will
  * used for verifying
  * @param pMessage the complete CMP message as c-structure
  * @return TRUE if verification succeded, otherwise FALSE
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
unsigned int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV verify_MessageSignature SEC_PROTOTYPE_1(
	struct CMP_PKIMessage *	, pMessage
);

/** 
  * this function encodes a complete CMP_SeqifInfoType to asn.1
  * @param pSeqIType the c-structure representation
  * @return a SECUDE OctetString within the asn.1 coding if succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_SeqofInfoType SEC_PROTOTYPE_1(
	struct CMP_SeqofInfoType *	, pSeqIType
);

/** 
  * this function decodes a complete CMP_SeqofInfoType to a c-struct
  * @param asn1_string a OctetString within the asn.1 coded SeqofInfoType
  * @return a pointer to the c-struct with the SeqofInfoType if succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_SeqofInfoType SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_SeqofInfoType SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);


/** 
  * this allocation function alloc the memory for the CMP_PKIHeader c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
CMP_PKIHeader SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_PKIHeader SEC_PROTOTYPE_0();

/** 
  * this allocation function alloc the memory for the CMP_PKIBody c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
CMP_PKIBody SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_PKIBody SEC_PROTOTYPE_0();

/** 
  * this allocation function alloc the memory for the SeqCert c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
SeqCert SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_SeqCert SEC_PROTOTYPE_0();

/** 
  * this allocation function alloc the memory for the CMP_PKIBodyCertRequest c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
CMP_PKIBody_CertRequest SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_BodyCertRequest SEC_PROTOTYPE_0();

/** 
  * this allocation function alloc the memory for the CMP_PKIBody_CertResponse c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
CMP_PKIBody_CertResponse SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_BodyCertResponse SEC_PROTOTYPE_0();

/** 
  * this allocation function alloc the memory for the SeqofRevDetails c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
SeqofRevDetails SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_BodyRevReq SEC_PROTOTYPE_0();

/** 
  * this allocation function alloc the memory for the CMP_PKIBodyRevResp c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
CMP_PKIBody_RevResp SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_BodyRevResp SEC_PROTOTYPE_0();

/** 
  * this allocation function alloc the memory for the CMP_PKIMessage c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
CMP_PKIMessage SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_PKIMessage SEC_PROTOTYPE_1(
	enum CMP_PKIBodyType , cnBodyType
);

/** 
  * this allocation function alloc the memory for the SeqValuePair c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
SeqValuePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_SeqValuePair SEC_PROTOTYPE_0();

/** 
  * this allocation function alloc the memory for the CMP_PKIValuePair c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
CMP_PKIValuePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_CMP_PKIValuePair SEC_PROTOTYPE_0();

/** 
  * this allocation function alloc the memory for the SeqValueAttr c-structure
  * @return a pointer to a initialized c-structure if allocation succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
SeqValueAttr SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_Alloc_SeqValueAttr SEC_PROTOTYPE_0();

/** 
  * this deallocation function dealloc the memory for the CMP_PKIMessage c-structure
  * @param pMessage a pointer to the c-structure
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV cmp_Dealloc_PKIMessage SEC_PROTOTYPE_1(
	CMP_PKIMessage ** , pMessage
);

/** 
  * this deallocation function dealloc the memory for the CMP_PKIMessage c-structure
  * @param pMessage a pointer to the c-structure
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV cmp_Dealloc_CMP_PKIValuePair SEC_PROTOTYPE_1(
	CMP_PKIValuePair ** , pSeqValue
);

/** 
  * this deallocation function dealloc the memory for the CMP_SeqofInfoType c-structure
  * @param pMessage a pointer to the c-structure
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV cmp_Dealloc_PKISeqInfoType SEC_PROTOTYPE_1(
	CMP_SeqofInfoType ** , pSeqInfo
);

/** 
  * this deallocation function dealloc the memory for the SeqValuePair c-structure
  * @param pMessage a pointer to the c-structure
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV cmp_Dealloc_SeqValuePair SEC_PROTOTYPE_1(
   SeqValuePair ** , pSeqPair
);

/** 
  * this function build a url like parameter string and encode it in an asn.1-structure
  * @param pSeqPair a pointer to a SeqValuePair structure
  * @return a pointer to the buildt asn.1 structure if succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
CMP_SeqofInfoType SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_set_RegInfo SEC_PROTOTYPE_1(
	SeqValuePair * , pSeqPair
);

/** 
  * this is the opposite function of the function above and decodes the asn.1 structure to a c-struct
  * @param pSeqInfo the asn.1 structure
  * @return the appropriate c-struct if succeded, otherwise NULL
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
SeqValuePair SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_get_RegInfo SEC_PROTOTYPE_1(
	CMP_SeqofInfoType * , pSeqInfo
);

/** 
  * this functions adds a key/value pair to the url param string
  * @param pSeqPair a double pointer to url string
  * @param szName the key value
  * @param szValue the value
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV cmp_add_RegInfoValuePair SEC_PROTOTYPE_3(
	SeqValuePair**	, pSeqPair ,
	char*			, szName ,
	char*			, szValue
);

/** 
  * this function searches a value in a url param string
  * @param pSeqValuePair a pointer to the structure we'd like to search within
  * @param szKey the search value
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV cmp_find_RegInfo SEC_PROTOTYPE_2(
  SeqValuePair* , pSeqVPair ,
  char*  , szKey
);

/**
  * @}
  */

/* global Variables and Constants */

/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_General_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CRL_Reason_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_RegInfo_OID;

/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_RequestEntry_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_RequestEntry_NO_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_RequestEntry_YES_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_RequestEntry_UKNOWN_OID;

/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_CertificateGenerated_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_CertificateGenerated_NO_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_CertificateGenerated_YES_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_CertificateGenerated_UKNOWN_OID;

/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_SmartCardDelivered_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_SmartCardDelivered_NO_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_SmartCardDelivered_YES_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_SmartCardDelivered_UKNOWN_OID;

/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_PINLetterDelivered_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_PINLetterDelivered_NO_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_PINLetterDelivered_YES_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_PINLetterDelivered_UKNOWN_OID;

/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_CertificatePublished_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_CertificatePublished_NO_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_CertificatePublished_YES_OID;
/** a global Object Identifier */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TC_CertificatePublished_UKNOWN_OID;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CMP_P_H_ */

