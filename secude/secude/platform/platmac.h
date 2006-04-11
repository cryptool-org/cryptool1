/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/platform/platmac.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*
 * Platform specific header for Apple MacOS 8/9, MPW MrC or Metrowerks Codewarrior
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif

#include <secude/conf_mac.h> /* This file will go away */

#define SEC_TARGET_OS_MACOS 1
#define SEC_TARGET_OS_NAME "Mac OS"
#define SEC_TARGET_API_MAC_CARBON 1
#define SEC_TARGET_CPU_PPC 1

