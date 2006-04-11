/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/platform/platlinu.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*
 * Platform specific header for FSF GNU/Linux, GNU gcc
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif


#define SEC_TARGET_OS_LINUX 1
#define SEC_TARGET_OS_NAME "Linux"
#define SEC_TARGET_API_UNIX 1

#if defined(__i386) || defined(__i386__)
# define SEC_TARGET_CPU_X86 1
#elif defined(__ppc) || defined(__ppc__) || defined(__PPC__)
# define SEC_TARGET_CPU_PPC 1
#elif defined(__s390x__)
# define SEC_TARGET_CPU_OS390 1
#elif defined(__ia64__)
# define SEC_TARGET_CPU_IA64 1
#elif defined(__x86_64__)
# define SEC_TARGET_CPU_AMD64 1
#else
# error "architecture not supported"
#endif

#if !defined __GNUC__ || __GNUC__ < 2
# error "compiler not supported"
#endif

#if __GNUC__ >= 3 || __GNUC_MINOR__ > 8 /* This is stupid: egcs is libc6, else libc5. Find a better way! */

#define _BSD_SOURCE 1

#include <stdint.h>
#include <endian.h>

#else

#include <sys/types.h>

/* 7.18.1.1  Exact-width integer types */
typedef u_int8_t	uint8_t;
typedef u_int16_t       uint16_t;
typedef u_int32_t       uint32_t;
typedef u_int64_t       uint64_t;

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
#ifndef __ia64__
typedef int16_t   int_fast16_t;
typedef uint16_t  uint_fast16_t;
typedef int32_t   int_fast32_t;
typedef uint32_t  uint_fast32_t;
#endif
typedef int64_t   int_fast64_t;
typedef uint64_t  uint_fast64_t;

#include <endian.h>

#endif

