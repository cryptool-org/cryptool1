/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/urlref.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#ifndef URLREF_H_
#define URLREF_H_

#include <secude/sec_conf.h>

#include <stdlib.h>

#ifndef SSL_INSTALLED
#define SSL_INSTALLED 1
#endif

#if defined(SSL_INSTALLED) && SSL_INSTALLED
#include <secude/ssl.h>
#endif
#include <secude/af.h>

SEC_BEGIN_EXTERNC

typedef struct URL_Structure *URL_Reference;

typedef enum URL_Error {
    URLERR_NOERR, /*0*/
    URLERR_NOREF, /*1*/
    URLERR_ABORTED, /*2*/
    URLERR_ERROR, /*3*/
    URLERR_MEMERR, /*4*/
    URLERR_NOHOST, /*5*/
    URLERR_CONNECTERR, /*6*/
    URLERR_TIMEOUTERR, /*7*/
    URLERR_EOT, /*8*/
    URLERR_NOTIMPLEMENTED, /*9*/
    URLERR_SERVERERR, /*10*/
    URLERR_UNKNOWNPROPERTY, /*11*/
    URLERR_WRONGSSLCERT /*12*/
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
    URLSTATE_CONNECTED,
    URLSTATE_SEND,
    URLSTATE_RECEIVE,
    URLSTATE_CLOSE,
    URLSTATE_SSLCONNECT,
    URLSTATE_SSLCONNECTED,
    URLSTATE_SSLCLOSE
} URL_State;

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_initialize SEC_PROTOTYPE_0();

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_cleanup SEC_PROTOTYPE_0();

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_query SEC_PROTOTYPE_5(
    URL_Reference, ref,
    OctetString *, query,
    const char *, querytype,
    OctetString **, result,
    const char **, resulttype);

URL_Reference SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_newReference SEC_PROTOTYPE_1(
    const char *, url);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_deleteReference SEC_PROTOTYPE_1(
    URL_Reference, ref);

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setProxy SEC_PROTOTYPE_2(
    URL_Reference, ref,
    URL_Reference, proxyref);

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setTimeout SEC_PROTOTYPE_3(
    URL_Reference, ref,
    long, seconds,
    long, microseconds);

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setAuth SEC_PROTOTYPE_3(
    URL_Reference, ref,
    const char *, username,
    const char *, password);

/* progress callback */
typedef SEC_CALLBACK (int, URL_Callback) SEC_PROTOTYPE_2(
    URL_State, state,
    void *, context);

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setCallback SEC_PROTOTYPE_3(
    URL_Reference, ref,
    URL_Callback *, callback,
    void *, context);

/* trace callback */
typedef SEC_CALLBACK(void, URLTraceFunc) SEC_PROTOTYPE_3(
    const char *, header,
    const char *, msg,
    void *, context);

/***** Enumeration URLTraceLevel *****/
/** @ingroup header_ocsp
  */
enum URLTraceLevel {
    URL_TRACENONE = 0,   /**< =0 */
    URL_TRACEERROR,
    URL_TRACEWARNING,
    URL_TRACELOG,
    URL_TRACEALL
};
#ifndef DOXYGEN_EXCLUDE
typedef enum URLTraceLevel URLTraceLevel;
#endif

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setTraceFunc SEC_PROTOTYPE_4(
    URL_Reference, ref,
    URLTraceFunc *, traceFunc,
    void *, traceFuncContext,
    URLTraceLevel, traceLevel);

/* authentication callback */

typedef enum URLAuthentication {
    URL_AUTHNONE = 0,
    URL_AUTHPASS,
    URL_AUTHPROXY,
    URL_AUTHSSL, URL_AUTHSSLEND
} URLAuthentication;

typedef SEC_CALLBACK(void, URLAuthFunc) SEC_PROTOTYPE_3(
    URL_Reference, ref,
    URLAuthentication, auth,
    void *, context);

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setAuthFunc SEC_PROTOTYPE_3(
    URL_Reference, ref,
    URLAuthFunc *, authFunc,
    void *, traceFuncContext);

URL_Reference SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_newTracedReference SEC_PROTOTYPE_4(
    const char *, url,
    URLTraceFunc *, traceFunc,
    void *, traceFuncContext,
    URLTraceLevel, traceLevel);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV url_getStatus SEC_PROTOTYPE_1(
    URL_Reference, ref);

#if defined(SSL_INSTALLED) && SSL_INSTALLED
URL_Error SEC_STATIC_FUNC_PREFIX SEC_API_CALLING_CONV url_setSSL SEC_PROTOTYPE_2(
    URL_Reference, ref,
    H_SSL, ssl);
#endif

Certificates SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV url_get_SSL_peer_certificates SEC_PROTOTYPE_1(
    URL_Reference, ref);

typedef SEC_CALLBACK(URL_Error, URL_SSLCertCallback) SEC_PROTOTYPE_3(
    const char *, hostname,
    Certificates *, ssl_peer_certificates,
    void *, context);

URL_Error SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_setSSLCallback SEC_PROTOTYPE_3(
    URL_Reference, ref,
    URL_SSLCertCallback *, callback,
    void *, context);

#ifdef OCSP_INSTALLED

/* deprecated, don't use */
#define url_OCSPQueryContextMagic (0x4F51636DUL)

/***** Structure url_OCSPQueryContext *****/
/** @ingroup header_ocsp
  */
struct url_OCSPQueryContext {
/** magic value @em url_OCSPQueryContextMagic (to implement limited typechecking). */
    unsigned long magic;
/** The url of a proxy if there is no direct connection to the OCSP responder. */
    const char *proxyurl;
/** The username if the proxy requires authentication. */
    const char *user;
/** The password if the proxy requires authentication. */
    const char *pass;
#if defined(SSL_INSTALLED) && SSL_INSTALLED
    H_SSL ssl;
#else
/** Currently ignored, should be NULL. */
    void *ssl;
#endif
/** Currently ignored, should be NULL. */
    Certificates **ssl_peer_certificates;
/** A callback function for tracing, should be NULL. */
    URL_Callback *callback;
/** A context pointer for the callback function, should be NULL. */
    void *context;
    long seconds;
    long microseconds;
    URLTraceFunc *traceFunc;
    void *traceFuncContext;
    URLTraceLevel traceLevel;
};
/***** Typedef url_OCSPQueryContext *****/
/** @ingroup header_ocsp
  */
typedef struct url_OCSPQueryContext url_OCSPQueryContext;

#define url_OCSPQueryContextMagic2 (0x4F516370UL)

typedef struct url_OCSPQueryContext2 {
    unsigned long magic;
    const char *proxyurl; /* url of a http proxy */
    const char *user; /* username for the proxy */
    const char *pass; /* password for the proxy */
    URLAuthFunc *authFunc; /* authentication callback (proxy, SSL, ...) */
    void *authFuncContext;
    PSE pse; /* SSL pse, if no authentication callback is given */
    AF_options *options; /* SSL pse options */
    URL_SSLCertCallback *sslCertCallback; /* callback to check SSL peer certificate */
    void *sslCertCallbackContext;
    Certificates **ssl_peer_certificates;
    URL_Callback *callback; /* progress callback */
    void *context;
    long seconds; /* maximal time for the query */
    long microseconds;
    URLTraceFunc *traceFunc; /* trace callback */
    void *traceFuncContext;
    URLTraceLevel traceLevel;
} url_OCSPQueryContext2;

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_OCSPQueryFunc SEC_PROTOTYPE_5(
    OctetString *, in,
    OctetString **, out,
    char **, status,
    const char *, responderurl,
    void *, context);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV url_CSCQueryFunc SEC_PROTOTYPE_5(
    OctetString *, in,
    OctetString **, out,
    char **, status,
    const char *, responderurl,
    void *, context);

#endif /* OCSP_INSTALLED */

SEC_END_EXTERNC

#define SENF_API_URLS		(0x55524C53UL)		/* 'URLS' */
#if defined(SSL_INSTALLED) && SSL_INSTALLED
#define URLS_FEAT_SSL		(1UL<< 1)		/* SSL present */
#else
#define URLS_FEAT_SSL		(0UL)			/* SSL absent */
#endif

#endif /* URLREF_H_ */

