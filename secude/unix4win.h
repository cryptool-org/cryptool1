/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

#ifndef _UNIX4WIN_
#define _UNIX4WIN_



/*
 * Prototypes for functions of the UNIX4WIN package
 */
#ifdef OS2
#define INCL_DOSFILEMGR
#include <os2.h>
#include <msctypes.h>
struct timeval {
   int tv_sec;
   int tv_usec;
};

//struct dirent {
//	char		d_name[256];	/* name of file */
//};

//typedef struct {
//	HDIR dir;
//	struct dirent dir_ent;
//}	DIR;

#endif

#include "getuid.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_putenv SEC_PROTOTYPE_1(char *,str);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_gettimeofday SEC_PROTOTYPE_2(
	struct timeval	* , sec_tp1,
	struct timezone	* , sec_tzp1 );

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV link SEC_PROTOTYPE_2(
	char	* , name1,
	char	* , name2 );

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV getopt SEC_PROTOTYPE_3(
	int	 , argc,
	char ** , argv,
	char	* , optstring );


uid_t SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV getuid SEC_PROTOTYPE_0();
gid_t SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV getgid SEC_PROTOTYPE_0();


#ifndef SEC_BCC
DIR SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV opendir SEC_PROTOTYPE_1(
	char 		*	,	filename
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  closedir SEC_PROTOTYPE_1(
	DIR 		*	,	dir
);

struct dirent SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV readdir SEC_PROTOTYPE_1(
	DIR 		*	,	dir
);
#endif

/* externals */
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX optarg;
extern int SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  optind, opterr;


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* _UNIX4WIN_*/


