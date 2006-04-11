/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/platform/platos39.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*
 * Platform specific header for OS/390
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif


#define SEC_TARGET_OS_OS390 1
#define SEC_TARGET_OS_NAME "OS/390"
#ifndef BYTE_ORDER
#  define LITTLE_ENDIAN   1234    /* LSB first: i386, vax */
#  define BIG_ENDIAN      4321    /* MSB first: 68000, ibm, net, ppc */
#  define PDP_ENDIAN      3412    /* LSB first in word, MSW first in long (pdp) */
#  define BYTE_ORDER      BIG_ENDIAN
#endif
#include <rapi.h>
#include <dirent.h>
#ifdef OS390_08
typedef unsigned short uint16_t;
#else
typedef char int8_t;
#include <inttypes.h>
#endif

#define FPRINTF SEC_FPRINTF
#define PRINTF SEC_PRINTF
#define NO_X500 1
#define USE_ANSI_C
#define USE_STDARG

