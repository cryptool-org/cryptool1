#ifndef CONFIG__H
#define CONFIG__H
/* config.h --- configuration file for Windows NT
   Jim Blandy <jimb@cyclic.com> --- July 1995  

    Modified for Win32 Server support 
	Tony Hoyle <tmh@magenta-logic.com> --- December 1999
*/

/* This file lives in the windows-NT subdirectory, which is only included
   in your header search path if you're working under Microsoft Visual C++,
   and use ../cvsnt.mak for your project.  Thus, this is the right place to
   put configuration information for Windows NT.  */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* Windows NT doesn't have gid_t.  It doesn't even really have group
   numbers, I think.  This will take more thought to get right, but
   let's get it running first.  */
#define gid_t int

/* Define to `int' if <sys/types.h> doesn't define.  */
/* Under Windows NT, we use the process handle as the pid.
   We could #define pid_t to be HANDLE, but that would require
   us to #include <windows.h>, which I don't trust, and HANDLE
   is a pointer type anyway.  */
#define pid_t void*

/* Define to `int' if <sys/types.h> doesn't define.  */
/* Defined to void* for WinNT to take a handle (from LogonUser etc.) */
#define uid_t void*

/* Define if you have MIT Kerberos version 4 available.  */
/* We don't.  Cygnus says they've ported it to Windows 3.1, but
   I don't know if that means that it works under Windows NT as
   well.  */
#undef HAVE_KERBEROS

/* Define if you want CVS to be able to be a remote repository client.  */
/* We just want the client stuff.  */
#define CLIENT_SUPPORT

/* Define if you want CVS to be able to serve repositories to remote
   clients.  */
#if defined(CVS95)
#undef SERVER_SUPPORT
#undef AUTH_SERVER_SUPPORT
#else
#define SERVER_SUPPORT
#define AUTH_SERVER_SUPPORT
#endif

/* Define if creating an NT version */
#ifndef CVS95
#define WINNT_VERSION
#else
#undef WINNT_VERSION
#endif

/* Define if you have the connect function.  */
#define HAVE_CONNECT

/* Define if you have the fchdir function.  */
#undef HAVE_FCHDIR

/* Define if you have the fchmod function.  */
#undef HAVE_FCHMOD

/* Define if you have the fsync function.  */
#undef HAVE_FSYNC

/* Define if you have the ftime function.  */
#define HAVE_FTIME 1

/* Define if you have the ftruncate function.  */
#undef HAVE_FTRUNCATE

/* Define if you have the getpagesize function.  */
#undef HAVE_GETPAGESIZE

/* Define if you have the krb_get_err_text function.  */
#undef HAVE_KRB_GET_ERR_TEXT

/* Define if you have the putenv function.  */
#define HAVE_PUTENV 1

/* Define if you have the sigaction function.  */
#undef HAVE_SIGACTION

/* Define if you have the sigblock function.  */
#undef HAVE_SIGBLOCK

/* Define if you have the sigprocmask function.  */
#undef HAVE_SIGPROCMASK

/* Define if you have the sigsetmask function.  */
#undef HAVE_SIGSETMASK

/* Define if you have the sigvec function.  */
#undef HAVE_SIGVEC

/* Define if you have the timezone function.  */
/* Hmm, I actually rather think it's an extern long
   variable; that message was mechanically generated
   by autoconf.  And I don't see any actual uses of
   this function in the code anyway, hmm.  */
#undef HAVE_TIMEZONE

/* Define if you have the vfork function.  */
#undef HAVE_VFORK

/* Define if you have the vprintf function.  */
#define HAVE_VPRINTF 1

/* Define if you have the <direct.h> header file.  */
/* Windows NT wants this for mkdir and friends.  */
#define HAVE_DIRECT_H 1

/* Define if you have the <dirent.h> header file.  */
/* No, but we have the <direct.h> header file...  */
#undef HAVE_DIRENT_H

/* Define if you have the <errno.h> header file.  */
#define HAVE_ERRNO_H 1

/* Define if you have the <fcntl.h> header file.  */
#define HAVE_FCNTL_H 1

/* Define if you have the <io.h> header file.  */
/* Apparently this is where Windows NT declares all the low-level
   Unix I/O routines like open and creat and stuff.  */
#define HAVE_IO_H 1

/* Define if you have the <memory.h> header file.  */
#define HAVE_MEMORY_H 1

/* Define if you have the <ndbm.h> header file.  */
#undef HAVE_NDBM_H

/* Define if you have the <ndir.h> header file.  */
#define HAVE_NDIR_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define to force lib/regex.c to use malloc instead of alloca.  */
#define REGEX_MALLOC 1

/* Define to force lib/regex.c to define re_comp et al.  */
#define _REGEX_RE_COMP 1

/* Define if you have the <sys/bsdtypes.h> header file.  */
#undef HAVE_SYS_BSDTYPES_H

/* Define if you have the <sys/dir.h> header file.  */
#undef HAVE_SYS_DIR_H

/* Define if you have the <sys/ndir.h> header file.  */
#undef HAVE_SYS_NDIR_H

/* Define if you have the <sys/param.h> header file.  */	
#undef HAVE_SYS_PARAM_H

/* Define if you have the <sys/select.h> header file.  */
#undef HAVE_SYS_SELECT_H

/* Define if you have the <sys/time.h> header file.  */
#undef HAVE_SYS_TIME_H

/* Define if you have the <sys/timeb.h> header file.  */
#define HAVE_SYS_TIMEB_H 1

/* Define if you have the <unistd.h> header file.  */
#undef HAVE_UNISTD_H

/* Define if you have the <utime.h> header file.  */
#undef HAVE_UTIME_H
#define HAVE_SYS_UTIME_H

/* Define if you have the inet library (-linet).  */
#undef HAVE_LIBINET

/* Define if you have the nsl library (-lnsl).  */
/* This is not used anywhere in the source code.  */
#undef HAVE_LIBNSL

/* Define if you have the nsl_s library (-lnsl_s).  */
#undef HAVE_LIBNSL_S

/* Define if you have the socket library (-lsocket).  */
/* This isn't ever used either.  */
#undef HAVE_LIBSOCKET

/* Under Windows NT, mkdir only takes one argument.  */
#define CVS_MKDIR wnt_mkdir
extern int wnt_mkdir (const char *PATH, int MODE);
#define CVS_STAT stat
#define CVS_LSTAT stat
#define CVS_RENAME wnt_rename
extern int wnt_rename (const char *, const char *);

/* This function doesn't exist under Windows NT; we
   provide a stub.  */
extern int readlink (char *path, char *buf, int buf_size);

#if !defined(NO_GETPID)
/* This is just a call to GetCurrentProcessID.  */
#include <process.h>
#define getpid wnt_getpid
extern pid_t wnt_getpid (void);
#endif

/* We definitely have prototypes.  */
#define USE_PROTOTYPES 1

/* This is just a call to the Win32 Sleep function.  */
unsigned int sleep (unsigned int);

/* Don't worry, Microsoft, it's okay for these functions to
   be in our namespace.  */
#define popen _popen
#ifndef pclose
#define pclose _pclose
#endif

/* When writing binary data to stdout, we better set
   stdout to binary mode using setmode.  */
#define USE_SETMODE_STDOUT 1

/* Diff also has an ifdef for setmode, and it is HAVE_SETMODE.  */
#define HAVE_SETMODE 1

/* Diff needs us to define this.  I think it could always be
   -1 for CVS, because we pass temporary files to diff, but
   config.h seems like the easiest place to put this, so for
   now we put it here.  */
#define same_file(s,t) (-1)

/* This is where old bits go to die under Windows NT.  */
#define DEVNULL "nul"

/* Don't use an rsh subprocess to connect to the server, because
   the rsh does inappropriate translations on the data (CR-LF/LF).  */
#define RSH_NOT_TRANSPARENT 1
extern void wnt_start_server (int *tofd, int *fromfd,
			      char *client_user,
			      char *server_user,
			      char *server_host,
			      char *server_cvsroot);
extern void wnt_shutdown_server (int fd);
#define START_SERVER wnt_start_server
#define SHUTDOWN_SERVER wnt_shutdown_server

#define SYSTEM_INITIALIZE(mode,pargc,pargv) win32init(mode)
void win32init(int mode);
#define SYSTEM_CLEANUP() wnt_cleanup()
extern void wnt_cleanup (void);

#define HAVE_WINSOCK_H

/* This tells the client that it must use send()/recv() to talk to the
   server if it is connected to the server via a socket; Windows needs
   it because _open_osfhandle doesn't work.  */
#define NO_SOCKET_TO_FD 1

/* This tells the client that, in addition to needing to use
   send()/recv() to do socket I/O, the error codes for send()/recv()
   and other socket operations are not available through errno.
   Instead, this macro should be used to obtain an error code. */
#define SOCK_ERRNO (WSAGetLastError ())

/* This tells the client that, in addition to needing to use
   send()/recv() to do socket I/O, the error codes for send()/recv()
   and other socket operations are not known to strerror.  Instead,
   this macro should be used to convert the error codes to strings. */
#define SOCK_STRERROR sock_strerror
extern char *sock_strerror (int errnum);

/* The internal rsh client uses sockets not file descriptors.  Note
   that as the code stands now, it often takes values from a SOCKET and
   puts them in an int.  This is ugly but it seems like sizeof
   (SOCKET) <= sizeof (int) on win32, even the 64-bit variants.  */
#define START_SERVER_RETURNS_SOCKET 1

/* Is this true on NT?  Seems like I remember reports that NT 3.51 has
   problems with 200K writes (of course, the issue of large writes is
   moot since the use of buffer.c ensures that writes will only be as big
   as the buffers).  */
#define SEND_NEVER_PARTIAL 1

// Disable 'signed/unsigned mismatch'
#pragma warning (disable:4018)

// Disable function parameter differences in function pointers
#pragma warning (disable:4113)

// Disable conversion from long to char
#pragma warning (disable:4244)

#ifndef PROTOCOL_DLL /* If this is a protocol dll stop here */

// Validate a users' password against the NT username database on the 
// current machine
int win32_valid_user(char *username, char *pasword, char* domain);

// Helper routines for password stuff
//struct passwd *win32getpwuid(uid_t uid);
struct passwd *win32getpwnam(const char *name);
char *win32getlogin();
char *win32getfileowner(const char *file);

#ifdef SERVER_SUPPORT
int win32setuser(const char *username);
int win32switchtouser(const char *username);
#endif
void win32flush(int fd);
#include <stdio.h> // Stops error
#define pipe(_p) _pipe(_p,BUFSIZ,_O_BINARY)
void win32setblock(int h, int block);

// Debugging
#include <crtdbg.h>
#ifdef _DEBUG
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
/* Standard VC alloc checking */
#define malloc(_mem) _malloc_dbg(_mem, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(_ptr,_mem) _realloc_dbg(_ptr,_mem,_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

/* non-case sensitive filename comparison */
#define filename_cmp(a,b) stricmp(a, b)

/* Stuff to stop inconsistent dll linkage errors */
#ifndef CVSGUI
#define getenv getenv
#endif
#define strerror strerror

/* crypt() functionality */
char *crypt(const char *key,const char *salt);

#ifdef CVSGUI_PIPE
#	include "cvsgui.h"
#endif

/* Override so we can delete read-only files */
#define CVS_UNLINK wnt_unlink
int wnt_unlink(const char *file);

int win32_isadmin();
int win32_openpipe(const char *pipe);
void win32_perror(int quit, const char *prefix, ...); // Print last error from pipe

/* New open funcs, for pre-parsing '\' and '/' */
#include <io.h>
#include <sys/stat.h>
#include <sys/utime.h>

struct wnt_stat {
        _dev_t st_dev;
        _ino_t st_ino;
        unsigned short st_mode;
        short st_nlink;
        short st_uid;
        short st_gid;
        _dev_t st_rdev;
        _off_t st_size;
        time_t st_atime;
        time_t st_mtime;
        time_t st_ctime;
        };
int wnt_stat(const char *name, struct wnt_stat *buf);
int wnt_fstat (int fildes, struct wnt_stat *buf);
int wnt_lstat (const char *name, struct wnt_stat *buf);

#if !defined(NO_REDIRECTION)
#define fstat wnt_fstat
#define lstat wnt_lstat
#define stat wnt_stat

FILE *wnt_fopen(const char *filename, const char *mode);
int wnt_open(const char *filename, int oflag , int pmode);
int wnt_access(const char *path, int mode);
int wnt_utime(const char *filename, struct utimbuf *uf);

#define fopen wnt_fopen
#define open wnt_open
#define access wnt_access
#define utime wnt_utime
#else
#define lstat stat
#endif

#include <time.h>

#define asctime wnt_asctime
#define ctime wnt_ctime

char *wnt_asctime(const struct tm *tm);
char *wnt_ctime(const time_t *t);

#endif /* not PROTOCOL_DLL */

#define strcasecmp stricmp
#define strncasecmp strnicmp
#define snprintf _snprintf
#define vsnprintf _vsnprintf

#define HAVE_GSSAPI_GSSAPI_H
#define HAVE_GSSAPI_GSSAPI_GENERIC_H
#define HAVE_KRB5_H
#define GSS_C_NT_HOSTBASED_SERVICE gss_nt_service_name

#define HAVE_GETADDRINFO /* Provided by platform SDK */
#define HAVE_INET_ATON 

/* Stuff for xdelta */
#define NO_SYS_SIGLIST	1
#define NO_SYS_SIGLIST_DECL	1

#endif
