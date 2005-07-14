/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssysteme GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2001
 *
 ******************************************/

/*
 * Platform specific header for HP HP-UX
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif


#define SEC_TARGET_OS_HPUX 1
#define SEC_TARGET_OS_NAME "HP-UX"
#define SEC_TARGET_API_UNIX 1
#define SEC_TARGET_CPU_HPPA 1

#include <sys/types.h>
#ifndef __INTTYPES_INCLUDED
#include <model.h>
typedef u_int8 uint8_t;
typedef u_int16 uint16_t;
typedef u_int32 uint32_t;
typedef int8 int8_t;
typedef int16 int16_t;
typedef int32 int32_t;
#endif

