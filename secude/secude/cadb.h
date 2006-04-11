/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/cadb.h
 *###
 *### global functions:
 *###
 *###*****************************************/


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#include <secude/af.h>

/*----------------------------------------------------------------------------*/
/*     C A  s                                                                 */
/*----------------------------------------------------------------------------*/
   
#define DEF_ISSUER_ALGID        sha1WithRsaEncryption     /* default CA signature algid RSA  */
#define DEF_ISSUER_ALGID_DSA        dsaWithSHA1          /* default CA signature algid DSA  */
#define DEF_ISSUER_ALGID_DSACommon  dsaCommonWithSHA1    /* default CA signature algid DSA  */
#define DEF_SUBJECT_SIGNALGID   rsaEncryption           /* default CA encryption algid  */
#define DEF_SUBJECT_ENCRALGID   rsaEncryption           /* default CA encryption algid  */


#define CALOG		"calog"
#define	LOGFLAGS	"a+"

#define	LOGINIT(hdl)		log_print(hdl,"%s : INIT\n", logtime());
#define	LOGERR(hdl,msg)	log_print(hdl,"%s : ERROR\t%s\n", logtime(), msg);
#define	LOGAFERR(hdl)	log_print(hdl,"%s : ERROR\t%s\n", logtime(), th_get_last_error_text());
#define	LOGSECERR(hdl)	log_print(hdl,"%s : ERROR\t%s\n", logtime(), th_get_last_error_text());
#define LOGUSER(hdl,N)	log_print(hdl,"%s : NEW USER REGISTERED    <%s>\n", logtime(), N);
#define LOGCERT(hdl,C)	{char *name, *timebefore, *timeafter, *s = CNULL; \
			log_print(hdl,"%s : CERTIFICATE ISSUED FOR <%s>\n                    Validity %s - %s\n",\
			logtime(), name=aux_DName2Name((C)->tbs->subject), \
                        timebefore=aux_readable_UTCTime((C)->tbs->valid->notbefore), \
			timeafter=aux_readable_UTCTime((C)->tbs->valid->notafter));\
			s = aux_sprint_Serialnumber(s, (C)->tbs->serialnumber);\
			log_print(hdl,"                    SerialNo: %s", s);\
			free(s); free(name); free(timebefore); free(timeafter);}

#define LOGCERTSIGN(hdl,C)	{char *name, *timebefore, *timeafter, *s = CNULL; \
			log_print(hdl,"%s : SIGN CERTIFICATE ISSUED FOR <%s>\n                    Validity %s - %s\n",\
			logtime(), name=aux_DName2Name((C)->tbs->subject), \
                        timebefore=aux_readable_UTCTime((C)->tbs->valid->notbefore), \
			timeafter=aux_readable_UTCTime((C)->tbs->valid->notafter));\
			s = aux_sprint_Serialnumber(s, (C)->tbs->serialnumber);\
			log_print(hdl,"                    SerialNo: %s", s);\
			free(s); free(name); free(timebefore); free(timeafter);}

#define LOGCERTENCR(hdl,C)	{char *name, *timebefore, *timeafter, *s = CNULL; \
			log_print(hdl,"%s : ENCR CERTIFICATE ISSUED FOR <%s>\n                    Validity %s - %s\n",\
			logtime(), name=aux_DName2Name((C)->tbs->subject), \
                        timebefore=aux_readable_UTCTime((C)->tbs->valid->notbefore), \
			timeafter=aux_readable_UTCTime((C)->tbs->valid->notafter));\
			s = aux_sprint_Serialnumber(s, (C)->tbs->serialnumber);\
			log_print(hdl,"                    SerialNo: %s", s);\
			free(s); free(name); free(timebefore); free(timeafter);}

#define LOGPEMCRL(hdl,C)    {char *name, *crl; \
			log_print(hdl,"%s : CRL ISSUED BY <%s>:\n%s\n",\
			logtime(), name=aux_DName2Name((C)->crl->tbs->issuer), \
			crl=aux_sprint_CRL(NULL, (C)->crl));\
			free(name); free(crl);}


ASN1_en_de_PROTO(IssuedCertificate)



#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



