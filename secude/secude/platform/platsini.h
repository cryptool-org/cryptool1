/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/platform/platsini.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*
 * Platform specific header for Fujitsu-Siemens Reliant UNIX aka Sinix
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif


#define SEC_TARGET_OS_SINIX 1
#define SEC_TARGET_OS_NAME "Reliant UNIX"
#define SEC_TARGET_API_UNIX 1
#define SEC_TARGET_CPU_MIPS 1
#ifndef BYTE_ORDER
#  define LITTLE_ENDIAN   1234    /* LSB first: i386, vax */
#  define BIG_ENDIAN      4321    /* MSB first: 68000, ibm, net, ppc */
#  define PDP_ENDIAN      3412    /* LSB first in word, MSW first in long (pdp) */
#  define BYTE_ORDER      BIG_ENDIAN
#endif
#define NO_FDATASYNC 1
#define NO_INET_ATON 1
#include <unistd.h>
#ifndef _INTTYPES_H
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;
#endif

