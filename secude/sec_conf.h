/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/


#ifndef _SEC_CONFIG_
#define _SEC_CONFIG_


#define SPKM_INSTALLED




#include "configur.h"      /* generated with config/configure */
#ifdef SAPonOS390
#include <unistd.h>
#endif
#ifndef AS_400
#define aux_gettimeofday gettimeofday
#endif

#if defined(SEC_WINDOWS) || defined(SEC_WINDOWS_NT) || defined(SEC_MS_DOS_GNU) || defined(OS2)
#define SEC_PC
#endif

#if defined(SEC_WINDOWS) || defined(SEC_WINDOWS_NT) 
#ifndef SEC_BCC
#define SEC_MSC
#endif
#define _DOS_
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef USE_TIME_H
#include <time.h>
#endif

#if defined(__STDC__) || defined(OS2) || defined(WIN32) || defined(SAPonOS390)
#define USE_STDARG
#endif
#if defined(__STDC__) || defined(__cplusplus) || defined(OS2) || defined(WIN32) || defined(SAPonOS390)
#define USE_ANSI_PROTOTYPES
#endif

#ifdef SEC_MSC
#include "msctypes.h"
#else
#ifdef SEC_BCC
#include "bcctypes.h"
#else
#ifndef OS2
#include <sys/time.h>
#else
#define _O_BINARY O_BINARY
#define _O_RDONLY O_RDONLY
#define _O_WRONLY O_WRONLY
#define _O_CREAT  O_CREAT
#define _S_IREAD  S_IREAD
#define _O_RDWR   O_RDWR
#define _O_TRUNC  O_TRUNC
#endif
#ifndef NO_TIMEB_H
#include <sys/timeb.h>
#endif
#endif
#endif

#ifdef SYS_LINUX
#include <getopt.h>
#define optind sec_optind
#define optarg sec_optarg
#define opterr sec_opterr
#define getopt(a,b,c) getopt_linux(a,b,c,&optind,&optarg)
#endif

#ifdef USE_UNISTD_H
#include <unistd.h>          /* setruid */
#endif

                                      
/*
 * Miscellaneous
 */



#ifdef SEC_WINDOWS
typedef unsigned long	sec_uint4;
typedef long		sec_int4;
#else
typedef unsigned int	sec_uint4;
typedef int		sec_int4;
#endif
typedef unsigned short	sec_uint2;
typedef short		sec_int2;
typedef unsigned char	sec_uint1;
typedef char		sec_int1;

typedef sec_uint4 HTONL_TYPE;

#define SIZEOF_L_NUMBER 32

#if defined(SEC_MSC) || defined(SEC_BCC) || defined(OS2) 
typedef char *          caddr_t;
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned long   u_long;
#endif

#if defined(SEC_MSC)

#define SEC_CDECL __cdecl

#else

#ifdef SEC_BCC

#define SEC_CDECL __cdecl

#define _O_BINARY O_BINARY
#define _O_RDONLY O_RDONLY
#define _O_WRONLY O_WRONLY
#define _O_CREAT  O_CREAT
#define _S_IREAD  S_IREAD
#define _O_RDWR   O_RDWR
#define _O_TRUNC  O_TRUNC

#define _stat stat

#else

#define SEC_CDECL

#ifndef O_BINARY
#define O_BINARY 0
#endif
#if !defined(_O_BINARY) && !defined(OS2)
#define _O_BINARY 0
#endif

#endif /* SEC_BCC */
#endif /* SEC_MSC */


#define NDBM                    /* ndbm database functions are available:         */
#ifdef SEC_PC
#define GDBM 			/* from own GDBM installation			  */
#endif

#ifndef USE_BCOPY

#ifndef bcopy
#define       bcopy(b1,b2,length)     (void) memmove ((b2), (b1), (length))
#endif
#ifndef bcmp
#define       bcmp(b1,b2,length)      memcmp ((b1), (b2), (length))
#endif
#ifndef bzero
#define       bzero(b,length)         (void) memset ((b), 0, (length))
#endif

#endif
#if defined(__STDC__) || defined(SEC_MSC) || defined(SEC_BCC) || defined(__EXTENDED__)
#define MACRO_SEP_LIKE_STDC
#endif

#ifndef SEC_PC
/*
 * Definitions for secxlock
 */

#define DEF_FILESEARCHPATH "/%T/%N%S"
#endif



/* Prototype macros */
#include "f_macros.h"

#if defined(SEC_MSC) || defined (SEC_BCC) || defined(OS2)
#include "unix4win.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV open_create SEC_PROTOTYPE_3(
	const char *, path, int, flags, int, mode);

#ifdef USE_SYS_ERRLIST
     char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV strerror SEC_PROTOTYPE_1(int , errnum);
#endif

#ifdef AS_400
#define S_IREAD S_IRUSR
#define S_IWRITE S_IWUSR

#define S_IFMT 0370000
#define S_IFREG _S_IFREG
#define S_IFDIR _S_IFDIR

#define isascii(c) ((unsigned) c <= 0177)

/*struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};*/
int SEC_GLOBAL_FUNC_PREFIX codepage SEC_PROTOTYPE_0();
void SEC_GLOBAL_FUNC_PREFIX set_signoff_callback SEC_PROTOTYPE_3(
        char * , cmd, char *, lib, char *, parm);
int SEC_GLOBAL_FUNC_PREFIX get_user_profile SEC_PROTOTYPE_2(
        char ** , name, char **, home);
char SEC_GLOBAL_FUNC_PREFIX *as400convert(char *str, int len, int incp, int outcp);
int SEC_GLOBAL_FUNC_PREFIX aux_gettimeofday SEC_PROTOTYPE_2(
	struct timeval	* , sec_tp1,
	struct timezone	* , sec_tzp1 );
extern unsigned short file_codepage;
#define SEC_EBCDIC	
#define aux_char_ASCII2local(c) ASCII2EBCDIC_table[c]
#define aux_char_local2ASCII(c) EBCDIC2ASCII_table[c]
#define aux_str_ASCII2local(str, len) aux_str_ASCII2EBCDIC(str,len)
#define aux_str_local2ASCII(str, len) aux_str_EBCDIC2ASCII(str,len)
#else
#define aux_char_ASCII2local(c) c
#define aux_char_local2ASCII(c) c
#define aux_str_ASCII2local(str, len) 
#define aux_str_local2ASCII(str, len) 
#endif



#ifdef SECUDE_DEBUG
#define PLUGIN_DEBUG
#define TRACE_ASN1
#endif

#ifdef OS2
#define MAX_STACK_ARRAY_LEN 0x2000
#else
#define MAX_STACK_ARRAY_LEN 0x8000
#endif

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



#endif /* _SEC_CONFIG_ */

