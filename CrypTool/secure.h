/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


/* 
 *
 * $Id$
 *
 * $Log$
 * Revision 1.3  2004/04/30 12:09:41  clausius
 * Compiles with VS.NET C++
 *
 * Revision 1.2  2003/12/17 17:49:15  clausius
 * GPL Header hinzugefuegt
 *
 * Revision 1.1  2002/02/27 12:48:24  idj100
 * CrypTool develop 1.3.01
 *
 * Revision 1.1.1.1  2001/01/29 13:58:24  koy
 * CrypTool Weiterentwicklung zu Version 1.3
 *
 * Verzeichnisse umstrukturiert
 *
 * Revision 1.1.1.1.2.2  2001/01/09 12:38:14  blumenstein
 * no message
 *
 * Revision 1.1.1.1.2.1  2001/01/09 10:19:10  blumenstein
 * CR's Raus!
 *
 * Revision 1.1.1.1  2000/10/31 09:37:13  koy
 * Neuer CVS Baum ab CrypTool Version 1.2.02
 *
 *
 * Revision 1.1.1.1  2000/07/18 07:17:32  gruber
 * no message
 *
 * Revision 1.3  2000/07/17 13:31:49  gruber
 * Änderungen 17.7
 *
 * Revision 1.63  1997/11/14 10:27:55  surkau
 * use identifier for different SC types
 *
 * Revision 1.62  1997/11/13 14:01:07  surkau
 * *** empty log message ***
 *
 * Revision 1.61  1997/10/17 08:05:48  surkau
 * credentials with shared mem
 *
 * Revision 1.60  1997/10/07 15:40:54  surkau
 * sec_gen_key ohne PSE auch fuer DSA/RSA
 *
 * Revision 1.59  1997/09/18 21:17:28  schupp
 * changed DEFAULT_RSA_SIG_ALG handling (SAPSECULIB)
 *
 * Revision 1.58  1997/09/15 12:33:03  schupp
 * changed DEFAULT_RSA_SIG_ALG for SAPSECULIB
 *
 * Revision 1.57  1997/09/10 09:35:19  surkau
 * PSE file size
 *
 * Revision 1.56  1997/09/10 08:32:54  schupp
 * new field fileSize in toc->ext
 *
 * Revision 1.55  1997/08/12 18:28:55  schupp
 * MPSEFile v1
 *
 * Revision 1.54  1997/08/12 10:45:41  schupp
 * pse_name => file_name etc.
 *
 * Revision 1.53  1997/08/06 15:12:17  schupp
 * resolved conflicting typedefs (SEQUENCE_OF_OctetString)
 *
 * Revision 1.52  1997/08/06 14:54:02  schupp
 * added MPSEFile / PSEtype
 *
 * Revision 1.51  1997/07/29 21:22:18  schupp
 * changes for PSEFile v3
 *
 * Revision 1.50  1997/07/24 13:41:19  surkau
 * *** empty log message ***
 *
 * Revision 1.49  1997/07/22 16:50:33  schupp
 * PSEFile version 2 (mac => mic)
 *
 * Revision 1.48  1997/07/16 09:15:38  surkau
 * *** empty log message ***
 *
 * Revision 1.47  1997/06/13 09:25:46  surkau
 * secsc with function pointer
 *
 * Revision 1.46  1997/04/01 10:03:02  schupp
 * NEW_PSE_STRUCT
 *
 * Revision 1.45  1997/02/26 13:03:14  surkau
 * DSA key generation
 *
 * Revision 1.44  1997/02/20 08:25:51  surkau
 * .
 *
 * Revision 1.43  1997/01/29 17:05:37  koletzki
 * *** empty log message ***
 *
 * Revision 1.42  1997/01/27 11:58:59  hschold
 * type of SC_DATA.need_SC changed to int
 *
 * Revision 1.41  1996/10/11 11:23:49  koletzki
 * bad file checked in last time...
 *
 * Revision 1.39  1996/08/23 11:51:03  surkau
 * *** empty log message ***
 *
 * Revision 1.38  1996/07/25 16:22:03  schupp
 * added typedef for PSEObjects
 *
 * Revision 1.37  1996/07/05 16:05:07  surkau
 * *** empty log message ***
 *
 * Revision 1.36  1996/07/05 13:34:03  surkau
 * *** empty log message ***
 *
 * Revision 1.35  1996/04/02 14:46:40  surkau
 * .
 *
 * Revision 1.34  1996/03/21 14:27:42  surkau
 * *** empty log message ***
 *
 * Revision 1.33  1996/01/16 10:34:43  viebeg
 * *** empty log message ***
 *
 * Revision 1.32  1995/12/15 11:40:27  surkau
 * *** empty log message ***
 *
 * Revision 1.31  1995/11/28 07:43:06  viebeg
 * hdl
 *
 * Revision 1.30  1995/11/24 15:11:24  surkau
 * *** empty log message ***
 *
 * Revision 1.29  1995/11/20 14:54:26  surkau
 * hdl
 *
 * Revision 1.28  1995/11/20 12:34:55  surkau
 * hdl
 *
 * Revision 1.27  1995/11/03 11:07:24  surkau
 * single_login
 *
 * Revision 1.26  1995/09/19 07:51:03  viebeg
 * Struktur SCT_Info added.
 *
 * Revision 1.25  1995/09/14 11:34:34  surkau
 * *** empty log message ***
 *
 * Revision 1.24  1995/09/08 09:11:02  surkau
 * *** empty log message ***
 *
 * Revision 1.23  1995/09/08 07:43:36  surkau
 * RSAPrivate > sec.py
 *
 * Revision 1.22  1995/09/07 09:22:48  gloeckne
 * 'getenv'- prototype removed
 *
 * Revision 1.21  1995/08/23 14:07:14  gloeckne
 * externals moved to prototype-file
 *
 * Revision 1.20  1995/08/15 15:30:29  gloeckne
 * arithmetic.h included
 *
 * Revision 1.19  1995/08/11 07:45:34  gloeckne
 * include 'sec_p.h' removed
 *
 * Revision 1.18  1995/07/26 15:47:54  koletzki
 * inserted: ifdef __cpluscplus extern"C" {}
 *
 * Revision 1.17  1995/07/06 14:24:12  gloeckne
 * *** empty log message ***
 *
 * Revision 1.16  1995/06/21  12:15:15  gloeckne
 * *** empty log message ***
 *
 * Revision 1.15  1995/06/16  09:22:56  surkau
 * macros changed
 *
 * Revision 1.14  1995/05/12  08:37:32  koletzki
 * aux_fprint():
 * 	changed aux_print_usage_exit()
 * 	to aux_print_usage() without exit call
 *
 * AUX_PRINT_USAGE_EXIT() is a new macro for utilities
 *
 * Revision 1.13  1995/04/04  16:08:34  koletzki
 * Equalized option parser with usage output
 *
 * Revision 1.12  1995/04/04  13:10:58  koletzki
 * ProgramUsage type changed
 * Equalized option parser with usage output
 *
 * Revision 1.11  1995/04/04  11:24:07  koletzki
 * *** empty log message ***
 *
 * Revision 1.10  1995/04/04  09:26:18  koletzki
 * *** empty log message ***
 *
 * Revision 1.9  1995/04/04  09:07:16  koletzki
 * aux_fprint.c: new function
 * 	void aux_print_usage_exit(	ProgramUsage Usage,
 * 					int Level);
 *
 * 	use only for executable programs!
 * 	function exits -1
 *
 * Revision 1.8  1995/02/21  14:50:53  surkau
 * crypt and sca library
 *
 * Revision 1.7  1994/12/02  09:10:48  schneiw
 * *** empty log message ***
 *
 * Revision 1.6  1994/11/09  09:16:12  surkau
 * new function aux_file_type
 *
 * Revision 1.5  1994/11/02  10:44:39  surkau
 * Header replaced by Id
 *
 * Revision 1.4  1994/11/02  09:39:08  surkau
 * SecuDE-4.4.a0
 *
 *
 */
 
/********************************************************************
 * Copyright (C) 1990-1994, GMD Darmstadt. All rights reserved.     *
 *                                                                  *
 *                                                                  *
 *                         NOTICE                                   *
 *                                                                  *
 *    Acquisition, use, and distribution of this module             *
 *    and related materials are subject to restrictions             *
 *    mentioned in each volume of the documentation.                *
 *                                                                  *
 ********************************************************************/

/*-----------------------------------------------------------------------*/
/* INCLUDE FILE  secure.h                                                */
/* Definition of structures and types for the basic security functions   */
/*-----------------------------------------------------------------------*/

#ifndef _SECURE_
#define _SECURE_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "arithmet.h"

#ifdef SAPSECULIB
#define DEFAULT_RSA_SIG_ALG SAPSECULIB_RSA_ALG
#else
#define DEFAULT_RSA_SIG_ALG md5WithRsaEncryption
#endif
#define DEFAULT_DSA_SIG_ALG dsaWithSHA1
#define DEFAULT_DSACommon_SIG_ALG dsaCommonWithSHA1

#ifdef SEC_PC
#define chmod(a,b)
#endif /*SEC_PC*/


typedef SET_OF(OctetString)     SET_OF_OctetString;

typedef SET_OF(ObjId)           SET_OF_ObjId;
typedef struct Key              Key;
typedef struct PSE_Sel          PSESel;
typedef struct PSE_Toc          PSEToc;
typedef struct PSE_Object       PSEObject;
typedef struct PSE_Objects      PSEObjects;

/*-----------------------------------------------------------------------*/
/*    P S E                                                              */
/*-----------------------------------------------------------------------*/

#include "filename.h"


typedef enum {
        ERR_in_psetest = -1,
        SWpse = 0, 
        SCpse = 1 
} PSELocation;

typedef struct SC_DATA SC_DATA;

struct SC_DATA {
	int		 need_pin;
	int		 enter_pin_on_SCT;
	int		 need_SC;
        int  		 sct_id;
	int		 SC_timer;
	char		*puk;
	int		 pin_counter;
	int		 puk_counter;
	void		*data;
	char		*product_info;
	char		*sct;
	char		*sc;
};
#define NEED_SC_TO_GET_SC_DATA 0x7f

typedef struct PSE_Info PSE_Info;

#ifdef NEW_PSE_STRUCT
typedef enum PSEFlushMode {
    PSEfm_atOnce,
    PSEfm_onClose
} PSEFlushMode;
#endif

typedef enum PSEtype {
    PSEt_error = -1,
    PSEt_not_exist = 0,
    PSEt_directory,
    PSEt_file,
    PSEt_multiple
} PSEtype;


struct PSE_Info {
	char    *pse_name;
	char    *sw_pin;
	char    *sc_pin;
        PSEToc  *toc;
        PSEToc  *sc_toc;
	SC_DATA *sc_data;
#ifdef NEW_PSE_STRUCT
	PSEFlushMode flushMode;
	PSEtype	pse_type;
	int	mpse_sel;
#endif
	char	*file_name;
};

struct PSE_Sel {
        char    *object;         /* object name                     */
        ObjId   *object_type;    /* object type                     */
        void    *info;
};


/*
 *      Table of Contents of PSE
 */

typedef SEQUENCE_OF(OctetString) SEQUENCE_OF_OctetString;

#ifdef NEW_PSE_STRUCT
typedef struct PSE_Objects PSEObj;
typedef SET_OF(PSEObj) SET_OF_PSEObj;
typedef PSEToc PSECont;
typedef PSEToc EncPSECont;
typedef PSEToc SigPSECont;
typedef PSEToc CmpPSECont;
typedef PSEToc PSEFile;

typedef struct MPSEFileEntry {
    char *label;
    OctetString *psef;
} MPSEFileEntry;

typedef SEQUENCE_OF(MPSEFileEntry) SEQ_OF_MPSEFileEntry;

typedef struct MPSEFile {
    int version;
    SEQ_OF_MPSEFileEntry *pses;
} MPSEFile;

/*typedef SEQUENCE_OF_OctetString MPSEFile;*/

typedef enum PSEObjState {
    PSEObj_absent = 0,
    PSEObj_normal,
    PSEObj_isEncrypted,
    PSEObj_isKey
} PSEObjState;

typedef struct PSEKeyStruct {
    int		 keyId;
    AlgId	*algorithm;	/* OPTIONAL: NULL if absent */
    int		 keyLength;	/* OPTIONAL: 0 if absent */
    OctetString *cont;
} PSEKeyStruct;

typedef struct PSEObjValue {
    PSEObjState		 state;
    PSEKeyStruct	*keyStruct;
    OctetString		*obj;
} PSEObjValue;

typedef enum PSEWriteMode {
    PSEwm_noEncrypt = 0,
    PSEwm_encryptAll,
    PSEwm_encryptSome
} PSEWriteMode;

typedef enum PSECompressionMode {
    PSEcm_compressed = -1, /* if encrypted & compressed */
			   /* => method not available yet */
    PSEcm_noCompress = 0,
    PSEcm_zlib09
} PSECompressionMode;    

typedef struct PSEExt {
    /* internal management */
    PSEWriteMode	 writeMode;
    PSECompressionMode	 compressionMode; /* used in version 3 */
    Boolean		 dirty;
    /* field of PSEFile structure */
    int			 version;	/* initial version: 1 */
    OctetString		*encryptedPin;
    AlgId		*encAlg;
    AlgId		*micAlg;
    OctetString		*micOrEnc;
    OctetString		*compressed;
    char		*cardId;
    /* fields of PSECont structure */
    char		*caPath;
    OctetString		*extPin;
    char		*extPath;
    /* new 10.9.97 */
    int			 fileSize;
    int			 fileSize_avail;
} PSEExt;
#endif

struct PSE_Toc {
        char                    *owner;
        UTCTime                 *create;
        UTCTime                 *update;
        unsigned int            status;
        struct PSE_Objects      *obj;
#ifdef NEW_PSE_STRUCT
        PSEExt			*ext;
        SET_OF_PSEObj		*objset;
#endif
};

struct PSE_Objects {
        char                    *name;
        UTCTime                 *create;
        UTCTime                 *update;
        int                     noOctets;
        unsigned int            status;
        struct PSE_Objects      *next;
#ifdef NEW_PSE_STRUCT
        ObjId			*objType;
        PSEObjValue		*value;
#endif
};

struct PSE_Object {
        ObjId         *objectType;
        OctetString   *objectValue;
};



typedef enum {
        ERR_in_pseconfig = -1,
        NOT_ON_SC, 
        PSE_ON_SC, 
        FILE_ON_SC, 
        KEY_ON_SC
} PSEConfig;

PSEConfig sec_pseconfig();



typedef enum {
        ERR_in_scttest = -1,
        SCTDev_not_avail = 0, 
        SCTDev_avail = 1,
        SCTDev_lock = 2,
        SCTDev_not_config = 3
} SCTDevice;


typedef struct SCT_Info   {

	Boolean	    keyboard;	        /* if TRUE, SCT contains keyboard */

	Boolean     display;	        /* if TRUE, SCT contains display */

	Boolean	    crypto;		/* if TRUE, SCT supports
					   cryptographic functions */
	    } SCT_Info;



/*-----------------------------------------------------------------------*/
/*    K e y ' s   and   S i g n a t u r e                                */
/*-----------------------------------------------------------------------*/



struct Key {
        KeyInfo  *key;
        PSESel   *pse_sel;
        AlgId    *alg;
        char	 *add_object;
        ObjId	 *add_object_type;
        int	  key_size;
        KeyInfo  *private_key;
};



                 

/*
 * Program Usage
 */
#define		MAX_SHORT_HELP_LINES	15
#define		MAX_LONG_HELP_LINES	100
#define 	SHORT_HELP 		0
#define 	LONG_HELP 		1
typedef struct {
	char	*program;
	char	*purpose;
	char	*options;
	char	*short_help[MAX_SHORT_HELP_LINES];
	char	*long_help[MAX_LONG_HELP_LINES];
} ProgramUsage;



/*
 *  sec_asn1_length_encoding controls the ASN.1 length encoding of the 
 *  e_*() functions. DEFINITE or INDEFINITE encoding can be chosen.
 *  For the sake of distinguished ASN.1 encoding either of the two 
 *  methods must be agreed and fixed between all participants of the
 *  security infrastructure. X.509 says DEFINITE shall be used for
 *  DER encoding. sec_asn1_length_encoding is defined in sec_init.c
 *  and set to DEFINITE by default.
 *
 *  Don't change this parameter unless you are sure what you are doing, 
 *  otherwise the verification of certificates could yield some surprises.
 */ 

#define INDEFINITE 1
#define DEFINITE   2

#define ONEKEYPAIRONLY   1
#define FINGERPRINT_ALG  md5		/* SECUDE fingerprint */
#define MSBITINBYTE 0x80


#ifdef SCA
#include "secsc.h"
#endif



/*
 * Force exit from process
 * Only for utilities
 */
#define AUX_PRINT_USAGE_EXIT(usage, help)	{ aux_print_usage(&usage, help); return(-1); }

#include "sec_p.h"
#include "isode_p.h"

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* _SECURE_ */
