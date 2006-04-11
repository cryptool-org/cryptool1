/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/platform/platwin.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*
 * Platform specific header for Microsoft Windows NT, Visual Studio
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif


#define SEC_TARGET_OS_WIN32 1
#define SEC_TARGET_OS_NAME "Windows"
#define SEC_TARGET_API_WIN32 1
#define SEC_TARGET_CPU_X86 1

#if !defined(_M_IX86) && !defined(_M_IA64)
#  error "architecture not supported"
#endif

#if !defined(_MT)
#  error "compile with /MT or /MD (Multithreaded)"
#endif


/*
 * Minimum System Required, see MSDN Using the SDK Headers:
 * <http://msdn.microsoft.com/library/psdk/sdkintro/usage_8xgz.htm>
 */

#ifndef WINVER
# define WINVER 0x400 /* Windows 95 and Windows NT 4.0 */
#elif WINVER < 0x400
# error Windows 3.1 / Windows NT 3.51 is not supported
#endif

#ifndef _X86_
#define _X86_
#endif

#include <windef.h>

/* 7.18.1.1  Exact-width integer types */
typedef CHAR       int8_t;
typedef BYTE       uint8_t;
typedef SHORT      int16_t;
typedef WORD       uint16_t;
typedef LONG       int32_t;
typedef DWORD      uint32_t;
typedef LONGLONG   int64_t;
typedef ULONGLONG  uint64_t;

/* 7.18.1.2  Minimum-width integer types */
typedef int8_t    int_least8_t;
typedef uint8_t   uint_least8_t;
typedef int16_t   int_least16_t;
typedef uint16_t  uint_least16_t;
typedef int32_t   int_least32_t;
typedef uint32_t  uint_least32_t;
typedef int64_t   int_least64_t;
typedef uint64_t  uint_least64_t;

/*  7.18.1.3  Fastest minimum-width integer types */
typedef int8_t    int_fast8_t;
typedef uint8_t   uint_fast8_t;
typedef INT       int_fast16_t;
typedef UINT      uint_fast16_t;
typedef int32_t   int_fast32_t;
typedef uint32_t  uint_fast32_t;
typedef int64_t   int_fast64_t;
typedef uint64_t  uint_fast64_t;

#define USE_OWN_AUX_GETENV 1

#define SEC_CDECL __cdecl
typedef char *          caddr_t;

#ifdef SECUDE_DLL_EXPORT
#define SEC_WINDLL 1 
#endif
#define SEC_WINDOWS_NT  1  
#ifndef WIN32 
#define WIN32 1 
#endif  
#define SECUDE_ETC "c:\\secude\\etc"


#define USE_OWN_GETOPT 1

#define PKCS_FOR_AUTHENTICODE 1

