/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

#ifndef MSC_TYPES_H_
#define MSC_TYPES_H_


#ifdef SEC_BCC
#include "bcctypes.h"
#else

#include <ctype.h>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <memory.h>
#ifndef OS2
#include <winsock.h>
#endif
#include "getuid.h"
#include <process.h>


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
       
#ifndef OS2
#define S_IFMT    _S_IFMT
#define S_IFDIR   _S_IFDIR
#define S_IFREG   _S_IFREG
#define S_IREAD   _S_IREAD
#define S_IWRITE   _S_IWRITE

#define O_RDONLY  _O_RDONLY
#define O_WRONLY  _O_WRONLY
#define O_CREAT   _O_CREAT
#define O_EXCL    _O_EXCL
#define O_TRUNC   _O_TRUNC
#define O_RDWR    _O_RDWR
#define O_BINARY  _O_BINARY
#define O_APPEND  _O_APPEND
#else
#define S_IFMT (S_IFDIR | S_IFCHR | S_IFREG)
#endif

#define getpid _getpid

#define L_SET 	  SEEK_SET
 
 
#define read	  _read 
#define write	  _write
#define open	  _open
#define close	  _close
#define lseek     _lseek

#define getcwd    _getcwd

#define getpid	  _getpid
#if !defined(_MAC)
#define getch	  _getch
#else
#define getch     getchar
#endif
#ifndef OS2
#define stat      _stat
#define isascii   __isascii
#endif
#define fstat     _fstat     


#define strdup      _strdup
#define dup         _dup


#define mkdir(string, MODE)   _mkdir(string)
#define rmdir	              _rmdir

#define unlink    _unlink
#define putenv    _putenv
#define fdopen    _fdopen

#ifdef OS2
#define sleep(a)
#define off_t  long
#else
#ifndef sleep
#define sleep     Sleep
#endif
#define off_t  _off_t
#endif


/******
 * TypeDefs
 ******/

#endif /* SECUDE */

struct dirent {
	char		d_name[256];	/* name of file */
};
typedef struct {
	long dir;
	struct dirent dir_ent;
}	DIR;

#endif /* SEC_BCC */



                                             
#endif /* MSC_TYPES_H_ */

