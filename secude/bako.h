/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/


/*-----------------------------------------------------------------------*/
/* INCLUDE FILE  bako.h                                                  */
/* Type definitions                                                      */
/*-----------------------------------------------------------------------*/



#ifndef _BAKO_
#define _BAKO_



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




/*      ------------------------------------------------------------------------     */
/*                                                                                   */
/*       © SECUDE GmbH 1997 by Stephan André (mailto:andre@secude.com)               */
/*                                                                                   */
/*      ------------------------------------------------------------------------     */
/*                                                                                   */
/*      BAKO - Basic Cooperation Protocol                                            */
/*             BAKO API implementation of BAKO Specification V1.0                    */
/*                                                                                   */
/*      ------------------------------------------------------------------------     */
/*                                                                                   */
/*      Windows Dialogs by Jochen Dückminor (mailto:dueckminor@darmstadt.gmd.de)     */
/*                                                                                   */
/*      ------------------------------------------------------------------------     */



#include "pem.h"				/* BAKO API V1.0 uses PEM only */

#ifdef SECUDE
#include "../../lib/resource.h"			/* constant string identifier */
#endif

#define BAKO_TRACE

#define BAKO_SESSION_PSE_EXT			".1"			/* session PSE index in MultiPSE structure */
#define BAKO_TRANSACTION_PSE_EXT		".2"			/* transaction PSE index in MultiPSE structure */

#define BAKO_SIGN_PROCTYPE			PEM_MIC_BIN		/* used by PEM mechanism only */
#define BAKO_ENC_PROCTYPE			PEM_ENC_BIN		/* used by PEM mechanism only */
#define BAKO_PKLIST_PROCTYPE			PEM_PKLIST		/* used by PEM mechanism only */
#define BAKO_CERTS				1			/* no. of certificates sent in ordinary signed / encrypted message */
#define BAKO_SIGN_ALG				"RIPEMD-160"
#define BAKO_ENC_ALG				"DES-EDE3-CBC"
#define BAKO_DEK_ALG				"RSA"
	
#define BAKO_DAYS2LIVE				30			/* if client PSE certificate expires in less days open warning dialog */


/*
 * MESSAGES corresponding to BakoResult->bakoStatus
 */

#define SBAKO_NULL				"Status unbekannt"
#define SBAKO_OK				"Initialisierung fehlerfrei"
#define SBAKO_FATAL                             "Interner Fehler"
#define SBAKO_PSE                               "Öffnen der PSE nicht möglich"
#define SBAKO_ERROR                             "Fehler bei Zugriff auf PSE"
#define SBAKO_SAVEERROR                         "Fehler bei Sicherung der PSE"
#define SBAKO_RESTOREERROR                      "Fehler bei Restaurierung der PSE"
#define SBAKO_PARSE                             "Fehler bei Analyse des Transportformats"
#define SBAKO_FAILED                            "Keine Signaturprüfung möglich"
#define SBAKO_FAILED_SECOND                     "Keine Signaturprüfung möglich oder Formatfehler in Sequenz"
#define SBAKO_INVALID                           "Verifizierung fehlgeschlagen"
#define SBAKO_SIGN                              "Signaturerstellung nicht möglich"
#define SBAKO_FORMAT                            "Ungültiges Format"
#define SBAKO_RCPTDNAME				"Ungültiger Empfängername"
#define SBAKO_NOPK				"Kein öffentlicher Schlüssel vorhanden"
#define SBAKO_REJECTED                          "Abgewiesen durch Anwender"
#define SBAKO_MECHANISM                         "Ungültiger Sicherheitsmechanismus"
#define SBAKO_LOCAL                             "Fehler bei Konvertierung in lokales Format"
#define SBAKO_TEXT                              "Ungesicherter Klartext"
#define SBAKO_ENCRYPTEDBAKOGRAM			"Verschlüsseltes Datenpaket"
#define SBAKO_SIGNEDCLIENTHELLO			"Signierte Kundeninitialisierung"
#define SBAKO_SIGNEDSERVERHELLO			"Signierte Serverinitialisierung"
#define SBAKO_SIGNEDORDER			"Signierte Order"
#define SBAKO_SIGNEDRESPONSE			"Signierte Antwort"
#define SBAKO_SIGNEDREGISTRATION		"Signierte Registrierung"
#define SBAKO_SIGNEDCERTREQUEST			"Signierter Zertifizierungsantrag"
#define SBAKO_SIGNEDCERTREPLY			"Signierte Zertifizierungsantwort"
#define SBAKO_SIGNEDREVOCATIONREQUEST		"Signierter Sperrantrag"
#define SBAKO_SIGNEDPUBLICKEYLIST		"Signierte Liste öffentlicher Schlüssel"
#define SBAKO_NOUPDATEINFO			"Keine Aktualisierung erforderlich."
#define SBAKO_UPDATESESSIONCERTFAILED		"Aktualisierung des Verschlüsselungszertifikats fehlgeschlagen"
#define SBAKO_UPDATETRANSACTIONCERTFAILED	"Aktualisierung des Signierzertifikats fehlgeschlagen"
#define SBAKO_UPDATETRANSACTIONPKFAILED		"Aktualisierung des Signierschlüssels fehlgeschlagen"
#define SBAKO_UPDATEPKLISTFAILED		"Aktualisierung der Schlüsselliste fehlgeschlagen"
#define SBAKO_UPDATEDPKLIST			"Öffentliche Schlüssel erfolgreich installiert"
#define SBAKO_UPDATEDCERTS			"Zertifikate erfolgreich installiert"
#define SBAKO_BADSURE				"Ungültiger oder fehlender Paketstempel (oder in HELLO)"
#define SBAKO_BADSUREGEN			"Fehler bei Erzeugung des Paketstempels (oder in HELLO)"


/*
 * MESSAGES returned in BakoResult->validation
 */

#define MBAKO_TRUSTED_NEW_PKROOT                "Signatur gültig: geprüft gegen eigenes Basiszertifikat"
#define MBAKO_TRUSTED_OLD_PKROOT                "Signatur gültig: geprüft gegen altes Basiszertifikat"
#define MBAKO_TRUSTED_PROVIDED_PKROOT           "Signatur gültig: geprüft gegen enthaltenes Basiszertifikat"
#define MBAKO_TRUSTED_PKLIST                    "Signatur gültig: geprüft gegen eigene Liste bekannter Zertifikate"
#define MBAKO_TRUSTED_FCPATH                    "Signatur gültig: geprüft gegen eigenen Zertifikatspfad"
#define MBAKO_TRUSTED_SIGCERT                   "Signatur gültig: geprüft gegen eigenes Zertifikat"
#define MBAKO_TRUSTED_PCA                       "Signatur gültig: geprüft gegen Policy-Zertifikat"
#define MBAKO_PROTOTYPE				"Signatur gültig: Eigener selbstsignierter Prototyp"


/*
 * ERRORS returned in BakoResult->validation
 */

#define EBAKO_REPLY                             "Ungültige Zertifizierungsantwort"
#define EBAKO_ISSUER                            "Ungültiger Ausstellername"

#define EBAKO_FAILED                            "Signatur ungültig"
#define EBAKO_FAILED_SECOND                     "Signatur ungültig oder Formatfehler in Sequenz"
#define EBAKO_FAILED_NEW_PKROOT                 "Signatur ungültig: geprüft gegen eigenes Basiszertifikat"
#define EBAKO_FAILED_OLD_PKROOT                 "Signatur ungültig: geprüft gegen altes Basiszertifikat"
#define EBAKO_FAILED_PROVIDED_PKROOT            "Signatur ungültig: geprüft gegen enthaltenes Basiszertifikat"
#define EBAKO_FAILED_PKLIST                     "Signatur ungültig: geprüft gegen eigene Liste bekannter Zertifikate"
#define EBAKO_FAILED_FCPATH                     "Signatur ungültig: geprüft gegen eigenen Zertifikatspfad"
#define EBAKO_FAILED_NEXT_CERT                  "Signatur ungültig: geprüft gegen Hierarchiezertifikat"
#define EBAKO_FAILED_NEXT_EXPIRED               "Signatur ungültig: abgelaufenes Hierarchiezertifikat"
#define EBAKO_FAILED_NEXT_MISSING               "Signatur ungültig: fehlendes Hierarchiezertifikat"
#define EBAKO_FAILED_LAST_ROOT                  "Signatur ungültig: Selbstsignierter Prototyp"		
#define EBAKO_PROTOTYPE				"Signatur gültig: Selbstsignierter Prototyp"



/* used for Windows dialogs */
#define PRINT(a)  WinDlgAddText(dlg,a);


/* static text */
#define BAKO_REVOKE_TEXT			"USER revocation request\n"


/* imported types from pem.h:
 *
 * typedef int                  RC
 * typedef char                 Boolean
 * define TRUE                  1
 * define FALSE                 0
 * typedef struct { sec_uint4 noctets; char *octets } OctetString 
 */



typedef enum {
	BadSURE				= -300,		/*  +0 - SURE label validation failed */
	BadSUREgen,					/*  +1 - SURE label generation failed */
	NoUpdateInfo			= -200,		/*  +0 - bakogram does not contain CR or PKList to update PSE */
	UpdateSessionCertFailed,			/*  +1 - error during session PSE update of certificate */
	UpdateTransactionCertFailed,			/*  +2 - error during transaction PSE update of certificate */
	UpdateTransactionPKFailed,			/*  +3 - error during session PSE update of PKList with transaction PK during certificate installation */
	UpdatePKListFailed,				/*  +4 - error during session PSE update of PKList */
	Invalid				= -100,         /*  +0 - no valid Bakogram */
	Failed,                                         /*  +1 - unable to (de-)enhance */
	FailedSecond,                                   /*  +2 - unable to (de-)enhance second wrapper in level */
	RcptDName,					/*  +3 - invalid Distinguished Name of recipient */
	NoPK,						/*  +4 - no recipient Public Key stored */
	Format,						/*  +5 - format error in Bakogram */
	Mechanism,					/*  +6 - illegal BAKO mechanism */
	Rejected,                                       /*  +7 - user rejected action */
	SaveError,                                      /*  +8 - error during PSE saving */
	RestoreError,                                   /*  +9 - error during PSE restoring */
	Error,                                          /*  +10 - error during PSE access */
	Fatal,                                          /*  +11 - system error (e.g. memory allocation) */
	Null				= 0,            /*  +0 - initial value */
	OK,                                             /*  +1 - initialisation OK */
	Text,                                           /*  +2 - plain text or nothing done */
	EncryptedBakogram,                              /*  +3 - wrapped session data */
	SignedClientHello,                              /*  +4 - client signed HELLO */
	SignedServerHello,                              /*  +5 - server signed HELLO */
	SignedOrder,                                    /*  +6 - client signed transaction data */
	SignedResponse,                                 /*  +7 - server signed transaction data */
	SignedRegistration,                             /*  +8 - client signed user registration */
	SignedCertRequest,                              /*  +9 - client signed certification request */
	SignedCertReply,                                /*  +10 - server signed certification reply */
	SignedRevocationRequest,                        /*  +11 - client signed revocation request */
	SignedPublicKeyList,                            /*  +12 - server signed public key list */
	UpdatedPKList,				        /*  +13 - successfully updated PSE's PKList */
	UpdatedCerts				        /*  +14 - successfully updated PSE's Cert/FCPath/PKRoot */
} bakostatus;

typedef enum {
	BAKO_PEM,
	BAKO_PEM_SURE,
	BAKO_PKCS,
	BAKO_PKCS_SURE
} bakomechanism;

struct bakogram {                                       /* BAKO data unit */
	char			*version;		/* BAKO format version identifier */
	char			*utcTime;		/* time stamp as UTCTime string */
	OctetString             *data;			/* optional: additional data outside message */
	OctetString             *message;               /* message in transport encoding */
};
typedef struct bakogram          Bakogram;

struct bakorcpts {                                      /* list of recipients for encryption */
	char			*name;			/* recipient name */
	struct bakorcpts	*next;			/* next in list */
};
typedef struct bakorcpts         BakoRcpts;


struct bakoresult {                                     /* structure returned by BAKO API functions */
#ifdef BAKO_TRACE
	char			*callproc;		/* debugging only */
#endif
	bakostatus               bakoStatus;            /* status of BAKO operation on this Bakogram */
	char                    *signer;                /* readable distinguished name of signer */
	char                    *signerFP;              /* readable fingerprint of signer */
	char                    *issuer;                /* readable distinguished name of direct issuer */
	char                    *issuerFP;              /* readable fingerprint of direct issuer */
	char                    *root;                  /* readable distinguished name of root issuer */
	char                    *rootFP;                /* readable fingerprint of root issuer */
	OctetString             *sessionID;             /* (random) session identifier generated by server, processed by application */
	OctetString             *transactionID;         /* (random) transaction identifier generated by client, processed by application */
	char                    *timestamp;             /* time stamp string in readable UTCTime form */
	OctetString             *body;                  /* unwrapped/validated body of this Bakogram, may be another
							   Bakogram (which is unwrapped/validated in 'next' */
	OctetString             *data;                  /* additional data of this Bakogram, may be application data */
	char                    *validation;            /* Validation result in readable form */
	struct bakoresult       *next;                  /* succeeding Bakogram's de-enhancement result or NULL */
};
typedef struct bakoresult        BakoResult;
	

struct BAKO_ctx {                                       /* BAKO session context structure */
	bakomechanism		mechanism;		/* security wrapping mechanism to be used in a session */
	OctetString            *sessionID;		/* session identifier containing random data (application defined) */
	char                   *psename;		/* file name of MultiPSE containing session PSE and transaction PSE */
	Boolean                sessionMode;		/* TRUE if client or server has generated HELLO */
	/* client-side only */
	PSE                     sessionPSE;             /* PSE used for implicit signing & encrypting of session data */
	PSE                     transactionPSE;         /* PSE used for explicit signing of transaction and administrative data */
	char			*commonName;		/* Common Name part of Session DName (which should be the same for both PSEs!) */
	char			*doubleFingerprint;	/* fingerprint calculated from both PSE's public key bitstrings */
	/* server-side only */
	PSE                     serverPSE;		/* PSE used by server for validating, decrypting, signing, and encrypting any data*/
	PKList                 *serverVirtualPKList;	/* temporay PKList used by server for encrypting any data with previously scanned client PK */
	BakoRcpts	       *serverRecipients;	/* previously scanned client names for encryption */
};
typedef struct BAKO_ctx		 BAKO_ctx;
typedef struct BAKO_ctx         *BAKO;




/*****
 ***** Signed Unique References
 ***** - session labels for Bakograms
 *****
 *****/

/* tokens */
#define SURE_DELIMITER		"\t\r\n:"
#define SURE_BEGIN_KEY		"-----BEGIN SIGNED UNIQUE REFERENCE-----"
#define SURE_END_KEY		"-----END SIGNED UNIQUE REFERENCE-----"
#define SURE_VERSION_KEY	"Version"
#define SURE_SESSION_KEY	"Session"
#define SURE_TRANSACTION_KEY	"Transaction"
#define SURE_TIMESTAMP_KEY	"Timestamp"
#define SURE_STATUS_KEY		"Status"

/* values */
#define BAKO_VERSION			"BAKO-V1.0"
#define BAKO_CLIENT_HELLO		"SignedClientHello"
#define BAKO_SERVER_HELLO		"SignedServerHello"
#define BAKO_ORDER			"SignedOrder"
#define BAKO_RESPONSE			"SignedResponse"
#define BAKO_REGISTRATION		"SignedRegistration"
#define BAKO_CERT_REQUEST		"SignedCertRequest"
#define BAKO_CERT_REPLY			"SignedCertReply"
#define BAKO_REVOCATION_REQUEST		"SignedRevocationRequest"
#define BAKO_PKLIST			"SignedPublicKeyList"

/* parameters */
#define BAKO_RANDOM_BITS		64


#define bUPDATE		TRUE
#define bNOUPDATE	FALSE


/* for testing... */
#ifdef BAKO_TRACE
#define PUTCALLPROC(p)	{if (p && (p)->callproc) aux_free_String(&((p)->callproc)); (p)->callproc = aux_cpy_String(proc);}
#ifdef WIN32
#define BAKO_DEF_CLIENT_PSE			".\\dirba.pse"	/* default client PSE path and name */
#define BAKO_DEF_SERVER_PSE			".\\server.pse"	/* default server PSE path and name */
#else
#define BAKO_DEF_CLIENT_PSE			".//dirba.pse"	/* default client PSE path and name */
#define BAKO_DEF_SERVER_PSE			".//server.pse"	/* default server PSE path and name */
#endif
#else
#define PUTCALLPROC(p) {}
#endif /* BAKO_TRACE */



#include "bako_p.h"                                     /* prototypes */


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* _BAKO_ */

