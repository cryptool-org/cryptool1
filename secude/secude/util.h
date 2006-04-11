/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/util.h
 *###
 *### global functions:
 *###
 *###*****************************************/


#ifndef _SEC_UTIL_H_
#define _SEC_UTIL_H_

#include <secude/af.h>
#ifdef PKCS_INSTALLED
#include <secude/pkcs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef enum {
	CERTREQTYPE_CERT,
	CERTREQTYPE_PKCS7,
	CERTREQTYPE_PKCS10,
	CERTREQTYPE_PEM,
	CERTREQTYPE_NETSCAPE_BROWSER_REQ
} KEY_TRANSPORT_TYPE;

RC enter SEC_PROTOTYPE_3(
	char *, text,
	char *, puff,
	int , len
);
RC parse_cert_request SEC_PROTOTYPE_7(
	OctetString	*	, inp,
	KEY_TRANSPORT_TYPE	*	, type, 
	Boolean		*	, base64, 
	char		**	, boundary1, 
	char		**	, boundary2, 
	Certificate	**	, p_cert,
	void		**	, reserved
);

int objidsinit SEC_PROTOTYPE_3(
	char	 *, s_objids_destpath,
	char	 *, s_objids_destfile,
	char	 *, s_objids_source
);

#if defined(X509v3) && defined(CA_FUNCTIONS_INSTALLED)
int caextinit SEC_PROTOTYPE_3(
	char	 *, s_caexts_destpath,
	char	 *, s_caexts_destfile,
	char	 *, s_caexts_source
);
int cacrlextinit SEC_PROTOTYPE_3(
	char	 *,	s_caexts_destpath,
	char	 *,	s_caexts_destfile,
	char	 *,	s_caexts_source
);

#endif

RC change_cert_values SEC_PROTOTYPE_1(
	Certificate	*	, cert
);
RC build_cert_reply SEC_PROTOTYPE_9(
	PSE			, pse,
	KEY_TRANSPORT_TYPE		, type, 
	Boolean			, base64, 
	char		*	, boundary1, 
	char		*	, boundary2, 
	Certificate	*	, cert,
	OctetString	**	, output,
	void		*	, reserved,
	Boolean			, usecrl
);
Validity * aux_get_Validity SEC_PROTOTYPE_2(
	char	*	, notbefore,
	char	*	, notafter
);

#ifdef PKCS_INSTALLED
RC update_PSE SEC_PROTOTYPE_6(
	PSE , pse,
	SET_OF_CRL * , crls,
	Certificates * , certs,
	Certificate * , root_cert,
	ExtendedCertificatesAndCertificates * , ext_certs,
	int , verbose
);
#endif

RC SEC_API_CALLING_CONV pin_cb SEC_PROTOTYPE_2(
    void * ,client_data,
    void * ,cb_data
);

PSE util_af_open SEC_PROTOTYPE_6(
	char	 *	, psename,
	char	 *	, cadir,
	AF_options *	, af_options,
	int		, sct_id,
	Boolean		, single_login,
	char     *  , pin
);

int  get_cert_properties SEC_PROTOTYPE_2(char *, optarg, char **, info);

Certificate * templ2cert SEC_PROTOTYPE_5(PSE, pse, KeyInfo *, keyinfo, char *, obj_name,
										 DName *, subject, char *, templ_file);

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* _SEC_UTIL_H_*/



