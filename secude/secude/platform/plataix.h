/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/platform/plataix.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*
 * Platform specific header for IBM AIX, xlC
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif


#define SEC_TARGET_OS_AIX 1
#define SEC_TARGET_OS_NAME "AIX"
#define SEC_TARGET_API_UNIX 1
#define SEC_TARGET_CPU_PPC 1 /* Maybe this should be SEC_TARGET_CPU_POWER? */

#if !defined(_AIX41)
#  error "AIX 3.2 is not supported"
#endif

#include <sys/types.h>
#include <sys/machine.h>

