/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

#ifndef _INSTALL_
#define _INSTALL_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


struct s_record {
        char      port_name[24];
	int	  pn;
        int       bwt;
        int       cwt;
        int       baud;
        int       databits;
        int       stopbits;
        int       parity;
        int       dataformat;
        int       tpdu_size;
        int       apdu_size;
        int       edc;
	char	  ct_type[5];
	char	  wki[7];		  /* well known identifier */
	int	  version;
	char	  doku[30]; 

        };


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* _INSTALL_ */


  

