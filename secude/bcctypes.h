/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

/* Headerfile for Borland C++ Compiler */

#ifndef BCC_TYPES_H_
#define BCC_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include <ctype.h>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <memory.h>
#include <winsock.h>
#include "getuid.h"

/* needed for sleep() */
#include <dos.h>

#ifdef SECUDE
/* these defines only during compiling SecuDE */

/******
 * DEFINES
 ******/    

#ifndef bcopy
#define       bcopy(b1,b2,length)     (void) memmove ((b2), (b1), (length))
#endif
#ifndef bcmp
#define       bcmp(b1,b2,length)      memcmp ((b1), (b2), (length))
#endif
#ifndef bzero
#define       bzero(b,length)         (void) memset ((b), 0, (length))
#endif
 

#define sys_errlist  _sys_errlist

#define L_SET 	  SEEK_SET

#define _filelength filelength

#define mkdir(string, MODE)   mkdir(string)


/******
 * TypeDefs
 ******/
#define off_t  long

#endif /* SECUDE */

/*
struct dirent {
	char		d_name[256];	* name of file *
};
typedef struct {
	long dir;
	struct dirent dir_ent;
}	DIR;
*/

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


                                             
#endif /* BCC_TYPES_H_ */

