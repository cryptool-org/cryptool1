/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/secsc.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*-----------------------------------------------------------------------*/
/* INCLUDE FILE  secsc.h                                                 */
/* Definition of structures and types for the 				 */
/* SEC-IF - SCA-IF interface module (secsc).				 */
/*-----------------------------------------------------------------------*/

#ifndef _SECSC_
#define _SECSC_

#include <secude/secure.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/*
 *
 *   secure.h defines:
 *          AlgId               (typedef struct AlgId)
 *          BitString           (typedef struct Bitstring)
 *          Boolean             (typedef char)
 *          EncryptedKey        (typedef struct EncryptedKey)
 *          ENCRYPTED           (typedef struct BitString)
 *          EncryptedKey        (typedef struct EncryptedKey) 
 *          KeyBits             (typedef struct KeyBits)
 *          More                (typedef enum { SEC_END, SEC_MORE })
 *          ObjId               (typedef struct ObjId)
 *          OctetString         (typedef struct Octetstring)
 *          Signature           (typedef struct Signature)
 *
 *   sca.h defines:
 *           Structures and types of the SCA-IF
 */

/***** Structure TERMINAL *****/
/** @ingroup header_secure
  */
typedef struct {
	char *id;    /**< SCT id */
	char *port;  /**< serial port name */
	char *lib;   /**< SCT access library */
	char *parms; /**< optional SCT parameters */
	char *comment; /**< Comment */
} TERMINAL;

#define CMD_INFO_V1 13

typedef struct {
	int   id;
	char *cmd;
	int   pin_offset1;
	int   pin_offset2;
	int   pin_length;
	int   time;
	char *rfu1s;
	char *rfu2s;
	int   rfu1i;
	int   rfu2i;
	char *text[8];
} CMD_INFO;

#define PSE_PIN_CHARS	 "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define PSE_PIN_L 8
#define SC_WAITTIME 20


/* this type is used in "sec_p.h", so it needs to be publicly visible... */
/***** Typedef IO_CB *****/
/** <B>IO_CB</B> specifies the type of a callback function managing input and output.
  *
  * @param prompt A string to be printed.
  * @param inp An input buffer or NULL if no input required.
  * @param size The size of the input buffer. The function should
  *      set it to the size of the input string entered.
  * @param visible A flag telling if the input of a string 
  *      should be visible on the screen. 
  * @ingroup header_secure
  */
typedef int  SEC_API_CALLING_CONV IO_CB	        SEC_PROTOTYPE_4( char * , prompt, char *  , inp, int * , size, Boolean  , visible);





#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



#endif /* _SECSC_ */

