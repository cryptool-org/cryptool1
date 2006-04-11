/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/secure.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*-----------------------------------------------------------------------*/
/* INCLUDE FILE  secure.h                                                */
/* Definition of structures and types for the basic security functions   */
/*-----------------------------------------------------------------------*/

#ifndef _SECURE_
#define _SECURE_


#include <secude/arithmet.h>


#include <secude/filename.h>

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

/***** Typedef SET_OF_OctetString *****/
/** @ingroup header_secure
  */
typedef SET_OF(OctetString)     SET_OF_OctetString;
/***** Typedef SET_OF_ObjId *****/
/** @ingroup header_secure
  */
typedef SET_OF(ObjId)           SET_OF_ObjId;
/***** Typedef SEQUENCE_OF_ObjId *****/
/** @ingroup header_secure
  */
typedef SEQUENCE_OF(ObjId)      SEQUENCE_OF_ObjId;
/***** Typedef Key *****/
/** @ingroup header_secure
  */
typedef struct Key              Key;
/***** Typedef PSESel *****/
/** @ingroup header_secure
  */
typedef struct PSE_Sel          PSESel;
/***** Typedef PSEToc *****/
/** @ingroup header_secure
  */
typedef struct PSE_Toc          PSEToc;
/***** Typedef PSEObject *****/
/** @ingroup header_secure
  */
typedef struct PSE_Object       PSEObject;
/***** Typedef PSEObjects *****/
/** @ingroup header_secure
  */
typedef struct PSE_Objects      PSEObjects;

/*-----------------------------------------------------------------------*/
/*    P S E                                                              */
/*-----------------------------------------------------------------------*/

/***** Enum PINType *****/
/** @ingroup header_secure
  */
typedef enum { Extension_PIN, SignatureKey_PIN, EncryptionKey_PIN, AuthenticationKey_PIN, Card_PIN, Slot1_PIN, Slot2_PIN, Slot3_PIN, Slot4_PIN, Card_PUK } PINType;
typedef enum { CB_TYPE_VERIFY, CB_TYPE_SET, CB_TYPE_CHANGE, CB_TYPE_SCT_VERIFY, CB_TYPE_SCT_SET, CB_TYPE_SCT_CHANGE, CB_TYPE_UNBLOCK, CB_TYPE_SCT_UNBLOCK, 
   CB_TYPE_SCT_VERIFY_DONE, CB_TYPE_SCT_SET_DONE, CB_TYPE_SCT_CHANGE_DONE, CB_TYPE_SCT_UNBLOCK_DONE } CBType;
/***** Structure CB_DATA_PIN *****/
/** @ingroup header_secure
  */
typedef struct {
/** type of operation, CB_TYPE_VERIFY, CB_TYPE_SET, CB_TYPE_CHANGE */
    sec_uint4 type;         /* type of operation, CB_TYPE_VERIFY, CB_TYPE_SET, CB_TYPE_CHANGE */
                            /* CB_TYPE_SCT - types indicates that the action is started       */
                            /*   on SmartCard reader PIN pad after the callback function returned */
/** change: the new PIN */
    char      pin[65];      /* verify: the PIN to verify                                      */
                            /* set: the PIN to initialize                                     */
                            /* change: the old PIN                                            */
/** verify: the PIN to verify<BR>set: the PIN to initialize<BR>change: the old PIN */
    char      newpin[65];   /* change: the new PIN                                            */
/** TRUE if there was an unsuccessful verification/initialization before */
    char      retry;        /* TRUE if there was an unsuccessful verification/initialization before */
/** the number of remaining  presentations of bad PIN, -1: not supported */
    int       counter;      /* the number of remaining  presentations of bad PIN, -1: not supported */
/** identification for the PIN object */
    PINType   pintype;      /* identification for the PIN object                              */
/** identification for the PIN object as printable string */
    char *    pinname;      /* identification for the PIN object as printable string          */

/** the minimum / maximum number of digits the PIN must have */
    int       min_pin_len;      /* new in 7.4.56, should be backward compatible as it is attached to the end */
    int       max_pin_len;      /* new in 7.4.56, should be backward compatible as it is attached to the end */
    
} CB_DATA_PIN;
 
/***** Typedef SECUDE_CB_T *****/
/** @ingroup header_secure
  */
typedef RC       SEC_API_CALLING_CONV SECUDE_CB_T     SEC_PROTOTYPE_2( void * ,client_data,void *, callback_data);

/***** Typedef SC_DATA *****/
/** @ingroup header_secure
  */
typedef struct SC_DATA SC_DATA;

/***** Structure SC_DATA *****/
/** This structure is created by #sec_get_SC_DATA and used by
  * #sec_open/#sec_create. It holds information how to open/create a SC-PSE.
  * Some element are to be changed by the application.
  *
  * <B>Typedef:</B> <TT>typedef struct SC_DATA #SC_DATA;</TT>
  *
  * <p>To access the members of this structure in a way which is portable
  * across different versions of the SECUDE SDK, an application should use
  * the <tt>aux_SC_DATA_get_xxx_param()</tt> and <tt>aux_SC_DATA_set_xxx_param()</tt>
  * functions.
  * 
  * @ingroup header_secure
  */
struct SC_DATA {
/** Tells if a PIN is needed for opening a PSE.<BR>
  * <B>TRUE:</B> PIN needed for PSE access.<BR>
  * <B>FALSE:</B> PSE is not PIN protected.
  */
	int		 need_pin;                      /* 
	                                         * Tells if a PIN is needed to open the PSE (TRUE/FALSE)
	                                         */
/** <B>TRUE:</B> SCT has a PIN-PAD and the PIN has to be entered there when opening a PSE.<BR>
  * <B>FALSE:</B> The application has to prompt for the PIN and to give it as parameter
  * in the open call.
  */
	int		 enter_pin_on_SCT;              /* 
	                                         * Tells if the PIN has to be entered on the SCT (TRUE/FALSE)
	                                         */
/** <B>0:</B> SC already inserted.<BR>
  * <B>1:</B> No SC inserted, SC not activated. SC will be requested by open/create.<BR>
  * <B>2:</B> SC inserted, but could not be activated.
  * Probably it was inserted incorrectly.
  */
	int		 need_SC;                       /* 
	                                         * Tells if the Card has to be inserted 
	                                         * 0: SC already inserted
	                                         * 1: No SC inserted, SC not activated
	                                         * 2: SC inserted, but could not be activated. Probably it was inserted incorrectly
	                                         */
/** The SCT identifier. */
    int  	 sct_id;                        /* 
	                                         * The SCT identifier
	                                         */
/** The time in seconds the SCT waits until the SC is inserted. If SC_timer
  * is set to 0, no time-out is specified. Default value is 20. Could be
  * changed by the application before the open/create call.
  */
	int		 SC_timer;                      /* 
	                                         * The time in seconds the SCT waits until the SC is inserted. If SC_timer
	                                         * is set to 0, no time-out is specified. Default value is 20. Could be
	                                         * changed by the application before the open/create call
	                                         */
/** The PUK or NULL pointer (no PUK).<BR>
  * The application should set this element for using
  * #sec_create, #sec_delete_PSE or #sec_unblock_pin.
  * If puk_counter is set to -1 by #sec_get_SC_DATA
  * PUK handling is not supported.
  */
	char	*puk;                           /* 
	                                         * The PUK or NULL pointer (no PUK).
    					                     * The application should set this element for using
    					                     * sec_create, sec_delete_PSE or sec_unblock_pin.
    					                     * If puk_counter is set to -1 by sec_get_SC_DATA
    					                     * PUK handling is not supported. 
	                                         */
/** On most cards there is a counter for false attempt to enter the PIN.<BR>
  * If there is a PSE on Card #sec_get_SC_DATA
  * sets this element to the number of remaining attempts to enter the correct PIN.<BR>
  * If there is no PSE on Card #sec_get_SC_DATA
  * sets this element to the highest supported value of this counter and the application
  * should change it to the desired value when calling
  * #sec_create<BR>
  * If not supported the element is set to -1.
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
/** On most cards there is a counter for false attempt to enter the PUK.<BR>
  * If there is a PSE on Card #sec_get_SC_DATA
  * sets this element to the number of remaining attempts to enter the correct PUK.<BR>
  * If there is no PSE on Card #sec_get_SC_DATA
  * sets this element to the highest supported value of this counter and the application
  * should change it to the desired value when calling
  * #sec_create<BR>
  * If not supported the element is set to -1 or 0 (PUK supported but no PSE on card).
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
/** Internal information of SECURE interface to handle SC-PSEs. */
	void	*func;                          /* 
	                                         * Internal information of SECURE interface to handle SC-PSEs 
	                                         */
/** Information about the SmartCard access library. */
	char	*product_info;                  /* 
	                                         * Information about the SmartCard access library 
	                                         */
/** Information about SCT (NULLpointer : A cryptographic modul is accessed not a SCT). */
	char	*sct;                           /* 
	                                         * Information about SCT (NULLpointer : A cryptographic modul is accessed not a SCT) 
	                                         */
/** Information about SC . */
	char	*sc;                            /* 
	                                         * Information about SC 
	                                         */
/** Internal information of plugin interface to handle SC-PSEs. */
	void	*hdl;                           /* 
	                                         * Internal information of plugin interface to handle SC-PSEs 
	                                         */
/** SmartCard serial number (if available). */
	char	*serial;                        /* 
	                                         * SmartCard serial number (if available) 
	                                         */
/** <B>TRUE:</B>
  * SCT has a PIN-PAD and the PIN has to be entered there when creating a PSE.<BR>
  * <B>FALSE:</B> The application has to prompt for the PIN and to give it as parameter
  * in the create call.
  */
	int		 enter_pin_on_SCT_on_install;   /* 
	                                         * TRUE if SCT has a PIN-PAD and the PIN has to be entered there when creating a PSE 
	                                         */
/** <B>TRUE:</B>
  * SCT has a PIN-PAD and the PIN has to be entered there when change the PIN.<BR>
  * <B>FALSE:</B> The application has to prompt for the PIN and to give it as parameter
  * in the chpin call.
  */
	int		 enter_pin_on_SCT_on_change;    /* 
	                                         * TRUE ifSCT has a PIN-PAD and the PIN has to be entered there when change the PIN  
	                                         */
/** Information about algorithms supported by the SmartCard / Crypto device.<BR>
  * This field contains a sequence of integers using this syntax: <BR>
  * [<I>alg_type</I> [<I>begin_of_scope</I> <I>end_of_scope</I> <I>step</I>]* -1 ] -1 <BR>
  * where <I>alg_type</I> is one of the integers defined by the enumeration
  * #AlgEnc like <I>RSA</I> and each block
  * of the 3 values <I>begin_of_scope</I>, <I>end_of_scope</I> and <I>step</I>
  * defines ascope of valid key sizes.
  * beginning with<BR>
  * Examples for RSA with key size 512, 768, 1024 and 2048:<BR>
  * <UL>
  * <LI>EXAMPLE: [RSA, [512, 1024, 256,] [2048, 2048, 1,]-1,]-1 
  * <LI>EXAMPLE: [RSA, [512, 512, 1,] [768, 768, 1,] [1024, 1024, 1, ] [2048, 2048, 1, ]-1,]-1 
  * </UL>
  * Example for DSA and RSA with key size 512 and  1024:<BR>
  * <UL>
  * <LI>EXAMPLE: [RSA, [512, 1024, 512,] -1,][DSA, [512, 1024, 512,] -1,]-1 
  * </UL>
  * NULL Pointer mean's that no information is available.
  */
	int		*supported_algs_and_sizes; 
                                			/* This integer array has the following format:
                                      			   [alg_type [begin_of_scope end_of_scope step]* -1 ]* -1     
                                			   EXAMPLE: RSA, 512, 1024, 512,-1,-1  
                                			   EXAMPLE: RSA, 512, 512, 1, 1024, 1024, 1,-1,-1  
                                			   NULL Pointer mean's that no information is available */
/** Information about PIN protection.<BR>
  * This field specifies if PIN has to be entered to delete a PSE on SC: <BR>
  * <UL>
  * <LI> Value as set by #sec_get_SC_DATA (PSE existing):
  * <UL>
  * <LI> (delete_flag == DEL_UNKNOWN) : Don't know if PIN is needed for deleting a SC PSE.
  * <LI> (delete_flag & DEL_WITH_PIN) : Need PIN to delete PSE
  * <LI> (delete_flag & DEL_WITH_PUK) : Need PUK to delete PSE
  * <LI> (delete_flag & DEL_WITHOUT_PIN) PSE could be deleted without PIN check
  * </UL>
  * <LI> Value as set by #sec_get_SC_DATA (PSE not existing):
  * <UL>
  * <LI> (delete_flag == DEL_UNKNOWN) : Don't know if PIN is needed for deleting a SC PSE.
  * <LI> (delete_flag & DEL_WITH_PIN) : It's possible to create a
  * PSE that could only be deleted after PIN check
  * <LI> (delete_flag & DEL_WITH_PUK) : It's possible to create a
  * PSE that could only be deleted after PUK check
  * <LI> (delete_flag & DEL_WITHOUT_PIN) It's possible to create a
  * PSE that could be deleted without PIN check
  * </UL>
  * <LI> Value as used by #sec_create:
  * <UL>
  * <LI> (delete_flag == DEL_WITH_PIN) : A PSE is created that could
  * only be deleted with PIN check
  * <LI> (delete_flag == DEL_WITH_PUK) : A PSE is created that could
  * only be deleted with PUK check
  * <LI> (delete_flag == DEL_WITHOUT_PIN) : A PSE is created that could
  * be deleted without PIN check
  * <LI> OTHERWISE : Unspecified if PIN is needed for deleting the PSE
  * </UL>
  * </UL>
  */
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
/** If the application sets this field to TRUE the SmartCard driver is
  * allowed to wait with writing the SC files until the #sec_close call.<BR>
  * This is faster if there are more than one write operations, but you could
  * have inconsistencies if the SC access is not ended normally
  */
	char	 write_later;
			                                 /* if TRUE it's allowed to wait with writing the SC file until sec_close() call */
/** Name of SC plugin. */
	char	*plugin_name;                    /* Name of SC plugin */
/** Name of SmartCard. */
	char	*card_name;                      /* Name of SmartCard */
/** Eject SmartCard when closing PSE. */
	char	 eject;                          /* eject Card on sec_close */
/** Not supported any more. */
	char	 recreate_ext;                   /* Not supported any more */
/** The application could set this
  * value to define the number of seconds to wait for a SCT connection if it is busy.
  */
	int      SCT_timer;                      /* seconds to wait for getting a connection to the SCT */
/** The application could set this
  * value to define how many test are made per second when waiting for a SCT connection.
  * On UNIX there is only one test per second.
  */
	int      SCT_timer_tps;                  /* tests per second */
/** supported RSA padding methods for signature(SIGPAD_ALL,SIGPAD_PKCS1,SIGPAD_ISO9796_2). */
	char	 pkcs1_signature_only;           /* supported RSA padding methods for signature(SIGPAD_ALL,SIGPAD_PKCS1,SIGPAD_ISO9796_2)*/
/** Information about SCT connection.<BR>
  * This field specifies if the connection to the SCT should be open until the PSE is closed: <BR>
  * <UL>
  * <LI> Value as set by #sec_get_SC_DATA defines the supported SCT modes:
  * <UL>
  * <LI> (sct_mode == SCT_UNKNOWN) : Don't know supported modes.
  * <LI> (sct_mode & SCT_HOLD_OPEN) : Connection is close when PSE is closed
  * <LI> (sct_mode & SCT_CLOSE_AFTER_EACH_CALL) Connection is close after each call
  * </UL>
  * <LI> Value as used by #sec_open:
  * <UL>
  * <LI> (sct_mode == SCT_HOLD_OPEN) : Connection is close when PSE is closed
  * <LI> (sct_mode == SCT_CLOSE_AFTER_EACH_CALL) Connection is closed after each call
  * <LI> (other values) : Mode undefined.
  * </UL>
  * </UL>
  */
	char     sct_mode;                       /* This field specifies if the connection to the SCT should be open until the PSE is closed 
                                			  After get_SC_DATA:
                                				(sct_mode == SCT_UNKNOWN) Don't know supported modes.
                                				(sct_mode & SCT_HOLD_OPEN) Supported: Connection is close when PSE is closed
                                				(sct_mode & SCT_CLOSE_AFTER_EACH_CALL) Supported: Connection is close after each call
                                											 
                                		      When opening a PSE
                                				(sct_mode == SCT_HOLD_OPEN) Connection is close when PSE is closed
                                				(sct_mode == SCT_CLOSE_AFTER_EACH_CALL) Connection is close after each call */
/** The minimum PIN length (0:unknown). */
	int      min_pin_len;                    /* minimal pin size to be used (0 if unknown)*/
/** The maximum PIN length (0:unknown). */
	int      max_pin_len;                    /* minimal pin size to be used (0 if unknown)*/
/** Information about PIN handling.<BR>
  * <UL>
  * <LI> Value as set by #sec_get_SC_DATA:
  * <UL>
  * <LI> (need_pin_change == PIN_UNKNOWN) : Don't know supported modes.
  * <LI> (need_pin_change & PIN_NORMAL_PIN) : No transport PIN
  * <LI> (need_pin_change & PIN_NULLPIN) : NULL-transport PIN is active: PIN has to be changed (with empty old PIN) before Card could be used
  * <LI> (need_pin_change & PIN_TRANSPORTPIN) : Transport PIN is active: PIN has to be changed before Card could be used
  * <LI> (need_pin_change & PIN_USE_EXISTING_PIN) : Existing PIN has to be used when creating a PSE
  * <LI> (need_pin_change & LOGIN_WITHOUT_PIN) : Login without PIN is possible to see public objects
  * </UL>
  * </UL>
  */
	char     need_pin_change;                /* PIN_NULLPIN : NULL-transport PIN is active: PIN has to be changed (with empty old PIN) before Card could be used 
	                                            PIN_TRANSPORTPIN: Transport PIN is active: PIN has to be changed before Card could be used
	                                            PIN_NORMAL_PIN : No transport PIN
	                                            PIN_USE_EXISTING_PIN : Existing PIN has to be used when creating a PSE
	                                            LOGIN_WITHOUT_PIN : Login without PIN is possible to see public objects 
	                                          */
/** Information about PIN unblocking.<BR>
  * <UL>
  * <LI> Value as set by #sec_get_SC_DATA:
  * <UL>
  * <LI> (unblock == SUP_UNKNOWN) : Don't know supported modes.
  * <LI> (unblock & SUP_YES) : Supported
  * <LI> (unblock & SUP_NO) : Not supported
  * </UL>
  * </UL>
  */
	char     unblock;                        /* SUP_UNKNOWN, SUP_YES, SUP_NO */
/** Information about PIN change.<BR>
  * <UL>
  * <LI> Value as set by #sec_get_SC_DATA:
  * <UL>
  * <LI> (unblock == SUP_UNKNOWN) : Don't know supported modes.
  * <LI> (unblock & SUP_YES) : Supported
  * <LI> (unblock & SUP_NO) : Not supported
  * </UL>
  * </UL>
  */
	char     pin_change;                     /* SUP_UNKNOWN, SUP_YES, SUP_NO */
/** Information about decryption.<BR>
  * <UL>
  * <LI> Value as set by #sec_get_SC_DATA:
  * <UL>
  * <LI> (decrypt == DECR_UNKNOWN) : Don't know supported modes.
  * <LI> (decrypt == DECR_YES) : Decryption supported.
  * <LI> (decrypt == DECR_NO) : Decryption not supported.
  * <LI> (decrypt == DECR_RESTRICTED) : Decryption restricted to known clear text size (see next element).
  * <LI> (decrypt == DECR_RESTRICTION_UNKNOWN) : Decryption restricted to unknown clear text size.
  * </UL>
  * </UL>
  */
	char     decrypt;                        /* (decrypt == DECR_UNKNOWN) : Don't know supported modes.                                           
	                                            (decrypt == DECR_YES) : Decryption supported.                                                     
	                                            (decrypt == DECR_NO) : Decryption not supported.                                                  
	                                            (decrypt == DECR_RESTRICTED) : Decryption restricted to known clear text size (see next element). 
	                                            (decrypt == DECR_RESTRICTION_UNKNOWN) : Decryption restricted to unknown clear text size.         
	                                          */
/** Bits of clear text which are allowed for decryption. */
	int      decrypt_restr;                  /* decrypt restriction bits, see element 'decrypt' */
/** Unused */
	char   **mPSEs;                          /* unused */
/** Should be set to TRUE if objects should searched in the extension first.
  * This allows faster access.
  */
	char     extension_objects_first;        /* TRUE if an objects should searched in the extension first */
/** It may happen with different SmartCards/Drivers that it's neccesary to verify another PIN.
  * For example it's not always possible to store the PIN for the PSE extension on the card.
  * So this element should be set to a callback function which prompts for a PIN. This function
  * will be called by the SC driver when neccesary. The first parameter is the value of 'pin_cb_data',
  * the second parameter a CB_DATA_PIN pointer to be changed by applicaton.
  */
	SECUDE_CB_T *pin_cb;                     /* callback to prompt for additional PIN to be used for verification/initialization/change */  
/** As the first argument when calling the 'pin_cb' function this value is used . */
	void    *pin_cb_data;                    /* callback data */
/** If TRUE the 'pin_cb' function is allowed to be used for prompting for PIN to be used
  * (PIN verification).
  */
	char     pin_cb_use_for_verify;          /* If TRUE the 'pin_cb' function is allowed to be used for prompting for PIN to be used
                                                (PIN verification). */
/** If TRUE the 'pin_cb' function is allowed to be used for prompting for PIN to be initialized
  * (New creation of a PIN, PIN should be confirmed in dialog).
  */
	char     pin_cb_use_for_set;             /* If TRUE the 'pin_cb' function is allowed to be used for prompting for PIN to be initialized
                                                (New creation of a PIN, PIN should be confirmed in dialog). */
/** If TRUE the 'pin_cb' function is allowed to be used for prompting for PIN to be changed
  * (prompting for old PIN and  creation of a new PIN, new PIN should be confirmed in dialog).
  */
	char     pin_cb_use_for_change;          /* If TRUE the 'pin_cb' function is allowed to be used for prompting for PIN to be changed
                                                (prompting for old PIN and  creation of a new PIN, new PIN should be confirmed in dialog).*/
/** If TRUE the SmartCard driver is allowed to store the PSE extension PIN in encrypted form.
  * This may avoid user interaction.
  */
	char     get_extension_PIN_by_card;      /* TRUE if extension PIN should be get by card operation (if supported) this needs some time */

    char     never_cache_PKRoot;             /* Should be set to true if PKRoot should not be cached in Extension or memory */
    char     pin_char_set;             		 /* allowed PIN character set, see enum PCS_.. */
    char     open_ext_without_card_pin;      /* Boolean value tells if extension could be opened without card PIN */
};
enum { DEL_UNKNOWN = 0, DEL_WITH_PIN = 1, DEL_WITHOUT_PIN = 2, DEL_WITH_PUK = 4, DEL_IMPOSSIBLE = 8 };
enum { SCT_UNKNOWN = 0, SCT_HOLD_OPEN = 1, SCT_CLOSE_AFTER_EACH_CALL = 2 };
enum { PIN_UNKNOWN = 0, PIN_NORMAL_PIN = 1, PIN_NULLPIN = 2, PIN_USE_EXISTING_PIN = 4, LOGIN_WITHOUT_PIN = 8, PIN_TRANSPORTPIN = 16 };
enum { SUP_UNKNOWN = 0, SUP_YES = 1, SUP_NO = 2 };
enum { DECR_UNKNOWN = 0, DECR_YES = 1, DECR_NO = 2, DECR_RESTRICTED = 3, DECR_RESTRICTION_UNKNOWN = 4 };
enum { SIGPAD_ALL = 0, SIGPAD_PKCS1 = 1, SIGPAD_ISO9796_2 = 2};
enum { PCS_ALL = 0, PCS_ALNUM = 1, PCS_NUM = 2};

/* the following defines are used to access the fields of SC_DATA structure;
   use the apropriate accessor function as indicated by the type in the comment */
#define PARM_SC_DATA_need_pin                       0x0001 /* Boolean, ro */
#define PARM_SC_DATA_enter_pin_on_SCT               0x0002 /* Boolean, ro */
#define PARM_SC_DATA_need_SC                        0x0003 /* int, ro */
#define PARM_SC_DATA_sct_id                         0x0004 /* int */
#define PARM_SC_DATA_SC_timer                       0x0005 /* int */
#define PARM_SC_DATA_puk                            0x0006 /* String */
#define PARM_SC_DATA_pin_counter                    0x0007 /* int */
#define PARM_SC_DATA_puk_counter                    0x0008 /* int */
#define PARM_SC_DATA_product_info                   0x0009 /* String */
#define PARM_SC_DATA_sct                            0x000a /* String */
#define PARM_SC_DATA_sc                             0x000b /* String */
#define PARM_SC_DATA_serial                         0x000c /* String */
#define PARM_SC_DATA_enter_pin_on_SCT_on_install    0x000d /* Boolean */
#define PARM_SC_DATA_enter_pin_on_SCT_on_change     0x000e /* Boolean */
#define PARM_SC_DATA_supported_algs_and_sizes       0x000f /* int-array */
/*#define PARM_SC_DATA_supported_algs_and_sizes_CONT  0x0010 / * array of SIZE * int */
#define PARM_SC_DATA_delete_flag                    0x0011 /* int */
#define PARM_SC_DATA_write_later                    0x0012 /* Boolean */
#define PARM_SC_DATA_plugin_name                    0x0013 /* String, ro */
#define PARM_SC_DATA_card_name                      0x0014 /* String, ro */
#define PARM_SC_DATA_eject                          0x0015 /* Boolean */
#define PARM_SC_DATA_SCT_timer                      0x0016 /* int */
#define PARM_SC_DATA_SCT_timer_tps                  0x0017 /* int */
#define PARM_SC_DATA_pkcs1_signature_only           0x0018 /* int, ro */
#define PARM_SC_DATA_sct_mode                       0x0019 /* int */
#define PARM_SC_DATA_min_pin_len                    0x001a /* int, ro */
#define PARM_SC_DATA_max_pin_len                    0x001b /* int, ro */
#define PARM_SC_DATA_need_pin_change                0x001c /* int, ro */
#define PARM_SC_DATA_unblock                        0x001d /* int */
#define PARM_SC_DATA_pin_change                     0x001e /* int */
#define PARM_SC_DATA_decrypt                        0x001f /* int */
#define PARM_SC_DATA_decrypt_restr                  0x0020 /* int */
#define PARM_SC_DATA_extension_objects_first        0x0021 /* Boolean */
#define PARM_SC_DATA_pin_cb_with_data               0x0022 /* (SECUDE_CB_T *) plus (void *) */
#define PARM_SC_DATA_pin_cb_use_for_verify          0x0023 /* Boolean */
#define PARM_SC_DATA_pin_cb_use_for_set             0x0024 /* Boolean */
#define PARM_SC_DATA_pin_cb_use_for_change          0x0025 /* Boolean */
#define PARM_SC_DATA_get_extension_PIN_by_card      0x0026 /* Boolean */
#define PARM_SC_DATA_pin_char_set                   0x0027 /* int */
#define PARM_SC_DATA_open_ext_without_card_pin      0x0028 /* Boolean */
/* there are no constants for: func, hdl */

#define NEED_SC_TO_GET_SC_DATA 0x7f

/* results of *get_SC_DATA */
#define SC_DATA_PSE_ON_CARD 0
#define SC_DATA_CARD_EMPTY 1
#define SC_DATA_CARD_STATE_UNKNOWN 2

/***** Enum PSELocation *****/
/** @ingroup header_secure
  */
typedef enum {
        ERR_in_psetest = -1, /**< <tt>=-1</tt> */
        SWpse = 0, /**< <tt>=0</tt> */
        SCpse = 1 /**< <tt>=1</tt> */
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

/***** Structure PSE_Sel *****/
/** This structure is created by #sec_create or #sec_open. It is given to all
  * other sec_* functions to select a PSE or a PSE object. To select a PSE
  * object its name and Object Identifier must be given to the function.
  *
  * <B>Typedef:</B> <TT>typedef struct PSE_Sel #PSESel;</TT>
  *
  * @ingroup header_secure
  */
struct PSE_Sel {
/** Name of a PSE object. */
        char    *object;         /* object name                     */
/** Object Identifier. */
        ObjId   *object_type;    /* object type                     */
        void    *info;
};


/*
 *      Table of Contents of PSE
 */

/***** Typedef SEQUENCE_OF_OctetString *****/
/** @ingroup header_secure
  */
typedef SEQUENCE_OF(OctetString) SEQUENCE_OF_OctetString;

#ifdef NEW_PSE_STRUCT
/***** Typedef PSEObj *****/
/** @ingroup header_secure
  */
typedef struct PSE_Objects PSEObj;
/***** Typedef SET_OF_PSEObj *****/
/** @ingroup header_secure
  */
typedef SET_OF(PSEObj) SET_OF_PSEObj;
typedef PSEToc PSECont;
typedef PSEToc EncPSECont;
typedef PSEToc SigPSECont;
typedef PSEToc CmpPSECont;
typedef PSEToc PSEFile;

/***** Structure MPSEFileEntry *****/
/** @ingroup header_secure
  */
struct MPSEFileEntry {
    char *label;
    OctetString *psef;
};
/***** Typedef MPSEFileEntry *****/
/** @ingroup header_secure
  */
typedef struct MPSEFileEntry MPSEFileEntry;

/***** Typedef SEQ_OF_MPSEFileEntry *****/
/** @ingroup header_secure
  */
typedef SEQUENCE_OF(MPSEFileEntry) SEQ_OF_MPSEFileEntry;

/***** Structure MPSEFile *****/
/** @ingroup header_secure
  */
struct MPSEFile {
    int version;
    SEQ_OF_MPSEFileEntry *pses;
};
/***** Typedef MPSEFile *****/
/** @ingroup header_secure
  */
typedef struct MPSEFile MPSEFile;

/*typedef SEQUENCE_OF_OctetString MPSEFile;*/

/***** Enum PSEObjState *****/
/** @ingroup header_secure
  */
enum PSEObjState {
    PSEObj_absent = 0,  /**< <tt>=0</tt> */
    PSEObj_normal,
    PSEObj_isEncrypted,
    PSEObj_isKey
};
#ifndef DOXYGEN_EXCLUDE
typedef enum PSEObjState PSEObjState;
#endif

/***** Structure PSEKeyStruct *****/
/** @ingroup header_secure
  */
struct PSEKeyStruct {
    int		 keyId;
    AlgId	*algorithm;	/* OPTIONAL: NULL if absent */
    int		 keyLength;	/* OPTIONAL: 0 if absent */
    OctetString *cont;
};
/***** Typedef PSEKeyStruct *****/
/** @ingroup header_secure
  */
typedef struct PSEKeyStruct PSEKeyStruct;

/***** Structure PSEObjValue *****/
/** @ingroup header_secure
  */
struct PSEObjValue {
    PSEObjState		 state;
    PSEKeyStruct	*keyStruct;
    OctetString		*obj;
};
/***** Typedef PSEObjValue *****/
/** @ingroup header_secure
  */
typedef struct PSEObjValue PSEObjValue;

/***** Enum PSEWriteMode *****/
/** @ingroup header_secure
  */
enum PSEWriteMode {
    PSEwm_noEncrypt = 0,  /**< <tt>=0</tt> */
    PSEwm_encryptAll,
    PSEwm_encryptSome
};
#ifndef DOXYGEN_EXCLUDE
typedef enum PSEWriteMode PSEWriteMode;
#endif

/***** Enum PSECompressionMode *****/
/** @ingroup header_secure
  */
enum PSECompressionMode {
    PSEcm_compressed = -1, /**< <tt>=-1</tt> if encrypted \& compressed */
			   /* => method not available yet */
    PSEcm_noCompress = 0,  /**< <tt>=0</tt> */
    PSEcm_zlib09
};
#ifndef DOXYGEN_EXCLUDE
typedef enum PSECompressionMode PSECompressionMode;
#endif 

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

/***** Structure PSE_Toc *****/
/** This structure is only use internally to hold general information about the
  * PSE. Toc stands for <I>table of contents</I>.
  *
  * <B>Typedef:</B> <TT>typedef struct PSE_Toc #PSEToc;</TT>
  * 
  * @ingroup header_secure
  */
struct PSE_Toc {
/** owner of PSE */
        char                    *owner;
/** time of creation */
        UTCTime                 *create;
/** time of last update */
        UTCTime                 *update;
/** optional status information */
        unsigned int            status;
/** information of objects in PSE */
        struct PSE_Objects      *obj;
#ifdef NEW_PSE_STRUCT
        PSEExt			*ext;
        SET_OF_PSEObj		*objset;
#endif
};

/***** Structure PSE_Objects *****/
/** Structure representing PSE objects.
  * <B>Typedef:</B> <TT>typedef struct PSE_Objects #PSEObjects;</TT> 
  * @ingroup header_secure
  */
struct PSE_Objects {
/** name of PSE Object */
        char                    *name;
/** time of creation of object */
        UTCTime                 *create;
/** time of last update of object */
        UTCTime                 *update;
/** size of object in bytes */
        int                     noOctets;
/** optional status information */
        unsigned int            status;
/** linkage */
        struct PSE_Objects      *next;
#ifdef NEW_PSE_STRUCT
        ObjId			*objType;
        PSEObjValue		*value;
#endif
};

/***** Structure PSE_Object *****/
/** Structure representing a PSE object.
  * <B>Typedef:</B> <TT>typedef struct PSE_Object #PSEObject;</TT> 
  * @ingroup header_secure
  */
struct PSE_Object {
/** type of contained object */
        ObjId         *objectType;
/** DER code of contained object */
        OctetString   *objectValue;
};



/***** Enum PSEConfig *****/
/** @ingroup header_secure
  */
typedef enum {
        ERR_in_pseconfig = -1,  /**< <tt>=-1</tt> */
        NOT_ON_SC, 
        PSE_ON_SC, 
        FILE_ON_SC, 
        KEY_ON_SC
} PSEConfig;

PSEConfig sec_pseconfig();



enum {PSE_FLUSH, PSE_IS_PSEFILE, PSE_GET_ENCALG, PSE_SET_ENCALG, 
	PSE_CARDCOMMAND, PSE_SCTCOMMAND, 
	PSE_SET_SCT_MODE, PSE_GET_SCT_MODE, 
	PSE_GINA_WRITE_PROFILE, PSE_GINA_READ_PROFILE, 
	PSE_RELOAD_EXTENSION, 
	CARD_LOGIN, CARD_LOGOUT, 
	P11_SWITCH_PSE};

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



/***** Structure Key *****/
/** Structure representing a key object.
  * <B>Typedef:</B> <TT>typedef struct Key #Key;</TT>
  * @ingroup header_secure
  */
struct Key {
        KeyInfo  *key;
        PSESel   *pse_sel;
        AlgId    *alg;
/** If a DSA key with common parameters should be generated/used
  * this and the following element must specify the PSE object
  * for the common parameters.
  */
        char	 *add_object;
        ObjId	 *add_object_type;
/** This element tells #sec_gen_key the size of the keys to generate */
        int	  key_size;
/** In case of RSA/DSA #sec_gen_key stores the private Key in this
  * element if pse_sel is NULL. This element is not accessed by
  * other functions, it has to be freed by application separately.
  */
        KeyInfo  *private_key;

};

#define DLL_SCT "SmartCardReader plugin"
#define DLL_SC  "SmartCard plugin"
#define DLL_SECUDE "security library"
#define DLL_ALGS "Algorithm plugin"
#define DLL_DEVICE "PSE Device plugin"

#ifdef WIN32
#define SECUDE_PRODUCT_INFO_STATIC   "_secude_product_info_static@20"
#else
#define SECUDE_PRODUCT_INFO_STATIC   "secude_product_info_static"
#endif

typedef RC      SEC_API_CALLING_CONV SECUDE_PRODUCT_INFO_T    SEC_PROTOTYPE_5( char **  , name, char ** , type, Boolean * , debug, char **  , info, char ** , copyr );


extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_sc_plugins[];
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_sct_plugins[];
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_algs_plugins[];
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_psedevice_plugins[];
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  secude_plugins[];

#define PLUGIN_PCSM_GEN "pcsmgen"
#ifdef WIN32
#define PLUGIN_ALGS 
#else
#define PLUGIN_ALGS
#endif
#define PLUGIN_DEVICE "crisecsc", 
#define PLUGIN_SC "tcos", "sse", "p11sc",
#define PLUGIN_SCT  "kaanprof", "orgamct", "esnt4sct", "es95sct", "snsct", "desko", "eltron", "secpcsc", "rsr3", "rsrp", "p11sct",
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
#include <secude/secsc.h>
#endif
#define SECUDE_SECURE_INCLUDE 1
#include <secude/sec_p.h>
#undef SECUDE_SECURE_INCLUDE
#include <secude/isode.h>

#endif /* _SECURE_ */

