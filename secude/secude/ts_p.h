/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/ts_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#if !defined(SECUDE_TS_INCLUDE) || !SECUDE_TS_INCLUDE
#error do not include this file, include <secude/tesecude.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sme_init SEC_PROTOTYPE_0();

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sme_final SEC_PROTOTYPE_0();

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sme_sign SEC_PROTOTYPE_4(
	PSE           , pse_handle,
	char        * , infile,
	char        * , outfile,
	ts_sme_type * , sme_type_p
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sme_any SEC_PROTOTYPE_3(
	char        * , infile,
	char        * , outfile,
	ts_sme_type * , sme_type_p
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sme_encrypt SEC_PROTOTYPE_5(
	PSE           , pse_handle,
	char        * , infile,
	char        * , outfile,
	SET_OF_TSCertTemplate     * , recipients,
	ts_sme_type * , sme_type_p
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sme_scan SEC_PROTOTYPE_7(
	PSE           , pse_handle,
	char        * , infile,
	char        * , outfile,
	ts_sme_type * , sme_type_p,
	TSVerRes       **, verif_result,
	TSEncPar       **, encpar,
	TSFileOri	* , fo_par_p
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_TBS_from_cert_encoding SEC_PROTOTYPE_2(
        OctetString       *  , certDER,
	ts_cert_type         , cert_type
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_TSVerRes SEC_PROTOTYPE_3(
	PSE				, pse,
	char			 *	, string,
	TSVerRes		 *	, verRes
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_TSVerRes SEC_PROTOTYPE_3(
	PSE				, pse,
	FILE			 *	, ff,
	TSVerRes		 *	, verRes
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_TSVerRes SEC_PROTOTYPE_2(
	PSE				, pse,
	TSVerRes		 *	, verRes
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_TSVerRes SEC_PROTOTYPE_1(
	TSVerRes	 *	, verRes
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TSVerRes SEC_PROTOTYPE_1(
	TSVerRes	 **	, verRes
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_TSFileOri SEC_PROTOTYPE_1(
	TSFileOri	*	, fo
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TSFileOri SEC_PROTOTYPE_1(
	TSFileOri	**	, fo
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_TSCertTemplate SEC_PROTOTYPE_1(
	TSCertTemplate	 *	, cert
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TSCertTemplate SEC_PROTOTYPE_1(
	TSCertTemplate	 **	, cert
);
TSCertTemplate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_TSCertTemplate SEC_PROTOTYPE_1(
	TSCertTemplate	 *	, cert
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_TSCertTemplate SEC_PROTOTYPE_1(
	SET_OF_TSCertTemplate	 **	, certsetp
);
SET_OF_TSCertTemplate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_SET_OF_TSCertTemplate SEC_PROTOTYPE_1(
	SET_OF_TSCertTemplate	 *	, certset
);

SET_OF_TSCertTemplate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_TSPKDP2SET_OF_TSCertTemplate SEC_PROTOTYPE_1(
	OctetString	 *	, PKDP_octets
);

Crl SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_TSRLP2Crl SEC_PROTOTYPE_1(
	OctetString	 *	, RLP_octets
);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_TelesecCertTBS SEC_PROTOTYPE_1(
	TelesecCertTBS	 *	, tbs
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TelesecCertTBS SEC_PROTOTYPE_1(
	TelesecCertTBS	 **	, tbs
);
TelesecCertTBS SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_TelesecCertTBS SEC_PROTOTYPE_1(
	TelesecCertTBS	 *	, tbs
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_TelesecCert SEC_PROTOTYPE_1(
	TelesecCert	 *	, cert
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TelesecCert SEC_PROTOTYPE_1(
	TelesecCert	 **	, cert
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_TSEncPar SEC_PROTOTYPE_1(
	TSEncPar	 *	, encpar
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_TSEncPar SEC_PROTOTYPE_1(
	TSEncPar	 **	, encpar
);
TSEncPar SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_TSEncPar SEC_PROTOTYPE_1(
	TSEncPar	 *	, encpar
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_TelesecCertTBS SEC_PROTOTYPE_3(
	PSE				, pse,
	char			 *	, string,
	TelesecCertTBS		 *	, tbs
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_TelesecCertTBS SEC_PROTOTYPE_3(
	PSE			, pse,
	FILE		 *	, ff,
	TelesecCertTBS	 *	, tbs
);
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_TelesecCertTBS SEC_PROTOTYPE_2(
	PSE			, pse,
	TelesecCertTBS	 *	, tbs
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_TelesecCert SEC_PROTOTYPE_3(
	PSE				, pse,
	char			 *	, string,
	TelesecCert		 *	, cert
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_TelesecCert SEC_PROTOTYPE_3(
	PSE			, pse,
	FILE		 *	, ff,
	TelesecCert	 *	, cert
);
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_TelesecCert SEC_PROTOTYPE_2(
	PSE			, pse,
	TelesecCert	 *	, cert
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_SET_OF_TSCertTemplate SEC_PROTOTYPE_3(
	PSE				, pse,
	FILE		 	 *	, ff,
	SET_OF_TSCertTemplate	 *	, certset
);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_TelesecCert SEC_PROTOTYPE_1(
	TelesecCert	 *	, cert
);
TelesecCert SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_TelesecCert SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_DERcode SEC_PROTOTYPE_1(
	OctetString	 *	, der
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_DERcode SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

#ifdef X509v3
ToBeSigned SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_TelesecCert2X509v3TBS SEC_PROTOTYPE_2(
	OctetString	*	, cert_DERcode,
	KeyType			, keytype
);
TSCertTemplate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_X509v3TBS2TSCertTemplate SEC_PROTOTYPE_1(
	ToBeSigned	*	, tbs
);
Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_TelesecTBS2signedCert SEC_PROTOTYPE_3(
	PSE		  	, pse,
	OctetString	*	, cert_DERcode,
	ToBeSigned	*	, tbs
);

CRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_Crl2CRL SEC_PROTOTYPE_2(
	PSE		, pse,
	Crl	*	, crlist
);

#endif



/***   New Prototypes for Communication with Telesec Trust Center   ***/

SET_OF_TSCertTemplate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pks_request_PKDP SEC_PROTOTYPE_4(
	PSE			, pse_handle,
	pks_FILTER	*	, filter,
	char		*	, call_number,
	int    		*	, no_of_returned_certs
);

Crl SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pks_request_RLP SEC_PROTOTYPE_3(
	PSE			, pse_handle,
	char		*	, call_number,
	int    		*	, no_of_returned_entries
);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pks_retrieve_Certificate SEC_PROTOTYPE_4(
	PSE			, pse_handle,
	char		*	, callNumber,
	KeyType	  		, ktype,
	DName	 	*	, dname
);

TSCertTemplate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pks_retrieve_TSCertTemplate SEC_PROTOTYPE_3(
	PSE			, pse_handle,
	char		*	, callNumber,
	DName	 	*	, dname
);

ts_check_res SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pks_check_certificate SEC_PROTOTYPE_4(
	PSE			, pse_handle,
	char		*	, call_number,
	TSCertTemplate  *	, tscert,
	UTCTime		**	, time
);

pks_FILTER SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_pks0_filter SEC_PROTOTYPE_1(
        char        * , timeofIssue
);

pks_FILTER SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_pks8_filter SEC_PROTOTYPE_8(
    char	* , surName,
    char	* , givenName,
    char	* , postalCode,
    char	* , localityName,
    char	* , organisationName,
    char	* , organisationUnitName,
    char	* , timeofIssue,
    int		  , userGroupR
);

pks_FILTER SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_pks1_filter SEC_PROTOTYPE_2(
        char        * , certNumber,
	DName	    * , dname

);

RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_pks_sign_dummy SEC_PROTOTYPE_2(
	PSE			, pse_handle,
	char		**	, signedSME_file
);

ts_cert_type SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2ts_cert_type SEC_PROTOTYPE_1(
	ObjId		*	, oid
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_TSCertNum2SerialNumber SEC_PROTOTYPE_2(
	char	*	, certNumber,
	KeyType		, keytype
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_getTSCertTemplate_forDName SEC_PROTOTYPE_5(
	PSE			, pse_handle,
	DName		*	, dname,
	KeyType			, type,
	char		*	, ttc_callNumber,
	TSCertTemplate **	, tscert

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_search_for_TSCertTemplate SEC_PROTOTYPE_4(
	PSE			, pse_handle,
	TSCertTemplate  *	, tscert,
	KeyType			, type,
	char		*	, ttc_callNumber

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_is_TSCertTemplate_revoked SEC_PROTOTYPE_8(
	PSE			, pse_handle,
	TSCertTemplate  *	, tscert,
	UTCTime 	*	, relevant_time,
	KeyType			, type,
	char		*	, ttc_callNumber,
	UTCTime		**	, revocation_time,
        CRL         	**	, retCRL,
	UTCTime		**	, next_update

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ts_input SEC_PROTOTYPE_3(
	char *, text,
	char *, puff,
	int , len
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ts_look_for_PublicKey SEC_PROTOTYPE_3(
	PSE    			, pse_handle,
	KeyType		  	, type,
	ToBeSigned	 *	, pk
);

#if 0
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_OctetString2LongSerial SEC_PROTOTYPE_1(
        OctetString            *  , sernum
);
#endif

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_DName2SubjectPart SEC_PROTOTYPE_1(
	DName	    * , dname
);


#ifdef TRACE_SME
extern struct  timeval ts_time_tp1, ts_time_tp2;
extern struct  timezone ts_time_tzp1, ts_time_tzp2;
#define TS_TIME_START(str) {aux_gettimeofday(&ts_time_tp1, &ts_time_tzp1); fprintf(stderr, "$ %s\n", str);}
#define TS_TIME_PRINT(str) {aux_gettimeofday(&ts_time_tp2, &ts_time_tzp2);\
	fprintf(stderr, "$ %s: %d us\n", str, ((ts_time_tp2.tv_sec - ts_time_tp1.tv_sec)) * 1000000 + (ts_time_tp2.tv_usec - ts_time_tp1.tv_usec));}
#else
#define TS_TIME_START(str)
#define TS_TIME_PRINT(str)
#endif


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

