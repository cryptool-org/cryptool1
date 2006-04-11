
#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif

#define SEC_TARGET_OS_MACOSX 1
#define SEC_TARGET_OS_NAME "Mac OS X"
#define SEC_TARGET_API_MAC_OSX 1
#define SEC_TARGET_RT_MAC_MACHO 1
#define SEC_TARGET_API_MAC_CARBON 1
#define SEC_TARGET_API_UNIX 1
#define SEC_TARGET_CPU_PPC 1

/*
#define _BSD_SOURCE 1
*/

#define PATH_SEPARATION_STRING "/"
#define PATH_SEPARATION_CHAR   '/'

#include <stdint.h>
#include <machine/endian.h>

