/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/
#ifndef SECUDE_INSQUE_H
#define SECUDE_INSQUE_H


/* Use the qbuf type taken from ISODE's compat/manifest.h

	struct qelem {
	     struct    qelem *q_forw;
 	    struct    qelem *q_back;
 	    char *q_data;
	};
*/
#include "compat/manifest.h"
#define qelem	qbuf
#define q_forw	qb_forw
#define q_back	qb_back


#endif

