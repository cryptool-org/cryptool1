/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/



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

