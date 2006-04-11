/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/platform/platosf1.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*
 * Platform specific header for Compaq Tru64 UNIX aka Digital
UNIX aka DEC OSF/1
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif


#define SEC_TARGET_OS_OSF1 1
#define SEC_TARGET_OS_NAME "Tru64 UNIX"
#define SEC_TARGET_API_UNIX 1
#define SEC_TARGET_CPU_ALPHA 1
#include <db.h>
#include <wait.h>
#ifndef _OSF_SOURCE
typedef unsigned long u_long;
typedef u_int8_t u_char;
#endif
typedef u_int8_t uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;
typedef unsigned long uint64_t;

