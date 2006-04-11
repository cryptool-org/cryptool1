/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/cmd_srch.h
 *###
 *### global functions:
 *###
 *###*****************************************/



#ifndef _CMD_SRCH_
#define _CMD_SRCH_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



typedef struct  cmd_table {
	char    *cmd_key;
	int     cmd_value;
} CMD_TABLE;


struct  cm_args {
	char    *cm_key;
	char    *cm_value;
};

int     cmd_srch ();
char   *rcmd_srch ();


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* _CMD_SRCH_ */

