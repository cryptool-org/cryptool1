/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/


#ifndef _SEC_UTIL_H_
#define _SEC_UTIL_H_

#include "af.h"
#ifdef PKCS_INSTALLED
#include "pkcs.h"
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

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* _SEC_UTIL_H_*/



