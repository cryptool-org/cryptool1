/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

/*-----------------------------------------------------------------------*/
/* INCLUDE FILE  secure.h                                                */
/* Definition of structures and types for the basic security functions   */
/*-----------------------------------------------------------------------*/

#ifndef _SECURE_
#define _SECURE_

#include "arithmet.h"
#include "filename.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#ifdef SAPSECULIB
#define DEFAULT_RSA_SIG_ALG SAPSECULIB_RSA_ALG
/* changed DSA default in accordance to MM, 02/01/2000 */
#define DEFAULT_DSA_SIG_ALG id_dsa_with_sha1
#else
#define DEFAULT_RSA_SIG_ALG sha1WithRsaEncryption
#define DEFAULT_DSA_SIG_ALG dsaWithSHA1
#endif
#define DEFAULT_DSACommon_SIG_ALG dsaCommonWithSHA1

#ifdef SEC_PC
#define chmod(a,b)
#endif /*SEC_PC*/


typedef SET_OF(OctetString)     SET_OF_OctetString;

typedef SET_OF(ObjId)           SET_OF_ObjId;
typedef struct Key              Key;
typedef struct PSE_Sel          PSESel;
typedef struct PSE_Toc          PSEToc;
typedef struct PSE_Object       PSEObject;
typedef struct PSE_Objects      PSEObjects;

/*-----------------------------------------------------------------------*/
/*    P S E                                                              */
/*-----------------------------------------------------------------------*/

typedef enum { Extension_PIN } PINType;
typedef enum { CB_TYPE_VERIFY, CB_TYPE_SET, CB_TYPE_CHANGE } CBType;
typedef struct {
    sec_uint4 type;         /* type of operation, CB_TYPE_VERIFY, CB_TYPE_SET, CB_TYPE_CHANGE */
    char      pin[65];      /* verify: the PIN to verify                                      */
                            /* set: the PIN to initialize                                     */
                            /* change: the old PIN                                            */
    char      newpin[65];   /* change: the new PIN                                            */
    char      retry;        /* TRUE if there was an unsuccessful verification/initialization before */
    int       counter;      /* the number of remaining  presentations of bad PIN, -1: not supported */
    PINType   pintype;      /* identification for the PIN object                              */
    char *    pinname;      /* identification for the PIN object as printable string          */
    
} CB_DATA_PIN;
typedef RC      ( SEC_API_CALLING_CONV SECUDE_CB_T )    SEC_PROTOTYPE_2( void * ,client_data,void *, callback_data);

typedef struct SC_DATA SC_DATA;

struct SC_DATA {
	int		 need_pin;                      /* 
	                                         * Tells if a PIN is needed to open the PSE (TRUE/FALSE)
	                                         */
	int		 enter_pin_on_SCT;              /* 
	                                         * Tells if the PIN has to be entered on the SCT (TRUE/FALSE)
	                                         */
	int		 need_SC;                       /* 
	                                         * Tells if the Card has to be inserted 
	                                         * 0: SC already inserted
	                                         * 1: No SC inserted, SC not activated
	                                         * 2: SC inserted, but could not be activated. Probably it was inserted incorrectly
	                                         */
    int  	 sct_id;                        /* 
	                                         * The SCT identifier
	                                         */
	int		 SC_timer;                      /* 
	                                         * The time in seconds the SCT waits until the SC is inserted. If SC_timer
	                                         * is set to 0, no time-out is specified. Default value is 20. Could be
	                                         * changed by the application before the open/create call
	                                         */
	char	*puk;                           /* 
	                                         * The PUK or NULL pointer (no PUK).
    					                     * The application should set this element for using
    					                     * sec_create, sec_delete_PSE or sec_unblock_pin.
    					                     * If puk_counter is set to -1 by sec_get_SC_DATA
    					                     * PUK handling is not supported. 
	                                         */
	int		 pin_counter;                   /* 
	                                         * On most cards there is a counter for false attempt to enter the PIN.
                                             * If there is a PSE on Card sec_get_SC_DATA
                                             * sets this element to the number of remaining attempts to enter the correct PIN.
                                             * If there is no PSE on Card sec_get_SC_DATA
                                             * sets this element to the highest supported value of this counter and the application
    					                     * should change it to the desired value when calling
    					                     * sec_create
    					                     * If not supported the element is set to -1.
	                                         */
	int		 puk_counter;                   /* 
	                                         * On most cards there is a counter for false attempt to enter the PUK.
                                             * If there is a PSE on Card sec_get_SC_DATA
                                             * sets this element to the number of remaining attempts to enter the correct PUK.
                                             * If there is no PSE on Card sec_get_SC_DATA
                                             * sets this element to the highest supported value of this counter and the application
    					                     * should change it to the desired value when calling
    					                     * sec_create
    					                     * If not supported the element is set to -1 or 0 (PUK supported but no PSE on card). 
	                                         */
	void	*func;                          /* 
	                                         * Internal information of SECURE interface to handle SC-PSEs 
	                                         */
	char	*product_info;                  /* 
	                                         * Information about the SmartCard access library 
	                                         */
	char	*sct;                           /* 
	                                         * Information about SCT (NULLpointer : A cryptographic modul is accessed not a SCT) 
	                                         */
	char	*sc;                            /* 
	                                         * Information about SC 
	                                         */
	void	*hdl;                           /* 
	                                         * Internal information of plugin interface to handle SC-PSEs 
	                                         */
	char	*serial;                        /* 
	                                         * SmartCard serial number (if available) 
	                                         */
	int		 enter_pin_on_SCT_on_install;   /* 
	                                         * TRUE if SCT has a PIN-PAD and the PIN has to be entered there when creating a PSE 
	                                         */
	int		 enter_pin_on_SCT_on_change;    /* 
	                                         * TRUE ifSCT has a PIN-PAD and the PIN has to be entered there when change the PIN  
	                                         */
	int		*supported_algs_and_sizes; 
                                			/* This integer array has the following format:
                                      			   [alg_type [begin_of_scope end_of_scope step]* -1 ]* -1     
                                			   EXAMPLE: RSA, 512, 1024, 512,-1,-1  
                                			   EXAMPLE: RSA, 512, 512, 1, 1024, 1024, 1,-1,-1  
                                			   NULL Pointer mean's that no information is available */
	char	 delete_flag;
                                			/* 
                                			  After get_SC_DATA: (PSE existing)
                                				(delete_flag == DEL_UNKNOWN) Don't know if PIN is needed for deleting a SC PSE.
                                				(delete_flag == DEL_WITH_PIN) Need PIN to delete PSE
                                				(delete_flag == DEL_WITH_PUK) Need PUK to delete PSE
                                				(delete_flag == DEL_WITHOUT_PIN) PSE could be deleted without any check
                                				
                                			  After get_SC_DATA: (PSE not existing)
                                				(delete_flag == DEL_UNKNOWN) Don't know if PIN is needed for deleting a SC PSE.
                                				(delete_flag & DEL_WITH_PIN) It's possible to create a 
                                											 PSE that could only be deleted after PIN check
                                				(delete_flag & DEL_WITH_PUK) It's possible to create a 
                                											 PSE that could only be deleted after PUK check
                                				(delete_flag & DEL_WITHOUT_PIN) It's possible to create a 
                                											 PSE that could be deleted without PIN check
                                											 
                                		      When creating a PSE
                                				(delete_flag == DEL_WITH_PIN) A PSE is created that could 
                                											 only be deleted after PIN check
                                				(delete_flag == DEL_WITH_PIN) A PSE is created that could 
                                											 only be deleted after PUK check
                                				(delete_flag == DEL_WITHOUT_PIN) A PSE is created that could
                                											 be deleted without PIN check
                                				 OTHERWISE					 Don't know if PIN is needed for deleting the PSE */
	char	 write_later;
			                                 /* if TRUE it's allowed to wait with writing the SC file until sec_close() call */
	char	*plugin_name;                    /* Name of SC plugin */
	char	*card_name;                      /* Name of SmartCard */
	char	 eject;                          /* eject Card on sec_close */
	char	 recreate_ext;                   /* Not supported any more */
	int      SCT_timer;                      /* seconds to wait for getting a connection to the SCT */
	int      SCT_timer_tps;                  /* tests per second */
	char	 pkcs1_signature_only;           /* supported RSA padding methods for signature(SIGPAD_ALL,SIGPAD_PKCS1,SIGPAD_ISO9796_2)*/
	char     sct_mode;                       /* This field specifies if the connection to the SCT should be open until the PSE is closed 
                                			  After get_SC_DATA:
                                				(sct_mode == SCT_UNKNOWN) Don't know supported modes.
                                				(sct_mode & SCT_HOLD_OPEN) Supported: Connection is close when PSE is closed
                                				(sct_mode & SCT_CLOSE_AFTER_EACH_CALL) Supported: Connection is close after each call
                                											 
                                		      When opening a PSE
                                				(sct_mode == SCT_HOLD_OPEN) Connection is close when PSE is closed
                                				(sct_mode == SCT_CLOSE_AFTER_EACH_CALL) Connection is close after each call */
	int      min_pin_len;                    /* minimal pin size to be used (0 if unknown)*/
	int      max_pin_len;                    /* minimal pin size to be used (0 if unknown)*/
	char     need_pin_change;                /* PIN_NULLPIN : NULL-transport PIN is active: PIN has to be changed (with empty old PIN) before Card could be used 
	                                            PIN_TRANSPORTPIN: Transport PIN is active: PIN has to be changed before Card could be used
	                                            PIN_NORMAL_PIN : No transport PIN
	                                            PIN_USE_EXISTING_PIN : Existing PIN has to be used when creating a PSE
	                                            LOGIN_WITHOUT_PIN : Login without PIN is possible to see public objects 
	                                          */
	char     unblock;                        /* SUP_UNKNOWN, SUP_YES, SUP_NO */
	char     pin_change;                     /* SUP_UNKNOWN, SUP_YES, SUP_NO */
	char     decrypt;                        /* (decrypt == DECR_UNKNOWN) : Don't know supported modes.                                           
	                                            (decrypt == DECR_YES) : Decryption supported.                                                     
	                                            (decrypt == DECR_NO) : Decryption not supported.                                                  
	                                            (decrypt == DECR_RESTRICTED) : Decryption restricted to known clear text size (see next element). 
	                                            (decrypt == DECR_RESTRICTION_UNKNOWN) : Decryption restricted to unknown clear text size.         
	                                          */
	int      decrypt_restr;                  /* decrypt restriction bits, see element 'decrypt' */
	char   **mPSEs;                          /* unused */
	char     extension_objects_first;        /* TRUE if an objects should searched in the extension first */
	SECUDE_CB_T *pin_cb;                     /* callback to prompt for additional PIN to be used for verification/initialization/change */  
	void    *pin_cb_data;                    /* callback data */
	char     pin_cb_use_for_verify;          /* If TRUE the 'pin_cb' function is allowed to be used for prompting for PIN to be used
                                                (PIN verification). */
	char     pin_cb_use_for_set;             /* If TRUE the 'pin_cb' function is allowed to be used for prompting for PIN to be initialized
                                                (New creation of a PIN, PIN should be confirmed in dialog). */
	char     pin_cb_use_for_change;          /* If TRUE the 'pin_cb' function is allowed to be used for prompting for PIN to be changed
                                                (prompting for old PIN and  creation of a new PIN, new PIN should be confirmed in dialog).*/
	char     get_extension_PIN_by_card;      /* TRUE if extension PIN should be get by card operation (if supported) this needs some time */
#if 0
    /* HRS: Hallo Thomas, Du hast die folgende Variable vor Deinem Urlaub aus der SC_DATA Struktur entfernt.
            Ich bin mir nicht sicher, ob das Absicht war, oder nur ein "Unfall"... kannst Du Dir das nochmal
            anschauen, wenn Du wieder da bist? */
	char     verify_PIN_during_open; /* TRUE if PIN must be verified during open, 
	                                    FALSE if you want to avoid SC access during open */
#endif
};
enum { DEL_UNKNOWN = 0, DEL_WITH_PIN = 1, DEL_WITHOUT_PIN = 2, DEL_WITH_PUK = 4, DEL_IMPOSSIBLE = 8 };
enum { SCT_UNKNOWN = 0, SCT_HOLD_OPEN = 1, SCT_CLOSE_AFTER_EACH_CALL = 2 };
enum { PIN_UNKNOWN = 0, PIN_NORMAL_PIN = 1, PIN_NULLPIN = 2, PIN_USE_EXISTING_PIN = 4, LOGIN_WITHOUT_PIN = 8, PIN_TRANSPORTPIN = 16 };
enum { SUP_UNKNOWN = 0, SUP_YES = 1, SUP_NO = 2 };
enum { DECR_UNKNOWN = 0, DECR_YES = 1, DECR_NO = 2, DECR_RESTRICTED = 3, DECR_RESTRICTION_UNKNOWN = 4 };
enum { SIGPAD_ALL = 0, SIGPAD_PKCS1 = 1, SIGPAD_ISO9796_2 = 2};

#define NEED_SC_TO_GET_SC_DATA 0x7f

/* results of *get_SC_DATA */
#define SC_DATA_PSE_ON_CARD 0
#define SC_DATA_CARD_EMPTY 1
#define SC_DATA_CARD_STATE_UNKNOWN 2

typedef enum {
        ERR_in_psetest = -1,
        SWpse = 0, 
        SCpse = 1 
} PSELocation;


typedef struct PSE_Info PSE_Info;

#ifdef NEW_PSE_STRUCT
typedef enum PSEFlushMode {
    PSEfm_atOnce,
    PSEfm_onClose
} PSEFlushMode;
#endif

typedef enum PSEtype {
    PSEt_error = -1,
    PSEt_not_exist = 0,
    PSEt_directory,
    PSEt_file,
    PSEt_multiple
} PSEtype;


struct PSE_Info {
	char    *pse_name;
	char    *sw_pin;
	char    *sc_pin;
        PSEToc  *toc;
        PSEToc  *sc_toc;
	SC_DATA *sc_data;
#ifdef NEW_PSE_STRUCT
	PSEFlushMode flushMode;
	PSEtype	pse_type;
	int	mpse_sel;
#endif
	char	*file_name;
};

struct PSE_Sel {
        char    *object;         /* object name                     */
        ObjId   *object_type;    /* object type                     */
        void    *info;
};


/*
 *      Table of Contents of PSE
 */

typedef SEQUENCE_OF(OctetString) SEQUENCE_OF_OctetString;

#ifdef NEW_PSE_STRUCT
typedef struct PSE_Objects PSEObj;
typedef SET_OF(PSEObj) SET_OF_PSEObj;
typedef PSEToc PSECont;
typedef PSEToc EncPSECont;
typedef PSEToc SigPSECont;
typedef PSEToc CmpPSECont;
typedef PSEToc PSEFile;

typedef struct MPSEFileEntry {
    char *label;
    OctetString *psef;
} MPSEFileEntry;

typedef SEQUENCE_OF(MPSEFileEntry) SEQ_OF_MPSEFileEntry;

typedef struct MPSEFile {
    int version;
    SEQ_OF_MPSEFileEntry *pses;
} MPSEFile;

/*typedef SEQUENCE_OF_OctetString MPSEFile;*/

typedef enum PSEObjState {
    PSEObj_absent = 0,
    PSEObj_normal,
    PSEObj_isEncrypted,
    PSEObj_isKey
} PSEObjState;

typedef struct PSEKeyStruct {
    int		 keyId;
    AlgId	*algorithm;	/* OPTIONAL: NULL if absent */
    int		 keyLength;	/* OPTIONAL: 0 if absent */
    OctetString *cont;
} PSEKeyStruct;

typedef struct PSEObjValue {
    PSEObjState		 state;
    PSEKeyStruct	*keyStruct;
    OctetString		*obj;
} PSEObjValue;

typedef enum PSEWriteMode {
    PSEwm_noEncrypt = 0,
    PSEwm_encryptAll,
    PSEwm_encryptSome
} PSEWriteMode;

typedef enum PSECompressionMode {
    PSEcm_compressed = -1, /* if encrypted & compressed */
			   /* => method not available yet */
    PSEcm_noCompress = 0,
    PSEcm_zlib09
} PSECompressionMode;    

typedef struct PSEExt {
    /* internal management */
    PSEWriteMode	 writeMode;
    PSECompressionMode	 compressionMode; /* used in version 3 */
    Boolean		 dirty;
    /* field of PSEFile structure */
    int			 version;	/* initial version: 1 */
    OctetString		*encryptedPin;
    AlgId		*encAlg;
    AlgId		*micAlg;
    OctetString		*micOrEnc;
    OctetString		*compressed;
    char		*cardId;
    /* fields of PSECont structure */
    char		*caPath;
    OctetString		*extPin;
    char		*extPath;
    /* new 10.9.97 */
    int			 fileSize;
    int			 fileSize_avail;
} PSEExt;
#endif

struct PSE_Toc {
        char                    *owner;
        UTCTime                 *create;
        UTCTime                 *update;
        unsigned int            status;
        struct PSE_Objects      *obj;
#ifdef NEW_PSE_STRUCT
        PSEExt			*ext;
        SET_OF_PSEObj		*objset;
#endif
};

struct PSE_Objects {
        char                    *name;
        UTCTime                 *create;
        UTCTime                 *update;
        int                     noOctets;
        unsigned int            status;
        struct PSE_Objects      *next;
#ifdef NEW_PSE_STRUCT
        ObjId			*objType;
        PSEObjValue		*value;
#endif
};

struct PSE_Object {
        ObjId         *objectType;
        OctetString   *objectValue;
};



typedef enum {
        ERR_in_pseconfig = -1,
        NOT_ON_SC, 
        PSE_ON_SC, 
        FILE_ON_SC, 
        KEY_ON_SC
} PSEConfig;

PSEConfig sec_pseconfig();



enum {PSE_FLUSH, PSE_IS_PSEFILE, PSE_GET_ENCALG, PSE_SET_ENCALG, PSE_CARDCOMMAND, PSE_SCTCOMMAND, PSE_SET_SCT_MODE, PSE_GET_SCT_MODE, PSE_GINA_WRITE_PROFILE, PSE_GINA_READ_PROFILE, PSE_RELOAD_EXTENSION};

typedef struct {
	int			dadin;
	int			sadin;
	OctetString cmd;
	int			ret;
	int			dadout;
	int			sadout;
	OctetString resp;
} SCT_COMMAND;

/*-----------------------------------------------------------------------*/
/*    K e y ' s   and   S i g n a t u r e                                */
/*-----------------------------------------------------------------------*/



struct Key {
        KeyInfo  *key;
        PSESel   *pse_sel;
        AlgId    *alg;
        char	 *add_object;
        ObjId	 *add_object_type;
        int	  key_size;
        KeyInfo  *private_key;

};

#define DLL_SCT "SmartCardReader plugin"
#define DLL_SC  "SmartCard plugin"
#define DLL_SECUDE "security library"
#define DLL_ALGS "Algorithm plugin"
#define DLL_DEVICE "PSE Device plugin"

#ifdef WIN32
#define SECUDE_PRODUCT_INFO   "_secude_product_info@20"
#else
#define SECUDE_PRODUCT_INFO   "secude_product_info"
#endif
typedef RC      ( SEC_API_CALLING_CONV SECUDE_PRODUCT_INFO_T )    SEC_PROTOTYPE_5( char **  , name, char ** , type, Boolean * , debug, char **  , info, char ** , copyr );

extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_sc_plugins[];
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_sct_plugins[];
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_algs_plugins[];
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_psedevice_plugins[];
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_plugins[];

#define PLUGIN_PCSM_GEN "pcsmgen"
#ifdef WIN32
#define PLUGIN_ALGS PLUGIN_PCSM_GEN ,
#else
#define PLUGIN_ALGS
#endif
#define PLUGIN_DEVICE "crisecsc", "pcsm",
#define PLUGIN_SC "crflx",  "tcos", "cardosm2", "cardosm3", "gpk4000", "sse", "p11sc",
#define PLUGIN_SCT  "esnt4sct", "es95sct", "ict800std",  "snsct", "desko", "eltron", "gcr400", "secpcsc", "rsr3", "rsrp", "p11sct",
#define PLUGIN_ALL "$SECUDE_LDAP_LIB", "secude", PLUGIN_ALGS PLUGIN_DEVICE PLUGIN_SC PLUGIN_SCT

/*
 * Program Usage
 */
#define		MAX_SHORT_HELP_LINES	15
#define		MAX_LONG_HELP_LINES	100
#define 	SHORT_HELP 		0
#define 	LONG_HELP 		1
typedef struct {
	char	*program;
	char	*purpose;
	char	*options;
	char	*short_help[MAX_SHORT_HELP_LINES];
	char	*long_help[MAX_LONG_HELP_LINES];
} ProgramUsage;



/*
 *  sec_asn1_length_encoding controls the ASN.1 length encoding of the 
 *  e_*() functions. DEFINITE or INDEFINITE encoding can be chosen.
 *  For the sake of distinguished ASN.1 encoding either of the two 
 *  methods must be agreed and fixed between all participants of the
 *  security infrastructure. X.509 says DEFINITE shall be used for
 *  DER encoding. sec_asn1_length_encoding is defined in sec_init.c
 *  and set to DEFINITE by default.
 *
 *  Don't change this parameter unless you are sure what you are doing, 
 *  otherwise the verification of certificates could yield some surprises.
 */ 

#define INDEFINITE 1
#define DEFINITE   2

#define ONEKEYPAIRONLY   1
#define HAS_EXT   2
#define FINGERPRINT_ALG  md5		/* SECUDE fingerprint */
#define MSBITINBYTE 0x80




/*
 * Force exit from process
 * Only for utilities
 */
#define AUX_PRINT_USAGE_EXIT(usage, help)	{ aux_print_usage(&usage, help); return(-1); }


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#ifdef SCA
#include "secsc.h"
#endif
#include "sec_p.h"
#include "isode_p.h"

#endif /* _SECURE_ */

