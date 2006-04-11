/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/platform/platsun.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*
 * Platform specific header for Sun Solaris aka SunOS, Sun cc
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif


#define SEC_TARGET_OS_SUNOS 1
#define SEC_TARGET_OS_NAME "Solaris"
#define SEC_TARGET_API_UNIX 1

#if defined(__sparc) || defined(sparc)
#  define SEC_TARGET_CPU_SPARC 1
#elif defined(__i386) || defined(i386)
#  define SEC_TARGET_CPU_X86 1
#elif defined(__ppc)
#  define SEC_TARGET_CPU_PPC 1
#elif defined(__ia64)
#  error "architecture not supported"
#else
#  error "architecture not supported"
#endif

#include <sys/types.h>

