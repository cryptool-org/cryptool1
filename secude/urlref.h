#ifndef URLREF_H_
#define URLREF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <af.h>

typedef void* URL_Reference;

typedef enum URL_Error {
	URLERR_NOERR,
	URLERR_NOREF,
	URLERR_ABORTED,
	URLERR_ERROR,
	URLERR_MEMERR,
	URLERR_NOHOST,
	URLERR_CONNECTERR,
	URLERR_TIMEOUTERR,
	URLERR_EOT,
	URLERR_NOTIMPLEMENTED,
	URLERR_UNKNOWNPROPERTY
} URL_Error;

typedef enum URL_Property {
	URLPROP_NONE,
	URLPROP_USERNAME,
	URLPROP_PASSWORD,
	URLPROP_HOST,
	URLPROP_PATH,
	URLPROP_PORT,
	URLPROP_MIMETYPE,
	URLPROP_USERAGENT
} URL_Property;

typedef enum URL_State {
	URLSTATE_NONE,
	URLSTATE_ERR,
	URLSTATE_CONNECT,
	URLSTATE_SEND,
	URLSTATE_RECEIVE,
	URLSTATE_CLOSE
} URL_State;

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_query SEC_PROTOTYPE_5(
	URL_Reference, ref,
	OctetString*, query,
	const char*, querytype,
	OctetString**, result,
	const char**, resulttype);

URL_Reference SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_newReference SEC_PROTOTYPE_1(
	const char*, url);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_deleteReference SEC_PROTOTYPE_1(
	URL_Reference, ref);

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setProxy SEC_PROTOTYPE_2(
	URL_Reference, ref,
	URL_Reference, proxyref);

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setTimeout SEC_PROTOTYPE_3(
	URL_Reference, ref,
	long, seconds,
	long, microseconds);

typedef int (URL_Callback)(URL_State state, void* context);

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setCallback SEC_PROTOTYPE_3(
	URL_Reference, ref,
	URL_Callback *, callback,
	void *, context);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV url_getStatus SEC_PROTOTYPE_1(
	URL_Reference, ref);

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* URLREF_H_ */

