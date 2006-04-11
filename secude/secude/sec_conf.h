/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/sec_conf.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#ifndef _SEC_CONFIG_
#define _SEC_CONFIG_

#ifdef undefined /* just in case... */
# undef undefined
#endif

#ifndef SECUDE_VERSION_MAJ
#include <secude/secver.h>
#endif

#define SECUDE_CONF_INCLUDE 1

#if defined(__MRC__) || defined(__MWERKS__) /* Apple MacOS 8/9, MPW MrC or Metrowerks Codewarrior */
#  include <secude/platform/platmac.h>
#elif defined(__APPLE__) /* Apple MacOS X, Apple gcc */
#  include <secude/platform/platmosx.h>
#elif defined(__osf__) /* Compaq Tru64 UNIX aka Digital UNIX aka DEC OSF/1 */
#  include <secude/platform/platosf1.h>
#elif defined(undefined) /* Data General DG/UX */
#  include <secude/platform/platxxx.h>
#elif defined(__linux__) /* FSF GNU/Linux, GNU gcc */
#  include <secude/platform/platlinu.h>
#elif defined(__hpux) /* HP HP-UX */
#  include <secude/platform/plathpux.h>
#elif defined(_AIX) /* IBM AIX, xlC */
#  include <secude/platform/plataix.h>
#elif defined(undefined) /* IBM AS/400 */
#  include <secude/platform/platxxx.h>
#elif defined(__OS2__) /* IBM OS/2, VisualAge C++ */
#  include <secude/platform/platos2.h>
#elif defined(__OS390__) /* IBM OS/390 */
#  include <secude/platform/platos39.h>
#elif defined(_WIN32) /* Microsoft Windows NT, Visual Studio */
#  include <secude/platform/platwin.h>
#elif defined(undefined) /* SGI Irix */
#  include <secude/platform/platirix.h>
#elif defined(__sun) /* Sun Solaris aka SunOS, Sun cc */
#  include <secude/platform/platsun.h>
#elif defined(__SNI_HOST_UNIX) /* Fujitsu-Siemens Reliant UNIX aka Sinix */
#  include <secude/platform/platsini.h>
#else /* unknown platform/compiler combination */
/* this is a compiler which is unsupported or we cannot autodetect */
/* please include your own header file */
#  include <secude/platform/platxxx.h>
#endif

#undef SECUDE_CONF_INCLUDE

/*
 * The configuration files define:
 * from ISO/IEC 988:1999 spec
 * 7.18.1.1 Exact-width integer types [u]int{8,16,32,64}_t
 * 7.18.1.2 Minumun-width integer types [u]int_least{8,16,32,64}_t
 * 7.18.1.3 Fastest-width integer types [u]int_fast{8,16,32,64}_t
 *
 * size_t, ssize_t, ptrdiff_t
 * SEC_BYTE_ORDER
 */

/*
 * if SEC_BYTE_ORDER is not defined in the configuration files
 * try BYTE_ORDER first
 * then autodetect by SEC_TARGET_CPU
 */

#if !defined(SEC_BYTE_ORDER)
# if defined(BYTE_ORDER) && defined(LITTLE_ENDIAN) && defined(BIG_ENDIAN) && defined(PDP_ENDIAN)
#  define SEC_LITTLE_ENDIAN LITTLE_ENDIAN
#  define SEC_BIG_ENDIAN BIG_ENDIAN
#  define SEC_PDP_ENDIAN PDP_ENDIAN
#  define SEC_BYTE_ORDER BYTE_ORDER
# else
#  define SEC_LITTLE_ENDIAN   1234    /* LSB first: i386, vax */
#  define SEC_BIG_ENDIAN      4321    /* MSB first: 68000, ibm, net, ppc */
#  define SEC_PDP_ENDIAN      3412    /* LSB first in word, MSW first in long (pdp) */
#  if defined(SEC_TARGET_CPU_X86) && SEC_TARGET_CPU_X86 \
     || defined(SEC_TARGET_CPU_ALPHA) && SEC_TARGET_CPU_ALPHA
#   define SEC_BYTE_ORDER      SEC_LITTLE_ENDIAN
#  elif defined(SEC_TARGET_CPU_SPARC) && SEC_TARGET_CPU_SPARC \
     || defined(SEC_TARGET_CPU_PPC) && SEC_TARGET_CPU_PPC \
     || defined(SEC_TARGET_CPU_HPPA) && SEC_TARGET_CPU_HPPA
#   define SEC_BYTE_ORDER      SEC_BIG_ENDIAN
#  endif
# endif
#endif

#if !defined(SEC_BYTE_ORDER) || \
    (SEC_BYTE_ORDER != SEC_LITTLE_ENDIAN && SEC_BYTE_ORDER != SEC_BIG_ENDIAN && SEC_BYTE_ORDER != SEC_PDP_ENDIAN)
# error "you must determine the correct byte order for your operating system";
#endif

#if defined(__cplusplus)
# define SEC_EXTERNC extern "C"
# define SEC_BEGIN_EXTERNC extern "C" {
# define SEC_END_EXTERNC	}
#else
# define SEC_EXTERNC extern
# define SEC_BEGIN_EXTERNC
# define SEC_END_EXTERNC
#endif

/*
 * calling conventions
 */

#ifndef SEC_CDECL
# define SEC_CDECL
#endif

#define SPKM_INSTALLED

#if defined(SEC_WINDOWS) || defined(SEC_WINDOWS_NT) || defined(SEC_MS_DOS_GNU) || defined(OS2)
#define SEC_PC
#endif

#if defined(SEC_WINDOWS) || defined(SEC_WINDOWS_NT) 
#ifndef SEC_BCC
#define SEC_MSC
#endif
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#if defined(__STDC__) || defined(OS2) || defined(WIN32) || defined(SAPonOS390)
#define USE_STDARG
#endif
#if defined(__STDC__) || defined(__cplusplus) || defined(OS2) || defined(WIN32) || defined(SAPonOS390)
#define USE_ANSI_PROTOTYPES
#endif



                                      
/*
 * Miscellaneous
 */


/*
 * Legacy, deprecated
 */
typedef uint32_t	sec_uint4;
typedef int32_t		sec_int4;
typedef uint16_t	sec_uint2;
typedef int16_t		sec_int2;
typedef uint8_t		sec_uint1;
typedef int8_t		sec_int1;

typedef sec_uint4 HTONL_TYPE;

#define SIZEOF_L_NUMBER 32






#if defined(__STDC__) || defined(SEC_MSC) || defined(SEC_BCC) || defined(__EXTENDED__)
#define MACRO_SEP_LIKE_STDC
#endif




/* Prototype macros */
#include <secude/f_macros.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




#ifdef SECUDE_DEBUG
#define PLUGIN_DEBUG 1
#define TRACE_ASN1 1
#endif



#ifdef USE_OWN_AUX_GETENV
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_getenv SEC_PROTOTYPE_1(const char *,str);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_putenv SEC_PROTOTYPE_1(const char *,str);
#else
#define aux_getenv(c) getenv(c)
#define aux_putenv(c) putenv(c)
#endif
#ifdef USE_OWN_GETOPT
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV getopt SEC_PROTOTYPE_3(
	int	 , argc,
	char ** , argv,
	char	* , optstring );
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX optarg;
extern int SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  optind, opterr;
#endif


#ifndef MAXKEYLENGTH
#define MAXKEYLENGTH 16384
#endif
#ifndef SIZEOFINT
#define SIZEOFINT 32  
#endif
#define NEW_PSE_STRUCT 1 
#define ENABLE_GENERIC_CIPHER_MODES 1


#ifndef NO_SCA
#define SCA 1
#endif
#ifndef NO_X509v3
#define X509v3 1
#endif
#ifndef NO_ASN1_NETSCAPE_STUFF
#define ASN1_NETSCAPE_STUFF 1
#endif
#ifndef NO_WWW
#define WWW 1
#endif
#ifndef NO_SSL_INSTALLED         
#define SSL_INSTALLED 1
#endif                           
#ifndef NO_RSA_INSTALLED         
#define RSA_INSTALLED 1
#endif                           
#ifndef NO_SQMODN_INSTALLED      
#define SQMODN_INSTALLED 1
#endif                           
#ifndef NO_AFDBFILE              
#define AFDBFILE 1
#endif                           
#ifndef NO_MD_INSTALLED          
#define MD_INSTALLED 1
#endif                           
#ifndef NO_EC_INSTALLED          
#define EC_INSTALLED 1
#endif                           
#ifndef NO_DES_INSTALLED         
#define DES_INSTALLED 1
#endif                           
#ifndef NO_SECUDE_IMPLEMENTS_AES 
#define SECUDE_IMPLEMENTS_AES 1
#endif                           
#ifndef NO_DH_INSTALLED          
#define DH_INSTALLED 1
#endif                           
#ifndef NO_RC_INSTALLED          
#define RC_INSTALLED 1
#endif                           
#ifndef NO_DSA_INSTALLED         
#define DSA_INSTALLED 1
#endif                           
#ifndef NO_SHS_INSTALLED         
#define SHS_INSTALLED 1
#endif                           
#ifndef NO_RMD_INSTALLED         
#define RMD_INSTALLED 1
#endif                           
#ifndef NO_IDEA_INSTALLED        
#define IDEA_INSTALLED 1
#endif                           
#ifndef NO_GSSAPI_INSTALLED      
#define GSSAPI_INSTALLED 1
#endif                           
#ifndef NO_PEM_INSTALLED         
#define PEM_INSTALLED 1
#endif                           
#ifndef NO_PKCS_INSTALLED        
#define PKCS_INSTALLED 1
#endif                           
#ifndef NO_CA_FUNCTIONS_INSTALLED
#define CA_FUNCTIONS_INSTALLED 1
#endif                           
#ifndef NO_CRS_INSTALLED         
#define CRS_INSTALLED 1
#endif                           
#ifndef NO_X500                  
#define X500 1         
#endif                           
#ifndef NO_LDAP_WITH_DL_OPEN         
#define LDAP_WITH_DL_OPEN 1
#endif                           
#ifndef NO_X500_USE_LDAP         
#define X500_USE_LDAP 1
#endif                           
#ifndef NO_USE_TIME_H            
#define USE_TIME_H 1 
#endif                           
#ifndef NO_GSS_SAMPLE_INSTALLED  
#define GSS_SAMPLE_INSTALLED 1
#endif                           
#ifndef NO_SECURE_INSTALLED      
#define SECURE_INSTALLED 1
#endif                                        
#ifndef NO_OCSP_INSTALLED        
#define OCSP_INSTALLED 1
#endif            

#define NO_SENF_INSTALLED
               
#ifndef NO_SENF_INSTALLED        
#define SENF_INSTALLED 1
#endif                           

#ifdef __cplusplus       
} /* extern C */         
#endif /* __cplusplus */ 
                         
                         
                         
#endif /* _SEC_CONFIG_ */

